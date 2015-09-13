; debi_eq.asp
;
; Low-Level Debi Debugger constant equates
;
;






OFF                         EQU 0
ON                          EQU -1

_NO                         EQU 0
_YES                        EQU 1

; Used by invDEBI_parse_expression()
_SEGMENT                    EQU 0
_OFFSET                     EQU 1
_DISP                       EQU 2
; Last encountered operators
_NONE                       EQU 0
_ADDITION                   EQU 1
_MULTIPLICATION             EQU 2
_DIVISION                   EQU 3
_SUBTRACTION                EQU 4
_SHIFT_RIGHT                EQU 5
_SHIFT_LEFT                 EQU 6


; Pixel equates
FONT_X                      EQU 8                                   ; pixels per character horizontally
FONT_Y                      EQU 6                                   ; pixels per character vertically
_IMMEDIATE_COUNT            EQU 2


; Constant structure lengths
_ST_OBJECT_SCREEN_WIDTH     EQU -4                                  ; These two were added later.  They represent the size of a
_ST_OBJECT_SCREEN_HEIGHT    EQU -2                                  ; window (used when dragging to pick up the whole window)
_ST_OBJECT_ALTERABLE        EQU 0                                   ; Can item be moved/deleted on screen?
_ST_OBJECT_ACTIVE           EQU 1
;                           EQU 2                                   ; +--Nuserved,2
_ST_OBJECT_UL_HORIZONTAL    EQU 4                                   ; +_ST_OBJECT_UL_HORIZONTAL, ul-Horizontal
_ST_OBJECT_UL_VERTICAL      EQU 8                                   ; +_ST_OBJECT_UL_VERTICAL,   ul-Vertical
_ST_MEMVAR_OFFSET           EQU 12                                  ; +_ST_MEMVAR_OFFSET,        offsets to memory variables used
_ST_OBJECT_KBD_OFFSET       EQU 16                                  ; +_ST_OBJECT_KBD_OFFSET,    object's keyboard objects
_ST_OBJECT_MEMORY_OFFSET    EQU 20                                  ; +_ST_OBJECT_MEMORY_OFFSET, Starting offset in DEBI mem space
_ST_OBJECT_MOUSE_OFFSET     EQU 24                                  ; +_ST_OBJECT_MOUSE_OFFSET,  object's mouse objects
_ST_OBJECT_SCREEN_OFFSET    EQU 28                                  ; +_ST_OBJECT_SCREEN_OFFSET, object's screen objects
_ST_LENGTH                  EQU 32

; Used only on menu items
_ST_OBJECT_WIDTH            EQU 12
_ST_OBJECT_HEIGHT           EQU 16


; MEMVAR structure offsets
_MEMVAR_MEMORY_VARIABLE     EQU 0
_MEMVAR_LENGTH              EQU 4
_MEMVAR_STRUCT_LENGTH       EQU 8


; Mouse object structure offsets
_MO_OBJECT_TYPE             EQU 0
_MO_X1                      EQU 1
_MO_Y1                      EQU 5
_MO_X2                      EQU 9
_MO_Y2                      EQU 13
_MO_FUNC                    EQU 17
_MO_DATA                    EQU 21
_MO_DATA1                   EQU 21
_MO_DATA2                   EQU 25
_MO_DATA3                   EQU 27
_MO_TYPE                    EQU 27
_MO_LENGTH                  EQU 28

; Keyboard object structure offsets
_KO_OBJECT_TYPE             EQU 0
_KO_X                       EQU 1
_KO_Y                       EQU 5
_KO_LEN                     EQU 9
_KO_LENGTH                  EQU 24

; Textbox and checkbox specific
_KO_VAR                     EQU 13

; Checkbox and button specific
_KO_X_OFFSET                EQU 17

; Button specific
_KO_FUNC                    EQU 13

; Function specific
_KO_X_FUNCTION              EQU 1
_KO_Y_FUNCTION              EQU 3
_KO_MOUSE_FUNCTION          EQU 5
_KO_KBD_FUNCTION            EQU 9
_KO_REFRESH_FUNCTION        EQU 13
_KO_ACTIVATE_FUNCTION       EQU 17

; Object types for keyboard objects
_KO_TEXTBOX                 EQU 0
_KO_CHECKBOX                EQU 1
_KO_BUTTON                  EQU 2
_KO_FUNCTION                EQU 254


; Object types for menu objects
_MENU_ITEM                  EQU 0
_MENU_ITEM_EVENT            EQU 1
_MENU_BAR                   EQU 2


; Object offsets for DEBI keyboard objects (These are the offsets to the @DEBI_* macros in DEBI_MAC.ASP)
_DEBI_ID                    EQU 0
_DEBI_X                     EQU 1
_DEBI_Y                     EQU 5
_DEBI_LEN                   EQU 9
_DEBI_VAR                   EQU 13
_DEBI_FUNC                  EQU 17
_DEBI_RESERVED              EQU 21

