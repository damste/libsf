; bootup.asm
;
; Exodus BOOTUP.COM
;

TITLE Bootup

    .MODEL tiny

    .386P
;_DEBI   EQU 0

INCLUDE ../source/common/macros.asp							; Macros used throughout Exodus
INCLUDE ../source/common/equates.asp						; Constants used to access memory variables, etc
INCLUDE ../source/common/errors.asp							; Error codes used throughout
INCLUDE equates.asp

;;
;;  úúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúú
;;  úúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúú
;;  úúúÛÛúúúúúÛÛÛúúúúúúúúúúúÛÛÛúúúúúúúúÛÛúúúúúúÛúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúÛÛÛúúúúúúúúúú
;;  úúÛÛÛúúúúÛÛúúúúúúúúúúúúúúÛÛúúúúúúúúÛÛúúúúúÛÛúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúÛÛúúúúúúúúúú
;;  úÛÛÛÛúúúÛÛúúúúúúúúúúúúúúúÛÛúúúúúúúúúúúúúúúÛÛúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúÛÛúúúúúúúúúú
;;  úúúÛÛúúúÛÛúúúúúúúúúúúúúúúÛÛÛÛúúúúúÛÛÛúúúÛÛÛÛÛÛúúúúúúúúúúúÛÛÛÛÛúúúÛÛÛÛÛúúúúÛÛÛÛúúúÛÛÛÛÛúú
;;  úúúÛÛúúúÛÛÛÛÛÛúúúúúúúúúúúÛÛúÛÛúúúúúÛÛúúúúúÛÛúúúúúúúúúúúúÛÛúúúÛÛúÛÛúúúÛÛúúÛÛúÛÛúúÛÛúúúÛÛú
;;  úúúÛÛúúúÛÛúúúÛÛúúúúúúúúúúÛÛúúÛÛúúúúÛÛúúúúúÛÛúúúúúúúúúúúúÛÛúúúúúúÛÛúúúÛÛúÛÛúúÛÛúúÛÛÛÛÛÛÛú
;;  úúúÛÛúúúÛÛúúúÛÛúúúúúúúúúúÛÛúúÛÛúúúúÛÛúúúúúÛÛúúúúúúúúúúúúÛÛúúúúúúÛÛúúúÛÛúÛÛúúÛÛúúÛÛúúúúúú
;;  úúúÛÛúúúÛÛúúúÛÛúúúúúúúúúúÛÛúúÛÛúúúúÛÛúúúúúÛÛúÛÛúúúúúúúúúÛÛúúúÛÛúÛÛúúúÛÛúÛÛúúÛÛúúÛÛúúúÛÛú
;;  úÛÛÛÛÛÛúúÛÛÛÛÛúúúúúúúúúúúÛÛÛÛÛúúúúÛÛÛÛúúúúúÛÛÛúúúúúúúúúúúÛÛÛÛÛúúúÛÛÛÛÛúúúÛÛÛúÛÛúúÛÛÛÛÛúú
;;  úúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúú
;;  úúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúú
;;  úúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúú
;;
_TEXT   SEGMENT PUBLIC  'CODE'  USE16
    ORG 0h
;;
;; START OF EXODUS
;;
;; ---------------
;;
;; During this segment we're in real mode.
;; All BIOS services are available
;;
;; Upon entry:  cx - total # of bytes in boot_parameter_block
;;             edx - next linear address of free memory (between 010000h and 03ffffh)
;;         cs:[si] - far ptr to start of parameter_block
;;      cs:[si-12] - linear address of boot device's DT entry
;;      cs:[si-08] - linear address of boot device's NP entry
;;      cs:[si-04] - linear address of boot device's RP entry
;;

  start:
;; Save the parameter block information given by BOOT.COM
    mov     cs:boot_parameter_count,cx                              ; Number of drivers loaded
    mov     cs:next_linear_address,edx                              ; Next address of free memory in Exodus bootup area
    mov     eax,dword ptr ds:[si-12]
    mov     cs:boot_dt_linear,eax                                   ; 1st sector of DT
    mov     eax,dword ptr ds:[si-8]
    mov     cs:boot_np_linear,eax                                   ; 1st sector of NP
    mov     eax,dword ptr ds:[si-4]
    mov     cs:boot_rp_linear,eax                                   ; 1st sector of RP
    xor     eax,eax
    and     esi,0ffffh
    mov     ax,ds
    shl     eax,4
    add     eax,esi
    mov     cs:boot_parameter_block,eax                             ; Linear offset into memory where boot_parameter_block starts
                                                                    ; * Refer to source\boot.asm for boot_parameter_block info

