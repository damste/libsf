//
// extras.c
//
//






void derive_input_file_names(char *src)
{
    char *dest;
    ushort len;

    len = strlen(src);

  // Save for later use
    cmd_line_pathname = src;
    cmd_line_pathname_length = len;

  // Copy the ASM filename
    dest = (char *)asm_filename;
    strncpy(dest, src, len);
    dest += len;
    *dest++ = '\\';
    strncpy(dest, src, len);
    dest += len;
    strncpy(dest, dot_asm, sizeof(dot_asm));

  // Copy the LST filename
    dest = (char *)lst_filename;
    strncpy(dest, src, len);
    dest += len;
    strncpy(dest, dot_lst, sizeof(dot_lst));
}




ushort allocate_xms_buffers(void)
{
    ulong func;

   // See if XMS is installed
    _asm {
        mov     ax,0x4300
        int     0x2f
        cmp     al,0x80
        jz      ok_to_go
    }
  error:
    return(0);                                                      // Fail

  ok_to_go:
    _asm {
        push    es

        mov     ax,0x4310
        int     0x2f
        mov     func[0],bx
        mov     func[2],es

        pop     es
    }
    xms_func = func;

  // See if XMS is available
    _asm {
        mov     ah,0
        call    xms_func
        cmp     dx,0
        jz      error
    }

  // Allocate ASM buffer
    _asm {
        mov     ah,9
        mov     dx,kilobytes
        call    xms_func
        cmp     ax,0
        jz      error
        mov     asm_mem,dx
    }

  // Allocate LST buffer
    _asm {
        mov     ah,9
        mov     dx,kilobytes
        call    xms_func
        cmp     ax,0
        jz      error
        mov     lst_mem,dx
    }

  // Allocate IN buffer
    _asm {
        mov     ah,9
        mov     dx,kilobytes
        call    xms_func
        cmp     ax,0
        jz      error
        mov     in_mem,dx
    }

  // Allocate OUT buffer
    _asm {
        mov     ah,9
        mov     dx,kilobytes
        call    xms_func
        cmp     ax,0
        jz      error
        mov     out_mem,dx
    }

  // Allocate LINE buffer
    _asm {
        mov     ah,9
        mov     dx,kilobytes
        call    xms_func
        cmp     ax,0
        jnz     ok_1
        jmp     error
      ok_1:
        mov     line_mem,dx
    }
    return(1);                                                      // Success
}




ushort deallocate_xms_buffers(void)
{
    ulong func;

  // Deallocate ASM buffer
    _asm {
        mov     ah,0xa
        mov     dx,asm_mem
        call    xms_func
        cmp     ax,0
        jz      error
    }

  // Deallocate LST buffer
    _asm {
        mov     ah,0xa
        mov     dx,lst_mem
        call    xms_func
        cmp     ax,0
        jz      error
    }

  // Deallocate IN buffer
    _asm {
        mov     ah,0xa
        mov     dx,in_mem
        call    xms_func
        cmp     ax,0
        jz      error
    }

  // Deallocate OUT buffer
    _asm {
        mov     ah,0xa
        mov     dx,out_mem
        call    xms_func
        cmp     ax,0
        jz      error
    }

  // Deallocate LINE buffer
    _asm {
        mov     ah,0xa
        mov     dx,line_mem
        call    xms_func
        cmp     ax,0
        jz      error
    }
    return(1);                                                      // Success

  error:
    return(0);                                                      // Failure
}




ushort load_file(FILE *fh, ushort xms_mem)
{
    ushort numread, result;
    struct XMS_MOVE move_info;

    load_files[load_file_count].source_start = xms_offset;

  // Setup static information
    move_info.src_handle = 0;                                       // Interpreted as seg:offset in src_offset
    _asm {
        mov     word ptr move_info.src_offset[0],offset local_io_buffer
        mov     word ptr move_info.src_offset[2],ds
    }
    move_info.dst_handle = xms_mem;

    goto read_next;
    while (numread != 0) {
      read_next:
        numread = fread(local_io_buffer, 1, _LOCAL_IO_BUFFER_SIZE, fh);
        if (numread != 0) {
          // Copy from the I/O buffer to XMS memory
            move_info.length = (ulong)((numread + 1) & 0xfffe);     // Always write next highest even number of bytes read
            result = conventional_to_XMS(xms_offset, (struct XMS_MOVE *)&move_info);
            if (result == 0) {
                return(result);
            }
        }
      next:
        xms_offset += (ulong)numread;
    }

    load_files[load_file_count].source_end = xms_offset;
    fclose(fh);
    return(1);                                                      // Success
}




