; cfsca.asp
;
; Low-Level Debi Debugger CFSCA window handler
;
;


source_not_available    db  "®<Source not available>¯",0
cfsca_buffer1           db  128 dup(0)
cfsca_buffer2           db  128 dup(0)



invDEBI_cfsca_1_window      PROC
; This routine is called to populate the CFSCA.1 window
;
    mov     dword ptr ss:[ebp-12],13*FONT_Y
    jmp     invDEBI_cfsca_window_common
invDEBI_cfsca_1_window      ENDP



invDEBI_cfsca_2_window      PROC
; This routine is called to populate the CFSCA.2 window
;
    mov     dword ptr ss:[ebp-12],26*FONT_Y
    jmp     invDEBI_cfsca_window_common
invDEBI_cfsca_2_window      ENDP




invDEBI_cfsca_3_window      PROC
; This routine is called to populate the CFSCA.3 window
;
    mov     dword ptr ss:[ebp-12],39*FONT_Y
    ; Note, this next line is not executed because it will flow right into that algorithm
    ;jmp     invDEBI_cfsca_window_common
invDEBI_cfsca_3_window      ENDP




invDEBI_cfsca_window_common     PROC
; This routine is called to process the cfsca windows
;
; Upon entry:   ds:[esi] - far ptr to this object's screen table info
;               ds:[edi] - far ptr to this object's parameters
;                  [ebp] - pointer to stack frame from debi_debug()
;               [ebp-12] - dword indicating maximum line to reach
;
; Upon exit:    The window is updated with either source code or an assembly listing
;
  ; Refer to debi_debug() for these stack references
  ; [ebp+56] - cs
  ; [ebp+52] - eip
  ; [ebp-08] - dword, Current font increment
  ; [ebp-12] - dword, maximum line to reach
    push    ds
    push    es
    push    fs
    pushfd
    pushad

  ; Save esi use below (as edx)
    mov     edx,esi

  ; We need:  ds:[esi] - far ptr to execution code
  ;           es:[edi] - far ptr to text string
  ;                 fs - current data segment (used below for DEBI_simplify_disassembly)
  ;                ebx - used to indicate how far down the screen we are
    mov     es,cs:data_segment
    mov     fs,cs:data_segment
    mov     esi,dword ptr ss:[ebp+52]
    .IF (es:single_step_history != 0ffffffffh)
      ; They've been single stepping
        .IF (esi >= es:single_step_top && esi < es:single_step_end)
            mov     esi,es:single_step_top
        .ENDIF
    .ENDIF
    mov     es:single_step_history,0
    mov     es:single_step_top,esi

    mov     ebx,dword ptr ss:[ebp-08]                               ; Start at 8 pixels down in window
  ;-[loop]---
  @@:
        mov     ds,dword ptr ss:[ebp+56]
        mov     edi,offset cfsca_buffer1
        call    fword ptr es:_x86_disassemble
        push    ecx

      ; We need:  es:[edi] - far ptr to disassembly cask
      ;           fs:[ebx] - far ptr to simplified string
      ;                eax - number of spaces in string to use for displaying instruction bytes
      ;                ecx - maximum length of string
        push    ebx
        mov     eax,16
        mov     ecx,55                                              ; Actually 59-4 (-4 for the "CFSCA" vertical frames)
        mov     ebx,offset cfsca_buffer2
        call    fword ptr es:_x86_simplify_disassembly
        pop     ebx

        mov     ds,cs:data_segment
        pushfd
        .IF (esi == dword ptr ss:[ebp+52])
          ; It is the current instruction, we have to display it in reverse color
            mov     ecx,dword ptr ss:[esp+04]
            mov     ds:instruction_offset,esi
            mov     ds:instruction_length,ecx
          ; Draw the text
            push    dword ptr 0                                     ; Write mode (0-overlay)
            push    dword ptr ds:[edx+_ST_OBJECT_UL_HORIZONTAL]
            add     dword ptr ss:[esp+00],8*4                       ; Move over for the "CFSCA" vertical frames
            mov     ecx,dword ptr ss:[esp+00]
            mov     ds:cursor_x,ecx
            push    dword ptr ds:[edx+_ST_OBJECT_UL_VERTICAL]
            add     dword ptr ss:[esp+00],ebx                       ; Move down to whatever line we're currently on
            mov     ecx,dword ptr ss:[esp+00]
            mov     ds:cursor_y,ecx
            push    dword ptr 1                                     ; Display mode (1-reverse)
            push    dword ptr offset cfsca_buffer2
            cli
            call    fword ptr ds:_VID_g_mono_display_text_mode
        .ELSE
          ; It's not the current instruction
            push    dword ptr ds:[edx+_ST_OBJECT_UL_HORIZONTAL]
            add     dword ptr ss:[esp+00],8*4                       ; Move over for the "CFSCA" vertical frames
            push    dword ptr ds:[edx+_ST_OBJECT_UL_VERTICAL]
            add     dword ptr ss:[esp+00],ebx                       ; Move down to whatever line we're currently on
            push    dword ptr offset cfsca_buffer2
            cli
            call    fword ptr ds:_VID_g_mono_display_text
        .ENDIF
        popfd

      ; Move to the next instruction
        pop     ecx
        add     esi,ecx

    add     ebx,dword ptr ss:[ebp-08]
    cmp     ebx,dword ptr ss:[ebp-12]
    jb      @B
  ;-------
    mov     ds:single_step_end,esi

    popad
    popfd
    pop     fs
    pop     es
    pop     ds
    ret
invDEBI_cfsca_window_common     ENDP




invDEBI_cfsca_2_click       PROC
; This routine is called when they click on the cfsca.2 casq
    ret
invDEBI_cfsca_2_click       ENDP




invDEBI_cfsca_3_click       PROC
; This routine is called when they click on the cfsca.3 casq
    ret
invDEBI_cfsca_3_click       ENDP




invDEBI_cfsca_4_click       PROC
; This routine is called when they click on the cfsca.4 casq
    ret
invDEBI_cfsca_4_click       ENDP