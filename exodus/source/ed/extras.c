// extras.c
//
// Exodus OBJECT Manager
//






void add_file(void)     // function
{
    ushort key, i;
    ulong last_offset, this_offset;
    struct FILE_RECORD fi_add;
    struct FILE_RECORD huge *fiptr;
    struct FILE_RECORD huge *ptr;

    full_strnset((char huge *)fi_add.name, 32,sizeof(fi_add.name));

    reset_input();
    file_screen();
    push_input(32,26,(char huge *)fi_add.name, sizeof(fi_add.name), _INPUT_UPPER, _INPUT_NO_SPACES);
  try_again:
    key = get_input();
    if (key == f10) {
      // They want to save changes.  Verify everything is valid
        for (i=0; i<input_count; i++) {
            if (verify_no_spaces_in_input(i)) {
                current_input = i;
                goto try_again;
            }
        }


      // Ok, the input is valid.  Let's copy it to a permanent record
      // Find the last base object
        this_offset = header.next_avail_offset;
        ptr = (struct FILE_RECORD huge *)(buf + this_offset);
        if (header.first_file_offset == -1) {
            header.first_file_offset = this_offset;
            ptr->prev_file = -1;
        } else {
            last_offset = header.first_file_offset;
            fiptr = (struct FILE_RECORD huge *)(buf + last_offset);
            while (fiptr->next_file != -1) {
                last_offset = fiptr->next_file;
                fiptr = (struct FILE_RECORD huge *)(buf + last_offset);
            }
            fiptr->next_file = this_offset;

          // Copy fields unique to the addition of a new record
            ptr->prev_file = last_offset;
        }
      // Copy the data
        ++header.file_records;
        header.next_avail_offset += sizeof(struct FILE_RECORD);
        highlighted_file = this_offset;
        ptr->status = 0;
        full_strncpy((char huge *)ptr->name, (char huge *)fi_add.name, sizeof(fi_add.name));
        ptr->next_file = -1;
        ptr->first_func = -1;
    }
}




void add_function(void)     // function
{
    ushort key, i;
    ulong last_offset, this_offset;
    struct FUNC_RECORD fu_add;
    struct FILE_RECORD huge *fiptr;
    struct FUNC_RECORD huge *fuptr;
    struct FUNC_RECORD huge *ptr;

    full_strnset((char huge *)fu_add.name, 32, sizeof(fu_add.name));

    reset_input();
    function_screen();
    push_input(32,26,(char huge *)fu_add.name, sizeof(fu_add.name), _INPUT_MIXED, _INPUT_NO_SPACES);
  try_again:
    key = get_input();
    if (key == f10) {
      // They want to save changes.  Verify everything is valid
        for (i=0; i<input_count; i++) {
            if (verify_no_spaces_in_input(i)) {
                current_input = i;
                goto try_again;
            }
        }


      // Ok, the input is valid.  Let's copy it to a permanent record
      // Find the last base object
        fiptr = (struct FILE_RECORD huge *)(buf + highlighted_file);
        this_offset = header.next_avail_offset;
        ptr = (struct FUNC_RECORD huge *)(buf + this_offset);
        if (fiptr->first_func == -1) {
            fiptr->first_func = this_offset;
            ptr->prev_func = -1;               // No previous record data
        } else {
          // Find the last object in the chain (to update the link)
            last_offset = fiptr->first_func;
            fuptr = (struct FUNC_RECORD huge *)(buf + last_offset);
            while (fuptr->next_func != -1) {
                last_offset = fuptr->next_func;
                fuptr = (struct FUNC_RECORD huge *)(buf + last_offset);
            }
            fuptr->next_func = this_offset;

          // Copy fields unique to the addition of a new record
            ptr->prev_func = last_offset;      // Update the link
        }
        header.next_avail_offset += sizeof(struct FUNC_RECORD);
        highlighted_function = this_offset;
        ++header.func_records;
        ptr->status = 0;
        full_strncpy((char huge *)ptr->name, (char huge *)fu_add.name, sizeof(fu_add.name));
        ptr->next_func = -1;
    }
}




void edit_file(void)     // function
{
    ushort key, i;
    struct FILE_RECORD fi_add;
    struct FILE_RECORD huge *fiptr;
    char huge *screen_ptr;

    screen_ptr = item_save(_SCREEN);
    fiptr = (struct FILE_RECORD huge *)(buf + highlighted_file);
    full_strncpy((char huge *)fi_add.name, fiptr->name, sizeof(fi_add.name));

    reset_input();
    file_screen();
    push_input(32,26,(char huge *)fi_add.name, sizeof(fi_add.name), _INPUT_UPPER, _INPUT_NO_SPACES);
  try_again:
    key = get_input();
    if (key == f10) {
      // They want to save changes.  Verify everything is valid
        for (i=0; i<input_count; i++) {
            if (verify_no_spaces_in_input(i)) {
                current_input = i;
                goto try_again;
            }
        }

      // Copy the data back to permanent space
        full_strncpy((char huge *)fiptr->name, (char huge *)fi_add.name, sizeof(fi_add.name));
    }
    item_restore(screen_ptr);
}




