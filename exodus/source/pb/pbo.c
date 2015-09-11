//////////
//
// pb.c
//
/////
//
// This routine puts the boot programs on a floppy disk.
//
//   boot.com        - Boot sector loader
//   bootup.com      - Exodus Boot Loader
//   exodus.ini      - Required to indicate what drivers are installed
//   xxxxxxx.drv     - Any drivers required by the exodus.ini file
//
// These items are placed in the first DT entries.  They are sequential on the disk (meaning they start at a particular
// sector and continue sector after sector until the full extent of the file has been loaded).  The only records that
// include NP records are the drivers themselves.  BOOT.COM, BOOTUP.COM and EXODUS.INI do not have names in the NP because
// their file types are uniquely identified in the DT structure records.  The other drivers do have names in the NP.  All
// files have entries in the RP.
//
// This program loads the following file from the command line and parses it, loading the files within.
//   pb.ini
//
// PB.INI contains this type of structure:
//
//   B|boot.com                 ; B indicates it is the boot sector                 * Required
//   L|bootup.com               ; L indicates it is the Exodus Loader program       * Required
//   S|special.com              ; S indicates it is a special Exodus Loader program * Optional, cannot exist with L|bootup.com
//   I|exodus.ini               ; I indicates it is the exodus.ini file             * Required
//   D|path\name1.drv name1.map ; D indicates it is a driver                        * Optional
//   D|path\name2.drv name2.map
//   D|path\name3.drv name3.map


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <math.h>
#include <malloc.h>

#include "pb.h"
#include "defs.inc"


