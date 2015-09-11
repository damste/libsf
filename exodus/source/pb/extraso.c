//
// extras.c
//
// PutBoot
//




void set_video_mode(void)
{
    _asm {

      // Video mode 3 - 80x25 color
        mov     ax,0x0003
        int     0x10

      // Enable high intensity
        mov     ax,0x1003
        xor     bl,bl
        int     0x10
    }
}




void clear_screen(void)
{
    _asm {
      // Set background color to 7
      // Store spaces
        push    es
        mov     ax,0xb800
        mov     es,ax
        xor     di,di
        mov     cx,80*25
        mov     ax,0720h
        cld
        rep     stosw
        pop     es
    }
}




void print_string(uint y, uint x, uchar color, char *string)
{
    ushort i;

    i = y*80*2 + x*2;
    _asm {
        push    es
        mov     ax,0xb800
        mov     es,ax
        mov     di,i
        mov     si,string
      top_loop:
        lodsb
        cmp     al,';'
        jz      quit
        cmp     al,'¯'
        jz      change_color

        stosb
        mov     al,color
        stosb
        jmp     top_loop

      change_color:
        lodsb
        mov     color,al
        jmp     top_loop

      quit:
        pop     es
    }
}




void print_string_count(uint y, uint x, uchar color, char *string, uint count)
{
    ushort i;

    i = y*80*2 + x*2;
    _asm {
        push    es
        mov     ax,0xb800
        mov     es,ax
        mov     di,i
        mov     si,string
        mov     cx,count
      top_loop:
        lodsb
        cmp     al,'¯'
        jz      change_color

        stosb
        mov     al,color
        stosb
        loop    top_loop
        jmp     quit

      change_color:
        lodsb
        mov     color,al
        dec     cx
        jz      quit
        loop    top_loop

      quit:
        pop     es
    }
}




ushort get_a_key(void)
{
    ushort key;

    _asm {
        xor     ah,ah
        int     0x16
        mov     key,ax
    }
    return(key);
}




void main_screen(void)
{
    int i;

    i = 0;
    print_string(i++, 0, 241,"ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿;");
    print_string(i++, 0, 241,"³ Exodus DT/NP/RP Put Boot Utility                                      FLOPPY ³;");
    print_string(i++, 0, 241,"³ Beatleworks, Inc. 2001                                    Version 10.10.2010 ³;");
    print_string(i++, 0, 241,"ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ;");
    print_string(i++, 0, 159,"                                                                               ¯ñ°;");
    print_string(i++, 0, 159,"                                                                               ¯ñ°;");
    print_string(i++, 0, 159,"                                                                               ¯ñ°;");
    print_string(i++, 0, 159,"                                                                               ¯ñ°;");
    print_string(i++, 0, 159,"                                                                               ¯ñ°;");
    print_string(i++, 0, 159,"                                                                               ¯ñ°;");
    print_string(i++, 0, 159,"                                                                               ¯ñ°;");
    print_string(i++, 0, 159,"                                                                               ¯ñ°;");
    print_string(i++, 0, 159,"                                                                               ¯ñ°;");
    print_string(i++, 0, 159,"                                                                               ¯ñ°;");
    print_string(i++, 0, 159,"                                                                               ¯ñ°;");
    print_string(i++, 0, 159,"                                                                               ¯ñ°;");
    print_string(i++, 0, 159,"                                                                               ¯ñ°;");
    print_string(i++, 0, 159,"                                                                               ¯ñ°;");
    print_string(i++, 0, 159,"                                                                               ¯ñ°;");
    print_string(i++, 0, 159,"                                                                               ¯ñ°;");
    print_string(i++, 0, 159,"                                                                               ¯ñ°;");
    print_string(i++, 0, 159,"                                                                               ¯ñ°;");
    print_string(i++, 0, 159,"                                                                               ¯ñ°;");
    print_string(i++, 0, 159,"                                                                               ¯ñ°;");
    print_string(i++, 0, 241,"Entries written      ³                                                          ;");
}