void edit_function(void)     // function
{
    ushort key, i;
    struct FUNC_RECORD fu_add;
    struct FUNC_RECORD huge *fuptr;
    char huge *screen_ptr;

    screen_ptr = item_save(_SCREEN);
    fuptr = (struct FUNC_RECORD huge *)(buf + highlighted_function);
    full_strncpy((char huge *)fu_add.name, fuptr->name, sizeof(fu_add.name));

    reset_input();
    function_screen();
    push_input(32,26,(char huge *)fu_add.name, sizeof(fu_add.name), _INPUT_MIXED, _INPUT_NO_SPACES);
  try_again:
    key = get_input();
    if (key == f10) {
      // They want to save changes.  Verify everything is valid
        for (i=0; i<input_count; i++) {
            if (verify_no_spaces_in_input(i)) {
                current_input = i;
                goto try_again;
            }
        }
        full_strncpy((char huge *)fuptr->name, (char huge *)fu_add.name, sizeof(fu_add.name));
    }
    item_restore(screen_ptr);
}




void draw_files(ushort cursor)     // function
{
    ushort top_line,x;
    ulong current_offset, start_offset;
    struct FILE_RECORD huge *ptr;
    int displayed;

    top_line = 4;
    x=0;
    if (header.first_file_offset == -1) {
      // No base objects have been added yet
        display_text_length(top_line,x,no_files_text,51);
        if (cursor) {
            pos_cursor(top_line,x);
        }
    } else {
      // There is data to print
        ptr = (struct FILE_RECORD huge *)(buf + header.first_file_offset);
        current_offset = header.first_file_offset;
        start_offset = current_offset;
        displayed = 0;
      cont1:
        while (top_line < 75) {
            if (current_offset == highlighted_file) {
                displayed = 1;
            }
            if (ptr->next_file == -1) {
              // No more
                if (displayed == 1) {
                    goto display_it;
                }
                goto quit;
            } else {
                current_offset = ptr->next_file;
                ptr = (struct FILE_RECORD huge *)(buf + current_offset);
            }
            ++top_line;
        }
        if (top_line == 75 && displayed == 0) {
            start_offset = current_offset;
            top_line = 4;
            goto cont1;
        }

      // Now, display the data
      display_it:
        current_offset = start_offset;
        ptr = (struct FILE_RECORD huge *)(buf + current_offset);
        top_line = 4;
        while (top_line < 75) {
            if (current_offset == highlighted_file) {
                color = 31;
                if (cursor) {
                    pos_cursor(top_line,x);
                }
            } else {
                color = 159;
            }
            display_far_text_length(top_line,x,(char huge *)(ptr->name),51);
            if (ptr->next_file == -1) {
              // No more
                goto quit;
            } else {
                current_offset = ptr->next_file;
                ptr = (struct FILE_RECORD huge *)(buf + current_offset);
            }
            ++top_line;
        }
    }
  quit:
    ++top_line;
    while (top_line < 75) {
        display_text_length(top_line,x,empty_text,51);
        ++top_line;
    }
}




void draw_functions(ushort cursor)     // function
{
    ushort top_line,x;
    ulong current_offset, start_offset;
    struct FILE_RECORD huge *fiptr;
    struct FUNC_RECORD huge *fuptr;
    int displayed;

    top_line = 4;
    x=52;
    if (highlighted_function == -1) {
      // No base objects have been added yet
      no_objects:
        display_text_length(top_line,x,no_funcs_text,80);
        if (cursor) {
            pos_cursor(top_line,x);
        }
    } else {
      // There is data to print
        fiptr = (struct FILE_RECORD huge *)(buf + highlighted_file);
        if (fiptr->first_func == -1) {
            goto no_objects;
        }
        fuptr = (struct FUNC_RECORD huge *)(buf + fiptr->first_func);
        current_offset = fiptr->first_func;
        start_offset = current_offset;
        displayed = 0;
      cont1:
        while (top_line < 75) {
            if (current_offset == highlighted_function) {
                displayed = 1;
            }
            if (fuptr->next_func == -1) {
              // No more
                if (displayed == 1) {
                    goto display_it;
                }
                goto quit;
            } else {
                current_offset = fuptr->next_func;
                fuptr = (struct FUNC_RECORD huge *)(buf + current_offset);
            }
            ++top_line;
        }
        if (top_line == 75 && displayed == 0) {
            start_offset = current_offset;
            top_line = 4;
            goto cont1;
        }

      // Now, display the data
      display_it:
        current_offset = start_offset;
        fuptr = (struct FUNC_RECORD huge *)(buf + current_offset);
        top_line = 4;
        while (top_line < 75) {
            if (current_offset == highlighted_function) {
                color = 31;
                if (cursor) {
                    pos_cursor(top_line,x);
                }
            } else {
                color = 159;
            }
            display_far_text_length(top_line,x,(char huge *)fuptr->name,80);
            if (fuptr->next_func == -1) {
              // No more
                goto quit;
            } else {
                current_offset = fuptr->next_func;
                fuptr = (struct FUNC_RECORD huge *)(buf + current_offset);
            }
            ++top_line;
        }
    }
  quit:
    ++top_line;
    while (top_line < 75) {
        display_text_length(top_line,x,empty_text,80);
        ++top_line;
    }
}




