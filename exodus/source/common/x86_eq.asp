; x86_eq.asp
;
; Constants specific to the Intel architecture
;



_TSS_BACK_LINK              EQU 0
_TSS_ESP0                   EQU 4
_TSS_SS0                    EQU 8
_TSS_ESP1                   EQU 12
_TSS_SS1                    EQU 16
_TSS_ESP2                   EQU 20
_TSS_SS2                    EQU 24
_TSS_CR3                    EQU 28
_TSS_EIP                    EQU 32
_TSS_EFLAGS                 EQU 36
_TSS_EAX                    EQU 40
_TSS_ECX                    EQU 44
_TSS_EDX                    EQU 48
_TSS_EBX                    EQU 52
_TSS_ESP                    EQU 56
_TSS_EBP                    EQU 60
_TSS_ESI                    EQU 64
_TSS_EDI                    EQU 68
_TSS_ES                     EQU 72
_TSS_CS                     EQU 76
_TSS_SS                     EQU 80
_TSS_DS                     EQU 84
_TSS_FS                     EQU 88
_TSS_GS                     EQU 92
_TSS_LDT                    EQU 96
_TSS_TRAP_BIT               EQU 100
_TSS_TRAP_BIT_MASK          EQU 1b
_TSS_IO_MAP                 EQU 102
; The following area is used by Exodus.  It appears immediate after the TSS in memory
_TSS_FPU_SAVE_AREA          EQU 104


; EFLAGS register constants to access individual flags
_EFLAGS_CF                  EQU 0
_EFLAGS_PF                  EQU 2
_EFLAGS_ACF                 EQU 4
_EFLAGS_ZF                  EQU 6
_EFLAGS_SF                  EQU 7
_EFLAGS_TF                  EQU 8
_EFLAGS_IF                  EQU 9
_EFLAGS_DF                  EQU 10
_EFLAGS_OF                  EQU 11
_EFLAGS_IOPL                EQU 12
_EFLAGS_NT                  EQU 14
_EFLAGS_RF                  EQU 16
_EFLAGS_VM                  EQU 17
; Masks to access specific bits
_EFLAGS_CF_MASK             EQU  1b SHL _EFLAGS_CF
_EFLAGS_PF_MASK             EQU  1b SHL _EFLAGS_PF
_EFLAGS_ACF_MASK            EQU  1b SHL _EFLAGS_ACF
_EFLAGS_ZF_MASK             EQU  1b SHL _EFLAGS_ZF
_EFLAGS_SF_MASK             EQU  1b SHL _EFLAGS_SF
_EFLAGS_TF_MASK             EQU  1b SHL _EFLAGS_TF
_EFLAGS_IF_MASK             EQU  1b SHL _EFLAGS_IF
_EFLAGS_DF_MASK             EQU  1b SHL _EFLAGS_DF
_EFLAGS_OF_MASK             EQU  1b SHL _EFLAGS_OF
_EFLAGS_IOPL_MASK           EQU 11b SHL _EFLAGS_IOPL
_EFLAGS_NT_MASK             EQU  1b SHL _EFLAGS_NT
_EFLAGS_RF_MASK             EQU  1b SHL _EFLAGS_RF
_EFLAGS_VM_MASK             EQU  1b SHL _EFLAGS_VM

_CW_INFINITY                EQU 1000000000000b
_CW_ROUNDING                EQU  110000000000b
_CW_ROUNDING_00             EQU  000000000000b
_CW_ROUNDING_01             EQU  010000000000b
_CW_ROUNDING_10             EQU  100000000000b
_CW_ROUNDING_11             EQU  110000000000b
_CW_PRECISION               EQU    1100000000b
_CW_PRECISION_00            EQU    0000000000b
_CW_PRECISION_01            EQU    0100000000b
_CW_PRECISION_10            EQU    1000000000b
_CW_PRECISION_11            EQU    1100000000b
_CW_PM                      EQU        100000b
_CW_UM                      EQU         10000b
_CW_OM                      EQU          1000b
_CW_ZM                      EQU           100b
_CW_DM                      EQU            10b
_CW_IM                      EQU             1b

_SW_BUSY                    EQU 1000000000000000b
_SW_C3                      EQU  100000000000000b
_SW_TOS                     EQU   11100000000000b
_SW_C2                      EQU      10000000000b
_SW_C1                      EQU       1000000000b
_SW_C0                      EQU        100000000b
_SW_ERROR_SUMMARY           EQU         10000000b
_SW_STACK_FAULT             EQU          1000000b
_SW_PE                      EQU           100000b
_SW_UE                      EQU            10000b
_SW_OE                      EQU             1000b
_SW_ZE                      EQU              100b
_SW_DE                      EQU               10b
_SW_IE                      EQU                1b