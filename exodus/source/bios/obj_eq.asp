; obj_eq.asp
;
; Exodus Object System constant equates
;
;  ⁄ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒø
;  ¥-=-=-=- NOTE! -=-=-=-≥
;  ¿√√√√√√√√√√√√√√√√√√√√√Ÿ
;   Any changes made to this program need to be applied to COMMON\OBJ_MAC.ASP
;
; Base Objects:
;   _DESKTOP
;
; Objects:
;   _TEXT_FIELD
;   _HLINE
;   _RECTANGLE
;   _BORDER_BOX
;



; Object header constants
_OBJECT_HEADER_NEXT_OBJECT          EQU 0
_OBJECT_HEADER_FIRST_BASE_OBJECT    EQU 4
_OBJECT_HEADER_FIRST_OBJECT         EQU 8
_FIRST_OBJECT                       EQU 16                          ; Offset where the first object records are



; Object structure constants (offsets to obtain these variablse within the structures)
; Common to all:
_OBJECT_NEXT_BASE_OBJECT        EQU 0
_BASE_OBJECT_TYPE               EQU 4                               ; These two are the same thing, just different names for
_OBJECT_TYPE                    EQU 4                               ;  whatever use they're associated with
_OBJECT_FIRST_OBJECT            EQU 8                               ; Used on base objects for first object
_OBJECT_NEXT_OBJECT             EQU 8                               ; Used on objects to point to the next object
_OBJECT_FIXED_LENGTH            EQU 12

_BO_TOP                         EQU 12
_BO_LEFT                        EQU 16
_BO_LENGTH                      EQU 256
_O_LENGTH                       EQU 256

; _GROUPING
_BO_G_                          EQU