void save_file(void)     // function
{
    ulong i;
    ushort block;
    char huge *ptr;

    fseek(fh,0,SEEK_SET);
    fwrite(&header,1,sizeof(header),fh);

    i = 0;
    while (i < header.next_avail_offset) {
        block = 0;
        ptr = (char huge *)(buf + i);
        while (i < header.next_avail_offset && block < sizeof(load_buf)) {
            load_buf[block++] = *ptr++;
            ++i;
        }
        fwrite(load_buf,1,block,fh);
    }
}




void pos_cursor(ushort y, ushort x)     // function
{
    _asm {
        mov     ah,02h
        xor     bh,bh
        mov     dh,y
        mov     dl,x
        int     0x10
    }
}




void get_cursor()     // function
{
    uchar x, y;

    _asm {
        mov     ah,03h
        xor     bh,bh
        int     0x10
        mov     y,dh
        mov     x,dl
    }
    cp.x = x;
    cp.y = y;
}




ushort get_a_key(void)     // function
{
    int i;
    ushort key;
    char huge *input;
    char huge *screen;
    struct MACRO_RECORD mac;

  get_next_key:
    if (running_macro == 1) {
        if (running_keys_left > 0) {
            --running_keys_left;
            key = *running_mac_keydata++;
        } else {
            running_macro = 0;
            goto get_next_key;
        }
    } else {
        _asm {
            xor     ah,ah
            int     0x16
            mov     key,ax
        }
    }
    if (getting_macro != -1) {
        if (running_macro == 0) {
            if (key == ctrl_m) {
                // They want to define a macro
                switch (getting_macro) {
                  case 0:
                    getting_macro = -1;
                    input = item_save(_INPUT);
                    screen = item_save(_SCREEN);

                    mac.key = 0xffff;
                    full_strnset((char huge *)mac.desc, 32, sizeof(mac.desc));
                    draw_macro_window();

                    reset_input();
                    push_input(33,60,(char huge *)&mac.key, sizeof(mac.desc), _INPUT_GET_A_KEY, 0);
                    push_input(34,60,(char huge *)mac.desc, sizeof(mac.desc), _INPUT_MIXED, _INPUT_SPACES);
                    key = get_input();
                    if (key == f10) {
                        // They're saving this macro
                        // See if this key already exists
                        defining_macro = total_macros;
                        for (i=0; i<MAX_MACROS; i++) {
                            if (macro[i].key == mac.key) {
                                // We found one to replace

                                defining_macro = i;
                                break;
                            }
                        }
                        macro[defining_macro].key = mac.key;
                        macro[defining_macro].num_keys = 0;
                        macro[defining_macro].start_offset = next_mac_keydata - mac_keydata;
                        full_strncpy((char huge *)macro[defining_macro].desc, mac.desc, sizeof(mac.desc));
                        getting_macro = 1;
                    } else {
                        getting_macro = 0;
                    }

                    item_restore(screen);
                    item_restore(input);
                    break;
                  case 1:
                    if (defining_macro == total_macros) {
                        ++total_macros;
                        if (total_macros > MAX_MACROS) {
                            total_macros = 0;
                        }
                    }
                    getting_macro = 0;
                    break;
                }
                goto get_next_key;
            }
            if (getting_macro == 1) {
                // We have to store this key as part of the current macro
                if ((next_mac_keydata - mac_keydata) < MAX_KEYSTROKES) {
                    *next_mac_keydata++ = key;
                    ++macro[defining_macro].num_keys;
                }
            }
        }
        if (running_macro == 0) {
            // They're not running a macro, so we see if
            for (i=0; i<MAX_MACROS; i++) {
                if (key == macro[i].key) {
                    // We found a macro to run!  Woo hoo!
                    running_macro = 1;
                    running_mac_keydata = mac_keydata + macro[i].start_offset;
                    running_keys_left = macro[i].num_keys;
                    goto get_next_key;
                }
            }
        }
    }
    return(key);
}




void display_text(ushort y, ushort x, char *ptr)     // function
{
    char huge *vptr;
    char _ch, save_ch;

    _ch = color;
    vptr = ((char huge *)0xb8000000) + (((y*132) + x) * 2);
    while (*ptr != 0) {
        switch (*ptr) {
          case '¯':
            ++ptr;
            _ch = *ptr;
            break;
          case 'ô':
            save_ch = _ch;
            _asm {
                mov     al,_ch
                not     al
                mov     _ch,al
            }
            break;
          case 'õ':
            _ch = save_ch;
            break;
          default:
            *vptr++ = *ptr;
            *vptr++ = _ch;
        }
        ++ptr;
    }
}




