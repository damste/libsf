; create.asp
;
; Exodus BIOS Object Handler - Create object algorithms
;
;   00000 - BASE OBJECTS
;   11111 - OBJECTS
;





;; 00000 - BASE OBJECTS
    OBJECT_create_base_object       PROC
    ; This routine is called to create a base object
    ;
    ; Upon entry:         ax - handle
    ;               ds:[esi] - far ptr to base of object's parameters
    ;
    ; Upon exit:    carry?  CLEARÂ The object is created
    ;                            À ebx - handle
    ;                         SET-eax is error code
    ;
        enter   12,0
      ; [ebp-04] dword, value to store for first base offset (if any)
      ; [ebp-08] dword, value to store for next base offset (if any)
      ; [ebp-12] dword, where to store [ebp-08]
        push    gs
        pushad

      ;; Verify that the handle they're using is a valid task
        callf   iTASK_locate_handle                                 ; Returns, carry?, gs:[edi] - far ptr to TASK data structure
        .IF (carry?)
            mov     dword ptr ss:[esp+28],_TASK_NOT_FOUND
            jmp     quit
        .ENDIF


      ;; Get the pointer to this task's object structure
        mov     es,word ptr gs:[edi+_TASK_ENTRY_SELECTOR_OBJECTS]
        xor     edi,edi
      ; Right now, es:[edi] - far ptr to the base of this task's object
      ;            ds:[esi] - far ptr to the user's object definition area
        mov     dword ptr ss:[ebp-04],-1
        mov     dword ptr ss:[ebp-08],-1
        mov     dword ptr ss:[ebp-12],-1


      ;; Find out where we're adding this base object
        mov     edx,dword ptr es:[edi+_OBJECT_HEADER_FIRST_BASE_OBJECT]
        mov     ebx,dword ptr es:[edi+_OBJECT_HEADER_NEXT_OBJECT]
        .IF (edx == -1)
          ; There isn't currently a base object for this task
          ; So, we raise the flag indicating we need to set one (if creation is successful)
            mov     dword ptr ss:[ebp-04],ebx
        .ELSE
          ; We have to traverse the base objects that already exist to find the last one
            mov     edx,dword ptr es:[edi+_OBJECT_HEADER_FIRST_BASE_OBJECT]
            .WHILE (dword ptr es:[edx+_OBJECT_NEXT_BASE_OBJECT] != -1)
                mov     edx,es:[edx+_OBJECT_NEXT_BASE_OBJECT]
            .ENDW
          ; Right now, es:[edx] - far ptr to the last base object
            mov     dword ptr ss:[ebp-08],ebx
            mov     dword ptr ss:[ebp-12],edx
        .ENDIF
        mov     edx,ebx
      ; Right now, es:[edx] - far ptr to the slot for this base object


      ;; Initialize common header fields
        mov     dword ptr es:[edx+_OBJECT_NEXT_BASE_OBJECT],-1
        mov     dword ptr es:[edx+_OBJECT_FIRST_OBJECT],-1


      ;; Call appropriate base object initialization routine
        mov     al,byte ptr ds:[esi]
        .IF (al == _GROUPING)
            call    invOBJECT_create_base_object_grouping
        .ELSEIF (al == _DESKTOP)
            call    invOBJECT_create_base_object_desktop
        .ELSEIF (al == _WINDOW)
            call    invOBJECT_create_base_object_window
        .ELSEIF (al == _CONSOLE)
            call    invOBJECT_create_base_object_console
        .ELSEIF (al == _TEXT_MODE)
            call    invOBJECT_create_base_object_text_mode
        .ELSEIF (al == _MONO_DESKTOP)
            call    invOBJECT_create_base_object_mono_desktop
        .ELSEIF (al == _MONO_WINDOW)
            call    invOBJECT_create_base_object_mono_window
        .ELSEIF (al == _MONO_CONSOLE)
            call    invOBJECT_create_base_object_mono_console
        .ELSEIF (al == _MONO_TEXT_MODE)
            call    invOBJECT_create_base_object_mono_text_mode
        .ELSE
          ; It's an unknown object type
            mov     dword ptr ss:[esp+28],_UNKNOWN_OBJECT_TYPE
            stc
        .ENDIF
        jc      quit


      ;; Update the pointers after a successful creation
        .IF (dword ptr ss:[ebp-4] != -1)
          ; Set the first base object pointer
            mov     ebx,dword ptr ss:[ebp-4]
            mov     dword ptr es:[_OBJECT_HEADER_FIRST_BASE_OBJECT],ebx
        .ENDIF
        .IF (dword ptr ss:[ebp-12] != -1)
          ; Set the first base object pointer
            mov     ebx,dword ptr ss:[ebp-8]
            mov     edx,dword ptr ss:[ebp-12]
            mov     dword ptr es:[edx+_OBJECT_NEXT_BASE_OBJECT],ebx
        .ENDIF
        add     dword ptr es:[_OBJECT_HEADER_NEXT_OBJECT],_BO_LENGTH
        clc


      quit:
        popad
        pop     gs
        leave
        retf
    OBJECT_create_base_object       ENDP




    invOBJECT_create_base_object_grouping       PROC
    ; This routine handles the creation of a _GROUPING object
    ; * Note:  Refer to inf\objects.inf for information on this object
    ;
    ; Upon entry:   ds:[esi] - far ptr to _GROUPING data item in structure
    ;               es:[edi] - far ptr to the TASK structure
    ;
    ; Upon exit:    carry? - SET if error
    ;                        CLEAR - the object was created
    ;

        ret
    invOBJECT_create_base_object_grouping       ENDP




    invOBJECT_create_base_object_desktop        PROC
    ; This routine handles the creation of a _DESKTOP object
    ; * Note:  Refer to inf\objects.inf for information on this object
    ;
    ; Upon entry:   ds:[esi] - far ptr to _DESKTOP data item in structure
    ;               es:[edi] - far ptr to the TASK structure
    ;
    ; Upon exit:    carry? - SET if error
    ;                        CLEAR - the object was created
    ;
        mov     byte ptr es:[edx+_BASE_OBJECT_TYPE],_DESKTOP

      ; Headers unique to _DESKTOP items
      ; Required headers
        mov     ebx,dword ptr ds:[esi+_BO_LD_TOP]
        mov     dword ptr es:[edx+_BO_D_TOP],ebx
        mov     ebx,dword ptr ds:[esi+_BO_LD_LEFT]
        mov     dword ptr es:[edx+_BO_D_LEFT],ebx
        mov     ebx,dword ptr ds:[esi+_BO_LD_WIDTH]
        mov     dword ptr es:[edx+_BO_D_WIDTH],ebx
        mov     ebx,dword ptr ds:[esi+_BO_LD_HEIGHT]
        mov     dword ptr es:[edx+_BO_D_HEIGHT],ebx

      ; Default initialization
        mov     eax,-1
        xor     ecx,ecx
        mov     byte ptr es:[edx+_BO_D_ENABLED],1
        mov     byte ptr es:[edx+_BO_D_VISIBLE],cl
        mov     byte ptr es:[edx+_BO_D_BACKGROUND+_OBJECT_RED],cl
        mov     byte ptr es:[edx+_BO_D_BACKGROUND+_OBJECT_GREEN],cl
        mov     byte ptr es:[edx+_BO_D_BACKGROUND+_OBJECT_BLUE],cl
        mov     byte ptr es:[edx+_BO_D_ICON_HORIZONTAL],20
        mov     byte ptr es:[edx+_BO_D_ICON_VERTICAL],20
        mov     byte ptr es:[edx+_BO_D_MENU_POSITION],6
        mov     word ptr es:[edx+_BO_D_MENU_HEIGHT],30
        mov     dword ptr es:[edx+_BO_D_WALLPAPER],eax
        mov     dword ptr es:[edx+_BO_D_MISC_1],eax
        mov     dword ptr es:[edx+_BO_D_MISC_2],eax
        mov     dword ptr es:[edx+_BO_D_MISC_3],eax
        mov     dword ptr es:[edx+_BO_D_MISC_4],eax
        mov     byte ptr es:[edx+_BO_D_MISC_FLAG_1],al
        mov     byte ptr es:[edx+_BO_D_MISC_FLAG_2],al
        mov     byte ptr es:[edx+_BO_D_MISC_FLAG_3],al
        add     edx,_BO_D_ACTIVATE
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_ACTIVATE],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_CLICK_BOTH_SINGLE],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_CLICK_BOTH_DOUBLE],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_CLICK_LEFT_SINGLE],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_CLICK_LEFT_DOUBLE],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_CLICK_LEFT_DOWN],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_CLICK_LEFT_UP],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_CLICK_RIGHT_SINGLE],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_CLICK_RIGHT_DOUBLE],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_CLICK_RIGHT_DOWN],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_CLICK_RIGHT_UP],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_DROPPED_INTO_LEFT],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_DROPPED_INTO_RIGHT],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_DRAG_LEFT_START],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_DRAG_LEFT_STOP],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_DRAG_RIGHT_START],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_DRAG_RIGHT_STOP],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_FOCUS_GOT],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_FOCUS_LOST],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_FOCUS_SET],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_HOVER],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_KEYSTROKE],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_WHEN_CREATED],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_WHEN_DESTROYED],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_REQUESTOR],eax
        mov     dword ptr es:[edx-_BO_D_ACTIVATE+_BO_D_REFRESH],eax
        sub     edx,_BO_D_ACTIVATE
        add     esi,_BO_LD_LENGTH

      ; Right now, ds:[esi] is sitting on any subsequent properties that are initialized to "other-than-default" values
        mov     bl,_PROPERTY_START
        .WHILE (byte ptr ds:[esi] != _OBJECT_END)
            mov     al,byte ptr ds:[esi]
            .IF (al == _PROPERTY_START || al == _EVENT_START)
                mov     bl,al
            .ELSE
                .IF (bl == _PROPERTY_START)
                  ; They're setting a property, which one?
                    .IF     (al == _DP_ENABLED)
                        mov     al,byte ptr ds:[esi+_BO_LD_ENABLED]
                        mov     byte ptr es:[edx+_BO_D_ENABLED],al
                        add     esi,_BO_LD_ENABLED_SIZE
                    .ELSEIF (al == _DP_VISIBLE)
                        mov     al,byte ptr ds:[esi+_BO_LD_VISIBLE]
                        mov     byte ptr es:[edx+_BO_D_VISIBLE],al
                        add     esi,_BO_LD_VISIBLE_SIZE
                    .ELSEIF (al == _DP_BACKGROUND)
                        mov     al,byte ptr ds:[esi+_BO_LD_BACKGROUND_RED]
                        mov     byte ptr es:[edx+_BO_D_BACKGROUND+_OBJECT_RED],al
                        mov     al,byte ptr ds:[esi+_BO_LD_BACKGROUND_GREEN]
                        mov     byte ptr es:[edx+_BO_D_BACKGROUND+_OBJECT_GREEN],al
                        mov     al,byte ptr ds:[esi+_BO_LD_BACKGROUND_BLUE]
                        mov     byte ptr es:[edx+_BO_D_BACKGROUND+_OBJECT_BLUE],al
                        add     esi,_BO_LD_BACKGROUND_SIZE
                    .ELSEIF (al == _DP_ICON_HORIZONTAL)
                        mov     al,byte ptr ds:[esi+_BO_LD_ICON_HORIZONTAL]
                        mov     byte ptr es:[edx+_BO_D_ICON_HORIZONTAL],al
                        add     esi,_BO_LD_ICON_HORIZONTAL_SIZE
                    .ELSEIF (al == _DP_ICON_VERTICAL)
                        mov     al,byte ptr ds:[esi+_BO_LD_ICON_VERTICAL]
                        mov     byte ptr es:[edx+_BO_D_ICON_VERTICAL],al
                        add     esi,_BO_LD_ICON_VERTICAL_SIZE
                    .ELSEIF (al == _DP_MENU_POSITION)
                        mov     al,byte ptr ds:[esi+_BO_LD_MENU_POSITION]
                        mov     byte ptr es:[edx+_BO_D_MENU_POSITION],al
                        add     esi,_BO_LD_MENU_POSITION_SIZE
                    .ELSEIF (al == _DP_MENU_HEIGHT)
                        mov     al,byte ptr ds:[esi+_BO_LD_MENU_HEIGHT]
                        mov     byte ptr es:[edx+_BO_D_MENU_HEIGHT],al
                        add     esi,_BO_LD_MENU_HEIGHT_SIZE
                    .ELSEIF (al == _DP_MENU_AUTOHIDE)
                        mov     al,byte ptr ds:[esi+_BO_LD_MENU_AUTOHIDE]
                        mov     byte ptr es:[edx+_BO_D_MENU_AUTOHIDE],al
                        add     esi,_BO_LD_MENU_AUTOHIDE_SIZE
                    .ELSEIF (al == _DP_MISC_1)
                        mov     al,byte ptr ds:[esi+_BO_LD_MISC_1]
                        mov     byte ptr es:[edx+_BO_D_MISC_1],al
                        add     esi,_BO_LD_MISC_1_SIZE
                    .ELSEIF (al == _DP_MISC_2)
                        mov     al,byte ptr ds:[esi+_BO_LD_MISC_2]
                        mov     byte ptr es:[edx+_BO_D_MISC_2],al
                        add     esi,_BO_LD_MISC_2_SIZE
                    .ELSEIF (al == _DP_MISC_3)
                        mov     al,byte ptr ds:[esi+_BO_LD_MISC_3]
                        mov     byte ptr es:[edx+_BO_D_MISC_3],al
                        add     esi,_BO_LD_MISC_3_SIZE
                    .ELSEIF (al == _DP_MISC_4)
                        mov     al,byte ptr ds:[esi+_BO_LD_MISC_4]
                        mov     byte ptr es:[edx+_BO_D_MISC_4],al
                        add     esi,_BO_LD_MISC_4_SIZE
                    .ELSEIF (al == _DP_MISC_FLAG_1)
                        mov     al,byte ptr ds:[esi+_BO_LD_MISC_FLAG_1]
                        mov     byte ptr es:[edx+_BO_D_MISC_FLAG_1],al
                        add     esi,_BO_LD_MISC_FLAG_1_SIZE
                    .ELSEIF (al == _DP_MISC_FLAG_2)
                        mov     al,byte ptr ds:[esi+_BO_LD_MISC_FLAG_2]
                        mov     byte ptr es:[edx+_BO_D_MISC_FLAG_2],al
                        add     esi,_BO_LD_MISC_FLAG_2_SIZE
                    .ELSEIF (al == _DP_MISC_FLAG_3)
                        mov     al,byte ptr ds:[esi+_BO_LD_MISC_FLAG_3]
                        mov     byte ptr es:[edx+_BO_D_MISC_FLAG_3],al
                        add     esi,_BO_LD_MISC_FLAG_3_SIZE
                    .ELSEIF (al == _DP_WALLPAPER)
                        mov     al,byte ptr ds:[esi+_BO_LD_WALLPAPER]
                        mov     byte ptr es:[edx+_BO_D_WALLPAPER],al
                        add     esi,_BO_LD_WALLPAPER_SIZE
                    .ELSE
                      ; Unknown property, abort
                        mov     dword ptr ss:[esp+28],_UNKNOWN_OBJECT_PROPERTY
                        stc
                        jmp     quit
                    .ENDIF
                .ELSE
                  ; They're setting an event, which one?
                    mov     ecx,dword ptr ds:[esi+1]
                    .IF     (al == _DE_ACTIVATE)
                        mov     dword ptr es:[edx+_BO_D_ACTIVATE],ecx
                    .ELSEIF (al == _DE_CLICK_BOTH_SINGLE)
                        mov     dword ptr es:[edx+_BO_D_CLICK_BOTH_SINGLE],ecx
                    .ELSEIF (al == _DE_CLICK_BOTH_DOUBLE)
                        mov     dword ptr es:[edx+_BO_D_CLICK_BOTH_DOUBLE],ecx
                    .ELSEIF (al == _DE_CLICK_LEFT_SINGLE)
                        mov     dword ptr es:[edx+_BO_D_CLICK_LEFT_SINGLE],ecx
                    .ELSEIF (al == _DE_CLICK_LEFT_DOUBLE)
                        mov     dword ptr es:[edx+_BO_D_CLICK_LEFT_DOUBLE],ecx
                    .ELSEIF (al == _DE_CLICK_LEFT_DOWN)
                        mov     dword ptr es:[edx+_BO_D_CLICK_LEFT_DOWN],ecx
                    .ELSEIF (al == _DE_CLICK_LEFT_UP)
                        mov     dword ptr es:[edx+_BO_D_CLICK_LEFT_UP],ecx
                    .ELSEIF (al == _DE_CLICK_RIGHT_SINGLE)
                        mov     dword ptr es:[edx+_BO_D_CLICK_RIGHT_SINGLE],ecx
                    .ELSEIF (al == _DE_CLICK_RIGHT_DOUBLE)
                        mov     dword ptr es:[edx+_BO_D_CLICK_RIGHT_DOUBLE],ecx
                    .ELSEIF (al == _DE_CLICK_RIGHT_DOWN)
                        mov     dword ptr es:[edx+_BO_D_CLICK_RIGHT_DOWN],ecx
                    .ELSEIF (al == _DE_CLICK_RIGHT_UP)
                        mov     dword ptr es:[edx+_BO_D_CLICK_RIGHT_UP],ecx
                    .ELSEIF (al == _DE_DROPPED_INTO_LEFT)
                        mov     dword ptr es:[edx+_BO_D_DROPPED_INTO_LEFT],ecx
                    .ELSEIF (al == _DE_DROPPED_INTO_RIGHT)
                        mov     dword ptr es:[edx+_BO_D_DROPPED_INTO_RIGHT],ecx
                    .ELSEIF (al == _DE_DRAG_LEFT_START)
                        mov     dword ptr es:[edx+_BO_D_DRAG_LEFT_START],ecx
                    .ELSEIF (al == _DE_DRAG_LEFT_STOP)
                        mov     dword ptr es:[edx+_BO_D_DRAG_LEFT_STOP],ecx
                    .ELSEIF (al == _DE_DRAG_RIGHT_START)
                        mov     dword ptr es:[edx+_BO_D_DRAG_RIGHT_START],ecx
                    .ELSEIF (al == _DE_DRAG_RIGHT_STOP)
                        mov     dword ptr es:[edx+_BO_D_DRAG_RIGHT_STOP],ecx
                    .ELSEIF (al == _DE_FOCUS_GOT)
                        mov     dword ptr es:[edx+_BO_D_FOCUS_GOT],ecx
                    .ELSEIF (al == _DE_FOCUS_LOST)
                        mov     dword ptr es:[edx+_BO_D_FOCUS_LOST],ecx
                    .ELSEIF (al == _DE_FOCUS_SET)
                        mov     dword ptr es:[edx+_BO_D_FOCUS_SET],ecx
                    .ELSEIF (al == _DE_HOVER)
                        mov     dword ptr es:[edx+_BO_D_HOVER],ecx
                    .ELSEIF (al == _DE_KEYSTROKE)
                        mov     dword ptr es:[edx+_BO_D_KEYSTROKE],ecx
                    .ELSEIF (al == _DE_WHEN_CREATED)
                        mov     dword ptr es:[edx+_BO_D_WHEN_CREATED],ecx
                    .ELSEIF (al == _DE_WHEN_DESTROYED)
                        mov     dword ptr es:[edx+_BO_D_WHEN_DESTROYED],ecx
                    .ELSEIF (al == _DE_REQUESTOR)
                        mov     dword ptr es:[edx+_BO_D_REQUESTOR],ecx
                    .ELSEIF (al == _DE_REFRESH)
                        mov     dword ptr es:[edx+_BO_D_REFRESH],ecx
                    .ELSE
                      ; Unknown property, abort
                        mov     dword ptr ss:[esp+28],_UNKNOWN_OBJECT_EVENT
                        stc
                        jmp     quit
                    .ENDIF
                    add     esi,5
                .ENDIF
            .ENDIF
        .ENDW
      ; We're successful!

      quit:
        ret
    invOBJECT_create_base_object_desktop        ENDP




    invOBJECT_create_base_object_window     PROC
    ; This routine handles the creation of a _WINDOW object
    ; * Note:  Refer to inf\objects.inf for information on this object
    ;
    ; Upon entry:   ds:[esi] - far ptr to _WINDOW data item in structure
    ;               es:[edi] - far ptr to the TASK structure
    ;
    ; Upon exit:    carry? - SET if error
    ;                        CLEAR - the object was created
    ;

        ret
    invOBJECT_create_base_object_window     ENDP




    invOBJECT_create_base_object_console        PROC
    ; This routine handles the creation of a _CONSOLE object
    ; * Note:  Refer to inf\objects.inf for information on this object
    ;
    ; Upon entry:   ds:[esi] - far ptr to _CONSOLE data item in structure
    ;               es:[edi] - far ptr to the TASK structure
    ;
    ; Upon exit:    carry? - SET if error
    ;                        CLEAR - the object was created
    ;

        ret
    invOBJECT_create_base_object_console        ENDP




    invOBJECT_create_base_object_text_mode      PROC
    ; This routine handles the creation of a _TEXT_MODE object
    ; * Note:  Refer to inf\objects.inf for information on this object
    ;
    ; Upon entry:   ds:[esi] - far ptr to _TEXT_MODE data item in structure
    ;               es:[edi] - far ptr to the TASK structure
    ;
    ; Upon exit:    carry? - SET if error
    ;                        CLEAR - the object was created
    ;

        ret
    invOBJECT_create_base_object_text_mode      ENDP




    invOBJECT_create_base_object_mono_desktop       PROC
    ; This routine handles the creation of a _MONO_DESKTOP object
    ; * Note:  Refer to inf\objects.inf for information on this object
    ;
    ; Upon entry:   ds:[esi] - far ptr to _MONO_DESKTOP data item in structure
    ;               es:[edi] - far ptr to the TASK structure
    ;
    ; Upon exit:    carry? - SET if error
    ;                        CLEAR - the object was created
    ;

        ret
    invOBJECT_create_base_object_mono_desktop       ENDP




    invOBJECT_create_base_object_mono_window        PROC
    ; This routine handles the creation of a _MONO_WINDOW object
    ; * Note:  Refer to inf\objects.inf for information on this object
    ;
    ; Upon entry:   ds:[esi] - far ptr to _MONO_WINDOW data item in structure
    ;               es:[edi] - far ptr to the TASK structure
    ;
    ; Upon exit:    carry? - SET if error
    ;                        CLEAR - the object was created
    ;

        ret
    invOBJECT_create_base_object_mono_window        ENDP




    invOBJECT_create_base_object_mono_console       PROC
    ; This routine handles the creation of a _MONO_CONSOLE object
    ; * Note:  Refer to inf\objects.inf for information on this object
    ;
    ; Upon entry:   ds:[esi] - far ptr to _MONO_CONSOLE data item in structure
    ;               es:[edi] - far ptr to the TASK structure
    ;
    ; Upon exit:    carry? - SET if error
    ;                        CLEAR - the object was created
    ;

        ret
    invOBJECT_create_base_object_mono_console       ENDP




    invOBJECT_create_base_object_mono_text_mode     PROC
    ; This routine handles the creation of a _MONO_TEXT_MODE object
    ; * Note:  Refer to inf\objects.inf for information on this object
    ;
    ; Upon entry:   ds:[esi] - far ptr to _MONO_TEXT_MODE data item in structure
    ;               es:[edi] - far ptr to the TASK structure
    ;
    ; Upon exit:    carry? - SET if error
    ;                        CLEAR - the object was created
    ;

        ret
    invOBJECT_create_base_object_mono_text_mode     ENDP