// This routine uses the currently loaded file and creates a listing of where all lines physically start
ushort identify_line_numbers(ushort xms_mem)
{
    struct LINE_NUM *lptr;
    char *dptr;
    ushort forced, length, result;
    ulong i, our_offset, start_offset, line_number, total_lines;
    struct XMS_MOVE move_info1;
    struct XMS_MOVE move_info2;


  // Indicate starting line number
    load_files[load_file_count].line_start = line_offset;


  // Get variables required by this algorithm
    our_offset = load_files[load_file_count].source_start;


  // Set constants used throughout this algorithm
    move_info1.length = 4096;
    length = 4096;
    move_info1.src_handle = xms_mem;
    _asm {
        mov     move_info1.dst_handle,0
        mov     word ptr move_info1.dst_offset[0],offset local_io_buffer
        mov     word ptr move_info1.dst_offset[2],ds
    }

    line_number = 0;
    total_lines = 0;
    lptr = (struct LINE_NUM *)local_ln_buffer;
    move_info2.src_handle = 0;
    _asm {
        mov     word ptr move_info2.src_offset[0],offset local_ln_buffer
        mov     word ptr move_info2.src_offset[2],ds
    }
    move_info2.dst_handle = line_mem;
    start_offset = 0;

    result = XMS_to_conventional(our_offset, (struct XMS_MOVE *)&move_info1);
    if (result == 0) {
        return(result);
    }
    our_offset += move_info1.length;
    forced = 0;
    if ((load_files[load_file_count].source_end - load_files[load_file_count].source_start) < move_info1.length) {
        forced = 1;
        length = (ushort)(load_files[load_file_count].source_end - load_files[load_file_count].source_start);
        goto force_once_through;
    }

    while (our_offset <= load_files[load_file_count].source_end) {
      force_once_through:
        dptr = (char *)local_io_buffer;
        for (i=0; i<length; ++i) {
            if (*dptr == 13) {      // Carriage return
              // This is the end of a line
                if (i == length-1) {
                  // We've encountered the CR as the last char in our 4K buffer
                  // We have to adjust a little here
                    *(char *)local_io_buffer = *(char *)(local_io_buffer + i);
                    _asm mov word ptr move_info1.dst_offset[0],offset local_io_buffer + 1
                    move_info1.length = 4094;
                    result = XMS_to_conventional(our_offset, (struct XMS_MOVE *)&move_info1);
                    if (result == 0) {
                        return(result);
                    }
                    length = 4095;
                    if ((ulong)length > load_files[load_file_count].source_end - our_offset) {
                        length = (ushort)(load_files[load_file_count].source_end - our_offset);
                    }
                    our_offset += length;

                  // Put things back the way they were
                    _asm mov word ptr move_info1.dst_offset[0],offset local_io_buffer
                    move_info1.length = 4096;
                    goto next;

                } else {
                    ++total_lines;
                    lptr[line_number++].line_offset = start_offset;
                    ++dptr;                                         // Move passed the CR onto the LF
                    ++i;                                            // Increase count for the CR (so next will be for LF)
                    start_offset = our_offset - load_files[load_file_count].source_start - length + i + 1;
                    if (line_number * sizeof(struct LINE_NUM) > sizeof(local_ln_buffer)) {
                      // We have to store this portion of the line number file to XMS
                        move_info2.length = sizeof(local_ln_buffer);
                        result = conventional_to_XMS(line_offset, (struct XMS_MOVE *)&move_info2);
                        if (result == 0) {
                            return(result);
                        }
                        move_info2.dst_offset = line_offset;

                      good1:
                        line_offset += sizeof(local_ln_buffer);
                        line_number = 0;
                    }
                }
            }
            ++dptr;
        }
        if (forced == 1 || load_files[load_file_count].source_end == our_offset) {
            goto finished;
        }
        result = XMS_to_conventional(our_offset, (struct XMS_MOVE *)&move_info1);
        if (result == 0) {
            return(result);
        }
        length = 4096;
        if ((ulong)length > load_files[load_file_count].source_end - our_offset) {
            length = (ushort)(load_files[load_file_count].source_end - our_offset);
        }
        our_offset += length;

      next:
        i = i;
    }

  finished:
  // Write the last line(s) of data to the line_buffer
    move_info2.length = line_number * sizeof(struct LINE_NUM);
    result = conventional_to_XMS(line_offset, (struct XMS_MOVE *)&move_info2);
    if (result == 0) {
        return(result);
    }
    line_offset += move_info2.length;
    load_files[load_file_count].line_end = line_offset;
    load_files[load_file_count].total_lines = total_lines;
    return(1);
}




