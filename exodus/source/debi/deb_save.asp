; debidata.asp
;
; Debi data
;


;;============================
;; These value are stack offsets used for temporary space during debi_generate_disassembly()
;;
_INS_DISPLAYED              EQU 4
_SHIFT_LEFT                 EQU 8
_SHIFT_RIGHT                EQU 12
_INS_BYTES                  EQU 16
_TEMP_DATA                  EQU 20



;;============================
;; This variable is used
;;
debi_instruction_output     db  60 dup(0)
debi_single_step            db  0
debi_resume                 db  0
debi_busy                   db  0


;;============================
;; This is the screen that is the main Debi debugging screen
;;
;                                          1    1    2    2    3    3    4    4    5    5    6    6    7    7
;                                0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ
debi_debug_info_screen      db  "פ³Ý                                      Þץ³פ F5:go  F8:step  F9:break  F10:over     ץ"   ; 0
                            db  "ÄInstruction streamÄ´תתתת:תתתתתתתתÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿ÄInstruction PointerÄÄÄÄÄ"   ; 1
                            db  "-0010 תת תת תת תת תת תת תת תת תת תת תת תת תת תת תת תת ³cs:eip-תתתת  cr0-תתתתתתתת"   ; 2
                            db  "+0000 תת תת תת תת תת תת תת תת תת תת תת תת תת תת תת תת ³   תתתתתתתת  cr4-תתתתתתתת"   ; 3
                            db  "+0010 תת תת תת תת תת תת תת תת תת תת תת תת תת תת תת תת ³        vme ne ts de "   ; 4
                            db  255
                            db  "ÄQueryBoxÄÄÄÄÄÄÄÄÄÄ¿"   ; 21
Infobox_text                db  "ÄInfoBoxÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ"   ; (second half of 21)
                            db  "                   ³                                                            "   ; 22
                            db  "                   ³               פ Low-Level Debi(tm) Debugger ץ                "   ; 23
                            db  "                   ³               פ      by Beatleworks, Inc.   ץ                ",0 ; 24

;                                          1    1    2    2    3    3
;                                0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ
debi_debug_gdt_idt          db  "Ä¯GDT¯Ä´תתתתתתתתÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¯D1¯Ä1ÂÄ¿",255
                            db  "  60¿ 56¿  52¿ 48¿  44¿ 40¿  36¿ 32¿ ³³",255
                            db  " ÚÂÂÅÂÂÂ´ ÚÂÂÅÂÂÂ´ ÚÂÂÅÂÂÂ´ ÚÂÂÅÂÂÂ´ ³°³",255
                            db  " תתתתתתתת תתתתתתתת תתתתתתתת תתתתתתתת ³°³",255
                            db  " תתתתתתתת תתתתתתתת תתתתתתתת תתתתתתתת ³°³",255
                            db  " ÀÁÁÅÁÁÁ´ ÀÁÁÅÁÁÁ´ ÀÁÁÅÁÁÁ´ ÀÁÁÅÁÁÁ´ ³°³",255
                            db  "  28Ù 24Ù  20Ù 16Ù  12Ù  8Ù   4Ù  0Ù ³³",0

;                                          1    1    2    2    3    3
;                                0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ
debi_debug_fpu              db  "ÄFPUÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¯D1¯Ä2¿",255
                            db  "st0 תתתתתתתתתתתתתתתתתתתת  cw תתתתתתתת  ³",255
                            db  "st1 תתתתתתתתתתתתתתתתתתתת  sw תתתתתתתת  ³",255
                            db  "st2 תתתתתתתתתתתתתתתתתתתת  tw תתתתתתתת  ³",255
                            db  "st3 תתתתתתתתתתתתתתתתתתתת               ³",255
                            db  "st4 תתתתתתתתתתתתתתתתתתתת  fcs:תתתתתתתת ³",255
                            db  "st5 תתתתתתתתתתתתתתתתתתתת feip:תתתתתתתת ³",255
                            db  "st6 תתתתתתתתתתתתתתתתתתתת  fds:תתתתתתתת ³",255
                            db  "st7 תתתתתתתתתתתתתתתתתתתת fesi:תתתתתתתת ³",0