void display_text_length(ushort y, ushort x, char *ptr, ushort len)     // function
{
    char huge *vptr;
    char _ch, save_ch;

    _ch = color;
    vptr = ((char huge *)0xb8000000) + (((y*132) + x) * 2);
    while (len > 0) {
        switch (*ptr) {
          case '¯':
            ++ptr;
            _ch = *ptr;
            break;
          case 'ô':
            save_ch = _ch;
            _asm {
                mov     al,_ch
                not     al
                mov     _ch,al
            }
            break;
          case 'õ':
            _ch = save_ch;
            break;
          default:
            --len;
            *vptr++ = *ptr;
            *vptr++ = _ch;
        }
        ++ptr;
    }
}




void display_text_only(ushort y, ushort x, char *ptr)     // function
{
    char huge *vptr;

    vptr = ((char huge *)0xb8000000) + (((y*132) + x) * 2);
    while (*ptr != 0) {
        switch (*ptr) {
          case '¯':
            ++ptr;
            break;
          case 'ô':
          case 'õ':
            break;
          default:
            *vptr = *ptr;
            vptr += 2;
        }
        ++ptr;
    }
}




void display_far_text_length(ushort y, ushort x, char huge *ptr, ushort len)     // function
{
    char huge *vptr;
    char _ch, save_ch;

    if (ptr != (char huge *)NULL) {
        _ch = color;
        vptr = ((char huge *)0xb8000000) + (((y*132) + x) * 2);
        while (len > 0) {
            switch (*ptr) {
              case '¯':
                ++ptr;
                _ch = *ptr;
                break;
              case 'ô':
                save_ch = _ch;
                _asm {
                    mov     al,_ch
                    not     al
                    mov     _ch,al
                }
                break;
              case 'õ':
                _ch = save_ch;
                break;
              default:
                --len;
                if (*ptr == 0) {
                    *vptr++ = 'ú';
                    *vptr++ = _ch;
                } else {
                    *vptr++ = *ptr;
                    *vptr++ = _ch;
                }
            }
            ++ptr;
        }
    }
}




void display_far_text_only_length(ushort y, ushort x, char huge *ptr, ushort len)     // function
{
    char huge *vptr;

    vptr = ((char huge *)0xb8000000) + (((y*132) + x) * 2);
    while (len > 0) {
        switch (*ptr) {
          case '¯':
            ++ptr;
            break;
          case 'ô':
          case 'õ':
            break;
          default:
            --len;
            if (*ptr == 0) {
                *vptr = 'ú';
            } else {
                *vptr = *ptr;
            }
            vptr += 2;
        }
        ++ptr;
    }
}




void main_screen(void)     // function
{
    display_text( 0,0,text0);
    display_text( 1,0,text1);
    display_text( 2,0,text2);
    display_text( 3,0,text3);
    display_text( 4,0,text4);
    display_text( 5,0,text4);
    display_text( 6,0,text4);
    display_text( 7,0,text4);
    display_text( 8,0,text4);
    display_text( 9,0,text4);
    display_text(10,0,text4);
    display_text(11,0,text4);
    display_text(12,0,text4);
    display_text(13,0,text4);
    display_text(14,0,text4);
    display_text(15,0,text4);
    display_text(16,0,text4);
    display_text(17,0,text4);
    display_text(18,0,text4);
    display_text(19,0,text4);
    display_text(20,0,text4);
    display_text(21,0,text4);
    display_text(22,0,text4);
    display_text(23,0,text4);
    display_text(24,0,text4);
    display_text(25,0,text4);
    display_text(26,0,text4);
    display_text(27,0,text4);
    display_text(28,0,text4);
    display_text(29,0,text4);
    display_text(30,0,text4);
    display_text(31,0,text4);
    display_text(32,0,text4);
    display_text(33,0,text4);
    display_text(34,0,text4);
    display_text(35,0,text4);
    display_text(36,0,text4);
    display_text(37,0,text4);
    display_text(38,0,text4);
    display_text(39,0,text4);
    display_text(40,0,text4);
    display_text(41,0,text4);
    display_text(42,0,text4);
    display_text(43,0,text4);
    display_text(44,0,text4);
    display_text(45,0,text4);
    display_text(46,0,text4);
    display_text(47,0,text4);
    display_text(48,0,text4);
    display_text(49,0,text4);
    display_text(50,0,text4);
    display_text(51,0,text4);
    display_text(52,0,text4);
    display_text(53,0,text4);
    display_text(54,0,text4);
    display_text(55,0,text4);
    display_text(56,0,text4);
    display_text(57,0,text4);
    display_text(58,0,text4);
    display_text(59,0,text4);
    display_text(60,0,text4);
    display_text(61,0,text4);
    display_text(62,0,text4);
    display_text(63,0,text4);
    display_text(64,0,text4);
    display_text(65,0,text4);
    display_text(66,0,text4);
    display_text(67,0,text4);
    display_text(68,0,text4);
    display_text(69,0,text4);
    display_text(70,0,text4);
    display_text(71,0,text4);
    display_text(72,0,text4);
    display_text(73,0,text4);
    display_text(74,0,text4);
    display_text(75,0,text75);
    display_text(76,0,text76);
    display_text(77,0,text77);
    display_text(78,0,text78);
    display_text(79,0,text79);
}