//int main(int argc, char *argv[])
int main(void)
{
    FILE *fh;
    uint line_no, i;
    uchar *tptr;
    ulong bufptr, num;
    ushort key;
    int save_value;
    ulong entries_written;

    _asm {
      // Reduce allocated memory to 64k
        mov     ax,cs
        mov     es,ax
        mov     ah,0x4a
        mov     bx,0x1000
        int     0x21
        jc      memory_error

        mov     bx,(192 * 1024 / 16) + 1                            // Allocate 192k
        mov     ah,0x48
        int     0x21
        jc      memory_error
        mov     dx,ax
        mov     cl,4
        shl     ax,cl
        mov     cl,12
        shr     dx,cl
        mov     word ptr bufptr[0],ax
        mov     word ptr bufptr[2],dx
    }
    goto please_continue;

  memory_error:
    display_text("¯ÀUnable to allocate memory.  Fatal error.  Terminating.;");
    goto get_a_key_quit;


  please_continue:
    //set_video_mode();
    //clear_screen();
    //main_screen();


  // Initialize the buffers
    full_strnset(line_buffer, 32, sizeof(line_buffer));
    full_strnset(list_buffer, 32, sizeof(list_buffer));
    full_strnset(boot_sector, 0xcc, sizeof(boot_sector));
    full_strnset(dt_buffer, 0xff, sizeof(dt_buffer));
    full_strnset(np_buffer, 0xff, sizeof(np_buffer));
    full_strnset(rp_buffer, 0xff, sizeof(rp_buffer));
    dt_offset = 2;
    np_offset = 2;
    rp_offset = 2;

  // Load PB.INI
    display_text("¯ŸLoading PB.INI...;");
    pb_fh = fopen("pb.ini","rb");
    if (pb_fh == NULL) {
        display_text("¯Àunable to open¯;");
        goto get_a_key_quit;
    }
    pb_num = fread(pb_ini_buffer,1,sizeof(pb_ini_buffer),pb_fh);
    strcpy(line_buffer,"Loaded");
    strcpy(&line_buffer[7],convert_dword_to_decimal(pb_num));
    add_to_line_buffer();
    if (pb_num == 1024) {
        display_text("*** Warning:  Load reached max allocated space (1k).  Possible data loss.;");
    }

  // Initialize the global pointers
    dt_ptr = (char*)dt_buffer+2;
    *(ushort *)dt_ptr = 0xffff;
    np_ptr = (char*)np_buffer+2;
    *(ushort *)np_ptr = 0xffff;
    rp_ptr = (char*)rp_buffer+2;
    *(ushort *)rp_ptr = 0xffff;

    line_no = 0;
    entries_written = 0;
    pbptr = (char *)pb_ini_buffer;
    end_pbptr = pbptr + pb_num;
    while (pbptr < end_pbptr) {
      // Skip past white spaces
        while ((*pbptr == ' ' || *pbptr == 9) && pbptr < end_pbptr) {
            ++pbptr;
        }
        if (*pbptr == ';' || *(ushort *)pbptr == 0x0d0a || *(ushort *)pbptr == 0x0a0d) {
          // It's a comment
            goto skip_to_next_line;
        }

        if (*(pbptr+1) != '|') {
            display_text("¯ÀSyntax error on line:;");
          error_line_info:
            strcpy(&line_buffer[0],convert_dword_to_decimal(line_no));
            line_buffer[4] = '³';
            tptr = &line_buffer[5];
            i = 0;
            while (i < 70 && *(ushort *)(pbptr+i) != 0x0d0a && *(ushort *)(pbptr+i) != 0x0a0d && pbptr+i < end_pbptr) {
                *tptr++ = *(pbptr+(i++));
            }
            if (i == 70 && *(ushort *)(pbptr+i) != 0x0d0a && *(ushort *)(pbptr+i) != 0x0a0d) {
                *(ulong *)tptr = 0x2e2e2e2e;        // Add a "...." (to indicate more of the line goes here)
            }
            add_to_line_buffer();
            goto get_a_key_quit;
        }

      // Get ready
        full_strnset(file_open, 0, sizeof(file_open));

      // See what the item is
        tptr = pbptr + 2;
        tptr = copy_filename(file_open,tptr);
        if ((fh = fopen(file_open,"rb+")) == NULL) {
            display_text("¯ÀFile open error on line:;");
            display_text(file_open);
            goto error_line_info;
        }
        switch (*pbptr) {
          case 'B':
          case 'b':
          // It's the boot record (boot.bin)
          // This one is always known to be 512 bytes
          // This one does not have an entry in the DT
            display_text("¯ŸBOOT.BIN;");
            num = fread(boot_sector, 1, 512, fh);
            full_copy(load_sector, boot_sector, 512);
            display_text("  Loaded 512;");
            gFile_data[gFile_data_count].type = 'B';

          // Write it to floppy disk
            num = write_sector(0,1,0,0);
            if (num == 0) {
              // Error writing
              error_writing:
                display_text("*** Unable to write to floppy disk on line;");
                goto error_line_info;
            }
            strcpy(line_buffer,"  Wrote");
            strcpy(&line_buffer[8],convert_dword_to_decimal((ulong)num));
            strcpy(&line_buffer[11],"sectors");
            add_to_line_buffer();
            ++gFile_data_count;
            ++entries_written;
            break;

          case 'L':
          case 'l':
          // It's the boot loader (bootup.bin)
            display_text("¯ŸBOOTUP.BIN;");
            gFile_data[gFile_data_count].type = 'L';
            gFile_data[gFile_data_count].start = bufptr;
            bufptr = load_file(bufptr);
            gFile_data[gFile_data_count].length = gNumread;
            strcpy(line_buffer,"  Loaded");
            strcpy(&line_buffer[9],convert_dword_to_decimal((ulong)gNumread));
            add_to_line_buffer();

          // Write it to floppy disk
            update_dt(_BOOTUP_BIN);
            num = write_data_to_disk(gFile_data_count);
            if (num == 0) {
              // Error writing
                goto error_writing;
            }
            strcpy(line_buffer,"  Wrote");
            strcpy(&line_buffer[8],convert_dword_to_decimal((ulong)num));
            strcpy(&line_buffer[11],"sectors");
            add_to_line_buffer();
            strcpy(line_buffer,"  CRC16");
            strcpy(&line_buffer[8],convert_dword_to_decimal((ulong)gCRC16));
            add_to_line_buffer();
            update_rp(gFile_data_count);
            ++gFile_data_count;
            ++entries_written;
            break;

          case 'S':
          case 's':
          // It's a special loader (special.bin)
            display_text("¯ŸSPECIAL.BIN;");
            gFile_data[gFile_data_count].type = 'S';
            gFile_data[gFile_data_count].start = bufptr;
            bufptr = load_file(bufptr);
            gFile_data[gFile_data_count].length = gNumread;
            strcpy(line_buffer,"  Loaded");
            strcpy(&line_buffer[9],convert_dword_to_decimal((ulong)gNumread));
            add_to_line_buffer();

          // Write it to floppy disk
            update_dt(_SPECIAL);
            num = write_data_to_disk(gFile_data_count);
            if (num == 0) {
              // Error writing
                goto error_writing;
            }
            strcpy(line_buffer,"  Wrote");
            strcpy(&line_buffer[8],convert_dword_to_decimal((ulong)num));
            strcpy(&line_buffer[11],"sectors");
            add_to_line_buffer();
            strcpy(line_buffer,"  CRC16");
            strcpy(&line_buffer[8],convert_dword_to_decimal((ulong)gCRC16));
            add_to_line_buffer();
            update_rp(gFile_data_count);
            ++gFile_data_count;
            ++entries_written;
            break;

          case 'I':
          case 'i':
          // It's exodus.ini
            display_text("¯Ÿexodus.ini;");
            gFile_data[gFile_data_count].type = 'I';
            gFile_data[gFile_data_count].start = bufptr;
            bufptr = load_file(bufptr);
            gFile_data[gFile_data_count].length = gNumread;
            strcpy(line_buffer,"  Loaded");
            strcpy(&line_buffer[9],convert_dword_to_decimal((ulong)gNumread));
            add_to_line_buffer();

          // Write it to floppy disk
            update_dt(_EXODUS_INI);
            num = write_data_to_disk(gFile_data_count);
            if (num == 0) {
              // Error writing
                goto error_writing;
            }
            strcpy(line_buffer,"  Wrote");
            strcpy(&line_buffer[8],convert_dword_to_decimal((ulong)num));
            strcpy(&line_buffer[11],"sectors");
            add_to_line_buffer();
            strcpy(line_buffer,"  CRC16");
            strcpy(&line_buffer[8],convert_dword_to_decimal((ulong)gCRC16));
            add_to_line_buffer();
            update_rp(gFile_data_count);
            ++gFile_data_count;
            ++entries_written;
            break;

          case 'D':
          case 'd':
          // It's a driver
            display_text_color(file_open,159);
            gFile_data[gFile_data_count].type = 'D';
            gFile_data[gFile_data_count].start = bufptr;
            bufptr = load_file(bufptr);
            gFile_data[gFile_data_count].length = gNumread;
            strcpy(line_buffer,"  Loaded");
            strcpy(&line_buffer[9],convert_dword_to_decimal((ulong)gNumread));
            add_to_line_buffer();

          // Write it to floppy disk
            update_dt(_DRIVER);
            update_np();
            num = write_data_to_disk(gFile_data_count);
            if (num == 0) {
              // Error writing
                goto error_writing;
            }
            strcpy(line_buffer,"  Wrote");
            strcpy(&line_buffer[8],convert_dword_to_decimal((ulong)num));
            strcpy(&line_buffer[11],"sectors");
            add_to_line_buffer();
            strcpy(line_buffer,"  CRC16");
            strcpy(&line_buffer[8],convert_dword_to_decimal((ulong)gCRC16));
            add_to_line_buffer();
            update_rp(gFile_data_count);
            ++gFile_data_count;
            ++entries_written;
            break;

          case 'E':
          case 'e':
          // It's EXODUS.COM
            display_text_color(file_open,159);
            gFile_data[gFile_data_count].type = 'E';
            gFile_data[gFile_data_count].start = bufptr;
            bufptr = load_file(bufptr);
            gFile_data[gFile_data_count].length = gNumread;
            strcpy(line_buffer,"  Loaded");
            strcpy(&line_buffer[9],convert_dword_to_decimal((ulong)gNumread));
            add_to_line_buffer();

          // Write it to floppy disk
            update_dt(_EXODUS_COM);
            update_np();
            num = write_data_to_disk(gFile_data_count);
            if (num == 0) {
              // Error writing
                goto error_writing;
            }
            strcpy(line_buffer,"  Wrote");
            strcpy(&line_buffer[8],convert_dword_to_decimal((ulong)num));
            strcpy(&line_buffer[11],"sectors");
            add_to_line_buffer();
            strcpy(line_buffer,"  CRC16");
            strcpy(&line_buffer[8],convert_dword_to_decimal((ulong)gCRC16));
            add_to_line_buffer();
            update_rp(gFile_data_count);
            ++gFile_data_count;
            ++entries_written;
            break;

          default:
          // Who knows?
            display_text("¯ÀUnrecognized option on line:;");
            goto error_line_info;
        }
      skip_to_next_line:
        print_string(24,16,241,make_length(convert_dword_to_decimal(entries_written),4));
        ++line_no;
        while (*(ushort *)pbptr != 0x0d0a && *(ushort *)pbptr != 0x0a0d && pbptr < end_pbptr) {
            ++pbptr;
        }
        if (*(ushort *)pbptr != 0x0d0a || *(ushort *)pbptr != 0x0a0d) {
            pbptr += 2;
        }
    }


  // Now, update the DT/NP/RP
    display_text("¯ŸWriting DT;");
    full_copy(load_sector,dt_buffer,512);
    num = write_sector(0,2,0,0);
    if (num == 0) {
      xx_error:
        display_text("*** Error writing to disk;");
        goto get_a_key_quit;
    }

    display_text("¯ŸWriting NP;");
    full_copy(load_sector,np_buffer,512);
    num = write_sector(0,3,0,0);
    if (num == 0) {
        goto xx_error;
    }

    display_text("¯ŸWriting RP;");
    full_copy(load_sector,rp_buffer,512);
    num = write_sector(0,4,0,0);
    if (num == 0) {
        goto xx_error;
    }

    display_text(";");
    display_text("¯ñ Finished successfully;");


  // We're finished
    goto quit;
  get_a_key_quit:
    while (1) {
        display_listing();
        key = get_a_key();
        switch (key) {
          case Escape:
            goto quit;

          case Up:
          case Grey_Up:
            if (cur_line > 0) {
                --cur_line;
            }
            goto next_one;

          case Down:
          case Grey_Down:
            if (cur_line < max_line-1) {
                ++cur_line;
            }
            goto next_one;

          case PgDn:
          case Grey_PgDn:
            if (cur_line+20 < max_line) {
                cur_line += 20;
            }
            goto next_one;

          case PgUp:
          case Grey_PgUp:
            if (cur_line-20 > 0) {
                cur_line -= 20;
            } else {
                cur_line = 0;
            }
            goto next_one;

          case Home:
          case Grey_Home:
            cur_line = 0;
            goto next_one;

          case End_Key:
          case Grey_End:
          force_end:
            if (cur_line == 0) {
              // We're home
                if (max_line > 20) {
                    cur_line = max_line - 20;
                } else {
                    cur_line = 0;
                }
            } else {
              // We're already down somewhere in the list
                if (max_line - cur_line > 20) {
                    cur_line = max_line - 20;
                }
            }
            goto next_one;
        }

        switch (key & 0xff) {
          case '+':
          // Lock onto the next item
            if (cur_line < max_line-1) {
                save_value = cur_line;
                tptr = &list_buffer[cur_line*79];
                while (++cur_line < max_line-1) {
                    tptr += 79;
                    if (*tptr == '¯') {
                        // We're there
                        goto skip1;
                    }
                }
              // We didn't find it
                cur_line = save_value;
            }
          skip1:
            break;

          case '-':
          // Lock onto the previous item
            if (cur_line != 0) {
                tptr = &list_buffer[cur_line*79];
                while (--cur_line > 0) {
                    tptr -= 79;
                    if (*tptr == '¯') {
                        // We're there
                        goto skip2;
                    }
                }
            }
          skip2:
            break;

          case 'w':
          case 'W':
          // Write the listing to disk
            write_listing();
            goto force_end;
            break;

          case 'r':
          case 'R':
          // They want to reboot
            _asm {
                int 0x19
            }
        }
        _asm {
          next_one:
        }
    }

  quit:
    //clear_screen();
    return(0);
}



#include "extras.c"