;                                          1    1    2    2    3    3
;                                0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ
debi_debug_disasm           db  "ÄDisassemblyÄ´תתתת:תתתתתתתתÃÄÄÄÄÄÄÄÄÄÄ3¿",255
                            db  "                                       ³",255
                            db  "                                       ³",255
                            db  "                                       ³",255
                            db  "                                       ³",255
                            db  "                                       ³",255
                            db  "                                       ³",0

;                                          1    1    2    2    3    3
;                                0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ
debi_debug_stack            db  "ÄStackÄ´תתתת:תתתתתתתתÃÄÄÄÄÄÄÄÄÄ¯D1¯Ä4ÂÄ¿",255
                            db  " תת תת תת תת +0044  תת תת תת תת +001c³³",255
                            db  " תת תת תת תת +0040  תת תת תת תת +0018³°³",255
                            db  " תת תת תת תת +003c  תת תת תת תת +0014³°³",255
                            db  " תת תת תת תת +0038  תת תת תת תת +0010³°³",255
                            db  " תת תת תת תת +0034  תת תת תת תת +000c³°³",255
                            db  " תת תת תת תת +0030  תת תת תת תת +0008³°³",255
                            db  " תת תת תת תת +002c  תת תת תת תת +0004³°³",255
                            db  " תת תת תת תת +0028  תת תת תת תת +0000³³",0

;                                          1    1    2    2    3    3
;                                0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ
debi_debug_registers        db  "ÄRegistersÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ5¿",255
                            db  " eax תתתתתתתת  ds תתתת  eflags תתתתתתתת³",255
                            db  " ebx תתתתתתתת  es תתתת  Ã nt  of acf³",255
                            db  " ecx תתתתתתתת  fs תתתת  Ã pf  sf  if³",255
                            db  " edx תתתתתתתת  gs תתתת  À df  zf  cf³",255
                            db  " esi תתתתתתתת          Ú ebp תתתתתתתת  ³",255
                            db  " edi תתתתתתתת  ss תתתתÄÁ esp תתתתתתתת  ³",0

;                                          1    1    2    2    3    3
;                                0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ0ÀÁÁÙ5ÀÁÁÙ
debi_debug_stack_mem        db  "ÄStackÄÄÄÄÄÄ¯D1¯ÄÄ¿Mem´תתתתתתתתÃÄ¯D1¯Â6¿",255
                            db  " תת תת תת תת +001c³ תת תת תת תת +001c³³",255
                            db  " תת תת תת תת +0018³ תת תת תת תת +0018³°³",255
                            db  " תת תת תת תת +0014³ תת תת תת תת +0014³°³",255
                            db  " תת תת תת תת +0010³ תת תת תת תת +0010³°³",255
                            db  " תת תת תת תת +000c³ תת תת תת תת +000c³°³",255
                            db  " תת תת תת תת +0008³ תת תת תת תת +0008³°³",255
                            db  " תת תת תת תת +0004³ תת תת תת תת +0004³°³",255
                            db  " תת תת תת תת +0000³ תת תת תת תת +0000³³",0

debi_screen_format          db  2                                       ; FPU
                            db  3                                       ; Disassembly
                            db  5                                       ; Registers
                            db  6                                       ; Stack & Mem


;;============================
;; These are the different types of InfoBox's that get drawn depending on what item the mouse is currently over
;; * Note:  These use encoding, the numbers below represent the "insert_text_*" variables.  This was added to save storage
;;          space for frequently repeated text items.  A code of 255 fills the rest of the line with spaces, 1 uses ASCII-196's
;;          and a 0 is used to terminate the InfoBox.  Special character are also recognized, פ for reverse-video-start and
;;          ץ for reverse-video-stop.  * Refer to the debi_clear_info_box() routine for more information.
;;
infobox_clear               db  "ÄInfoBox",1
                            db  255
                            db  255
                            db  255,0

