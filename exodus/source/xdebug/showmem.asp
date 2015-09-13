; showmem.asp
;
; xDebug
; This routines updates the memory display windows
;

show_mem2:
;
; Upon entry:   Nothing
;
; Upon exit:  everything is preserved
;
    pushad
    push    DS
    push    ES

    mov     AX,CS
    mov     DS,AX

    ; Determine the segment
    xor     ecx,ecx
    xor     esi,esi
    mov     si,offset mem2_address + 2
    mov     al,mem2_seg
    call    get_register
    mov     di,((18 * 80) + 14) * 2
    mov     al,1
    call    show_register

    ; Determine the offset
    mov     si,offset mem2_address
    mov     al,mem2_offset
    call    get_register
    mov     al,2
    call    show_register

    ; Now, display the contents on screen
    lds     si,mem2_address
    mov     al,3
    call    show_register
    lfs     bx,last_mem2_addr
    mov     di,((19 * 80) + 13) * 2
    jmp     show_mem_get_ready

show_mem1:
    pushad
    push    DS
    push    ES

    mov     AX,CS
    mov     DS,AX

    ; Determine the segment
    xor     ecx,ecx
    xor     esi,esi
    mov     si,offset mem1_address + 2
    mov     al,mem1_seg
    call    get_register
    mov     di,((13 * 80) + 14) * 2
    mov     al,1
    call    show_register

    ; Determine the offset
    mov     si,offset mem1_address
    mov     al,mem1_offset
    call    get_register
    mov     al,2
    call    show_register

    ; Now, display the contents on screen
    lds     si,mem1_address
    mov     al,3
    call    show_register
    lfs     bx,last_mem1_addr
    mov     di,((14 * 80) + 13) * 2
  show_mem_get_ready:
    mov     ax,0b000h
    mov     es,ax
    mov     cx,4                                                    ; Display 4 lines
  show_mem_outer_loop:
    push    cx
    push    di
    mov     bp,di
    add     bp,33*2
        mov     cx,16                                               ; 16 characters per line
      show_mem_inner_loop:
        push    cx
        push    bx
        mov     bl,byte ptr fs:[bx]                                 ; Previous character
        mov     dl,byte ptr [si]                                    ; Current character
        call    show_register_8                                     ; Display it in hexidecimal
        mov     byte ptr es:[bp],dl                                 ; Display it in ASCII
        mov     byte ptr es:[bp+1],ah                               ; Store the color from show_register_8
        add     di,4                                                ; Move to the next hexidecimal location
        add     bp,2                                                ; Move to the next ASCII location
        inc     si                                                  ; Move to the next data byte
        pop     bx
        inc     bx
        pop     cx
        loop    show_mem_inner_loop
    pop     di
    add     di,80*2
    pop     cx
    loop    show_mem_outer_loop

    pop     ES
    pop     DS
    popad
    ret