; _DESKTOP
; This structure represents how this object is stored within this task's OBJECT structure area
; Properties
_BO_D_TOP                       EQU 12
_BO_D_LEFT                      EQU 16
_BO_D_WIDTH                     EQU 20
_BO_D_HEIGHT                    EQU 24
_BO_D_ENABLED                   EQU 28
_BO_D_VISIBLE                   EQU 29
_BO_D_BACKGROUND                EQU 30
_BO_D_ICON_HORIZONTAL           EQU 33
_BO_D_ICON_VERTICAL             EQU 34
_BO_D_MENU_POSITION             EQU 35
_BO_D_MENU_HEIGHT               EQU 36
_BO_D_WALLPAPER                 EQU 38
_BO_D_MISC_1                    EQU 40
_BO_D_MISC_2                    EQU 44
_BO_D_MISC_3                    EQU 48
_BO_D_MISC_4                    EQU 52
_BO_D_MISC_FLAG_1               EQU 56
_BO_D_MISC_FLAG_2               EQU 57
_BO_D_MISC_FLAG_3               EQU 58
_BO_D_MENU_AUTOHIDE             EQU 59
; Events
_BO_D_ACTIVATE                  EQU 128
_BO_D_CLICK_BOTH_SINGLE         EQU 132
_BO_D_CLICK_BOTH_DOUBLE         EQU 136
_BO_D_CLICK_LEFT_SINGLE         EQU 140
_BO_D_CLICK_LEFT_DOUBLE         EQU 144
_BO_D_CLICK_LEFT_DOWN           EQU 148
_BO_D_CLICK_LEFT_UP             EQU 152
_BO_D_CLICK_RIGHT_SINGLE        EQU 156
_BO_D_CLICK_RIGHT_DOUBLE        EQU 160
_BO_D_CLICK_RIGHT_DOWN          EQU 164
_BO_D_CLICK_RIGHT_UP            EQU 168
_BO_D_DROPPED_INTO_LEFT         EQU 172
_BO_D_DROPPED_INTO_RIGHT        EQU 176
_BO_D_DRAG_LEFT_START           EQU 180
_BO_D_DRAG_LEFT_STOP            EQU 184
_BO_D_DRAG_RIGHT_START          EQU 188
_BO_D_DRAG_RIGHT_STOP           EQU 192
_BO_D_FOCUS_GOT                 EQU 196
_BO_D_FOCUS_LOST                EQU 200
_BO_D_FOCUS_SET                 EQU 204
_BO_D_HOVER                     EQU 208
_BO_D_KEYSTROKE                 EQU 212
_BO_D_WHEN_CREATED              EQU 216
_BO_D_WHEN_DESTROYED            EQU 220
_BO_D_REQUESTOR                 EQU 224
_BO_D_REFRESH                   EQU 228
; Input data structures
_BO_LD_TYPE                     EQU 0
_BO_LD_TOP                      EQU 1
_BO_LD_LEFT                     EQU 5
_BO_LD_WIDTH                    EQU 9
_BO_LD_HEIGHT                   EQU 13
_BO_LD_LENGTH                   EQU 17
; Properties
_BO_LD_ENABLED                  EQU 1
_BO_LD_VISIBLE                  EQU 1
_BO_LD_BACKGROUND_RED           EQU 1
_BO_LD_BACKGROUND_GREEN         EQU 2
_BO_LD_BACKGROUND_BLUE          EQU 3
_BO_LD_ICON_HORIZONTAL          EQU 1
_BO_LD_ICON_VERTICAL            EQU 1
_BO_LD_MENU_POSITION            EQU 1
_BO_LD_MENU_HEIGHT              EQU 1
_BO_LD_MENU_AUTOHIDE            EQU 1
_BO_LD_MISC_1                   EQU 1
_BO_LD_MISC_2                   EQU 1
_BO_LD_MISC_3                   EQU 1
_BO_LD_MISC_4                   EQU 1
_BO_LD_MISC_FLAG_1              EQU 1
_BO_LD_MISC_FLAG_2              EQU 1
_BO_LD_MISC_FLAG_3              EQU 1
_BO_LD_WALLPAPER                EQU 1
; Sizes
_BO_LD_ENABLED_SIZE             EQU 2
_BO_LD_VISIBLE_SIZE             EQU 2
_BO_LD_BACKGROUND_SIZE          EQU 4
_BO_LD_ICON_HORIZONTAL_SIZE     EQU 2
_BO_LD_ICON_VERTICAL_SIZE       EQU 2
_BO_LD_MENU_POSITION_SIZE       EQU 2
_BO_LD_MENU_HEIGHT_SIZE         EQU 2
_BO_LD_MENU_AUTOHIDE_SIZE       EQU 2
_BO_LD_MISC_1_SIZE              EQU 5
_BO_LD_MISC_2_SIZE              EQU 5
_BO_LD_MISC_3_SIZE              EQU 5
_BO_LD_MISC_4_SIZE              EQU 5
_BO_LD_MISC_FLAG_1_SIZE         EQU 2
_BO_LD_MISC_FLAG_2_SIZE         EQU 2
_BO_LD_MISC_FLAG_3_SIZE         EQU 2
_BO_LD_WALLPAPER_SIZE           EQU 5


; _WINDOW
_BO_W_                          EQU


; _CONSOLE
_BO_C_                          EQU


; _TEXT_MODE
_BO_T_                          EQU


; _MONO_DESKTOP
_BO_MD_                         EQU


; _MONO_WINDOW
_BO_MW_                         EQU


; _MONO_CONSOLE
_BO_MC_                         EQU


; _MONO_TEXT_MODE
_BO_MT_                         EQU



;----------------------------------------
; Objects
;----------------------------------------

