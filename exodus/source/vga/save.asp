;    invVID_g_queue_function_request     PROC
;    ; This routine is used to queue a function request to a VID_g algorithm.  This guarantees atomicity.
;    ;
;    ; Upon entry:   the stack is arranged as below
;    ;               es - VGA's data segment
;    ;
;    ; Upon exit:    The function was executed
;    ;
;      ; [ebp+24] - start of parameters
;      ; [ebp+20] - cs
;      ; [ebp+16] - eip
;      ; [ebp+12] - es
;      ; [ebp+08] - dword count, # of parameters
;      ; [ebp+04] - eip of local routine
;      ; [ebp+00] - ebp
;        enter   0,0
;        push    ebx
;        mov     ebx,dword ptr ss:[ebp+08]
;        .IF (ebx == offset VID_g_mono_cursor_offset)
;          ; It's a queue to the cursor algorithm
;          ; [ebp+28] - dword, horizontal
;          ; [ebp+24] - dword, vertical
;
;        .ELSEIF (ebx == offset VID_g_mono_window_function_offset)
;          ; It's a queue to the window algorithm
;          ; [ebp+42] - dword, ul-x
;          ; [ebp+40] - dword, ul-y
;          ; [ebp+36] - dword, lr-x
;          ; [ebp+32] - dword, lr-y
;          ; [ebp+28] - dword, request (0-put text, 1-get text, 2-clear, 3-calculate required buffer for action)
;          ; [ebp+24] - dword, offset to data location if [ebp+16] = 0 or 1
;
;        .ELSEIF (ebx == offset VID_g_mono_mouse_pointer)
;          ; It's a queue to the mouse pointer algorithm
;          ; [ebp+36] - dword, horizontal
;          ; [ebp+32] - dword, vertical
;          ; [ebp+28] - dword, display mode (0-hide, 1-show)
;          ; [ebp+24] - dword, offset to store/retrieve mouse pointer data from
;
;        .ELSEIF (ebx == offset VID_g_mono_display_text_mode)
;          ; It's a queue to the display text algorithm
;          ; [ebp+40] - param, dword, write operation (0-overlay, 1-or, 2-and, 3-xor)
;          ; [ebp+36] - param, dword, horizontal
;          ; [ebp+32] - param, dword, vertical
;          ; [ebp+28] - param, dword, display mode (0-normal, 1-reverse)
;          ; [ebp+24] - param, dword, offset to text to the display
;
;        .ENDIF
;        pop     ebx
;        leave
;        ret 4                                                       ; Get the count off the stack
;    invVID_g_queue_function_request     ENDP
;
;
;
;
;    invVID_g_execute_queued_functions       PROC
;    ; This routine is sued to execute a previously queued VID_g function
;    ;
;    ; Upon entry:   es - VGA's data segment
;    ;
;    ; Upon exit:    The function was executed
;    ;
;        ret
;    invVID_g_execute_queued_functions       ENDP