int read_sector(uchar track, uchar sector, uchar head, uchar drive)
{
    int r;

    _asm {
        push    es
        mov     ax,ds
        mov     es,ax

      try_again:
        mov     ah,02h                                              // Read disk sectors
        mov     al,1                                                // Only read one
        mov     bx,offset load_sector                               // es:[bx] - where to load
        mov     ch,track                                            // track 0
        mov     cl,sector                                           // sector 1
        mov     dh,head                                             // head 0
        mov     dl,drive                                            // drive A:
        int     0x13
        jnc     read_ok
        cmp     ah,6
        jz      try_again
        mov     al,0                                                // Indicate that we didn't read any sectors

      read_ok:
        xor     bx,bx
        mov     bl,al
        mov     r,bx
        pop     es
    }
    return(r);
}




void iWriteFloppyFile(ulong dataptr,
                      uchar track,
                      uchar sector,
                      uchar head,
                      uchar drive)
{
    ulong offset;
    ushort numread;


    if (!gfh)
    {
        // Open the file
        gfh = fopen(floppy_filename, "rb+");
        if (!gfh)
            _asm int 3;
    }
    // Find out where we need to seek
    offset = ((ulong)track * 18 * 2 * 512) + ((ulong)head * 18 * 512) + (((ulong)sector - 1) * 512);

if (offset == 0)
    _asm int 3;

    // Copy the block to local memory
    _asm
    {
        pusha
        push    ds
        push    es

// int 3
        cmp     word ptr dataptr[0],0xffff
        jnz     normal_address
        cmp     word ptr dataptr[1],0xffff
        jnz     normal_address
        // It's the load_sector buffer
        push    ds
        pop     es
        mov     di,offset load_sector
        jmp     got_our_address

      normal_address:
        mov     dx,word ptr dataptr[1]
        mov     ax,word ptr dataptr[0]
        call    convert_dx_ax_to_far_ptr
        mov     es,dx
        mov     di,ax

      got_our_address:
        mov     bp,offset write_buffer
        mov     cx,512
        // Right now, es:[di] - copy from
        //            ds:[bp] - copy to
        //                 cx - count
      top_loop:
        mov     al,byte ptr es:[di]
        mov     byte ptr ds:[bp],al
        inc     di
        inc     bp
        loop    top_loop

        pop     es
        pop     ds
        popa
    }
    // Right now it's been copied


    fseek(gfh, offset, SEEK_SET);
    numread = fwrite((uchar*)&write_buffer[0], 1, 512, gfh);
    if (numread != 512)
        _asm int 3;
}




int write_sector(uchar track, uchar sector, uchar head, uchar drive)
{
    int r;

    // October 12, 2008
    // Rick C. Hodgin - Changed to write to the FLOPPY.FLP file instead of the physical floppy.
    //                  Added/modified because EXODUS development is continuing under VMWare.

    if (1)
    {
        iWriteFloppyFile(-1, track, sector, head, drive);
    }
    else
    {
        // Code never executes
        _asm {
            push    es
            mov     ax,ds
            mov     es,ax

          try_again:
            mov     ah,03h                                              // Write disk sectors
            mov     al,1                                                // Only write one
            mov     bx,offset load_sector                               // es:[bx] - where to write from
            mov     ch,track                                            // track 0
            mov     cl,sector                                           // sector 1
            mov     dh,head                                             // head 0
            mov     dl,drive                                            // drive A:
            int     0x13
            jnc     read_ok
            cmp     ah,6
            jz      try_again
            mov     al,0                                                // Indicate that we didn't read any sectors

          read_ok:
            xor     bx,bx
            mov     bl,al
            mov     r,bx
            pop     es
        }
    }
    return(r);
}




void add_to_line_buffer(void)
{
    if (max_line <= 100) {
        add_to_line_buffer_only();
        ++max_line;
        full_strnset(line_buffer,32,79);
        if (max_line >= 20) {
            ++cur_line;
        }
        display_listing();
    }
}




void add_to_line_buffer_only(void)
{
    full_copy(&list_buffer[max_line*79],line_buffer,79);
}




void display_text(char *text)
{
    char *tptr;
    int i;

    printf("%s\n", text);
    tptr = (char *)line_buffer;
    i = 0;
    while (*text != ';' && ++i < 79) {
        *tptr++ = *text++;
    }
    add_to_line_buffer();
}




