; data16.asp
;
; Exodus data used in the 16-bit segment
;

; DATA
    bootup_id1              db  " Exodus(tm) Operating System                                    10.10.2010.beta "
    bootup_id2              db  " (c) Copyright Beatleworks, Inc.                                                "

    verifying_crc           db  "þ Verifying CRC"
    enabling_gate_a20       db  "þ Enabling A20"
    setup_pmode_vars        db  "þ Setup IDT, GDT"
    entering_pmode          db  "þ Entering protected mode"

    crc_comparitive         db  13,10,"xxxx  xxxx"
    crc_error_start         db  "þ CRC error has been detected.",13,10
    crc_error_code          db  "þ (x) is the error code",13,10
                            db  13,10
                            db  "þ Exodus cannot boot up when CRC errors are found.",13,10
                            db  "þ Please correct this error and try again.  You may need",13,10
                            db  "  to copy system files from the master Exodus Boot Disk.",13,10
                            db  13,10
                            db  "þ System halted.  Please press RESET to reboot."
    crc_error_end:

    boot_parameter_block    dd  0
    boot_parameter_count    dw  0
    next_linear_address     dd  0
    boot_dt_linear          dd  0
    boot_np_linear          dd  0
    boot_rp_linear          dd  0

    IDT_ptr                 dw  _sIDT_limit     ; 256 slots, 8 bytes each = 7ffh bytes
                            dd  _sIDT_base      ; Linear offset in memory

    GDT_ptr                 dw  _sGDT_limit     ; 4096 GDT entries
                            dd  _sGDT_base      ; Linear offset