; _TEXT_FIELD
; Properties
_O_TF_TOP                       EQU 12
_O_TF_LEFT                      EQU 16
_O_TF_WIDTH                     EQU 20
_O_TF_HEIGHT                    EQU 24
_O_TF_BORDER                    EQU 28
_O_TF_ALIGNMENT                 EQU 29
_O_TF_AUTO_SIZE                 EQU 30
_O_TF_BACKGROUND                EQU 31
_O_TF_FOREGROUND                EQU 34
_O_TF_COLOR_SELECTED_BACKGROUND EQU
_O_TF_COLOR_SELECTED_FOREGROUND EQU
_O_TF_ENABLED                   EQU 37
_O_TF_SOURCE_PTR_SEGMENT        EQU 40
_O_TF_SOURCE_PTR_OFFSET         EQU 44
_O_TF_FONT_NAME                 EQU 48
_O_TF_FONT_SIZE                 EQU 52
_O_TF_FONT_TYPEFACE_BOLD        EQU 53
_O_TF_FONT_TYPEFACE_DITHER      EQU 54
_O_TF_FONT_TYPEFACE_ITALICS     EQU 55
_O_TF_FONT_TYPEFACE_REVERSE     EQU 56
_O_TF_FONT_TYPEFACE_STRIKETHROUGH EQU 57
_O_TF_FONT_TYPEFACE_UNDERLINE   EQU 58
_O_TF_VISIBLE                   EQU 59
_O_TF_FONT_NAME_ID              EQU 60
_O_TF_MARGIN_LEFT               EQU 64
_O_TF_MARGIN_TOP                EQU 66
_O_TF_SELECTED_TEXT_START       EQU
_O_TF_SELECTED_TEXT_END         EQU
_O_TF_MISC_1                    EQU 68
_O_TF_MISC_2                    EQU 72
_O_TF_MISC_3                    EQU 76
_O_TF_MISC_4                    EQU 80
_O_TF_MISC_FLAG_1               EQU 84
_O_TF_MISC_FLAG_2               EQU 85
_O_TF_MISC_FLAG_3               EQU 86
; Events
_O_TF_ACTIVATE                  EQU 128
_O_TF_CLICK_BOTH_SINGLE         EQU 132
_O_TF_CLICK_BOTH_DOUBLE         EQU 136
_O_TF_CLICK_LEFT_SINGLE         EQU 140
_O_TF_CLICK_LEFT_DOUBLE         EQU 144
_O_TF_CLICK_LEFT_DOWN           EQU 148
_O_TF_CLICK_LEFT_UP             EQU 152
_O_TF_CLICK_RIGHT_SINGLE        EQU 156
_O_TF_CLICK_RIGHT_DOUBLE        EQU 160
_O_TF_CLICK_RIGHT_DOWN          EQU 164
_O_TF_CLICK_RIGHT_UP            EQU 168
_O_TF_DROPPED_INTO_LEFT         EQU 172
_O_TF_DROPPED_INTO_RIGHT        EQU 176
_O_TF_DRAG_LEFT_START           EQU 180
_O_TF_DRAG_LEFT_STOP            EQU 184
_O_TF_DRAG_RIGHT_START          EQU 188
_O_TF_DRAG_RIGHT_STOP           EQU 192
_O_TF_FOCUS_GOT                 EQU 196
_O_TF_FOCUS_LOST                EQU 200
_O_TF_FOCUS_SET                 EQU 204
_O_TF_HOVER                     EQU 208
_O_TF_KEYSTROKE                 EQU 212
_O_TF_WHEN_CREATED              EQU 216
_O_TF_WHEN_DESTROYED            EQU 220
_O_TF_REQUESTOR                 EQU 224
_O_TF_REFRESH                   EQU 228
; Input data structures
_O_LTF_TYPE                     EQU 0
_O_LTF_TOP                      EQU 1
_O_LTF_LEFT                     EQU 5
_O_LTF_WIDTH                    EQU 9
_O_LTF_HEIGHT                   EQU 13
_O_LTF_LENGTH                   EQU 17
; Properties
_O_LTF_ENABLED                  EQU 1
_O_LTF_VISIBLE                  EQU 1
_O_LTF_BORDER                   EQU 1
_O_LTF_ALIGNMENT                EQU 1
_O_LTF_AUTO_SIZE                EQU 1
_O_LTF_BACKGROUND_RED           EQU 1
_O_LTF_BACKGROUND_GREEN         EQU 2
_O_LTF_BACKGROUND_BLUE          EQU 3
_O_LTF_FOREGROUND_RED           EQU 1
_O_LTF_FOREGROUND_GREEN         EQU 2
_O_LTF_FOREGROUND_BLUE          EQU 3
_O_LTF_SOURCE_PTR_SEGMENT       EQU 1
_O_LTF_SOURCE_PTR_OFFSET        EQU 3
_O_LTF_FONT_NAME                EQU 1
_O_LTF_FONT_SIZE                EQU 1
_O_LTF_FONT_TYPEFACE_BOLD       EQU 1
_O_LTF_FONT_TYPEFACE_DITHER     EQU 1
_O_LTF_FONT_TYPEFACE_ITALICS    EQU 1
_O_LTF_FONT_TYPEFACE_REVERSE    EQU 1
_O_LTF_FONT_TYPEFACE_STRIKETHROUGH EQU 1
_O_LTF_FONT_TYPEFACE_UNDERLINE  EQU 1
_O_LTF_FONT_NAME_ID             EQU 1
_O_LTF_MARGIN_LEFT              EQU 1
_O_LTF_MARGIN_TOP               EQU 1
_O_LTF_MISC_1                   EQU 1
_O_LTF_MISC_2                   EQU 1
_O_LTF_MISC_3                   EQU 1
_O_LTF_MISC_4                   EQU 1
_O_LTF_MISC_FLAG_1              EQU 1
_O_LTF_MISC_FLAG_2              EQU 1
_O_LTF_MISC_FLAG_3              EQU 1
; Sizes
_O_LTF_ENABLED_SIZE             EQU 2
_O_LTF_VISIBLE_SIZE             EQU 2
_O_LTF_BORDER_SIZE              EQU 2
_O_LTF_ALIGNMENT_SIZE           EQU 2
_O_LTF_AUTO_SIZE_SIZE           EQU 2
_O_LTF_BACKGROUND_SIZE          EQU 4
_O_LTF_FOREGROUND_SIZE          EQU 4
_O_LTF_SOURCE_PTR_SIZE          EQU 7
_O_LTF_FONT_NAME_SIZE           EQU 5
_O_LTF_FONT_SIZE_SIZE           EQU 2
_O_LTF_FONT_TYPEFACE_BOLD_SIZE  EQU 2
_O_LTF_FONT_TYPEFACE_DITHER_SIZE EQU 2
_O_LTF_FONT_TYPEFACE_ITALICS_SIZE EQU 2
_O_LTF_FONT_TYPEFACE_REVERSE_SIZE EQU 2
_O_LTF_FONT_TYPEFACE_STRIKETHROUGH_SIZE EQU 2
_O_LTF_FONT_TYPEFACE_UNDERLINE_SIZE EQU 2
_O_LTF_FONT_NAME_ID_SIZE        EQU 5
_O_LTF_MARGIN_LEFT_SIZE         EQU 3
_O_LTF_MARGIN_TOP_SIZE          EQU 3
_O_LTF_MISC_1_SIZE              EQU 5
_O_LTF_MISC_2_SIZE              EQU 5
_O_LTF_MISC_3_SIZE              EQU 5
_O_LTF_MISC_4_SIZE              EQU 5
_O_LTF_MISC_FLAG_1_SIZE         EQU 2
_O_LTF_MISC_FLAG_2_SIZE         EQU 2
_O_LTF_MISC_FLAG_3_SIZE         EQU 2

