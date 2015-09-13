; dma.asp
;
; Exodus Programmable Direct Memory Access (DMA) routines
;
;   iDMA_setup()
;


iDMA_setup      PROC
; This routine is used setup a DMA read-from-device
; Upon entry:  Parameters are expected on the stack
;  Upon exit:  carry? - SET if error, CLEAR if ok
;
  ; [esp+56] [ebp+28] DWORD, channel to use
  ; [esp+52] [ebp+24] DWORD, mode type
  ; [esp+48] [ebp+20] DWORD, memory read/write direction (0-up, 1-down)
  ; [esp+44] [ebp+16] DWORD, linear memory address to read/write
  ; [esp+42] [ebp+14] WORD,  type of operation
  ; [esp+40] [ebp+12] WORD,  bytes to transfer
  ; [esp+36] [ebp+08] DWORD, cs
  ; [esp+32] [ebp+04] DWORD, eip
  ; [esp+28] [ebp+00] DWORD, ebp
    enter   16,0
  ; [esp+26] [ebp-02] WORD,  DMA Base Current Count
  ; [esp+24] [ebp-04] WORD,  DMA Base Current Address
  ; [esp+22] [ebp-06] WORD,  DMA mode register
  ; [esp+20] [ebp-08] WORD,  DMA mask register
  ; [esp+18] [ebp-10] WORD,  DMA clear byte register
  ; [esp+17] [ebp-11] BYTE,  Mode byte
  ; [esp+16] [ebp-12] BYTE,  --Not used
  ; [esp+14] [esp-14] WORD,  DMA page register
  ; [esp+12] [esp-16] WORD,  --Not used
  ; [esp+08] [ebp-20] DWORD, edx
  ; [esp+04] [ebp-24] DWORD, eax
  ; [esp+00] [ebp-28] DWORD, ecx
