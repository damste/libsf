#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <process.h>
#include <errno.h>
#include <dos.h>

#include "defs.inc"
#include "ed_hdr.h"
#include "ed.inc"
#include "keylist.inc"          // Keyboard variables (used for macros)

void main(int argc,char *argv[])        // function
{
    FILE *tfh;
    char *tptr;
    char huge *hptr;
    struct FILE_RECORD *fiptr;
    struct FUNC_RECORD *fuptr;
    struct FILE_RECORD huge *ffiptr;
    struct FUNC_RECORD huge *ffuptr;
    ulong load_size;
    ulong i;
    ushort numread, key;
    char filename[128];
    char funcname[128];
    char cah, cal;

  // Reduce allocated memory to 64k
    _asm {
        mov     ax,cs
        mov     es,ax
        mov     ah,0x4a
        mov     bx,0x1000
        int     0x21
    }


  // Tell the world who we are
    printf("Exodus File/Function Manager, May.28.2001\n");
    printf("Beatleworks, Inc. 2001\n\n");


  // See if there are any command lines
    if (argc > 1) {
        if (strnicmp(argv[1],"/newmac",7) == 0) {
            printf("Creating MACROS.DAT, ");
            fh = fopen("macros.dat","w+");
            if (fh == NULL) {
                printf("ERROR!\n\n");
            } else {
                printf("writing header, ");
                for (i=0; i<MAX_MACROS; i++) {
                    macro[i].key = 0xffff;
                    macro[i].num_keys = 0;
                    macro[i].start_offset = 0xffff;
                    full_strnset(macro[i].desc, 32, sizeof(macro[i].desc));
                }
                if (fwrite(macro, sizeof(struct MACRO_RECORD), MAX_MACROS, fh) == 0) {
                    printf("ERROR!\n\n");
                } else {
                    printf("done.\n\n");
                    fclose(fh);
                }
            }
            exit(0);
        }
        if (strnicmp(argv[1],"/new",4) == 0) {
            printf("Creating ED.DAT, ");
            fh = fopen("ed.dat","w+");
            if (fh == NULL) {
                printf("ERROR!\n\n");
            } else {
                printf("writing header, ");
                header.first_file_offset = -1;
                header.next_avail_offset = sizeof(header);
                header.file_records = 0;
                header.func_records = 0;
                if (fwrite(&header, 1, sizeof(header), fh) == 0) {
                    printf("ERROR!\n\n");
                } else {
                    printf("done.\n\n");
                    fclose(fh);
                }
            }
            exit(0);
        }
        if (strnicmp(argv[1],"/big",4) == 0) {
            extra_space = 80000;
        }
        for (i=2; i<argc; i++) {
            printf("Ignored '%s'\n",argv[i]);
        }
    }


  cont:
  // Open the file
    fh = fopen("ed.dat","rb+");
    if (fh == NULL) {
        printf("Error opening ED.DAT\nUse: ED /new\n");
        exit(-1);
    }


  // Find out how big the file is
    fseek(fh,0,SEEK_END);
    load_size = ftell(fh) - sizeof(struct FILE_HDR);
    fseek(fh,0,SEEK_SET);


  // Allocate memory for load
    buf = (char huge *)halloc((load_size+extra_space),1);
    if (buf == NULL) {
        printf("Out of memory\n");
    }
    buf_end = buf + load_size + extra_space;
    full_strnset_far(buf, buf_end, (char)0xff);


  // Read the file into memory
    printf("Loading, ");
    numread = fread(&header,1,sizeof(header),fh);
    i = 0;
    bptr = buf;
    while (i < load_size) {
        numread = fread(load_buf,1,sizeof(load_buf),fh);
        i += numread;
        tptr = (char *)load_buf;
        while (numread-- > 0) {
            *bptr++ = *tptr++;
        }
    }
    highlighted_file = header.first_file_offset;
    if (highlighted_file != -1) {
        ffiptr = (struct FILE_RECORD huge *)(buf + highlighted_file);
        highlighted_function = ffiptr->first_func;
    }
    printf("done.\n");

  // Load the keyboard macros (if any)
    load_macros();


  // Enter 132x80 video mode
  // Load the 8x6 font
    if ((tfh = fopen("font8x6.dat","rb")) == NULL) {
        printf("Error opening font8x6.dat.\nUsing 132x60 mode.\n");
        while (!kbhit());
        max_rows = 60;
    } else {
        numread = fread(load_buf,1,256*6,tfh);
        if (numread != 1536) {
            printf("Error reading from font8x6.dat.\nFile should be 1536 bytes.\n");
            max_rows = 60;
        } else {
            max_rows = 80;
        }
        fclose(tfh);
    }

    _asm {
        pusha

      // Set 132x60 video mode (VESA BIOS request)
        mov     ax,0x4f02
        mov     bx,0x10c
        int     0x10

      // Turn high intensity colors on
        call    turn_high_intensity_on

        cmp     max_rows,60
        jz      skip_it
      // Set our 8x6 font
        push    es
        mov     dx,ds
        mov     es,dx
        mov     ax,0x1110
        mov     bx,0x0600
        mov     cx,0x0100
        xor     dx,dx
        mov     bp,offset load_buf
        int     10h
        pop     es

      skip_it:
        popa
    }


  // Display the screen, get the input, etc.
    column = 1;
  redraw_screen:
    main_screen();
  redraw_functions:
    if (column == 1) {
        draw_files(1);
        origin_column = 1;
    } else {
        draw_files(0);
    }
    if (column == 2) {
        draw_functions(1);
        origin_column = 2;
    } else {
        draw_functions(0);
    }

    while (1) {
        key = get_a_key();
      process_key:
        switch (key) {
          case insert:
          case grey_insert:
            switch (column) {
              case 1:
                add_file();
                break;
              case 2:
                add_function();
                break;
            }
            goto redraw_screen;
            break;
          case up:
          case grey_up:
            switch (column) {
              case 1:
                if (highlighted_file != -1) {
                    ffiptr = (struct FILE_RECORD huge *)(buf + highlighted_file);
                    if (ffiptr->prev_file != -1) {
                        highlighted_file = ffiptr->prev_file;
                      highlight_column1:
                        ffiptr = (struct FILE_RECORD huge *)(buf + highlighted_file);
                        highlighted_function = ffiptr->first_func;
                    }
                }
                break;
              case 2:
                if (highlighted_function != -1) {
                    ffuptr = (struct FUNC_RECORD huge *)(buf + highlighted_function);
                    if (ffuptr->prev_func != -1) {
                        highlighted_function = ffuptr->prev_func;
                    }
                }
                break;
            }
            goto redraw_functions;
          case down:
          case grey_down:
            switch (column) {
              case 1:
                if (highlighted_file != -1) {
                    ffiptr = (struct FILE_RECORD huge *)(buf + highlighted_file);
                    if (ffiptr->next_file != -1) {
                        highlighted_file = ffiptr->next_file;
                    }
                    goto highlight_column1;
                }
                break;
              case 2:
                if (highlighted_function != -1) {
                    ffuptr = (struct FUNC_RECORD huge *)(buf + highlighted_function);
                    if (ffuptr->next_func != -1) {
                        highlighted_function = ffuptr->next_func;
                    }
                }
            }
            goto redraw_functions;
          case tab:
          case right:
          case grey_right:
            if (column == 1) {
                if (highlighted_file != -1) {
                    ++column;
                }
            }
            goto redraw_screen;
          case shift_tab:
          case left:
          case grey_left:
            if (column > 1) {
                --column;
            }
            if (column == 1) {
                goto highlight_column1;
            }
            goto redraw_screen;
          case pgdn:
          case grey_pgdn:
            max_rows = 71;
          scroll_down_xx_columns:
            switch (column) {
              case 1:
                ffiptr = (struct FILE_RECORD huge *)(buf + highlighted_file);
                i = 0;
                while (i < max_rows && ffiptr->next_file != -1) {
                    highlighted_file = ffiptr->next_file;
                    ffiptr = (struct FILE_RECORD huge *)(buf + ffiptr->next_file);
                    ++i;
                }
                goto redraw_functions;
              case 2:
                ffuptr = (struct FUNC_RECORD huge *)(buf + highlighted_function);
                i = 0;
                while (i < max_rows && ffuptr->next_func != -1) {
                    highlighted_function = ffuptr->next_func;
                    ffuptr = (struct FUNC_RECORD huge *)(buf + ffuptr->next_func);
                    ++i;
                }
                goto redraw_functions;
            }
            break;
          case pgup:
          case grey_pgup:
            max_rows = 71;
          scroll_up_xx_columns:
            switch (column) {
              case 1:
                ffiptr = (struct FILE_RECORD huge *)(buf + highlighted_file);
                i = 0;
                while (i < max_rows && ffiptr->prev_file != -1) {
                    highlighted_file = ffiptr->prev_file;
                    ffiptr = (struct FILE_RECORD huge *)(buf + ffiptr->prev_file);
                    ++i;
                }
                goto redraw_functions;
              case 2:
                ffuptr = (struct FUNC_RECORD huge *)(buf + highlighted_function);
                i = 0;
                while (i < max_rows && ffuptr->prev_func != -1) {
                    highlighted_function = ffuptr->prev_func;
                    ffuptr = (struct FUNC_RECORD huge *)(buf + ffuptr->prev_func);
                    ++i;
                }
                goto redraw_functions;
            }
            break;
          case home:
          case grey_home:
            switch (column) {
              case 1:
                highlighted_file = header.first_file_offset;
                goto redraw_functions;
              case 2:
                ffiptr = (struct FILE_RECORD huge *)(buf + highlighted_file);
                highlighted_function = ffiptr->first_func;
                goto redraw_functions;
            }
            break;
          case end:
          case grey_end:
            switch (column) {
              case 1:
                ffiptr = (struct FILE_RECORD huge *)(buf + highlighted_file);
                while (ffiptr->next_file != -1) {
                    highlighted_file = ffiptr->next_file;
                    ffiptr = (struct FILE_RECORD huge *)(buf + ffiptr->next_file);
                }
                goto redraw_functions;
              case 2:
                ffuptr = (struct FUNC_RECORD huge *)(buf + highlighted_function);
                i = 0;
                while (ffuptr->next_func != -1) {
                    highlighted_function = ffuptr->next_func;
                    ffuptr = (struct FUNC_RECORD huge *)(buf + ffuptr->next_func);
                }
                goto redraw_functions;
            }
            break;
          case enter:
          case grey_enter:
            switch (column) {
              case 1:
                edit_file();
                break;
              case 2:
                edit_function();
                break;
            }
            break;
          case f5:
            ffiptr = (struct FILE_RECORD huge *)(buf + highlighted_file);
            hptr = (char huge *)filename;
            full_strnset_far(hptr, hptr + sizeof(filename), 0);
            full_strncpy((char huge *)filename, (char huge *)ffiptr->name, populated_string_length((char huge *)ffiptr->name,sizeof(ffiptr->name)));
            switch (column) {
              case 1:
                spawnlp(P_WAIT, "e", "e", (char *)filename, NULL);
                break;
              case 2:
                ffuptr = (struct FUNC_RECORD huge *)(buf + highlighted_function);

                // Do the function name
                hptr = (char huge *)funcname;
                full_strnset_far(hptr, hptr + sizeof(funcname), 0);
                full_strncpy(hptr,(char huge *)"-g",2);
                full_strncpy(hptr+2,(char huge *)ffuptr->name, populated_string_length((char huge *)ffuptr->name,sizeof(ffuptr->name)));
                spawnlp(P_WAIT, "e", "e", (char *)filename, (char *)funcname, NULL);
                break;
            }
            turn_high_intensity_on();
            break;
          case escape:
            key = get_a_key();
            if (key == escape) {
                goto quit;
            } else {
                goto process_key;
            }
          case f10:
            save_file();
            save_macros();
            break;
          default:
            _asm {
                mov     ax,key
                mov     cah,ah
                mov     cal,al
            }
            switch (cal) {
              case '+':
                switch (column) {
                  case 1:
                    // Scan forward for the "-------" lines
                    max_rows = 10;
                    ffiptr = (struct FILE_RECORD huge *)(buf + highlighted_file);
                    if (ffiptr->next_file != -1) {
                        i = 0;
                        goto skip_one_automatically1;
                        while (i < max_rows && ffiptr->next_file != -1 && full_strncmp((char huge *)ffiptr->name,(char huge *)"-----",5) != 0) {
                          skip_one_automatically1:
                            highlighted_file = ffiptr->next_file;
                            ffiptr = (struct FILE_RECORD huge *)(buf + ffiptr->next_file);
                            ++i;
                        }
                        // Right now, we're on the "-----" line.  See if we can go one more (so we're not on a useless line)
                        if (ffiptr->next_file != -1 && i < max_rows) {
                            highlighted_file = ffiptr->next_file;
                        }
                        goto redraw_functions;
                    }
                    break;
                  case 2:
                    max_rows = 5;
                    goto scroll_down_xx_columns;
                }
                break;
              case '-':
                switch (column) {
                  case 1:
                    // Scan backwards for the "-------" lines
                    max_rows = 10;
                    ffiptr = (struct FILE_RECORD huge *)(buf + highlighted_file);
                    if (ffiptr->prev_file != -1) {
                        i = 0;
                        goto skip_one_automatically2;
                        while (i < max_rows && ffiptr->prev_file != -1 && full_strncmp((char huge *)ffiptr->name,(char huge *)"-----",5) != 0) {
                          skip_one_automatically2:
                            highlighted_file = ffiptr->prev_file;
                            ffiptr = (struct FILE_RECORD huge *)(buf + ffiptr->prev_file);
                            ++i;
                        }
                        // Right now, we're on the "-----" line.  See if we can go one more (so we're not on a useless line)
                        if (ffiptr->prev_file != -1 && i < max_rows) {
                            highlighted_file = ffiptr->prev_file;
                        }
                        goto redraw_functions;
                    }
                    break;
                  case 2:
                    max_rows = 5;
                    goto scroll_up_xx_columns;
                }
                break;
            }
            break;
        }
    }


  // Write the changes
  quit:
    clear_screen();

  // Finished
    exit(0);
}


#include "extras.c"
