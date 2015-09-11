; equates.asp
;
; Exodus constants.  These are used at various places.
; This file provides a common area to modify constant values, rather than sifting through programs, etc.
;



INCLUDE x86_eq.asp


; ÚÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
; ³ GDT ENTRIES ³
; ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
    _sIDT                       EQU 1 * 8       ; IDT
    _sGDT                       EQU 2 * 8       ; GDT
    _sSTACK                     EQU 3 * 8       ; STACK
    _sCODE                      EQU 4 * 8       ; kernel CODE for kernel code
    _sDATA                      EQU 9 * 8       ; kernel DATA selector for kernel data
    _sGRAPHICS                  EQU 5 * 8       ; Graphics video (0a0000h)
    _sMONO                      EQU 6 * 8       ; Mono video (0b0000h)
    _sVGA                       EQU 7 * 8       ; VGA video (0b8000h)
    _sALL_MEM                   EQU 8 * 8       ; All memory (for debugging)
    ; 9 is above, _sDATA
    _sEXODUS_MEM                EQU 10 * 8      ; Exodus assigned memory
    _sEXODUS_PORTS              EQU 11 * 8      ; Exodus assigned ports
    _sEXODUS_INTS               EQU 12 * 8      ; Exodus assigned ints
    ;_sNOT_USED                                 ; available
    _sEXODUS_TSS                EQU 14 * 8      ; Exodus TSS
    _sEXODUS_TASK_GATE          EQU 15 * 8      ; Exodus kernel task gate (points to _sEXODUS_TSS)
    _sEXODUS_SLAVE_TSS          EQU 16 * 8      ; Exodus Slave TSS
    _sEXODUS_SLAVE_TASK_GATE    EQU 17 * 8      ; Exodus kernel slave task gate (points to _sEXODUS_SLAVE_TSS)
    ;_sNOT USED
    _sPRIMATIVES                EQU 19 * 8      ; Primative structure for natives
    _sPRIMATIVE_LOAD_INFO       EQU 20 * 8      ; Primative load information (for reporting on each driver)
    _sSYSTEM                    EQU 21 * 8      ; Exodus system memory
    _sEXODUS_REQUESTOR          EQU 22 * 8      ; Call gate to Exodus's requestor() function
    _sSYSTEM_RING1              EQU 23 * 8      ; Exodus system memory for ring-1 apps
    _sSYSTEM_RING2              EQU 24 * 8      ; Exodus system memory for ring-2 apps
    _sSYSTEM_RING3              EQU 25 * 8      ; Exodus system memory for ring-3 apps
    _sDEBI_screen               EQU 26 * 8      ; low-level DEBI debugger's save screen buffer
    _sDEBI_memory               EQU 27 * 8      ; low-level DEBI debugger's memory
    _sFLOPPY_TRACK              EQU 28 * 8      ; Floppy disk data I/O for one full track
    _sVGA_BACKUP                EQU 29 * 8      ; VGA video (060000h, used when in a graphics mode so writes
                                                ;  to the text screen are still valid)
    _sDEBI_screen2              EQU 30 * 8      ; low-level DEBI debugger's save screen buffer2 (for popups and menus)
    _sDEBI_temp                 EQU 31 * 8      ; low-level DEBI debugger's temporary selector (used for various things)
    _sEXODUS_OBJECTS            EQU 32 * 8      ; Exodus objects
    _sTASK_SWITCH_TSS           EQU 33 * 8      ; Task Manager's switch_task() function
    _sTASK_SWITCH_TASK_GATE     EQU 34 * 8      ; Task Manager's task gate (points to _sTASK_SWITCH_TSS)
    _sTASK_STACK                EQU 35 * 8      ; Task Manger task's stack
    _sSTACK0                    EQU 36 * 8      ; Exodus Stack 0
    _sSTACK1                    EQU 37 * 8      ; Exodus Stack 1
    _sSTACK2                    EQU 38 * 8      ; Exodus Stack 2
    _sDEBI_dt                   EQU 39 * 8      ; low-level DEBI debugger's DT storage
    _sDEBI_np                   EQU 40 * 8      ; low-level DEBI debugger's NP storage
    _sDEBI_rp                   EQU 41 * 8      ; low-level DEBI debugger's RP storage

  ; Variable base/limit GDT slots setup in INIT32.ASP
    _sEXODUS_INI                EQU 50 * 8      ; Holds the parsed EXODUS.INI sructure
    _sEXODUS_INI_ERRORS         EQU 51 * 8      ; Holds any errors found while parsing EXODUS.INI
    _sTASK_SYSTEM               EQU 52 * 8      ; Holds all tasks

    _cgTEMP_PRIMATIVE_MAIN      EQU 2996 * 8
    _cgTEMP_PRIMATIVE_REQUESTOR EQU 2997 * 8
    _csTEMP_PRIMATIVE           EQU 2998 * 8
    _dsTEMP_PRIMATIVE           EQU 2999 * 8