void display_text_color(char *text, uchar color)
{
    char *tptr;
    int i;

    tptr = (char *)line_buffer;
    *tptr++ = '¯';
    *(uchar *)tptr++ = color;
    i = 0;
    while (*text != ';' && ++i < 77) {
        *tptr++ = *text++;
    }
    add_to_line_buffer();
}




void display_error(ushort error)
{
    char *tptr;

    switch (error) {
      case 0x1:
        tptr = "Invalid function handle;";
        break;
      case 0x2:
        tptr = "File not found;";
        break;
      case 0x3:
        tptr = "Path not found;";
        break;
      case 0x4:
        tptr = "No handles left;";
        break;
      case 0x5:
        tptr = "Access denied;";
        break;
      case 0x6:
        tptr = "Invalid handle;";
        break;
      case 0x7:
        tptr = "Memory CBs destroyed;";
        break;
      case 0x8:
        tptr = "Insufficient memory;";
        break;
      case 0x9:
        tptr = "Invalid memory block address;";
        break;
      case 0xa:
        tptr = "Invalid environment;";
        break;
      case 0xb:
        tptr = "Invalid format;";
        break;
      case 0xc:
        tptr = "Invalid access code;";
        break;
      case 0xd:
        tptr = "Invalid data;";
        break;
      case 0xf:
        tptr = "Invalid drive specified;";
        break;
      case 0x10:
        tptr = "Attempt to remove current directory;";
        break;
      case 0x11:
        tptr = "Not same device;";
        break;
      case 0x12:
        tptr = "No more files;";
        break;
      case 0x13:
        tptr = "Write protected;";
        break;
      case 0x14:
        tptr = "Unknown unit;";
        break;
      case 0x15:
        tptr = "Drive not ready;";
        break;
      case 0x16:
        tptr = "Unknown command;";
        break;
      case 0x17:
        tptr = "CRC error;";
        break;
      case 0x18:
        tptr = "Bad request;";
        break;
      case 0x19:
        tptr = "Seek error;";
        break;
      case 0x1a:
        tptr = "Unknown media;";
        break;
      case 0x1b:
        tptr = "Sector not found;";
        break;
      case 0x1c:
        tptr = "Out of paper;";
        break;
      case 0x1d:
        tptr = "Write fault;";
        break;
      case 0x1e:
        tptr = "Read fault;";
        break;
      case 0x1f:
        tptr = "General Failure;";
        break;
      default:
        tptr = "(unrecognized error code);";
        break;
    }
    display_text(tptr);
}




char *convert_dword_to_decimal(ulong val)
{
    // *** DO NOT CHANGE THESE ***
    // There is a bug in MSC6 which causes the fbstp
    // instruction to not work correctly.  I have the
    // stack hardwired down below (0xf4 = offset buffer[0])
    uchar buffer[10], *tptr;

    _asm {
        finit
        fild    val

// BEGIN BLOCK
// This whole block does this:
// FBSTP tbyte ptr buffer
      // There is a bug in MSC6 which causes the fbstp instruction to be emitted as 0xdb 0x76
      // This is an error and is an unused opcode.  So I tried to hard wire it below with the
      // _emit statements, but that doesn't work either.  It just emits NULLs.  So, I've
      // physically had to modify the code in the code segment with this fix here.
      // Sucks, doesn't it?  YES IT DOES!!
        mov     si,offset some_label
        mov     word ptr [si],0x76df
        mov     byte ptr [si+2],0xf4
        jmp     some_label      // Clear cache so it decodes the new instruction I've just written there
      some_label:
        _emit   0xdf    // fbstp tbyte ptr buffer
        _emit   0x76    // It seems there's a bug with both this instruction
        _emit   0xf4    // And the emit statements
// END BLOCK
    }

  // Store the number
    trash_buffer[0] = (buffer[4] >> 4) + '0';
    trash_buffer[1] = (buffer[4] & 0xf) + '0';
    trash_buffer[2] = (buffer[3] >> 4) + '0';
    trash_buffer[3] = (buffer[3] & 0xf) + '0';
    trash_buffer[4] = (buffer[2] >> 4) + '0';
    trash_buffer[5] = (buffer[2] & 0xf) + '0';
    trash_buffer[6] = (buffer[1] >> 4) + '0';
    trash_buffer[7] = (buffer[1] & 0xf) + '0';
    trash_buffer[8] = (buffer[0] >> 4) + '0';
    trash_buffer[9] = (buffer[0] & 0xf) + '0';
    trash_buffer[10] = ';';

  // Skip past the leading 0's
    tptr = (char *)trash_buffer;
    while (*tptr == '0') {
        ++tptr;
    }
    if (*tptr == ';') {
      // Always point to at least one zero
        --tptr;
    }
    trash_buffer[10] = 0;
    return(tptr);
}




