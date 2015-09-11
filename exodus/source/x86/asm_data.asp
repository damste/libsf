; asm_data.asp
;
; Data for the Debi Debugger disassembly/assembly algorithms
;



    CONST_AL                EQU 000b
    CONST_AX                EQU 000b
    CONST_EAX               EQU 000b
    CONST_ES                EQU 000b

    CONST_CL                EQU 001b
    CONST_CX                EQU 001b
    CONST_ECX               EQU 001b
    CONST_CS                EQU 001b

    CONST_DL                EQU 010b
    CONST_DX                EQU 010b
    CONST_EDX               EQU 010b
    CONST_SS                EQU 010b

    CONST_BL                EQU 011b
    CONST_BX                EQU 011b
    CONST_EBX               EQU 011b
    CONST_DS                EQU 011b

    CONST_AH                EQU 100b
    CONST_SP                EQU 100b
    CONST_ESP               EQU 100b
    CONST_FS                EQU 100b

    CONST_CH                EQU 101b
    CONST_BP                EQU 101b
    CONST_EBP               EQU 101b
    CONST_GS                EQU 101b

    CONST_DH                EQU 110b
    CONST_SI                EQU 110b
    CONST_ESI               EQU 110b

    CONST_BH                EQU 111b
    CONST_DI                EQU 111b
    CONST_EDI               EQU 111b

    ebx_esi_register        db  "ebx+esi"
    ebx_edi_register        db  "ebx+edi"
    ebp_esi_register        db  "ebp+esi"
    ebp_edi_register        db  "ebp+edi"
    bx_si_register          db  "bx+si"
    bx_di_register          db  "bx+di"
    bp_si_register          db  "bp+si"
    bp_di_register          db  "bp+di"
    cs_register             db  "cs"
    ds_register             db  "ds"
    es_register             db  "es"
    fs_register             db  "fs"
    gs_register             db  "gs"
    ss_register             db  "ss"
    eax_register            db  "e"
    ax_register             db  "ax"
    ebx_register            db  "e"
    bx_register             db  "bx"
    ecx_register            db  "e"
    cx_register             db  "cx"
    edx_register            db  "e"
    dx_register             db  "dx"
    esi_register            db  "e"
    si_register             db  "si"
    edi_register            db  "e"
    di_register             db  "di"
    ebp_register            db  "e"
    bp_register             db  "bp"
    ah_register             db  "ah"
    al_register             db  "al"
    bh_register             db  "bh"
    bl_register             db  "bl"
    ch_register             db  "ch"
    cl_register             db  "cl"
    dh_register             db  "dh"
    dl_register             db  "dl"
    ip_register             db  "ip"
    esp_register            db  "e"
    sp_register             db  "sp"
    st0_register            db  "st0"
    st1_register            db  "st1"
    st2_register            db  "st2"
    st3_register            db  "st3"
    st4_register            db  "st4"
    st5_register            db  "st5"
    st6_register            db  "st6"
    st7_register            db  "st7"
    cr0_register            db  "cr0"
    cr1_register            db  "cr1"
    cr2_register            db  "cr2"
    cr3_register            db  "cr3"
    cr4_register            db  "cr4"
    cr5_register            db  "cr5"
    cr6_register            db  "cr6"
    cr7_register            db  "cr7"
    dr0_register            db  "dr0"
    dr1_register            db  "dr1"
    dr2_register            db  "dr2"
    dr3_register            db  "dr3"
    dr4_register            db  "dr4"
    dr5_register            db  "dr5"
    dr6_register            db  "dr6"
    dr7_register            db  "dr7"
    tr0_register            db  "tr0"
    tr1_register            db  "tr1"
    tr2_register            db  "tr2"
    tr3_register            db  "tr3"
    tr4_register            db  "tr4"
    tr5_register            db  "tr5"
    tr6_register            db  "tr6"
    tr7_register            db  "tr7"
    flags_register          db  "flags"
    zero_ffff               db  "0ffffh"

    temp_buffer             db  100 dup(0)
    temp_buffer2            db  100 dup(0)