; _HLINE
; Properties
_O_HL_TOP                       EQU 12
_O_HL_LEFT                      EQU 16
_O_HL_WIDTH                     EQU 20
_O_HL_BACKGROUND                EQU 24
_O_HL_ENABLED                   EQU 27
_O_HL_MISC_1                    EQU 28
_O_HL_MISC_2                    EQU 32
_O_HL_MISC_3                    EQU 36
_O_HL_MISC_4                    EQU 40
_O_HL_MISC_FLAG_1               EQU 44
_O_HL_MISC_FLAG_2               EQU 45
_O_HL_MISC_FLAG_3               EQU 46
_O_HL_VISIBLE                   EQU 47
; Events
_O_HL_ACTIVATE                  EQU 128
_O_HL_CLICK_BOTH_SINGLE         EQU 132
_O_HL_CLICK_BOTH_DOUBLE         EQU 136
_O_HL_CLICK_LEFT_SINGLE         EQU 140
_O_HL_CLICK_LEFT_DOUBLE         EQU 144
_O_HL_CLICK_LEFT_DOWN           EQU 148
_O_HL_CLICK_LEFT_UP             EQU 152
_O_HL_CLICK_RIGHT_SINGLE        EQU 156
_O_HL_CLICK_RIGHT_DOUBLE        EQU 160
_O_HL_CLICK_RIGHT_DOWN          EQU 164
_O_HL_CLICK_RIGHT_UP            EQU 168
_O_HL_DROPPED_INTO_LEFT         EQU 172
_O_HL_DROPPED_INTO_RIGHT        EQU 176
_O_HL_DRAG_LEFT_START           EQU 180
_O_HL_DRAG_LEFT_STOP            EQU 184
_O_HL_DRAG_RIGHT_START          EQU 188
_O_HL_DRAG_RIGHT_STOP           EQU 192
_O_HL_FOCUS_GOT                 EQU 196
_O_HL_FOCUS_LOST                EQU 200
_O_HL_FOCUS_SET                 EQU 204
_O_HL_HOVER                     EQU 208
_O_HL_KEYSTROKE                 EQU 212
_O_HL_WHEN_CREATED              EQU 216
_O_HL_WHEN_DESTROYED            EQU 220
_O_HL_REQUESTOR                 EQU 224
_O_HL_REFRESH                   EQU 228
; Input data structures
_O_LHL_TYPE                     EQU 0
_O_LHL_TOP                      EQU 1
_O_LHL_LEFT                     EQU 5
_O_LHL_WIDTH                    EQU 9
_O_LHL_LENGTH                   EQU 13
; Properties
_O_LHL_ENABLED                  EQU 1
_O_LHL_VISIBLE                  EQU 1
_O_LHL_BACKGROUND_RED           EQU 1
_O_LHL_BACKGROUND_GREEN         EQU 2
_O_LHL_BACKGROUND_BLUE          EQU 3
_O_LHL_MISC_1                   EQU 1
_O_LHL_MISC_2                   EQU 1
_O_LHL_MISC_3                   EQU 1
_O_LHL_MISC_4                   EQU 1
_O_LHL_MISC_FLAG_1              EQU 1
_O_LHL_MISC_FLAG_2              EQU 1
_O_LHL_MISC_FLAG_3              EQU 1
; Sizes
_O_LHL_ENABLED_SIZE             EQU 2
_O_LHL_VISIBLE_SIZE             EQU 2
_O_LHL_BACKGROUND_SIZE          EQU 4
_O_LHL_MISC_1_SIZE              EQU 5
_O_LHL_MISC_2_SIZE              EQU 5
_O_LHL_MISC_3_SIZE              EQU 5
_O_LHL_MISC_4_SIZE              EQU 5
_O_LHL_MISC_FLAG_1_SIZE         EQU 2
_O_LHL_MISC_FLAG_2_SIZE         EQU 2
_O_LHL_MISC_FLAG_3_SIZE         EQU 2