void display_common_screen(void)     // function
{
    display_text(30,25,xx_text0);
    // This line is displayed in either file_screen() or function_screen()
    display_text(32,25,xx_text2);
    display_text(33,25,xx_text3);
    display_text(34,25,xx_text4);
    display_text(35,25,xx_text5);
    display_text(36,25,xx_text6);
}




void file_screen(void)     // function
{
    color = 31;
    display_common_screen();
    display_text(31,25,fi_text1);
}




void function_screen(void)     // function
{
    color = 31;
    display_common_screen();
    display_text(31,25,fu_text1);
}




void clear_screen(void)     // function
{
    char huge *vptr;
    ushort i;

    vptr = (char huge *)0xb8000000;
    i = 132*80*2;
    while (i > 0) {
        *vptr++ = ' ';
        *vptr++ = 7;
        --i;
    }
    pos_cursor(0,0);
}




void reset_input(void)     // function
{
    input_count = 0;
    current_input = 0;
    input_hook_count = 0;
}




void set_input(void)     // function
{
    if (input_count != -1) {
        current_input = input_count;
    } else {
        current_input = 0;
    }
}




void push_input(ushort y, ushort x, char huge *ptr, ushort length, char type, char verify)     // function
{
    if (input_count < MAX_INPUT) {
        input[input_count].y = y;
        input[input_count].x = x;
        input[input_count].ptr = ptr;
        input[input_count].length = length;
        input[input_count].type = type;
        input[input_count].verify = verify;
        ++input_count;
    }
}




void push_input_hook_key(ushort key, int type, char huge *fptr)     // function
{
    ushort *tptr;

    if (input_hook_count < MAX_HOOKS && input_count != 0) {
        input_hook[input_hook_count].item = input_count-1;
        input_hook[input_hook_count].type = type;
        input_hook[input_hook_count].fptr = fptr;
        tptr = (ushort *)&input_hook[input_hook_count].data;
        *tptr = key;
        ++input_hook_count;
    }
}