void full_copy(uchar *dest, uchar *source, int count)
{
    while (count-- > 0) {
        *dest++ = *source++;
    }
}




void full_strnset(uchar *dest, uchar c, int count)
{
    while (count-- > 0) {
        *dest++ = c;
    }
}




void display_listing(void)
// This routine is used to display the generated listing from above
{
    int i;

    for (i=4; i<24; i++) {
        if ((cur_line + i - 4) < max_line) {
            print_string_count(i,0,31,&list_buffer[(cur_line+i-4)*79],79);
        } else {
            print_string_count(i,0,31,&list_buffer[100*79-79],79);
        }
    }
}




void write_listing(void)
{
    FILE *fh;
    uchar *tptr;
    uint j, num, skipped;
    int i;

    fh = fopen("pb.log","wb+");
    if (fh != NULL)
    {
        tptr = (char *)list_buffer;
        for (i=0; i<max_line; i++) {
            skipped = 0;
            for (j=79; j > 0; j--) {
                if (*(tptr+j) != 32 && *(tptr+j) != 0) {
                  // We found a non whitespace
                  goto  write_line;
                }
            }
            goto    write_cr_lf;

          write_line:
            if (*tptr == 175) {
                tptr += 2;
                j -= 2;
                skipped = 2;
            }
            if (j != 0) {
                num = fwrite(tptr,1,j,fh);
            }
          write_cr_lf:
            num = fwrite(crlf,1,2,fh);
            tptr += 79 - skipped;
        }
        fclose(fh);
        strcpy(line_buffer,"PB.LOG written to disk");
        printf("%s\n\n", (char*)list_buffer);

    }
    else
    {
        strcpy(line_buffer,"ERROR:  Unable to create file PB.LOG");
    }
    add_to_line_buffer();
}




char *copy_filename(char *dest, char *source)
{
    int i;

  // Copy the filename
    i = 0;
    while (i++ < 64 && *source != 32 && *(ushort *)source != 0x0d0a && *(ushort *)source != 0x0a0d) {
        *dest++ = *source++;
    }
    *++dest = ';';      // This is a terminator for displaying (if there's an error)

  // Skip past any spaces afterwards
    while (*source == 32) {
        ++source;
    }

  // Tell them where we are now
    return(source);
}