;; Setup the data segments for this program
    mov     ax,cs
    mov     ds,ax
    mov     es,ax

;; Set video mode using BIOS
    mov     ax,00003h                                               ; Mode 3 = 80x25 color
    int     10h

;; Turn on high intensity using BIOS
    mov     ax,1003h                                                ; video high intensity on (instead of blinking)
    xor     bl,bl
    int     10h

;; Show the bootup identification using BIOS
    mov     bx,57+128                                               ; bright blue on bright cyan
    xor     dx,dx
    mov     bp,offset bootup_id1
    mov     cx,sizeof bootup_id1
    xor     bh,bh
    mov     ax,01301h
    int     10h

    mov     bx,57+128                                               ; bright blue on bright cyan
    mov     dx,00100h
    mov     bp,offset bootup_id2
    mov     cx,sizeof bootup_id2
    xor     bh,bh
    mov     ax,01301h
    int     10h

;; Verify the CRC-16 of the boot files
;    mov     bx,07
;    mov     dx,00300h
;    mov     bp,offset verifying_crc
;    mov     cx,sizeof verifying_crc
;    xor     bh,bh
;    mov     ax,01301h
;    int     10h
;    call    verify_crc16

;; Enable gate A20 via Exodus
    mov     bp,offset enabling_gate_a20
    mov     cx,sizeof enabling_gate_a20
    mov     bx,07
    mov     dx,0400h
    mov     ax,01301h
    int     10h
    call    enable_gate_a20

;; Setup environment for protected mode via Exodus
    mov     bp,offset setup_pmode_vars
    mov     cx,sizeof setup_pmode_vars
    mov     bx,07
    mov     dx,0500h
    mov     ax,01301h
    int     10h
    call    setup_pmode_variables

;; Enter protected mode via Exodus
    mov     bp,offset entering_pmode
    mov     cx,sizeof entering_pmode
    mov     bx,07
    mov     dx,0600h
    mov     ax,01301h
    int     10h

    cli                                                             ; Clear interrupts
    mov     eax,cr0
    or      al,1
    mov     cr0,eax
;; Ok, we're in protected mode, still 16-bit code segment though
    jmp     $+2                                                     ; Clear the cache
    lidt    fword ptr IDT_ptr                                       ; Load IDT
    lgdt    fword ptr GDT_ptr                                       ; Load GDT
    xor     ax,ax
    lldt    ax                                                      ; Load LDT with NULL
    mov     ax,_sEXODUS_TSS                                         ; Load TR
    ltr     ax
  ; Data segment registers
    mov     ax,_sDATA
    mov     ds,ax
    mov     es,ax
  ; Extra segment registers
    mov     ax,_sVGA
    mov     fs,ax
    mov     ax,_sMONO
    mov     gs,ax
  ; Stack
    mov     ax,_sSTACK
    mov     ss,ax
    mov     esp,_sSTACK_limit - 4
    sti

;; Load the 32-bit _sCODE selector for CS and enter 32-bit code
    push    word ptr _sCODE                                         ; Exodus CODE segment
    push    word ptr offset end_of_16_bit_segment                   ; EIP
    retf                                                            ; Execution continues below after "first_pmode_instruction"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Note:  Each of these include files contains only 16-bit code and/or data.  However, some of them can create 32-bit items.
;;
    INCLUDE init16.asp
    INCLUDE data16.asp

end_of_16_bit_segment:
_TEXT   ENDS





