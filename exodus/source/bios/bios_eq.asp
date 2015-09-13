; bios_eq.asp
;
; Exodus BIOS functionality constant equates
;


; PIC register access (programmable interrupt controller)
_PIC_20h                        EQU 20h                             ; input  = 8259-1 read interrupt request/service registers
                                                                    ; output = 8259-1 interrupt command
_PIC_21h                        EQU 21h                             ; input  = 8259-1 interrupt mask register
                                                                    ; output = 8259-1 interrupt commands
_PIC_70h                        EQU 70h                             ; output = 8259-1 NMI enable (output only)
_PIC_A0h                        EQU 0a0h                            ; input  = 8259-2 read interrupt request / service registers
                                                                    ; output = 8259-2 interrupt command
                                                                    ; output = 8259-2 NMI control
_PIC_A1h                        EQU 0a1h                            ; input  = 8259-2 interrupt mask register
                                                                    ; output = 8259-2 interrupt commands


; PIT register access (8254 programmable interrupt timer)
_PIT_FREQUENCY                  EQU 1193181 ; Equivelent to 1.1931816666667MHz (or the 3.549545MHz chroma crystal / 3)
_PIT_0_BASE                     EQU 40h     ; Timer 0
_PIT_1_BASE                     EQU 41h     ; Timer 1
_PIT_2_BASE                     EQU 42h     ; Timer 2
_PIT_MODE                       EQU 43h     ; Mode control for timer's 0-2