insert_text_2               db  "   ת ",0
insert_text_3               db  "תתתת ",0
insert_text_4               db  "Hex: ",0
insert_text_5               db  "Bin: ",0
insert_text_6               db  "Dec: ",0
insert_text_7               db  "Signed: ",0
insert_text_8               db  "ÄInfoBoxÄ",0
insert_text_9               db  "®STD¯",0
insert_text_10              db  "®ALT¯",0
insert_text_11              db  "®CTRL¯",0
insert_text_12              db  "Exponent:",0
insert_text_13              db  "Mantissa:",0
insert_text_14              db  "Float",0
insert_text_15              db  "float",0
insert_text_16              db  "Normal",0
insert_text_17              db  "ized:",0
insert_text_18              db  "Status: ",0

infobox_byte                db  8,"(byte)",1
                            db  4,2,2,255
                            db  5,3,3,255
                            db  6,"‏תתת  ",7,"‏תתת",255,0

infobox_word                db  8,"(word)",1
                            db  4,2,2,2,2,255
                            db  5,3,3,3,3,255
                            db  6,"‏תתתתת  ",7,"‏תתתתת",255,0

infobox_dword               db  8,"(dword)Ä",9,1
                            db  4,2,2,2,2,2,2,2,2,255
                            db  5,3,3,3,3,3,3,3,3,255
                            db  6,"‏תתתתתתתתתת  ",7,"‏תתתתתתתתתת",255,0

infobox_dworda              db  8,"(dword/",15,"32)Ä",10,1
                            db  12,255
                            db  13,255
                            db  " ",14,"32:",255,0

infobox_dwordc              db  8,"(dword/",15,"32)Ä",11,1
                            db  255
                            db  "   ",14,"32:",255
                            db  16,17,255,0

infobox_reg32               db  8,"(32-bit)Ä",9,1
                            db  4,2,2,2,2,2,2,2,2,255
                            db  5,3,3,3,3,3,3,3,3,255
                            db  6,"‏תתתתתתתתתת  ",7,"‏תתתתתתתתתת",255,0

infobox_reg32a              db  8,"(32-bit/",15,"32)Ä",10,1
                            db  12,255
                            db  13,255
                            db  " ",14,"32:",255,0

infobox_reg32c              db  8,"(32-bit/",15,"32)Ä",11,1
                            db  255
                            db  "   ",14,"32:",255
                            db  16,17,255,0

infobox_flag                db  8,"(flag)Ä",9,1
                            db  18,"תתת",255
                            db  255
                            db  255,0

infobox_bin32               db  8,"(bin32)Ä",9,1
                            db  4,2,2,2,2,2,2,2,2,255
                            db  5,3,3,3,3,3,3,3,3,255
                            db  6,"‏תתתתתתתתתת  ",7,"‏תתתתתתתתתת",255,0

infobox_f32                 db  8,"(",15,"32)Ä",9,1
                            db  12,255
                            db  13,255
                            db  " ",14,"32:",255,0

infobox_f32a                db  8,"(",15,"32)Ä",10,1
                            db  255
                            db  "   ",14,"32:",255
                            db  16,17,255,0

infobox_f64                 db  8,"(",15,"64)Ä",9,1
                            db  12,255
                            db  13,255
                            db  " ",14,"32:",255,0

infobox_f64a                db  8,"(",15,"64)Ä",10,1
                            db  255
                            db  14,"64:",255
                            db  " ",16,":",255,0

infobox_f80                 db  8,"(",15,"80)Ä",9,1
                            db  12,255
                            db  13,255
                            db  " ",14,"80:",255,0

infobox_f80a                db  8,"(",15,"80)Ä",10,1
                            db  255
                            db  14,"80:",255
                            db  " ",16,":",255,0



;;============================
;; This system allows approximately 2800 items to be referenced on the screen at any one time
;; The memory used for this is stored off the MONO screen in MONO video memory (b0fa0-b7fffh)
;; * Note, for more information see INF\FAULT.INF
debi_udf_window_areas       dd  0
debi_text_1                 db  "Trap/error/exception ³ #num - Description"


debi_count                  db  0
debi_mouse_pointer_update   db  0
debi_mouse_y                db  12
debi_mouse_y_last           db  25                                  ; Just off the screen
debi_mouse_y_counter        dd  0
debi_mouse_x                db  40
debi_mouse_x_last           db  0
debi_color_last             db  0
debi_mouse_x_counter        dd  0
highlight_last_point1       dw  0
highlight_last_point2       dw  0
last_object_segment         dw  0                                   ;
last_object_offset          dd  0
; * Note:  mouse_redirect is in SOURCE\MOUSE.ASP
; * Note:  keyboard_redirect is in SOURCE\KEYBOARD.ASP