;; 11111 - OBJECTS
    OBJECT_create_object        PROC
    ; This routine is called to create an object
    ; * Note:  Refer to inf\objects.inf for information on this object
    ;
    ; Upon entry:         ax - task handle
    ;                     bx - base object handle to add to
    ;               ds:[esi] - far ptr to base of object's parameters
    ;
    ; Upon exit:    carry?  CLEAR-The object is created
    ;                         SET-eax is error code
    ;
        enter   8,0
      ; [ebp-4] - dword, ptr to object to store "next object ptr"
      ; [ebp-8] - dword, ptr to where object gets added
        push    gs
        pushad


      ;; Verify the ask handle they've specified is valid
        callf   iTASK_locate_handle                                 ; Returns, carry?, gs:[edi] - far ptr to TASK data structure
        .IF (carry?)
            mov     dword ptr ss:[esp+28],_TASK_NOT_FOUND
            jmp     quit
        .ENDIF
        mov     es,word ptr gs:[edi+_TASK_ENTRY_SELECTOR_OBJECTS]
        xor     edi,edi
      ; Right now, es:[edi] - far ptr to the base of this task's object
      ;            ds:[esi] - far ptr to the user's object definition area


      ;; Verify the base object handle they've specifed is valid
        callf   iOBJECT_locate_task_object
        .IF (carry?)
            mov     dword ptr ss:[esp+28],_OBJECT_NOT_FOUND
            jmp     quit
        .ENDIF
      ; Right now, es:[ebx] - far ptr to base object
      ;            ds:[esi] - far ptr to object they want to add
      ;            es:[_OBJECT_HEADER_NEXT_OBJECT] - where the ds:[esi] object will be added


      ;; Skip to the last object for this base object
        mov     edx,dword ptr es:[ebx+_OBJECT_FIRST_OBJECT]
        mov     ecx,edx
        .WHILE (edx != -1)
            mov     ecx,edx
            mov     edx,dword ptr es:[edx+_OBJECT_NEXT_OBJECT]
        .ENDW
        mov     edi,dword ptr es:[_OBJECT_HEADER_NEXT_OBJECT]
      ; Right now, es:[ebx] - far ptr to base object to add to to
      ;            es:[edx] - last object in base-object's chain
      ;            es:[edi] - where object will be added
      ;            ds:[esi] - far ptr to object source


      ;; Determine where we'll be adding
        mov     dword ptr ss:[ebp-4],ecx
        mov     dword ptr ss:[ebp-8],edi


      ;; Add common fields
        mov     dword ptr es:[edi+_OBJECT_NEXT_BASE_OBJECT],-1
        mov     dword ptr es:[edi+_OBJECT_NEXT_OBJECT],-1


      ;; Add the object
        mov     al,byte ptr ds:[esi]
        .IF     (al == _INPUT_FIELD)
          ; It's an input field
        .ELSEIF     (al == _TEXT_FIELD)
          ; It's a text field
            call    invOBJECT_create_text_field
        .ELSEIF (al == _BUTTON)
          ; It's a button
        .ELSEIF (al == _MENU_BAR)
          ; It's a menu bar
        .ELSEIF (al == _MENU_POPUP)
          ; It's a popup menu
        .ELSEIF (al == _RADIO_DIAL)
          ; It's a radio dial
        .ELSEIF (al == _CHECK_BOX)
          ; It's a check box
        .ELSEIF (al == _CIRCLE_BOX)
          ; It's a circle box
        .ELSEIF (al == _PULLDOWN)
          ; It's a pulldown
        .ELSEIF (al == _SLIDE_BAR)
          ; It's a slide bar
        .ELSEIF (al == _PERCENT_BAR)
          ; It's a percent bar
        .ELSEIF (al == _TRAY)
          ; It's a tray
        .ELSEIF (al == _ICON)
          ; It's a icon
        .ELSEIF (al == _BITMAP)
          ; It's a bitmap
        .ELSEIF (al == _HLINE)
          ; It's a horizontal line
            call    invOBJECT_create_hline
        .ELSEIF (al == _VLINE)
          ; It's a vertical line
        .ELSEIF (al == _LINE)
          ; It's a line
        .ELSEIF (al == _OVAL)
          ; It's a oval
        .ELSEIF (al == _RECTANGLE)
          ; It's a rectangle
            call    invOBJECT_create_rectangle
        .ELSEIF (al == _SCROLL_BAR_HORIZONTAL)
          ; It's a horizontal scroll bar
        .ELSEIF (al == _SCROLL_BAR_VERTICAL)
          ; It's a vertical scroll bar
        .ELSEIF (al == _CASK)
          ; It's a cask
        .ELSEIF (al == _CFSCA_WINDOW)
          ; It's a cfsca window
        .ELSEIF (al == _NUMBERS_WINDOW)
          ; It's a numbers window
        .ELSEIF (al == _TYPESET_WINDOW)
          ; It's a typeset window
        .ELSEIF (al == _BORDER_BOX)
          ; It's a border box
            call    invOBJECT_create_border_box
        .ELSE
            mov     eax,_UNKNOWN_OBJECT_TYPE
            mov     dword ptr ss:[esp+28],eax
            jmp     quit
        .ENDIF
        jc      quit


      ;; Update pointers after a successful creation
        mov     edi,dword ptr ss:[ebp-8]
        .IF (dword ptr ss:[ebp-4] != -1)
          ; We are adding one more object into the chain
            mov     edx,dword ptr ss:[ebp-4]
            add     edx,_OBJECT_NEXT_OBJECT
        .ELSE
          ; We are adding the first one, so we add it to the base object
            mov     edx,ebx
            add     edx,_OBJECT_FIRST_OBJECT
        .ENDIF
        mov     dword ptr es:[edx],edi
        add     dword ptr es:[_OBJECT_HEADER_NEXT_OBJECT],_O_LENGTH
        clc


      quit:
        popad
        pop     gs
        leave
        retf
    OBJECT_create_object        ENDP




    invOBJECT_create_text_field     PROC
    ; This routine is used to create a text field
    ;
    ; Upon entry:   es:[ebx] - far ptr to base object to add to to
    ;               es:[edx] - last object in base-object's chain
    ;               es:[edi] - where object will be added
    ;               ds:[esi] - far ptr to object source
    ;
    ; Upon exit:    The object is created if it contains valid information
    ;
        pushad
      ; Headers unique to _TEXT_FIELD items
        mov     byte ptr es:[edi+_OBJECT_TYPE],_TEXT_FIELD
      ; Required headers
        mov     ebx,dword ptr ds:[esi+_O_LTF_TOP]
        mov     dword ptr es:[edi+_O_TF_TOP],ebx
        mov     ebx,dword ptr ds:[esi+_O_LTF_LEFT]
        mov     dword ptr es:[edi+_O_TF_LEFT],ebx
        mov     ebx,dword ptr ds:[esi+_O_LTF_WIDTH]
        mov     dword ptr es:[edi+_O_TF_WIDTH],ebx
        mov     ebx,dword ptr ds:[esi+_O_LTF_HEIGHT]
        mov     dword ptr es:[edi+_O_TF_HEIGHT],ebx
      ; Default initialization
        mov     eax,-1
        xor     ecx,ecx
        mov     byte ptr es:[edi+_O_TF_ENABLED],1
        mov     byte ptr es:[edi+_O_TF_VISIBLE],cl
        mov     byte ptr es:[edi+_O_TF_BORDER],cl
        mov     byte ptr es:[edi+_O_TF_ALIGNMENT],cl
        mov     byte ptr es:[edi+_O_TF_AUTO_SIZE],cl
        mov     byte ptr es:[edi+_O_TF_BACKGROUND+_OBJECT_RED],cl
        mov     byte ptr es:[edi+_O_TF_BACKGROUND+_OBJECT_GREEN],cl
        mov     byte ptr es:[edi+_O_TF_BACKGROUND+_OBJECT_BLUE],cl
        mov     byte ptr es:[edi+_O_TF_FOREGROUND+_OBJECT_RED],cl
        mov     byte ptr es:[edi+_O_TF_FOREGROUND+_OBJECT_GREEN],cl
        mov     byte ptr es:[edi+_O_TF_FOREGROUND+_OBJECT_BLUE],cl
        mov     dword ptr es:[edi+_O_TF_SOURCE_PTR_SEGMENT],eax
        mov     dword ptr es:[edi+_O_TF_SOURCE_PTR_OFFSET],eax
        mov     dword ptr es:[edi+_O_TF_FONT_NAME],eax
        mov     byte ptr es:[edi+_O_TF_FONT_SIZE],al
        mov     byte ptr es:[edi+_O_TF_FONT_TYPEFACE_BOLD],cl
        mov     byte ptr es:[edi+_O_TF_FONT_TYPEFACE_DITHER],cl
        mov     byte ptr es:[edi+_O_TF_FONT_TYPEFACE_ITALICS],cl
        mov     byte ptr es:[edi+_O_TF_FONT_TYPEFACE_REVERSE],cl
        mov     byte ptr es:[edi+_O_TF_FONT_TYPEFACE_STRIKETHROUGH],cl
        mov     byte ptr es:[edi+_O_TF_FONT_TYPEFACE_UNDERLINE],cl
        mov     dword ptr es:[edi+_O_TF_FONT_NAME_ID],eax
        mov     word ptr es:[edi+_O_TF_MARGIN_LEFT],cx
        mov     word ptr es:[edi+_O_TF_MARGIN_TOP],cx
        mov     dword ptr es:[edi+_O_TF_MISC_1],eax
        mov     dword ptr es:[edi+_O_TF_MISC_2],eax
        mov     dword ptr es:[edi+_O_TF_MISC_3],eax
        mov     dword ptr es:[edi+_O_TF_MISC_4],eax
        mov     byte ptr es:[edi+_O_TF_MISC_FLAG_1],al
        mov     byte ptr es:[edi+_O_TF_MISC_FLAG_2],al
        mov     byte ptr es:[edi+_O_TF_MISC_FLAG_3],al
        add     edi,_O_TF_ACTIVATE
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_ACTIVATE],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_CLICK_BOTH_SINGLE],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_CLICK_BOTH_DOUBLE],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_CLICK_LEFT_SINGLE],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_CLICK_LEFT_DOUBLE],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_CLICK_LEFT_DOWN],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_CLICK_LEFT_UP],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_CLICK_RIGHT_SINGLE],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_CLICK_RIGHT_DOUBLE],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_CLICK_RIGHT_DOWN],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_CLICK_RIGHT_UP],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_DROPPED_INTO_LEFT],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_DROPPED_INTO_RIGHT],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_DRAG_LEFT_START],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_DRAG_LEFT_STOP],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_DRAG_RIGHT_START],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_DRAG_RIGHT_STOP],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_FOCUS_GOT],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_FOCUS_LOST],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_FOCUS_SET],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_HOVER],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_KEYSTROKE],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_WHEN_CREATED],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_WHEN_DESTROYED],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_REQUESTOR],eax
        mov     dword ptr es:[edi-_O_TF_ACTIVATE+_O_TF_REFRESH],eax
        sub     edi,_O_TF_ACTIVATE
        add     esi,_O_LTF_LENGTH

      ; Right now, ds:[esi] is sitting on any properties that are initialized to "other-than-default" values
        mov     bl,_PROPERTY_START
        .WHILE (byte ptr ds:[esi] != _OBJECT_END)
            mov     al,byte ptr ds:[esi]
            .IF (al == _PROPERTY_START || al == _EVENT_START)
                mov     bl,al
            .ELSE
                .IF (bl == _PROPERTY_START)
                  ; They're setting a property, which one?
                    .IF (al == _TFP_ENABLED)
                        mov     al,byte ptr ds:[esi+_O_LTF_ENABLED]
                        mov     byte ptr es:[edi+_O_TF_ENABLED],al
                        add     esi,_O_LTF_ENABLED_SIZE
                    .ELSEIF (al == _TFP_VISIBLE)
                        mov     al,byte ptr ds:[esi+_O_LTF_VISIBLE]
                        mov     byte ptr es:[edi+_O_TF_VISIBLE],al
                        add     esi,_O_LTF_VISIBLE_SIZE
                    .ELSEIF (al == _TFP_BORDER)
                        mov     al,byte ptr ds:[esi+_O_LTF_BORDER]
                        mov     byte ptr es:[edi+_O_TF_BORDER],al
                        add     esi,_O_LTF_BORDER_SIZE
                    .ELSEIF (al == _TFP_ALIGNMENT)
                        mov     al,byte ptr ds:[esi+_O_LTF_ALIGNMENT]
                        mov     byte ptr es:[edi+_O_TF_ALIGNMENT],al
                        add     esi,_O_LTF_ALIGNMENT_SIZE
                    .ELSEIF (al == _TFP_AUTO_SIZE)
                        mov     al,byte ptr ds:[esi+_O_LTF_AUTO_SIZE]
                        mov     byte ptr es:[edi+_O_TF_AUTO_SIZE],al
                        add     esi,_O_LTF_AUTO_SIZE_SIZE
                    .ELSEIF (al == _TFP_COLOR_FOREGROUND)
                        mov     al,byte ptr ds:[esi+_O_LTF_FOREGROUND_RED]
                        mov     byte ptr es:[edi+_O_TF_FOREGROUND+_OBJECT_RED],al
                        mov     al,byte ptr ds:[esi+_O_LTF_FOREGROUND_GREEN]
                        mov     byte ptr es:[edi+_O_TF_FOREGROUND+_OBJECT_GREEN],al
                        mov     al,byte ptr ds:[esi+_O_LTF_FOREGROUND_BLUE]
                        mov     byte ptr es:[edi+_O_TF_FOREGROUND+_OBJECT_BLUE],al
                        add     esi,_O_LTF_BACKGROUND_SIZE
                    .ELSEIF (al == _TFP_COLOR_BACKGROUND)
                        mov     al,byte ptr ds:[esi+_O_LTF_BACKGROUND_RED]
                        mov     byte ptr es:[edi+_O_TF_BACKGROUND+_OBJECT_RED],al
                        mov     al,byte ptr ds:[esi+_O_LTF_BACKGROUND_GREEN]
                        mov     byte ptr es:[edi+_O_TF_BACKGROUND+_OBJECT_GREEN],al
                        mov     al,byte ptr ds:[esi+_O_LTF_BACKGROUND_BLUE]
                        mov     byte ptr es:[edi+_O_TF_BACKGROUND+_OBJECT_BLUE],al
                        add     esi,_O_LTF_BACKGROUND_SIZE
                    .ELSEIF (al == _TFP_SOURCE_PTR)
                        movzx   eax,word ptr ds:[esi+_O_LTF_SOURCE_PTR_SEGMENT]
                        mov     dword ptr es:[edi+_O_TF_SOURCE_PTR_SEGMENT],eax
                        mov     eax,dword ptr ds:[esi+_O_LTF_SOURCE_PTR_OFFSET]
                        mov     dword ptr es:[edi+_O_TF_SOURCE_PTR_OFFSET],eax
                        add     esi,_O_LTF_SOURCE_PTR_SIZE
                    .ELSEIF (al == _TFP_FONT_NAME)
                        mov     eax,dword ptr ds:[esi+_O_LTF_FONT_NAME]
                        mov     dword ptr es:[edi+_O_TF_FONT_NAME],eax
                        add     esi,_O_LTF_FONT_NAME_SIZE
                    .ELSEIF (al == _TFP_FONT_SIZE)
                        mov     al,byte ptr ds:[esi+_O_LTF_FONT_SIZE]
                        mov     byte ptr es:[edi+_O_TF_FONT_SIZE],al
                        add     esi,_O_LTF_FONT_SIZE_SIZE
                    .ELSEIF (al == _TFP_FONT_TYPEFACE_BOLD)
                        mov     al,byte ptr ds:[esi+_O_LTF_FONT_TYPEFACE_BOLD]
                        mov     byte ptr es:[edi+_O_TF_FONT_TYPEFACE_BOLD],al
                        add     esi,_O_LTF_FONT_TYPEFACE_BOLD_SIZE
                    .ELSEIF (al == _TFP_FONT_TYPEFACE_DITHER)
                        mov     al,byte ptr ds:[esi+_O_LTF_FONT_TYPEFACE_DITHER]
                        mov     byte ptr es:[edi+_O_TF_FONT_TYPEFACE_DITHER],al
                        add     esi,_O_LTF_FONT_TYPEFACE_DITHER_SIZE
                    .ELSEIF (al == _TFP_FONT_TYPEFACE_ITALICS)
                        mov     al,byte ptr ds:[esi+_O_LTF_FONT_TYPEFACE_ITALICS]
                        mov     byte ptr es:[edi+_O_TF_FONT_TYPEFACE_ITALICS],al
                        add     esi,_O_LTF_FONT_TYPEFACE_ITALICS_SIZE
                    .ELSEIF (al == _TFP_FONT_TYPEFACE_REVERSE)
                        mov     al,byte ptr ds:[esi+_O_LTF_FONT_TYPEFACE_REVERSE]
                        mov     byte ptr es:[edi+_O_TF_FONT_TYPEFACE_REVERSE],al
                        add     esi,_O_LTF_FONT_TYPEFACE_REVERSE_SIZE
                    .ELSEIF (al == _TFP_FONT_TYPEFACE_STRIKETHROUGH)
                        mov     al,byte ptr ds:[esi+_O_LTF_FONT_TYPEFACE_STRIKETHROUGH]
                        mov     byte ptr es:[edi+_O_TF_FONT_TYPEFACE_STRIKETHROUGH],al
                        add     esi,_O_LTF_FONT_TYPEFACE_STRIKETHROUGH_SIZE
                    .ELSEIF (al == _TFP_FONT_TYPEFACE_UNDERLINE)
                        mov     al,byte ptr ds:[esi+_O_LTF_FONT_TYPEFACE_UNDERLINE]
                        mov     byte ptr es:[edi+_O_TF_FONT_TYPEFACE_UNDERLINE],al
                        add     esi,_O_LTF_FONT_TYPEFACE_UNDERLINE_SIZE
                    .ELSEIF (al == _TFP_FONT_NAME_ID)
                        mov     eax,dword ptr ds:[esi+_O_LTF_FONT_NAME_ID]
                        mov     dword ptr es:[edi+_O_TF_FONT_NAME_ID],eax
                        add     esi,_O_LTF_FONT_NAME_ID_SIZE
                    .ELSEIF (al == _TFP_MARGIN_LEFT)
                        mov     ax,word ptr ds:[esi+_O_LTF_MARGIN_LEFT]
                        mov     word ptr es:[edi+_O_TF_MARGIN_LEFT],ax
                        add     esi,_O_LTF_MARGIN_LEFT_SIZE
                    .ELSEIF (al == _TFP_MARGIN_TOP)
                        mov     ax,word ptr ds:[esi+_O_LTF_MARGIN_TOP]
                        mov     word ptr es:[edi+_O_TF_MARGIN_TOP],ax
                        add     esi,_O_LTF_MARGIN_TOP_SIZE
                    .ELSEIF (al == _TFP_MISC_1)
                        mov     eax,dword ptr ds:[esi+_O_LTF_MISC_1]
                        mov     dword ptr es:[edi+_O_TF_MISC_1],eax
                        add     esi,_O_LTF_MISC_1_SIZE
                    .ELSEIF (al == _TFP_MISC_2)
                        mov     eax,dword ptr ds:[esi+_O_LTF_MISC_2]
                        mov     dword ptr es:[edi+_O_TF_MISC_2],eax
                        add     esi,_O_LTF_MISC_2_SIZE
                    .ELSEIF (al == _TFP_MISC_3)
                        mov     eax,dword ptr ds:[esi+_O_LTF_MISC_3]
                        mov     dword ptr es:[edi+_O_TF_MISC_3],eax
                        add     esi,_O_LTF_MISC_3_SIZE
                    .ELSEIF (al == _TFP_MISC_4)
                        mov     eax,dword ptr ds:[esi+_O_LTF_MISC_4]
                        mov     dword ptr es:[edi+_O_TF_MISC_4],eax
                        add     esi,_O_LTF_MISC_4_SIZE
                    .ELSEIF (al == _TFP_MISC_FLAG_1)
                        mov     al,byte ptr ds:[esi+_O_LTF_MISC_FLAG_1]
                        mov     byte ptr es:[edi+_O_TF_MISC_FLAG_1],al
                        add     esi,_O_LTF_MISC_FLAG_1_SIZE
                    .ELSEIF (al == _TFP_MISC_FLAG_2)
                        mov     al,byte ptr ds:[esi+_O_LTF_MISC_FLAG_2]
                        mov     byte ptr es:[edi+_O_TF_MISC_FLAG_2],al
                        add     esi,_O_LTF_MISC_FLAG_2_SIZE
                    .ELSEIF (al == _TFP_MISC_FLAG_3)
                        mov     al,byte ptr ds:[esi+_O_LTF_MISC_FLAG_3]
                        mov     byte ptr es:[edi+_O_TF_MISC_FLAG_3],al
                        add     esi,_O_LTF_MISC_FLAG_3_SIZE
                    .ELSE
                      ; Unknown property, abort
                        mov     dword ptr ss:[esp+28],_UNKNOWN_OBJECT_PROPERTY
                        stc
                        jmp     quit
                    .ENDIF
                .ELSE
                  ; They're setting an event, which one?
                    mov     ecx,dword ptr ds:[esi+1]
                    .IF     (al == _TFE_ACTIVATE)
                        mov     dword ptr es:[edx+_O_TF_ACTIVATE],ecx
                    .ELSEIF (al == _TFE_CLICK_BOTH_SINGLE)
                        mov     dword ptr es:[edx+_O_TF_CLICK_BOTH_SINGLE],ecx
                    .ELSEIF (al == _TFE_CLICK_BOTH_DOUBLE)
                        mov     dword ptr es:[edx+_O_TF_CLICK_BOTH_DOUBLE],ecx
                    .ELSEIF (al == _TFE_CLICK_LEFT_SINGLE)
                        mov     dword ptr es:[edx+_O_TF_CLICK_LEFT_SINGLE],ecx
                    .ELSEIF (al == _TFE_CLICK_LEFT_DOUBLE)
                        mov     dword ptr es:[edx+_O_TF_CLICK_LEFT_DOUBLE],ecx
                    .ELSEIF (al == _TFE_CLICK_LEFT_DOWN)
                        mov     dword ptr es:[edx+_O_TF_CLICK_LEFT_DOWN],ecx
                    .ELSEIF (al == _TFE_CLICK_LEFT_UP)
                        mov     dword ptr es:[edx+_O_TF_CLICK_LEFT_UP],ecx
                    .ELSEIF (al == _TFE_CLICK_RIGHT_SINGLE)
                        mov     dword ptr es:[edx+_O_TF_CLICK_RIGHT_SINGLE],ecx
                    .ELSEIF (al == _TFE_CLICK_RIGHT_DOUBLE)
                        mov     dword ptr es:[edx+_O_TF_CLICK_RIGHT_DOUBLE],ecx
                    .ELSEIF (al == _TFE_CLICK_RIGHT_DOWN)
                        mov     dword ptr es:[edx+_O_TF_CLICK_RIGHT_DOWN],ecx
                    .ELSEIF (al == _TFE_CLICK_RIGHT_UP)
                        mov     dword ptr es:[edx+_O_TF_CLICK_RIGHT_UP],ecx
                    .ELSEIF (al == _TFE_DROPPED_INTO_LEFT)
                        mov     dword ptr es:[edx+_O_TF_DROPPED_INTO_LEFT],ecx
                    .ELSEIF (al == _TFE_DROPPED_INTO_RIGHT)
                        mov     dword ptr es:[edx+_O_TF_DROPPED_INTO_RIGHT],ecx
                    .ELSEIF (al == _TFE_DRAG_LEFT_START)
                        mov     dword ptr es:[edx+_O_TF_DRAG_LEFT_START],ecx
                    .ELSEIF (al == _TFE_DRAG_LEFT_STOP)
                        mov     dword ptr es:[edx+_O_TF_DRAG_LEFT_STOP],ecx
                    .ELSEIF (al == _TFE_DRAG_RIGHT_START)
                        mov     dword ptr es:[edx+_O_TF_DRAG_RIGHT_START],ecx
                    .ELSEIF (al == _TFE_DRAG_RIGHT_STOP)
                        mov     dword ptr es:[edx+_O_TF_DRAG_RIGHT_STOP],ecx
                    .ELSEIF (al == _TFE_FOCUS_GOT)
                        mov     dword ptr es:[edx+_O_TF_FOCUS_GOT],ecx
                    .ELSEIF (al == _TFE_FOCUS_LOST)
                        mov     dword ptr es:[edx+_O_TF_FOCUS_LOST],ecx
                    .ELSEIF (al == _TFE_FOCUS_SET)
                        mov     dword ptr es:[edx+_O_TF_FOCUS_SET],ecx
                    .ELSEIF (al == _TFE_HOVER)
                        mov     dword ptr es:[edx+_O_TF_HOVER],ecx
                    .ELSEIF (al == _TFE_KEYSTROKE)
                        mov     dword ptr es:[edx+_O_TF_KEYSTROKE],ecx
                    .ELSEIF (al == _TFE_WHEN_CREATED)
                        mov     dword ptr es:[edx+_O_TF_WHEN_CREATED],ecx
                    .ELSEIF (al == _TFE_WHEN_DESTROYED)
                        mov     dword ptr es:[edx+_O_TF_WHEN_DESTROYED],ecx
                    .ELSEIF (al == _TFE_REQUESTOR)
                        mov     dword ptr es:[edx+_O_TF_REQUESTOR],ecx
                    .ELSEIF (al == _TFE_REFRESH)
                        mov     dword ptr es:[edx+_O_TF_REFRESH],ecx
                    .ELSE
                      ; Unknown property, abort
                        mov     dword ptr ss:[esp+28],_UNKNOWN_OBJECT_EVENT
                        stc
                        jmp     quit
                    .ENDIF
                    add     esi,5
                .ENDIF
            .ENDIF
        .ENDW

      quit:
        popad
        ret
    invOBJECT_create_text_field     ENDP




    invOBJECT_create_hline      PROC
    ; This routine is called to create a horizontal line object
    ;
    ; Upon entry:   es:[ebx] - far ptr to base object to add to to
    ;               es:[edx] - last object in base-object's chain
    ;               es:[edi] - where object will be added
    ;               ds:[esi] - far ptr to object source
    ;
    ; Upon exit:    The object is created if it contains valid information
    ;
        pushad
      ; Headers unique to _HLINE items
        mov     byte ptr es:[edi+_OBJECT_TYPE],_HLINE
      ; Required headers
        mov     ebx,dword ptr ds:[esi+_O_LHL_TOP]
        mov     dword ptr es:[edi+_O_HL_TOP],ebx
        mov     ebx,dword ptr ds:[esi+_O_LHL_LEFT]
        mov     dword ptr es:[edi+_O_HL_LEFT],ebx
        mov     ebx,dword ptr ds:[esi+_O_LHL_WIDTH]
        mov     dword ptr es:[edi+_O_HL_WIDTH],ebx

      ; Default initialization
        mov     eax,-1
        xor     ecx,ecx
        mov     byte ptr es:[edi+_O_HL_ENABLED],1
        mov     byte ptr es:[edi+_O_HL_VISIBLE],cl
        mov     byte ptr es:[edi+_O_HL_BACKGROUND+_OBJECT_RED],cl
        mov     byte ptr es:[edi+_O_HL_BACKGROUND+_OBJECT_GREEN],cl
        mov     byte ptr es:[edi+_O_HL_BACKGROUND+_OBJECT_BLUE],cl
        mov     dword ptr es:[edi+_O_HL_MISC_1],eax
        mov     dword ptr es:[edi+_O_HL_MISC_2],eax
        mov     dword ptr es:[edi+_O_HL_MISC_3],eax
        mov     dword ptr es:[edi+_O_HL_MISC_4],eax
        mov     byte ptr es:[edi+_O_HL_MISC_FLAG_1],al
        mov     byte ptr es:[edi+_O_HL_MISC_FLAG_2],al
        mov     byte ptr es:[edi+_O_HL_MISC_FLAG_3],al
        add     edi,_O_HL_ACTIVATE
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_ACTIVATE],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_CLICK_BOTH_SINGLE],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_CLICK_BOTH_DOUBLE],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_CLICK_LEFT_SINGLE],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_CLICK_LEFT_DOUBLE],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_CLICK_LEFT_DOWN],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_CLICK_LEFT_UP],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_CLICK_RIGHT_SINGLE],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_CLICK_RIGHT_DOUBLE],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_CLICK_RIGHT_DOWN],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_CLICK_RIGHT_UP],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_DROPPED_INTO_LEFT],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_DROPPED_INTO_RIGHT],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_DRAG_LEFT_START],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_DRAG_LEFT_STOP],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_DRAG_RIGHT_START],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_DRAG_RIGHT_STOP],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_FOCUS_GOT],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_FOCUS_LOST],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_FOCUS_SET],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_HOVER],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_KEYSTROKE],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_WHEN_CREATED],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_WHEN_DESTROYED],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_REQUESTOR],eax
        mov     dword ptr es:[edi-_O_HL_ACTIVATE+_O_HL_REFRESH],eax
        sub     edi,_O_HL_ACTIVATE
        add     esi,_O_LHL_LENGTH

      ; Right now, ds:[esi] is sitting on any properties that are initialized to "other-than-default" values
        mov     bl,_PROPERTY_START
        .WHILE (byte ptr ds:[esi] != _OBJECT_END)
            mov     al,byte ptr ds:[esi]
            .IF (al == _PROPERTY_START || al == _EVENT_START)
                mov     bl,al
            .ELSE
                .IF (bl == _PROPERTY_START)
                  ; They're setting a property, which one?
                    .IF (al == _RP_ENABLED)
                        mov     al,byte ptr ds:[esi+_O_LHL_ENABLED]
                        mov     byte ptr es:[edi+_O_HL_ENABLED],al
                        add     esi,_O_LHL_ENABLED_SIZE
                    .ELSEIF (al == _RP_VISIBLE)
                        mov     al,byte ptr ds:[esi+_O_LHL_VISIBLE]
                        mov     byte ptr es:[edi+_O_HL_VISIBLE],al
                        add     esi,_O_LHL_VISIBLE_SIZE
                    .ELSEIF (al == _RP_BACKGROUND)
                        mov     al,byte ptr ds:[esi+_O_LHL_BACKGROUND_RED]
                        mov     byte ptr es:[edi+_O_HL_BACKGROUND+_OBJECT_RED],al
                        mov     al,byte ptr ds:[esi+_O_LHL_BACKGROUND_GREEN]
                        mov     byte ptr es:[edi+_O_HL_BACKGROUND+_OBJECT_GREEN],al
                        mov     al,byte ptr ds:[esi+_O_LHL_BACKGROUND_BLUE]
                        mov     byte ptr es:[edi+_O_HL_BACKGROUND+_OBJECT_BLUE],al
                        add     esi,_O_LHL_BACKGROUND_SIZE
                    .ELSEIF (al == _RP_MISC_1)
                        mov     eax,dword ptr ds:[esi+_O_LHL_MISC_1]
                        mov     dword ptr es:[edi+_O_HL_MISC_1],eax
                        add     esi,_O_LHL_MISC_1_SIZE
                    .ELSEIF (al == _RP_MISC_2)
                        mov     eax,dword ptr ds:[esi+_O_LHL_MISC_2]
                        mov     dword ptr es:[edi+_O_HL_MISC_2],eax
                        add     esi,_O_LHL_MISC_2_SIZE
                    .ELSEIF (al == _RP_MISC_3)
                        mov     eax,dword ptr ds:[esi+_O_LHL_MISC_3]
                        mov     dword ptr es:[edi+_O_HL_MISC_3],eax
                        add     esi,_O_LHL_MISC_3_SIZE
                    .ELSEIF (al == _RP_MISC_4)
                        mov     eax,dword ptr ds:[esi+_O_LHL_MISC_4]
                        mov     dword ptr es:[edi+_O_HL_MISC_4],eax
                        add     esi,_O_LHL_MISC_4_SIZE
                    .ELSEIF (al == _RP_MISC_FLAG_1)
                        mov     al,byte ptr ds:[esi+_O_LHL_MISC_FLAG_1]
                        mov     byte ptr es:[edi+_O_HL_MISC_FLAG_1],al
                        add     esi,_O_LHL_MISC_FLAG_1_SIZE
                    .ELSEIF (al == _RP_MISC_FLAG_2)
                        mov     al,byte ptr ds:[esi+_O_LHL_MISC_FLAG_2]
                        mov     byte ptr es:[edi+_O_HL_MISC_FLAG_2],al
                        add     esi,_O_LHL_MISC_FLAG_2_SIZE
                    .ELSEIF (al == _RP_MISC_FLAG_3)
                        mov     al,byte ptr ds:[esi+_O_LHL_MISC_FLAG_3]
                        mov     byte ptr es:[edi+_O_HL_MISC_FLAG_3],al
                        add     esi,_O_LHL_MISC_FLAG_3_SIZE
                    .ELSE
                      ; Unknown property, abort
                        mov     dword ptr ss:[esp+28],_UNKNOWN_OBJECT_PROPERTY
                        stc
                        jmp     quit
                    .ENDIF
                .ELSE
                  ; They're setting an event, which one?
                    mov     ecx,dword ptr ds:[esi+1]
                    .IF     (al == _RE_ACTIVATE)
                        mov     dword ptr es:[edx+_O_HL_ACTIVATE],ecx
                    .ELSEIF (al == _RE_CLICK_BOTH_SINGLE)
                        mov     dword ptr es:[edx+_O_HL_CLICK_BOTH_SINGLE],ecx
                    .ELSEIF (al == _RE_CLICK_BOTH_DOUBLE)
                        mov     dword ptr es:[edx+_O_HL_CLICK_BOTH_DOUBLE],ecx
                    .ELSEIF (al == _RE_CLICK_LEFT_SINGLE)
                        mov     dword ptr es:[edx+_O_HL_CLICK_LEFT_SINGLE],ecx
                    .ELSEIF (al == _RE_CLICK_LEFT_DOUBLE)
                        mov     dword ptr es:[edx+_O_HL_CLICK_LEFT_DOUBLE],ecx
                    .ELSEIF (al == _RE_CLICK_LEFT_DOWN)
                        mov     dword ptr es:[edx+_O_HL_CLICK_LEFT_DOWN],ecx
                    .ELSEIF (al == _RE_CLICK_LEFT_UP)
                        mov     dword ptr es:[edx+_O_HL_CLICK_LEFT_UP],ecx
                    .ELSEIF (al == _RE_CLICK_RIGHT_SINGLE)
                        mov     dword ptr es:[edx+_O_HL_CLICK_RIGHT_SINGLE],ecx
                    .ELSEIF (al == _RE_CLICK_RIGHT_DOUBLE)
                        mov     dword ptr es:[edx+_O_HL_CLICK_RIGHT_DOUBLE],ecx
                    .ELSEIF (al == _RE_CLICK_RIGHT_DOWN)
                        mov     dword ptr es:[edx+_O_HL_CLICK_RIGHT_DOWN],ecx
                    .ELSEIF (al == _RE_CLICK_RIGHT_UP)
                        mov     dword ptr es:[edx+_O_HL_CLICK_RIGHT_UP],ecx
                    .ELSEIF (al == _RE_DROPPED_INTO_LEFT)
                        mov     dword ptr es:[edx+_O_HL_DROPPED_INTO_LEFT],ecx
                    .ELSEIF (al == _RE_DROPPED_INTO_RIGHT)
                        mov     dword ptr es:[edx+_O_HL_DROPPED_INTO_RIGHT],ecx
                    .ELSEIF (al == _RE_DRAG_LEFT_START)
                        mov     dword ptr es:[edx+_O_HL_DRAG_LEFT_START],ecx
                    .ELSEIF (al == _RE_DRAG_LEFT_STOP)
                        mov     dword ptr es:[edx+_O_HL_DRAG_LEFT_STOP],ecx
                    .ELSEIF (al == _RE_DRAG_RIGHT_START)
                        mov     dword ptr es:[edx+_O_HL_DRAG_RIGHT_START],ecx
                    .ELSEIF (al == _RE_DRAG_RIGHT_STOP)
                        mov     dword ptr es:[edx+_O_HL_DRAG_RIGHT_STOP],ecx
                    .ELSEIF (al == _RE_FOCUS_GOT)
                        mov     dword ptr es:[edx+_O_HL_FOCUS_GOT],ecx
                    .ELSEIF (al == _RE_FOCUS_LOST)
                        mov     dword ptr es:[edx+_O_HL_FOCUS_LOST],ecx
                    .ELSEIF (al == _RE_FOCUS_SET)
                        mov     dword ptr es:[edx+_O_HL_FOCUS_SET],ecx
                    .ELSEIF (al == _RE_HOVER)
                        mov     dword ptr es:[edx+_O_HL_HOVER],ecx
                    .ELSEIF (al == _RE_KEYSTROKE)
                        mov     dword ptr es:[edx+_O_HL_KEYSTROKE],ecx
                    .ELSEIF (al == _RE_WHEN_CREATED)
                        mov     dword ptr es:[edx+_O_HL_WHEN_CREATED],ecx
                    .ELSEIF (al == _RE_WHEN_DESTROYED)
                        mov     dword ptr es:[edx+_O_HL_WHEN_DESTROYED],ecx
                    .ELSEIF (al == _RE_REQUESTOR)
                        mov     dword ptr es:[edx+_O_HL_REQUESTOR],ecx
                    .ELSEIF (al == _RE_REFRESH)
                        mov     dword ptr es:[edx+_O_HL_REFRESH],ecx
                    .ELSE
                      ; Unknown property, abort
                        mov     dword ptr ss:[esp+28],_UNKNOWN_OBJECT_EVENT
                        stc
                        jmp     quit
                    .ENDIF
                    add     esi,5
                .ENDIF
            .ENDIF
        .ENDW

      quit:
        popad
        ret
    invOBJECT_create_hline      ENDP




    invOBJECT_create_rectangle      PROC
    ; This routine is called to create a rectangle
    ;
    ; Upon entry:   es:[ebx] - far ptr to base object to add to to
    ;               es:[edx] - last object in base-object's chain
    ;               es:[edi] - where object will be added
    ;               ds:[esi] - far ptr to object source
    ;
    ; Upon exit:    The object is created if it contains valid information
    ;
        pushad
      ; Headers unique to _RECTANGLE items
        mov     byte ptr es:[edi+_OBJECT_TYPE],_RECTANGLE
      ; Required headers
        mov     ebx,dword ptr ds:[esi+_O_LR_TOP]
        mov     dword ptr es:[edi+_O_R_TOP],ebx
        mov     ebx,dword ptr ds:[esi+_O_LR_LEFT]
        mov     dword ptr es:[edi+_O_R_LEFT],ebx
        mov     ebx,dword ptr ds:[esi+_O_LR_WIDTH]
        mov     dword ptr es:[edi+_O_R_WIDTH],ebx
        mov     ebx,dword ptr ds:[esi+_O_LR_HEIGHT]
        mov     dword ptr es:[edi+_O_R_HEIGHT],ebx

      ; Default initialization
        mov     eax,-1
        xor     ecx,ecx
        mov     byte ptr es:[edi+_O_R_ENABLED],1
        mov     byte ptr es:[edi+_O_R_VISIBLE],cl
        mov     byte ptr es:[edi+_O_R_BACKGROUND+_OBJECT_RED],cl
        mov     byte ptr es:[edi+_O_R_BACKGROUND+_OBJECT_GREEN],cl
        mov     byte ptr es:[edi+_O_R_BACKGROUND+_OBJECT_BLUE],cl
        mov     dword ptr es:[edi+_O_R_MISC_1],eax
        mov     dword ptr es:[edi+_O_R_MISC_2],eax
        mov     dword ptr es:[edi+_O_R_MISC_3],eax
        mov     dword ptr es:[edi+_O_R_MISC_4],eax
        mov     byte ptr es:[edi+_O_R_MISC_FLAG_1],al
        mov     byte ptr es:[edi+_O_R_MISC_FLAG_2],al
        mov     byte ptr es:[edi+_O_R_MISC_FLAG_3],al
        add     edi,_O_R_ACTIVATE
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_ACTIVATE],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_CLICK_BOTH_SINGLE],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_CLICK_BOTH_DOUBLE],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_CLICK_LEFT_SINGLE],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_CLICK_LEFT_DOUBLE],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_CLICK_LEFT_DOWN],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_CLICK_LEFT_UP],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_CLICK_RIGHT_SINGLE],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_CLICK_RIGHT_DOUBLE],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_CLICK_RIGHT_DOWN],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_CLICK_RIGHT_UP],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_DROPPED_INTO_LEFT],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_DROPPED_INTO_RIGHT],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_DRAG_LEFT_START],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_DRAG_LEFT_STOP],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_DRAG_RIGHT_START],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_DRAG_RIGHT_STOP],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_FOCUS_GOT],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_FOCUS_LOST],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_FOCUS_SET],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_HOVER],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_KEYSTROKE],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_WHEN_CREATED],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_WHEN_DESTROYED],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_REQUESTOR],eax
        mov     dword ptr es:[edi-_O_R_ACTIVATE+_O_R_REFRESH],eax
        sub     edi,_O_R_ACTIVATE
        add     esi,_O_LR_LENGTH

      ; Right now, ds:[esi] is sitting on any properties that are initialized to "other-than-default" values
        mov     bl,_PROPERTY_START
        .WHILE (byte ptr ds:[esi] != _OBJECT_END)
            mov     al,byte ptr ds:[esi]
            .IF (al == _PROPERTY_START || al == _EVENT_START)
                mov     bl,al
            .ELSE
                .IF (bl == _PROPERTY_START)
                  ; They're setting a property, which one?
                    .IF (al == _RP_ENABLED)
                        mov     al,byte ptr ds:[esi+_O_LR_ENABLED]
                        mov     byte ptr es:[edi+_O_R_ENABLED],al
                        add     esi,_O_LR_ENABLED_SIZE
                    .ELSEIF (al == _RP_VISIBLE)
                        mov     al,byte ptr ds:[esi+_O_LR_VISIBLE]
                        mov     byte ptr es:[edi+_O_R_VISIBLE],al
                        add     esi,_O_LR_VISIBLE_SIZE
                    .ELSEIF (al == _RP_BACKGROUND)
                        mov     al,byte ptr ds:[esi+_O_LR_BACKGROUND_RED]
                        mov     byte ptr es:[edi+_O_R_BACKGROUND+_OBJECT_RED],al
                        mov     al,byte ptr ds:[esi+_O_LR_BACKGROUND_GREEN]
                        mov     byte ptr es:[edi+_O_R_BACKGROUND+_OBJECT_GREEN],al
                        mov     al,byte ptr ds:[esi+_O_LR_BACKGROUND_BLUE]
                        mov     byte ptr es:[edi+_O_R_BACKGROUND+_OBJECT_BLUE],al
                        add     esi,_O_LR_BACKGROUND_SIZE
                    .ELSEIF (al == _RP_MISC_1)
                        mov     eax,dword ptr ds:[esi+_O_LR_MISC_1]
                        mov     dword ptr es:[edi+_O_R_MISC_1],eax
                        add     esi,_O_LR_MISC_1_SIZE
                    .ELSEIF (al == _RP_MISC_2)
                        mov     eax,dword ptr ds:[esi+_O_LR_MISC_2]
                        mov     dword ptr es:[edi+_O_R_MISC_2],eax
                        add     esi,_O_LR_MISC_2_SIZE
                    .ELSEIF (al == _RP_MISC_3)
                        mov     eax,dword ptr ds:[esi+_O_LR_MISC_3]
                        mov     dword ptr es:[edi+_O_R_MISC_3],eax
                        add     esi,_O_LR_MISC_3_SIZE
                    .ELSEIF (al == _RP_MISC_4)
                        mov     eax,dword ptr ds:[esi+_O_LR_MISC_4]
                        mov     dword ptr es:[edi+_O_R_MISC_4],eax
                        add     esi,_O_LR_MISC_4_SIZE
                    .ELSEIF (al == _RP_MISC_FLAG_1)
                        mov     al,byte ptr ds:[esi+_O_LR_MISC_FLAG_1]
                        mov     byte ptr es:[edi+_O_R_MISC_FLAG_1],al
                        add     esi,_O_LR_MISC_FLAG_1_SIZE
                    .ELSEIF (al == _RP_MISC_FLAG_2)
                        mov     al,byte ptr ds:[esi+_O_LR_MISC_FLAG_2]
                        mov     byte ptr es:[edi+_O_R_MISC_FLAG_2],al
                        add     esi,_O_LR_MISC_FLAG_2_SIZE
                    .ELSEIF (al == _RP_MISC_FLAG_3)
                        mov     al,byte ptr ds:[esi+_O_LR_MISC_FLAG_3]
                        mov     byte ptr es:[edi+_O_R_MISC_FLAG_3],al
                        add     esi,_O_LR_MISC_FLAG_3_SIZE
                    .ELSE
                      ; Unknown property, abort
                        mov     dword ptr ss:[esp+28],_UNKNOWN_OBJECT_PROPERTY
                        stc
                        jmp     quit
                    .ENDIF
                .ELSE
                  ; They're setting an event, which one?
                    mov     ecx,dword ptr ds:[esi+1]
                    .IF     (al == _RE_ACTIVATE)
                        mov     dword ptr es:[edx+_O_R_ACTIVATE],ecx
                    .ELSEIF (al == _RE_CLICK_BOTH_SINGLE)
                        mov     dword ptr es:[edx+_O_R_CLICK_BOTH_SINGLE],ecx
                    .ELSEIF (al == _RE_CLICK_BOTH_DOUBLE)
                        mov     dword ptr es:[edx+_O_R_CLICK_BOTH_DOUBLE],ecx
                    .ELSEIF (al == _RE_CLICK_LEFT_SINGLE)
                        mov     dword ptr es:[edx+_O_R_CLICK_LEFT_SINGLE],ecx
                    .ELSEIF (al == _RE_CLICK_LEFT_DOUBLE)
                        mov     dword ptr es:[edx+_O_R_CLICK_LEFT_DOUBLE],ecx
                    .ELSEIF (al == _RE_CLICK_LEFT_DOWN)
                        mov     dword ptr es:[edx+_O_R_CLICK_LEFT_DOWN],ecx
                    .ELSEIF (al == _RE_CLICK_LEFT_UP)
                        mov     dword ptr es:[edx+_O_R_CLICK_LEFT_UP],ecx
                    .ELSEIF (al == _RE_CLICK_RIGHT_SINGLE)
                        mov     dword ptr es:[edx+_O_R_CLICK_RIGHT_SINGLE],ecx
                    .ELSEIF (al == _RE_CLICK_RIGHT_DOUBLE)
                        mov     dword ptr es:[edx+_O_R_CLICK_RIGHT_DOUBLE],ecx
                    .ELSEIF (al == _RE_CLICK_RIGHT_DOWN)
                        mov     dword ptr es:[edx+_O_R_CLICK_RIGHT_DOWN],ecx
                    .ELSEIF (al == _RE_CLICK_RIGHT_UP)
                        mov     dword ptr es:[edx+_O_R_CLICK_RIGHT_UP],ecx
                    .ELSEIF (al == _RE_DROPPED_INTO_LEFT)
                        mov     dword ptr es:[edx+_O_R_DROPPED_INTO_LEFT],ecx
                    .ELSEIF (al == _RE_DROPPED_INTO_RIGHT)
                        mov     dword ptr es:[edx+_O_R_DROPPED_INTO_RIGHT],ecx
                    .ELSEIF (al == _RE_DRAG_LEFT_START)
                        mov     dword ptr es:[edx+_O_R_DRAG_LEFT_START],ecx
                    .ELSEIF (al == _RE_DRAG_LEFT_STOP)
                        mov     dword ptr es:[edx+_O_R_DRAG_LEFT_STOP],ecx
                    .ELSEIF (al == _RE_DRAG_RIGHT_START)
                        mov     dword ptr es:[edx+_O_R_DRAG_RIGHT_START],ecx
                    .ELSEIF (al == _RE_DRAG_RIGHT_STOP)
                        mov     dword ptr es:[edx+_O_R_DRAG_RIGHT_STOP],ecx
                    .ELSEIF (al == _RE_FOCUS_GOT)
                        mov     dword ptr es:[edx+_O_R_FOCUS_GOT],ecx
                    .ELSEIF (al == _RE_FOCUS_LOST)
                        mov     dword ptr es:[edx+_O_R_FOCUS_LOST],ecx
                    .ELSEIF (al == _RE_FOCUS_SET)
                        mov     dword ptr es:[edx+_O_R_FOCUS_SET],ecx
                    .ELSEIF (al == _RE_HOVER)
                        mov     dword ptr es:[edx+_O_R_HOVER],ecx
                    .ELSEIF (al == _RE_KEYSTROKE)
                        mov     dword ptr es:[edx+_O_R_KEYSTROKE],ecx
                    .ELSEIF (al == _RE_WHEN_CREATED)
                        mov     dword ptr es:[edx+_O_R_WHEN_CREATED],ecx
                    .ELSEIF (al == _RE_WHEN_DESTROYED)
                        mov     dword ptr es:[edx+_O_R_WHEN_DESTROYED],ecx
                    .ELSEIF (al == _RE_REQUESTOR)
                        mov     dword ptr es:[edx+_O_R_REQUESTOR],ecx
                    .ELSEIF (al == _RE_REFRESH)
                        mov     dword ptr es:[edx+_O_R_REFRESH],ecx
                    .ELSE
                      ; Unknown property, abort
                        mov     dword ptr ss:[esp+28],_UNKNOWN_OBJECT_EVENT
                        stc
                        jmp     quit
                    .ENDIF
                    add     esi,5
                .ENDIF
            .ENDIF
        .ENDW

      quit:
        popad
        ret
    invOBJECT_create_rectangle      ENDP




    invOBJECT_create_border_box     PROC
    ; This routine is called to create a border box
    ;
    ; Upon entry:   es:[ebx] - far ptr to base object to add to to
    ;               es:[edx] - last object in base-object's chain
    ;               es:[edi] - where object will be added
    ;               ds:[esi] - far ptr to object source
    ;
    ; Upon exit:    The object is created if it contains valid information
    ;
        pushad
      ; Headers unique to _RECTANGLE items
        mov     byte ptr es:[edi+_OBJECT_TYPE],_BORDER_BOX
      ; Required headers
        mov     ebx,dword ptr ds:[esi+_O_LBB_TOP]
        mov     dword ptr es:[edi+_O_BB_TOP],ebx
        mov     ebx,dword ptr ds:[esi+_O_LBB_LEFT]
        mov     dword ptr es:[edi+_O_BB_LEFT],ebx
        mov     ebx,dword ptr ds:[esi+_O_LBB_WIDTH]
        mov     dword ptr es:[edi+_O_BB_WIDTH],ebx
        mov     ebx,dword ptr ds:[esi+_O_LBB_HEIGHT]
        mov     dword ptr es:[edi+_O_BB_HEIGHT],ebx

      ; Default initialization
        mov     eax,-1
        xor     ecx,ecx
        mov     byte ptr es:[edi+_O_BB_ENABLED],1
        mov     byte ptr es:[edi+_O_BB_VISIBLE],cl
        mov     byte ptr es:[edi+_O_BB_BACKGROUND+_OBJECT_RED],cl
        mov     byte ptr es:[edi+_O_BB_BACKGROUND+_OBJECT_GREEN],cl
        mov     byte ptr es:[edi+_O_BB_BACKGROUND+_OBJECT_BLUE],cl
        mov     byte ptr es:[edi+_O_BB_LIGHT_BORDER+_OBJECT_RED],cl
        mov     byte ptr es:[edi+_O_BB_LIGHT_BORDER+_OBJECT_GREEN],cl
        mov     byte ptr es:[edi+_O_BB_LIGHT_BORDER+_OBJECT_BLUE],cl
        mov     byte ptr es:[edi+_O_BB_SHADOW_BORDER+_OBJECT_RED],cl
        mov     byte ptr es:[edi+_O_BB_SHADOW_BORDER+_OBJECT_GREEN],cl
        mov     byte ptr es:[edi+_O_BB_SHADOW_BORDER+_OBJECT_BLUE],cl
        mov     dword ptr es:[edi+_O_BB_MISC_1],eax
        mov     dword ptr es:[edi+_O_BB_MISC_2],eax
        mov     dword ptr es:[edi+_O_BB_MISC_3],eax
        mov     dword ptr es:[edi+_O_BB_MISC_4],eax
        mov     byte ptr es:[edi+_O_BB_MISC_FLAG_1],al
        mov     byte ptr es:[edi+_O_BB_MISC_FLAG_2],al
        mov     byte ptr es:[edi+_O_BB_MISC_FLAG_3],al
        add     edi,_O_BB_ACTIVATE
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_ACTIVATE],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_CLICK_BOTH_SINGLE],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_CLICK_BOTH_DOUBLE],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_CLICK_LEFT_SINGLE],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_CLICK_LEFT_DOUBLE],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_CLICK_LEFT_DOWN],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_CLICK_LEFT_UP],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_CLICK_RIGHT_SINGLE],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_CLICK_RIGHT_DOUBLE],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_CLICK_RIGHT_DOWN],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_CLICK_RIGHT_UP],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_DROPPED_INTO_LEFT],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_DROPPED_INTO_RIGHT],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_DRAG_LEFT_START],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_DRAG_LEFT_STOP],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_DRAG_RIGHT_START],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_DRAG_RIGHT_STOP],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_FOCUS_GOT],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_FOCUS_LOST],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_FOCUS_SET],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_HOVER],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_KEYSTROKE],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_WHEN_CREATED],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_WHEN_DESTROYED],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_REQUESTOR],eax
        mov     dword ptr es:[edi-_O_BB_ACTIVATE+_O_BB_REFRESH],eax
        sub     edi,_O_BB_ACTIVATE
        add     esi,_O_LBB_LENGTH

      ; Right now, ds:[esi] is sitting on any properties that are initialized to "other-than-default" values
        mov     bl,_PROPERTY_START
        .WHILE (byte ptr ds:[esi] != _OBJECT_END)
            mov     al,byte ptr ds:[esi]
            .IF (al == _PROPERTY_START || al == _EVENT_START)
                mov     bl,al
            .ELSE
                .IF (bl == _PROPERTY_START)
                  ; They're setting a property, which one?
                    .IF (al == _BBP_ENABLED)
                        mov     al,byte ptr ds:[esi+_O_LBB_ENABLED]
                        mov     byte ptr es:[edi+_O_BB_ENABLED],al
                        add     esi,_O_LBB_ENABLED_SIZE
                    .ELSEIF (al == _BBP_VISIBLE)
                        mov     al,byte ptr ds:[esi+_O_LBB_VISIBLE]
                        mov     byte ptr es:[edi+_O_BB_VISIBLE],al
                        add     esi,_O_LBB_VISIBLE_SIZE
                    .ELSEIF (al == _BBP_BACKGROUND)
                        mov     al,byte ptr ds:[esi+_O_LBB_BACKGROUND_RED]
                        mov     byte ptr es:[edi+_O_BB_BACKGROUND+_OBJECT_RED],al
                        mov     al,byte ptr ds:[esi+_O_LBB_BACKGROUND_GREEN]
                        mov     byte ptr es:[edi+_O_BB_BACKGROUND+_OBJECT_GREEN],al
                        mov     al,byte ptr ds:[esi+_O_LBB_BACKGROUND_BLUE]
                        mov     byte ptr es:[edi+_O_BB_BACKGROUND+_OBJECT_BLUE],al
                        add     esi,_O_LBB_BACKGROUND_SIZE
                    .ELSEIF (al == _BBP_LIGHT_BORDER)
                        mov     al,byte ptr ds:[esi+_O_LBB_LIGHT_BORDER_RED]
                        mov     byte ptr es:[edi+_O_BB_LIGHT_BORDER+_OBJECT_RED],al
                        mov     al,byte ptr ds:[esi+_O_LBB_LIGHT_BORDER_GREEN]
                        mov     byte ptr es:[edi+_O_BB_LIGHT_BORDER+_OBJECT_GREEN],al
                        mov     al,byte ptr ds:[esi+_O_LBB_LIGHT_BORDER_BLUE]
                        mov     byte ptr es:[edi+_O_BB_LIGHT_BORDER+_OBJECT_BLUE],al
                        add     esi,_O_LBB_LIGHT_BORDER_SIZE
                    .ELSEIF (al == _BBP_SHADOW_BORDER)
                        mov     al,byte ptr ds:[esi+_O_LBB_SHADOW_BORDER_RED]
                        mov     byte ptr es:[edi+_O_BB_SHADOW_BORDER+_OBJECT_RED],al
                        mov     al,byte ptr ds:[esi+_O_LBB_SHADOW_BORDER_GREEN]
                        mov     byte ptr es:[edi+_O_BB_SHADOW_BORDER+_OBJECT_GREEN],al
                        mov     al,byte ptr ds:[esi+_O_LBB_SHADOW_BORDER_BLUE]
                        mov     byte ptr es:[edi+_O_BB_SHADOW_BORDER+_OBJECT_BLUE],al
                        add     esi,_O_LBB_SHADOW_BORDER_SIZE
                    .ELSEIF (al == _BBP_MISC_1)
                        mov     eax,dword ptr ds:[esi+_O_LBB_MISC_1]
                        mov     dword ptr es:[edi+_O_BB_MISC_1],eax
                        add     esi,_O_LBB_MISC_1_SIZE
                    .ELSEIF (al == _BBP_MISC_2)
                        mov     eax,dword ptr ds:[esi+_O_LBB_MISC_2]
                        mov     dword ptr es:[edi+_O_BB_MISC_2],eax
                        add     esi,_O_LBB_MISC_2_SIZE
                    .ELSEIF (al == _BBP_MISC_3)
                        mov     eax,dword ptr ds:[esi+_O_LBB_MISC_3]
                        mov     dword ptr es:[edi+_O_BB_MISC_3],eax
                        add     esi,_O_LBB_MISC_3_SIZE
                    .ELSEIF (al == _BBP_MISC_4)
                        mov     eax,dword ptr ds:[esi+_O_LBB_MISC_4]
                        mov     dword ptr es:[edi+_O_BB_MISC_4],eax
                        add     esi,_O_LBB_MISC_4_SIZE
                    .ELSEIF (al == _BBP_MISC_FLAG_1)
                        mov     al,byte ptr ds:[esi+_O_LBB_MISC_FLAG_1]
                        mov     byte ptr es:[edi+_O_BB_MISC_FLAG_1],al
                        add     esi,_O_LBB_MISC_FLAG_1_SIZE
                    .ELSEIF (al == _BBP_MISC_FLAG_2)
                        mov     al,byte ptr ds:[esi+_O_LBB_MISC_FLAG_2]
                        mov     byte ptr es:[edi+_O_BB_MISC_FLAG_2],al
                        add     esi,_O_LBB_MISC_FLAG_2_SIZE
                    .ELSEIF (al == _BBP_MISC_FLAG_3)
                        mov     al,byte ptr ds:[esi+_O_LBB_MISC_FLAG_3]
                        mov     byte ptr es:[edi+_O_BB_MISC_FLAG_3],al
                        add     esi,_O_LBB_MISC_FLAG_3_SIZE
                    .ELSE
                      ; Unknown property, abort
                        mov     dword ptr ss:[esp+28],_UNKNOWN_OBJECT_PROPERTY
                        stc
                        jmp     quit
                    .ENDIF
                .ELSE
                  ; They're setting an event, which one?
                    mov     ecx,dword ptr ds:[esi+1]
                    .IF     (al == _BBE_ACTIVATE)
                        mov     dword ptr es:[edx+_O_BB_ACTIVATE],ecx
                    .ELSEIF (al == _BBE_CLICK_BOTH_SINGLE)
                        mov     dword ptr es:[edx+_O_BB_CLICK_BOTH_SINGLE],ecx
                    .ELSEIF (al == _BBE_CLICK_BOTH_DOUBLE)
                        mov     dword ptr es:[edx+_O_BB_CLICK_BOTH_DOUBLE],ecx
                    .ELSEIF (al == _BBE_CLICK_LEFT_SINGLE)
                        mov     dword ptr es:[edx+_O_BB_CLICK_LEFT_SINGLE],ecx
                    .ELSEIF (al == _BBE_CLICK_LEFT_DOUBLE)
                        mov     dword ptr es:[edx+_O_BB_CLICK_LEFT_DOUBLE],ecx
                    .ELSEIF (al == _BBE_CLICK_LEFT_DOWN)
                        mov     dword ptr es:[edx+_O_BB_CLICK_LEFT_DOWN],ecx
                    .ELSEIF (al == _BBE_CLICK_LEFT_UP)
                        mov     dword ptr es:[edx+_O_BB_CLICK_LEFT_UP],ecx
                    .ELSEIF (al == _BBE_CLICK_RIGHT_SINGLE)
                        mov     dword ptr es:[edx+_O_BB_CLICK_RIGHT_SINGLE],ecx
                    .ELSEIF (al == _BBE_CLICK_RIGHT_DOUBLE)
                        mov     dword ptr es:[edx+_O_BB_CLICK_RIGHT_DOUBLE],ecx
                    .ELSEIF (al == _BBE_CLICK_RIGHT_DOWN)
                        mov     dword ptr es:[edx+_O_BB_CLICK_RIGHT_DOWN],ecx
                    .ELSEIF (al == _BBE_CLICK_RIGHT_UP)
                        mov     dword ptr es:[edx+_O_BB_CLICK_RIGHT_UP],ecx
                    .ELSEIF (al == _BBE_DROPPED_INTO_LEFT)
                        mov     dword ptr es:[edx+_O_BB_DROPPED_INTO_LEFT],ecx
                    .ELSEIF (al == _BBE_DROPPED_INTO_RIGHT)
                        mov     dword ptr es:[edx+_O_BB_DROPPED_INTO_RIGHT],ecx
                    .ELSEIF (al == _BBE_DRAG_LEFT_START)
                        mov     dword ptr es:[edx+_O_BB_DRAG_LEFT_START],ecx
                    .ELSEIF (al == _BBE_DRAG_LEFT_STOP)
                        mov     dword ptr es:[edx+_O_BB_DRAG_LEFT_STOP],ecx
                    .ELSEIF (al == _BBE_DRAG_RIGHT_START)
                        mov     dword ptr es:[edx+_O_BB_DRAG_RIGHT_START],ecx
                    .ELSEIF (al == _BBE_DRAG_RIGHT_STOP)
                        mov     dword ptr es:[edx+_O_BB_DRAG_RIGHT_STOP],ecx
                    .ELSEIF (al == _BBE_FOCUS_GOT)
                        mov     dword ptr es:[edx+_O_BB_FOCUS_GOT],ecx
                    .ELSEIF (al == _BBE_FOCUS_LOST)
                        mov     dword ptr es:[edx+_O_BB_FOCUS_LOST],ecx
                    .ELSEIF (al == _BBE_FOCUS_SET)
                        mov     dword ptr es:[edx+_O_BB_FOCUS_SET],ecx
                    .ELSEIF (al == _BBE_HOVER)
                        mov     dword ptr es:[edx+_O_BB_HOVER],ecx
                    .ELSEIF (al == _BBE_KEYSTROKE)
                        mov     dword ptr es:[edx+_O_BB_KEYSTROKE],ecx
                    .ELSEIF (al == _BBE_WHEN_CREATED)
                        mov     dword ptr es:[edx+_O_BB_WHEN_CREATED],ecx
                    .ELSEIF (al == _BBE_WHEN_DESTROYED)
                        mov     dword ptr es:[edx+_O_BB_WHEN_DESTROYED],ecx
                    .ELSEIF (al == _BBE_REQUESTOR)
                        mov     dword ptr es:[edx+_O_BB_REQUESTOR],ecx
                    .ELSEIF (al == _BBE_REFRESH)
                        mov     dword ptr es:[edx+_O_BB_REFRESH],ecx
                    .ELSE
                      ; Unknown property, abort
                        mov     dword ptr ss:[esp+28],_UNKNOWN_OBJECT_EVENT
                        stc
                        jmp     quit
                    .ENDIF
                    add     esi,5
                .ENDIF
            .ENDIF
        .ENDW

      quit:
        popad
        ret
    invOBJECT_create_border_box     ENDP