ulong load_file(ulong bufptr)
{
    ulong far_offset;
    ushort error, handle, crc16, temp_segment;

_asm int 3;
    far_offset = bufptr;
    _asm {
        mov     dx,offset file_open
        mov     ah,0x3d
        mov     al,0x40     // Deny none, read only
        int     0x21
        mov     error,ax
        jnc     cont1
        jmp     error1
      cont1:
        mov     handle,ax

      // Get this 20-bit quantity into ds:dx
        mov     dx,word ptr bufptr[1]
        mov     ax,word ptr bufptr[0]
        call    convert_dx_ax_to_far_ptr
      // Now it's in dx:ax

        push    ds
        mov     temp_segment,dx
        mov     ds,dx
        mov     dx,ax
        mov     ah,0x3f
        mov     bx,handle
        mov     cx,0xffff           // Maximum bytes to read = 64k-whatever value is in ax (a number from 0-16)
        sub     cx,dx
        int     0x21

// Calculate the CRC16 for the loaded data
        push    ax
        push    bx
        push    cx
        push    dx
        push    si
        push    di
        pushf


        mov     cx,ax               // Do it for all bytes loaded
        mov     si,dx               // Start at the beginning of the buffer
        mov     crc16,0             // Initialize our "seed value" to 0
      top_loop:
        push    cx
        push    si
        mov     ds,temp_segment     // Get our local data segment back

        mov     ax,0xa001
        push    ax                  // Mask
        xor     ah,ah
        mov     al,byte ptr [si]
        push    ax                  // Character
        push    crc16               // Current crc16 value

        mov     ax,cs               // Restore the data segment for update_crc()
        mov     ds,ax

        call    update_crc_reverse
        add     sp,6
        mov     crc16,ax

        pop     si
        inc     si
        pop     cx
        loop    top_loop

        popf
        pop     di
        pop     si
        pop     dx
        pop     cx
        pop     bx
        pop     ax
// Right now the CRC 16 value is calculated

        pop     ds
        mov     error,ax
        jc      error2
        mov     gNumread,ax

      // Store the CRC to it's permanent memory (used in update_dt())
        mov     bx,crc16
        mov     gCRC16,bx



      // Move to the next paragraph
        add     word ptr far_offset[0],ax
        adc     word ptr far_offset[2],0
        add     word ptr far_offset[0],16
        adc     word ptr far_offset[2],0
        and     word ptr far_offset[0],0xfff0

        mov     bx,handle
        mov     ah,0x3e
        int     0x21

        jmp     quit
    }

  error1:
    display_text("Error loading this file;");
    display_error(error);
    goto quit;

  error2:
    display_text("Error reading from this file;");
    display_error(error);
    goto quit;

  quit:
    return(far_offset);
}




void update_dt(uchar type)
{
    *dt_ptr = _BOOTABLE_ENTRY;
    *(ulong *)(dt_ptr+1) = 0;
    *(ulong *)(dt_ptr+5) = 0;
    *(ushort *)(dt_ptr+8) = (ushort)(rp_ptr - (ushort)&rp_buffer) - 2;
    *(dt_ptr+10) = type << 1 | 1;
    if (type == _DRIVER || type == _EXODUS_COM) {
        *(ushort *)(dt_ptr+11) = (ushort)(np_ptr - (ushort)&np_buffer - 2);
    }
    *(ushort *)(dt_ptr+13) = gCRC16;
    dt_ptr += 16;
    return;
}




void update_np(void)
{
    uchar *cptr;
    char *tptr, *lptr;
    uchar ch;

  // Move past any pathnames
    cptr = (uchar *)np_ptr++;
    tptr = (char *)file_open;
    lptr = tptr;
    while (*tptr != 0) {
        if (*tptr == '\\') {
            lptr = tptr+1;
        }
        ++tptr;
    }

  // Now, copy the name
    ch = 0;
    while (*lptr != 0) {
        *np_ptr++ = *lptr++;
        ++ch;
    }
    *cptr = ch;
    return;
}




void update_rp(int slot)
{
    ulong start, main_offset, requestor_offset;
    char ch;

  // Load in the

    ch = gFile_data[slot].type;
    if (ch == 'D' || ch == 'E') {
        start = gFile_data[slot].start;
      // Note, the reason I use the local variables requestor_offset below is because they're on the stack
      //       and are referenced through SS (which is safe because by this time I've altered DS).
        _asm {
            push    ds
            mov     ax,word ptr start[0]
            mov     dx,word ptr start[1]
            call    convert_dx_ax_to_far_ptr
            mov     ds,dx
            mov     si,ax
            mov     dx,word ptr [si]
            mov     word ptr main_offset[0],dx
            mov     dx,word ptr [si+2]
            mov     word ptr main_offset[2],dx
            mov     dx,word ptr [si+4]
            mov     word ptr requestor_offset[0],dx
            mov     dx,word ptr [si+6]
            mov     word ptr requestor_offset[2],dx
            pop     ds
        }
        gMain_offset = main_offset;
        gRequestor_offset = requestor_offset;
    }

    *(ulong *)rp_ptr = (ulong)gFile_data[slot].length;
    *(ulong *)(rp_ptr+4) = gMain_offset;
    *(ulong *)(rp_ptr+8) = gRequestor_offset;

    *(rp_ptr+12) = gStart_head;
    *(rp_ptr+13) = gStart_track;
    *(rp_ptr+14) = gStart_sector;

    *(rp_ptr+16) = gEnd_head;
    *(rp_ptr+17) = gEnd_track;
    *(rp_ptr+18) = gEnd_sector;
    rp_ptr += 20;

  // Update variables for next time through
    gMain_offset=0xffffffff;
    gRequestor_offset=0xffffffff;

    gStart_head=0xff;
    gStart_track=0xff;
    gStart_sector=0xff;

    gEnd_head=0xff;
    gEnd_track=0xff;
    gEnd_sector=0xff;
    return;
}