;;============================
;; This portion of the data is used to identify what has changed from the previous use of the debi_debug() algorithms
already_here                db  0
                                                                    ; Identified internally as:
last_eax                    dd  0ffffffffh                          ; eax=1, ax=20, ah=30, al=35
last_ebx                    dd  0ffffffffh                          ; ebx=2, bx=21, bh=31, bl=36
last_ecx                    dd  0ffffffffh                          ; ecx=3, cx=22, ch=32, cl=37
last_edx                    dd  0ffffffffh                          ; edx=4, dx=23, dh=33, dl=38
last_esi                    dd  0ffffffffh                          ; esi=5, si=24
last_edi                    dd  0ffffffffh                          ; edi=6, di=25
last_esp                    dd  0ffffffffh                          ; esp=7, sp=26
last_ip                     dd  0ffffffffh                          ; eip=8, ip=28
last_bp                     dd  0ffffffffh                          ; ebp=9, bp=27
current_esp                 dd  0
current_ebp                 dd  0
last_cs                     dw  0ffffh                              ; cs=10
last_ds                     dw  0ffffh                              ; ds=11
last_es                     dw  0ffffh                              ; es=12
last_fs                     dw  0ffffh                              ; fs=13
last_gs                     dw  0ffffh                              ; gs=14
last_ss                     dw  0ffffh                              ; ss=15
last_eflags                 dd  0ffffffffh                          ; flags=16
last_fpu_state              db  108 dup(0)
current_fpu_state           db  108 dup(0)