; _RECTANGLE
; Properties
_O_R_TOP                        EQU 12
_O_R_LEFT                       EQU 16
_O_R_WIDTH                      EQU 20
_O_R_HEIGHT                     EQU 24
_O_R_BACKGROUND                 EQU 28
_O_R_ENABLED                    EQU 31
_O_R_MISC_1                     EQU 32
_O_R_MISC_2                     EQU 36
_O_R_MISC_3                     EQU 40
_O_R_MISC_4                     EQU 44
_O_R_MISC_FLAG_1                EQU 48
_O_R_MISC_FLAG_2                EQU 49
_O_R_MISC_FLAG_3                EQU 50
_O_R_VISIBLE                    EQU 51
; Events
_O_R_ACTIVATE                   EQU 128
_O_R_CLICK_BOTH_SINGLE          EQU 132
_O_R_CLICK_BOTH_DOUBLE          EQU 136
_O_R_CLICK_LEFT_SINGLE          EQU 140
_O_R_CLICK_LEFT_DOUBLE          EQU 144
_O_R_CLICK_LEFT_DOWN            EQU 148
_O_R_CLICK_LEFT_UP              EQU 152
_O_R_CLICK_RIGHT_SINGLE         EQU 156
_O_R_CLICK_RIGHT_DOUBLE         EQU 160
_O_R_CLICK_RIGHT_DOWN           EQU 164
_O_R_CLICK_RIGHT_UP             EQU 168
_O_R_DROPPED_INTO_LEFT          EQU 172
_O_R_DROPPED_INTO_RIGHT         EQU 176
_O_R_DRAG_LEFT_START            EQU 180
_O_R_DRAG_LEFT_STOP             EQU 184
_O_R_DRAG_RIGHT_START           EQU 188
_O_R_DRAG_RIGHT_STOP            EQU 192
_O_R_FOCUS_GOT                  EQU 196
_O_R_FOCUS_LOST                 EQU 200
_O_R_FOCUS_SET                  EQU 204
_O_R_HOVER                      EQU 208
_O_R_KEYSTROKE                  EQU 212
_O_R_WHEN_CREATED               EQU 216
_O_R_WHEN_DESTROYED             EQU 220
_O_R_REQUESTOR                  EQU 224
_O_R_REFRESH                    EQU 228
; Input data structures
_O_LR_TYPE                      EQU 0
_O_LR_TOP                       EQU 1
_O_LR_LEFT                      EQU 5
_O_LR_WIDTH                     EQU 9
_O_LR_HEIGHT                    EQU 13
_O_LR_LENGTH                    EQU 17
; Properties
_O_LR_ENABLED                   EQU 1
_O_LR_VISIBLE                   EQU 1
_O_LR_BACKGROUND_RED            EQU 1
_O_LR_BACKGROUND_GREEN          EQU 2
_O_LR_BACKGROUND_BLUE           EQU 3
_O_LR_MISC_1                    EQU 1
_O_LR_MISC_2                    EQU 1
_O_LR_MISC_3                    EQU 1
_O_LR_MISC_4                    EQU 1
_O_LR_MISC_FLAG_1               EQU 1
_O_LR_MISC_FLAG_2               EQU 1
_O_LR_MISC_FLAG_3               EQU 1
; Sizes
_O_LR_ENABLED_SIZE              EQU 2
_O_LR_VISIBLE_SIZE              EQU 2
_O_LR_BACKGROUND_SIZE           EQU 4
_O_LR_MISC_1_SIZE               EQU 5
_O_LR_MISC_2_SIZE               EQU 5
_O_LR_MISC_3_SIZE               EQU 5
_O_LR_MISC_4_SIZE               EQU 5
_O_LR_MISC_FLAG_1_SIZE          EQU 2
_O_LR_MISC_FLAG_2_SIZE          EQU 2
_O_LR_MISC_FLAG_3_SIZE          EQU 2