ushort get_input(void)     // function
{
    ushort key;
    ushort i;
    char c1, c2, looking;
    ushort *tptr;
    char huge *fptr;

    if (input_count == 0) {
        key = get_a_key();
    } else {
      // We actually have to get input
      start_over:
        _offset = 0;

      redraw_all:
        color = 113;
        for (i=0; i<input_count; i++) {
            if (i != current_input) {
                if (input[i].type == _INPUT_GET_A_KEY) {
                    display_far_text_length(input[i].y, input[i].x, get_keystroke_text(*(ushort *)(input[i].ptr)), input[i].length);
                } else {
                    display_far_text_length(input[i].y, input[i].x, input[i].ptr, input[i].length);
                }
            }
        }

        while (1) {
          try_again:
            color = 249;
            if (input[current_input].type == _INPUT_GET_A_KEY) {
                display_far_text_length(input[current_input].y, input[current_input].x, get_keystroke_text(*(ushort *)(input[current_input].ptr)), input[current_input].length);
            } else {
                display_far_text_length(input[current_input].y, input[current_input].x, input[current_input].ptr, input[current_input].length);
            }
            pos_cursor(input[current_input].y, input[current_input].x + _offset);
            set_cursor_size();
            key = get_a_key();
            for (i=0; i<input_hook_count; i++) {
                if (input_hook[i].type == _INPUT_HOOK_KEY_BEFORE && input_hook[i].item == current_input) {
                    // This is a keyboard hook for this item before the key is processed
                    tptr = (ushort *)&input_hook[i].data;
                    if (*tptr == key) {
                        // And it's the correct key
                        fptr = input_hook[i].fptr;
                        _asm {
                            call    fptr
                        }
                    }
                }
            }
            switch (key) {
              case escape:
                goto quit;
              case f10:
                for (i=0; i<input_count; i++) {
                    if (verify_no_spaces_in_input(i)) {
                        current_input = i;
                        goto start_over;
                    }
                }
                goto quit;
              case f8:                                              // Delete to end of line
                if (input[current_input].type != _INPUT_GET_A_KEY) {
                    for (i=_offset; i<input[current_input].length; i++) {
                        *(input[current_input].ptr + i) = 32;
                    }
                }
                break;
              case f7:
                if (break_here == 1) {
                    break_here = 0;
                } else {
                    break_here = 1;
                }
                break;
              case home:
              case grey_home:
                _offset = 0;
                break;
              case end:
              case grey_end:
                if (input[current_input].type != _INPUT_GET_A_KEY) {
                    _offset = input[current_input].length;
                    while (_offset > 0 && *(input[current_input].ptr + _offset - 1) == 32) {
                        --_offset;
                    }
                }
                break;
              case down:
              case grey_down:
              case tab:
              case enter:
              case grey_enter:
              next_field:
                ++current_input;
                if (current_input >= input_count) {
                    if (key != down && key != grey_down) {
                        current_input = 0;
                    } else {
                        --current_input;
                    }
                }
                _offset = 0;
                goto redraw_all;
              case up:
              case grey_up:
              case shift_tab:
                if (current_input > 0) {
                    --current_input;
                } else {
                    if (key != up && key != grey_up) {
                        current_input = input_count - 1;
                    }
                }
                _offset = 0;
                goto redraw_all;
              case backspace:
                if (_offset > 0) {
                    --_offset;
                    if (insert_mode) {
                        get_input_delete_char(_offset);
                    } else {
                        *(input[current_input].ptr + _offset) = 32;
                    }
                }
                break;
              case delete:
              case grey_delete:
                if (input[current_input].type != _INPUT_GET_A_KEY) {
                    if (_offset < input[current_input].length) {
                        get_input_delete_char(_offset);
                    }
                }
                break;
              case insert:
              case grey_insert:
                if (insert_mode) {
                    insert_mode = 0;
                } else {
                    insert_mode = 1;
                }
                break;
              case left:
              case grey_left:
                if (_offset > 0) {
                    --_offset;
                }
                break;
              case right:
              case grey_right:
                if (input[current_input].type != _INPUT_GET_A_KEY) {
                    if (_offset < input[current_input].length) {
                        ++_offset;
                    }
                }
                break;
              case ctrl_left:
              case ctrl_grey_left:
                if (_offset > 0) {
                    --_offset;
                    looking = 0;
                    while (_offset > 0) {
                        if (_offset-1 >= 0) {
                            c1 = *(input[current_input].ptr + _offset - 1);
                            if (looking == 0) {
                              // We first look for the first non-space character
                                if (c1 != 32 && c1 != '_') {
                                    looking = 1;
                                }
                            } else {
                                if (c1 == 32 || c1 == '_') {
                                    goto try_again;
                                }
                            }
                        }
                        --_offset;
                    }
                }
                break;
              case ctrl_right:
              case ctrl_grey_right:
                if (input[current_input].type != _INPUT_GET_A_KEY) {
                    if (_offset < input[current_input].length) {
                        ++_offset;
                        c1 = *(input[current_input].ptr + _offset + 1);
                        if (c1 == 32 || c1 == '_') {
                            looking = 0;
                        } else {
                            looking = 1;
                        }
                        while (_offset < input[current_input].length) {
                            c1 = *(input[current_input].ptr + _offset - 1);
                            if (looking == 0) {
                              // We first look for the first non-space character
                                if (c1 != 32 && c1 != '_') {
                                    looking = 1;
                                }
                            } else {
                                if (c1 == 32 || c1 == '_') {
                                    c1 = *(input[current_input].ptr + _offset);
                                    if (c1 != 32 && c1 != '_') {
                                        goto check_eol;
                                    }
                                }
                            }
                            ++_offset;
                        }
                      // See if we're passed the end of the text (cursor is something like:  "This is a test _")
                      check_eol:
                        i = input[current_input].length;
                        while (i > 0 && *(input[current_input].ptr + i - 1) == 32) {
                            --i;
                        }
                        if (i < _offset) {
                            _offset = i;
                        }
                    }
                }
                break;
              default:
                _asm {
                    mov     ax,key
                    mov     c1,ah
                    mov     c2,al
                }
                if (c2 == 32 && input[current_input].verify == _INPUT_NO_SPACES) {
                    c2 = '_';
                }
              // It's just a character
                switch (input[current_input].type) {
                  case _INPUT_UPPER:
                    if (c2 >= 'a' && c2 <= 'z') {
                      // It's lower-case, conver it
                        c2 -= 0x20;
                    }
                    break;
                  case _INPUT_LOWER:
                    if (c2 >= 'A' && c2 <= 'Z') {
                      // It's upper-case, convert it
                        c2 += 0x20;
                    }
                    break;
                  case _INPUT_NUMBERS:
                    if (!((c2 >= '0' && c2 <= '9') || c2 == '.' || c2 == '-' || c2 == '+')) {
                      // It's not a valid character for a number
                        goto try_again;
                    }
                    break;
                  case _INPUT_GET_A_KEY:
                    *(ushort *)(input[current_input].ptr) = key;
                    goto next_field;
                }
                if (c2 == 0) {
                    // We can't store NULLs
                    goto try_again;
                }
                if (_offset < input[current_input].length) {
                    if (insert_mode) {
                        get_input_insert_space(_offset);
                    }
                    *(input[current_input].ptr + _offset) = c2;
                    ++_offset;
                }
            }
            for (i=0; i<input_hook_count; i++) {
                if (input_hook[i].type == _INPUT_HOOK_KEY_AFTER && input_hook[i].item == current_input) {
                    // This is a keyboard hook for this item after the key has been processed
                    tptr = (ushort *)&input_hook[i].data;
                    if (*tptr == key) {
                        // And it's the correct key
                        fptr = input_hook[i].fptr;
                        _asm {
                            call    fptr
                        }
                    }
                }
            }
        }
    }
  quit:
    return(key);
}




void get_input_insert_space(ushort _offset)     // function
{
    char huge *ptr;
    ushort i;

    ptr = input[current_input].ptr;
    if (_offset < input[current_input].length) {
        for (i=input[current_input].length-2; i >= _offset; i--) {       // -1 for operation, an additional -1 for base-1 to base-0
            *(ptr+i+1) = *(ptr+i);
            if (i == 0) {
                goto quit;
            }
        }
      quit:
        if (_offset == 0) {
            *ptr = 0;
        } else {
            *(ptr+i+1) = 32;
        }
    }
}