int write_data_to_disk(int slot)
{
    uchar head, track, sector;
    uchar last_head, last_track, last_sector;
    ushort sectors_written;
    long bytes_to_write;
    ulong start;

    gStart_head   = last_head   = head   = gHead;
    gStart_track  = last_track  = track  = gTrack;
    gStart_sector = last_sector = sector = gSector;
    sectors_written = 0;

    bytes_to_write = (long)gFile_data[slot].length;
    start = gFile_data[slot].start;
    goto verify_sector;
    while (bytes_to_write > 0) {
        if (1)
        {
            iWriteFloppyFile(start, track, sector, head, 0);
        }
        else
        {
            _asm {
                push    es
                push    bx

                mov     ax,word ptr start[0]
                mov     dx,word ptr start[1]
                call    convert_dx_ax_to_far_ptr
                mov     es,dx
                mov     bx,ax

              try_again:
              // Right now, es:[bx] - far ptr to 512 byte block
                mov     ah,03h                                          // Write disk sectors
                mov     al,1                                            // Only write one
                mov     ch,track                                        // track 0
                mov     cl,sector                                       // sector 1
                mov     dh,head                                         // head 0
                mov     dl,0                                            // drive A:
                int     0x13
                jnc     read_ok
                cmp     ah,6
                jz      try_again
                mov     al,0                                            // Indicate that we didn't read any sectors

              read_ok:
                pop     bx
                pop     es
            }
        }
        last_head = head;
        last_track = track;
        last_sector = sector;
        ++sectors_written;
        ++sector;
        start += 512;
        bytes_to_write -= 512;

      verify_sector:
        if (sector > 18) {
            sector = 1;
            ++head;
            if (head > 1) {
                head = 0;
                ++track;
                if (track > 79) {
                  // We're at the end of disk
                  // Force a failure here
                  sectors_written = 0;
                  goto quit;
                }
            }
        }
    }

  quit:
    gHead   = head;
    gTrack  = track;
    gSector = sector;
    gEnd_head   = last_head;
    gEnd_track  = last_track;
    gEnd_sector = last_sector;
    return(sectors_written);
}




// This function converts a 20-bit value stored with upper 12-bits in dx and lower 8-bits in ax into a 16-bit value in dx
// and 4-bit value in ax
//
// Upon entry:  dx:ax - 20-bit quantity
//
// Upon exit:   dx:ax - far ptr (dx is the segment, ax is the offset (0-16))
//

#pragma check_stack(off)

void convert_dx_ax_to_far_ptr(void)
{
//
    _asm {
      // Shift 4 bits from upper-nibble of al into lower nibble of dl
        push    ax
        shl     al,1
        rcl     dx,1

        shl     al,1
        rcl     dx,1

        shl     al,1
        rcl     dx,1

        shl     al,1
        rcl     dx,1
      // Right now, dx contains the upper 16-bits of the 20-bit quantity
        pop     ax

      // Mask off the upper 12 bits in ax
        and     ax,0xf
    }
}




uint update_crc(uint crc, uint c, uint mask)
{
    int i;

    c <<= 8;
    for (i=0; i<8; i++)
    {
        if ((crc ^ c) & 0x8000) {
            crc = (crc << 1 ) ^ mask;
        } else {
            crc <<= 1;
        }
        c <<= 1;
    }
    return(crc);
}




uint update_crc_reverse(uint crc, uint c, uint mask)
{
    int i;

    for (i=0; i<8 ;i++)
    {
        if ((crc ^ c) & 1) {
            crc = (crc >> 1) ^ mask;
        } else {
            crc >>= 1;
        }
        c >>= 1;
    }
    return(crc);
}




char *make_length(char *ptr, uint i)
{
    *(ptr+i) = ';';
    return(ptr);
}