; _BORDER_BOX
; Properties
_O_BB_TOP                       EQU 12
_O_BB_LEFT                      EQU 16
_O_BB_WIDTH                     EQU 20
_O_BB_HEIGHT                    EQU 24
_O_BB_BACKGROUND                EQU 28
_O_BB_LIGHT_BORDER              EQU 31
_O_BB_SHADOW_BORDER             EQU 34
_O_BB_ENABLED                   EQU 37
_O_BB_VISIBLE                   EQU 39
_O_BB_MISC_1                    EQU 40
_O_BB_MISC_2                    EQU 44
_O_BB_MISC_3                    EQU 48
_O_BB_MISC_4                    EQU 52
_O_BB_MISC_FLAG_1               EQU 56
_O_BB_MISC_FLAG_2               EQU 57
_O_BB_MISC_FLAG_3               EQU 58
; Events
_O_BB_ACTIVATE                  EQU 128
_O_BB_CLICK_BOTH_SINGLE         EQU 132
_O_BB_CLICK_BOTH_DOUBLE         EQU 136
_O_BB_CLICK_LEFT_SINGLE         EQU 140
_O_BB_CLICK_LEFT_DOUBLE         EQU 144
_O_BB_CLICK_LEFT_DOWN           EQU 148
_O_BB_CLICK_LEFT_UP             EQU 152
_O_BB_CLICK_RIGHT_SINGLE        EQU 156
_O_BB_CLICK_RIGHT_DOUBLE        EQU 160
_O_BB_CLICK_RIGHT_DOWN          EQU 164
_O_BB_CLICK_RIGHT_UP            EQU 168
_O_BB_DROPPED_INTO_LEFT         EQU 172
_O_BB_DROPPED_INTO_RIGHT        EQU 176
_O_BB_DRAG_LEFT_START           EQU 180
_O_BB_DRAG_LEFT_STOP            EQU 184
_O_BB_DRAG_RIGHT_START          EQU 188
_O_BB_DRAG_RIGHT_STOP           EQU 192
_O_BB_FOCUS_GOT                 EQU 196
_O_BB_FOCUS_LOST                EQU 200
_O_BB_FOCUS_SET                 EQU 204
_O_BB_HOVER                     EQU 208
_O_BB_KEYSTROKE                 EQU 212
_O_BB_WHEN_CREATED              EQU 216
_O_BB_WHEN_DESTROYED            EQU 220
_O_BB_REQUESTOR                 EQU 224
_O_BB_REFRESH                   EQU 228
; Input data structures
_O_LBB_TYPE                     EQU 0
_O_LBB_TOP                      EQU 1
_O_LBB_LEFT                     EQU 5
_O_LBB_WIDTH                    EQU 9
_O_LBB_HEIGHT                   EQU 13
_O_LBB_LENGTH                   EQU 17
; Properties
_O_LBB_ENABLED                  EQU 1
_O_LBB_VISIBLE                  EQU 1
_O_LBB_BACKGROUND_RED           EQU 1
_O_LBB_BACKGROUND_GREEN         EQU 2
_O_LBB_BACKGROUND_BLUE          EQU 3
_O_LBB_LIGHT_BORDER_RED         EQU 1
_O_LBB_LIGHT_BORDER_GREEN       EQU 2
_O_LBB_LIGHT_BORDER_BLUE        EQU 3
_O_LBB_SHADOW_BORDER_RED        EQU 1
_O_LBB_SHADOW_BORDER_GREEN      EQU 2
_O_LBB_SHADOW_BORDER_BLUE       EQU 3
_O_LBB_MISC_1                   EQU 1
_O_LBB_MISC_2                   EQU 1
_O_LBB_MISC_3                   EQU 1
_O_LBB_MISC_4                   EQU 1
_O_LBB_MISC_FLAG_1              EQU 1
_O_LBB_MISC_FLAG_2              EQU 1
_O_LBB_MISC_FLAG_3              EQU 1
; Sizes
_O_LBB_ENABLED_SIZE             EQU 2
_O_LBB_VISIBLE_SIZE             EQU 2
_O_LBB_BACKGROUND_SIZE          EQU 4
_O_LBB_LIGHT_BORDER_SIZE        EQU 4
_O_LBB_SHADOW_BORDER_SIZE       EQU 4
_O_LBB_MISC_1_SIZE              EQU 5
_O_LBB_MISC_2_SIZE              EQU 5
_O_LBB_MISC_3_SIZE              EQU 5
_O_LBB_MISC_4_SIZE              EQU 5
_O_LBB_MISC_FLAG_1_SIZE         EQU 2
_O_LBB_MISC_FLAG_2_SIZE         EQU 2
_O_LBB_MISC_FLAG_3_SIZE         EQU 2