void get_input_delete_char(ushort _offset)     // function
{
    char huge *ptr;
    ushort i;

    ptr = input[current_input].ptr;
    if (_offset < input[current_input].length) {
        for (i=_offset; i < input[current_input].length; i++) {
            if (i+1 < input[current_input].length) {
                *(ptr+i) = *(ptr+i+1);
            } else {
                *(ptr+i) = 32;
            }
        }
    }
}




void full_strnset(char huge *ptr, char c, ushort length)     // function
{
    while (length-- > 0) {
        *ptr++ = c;
    }
}




void full_strnset_far(char huge *ptr, char huge *eptr, char c)     // function
{
    while (ptr < eptr) {
        *ptr++ = c;
    }
}




void full_strncpy(char huge *dest, char huge *src, ushort length)     // function
{
    while (length-- > 0) {
        *dest++ = *src++;
    }
}




int full_strncmp(char huge *ptr1, char huge *ptr2, ushort length)
{
    int k;

    while (length-- > 0) {
        k = *ptr2++ - *ptr1++;
        if (k != 0) {
            return(k);
        }
    }
    return(0);
}




void set_cursor_size(void)     // function
{
    if (insert_mode) {
        _asm {
            mov     ah,1
            mov     ch,0
            mov     cl,5
            int     0x10
        }
    } else {
        _asm {
            mov     ah,1
            mov     ch,4
            mov     cl,5
            int     0x10
        }
    }
}




// This function returns 1 if there is a space or if the length is 0
ushort verify_no_spaces_in_input(ushort check_num)     // function
{
    ushort i, len;

  // Find out where the last character is
    if (input[check_num].length == 1) {
        if (*(input[check_num].ptr) == 32) {
            return(1);
        }
    } else {
        i = input[check_num].length - 1;
        while (i > 0 && *(input[check_num].ptr + i) == 32) {
            --i;
        }
        if (i != 0) {
          // See if there are any spaces between
            len = i;
            for (i=0; i<len; i++) {
                if (*(input[check_num].ptr + i) == 32) {
                    return(1);
                }
            }
        }
    }
    return(0);
}




char huge *item_save(int item)     // function
{
    int x, y;
    ulong size;

    char huge *ptr;
    switch (item) {
      case _INPUT:
        // They want to push the current get_input() data
        size = input_count * sizeof(struct INPUT_RECORD);
        ptr = (char huge *)halloc(size+9+16,1);
        if (ptr != (char huge *)NULL) {
        //
        // Mini-structure:
        // Off Len  Desc
        //  0   1   Type of item
        //  1   2   _offset
        //  3   2   input_count
        //  5   2   current_input
        //  7   2   insert_mode
        //  9   4   size
        //  13+     INPUT_RECORD data
        //
            *ptr = (char)item;
            *(ushort huge *)(ptr+1) = _offset;
            *(ushort huge *)(ptr+3) = input_count;
            *(ushort huge *)(ptr+5) = current_input;
            *(ushort huge *)(ptr+7) = insert_mode;
            *(ulong  huge *)(ptr+9) = size;
            full_strncpy(ptr+13, (char huge *)input, (ushort)size);
        }
        break;
      case _SCREEN:
        // They want to push the current screen contents
        ptr = (char huge *)halloc((132*80*2)+16,1);
        if (ptr != (char huge *)NULL) {
        //
        // Mini-structure:
        // Off Len  Desc
        //  0   1   Type of item
        //  1   2   Y coord for cursor
        //  3   2   X coord for cursor
        //  5+      screen
        //
            get_cursor();
            *ptr = (char)item;
            *(ushort huge *)(ptr+1) = cp.y;
            *(ushort huge *)(ptr+3) = cp.x;
            full_strncpy(ptr+5, (char huge *)0xb8000000, 132*80*2);
        }
        return(ptr);
        break;
      default:
        return((char huge *)NULL);
    }
}




void item_restore(char huge *iptr)      // iptr = item_ptr     // function
{
    int x, y;
    ulong size;

    switch (*iptr) {
      case _INPUT:
        // They're restoring previously saved get_input() data
        _offset       = *(ushort huge *)(iptr+1);
        input_count   = *(ushort huge *)(iptr+3);
        current_input = *(ushort huge *)(iptr+5);
        insert_mode   = *(ushort huge *)(iptr+7);
        size          = *(ulong  huge *)(iptr+9);
        full_strncpy((char huge *)input, iptr+13, (ushort)size);
        _ffree(iptr);
        break;
      case _SCREEN:
        // They're restoring a previously saved screen
        // Refer to mini-structure in save_item() for info
        full_strncpy((char huge *)0xb8000000, iptr+5, 132*80*2);
        y = *(ushort huge *)(iptr+1);
        x = *(ushort huge *)(iptr+3);
        pos_cursor(y,x);
        _ffree(iptr);
        break;
    }
}