;;
;;  úúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúú
;;  úúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúú
;;  úÛÛÛÛÛúúúÛÛÛÛÛúúúúúúúúúúÛÛÛúúúúúúúúÛÛúúúúúúÛúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúÛÛÛúúúúúúúúúú
;;  ÛÛúúúÛÛúÛÛúúúÛÛúúúúúúúúúúÛÛúúúúúúúúÛÛúúúúúÛÛúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúÛÛúúúúúúúúúú
;;  úúúúúÛÛúúúúúúÛÛúúúúúúúúúúÛÛúúúúúúúúúúúúúúúÛÛúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúÛÛúúúúúúúúúú
;;  úúúúúÛÛúúúúúÛÛúúúúúúúúúúúÛÛÛÛúúúúúÛÛÛúúúÛÛÛÛÛÛúúúúúúúúúúúÛÛÛÛÛúúúÛÛÛÛÛúúúúÛÛÛÛúúúÛÛÛÛÛúú
;;  úúÛÛÛÛúúúúúÛÛúúúúúúúúúúúúÛÛúÛÛúúúúúÛÛúúúúúÛÛúúúúúúúúúúúúÛÛúúúÛÛúÛÛúúúÛÛúúÛÛúÛÛúúÛÛúúúÛÛú
;;  úúúúúÛÛúúúÛÛúúúúúúúúúúúúúÛÛúúÛÛúúúúÛÛúúúúúÛÛúúúúúúúúúúúúÛÛúúúúúúÛÛúúúÛÛúÛÛúúÛÛúúÛÛÛÛÛÛÛú
;;  úúúúúÛÛúúÛÛúúúúúúúúúúúúúúÛÛúúÛÛúúúúÛÛúúúúúÛÛúúúúúúúúúúúúÛÛúúúúúúÛÛúúúÛÛúÛÛúúÛÛúúÛÛúúúúúú
;;  ÛÛúúúÛÛúÛÛúúúÛÛúúúúúúúúúúÛÛúúÛÛúúúúÛÛúúúúúÛÛúÛÛúúúúúúúúúÛÛúúúÛÛúÛÛúúúÛÛúÛÛúúÛÛúúÛÛúúúÛÛú
;;  úÛÛÛÛÛúúÛÛÛÛÛÛÛúúúúúúúúúúÛÛÛÛÛúúúúÛÛÛÛúúúúúÛÛÛúúúúúúúúúúúÛÛÛÛÛúúúÛÛÛÛÛúúúÛÛÛúÛÛúúÛÛÛÛÛúú
;;  úúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúú
;;  úúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúú
;;  úúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúú
;;
_TEXT32 SEGMENT PUBLIC BYTE 'CODE' USE32
    ASSUME NOTHING
;;
;; Exodus Bootup Program 32-bit kernel begins here
;;
;; -----
;;
;; PROTECTED MODE
;; All services from here on out are internal
;;

first_pmode_instruction:                                            ; Setup segment selectors so they are loaded correctly
;  ;; Indicate that we entered protected mode OK
;    mov     dword ptr fs:[6*80*2 + (sizeof entering_pmode * 2)],'KO'      ; Line 6, plus the offset of whatever text was shown


  ;; Turn off the nested-task flag
    pushfd
    and     dword ptr ss:[esp],NOT _EFLAGS_NT_MASK
    popfd


  ;; Setup some of the required memory blocks
    call    invSetup_memory_blocks                                  ; init32.asp


  ;; Setup the Exodus native primatives
    call    invSetup_native_primatives                              ; native.asp

  ; Note, this is temporarily done manually until the iFDC drivers are installed
    mov     al,001100b
    mov     edx,03f2h
    out     dx,al
  ;; Parse the exodus.ini file
    call    invFind_Exodus_ini                                      ; ini.asp
    call    invDetermine_Exodus_ini_ownership                       ;


  ;; Reset the video mode
    sub     esp,20                                                  ; return values (+16=bpp, +12=hp, +8=vp, +4=refresh, +0=status)
    push    0                                                       ; param: graphics mode
    push    8                                                       ; param: bits per pixel
    push    320                                                     ; param: horizontal pixels
    push    200                                                     ; param: vertical pixels
    push    60                                                      ; param: refresh rate
    mov     eax,1
    call    fword ptr cs:_VID_requestor
    add     esp,20                                                  ; get the return values off the stack (we know this works)


  ;; Turn off the floppy drive motor
;    mov     al,'A'
;    call    fword ptr cs:_iFDC_motor_off

  ;; Transfer control to EXODUS.COM
    jmp     fword ptr cs:_EXODUS_dot_com
;;
;; END OF PROGRAM
;;
;; --------------
;;
;; Control will never return here
;;
;; -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
;;



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Note:  Each of these include files contains only 32-bit code and/or data
;;

    INCLUDE init32.asp                                              ; Baseline initialization routines
    INCLUDE data32.asp
    INCLUDE native.asp                                              ; Native primatives
    INCLUDE ini.asp
    INCLUDE req.asp                                                 ; requestor()

end_of_32_bit_segment:
_TEXT32 ENDS


END
