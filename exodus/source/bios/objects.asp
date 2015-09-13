; objects.asp
;
; Exodus BIOS Object Handler
;
;





    iOBJECT_initialize_object_space     PROC
    ; This routine is called to initialize the object space set aside by a task
    ;
    ; Upon entry:   eax - selector for object space
    ;
    ; Upon exit:    It's initialize
    ;
        push    ds

        mov     ds,eax
        mov     dword ptr dword ptr ds:[_OBJECT_HEADER_NEXT_OBJECT],_FIRST_OBJECT
        mov     dword ptr dword ptr ds:[_OBJECT_HEADER_FIRST_BASE_OBJECT],-1
        mov     dword ptr dword ptr ds:[_OBJECT_HEADER_FIRST_OBJECT],-1

        pop     ds
        retf
    iOBJECT_initialize_object_space     ENDP




    iOBJECT_locate_task_object      PROC
    ; This routine is called to locate a particular object within a given task
    ;
    ; Upon entry:   es:[edi] - far ptr to this task's objects
    ;                    ebx - base object handle to find
    ;
    ; Upon exit:    carry? - SET if not found, CLEAR if found
    ;                  ebx - offset to task's base object
    ;
        push    edx
        push    eax

        mov     edx,dword ptr es:[_OBJECT_HEADER_FIRST_BASE_OBJECT]
        xor     eax,eax
        .WHILE (edx != -1)
            .IF (eax == ebx)
              ; This is the one
                mov     ebx,edx
                clc
                jmp     quit
            .ENDIF
            mov     edx,dword ptr es:[edx+_OBJECT_NEXT_BASE_OBJECT]
            inc     eax
        .ENDW
      ; It wasn't found
        stc

      quit:
        pop     eax
        pop     edx
        retf
    iOBJECT_locate_task_object      ENDP




    INCLUDE create.asp                                              ; Create base objects and objects
    INCLUDE redraw.asp                                              ; Redraw algorithms for base objects and objects