void draw_macro_window(void)     // function
{
    color = 177;
    display_text(30,52,mac_text0);
    display_text(31,52,mac_text1);
    display_text(32,52,mac_text2);
    display_text(33,52,mac_text3);
    display_text(34,52,mac_text4);
    display_text(35,52,mac_text5);
    display_text(36,52,mac_text6);
    display_text(37,52,mac_text7);
}




char huge *get_keystroke_text(ushort key)     // function
{
    int i;
    ushort k;
    char *sptr, *dptr;

    if (key != 0xffff) {
        i = 0;
        while (key_listing[i*2] != 0xffff && key_listing[i*2] != key) {
            ++i;
        }
        if (key_listing[i*2] == 0xffff) {
            return((char huge *)unknown_key);
        } else {
            k = key_listing[(i*2)+1];
            _asm {
                mov     ax,k
                mov     sptr,ax
            }
            dptr = (char *)known_key;
            while (*dptr != 0 && *sptr != ';') {
                *dptr++ = *sptr++;
            }
            while (*dptr != 0) {
                *dptr++ = 32;
            }
            return((char huge *)known_key);
        }
    } else {
        return((char huge *)press_a_key);
    }
}




void load_macros(void)     // function
{
    int i;
    FILE *mfh;
    ushort numread, keystroke_numread;
    ushort *tptr;
    ushort huge *fptr;

    total_macros = 0;
    if ((mfh = fopen("macros.dat","rb")) != NULL) {
        printf("Loading macros, ");
        mac_keydata = (ushort huge *)halloc(MAX_KEYSTROKES,2);
        if (mac_keydata != (ushort huge *)NULL) {
            full_strnset_far((char huge *)mac_keydata, (char huge *)(mac_keydata+MAX_KEYSTROKES), (char)0xff);
            numread = fread(macro,1,sizeof(struct MACRO_RECORD)*MAX_MACROS,mfh);
            // Load the keystroke data (up to MAX_KEYSTROKES keystrokes)
            keystroke_numread = fread(load_buf,2,MAX_KEYSTROKES,mfh);
            next_mac_keydata = mac_keydata + keystroke_numread;
            numread += keystroke_numread*2;
            tptr = (ushort *)load_buf;
            fptr = mac_keydata;
            for (i=0; i<keystroke_numread; i++) {
                *fptr++ = *tptr++;
            }
            // Count the active macros
            for (i=0; i<MAX_MACROS; i++) {
                if (macro[i].key != 0xffff) {
                    ++total_macros;
                }
            }
            if (i != 0) {
                printf("%i found, ",total_macros);
            }
            printf("done.\n");
        }
        fclose(mfh);
    }
}




void save_macros(void)     // function
{
    int i;
    FILE *mfh;
    ushort *tptr;
    ushort huge *fptr;

    if ((mfh = fopen("macros.dat","rb+")) != NULL) {
        fwrite(macro,1,sizeof(struct MACRO_RECORD)*MAX_MACROS,mfh);
        tptr = (ushort *)load_buf;
        fptr = mac_keydata;
        for (i=next_mac_keydata-mac_keydata; i>0; i--) {
            *tptr++ = *fptr++;
        }
        fwrite(load_buf,2,(ushort)(next_mac_keydata - mac_keydata),mfh);
        fclose(mfh);
    }
}




#pragma check_stack(off)
#pragma check_pointer(off)
void tse_edit_file(void)     // function
{
    int i;
    char funcname[128];
    char filename[128];
    char *tptr1, *tptr2;
    char huge *fptr;

// Microsoft C automatically does this:
// _asm {
//     enter   x,0
//     push    di
//     push    si
// }
//
    full_strnset_far((char huge *)funcname, (char huge *)funcname + sizeof(funcname), 0);
    full_strnset_far((char huge *)filename, (char huge *)filename + sizeof(funcname), 0);

    // Do the function name
    tptr1 = (char *)funcname;
    full_strncpy((char huge *)tptr1,(char huge *)"-g",2);
    tptr1 += 2;
    tptr2 = (char huge *)input[current_input-1].ptr;
    i = input[current_input-1].length;
    while (i > 0 && *(tptr2+i-1) == 32) {
        --i;
    }
    while (i-- > 0) {
        *tptr1++ = *tptr2++;
    }

    // Do the file name
    tptr1 = (char *)filename;
    fptr = input[current_input].ptr;
    i = input[current_input].length;
    while (i > 0 && *(fptr+i-1) == 32) {
        --i;
    }
    while (i-- > 0) {
        *tptr1++ = *fptr++;
    }

    spawnlp(P_WAIT, "e", "e", filename, funcname, NULL);

    turn_high_intensity_on();

// This code was added to allow the RETF that C won't allow in a tiny model (for whatever reason)
    _asm {
        pop     si
        pop     di
        leave
        retf
    }
}




void turn_high_intensity_on(void)     // function
{
    _asm {
        mov     ax,0x1003
        xor     bl,bl
        int     0x10
    }
}




int populated_string_length(char huge *ptr, int length)     // function
{
    while (length > 0) {
        if (*(ptr+length-1) != 32) {
            return(length);
        }
        --length;
    }
    return(0);
}