; ÚÄÄÄÄÄÄÄÄÄÄÄ¿
; ³ CONSTANTS ³
; ÀÄÄÄÄÄÄÄÄÄÄÄÙ
    _MIN_PRIMATIVE              EQU 200                             ; Start of the primatives
    _MAX_PRIMATIVE              EQU 2995                            ; End of the primatives
    _lastGDT                    EQU 4095                            ; Last valid GDT in the GDT
    _firstASSIGNMENT            EQU 50                              ; The first Exodus assigned GDT entry for various items
    _lastASSIGNMENT             EQU 199                             ; The last Exodus assigned GDT entry for various items
    _firstUSER_ASSIGNMENT       EQU 3000
    _lastUSER_ASSIGNMENT        EQU 4095
    _sGDT_init                  EQU 199                             ; Only initialize the first 199 GDT entries


  ; Required memory structures for Exodus
  ; Refer to Bootup(internal) document for definitive memory locations
    _sIDT_base                  EQU 8a000h
    _sIDT_limit                 EQU 800h
    _sGDT_base                  EQU 0800h
    _sGDT_limit                 EQU 8000h
    _sSTACK_base                EQU 98000h
    _sSTACK_limit               EQU 8000h
    _sCODE_base                 EQU 10000h
    _sCODE_limit                EQU 40000h
    _sDATA_base                 EQU 10000h
    _sDATA_limit                EQU 30000h
    _sGRAPHICS_base             EQU 0a0000h
    _sGRAPHICS_limit            EQU 10000h
    _sMONO_base                 EQU 0b0000h
    _sMONO_limit                EQU 8000h
    _sVGA_base                  EQU 0b8000h     ; Also, see _sVGA_BACKUP_ below
    _sVGA_limit                 EQU 8000h
    _sALL_MEM_base              EQU 0
    _sALL_MEM_limit             EQU 0ffffffffh
    _sEXODUS_MEM_base           EQU 70c00h
    _sEXODUS_MEM_limit          EQU 4000h
    _sEXODUS_PORTS_base         EQU 6cc00h
    _sEXODUS_PORTS_limit        EQU 4000h
    _sEXODUS_INTS_base          EQU 97e00h
    _sEXODUS_INTS_limit         EQU 200h
    _sEXODUS_TSS_base           EQU 68100h
    _sEXODUS_TSS_limit          EQU 100h        ; 256 bytes
   ;_sEXODUS_TASK_GATE          EQU task gate pointing to _sEXODUS_TSS
    _sEXODUS_SLAVE_TSS_base     EQU 68200h
    _sEXODUS_SLAVE_TSS_limit    EQU 100h        ; 256 bytes
    _sPRIMATIVES_base           EQU 8d380h
    _sPRIMATIVES_limit          EQU 4000h       ; 16k
    _sPRIMATIVE_LOAD_INFO_base  EQU 8c380h
    _sPRIMATIVE_LOAD_INFO_limit EQU 1000h       ; 4k
    _sSYSTEM_base               EQU 89400h
    _sSYSTEM_limit              EQU 0c00h       ; 3k
    _sSYSTEM_USER_limit         EQU 0800h       ; 2k
    _sDEBI_screen_base          EQU 281400h                         ; ; ; ; ; Added 2 MB, 02/26/2009 - RCH
    _sDEBI_screen_limit         EQU 8000h       ; 32k
    _sDEBI_memory_base          EQU 279400h                         ; ; ; ; ; Added 2 MB, 02/26/2009 - RCH
    _sDEBI_memory_limit         EQU 8000h       ; 32k
    _sFLOPPY_TRACK_base         EQU 74c00h
    _sFLOPPY_TRACK_limit        EQU 4800h       ; 512 bytes per sector * 18 sectors * 2 sides = 18k
    _sVGA_BACKUP_base           EQU 60000h      ; Note, the backup area is used when in graphics modes that use a0000h
    _sVGA_BACKUP_limit          EQU 8000h       ; so all video writes to the text window are still saved
    _sDEBI_screen2_base         EQU 258000h
    _sDEBI_screen2_limit        EQU 28000h       ; 32k
    _sTASK_SWITCH_TSS_base      EQU 68000h
    _sTASK_SWITCH_TSS_limit     EQU 100h        ; 256 bytes
    _sTASK_STACK_base           EQU 220000h                         ; ; ; ; ; Added 1 MB, 03/01/2009 - RCH
    _sTASK_STACK_limit          EQU 8000h       ; 32k
    _sSTACK0_base               EQU 95380h
    _sSTACK0_limit              EQU 2000h       ; 8k
    _sSTACK1_base               EQU 93380h
    _sSTACK1_limit              EQU 2000h       ; 8k
    _sSTACK2_base               EQU 91380h
    _sSTACK2_limit              EQU 2000h       ; 8k
    _sDEBI_dt_base              EQU 240000h                         ; ; ; ; ; Added 1 MB, 03/01/2009 - RCH
    _sDEBI_dt_limit             EQU 8000h       ; 32k
    _sDEBI_np_base              EQU 248000h                         ; ; ; ; ; Added 1 MB, 03/01/2009 - RCH
    _sDEBI_np_limit             EQU 8000h       ; 32k
    _sDEBI_rp_base              EQU 250000h                         ; ; ; ; ; Added 1 MB, 03/01/2009 - RCH
    _sDEBI_rp_limit             EQU 8000h       ; 32k

    _sEXODUS_OBJECTS_base       EQU 50000h
    _sEXODUS_OBJECTS_limit      EQU 8000h       ; 32k
    _sEXODUS_INI_base           EQU 200000h     ; 1MB               ; ; ; ; ; Added 1 MB, 03/01/2009 - RCH
    _sEXODUS_INI_limit          EQU 10000h      ; 64k
    _sEXODUS_INI_ERRORS_base    EQU 210000h     ; 1MB + 64k         ; ; ; ; ; Added 1 MB, 03/01/2009 - RCH
    _sEXODUS_INI_ERRORS_limit   EQU 4000h       ; 16k
    _sTASK_SYSTEM_base          EQU 210000h     ; 1MB + 64k         ; ; ; ; ; Added 1 MB, 03/01/2009 - RCH
    _sTASK_SYSTEM_limit         EQU 010000h     ; 64k


; ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
; ³ BOOT DT STRUCTURE ³
; ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
    _BOOT_DT_object_type        EQU 0
    _BOOT_DT_days               EQU 1
    _BOOT_DT_seconds            EQU 5
    _BOOT_DT_rp_offset          EQU 8
    _BOOT_DT_entry_type         EQU 10
    _BOOT_DT_np_offset          EQU 11


; ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
; ³ BOOT RP STRUCTURE ³
; ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
    _BOOT_RP_length				EQU 0
    _BOOT_RP_requestor			EQU 4
    _BOOT_RP_main				EQU 8
;; For original version using head/track/sector
	_BOOT_RP_start_head			EQU	12
	_BOOT_RP_start_track		EQU	13
	_BOOT_RP_start_sector		EQU	14
	_BOOT_RP_end_head			EQU	16
	_BOOT_RP_end_track			EQU	17
	_BOOT_RP_end_sector			EQU	18
;; For new version using linear disk offsets
    _BOOT_RP_disk_offset		EQU 12
	_BOOT_RP_nuserved			EQU 16 



; ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
; ³ BOOT PARAMETER BLOCK STRUCTURE ³
; ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
    _BOOT_PB_size               EQU 0
    _BOOT_PB_main               EQU 4
    _BOOT_PB_requestor          EQU 8
    _BOOT_PB_start_head         EQU 12
    _BOOT_PB_start_track        EQU 13
    _BOOT_PB_start_sector       EQU 14
    _BOOT_PB_end_head           EQU 16
    _BOOT_PB_end_track          EQU 17
    _BOOT_PB_end_sector         EQU 18
    _BOOT_PB_entry_type         EQU 20
    _BOOT_PB_linear_offset      EQU 22
    _BOOT_PB_dt_offset          EQU 26
    _BOOT_PB_crc16              EQU 28
    _BOOT_PB_structure_size     EQU 32




; ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
; ³ EXODUS.INI STRUCTURES ³
; ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
    _EXODUS_INI_FIRST_BRACKET       EQU 0
    _EXODUS_INI_TOTAL_BYTES         EQU 4
    _EXODUS_INI_TOTAL_BRACKET_GROUPS EQU 8
    _EXODUS_INI_TOTAL_PAREN_CASKS   EQU 12
    _EXODUS_INI_HEADER_LENGTH       EQU 16

    _EXODUS_BRACKET_NEXT            EQU 0
    _EXODUS_BRACKET_PAREN_CASKS     EQU 4
    _EXODUS_BRACKET_TOTAL_PARENS    EQU 8
    _EXODUS_BRACKET_NAME            EQU 12
    _EXODUS_BRACKET_HANDLE          EQU 16
    _EXODUS_BRACKET_REQUESTOR       EQU 20
    _EXODUS_BRACKET_REQUESTOR_FUNC  EQU 22
    _EXODUS_BRACKET_SCRATCH_AREA    EQU 26
    _EXODUS_BRACKET_LENGTH          EQU 30

    _EXODUS_PAREN_NEXT              EQU 0
    _EXODUS_PAREN_NEXT_SAME_LINE    EQU 4
    _EXODUS_PAREN_DATA_ITEMS        EQU 8
    _EXODUS_PAREN_TOTAL_DATA_ITEMS  EQU 12
    _EXODUS_PAREN_SOURCE_LINE       EQU 16
    _EXODUS_PAREN_SOURCE_LINE_LENGTH EQU 20
    _EXODUS_PAREN_HANDLE            EQU 24
    _EXODUS_PAREN_REQUESTOR         EQU 26
    _EXODUS_PAREN_REQUESTOR_FUNC    EQU 30
    _EXODUS_PAREN_SCRATCH_AREA      EQU 34
    _EXODUS_PAREN_LENGTH            EQU 38

    _EXODUS_DATA_NEXT               EQU 0
    _EXODUS_DATA_DATA_ITEM_SOURCE   EQU 4
    _EXODUS_DATA_DATA_ITEM_LENGTH   EQU 8
    _EXODUS_DATA_LENGTH             EQU 12




; ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
; ³ EXODUS xxx STRUCTURES ³
; ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
    _EXODUS_MEM_type                EQU 0
    _EXODUS_MEM_base                EQU 4
    _EXODUS_MEM_limit               EQU 8
    _EXODUS_MEM_gdt                 EQU 12
    _EXODUS_MEM_ldt                 EQU 14
    _EXODUS_MEM_size                EQU 16

    _EXODUS_PORTS_size              EQU 16

    _EXODUS_INTS_size               EQU 2




; ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
; ³ EXODUS SYSTEM MEMORY ³
; ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
; Note, when updates are made here they need to be reflected in INF\SYSTEM.INF
; Note, when updates are made here and INF\SYSTEM.INF, the "Exodus Quick Reference" manual needs to be updated
    _SYSTEM_SECONDS_SINCE_BOOTUP    EQU 0                           ; dword
    _SYSTEM_SECONDS_SINCE_MIDNIGHT  EQU 4                           ; dword
    _SYSTEM_HOURS                   EQU 8                           ; byte
    _SYSTEM_MINUTES                 EQU 9                           ; byte
    _SYSTEM_SECONDS                 EQU 10                          ; byte
    _SYSTEM_182S_OF_A_SECOND        EQU 11                          ; byte
    _SYSTEM_DAY                     EQU 12                          ; byte
    _SYSTEM_MONTH                   EQU 13                          ; byte
    _SYSTEM_YEAR                    EQU 14                          ; word
    _SYSTEM_DAY_OF_YEAR             EQU 16                          ; word
    _SYSTEM_BUILD                   EQU 18                          ; 10-byte string in the format: "mm.dd.yyyy"
    _SYSTEM_TOTAL_MEMORY            EQU 28                          ; dword, total ram in bytes
    _SYSTEM_VGA_HORIZONTAL          EQU 32                          ; word (pixels-graphics, or columns-text)
    _SYSTEM_VGA_VERTICAL            EQU 34                          ; word (pixels-graphics, or rows-text)
    _SYSTEM_VGA_VIDEO_MODE          EQU 36                          ; byte (0-graphics, 1-text)
    _SYSTEM_MONO_VIDEO_MODE         EQU 37                          ; byte (0-graphics, 1-text, 0ffh-Unknown)

  ; Non-user accessible system memory areas (Exodus internal, hence the use of the _i_)
    _SYSTEM_i_FATAL                 EQU 2048                        ; dword
    _SYSTEM_i_TASKS_CREATED         EQU 2052                        ; dword
    _SYSTEM_i_TASKS_BY_USER         EQU 2056                        ; dword
    _SYSTEM_i_TASKS_BY_ERROR        EQU 2060                        ; dword
    _SYSTEM_i_IRQ6_INDICATOR        EQU 2064                        ; byte, IRQ6 indicator (changes each time an IRQ6 is signaled)
    _SYSTEM_i_IRQ6_INDICATOR_LAST   EQU 2065                        ; byte, IRQ6 indicator previous, used to see when an IRQ6 is signaled
    _SYSTEM_i_BASE                  EQU 2066                        ; dword
    _SYSTEM_i_LIMIT                 EQU 2070                        ; dword
    _SYSTEM_i_DWORD_TO_COPY         EQU 2074                        ; word
    _SYSTEM_i_LAST_GDT_REFERENCED   EQU 2076                        ; qword
    _SYSTEM_i_CODE_GDT_OFFSET       EQU 2084                        ; dword (used temporarily during native primative install)
    _SYSTEM_i_DATA_GDT_OFFSET       EQU 2088                        ; dword (used temporarily during native primative install)
    _SYSTEM_i_MAIN_GDT_OFFSET       EQU 2092                        ; dword (used temporarily during native primative install)
    _SYSTEM_i_REQUESTOR_GDT_OFFSET  EQU 2096                        ; dword (used temporarily during native primative install)
    _SYSTEM_i_GDT_TO_ASSIGN         EQU 2100                        ; word (used various places to assign GDT entries)
    _SYSTEM_i_USER_GDT_TO_ASSIGN    EQU 2102                        ; word (used various places to assign USER Program GDTs)
  ; Next offset is 2104


  ; These scratch items exist from end of memory down
    _SYSTEM_i_SCRATCH_DWORD2        EQU 3064                        ; dword (used various places as a scratch buffer)
    _SYSTEM_i_SCRATCH_DWORD1        EQU 3068                        ; dword (used various places as a scratch buffer)




; ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
; ³ BOCHS SUPPORT ³
; ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
; These equates are used to communicate via INT 0FFh
; Values here are in ecx, with edx being used for data information.
; Values in eax must be
    _BOCHS1                         EQU 12345678h
    _BOCHS2                         EQU 87654321h
    _BOCHS_GET_MONO_MOUSE_XY        EQU 0
    _BOCHS_GET_MONO_CURSOR          EQU 1