; Object types for mouse objects
_LEFT_SINGLE_CLICK          EQU 0
_LEFT_DOUBLE_CLICK          EQU 1
_LEFT_DRAG_START            EQU 2
_LEFT_DRAG_STOP             EQU 3
_RIGHT_SINGLE_CLICK         EQU 4
_RIGHT_DOUBLE_CLICK         EQU 5
_RIGHT_DRAG_START           EQU 6
_RIGHT_DRAG_STOP            EQU 7
_BOTH_SINGLE_CLICK          EQU 8
_BOTH_DOUBLE_CLICK          EQU 9
_HOVER                      EQU 10
_EDIT                       EQU 11
_ABANDON_IF_NOT             EQU 12
_ANY_CLICK                  EQU 13
_IMMEDIATE                  EQU 14

; Object types for screen objects
_OBJECT_MEM_SIZE            EQU 0
_OBJECT_MEM_DEFAULT         EQU 1
_LOAD_TEMP                  EQU 2
_DISPLAY                    EQU 3
_INPUT                      EQU 4
_POST_DISPLAY               EQU 5
_POST_OBJECT                EQU 6
_FUNCTION                   EQU 7
_START                      EQU 252
_DRAW_WINDOW                EQU 253
_DRAW_WINDOW_ALWAYS         EQU 254
_END                        EQU 255

; Address defaults
_ADDRESS_PARSE              EQU 0               ; Stored as 4 bytes pointing to an expression in input_field_area
; Offset defaults
_OFFSET_LINEAR              EQU 1


; _LOAD_TEMP classes
_FAR_MEMORY_PTR             EQU 0


; _LOAD_TEMP types
_RAW_ADDRESS                EQU 0


; Parse expression constants
_CS                         EQU 0
_DS                         EQU 1
_ES                         EQU 2
_FS                         EQU 3
_GS                         EQU 4
_SS                         EQU 5
_AL                         EQU 6
_AH                         EQU 7
_AX                         EQU 8
_EAX                        EQU 9
_BL                         EQU 10
_BH                         EQU 11
_BX                         EQU 12
_EBX                        EQU 13
_CL                         EQU 14
_CH                         EQU 15
_CX                         EQU 16
_ECX                        EQU 17
_DL                         EQU 18
_DH                         EQU 19
_DX                         EQU 20
_EDX                        EQU 21
_SI                         EQU 22
_ESI                        EQU 23
_DI                         EQU 24
_EDI                        EQU 25
_IP                         EQU 26
_EIP                        EQU 27
_BP                         EQU 28
_EBP                        EQU 29
_SP                         EQU 30
_ESP                        EQU 31
_EFLAGS                     EQU 32
_ECODE                      EQU 33


; DEBI_debug() references to interrupted program's values on the stack
_STACK_EFLAGS               EQU 60
_STACK_CS                   EQU 56
_STACK_EIP                  EQU 52
_STACK_IP                   EQU 52
_STACK_ERROR_CODE           EQU 48
_STACK_EAX                  EQU 44
_STACK_AX                   EQU 44
_STACK_AL                   EQU 44
_STACK_AH                   EQU 45
_STACK_EBX                  EQU 40
_STACK_BX                   EQU 40
_STACK_BL                   EQU 40
_STACK_BH                   EQU 41
_STACK_ECX                  EQU 36
_STACK_CX                   EQU 36
_STACK_CL                   EQU 36
_STACK_CH                   EQU 37
_STACK_EDX                  EQU 32
_STACK_DX                   EQU 32
_STACK_DL                   EQU 32
_STACK_DH                   EQU 33
_STACK_ESI                  EQU 28
_STACK_SI                   EQU 28
_STACK_EDI                  EQU 24
_STACK_DI                   EQU 24
_STACK_DS                   EQU 20
_STACK_ES                   EQU 16
_STACK_FS                   EQU 12
_STACK_GS                   EQU 08
_STACK_SS                   EQU 04
_STACK_EBP                  EQU 00
_STACK_BP                   EQU 00
_STACK_ESP                  EQU -4
_STACK_SP                   EQU -4


; _DISPLAY classes
_TEMP_RELATIVE              EQU 0
_EBP_RELATIVE               EQU 1
_EBP_THROUGH_EBP_RELATIVE   EQU 2
_ESP_THROUGH_EBP_RELATIVE   EQU 3
_EBP_RELATIVE_EFLAG         EQU 4


; _DISPLAY types
_UPPER_NIBBLE               EQU 0               ; upper nibble
_LOWER_NIBBLE               EQU 1               ; lower nibble
_LOWER_NIBBLE3              EQU 2               ; least significant 3 bits of lower nibble
_8                          EQU 3               ; 8-bit value in xx form
_16                         EQU 4               ; 16-bit value in xxxx form
_32                         EQU 5               ; 32-bit value in xxxxxxxx form
_BINARY8                    EQU 6
_BINARY11                   EQU 7
_BINARY16                   EQU 8
_BINARY32                   EQU 9
_IEEE_80                    EQU 10
_TBYTE                      EQU 11
_ADJ_FLOAT14                EQU 12
_ADJ_FLOAT20                EQU 13
_ADJ_FLOAT21                EQU 14
_FPU_OPCODE                 EQU 15