int 3
    push    edx
    push    eax
    push    ecx

    cli

    mov     ecx,dword ptr ss:[ebp+28]
    .IF (ecx > 7 || dword ptr ss:[ebp+16] > 16*(1024*1000))         ; The page address must be in the lower 16MB
        stc
        jmp     iDMA_quit
    .ELSEIF (ecx <= 3)
      ; It's on DMA channel 1
        mov     word ptr ss:[ebp-06],_DMA1_port_mode_register
        mov     word ptr ss:[ebp-08],_DMA1_port_mask_register
        mov     word ptr ss:[ebp-10],_DMA1_port_clear_register
        mov     byte ptr ss:[ebp-11],cl
        .IF (ecx == 0)
          ; Channel 0, DMA1
            mov     word ptr ss:[ebp-02],_DMA1_port_bca_channel_0
            mov     word ptr ss:[ebp-04],_DMA1_port_bcc_channel_0
            mov     word ptr ss:[ebp-14],_DMA1_port_pr_channel_0
        .ELSEIF (ecx == 1)
          ; Channel 1, DMA1
            mov     word ptr ss:[ebp-02],_DMA1_port_bca_channel_1
            mov     word ptr ss:[ebp-04],_DMA1_port_bcc_channel_1
            mov     word ptr ss:[ebp-14],_DMA1_port_pr_channel_1
        .ELSEIF (ecx == 2)
          ; Channel 2, DMA1
            mov     word ptr ss:[ebp-02],_DMA1_port_bca_channel_2
            mov     word ptr ss:[ebp-04],_DMA1_port_bcc_channel_2
            mov     word ptr ss:[ebp-14],_DMA1_port_pr_channel_2
        .ELSE
          ; Channel 3, DMA1
            mov     word ptr ss:[ebp-02],_DMA1_port_bca_channel_3
            mov     word ptr ss:[ebp-04],_DMA1_port_bcc_channel_3
            mov     word ptr ss:[ebp-14],_DMA1_port_pr_channel_3
        .ENDIF
    .ELSE
      ; It's on DMA channel 2
        mov     word ptr ss:[ebp-06],_DMA2_port_mode_register
        mov     word ptr ss:[ebp-08],_DMA2_port_mask_register
        mov     word ptr ss:[ebp-10],_DMA2_port_clear_register
        mov     byte ptr ss:[ebp-11],cl
        sub     byte ptr ss:[ebp-11],4
        .IF (ecx == 4)
          ; Channel 4, DMA2
            mov     word ptr ss:[ebp-02],_DMA2_port_bca_channel_4
            mov     word ptr ss:[ebp-04],_DMA2_port_bcc_channel_4
            mov     word ptr ss:[ebp-14],_DMA2_port_pr_channel_4
        .ELSEIF (ecx == 5)
          ; Channel 5, DMA2
            mov     word ptr ss:[ebp-02],_DMA2_port_bca_channel_5
            mov     word ptr ss:[ebp-04],_DMA2_port_bcc_channel_5
            mov     word ptr ss:[ebp-14],_DMA2_port_pr_channel_5
        .ELSEIF (ecx == 6)
          ; Channel 6, DMA2
            mov     word ptr ss:[ebp-02],_DMA2_port_bca_channel_6
            mov     word ptr ss:[ebp-04],_DMA2_port_bcc_channel_6
            mov     word ptr ss:[ebp-14],_DMA2_port_pr_channel_6
        .ELSE
          ; Channel 7, DMA2
            mov     word ptr ss:[ebp-02],_DMA2_port_bca_channel_7
            mov     word ptr ss:[ebp-04],_DMA2_port_bcc_channel_7
            mov     word ptr ss:[ebp-14],_DMA2_port_pr_channel_7
        .ENDIF
    .ENDIF
  ;; Tell the DMA controller which channel to write
    mov     al,cl
    mov     dx,word ptr ss:[ebp-08]                                 ; Mask register
    out     dx,al
    jmp     $+2

  ;; Send the flip-flop byte (clears out the internal register)
    mov     dx,word ptr ss:[ebp-10]                                 ; Clear register
    out     dx,al
    jmp     $+2

  ;; Specify the mode to use for this DMA read/write
    mov     al,byte ptr ss:[ebp-11]                                 ; BITS0-1 - channel
    mov     dx,word ptr ss:[ebp+14]                                 ; BITS2-3 - transfer type
    and     dl,11b
    shl     edx,2
    or      al,dl
    ; BIT 4                                                         ; BIT4 is autoinitialization enable, 0-disable is the default
    mov     edx,dword ptr ss:[ebp+20]                               ; BIT5 - direction
    and     dl,1
    shl     edx,5
    or      al,dl
    mov     edx,dword ptr ss:[ebp+24]                               ; BIT6-7 - Mode type
    and     dl,11b
    shl     edx,6
    or      al,dl
    mov     dx,word ptr ss:[ebp-06]                                 ; Mode register
    out     dx,al
    jmp     $+2

  ;; Specify the paging address
    mov     ecx,dword ptr ss:[ebp+16]                               ; send bits 16-19
    mov     eax,ecx
    shr     eax,16
    mov     dx,word ptr ss:[ebp-14]
    out     dx,al
    jmp     $+2
    mov     al,ch                                                   ; send bits 8-15
    mov     dx,word ptr ss:[ebp-02]
    out     dx,al
    jmp     $+2
    mov     al,cl                                                   ; send bits 0-7
    out     dx,al
    jmp     $+2

  ;; Send the count
    mov     ax,word ptr ss:[ebp+12]
    dec     ax
    mov     dx,word ptr ss:[ebp-04]
    out     dx,al                                                   ; send bits 0-7
    jmp     $+2
    xchg    ah,al
    out     dx,al                                                   ; send bits 8-15
    jmp     $+2

  ;; FINISHED! :)


  iDMA_quit:
    sti

    pop     ecx
    pop     eax
    pop     edx
    retf
iDMA_setup      ENDP