// This routine is called recursively for each file it finds (they all get appended to the end of the "heap" in XMS)
ushort load_and_parse_include_files(void)
{
    ushort j,  file_num, result, x;
    ulong i, count, line_num;
    ulong line_num_offset, source_offset;
    ulong line_num_overhead, source_overhead;
    struct XMS_MOVE move_info1;
    struct XMS_MOVE move_info2;
    struct LINE_NUM *lptr;
    char *sptr, *save_sptr;
    char *sptrn;
    char *dptr;
    FILE *fh;
    ushort save_rpath_count;


  // Create the variables necessary for this local function (remember, it's recursive)
    file_num = load_file_count;                                     // Used locally for the current file
    source_offset = 0;
    source_overhead = load_files[file_num].source_start;
    line_num_offset = 0;
    line_num_overhead = load_files[file_num].line_start;
    save_rpath_count = rpath_count;
    x = 0;                                                          // Default to a failure, changes to 1 when/if ok


  // Initialize the move_info records with their constant components
  // Source code
    move_info1.length = 4096;
    move_info1.src_handle = asm_mem;
    move_info1.src_offset = source_offset;
    move_info1.dst_handle = 0;
    _asm {
        mov     word ptr move_info1.dst_offset[0],offset local_io_buffer
        mov     word ptr move_info1.dst_offset[2],ds
    }
  // Line numbers
    move_info2.length = 4096;
    move_info2.src_handle = line_mem;
    move_info2.src_offset = line_num_offset;
    move_info2.dst_handle = 0;
    _asm {
        mov     word ptr move_info2.dst_offset[0],offset local_ln_buffer
        mov     word ptr move_info2.dst_offset[2],ds
    }


  // Load the first block of data from the source code
    result = XMS_to_conventional(source_offset + source_overhead, (struct XMS_MOVE *)&move_info1);


  // Load the first block of data from the source code line info
    result = XMS_to_conventional(line_num_offset + line_num_overhead, (struct XMS_MOVE *)&move_info2);
    line_num = 0;


  // Parse the file looking for INCLUDE files
    lptr = (struct LINE_NUM *)local_ln_buffer;
    for (i=0; i<load_files[file_num].total_lines; i++) {
      try_line_num_again:
        if (line_num+1 >= sizeof(local_ln_buffer) / sizeof(struct LINE_NUM)) {
          // Processing this next buffer count will exceed our loaded buffer, so we load in the next line buffer block
            if (i < load_files[file_num].total_lines-1) {
              // There's still some data to load
                line_num_offset += move_info2.length - sizeof(struct LINE_NUM);
                result = XMS_to_conventional(line_num_offset + line_num_overhead, (struct XMS_MOVE *)&move_info2);
                if (result == 0) {
                    goto quit;
                }
                line_num = 0;
                goto try_line_num_again;
            } else {
              // We're at the end of the file
                goto force_read_this_line;
            }
        } else {
          try_source_again:
            if (lptr[line_num+1].line_offset >= source_offset + move_info1.length) {
              // This source line is beyond the block we have loaded, load the next block try again
                if (lptr[line_num].line_offset >= source_offset + move_info1.length) {
                  // The current source line is beyond, so just read the next block
                    source_offset += move_info1.length;
                    result = XMS_to_conventional(source_offset + source_overhead, (struct XMS_MOVE *)&move_info1);
                    goto try_source_again;
                } else {
                  // Part of the source line is in this block, the rest is in the next
                    count = source_offset + move_info1.length - lptr[line_num].line_offset;
                    source_offset += move_info1.length - count;
                    if (move_info1.length - count == 0) {
                        _asm int 3;
                    }
                    result = XMS_to_conventional(source_offset + source_overhead, (struct XMS_MOVE *)&move_info1);
                    goto try_source_again;
                }

            } else {
              // It's in this block
              force_read_this_line:
                j = (ushort)(lptr[line_num].line_offset - source_offset);
                _asm {      // sptr = (char *)(&local_io_buffer + j);
                    mov     ax,offset local_io_buffer
                    add     ax,j
                    mov     sptr,ax
                }
                j = (ushort)(lptr[line_num+1].line_offset - source_offset);
                _asm {      // sptrn = (char *)(&local_io_buffer + j);
                    mov     ax,offset local_io_buffer
                    add     ax,j
                    mov     sptrn,ax
                }
              // Right now, sptr = ptr to this line in this block
              //            sptrn = ptr to next line in this block
              // Skip past any white spaces
                while (*sptr == 32 || *sptr == 9 && sptr < sptrn) {
                    ++sptr;
                }
                if (sptr < sptrn && *sptr != 13 && *sptr != ';') {
                  // There's something here
                    if (strnicmp(sptr,"include",7) == 0) {
                      // We found an include file
                        ++load_file_count;
                        sptr += 8;
                        save_sptr = sptr;
                        dptr = (char *)load_files[load_file_count].filename;
                        if (*sptr != '\\') {
                          // It's a filename relative to the path specified on the command line
                            strncpy(dptr, cmd_line_pathname, cmd_line_pathname_length);
                            dptr += cmd_line_pathname_length;
                            *dptr++ = '\\';
                        } else {
                          // They've specified a full pathname
                          // We need to store it because MASM recognizes "relative paths" ... and so must we
                            push_relative_path(sptr);
                        }
                        while (*sptr != 32 && *sptr != 13 && *sptr != ';') {
                            *dptr++ = *sptr++;
                        }
                        fh = fopen(load_files[load_file_count].filename,"rb+");
                        if (fh == NULL) {
                          // The file could not be opened
                            if (rpath_count != 0) {
                              // We need to try it with a different path
                                dptr = (char *)load_files[load_file_count].filename;
                                strncpy(dptr, rpath[rpath_count-1].filename, strlen(rpath[rpath_count-1].filename));
                                dptr += strlen(rpath[rpath_count-1].filename);
                                sptr = save_sptr;
                                while (*sptr != 32 && *sptr != 13 && *sptr != ';') {
                                    *dptr++ = *sptr++;
                                }
                                fh = fopen(load_files[load_file_count].filename,"rb+");
                                if (fh == NULL) {
                                    goto quit;
                                }
                            } else {
                                goto quit;
                            }
                        }
                        printf(".");
                        result = load_file(fh, asm_mem);            // Loads entire file
                        if (result == 0) {
                            goto quit;
                        }
                        result = identify_line_numbers(asm_mem);    // Uses current load_file_count record
                        if (result == 0) {
                            goto quit;
                        }
                        result = load_and_parse_include_files();
                        if (result == 0) {
                            goto quit;
                        }
                      // Restore our memory blocks (they will have/could have been changed above)
                        result = XMS_to_conventional(source_offset + source_overhead, (struct XMS_MOVE *)&move_info1);
                        result = XMS_to_conventional(line_num_offset + line_num_overhead, (struct XMS_MOVE *)&move_info2);
                    }
                }
            }
        }
        ++line_num;
    }
    x=1;

  quit:
  // Success, we're finished
    rpath_count = save_rpath_count;
    return(x);
}