;=============================
;; Data used in the debi_generate_disassembly() procedure
    sreg_override           db  0
    sign_extend             db  0
    movxx                   db  0
    reverse_regs            db  0
    special_reg             db  0
    mod_reg_rm_byte         db  0
    sib_byte                db  0
    byte_word_size          db  0
    seg_override            db  0
    op_size_override        dw  0
    adr_size_override       dw  0

    int3_text               db  "int3"
    aaa_text                db  "aaa"
    xadd_text               db  "x"
    add_text                db  "add"
    aas_text                db  "aas"
    cbw_text                db  "cbw"
  cwde_text:
    cwd_text                db  "cwd"
                            db  "e"
    cdq_text                db  "cdq"
    clc_text                db  "clc"
    cld_text                db  "cld"
    cli_text                db  "cli"
    cmc_text                db  "cmc"
    daa_text                db  "daa"
    das_text                db  "das"
    hlt_text                db  "hlt"
    into_text               db  "into"
  iretd_text:
    iret_text               db  "iret"
                            db  "d"
    lahf_text               db  "lahf"
    leave_text              db  "leave"
    lock_text               db  "lock"
    nop_text                db  "nop"
  popad_text:
    popa_text               db  "popa"
                            db  "d"
  popfd_text:
    popf_text               db  "popf"
                            db  "d"
  pushad_text:
    pusha_text              db  "pusha"
                            db  "d"
  pushfd_text:
    pushf_text              db  "pushf"
                            db  "d"
    ret_text                db  "ret"
    retf_text               db  "retf"
    sahf_text               db  "sahf"
    stc_text                db  "stc"
    std_text                db  "std"
    sti_text                db  "sti"
    wait_text               db  "wait"
    xlat_text               db  "xlat"
    aad_text                db  "aad"
    aam_text                db  "aam"
    clts_text               db  "clts"
    wbinvd_text             db  "wb"
    invd_text               db  "invd"
    arpl_text               db  "arpl"
    bound_text              db  "bound"
    bswap_text              db  "bswap"
  call_far_text:
    call_text               db  "call"
                            db  "f"
    cmpxchg_text            db  "cmpxchg"
    enter_text              db  "enter"
    int_text                db  "int"
    ja_text                 db  "ja.u"
    jc_text                 db  "jc"
    jnc_text                db  "jnc"
    jbe_text                db  "jbe.u"
    jz_text                 db  "jz"
    jnz_text                db  "jnz"
    jl_text                 db  "jl.s"
    jg_text                 db  "jg.s"
    jle_text                db  "jle.s"
    jge_text                db  "jge.s"
    js_text                 db  "js"
    jns_text                db  "jns"
    jp_text                 db  "jp"
    jnp_text                db  "jnp"
    jo_text                 db  "jo"
    jno_text                db  "jno"
    seta_text               db  "seta.u"
    setc_text               db  "setc"
    setnc_text              db  "setnc"
    setbe_text              db  "setbe.u"
    setz_text               db  "setz"
    setnz_text              db  "setnz"
    setl_text               db  "setl.s"
    setg_text               db  "setg.s"
    setle_text              db  "setle.s"
    setge_text              db  "setge.s"
    sets_text               db  "sets"
    setns_text              db  "setns"
    setp_text               db  "setp"
    setnp_text              db  "setnp"
    seto_text               db  "seto"
    setno_text              db  "setno"
    jcxz_text               db  "jcxz"
    jecxz_text              db  "jecxz"
  jmp_far_text:
    jmp_text                db  "jmp"
                            db  "f"
  movsx_text:
    mov_text                db  "mov"
                            db  "sx"
    movzx_text              db  "movzx"
    lds_text                db  "lds"
    les_text                db  "les"
    lea_text                db  "lea"
  loopne_text:
    loop_text               db  "loop"
                            db  "ne"
  looped_text:
    loope_text              db  "loope"
    pop_text                db  "pop"
  pushd_text:
    push_text               db  "push"
                            db  "d"
  repne_text:
    rep_text                db  "rep"
                            db  "ne"
    repe_text               db  "repe"
    movsb_text              db  "movsb"
    movsw_text              db  "movsw"
    movsd_text              db  "movsd"
    stosb_text              db  "stosb"
    stosw_text              db  "stosw"
    stosd_text              db  "stosd"
    lodsb_text              db  "lodsb"
    lodsw_text              db  "lodsw"
    lodsd_text              db  "lodsw"
    insb_text               db  "insb"
    insw_text               db  "insw"
    insd_text               db  "insd"
    outsb_text              db  "outs"
    outsw_text              db  "outsw"
    outsd_text              db  "outsd"
    cmpsb_text              db  "cmpsb"
    cmpsw_text              db  "cmpsw"
    cmpsd_text              db  "cmpsd"
    scasb_text              db  "scasb"
    scasw_text              db  "scasw"
    scasd_text              db  "scasd"
    setccc_text             db  "setccc"
    bsf_text                db  "bsf"
    bsr_text                db  "bsr"
  btc_text:
    bt_text                 db  "bt"
                            db  "c"
    bts_text                db  "bts"
    btr_text                db  "btr"
    invlpg_text             db  "invlpg"
    lar_text                db  "lar"
    lfs_text                db  "lfs"
    lgs_text                db  "lgs"
    lss_text                db  "lss"
    lgdt_text               db  "lgdt"
    lidt_text               db  "lidt"
    lldt_text               db  "lldt"
    lmsw_text               db  "lmsw"
    lsl_text                db  "lsl"
    ltr_text                db  "ltr"
    sldt_text               db  "sldt"
    str_text                db  "str"
    verr_text               db  "verr"
    verw_text               db  "verw"
    sgdt_text               db  "sgdt"
    sidt_text               db  "sidt"
    smsw_text               db  "smsw"
  shld_text:
    shl_text                db  "shl"
                            db  "d"
    sal_text                db  "sal"
  shrd_text:
    shr_text                db  "shr"
                            db  "d"
    sar_text                db  "sar"
    imul_text               db  "i"
    mul_text                db  "mul"
    test_text               db  "test"
    not_text                db  "not"
    neg_text                db  "neg"
    idiv_text               db  "i"
    div_text                db  "div"
  inc_text:
    in_text                 db  "in"
                            db  "c"
    dec_text                db  "dec"
    rol_text                db  "rol"
    rcl_text                db  "rcl"
    ror_text                db  "ror"
    rcr_text                db  "rcr"
    xchg_text               db  "xchg"
    or_text                 db  "or"
    adc_text                db  "adc"
    sbb_text                db  "sbb"
    and_text                db  "and"
    sub_text                db  "sub"
    xor_text                db  "xor"
    cmp_text                db  "cmp"

    fadd_text               db  "fadd"
  fmulp_text:
    fmul_text               db  "fmul"
                            db  "p"
  fcompp_text:
  fcomp_text:
    fcom_text               db  "fcom"
                            db  "p"
                            db  "p"
  fsubrp_text:
  fsubr_text:
    fsub_text               db  "fsub"
                            db  "r"
                            db  "p"
  fdivr_text:
    fdiv_text               db  "fdiv"
                            db  "r"
    fdivp_text              db  "fdivp"
  fldcw_text:
    fld_text                db  "fld"
                            db  "cw"
  fstp_text:
    fst_text                db  "fst"
                            db  "p"
    fxch_text               db  "fxch"
    fnop_text               db  "fnop"
    fchs_text               db  "fchs"
    fabs_text               db  "fabs"
    ftst_text               db  "ftst"
    fxam_text               db  "fxam"
    fld1_text               db  "fld1"
    fldl2t_text             db  "fldl2t"
    fldl2e_text             db  "fldl2e"
    fldpi_text              db  "fldpi"
    fldg2_text              db  "fldg2"
    fldn2_text              db  "fldn2"
    fldz_text               db  "fldz"
    f2xm1_text              db  "f2xm1"
    fyl2x_text              db  "fyl2x"
    fptan_text              db  "fptan"
    fpatan_text             db  "fpatan"
    fxtract_text            db  "fxtract"
  fprem_text:
    fprem1_text             db  "fprem1"
    fdecstp_text            db  "fdecstp"
    fincstp_text            db  "fincstp"
    fyl2xp1_text            db  "fyl2xp1"
    fsqrt_text              db  "fsqrt"
    fsincos_text            db  "fsincos"
    frndint_text            db  "frndint"
    fscale_text             db  "fscale"
    fsin_text               db  "fsin"
    fcos_text               db  "fcos"
    fldenv_text             db  "fldenv"
    fstenv_text             db  "fstenv"
    fstcw_text              db  "fstcw"
    fucompp_text            db  "fucompp"
    fiadd_text              db  "fiadd"
    fimul_text              db  "fimul"
  ficomp_text:
    ficom_text              db  "ficom"
                            db  "p"
  fisubr_text:
    fisub_text              db  "fisub"
                            db  "r"
  fidivr_text:
    fidiv_text              db  "fidiv"
                            db  "r"
    fclex_text              db  "fclex"
    finit_text              db  "finit"
    fild_text               db  "fild"
  fistp_text:
    fist_text               db  "fist"
                            db  "p"
    ffree_text              db  "ffree"
  fucomp_text:
    fucom_text              db  "fucom"
                            db  "p"
    frstor_text             db  "frstor"
    fstsw_text              db  "fstsw"
    fbld_text               db  "fbld"
    fbstp_text              db  "fbstp"
    fsave_text              db  "fsave"


  illegal_register:
    unknown_text            db  "???"

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


    badnumber0              db  " +Unsupported               ",0
    badnumber1              db  " +NaN                       ",0
    badnumber2              db  " -Unsupported               ",0
    badnumber3              db  " -NaN                       ",0
    badnumber4              db  " +Normal                    ",0
    badnumber5              db  " +Infinity                  ",0
    badnumber6              db  " -Normal                    ",0
    badnumber7              db  " -Infinity                  ",0
    badnumber8              db  " 0.0000000000000000000+00000",0
    badnumber9              db  " +Empty                     ",0
    badnumber10             db  "-0.0000000000000000000+00000",0
    badnumber11             db  " -Empty                     ",0
    badnumber12             db  " +Denormals                 ",0
    badnumber13             db  " ?Unknown?                  ",0
    badnumber14             db  " -Denormals                 ",0

    fpu_stat                dw  ?
    exponent                sword   0
    number10                real4   10.0
    point5                  real4    0.5
    digit                   dw  ?
    controlword             dw  ?

    temp_buffer             db  40 dup(0)
