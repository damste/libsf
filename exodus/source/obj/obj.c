#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <process.h>
#include <errno.h>
#include <dos.h>

#include "defs.inc"
#include "obj_hdr.h"
#include "obj.inc"
#include "keylist.inc"          // Keyboard variables (used for macros)

void main(int argc,char *argv[])
{
    FILE *tfh;
    char *tptr;
    struct BO_RECORD *boptr;
    struct O_RECORD *optr;
    struct PROP_RECORD *pptr;
    struct EVENT_RECORD *eptr;
    struct BO_RECORD huge *fboptr;
    struct O_RECORD huge *foptr;
    struct PROP_RECORD huge *fopptr;
    struct EVENT_RECORD huge *foeptr;
    ulong load_size;
    ulong i;
    ushort numread, key;

  // Reduce allocated memory to 64k
    _asm {
        mov     ax,cs
        mov     es,ax
        mov     ah,0x4a
        mov     bx,0x1000
        int     0x21
    }


  // Tell the world who we are
    printf("Exodus OBJECT Manager, May.11.2001\n");
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
            printf("Creating OBJ.DAT, ");
            fh = fopen("obj.dat","w+");
            if (fh == NULL) {
                printf("ERROR!\n\n");
            } else {
                printf("writing header, ");
                header.first_bo_offset = -1;
                header.next_avail_offset = sizeof(header);
                header.bo_records = 0;
                header.o_records = 0;
                header.prop_records = 0;
                header.event_records = 0;
                if (fwrite(&header, 1, sizeof(header), fh) == 0) {
                    printf("ERROR!\n\n");
                } else {
                    printf("done.\n\n");
                    fclose(fh);
                }
            }
            exit(0);
        }
        for (i=2; i<argc; i++) {
            printf("Ignored '%s'\n",argv[i]);
        }
    }


  cont:
  // Open the file
    fh = fopen("obj.dat","rb+");
    if (fh == NULL) {
        printf("Error opening OBJ.DAT\nUse: OBJ /new\n");
        exit(-1);
    }


  // Find out how big the file is
    fseek(fh,0,SEEK_END);
    load_size = ftell(fh) - sizeof(struct FILE_HDR);
    fseek(fh,0,SEEK_SET);


  // Allocate memory for load
    buf = (char huge *)halloc((load_size+80000),1);
    if (buf == NULL) {
        printf("Out of memory\n");
    }
    buf_end = buf + load_size + 80000;
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
    highlighted_base_object = header.first_bo_offset;
    if (highlighted_base_object != -1) {
        fboptr = (struct BO_RECORD huge *)(buf + highlighted_base_object);
        highlighted_object = fboptr->first_o;
        highlighted_property = fboptr->first_prop;
        highlighted_event = fboptr->first_event;
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
        mov     ax,0x1003
        xor     bl,bl
        int     0x10

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
  redraw_objects:
    if (column == 1) {
        draw_base_objects(1);
        origin_column = 1;
    } else {
        draw_base_objects(0);
    }
    if (column == 2) {
        draw_objects(1);
        origin_column = 2;
    } else {
        draw_objects(0);
    }
    if (column == 3) {
        draw_properties(1);
    } else {
        draw_properties(0);
    }
    if (column == 4) {
        draw_events(1);
    } else {
        draw_events(0);
    }

    while (1) {
        key = get_a_key();
      process_key:
        switch (key) {
          case insert:
          case grey_insert:
            switch (column) {
              case 1:
                add_base_object();
                break;
              case 2:
                add_object();
                break;
              case 3:
                add_property();
                break;
              default:
                add_event();
                break;
            }
            goto redraw_screen;
            break;
          case up:
          case grey_up:
            switch (column) {
              case 1:
                if (highlighted_base_object != -1) {
                    fboptr = (struct BO_RECORD huge *)(buf + highlighted_base_object);
                    if (fboptr->prev_bo != -1) {
                        highlighted_base_object = fboptr->prev_bo;
                      highlight_column1:
                        fboptr = (struct BO_RECORD huge *)(buf + highlighted_base_object);
                        highlighted_object = fboptr->first_o;
                        highlighted_property = fboptr->first_prop;
                        highlighted_event = fboptr->first_event;
                    }
                }
                break;
              case 2:
                if (highlighted_object != -1) {
                    foptr = (struct O_RECORD huge *)(buf + highlighted_object);
                    if (foptr->prev_o != -1) {
                        highlighted_object = foptr->prev_o;
                      highlight_column2:
                        if (highlighted_object == -1) {
                            highlighted_property = -1;
                            highlighted_event = -1;
                        } else {
                            foptr = (struct O_RECORD huge *)(buf + highlighted_object);
                            highlighted_property = foptr->first_prop;
                            highlighted_event = foptr->first_event;
                        }
                    }
                }
                break;
              case 3:
                if (highlighted_property != -1) {
                    fopptr = (struct PROP_RECORD huge *)(buf + highlighted_property);
                    if (fopptr->prev_prop != -1) {
                        highlighted_property = fopptr->prev_prop;
                    }
                }
                break;
              case 4:
                if (highlighted_event != -1) {
                    foeptr = (struct EVENT_RECORD huge *)(buf + highlighted_event);
                    if (foeptr->prev_event != -1) {
                        highlighted_event = foeptr->prev_event;
                    }
                }
                break;
            }
            goto redraw_objects;
          case down:
          case grey_down:
            switch (column) {
              case 1:
                if (highlighted_base_object != -1) {
                    fboptr = (struct BO_RECORD huge *)(buf + highlighted_base_object);
                    if (fboptr->next_bo != -1) {
                        highlighted_base_object = fboptr->next_bo;
                    }
                    goto highlight_column1;
                }
                break;
              case 2:
                if (highlighted_object != -1) {
                    foptr = (struct O_RECORD huge *)(buf + highlighted_object);
                    if (foptr->next_o != -1) {
                        highlighted_object = foptr->next_o;
                    }
                    goto highlight_column2;
                }
              case 3:
                if (highlighted_property != -1) {
                    fopptr = (struct PROP_RECORD huge *)(buf + highlighted_property);
                    if (fopptr->next_prop != -1) {
                        highlighted_property = fopptr->next_prop;
                    }
                }
                break;
              case 4:
                if (highlighted_event != -1) {
                    foeptr = (struct EVENT_RECORD huge *)(buf + highlighted_event);
                    if (foeptr->next_event != -1) {
                        highlighted_event = foeptr->next_event;
                    }
                }
                break;
            }
            goto redraw_objects;
          case tab:
          case right:
          case grey_right:
            switch (column) {
              case 1:
                if (highlighted_base_object != -1) {
                    ++column;
                }
                goto highlight_column2;
              case 2:
                if (highlighted_object != -1) {
                    ++column;
                }
                break;
              case 3:
                ++column;
                break;
            }
            goto redraw_screen;
          case shift_tab:
          case left:
          case grey_left:
            if (column > 1) {
                --column;
            }
            switch (column) {
              case 1:
                goto highlight_column1;
              case 2:
                goto highlight_column2;
            }
            goto redraw_screen;
          case pgdn:
          case grey_pgdn:
            break;
          case pgup:
          case grey_pgup:
            break;
          case home:
          case grey_home:
            break;
          case end:
          case grey_end:
            break;
          case enter:
          case grey_enter:
            switch (column) {
              case 1:
                edit_base_object();
                break;
              case 2:
                edit_object();
                break;
              case 3:
                edit_property();
                break;
              case 4:
                edit_event();
                break;
            }
            goto redraw_screen;
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
            goto quit;
          case f3:
            if (column == 1) {
                column = 3;
            }
            goto redraw_screen;
          case f4:
            if (column == 1) {
                column = 4;
            }
            goto redraw_screen;
        }
    }


  // Write the changes
  quit:
    clear_screen();

  // Finished
    exit(0);
}


#include "extras.c"