ushort identify_exec_to_line_numbers(void)
{
    return(0);
}




// Load data from XMS to conventional
ushort XMS_to_conventional(ulong start, struct XMS_MOVE *move_info)
{
    move_info->src_offset = start;
    _asm {
        mov     si,move_info
        mov     ah,0xb
        call    xms_func
        cmp     ax,0
        jnz     good
    }
    return(0);
  good:
    return(1);
}




// Write data from conventional to XMS
ushort conventional_to_XMS(ulong start, struct XMS_MOVE *move_info)
{
    move_info->dst_offset = start;
    _asm {
        mov     si,move_info
        mov     ah,0xb
        call    xms_func
        cmp     ax,0
        jnz     good
    }
    return(0);
  good:
    return(1);
}




void push_relative_path(char *src)
{
    ushort i, last_backslash;
    char *tptr;
    char *dptr;

  // Find out where the last \ character is
    if (rpath_count < 10) {
      // We have room
        i = 0;
        last_backslash = 0;
        tptr = src;
        while (*tptr != 32 && *tptr != 13 && *tptr != ';') {
            if (*tptr == '\\') {
                last_backslash = i;
            }
            ++tptr;
            ++i;
        }

        if (last_backslash != 0) {
          // Copy the path over
            dptr = (char *)rpath[rpath_count].filename;
            for (i=0; i<=last_backslash; i++) {
                *dptr++ = *src++;
            }
            for ( ; i < sizeof(rpath[rpath_count].filename); i++) {
                *dptr++ = 0;
            }
            ++rpath_count;
        }
    }
}