get_register:
    xor     edx,edx
    mov     cx,2
    .IF (al == 0)
      ; cs
        mov     bx,current_sp
        mov     dx,word ptr SS:[bx+2]
        mov     bx,offset cs_register
    .ELSEIF (al == 1)
      ; ip
        mov     bx,current_sp
        mov     dx,word ptr SS:[bx+0]
        mov     bx,offset ip_register
    .ELSEIF (al == 2)
      ; bp
        mov     dx,current_bp
        mov     bx,offset bp_register
    .ELSEIF (al == 3)
      ; eax
        mov     edx,[bp-4]
        mov     bx,offset eax_register
        mov     cx,3
    .ELSEIF (al == 4)
      ; ebx
        mov     edx,[bp-8]
        mov     bx,offset ebx_register
        mov     cx,3
    .ELSEIF (al == 5)
      ; ecx
        mov     edx,[bp-12]
        mov     bx,offset ecx_register
        mov     cx,3
    .ELSEIF (al == 6)
      ; edx
        mov     edx,[bp-16]
        mov     bx,offset edx_register
        mov     cx,3
    .ELSEIF (al == 7)
      ; esi
        mov     edx,[bp-20]
        mov     bx,offset esi_register
        mov     cx,3
    .ELSEIF (al == 8)
      ; edi
        mov     edx,[bp-25]                                         ; 24
        mov     bx,offset edi_register
        mov     cx,3
    .ELSEIF (al == 9)
      ; sp
        mov     dx,current_sp
        mov     bx,offset sp_register
    .ELSEIF (al == 10)
      ; ds
        mov     dx,[bp-30]
        mov     bx,offset ds_register
    .ELSEIF (al == 11)
      ; es
        mov     dx,[bp-32]
        mov     bx,offset es_register
    .ELSEIF (al == 12)
      ; fs
        mov     dx,[bp-34]
        mov     bx,offset fs_register
    .ELSEIF (al == 13)
      ; gs
        mov     dx,[bp-36]
        mov     bx,offset gs_register
    .ELSEIF (al == 14)
      ; ss
        mov     dx,[bp-38]
        mov     bx,offset ss_register
    .ELSEIF (al == 15)
      ; flags
        mov     bx,current_sp
        mov     dx,word ptr SS:[bx+4]
        mov     bx,offset flags_register
        mov     cx,5
    .ELSEIF (al == 20)
      ; ax
        mov     dx,[bp-4]
        mov     bx,offset ax_register
    .ELSEIF (al == 21)
      ; bx
        mov     dx,[bp-8]
        mov     bx,offset bx_register
    .ELSEIF (al == 22)
      ; cx
        mov     dx,[bp-12]
        mov     bx,offset cx_register
    .ELSEIF (al == 23)
      ; dx
        mov     dx,[bp-16]
        mov     bx,offset dx_register
    .ELSEIF (al == 24)
      ; si
        mov     dx,[bp-20]
        mov     bx,offset si_register
    .ELSEIF (al == 25)
      ; di
        mov     dx,[bp-24]
        mov     bx,offset di_register
    .ELSEIF (al == 30)
      ; ah
        mov     dl,[bp-3]
        mov     bx,offset ah_register
    .ELSEIF (al == 31)
      ; bh
        mov     dl,[bp-7]
        mov     bx,offset bh_register
    .ELSEIF (al == 32)
      ; ch
        mov     dl,[bp-11]
        mov     bx,offset ch_register
    .ELSEIF (al == 33)
      ; dh
        mov     dl,[bp-15]
        mov     bx,offset dh_register
    .ELSEIF (al == 35)
      ; al
        mov     dl,[bp-4]
        mov     bx,offset al_register
    .ELSEIF (al == 36)
      ; bl
        mov     dl,[bp-8]
        mov     bx,offset bl_register
    .ELSEIF (al == 37)
      ; cl
        mov     dl,[bp-12]
        mov     bx,offset cl_register
    .ELSEIF (al == 38)
      ; dl
        mov     dl,[bp-16]
        mov     bx,offset dl_register
    .ELSE
      ; Unknown
        mov     dx,0ffffh
        mov     bx,offset zero_ffff
        mov     cx,6
    .ENDIF
    mov     word ptr [esi],dx
    ret


show_register:
    .IF (al == 1)
      ; They are displaying the left-part of the address, it is formatted like "ds:"
      ; But, before we do that we have to initialize the line
        push    di
        push    cx

        mov     cx,30                                               ; Clear off the line (replace it with ASCII-196)
        mov     al,"Ä"
      @@:
        stosb
        inc     di
        loop    @B

        pop     cx
        pop     di
        call    write_screen_ds_bx_to_es_di_for_cx_no_color

      ; Now, store the colon
        mov     al,":"
        stosb
        inc     di
    .ELSEIF (al == 2)
      ; They are displaying the right-part of the address, it is formatted like "[reg]"
        mov     al,"["
        stosb
        inc     di
        call    write_screen_ds_bx_to_es_di_for_cx_no_color
        mov     al,"]"
        stosb
        inc     di
    .ELSEIF (al == 3)
      ; They are displaying the actual values of the address
        pushad
        push    si                                                  ; Pushed as si
        mov     dx,ds                                               ; Show the segment
        add     di,2
        mov     al,"("
        stosb
        inc     di
        call    show_register_16_no_color
        add     di,4*2
        pop     dx                                                  ; Popped as dx, show the offset
        mov     al,":"
        stosb
        inc     di
        call    show_register_16_no_color
        add     di,4*2
        mov     al," "
        stosb
        inc     di
        mov     al,"="
        stosb
        inc     di
        mov     al," "
        stosb
        inc     di
        xor     edx,edx
        mov     dx,ds
        shl     edx,4
        add     edx,esi                                             ; Show the 20-bit address
        call    show_register_20_no_color
        add     di,5*2
        mov     al,")"
        stosb
        inc     di
        popad
    .ENDIF
    ret


write_screen_ds_bx_to_es_di_for_cx_no_color:
  @@:
    mov     al,[bx]
    stosb
    inc     di
    inc     bx
    loop    @B