; objects.asp
;
; Exodus Object Types and Parameters
;





; зддддддддддддд©
; Ё BASE OBJECT Ё
; юддддддддддддды
_GROUPING                           EQU 0
_DESKTOP                            EQU 1
_WINDOW                             EQU 2
_CONSOLE                            EQU 3
_TEXT_MODE                          EQU 4
_MONO_DESKTOP                       EQU 5
_MONO_WINDOW                        EQU 6
_MONO_CONSOLE                       EQU 7
_MONO_TEXT_MODE                     EQU 8
_PROPERTY_START                     EQU -3
_EVENT_START                        EQU -2
_OBJECT_END                         EQU -1

_OBJECT_RED                         EQU 0
_OBJECT_GREEN                       EQU 1
_OBJECT_BLUE                        EQU 2

;-----------------------------------------
; зддддддддд©
; Ё OBJECTS Ё
; юддддддддды
_INPUT_FIELD                        EQU 0
_TEXT_FIELD                         EQU 1
_BUTTON                             EQU 2
_MENU_BAR                           EQU 3
_MENU_POPUP                         EQU 4
_RADIO_DIAL                         EQU 5
_CHECK_BOX                          EQU 6
_CIRCLE_BOX                         EQU 7
_PULLDOWN                           EQU 8
_SLIDE_BAR                          EQU 9
_PERCENT_BAR                        EQU 10
_TRAY                               EQU 11
_ICON                               EQU 12
_BITMAP                             EQU 13
_HLINE                              EQU 14
_VLINE                              EQU 15
_LINE                               EQU 16
_OVAL                               EQU 17
_RECTANGLE                          EQU 18
_SCROLL_BAR_HORIZONTAL              EQU 19
_SCROLL_BAR_VERTICAL                EQU 20
_CASK                               EQU 21
_CFSCA_WINDOW                       EQU 22
_NUMBERS_WINDOW                     EQU 23
_TYPESET_WINDOW                     EQU 24
_BORDER_BOX                         EQU 25

;-----------------------------------------
; здддддддддддддддддд©
; Ё FONT_NAME ID #'S Ё
; юдддддддддддддддддды                  ; Note, Refer to INF\VGA.INF for information on this ID # structure
_BITMAP_8x6                         EQU 80000806h
_BITMAP_8x8                         EQU 80000808h
_BITMAP_8x14                        EQU 8000080eh
_BITMAP_8x16                        EQU 80000810h
_BITMAP_16x16                       EQU 80001010h



; здддддддддддддддддддддд©
; Ё _GROUPING PARAMETERS Ё
; юдддддддддддддддддддддды
_GP_ENABLED                         EQU
_GP_MISC_1                          EQU
_GP_MISC_2                          EQU
_GP_MISC_3                          EQU
_GP_MISC_4                          EQU
_GP_MISC_FLAG_1                     EQU
_GP_MISC_FLAG_2                     EQU
_GP_MISC_FLAG_3                     EQU

_GE_FOCUS_GOT                       EQU
_GE_FOCUS_LOST                      EQU
_GE_FOCUS_SET                       EQU
_GE_WHEN_CREATED                    EQU
_GE_WHEN_DESTROYED                  EQU
_GE_REQUESTOR                       EQU

; зддддддддддддддддддддд©
; Ё _DESKTOP PARAMETERS Ё
; юддддддддддддддддддддды
_DP_ENABLED                         EQU 0
_DP_VISIBLE                         EQU 1
_DP_BACKGROUND                      EQU 2
_DP_ICON_HORIZONTAL                 EQU 3
_DP_ICON_VERTICAL                   EQU 4
_DP_MENU_POSITION                   EQU 5
_DP_MENU_HEIGHT                     EQU 6
_DP_MENU_AUTOHIDE                   EQU 7
_DP_MISC_1                          EQU 8
_DP_MISC_2                          EQU 9
_DP_MISC_3                          EQU 10
_DP_MISC_4                          EQU 11
_DP_MISC_FLAG_1                     EQU 12
_DP_MISC_FLAG_2                     EQU 13
_DP_MISC_FLAG_3                     EQU 14
_DP_WALLPAPER                       EQU 15
;
_DE_ACTIVATE                        EQU 0
_DE_CLICK_BOTH_SINGLE               EQU 1
_DE_CLICK_BOTH_DOUBLE               EQU 2
_DE_CLICK_LEFT_SINGLE               EQU 3
_DE_CLICK_LEFT_DOUBLE               EQU 4
_DE_CLICK_LEFT_DOWN                 EQU 5
_DE_CLICK_LEFT_UP                   EQU 6
_DE_CLICK_RIGHT_SINGLE              EQU 7
_DE_CLICK_RIGHT_DOUBLE              EQU 8
_DE_CLICK_RIGHT_DOWN                EQU 9
_DE_CLICK_RIGHT_UP                  EQU 10
_DE_DROPPED_INTO_LEFT               EQU 11
_DE_DROPPED_INTO_RIGHT              EQU 12
_DE_DRAG_LEFT_START                 EQU 13
_DE_DRAG_LEFT_STOP                  EQU 14
_DE_DRAG_RIGHT_START                EQU 15
_DE_DRAG_RIGHT_STOP                 EQU 16
_DE_FOCUS_GOT                       EQU 17
_DE_FOCUS_LOST                      EQU 18
_DE_FOCUS_SET                       EQU 19
_DE_HOVER                           EQU 20
_DE_KEYSTROKE                       EQU 21
_DE_WHEN_CREATED                    EQU 22
_DE_WHEN_DESTROYED                  EQU 23
_DE_REQUESTOR                       EQU 24
_DE_REFRESH                         EQU 25

; здддддддддддддддддддд©
; Ё _WINDOW PARAMETERS Ё
; юдддддддддддддддддддды
_WP_ENABLED                         EQU
_WP_VISIBLE                         EQU
_WP_BORDER                          EQU
_WP_COLOR_DISABLEP_BACKGROUND       EQU
_WP_COLOR_DISABLEP_FOREGROUND       EQU
_WP_COLOR_DISABLEP_STYLE            EQU
_WP_COLOR_ENABLEP_BACKGROUND        EQU
_WP_COLOR_ENABLEP_FOREGROUND        EQU
_WP_COLOR_ENABLEP_STYLE             EQU
_WP_COLOR_HEADER_SELECTED_FOREGROUND EQU
_WP_COLOR_HEADER_SELECTED_BACKGROUND EQU
_WP_COLOR_HEADER_DESELECTED_BACKGROUND EQU
_WP_COLOR_HEADER_DESELECTED_FOREGROUND EQU
_WP_FONT_NAME                       EQU
_WP_FONT_SIZE                       EQU
_WP_FONT_TYPEFACE_BOLD              EQU
_WP_FONT_TYPEFACE_DITHER            EQU
_WP_FONT_TYPEFACE_ITALICS           EQU
_WP_FONT_TYPEFACE_REVERSE           EQU
_WP_FONT_TYPEFACE_STRIKETHROUGH     EQU
_WP_FONT_TYPEFACE_UNDERLINE         EQU
_WP_FONT_NAME_ID                    EQU
_WP_MARGIN_LEFT                     EQU
_WP_MARGIN_RIGHT                    EQU
_WP_MARGIN_TOP                      EQU
_WP_MARGIN_BOTTOM                   EQU
_WP_MISC_1                          EQU
_WP_MISC_2                          EQU
_WP_MISC_3                          EQU
_WP_MISC_4                          EQU
_WP_MOUSE_POINTER                   EQU
_WP_POSITION_HEIGHT                 EQU
_WP_POSITION_LEFT                   EQU
_WP_POSITION_TOP                    EQU
_WP_POSITION_WIDTH                  EQU
_WP_MISC_FLAG_1                     EQU
_WP_MISC_FLAG_2                     EQU
_WP_MISC_FLAG_3                     EQU
_WP_SIZEABLE                        EQU
_WP_WRAP_TEXT                       EQU

; зддддддддддддддддддддд©
; Ё _CONSOLE PARAMETERS Ё
; юддддддддддддддддддддды
_CP_ENABLED                         EQU
_CP_VISIBLE                         EQU
_CP_BORDER                          EQU
_CP_COLOR_DISABLEP_BACKGROUND       EQU
_CP_COLOR_DISABLEP_FOREGROUND       EQU
_CP_COLOR_ENABLEP_BACKGROUND        EQU
_CP_COLOR_ENABLEP_FOREGROUND        EQU
_CP_COLOR_HEADER_SELECTED_FOREGROUND EQU
_CP_COLOR_HEADER_SELECTED_BACKGROUND EQU
_CP_COLOR_HEADER_DESELECTED_BACKGROUND EQU
_CP_COLOR_HEADER_DESELECTED_FOREGROUND EQU
_CP_FONT_NAME                       EQU
_CP_FONT_SIZE                       EQU
_CP_FONT_NAME_ID                    EQU
_CP_MISC_1                          EQU
_CP_MISC_2                          EQU
_CP_MISC_3                          EQU
_CP_MISC_4                          EQU
_CP_POSITION_LEFT                   EQU
_CP_POSITION_TOP                    EQU
_CP_WINDOW_HEIGHT                   EQU
_CP_WINDOW_WIDTH                    EQU
_CP_MISC_FLAG_1                     EQU
_CP_MISC_FLAG_2                     EQU
_CP_MISC_FLAG_3                     EQU
_CP_SIZEABLE                        EQU

; зддддддддддддддддддддддд©
; Ё _TEXT_MODE PARAMETERS Ё
; юддддддддддддддддддддддды
_TP_ENABLED                         EQU
_TP_MISC_1                          EQU
_TP_MISC_2                          EQU
_TP_MISC_3                          EQU
_TP_MISC_4                          EQU
_TP_HEIGHT                          EQU
_TP_WIDTH                           EQU
_TP_MISC_FLAG_1                     EQU
_TP_MISC_FLAG_2                     EQU
_TP_MISC_FLAG_3                     EQU



;-----------------------------------------
;
; зддддддддддддддддддд©
; Ё _HLINE PARAMETERS Ё
; юддддддддддддддддддды
; Properties
_HLP_ENABLED                        EQU 0
_HLP_VISIBLE                        EQU 1
_HLP_BACKGROUND                     EQU 2
_HLP_MISC_1                         EQU 3
_HLP_MISC_2                         EQU 4
_HLP_MISC_3                         EQU 5
_HLP_MISC_4                         EQU 6
_HLP_MISC_FLAG_1                    EQU 7
_HLP_MISC_FLAG_2                    EQU 8
_HLP_MISC_FLAG_3                    EQU 9
; Events
_HLE_ACTIVATE                       EQU 0
_HLE_CLICK_BOTH_SINGLE              EQU 1
_HLE_CLICK_BOTH_DOUBLE              EQU 2
_HLE_CLICK_LEFT_SINGLE              EQU 3
_HLE_CLICK_LEFT_DOUBLE              EQU 4
_HLE_CLICK_LEFT_DOWN                EQU 5
_HLE_CLICK_LEFT_UP                  EQU 6
_HLE_CLICK_RIGHT_SINGLE             EQU 7
_HLE_CLICK_RIGHT_DOUBLE             EQU 8
_HLE_CLICK_RIGHT_DOWN               EQU 9
_HLE_CLICK_RIGHT_UP                 EQU 10
_HLE_DROPPED_INTO_LEFT              EQU 11
_HLE_DROPPED_INTO_RIGHT             EQU 12
_HLE_DRAG_LEFT_START                EQU 13
_HLE_DRAG_LEFT_STOP                 EQU 14
_HLE_DRAG_RIGHT_START               EQU 15
_HLE_DRAG_RIGHT_STOP                EQU 16
_HLE_FOCUS_GOT                      EQU 17
_HLE_FOCUS_LOST                     EQU 18
_HLE_FOCUS_SET                      EQU 19
_HLE_HOVER                          EQU 20
_HLE_KEYSTROKE                      EQU 21
_HLE_WHEN_CREATED                   EQU 22
_HLE_WHEN_DESTROYED                 EQU 23
_HLE_REQUESTOR                      EQU 24
_HLE_REFRESH                        EQU 25


;-----------------------------------------
;
; зддддддддддддддддддддддд©
; Ё _RECTANGLE PARAMETERS Ё
; юддддддддддддддддддддддды
; Properties
_RP_ENABLED                         EQU 0
_RP_VISIBLE                         EQU 1
_RP_BACKGROUND                      EQU 2
_RP_MISC_1                          EQU 3
_RP_MISC_2                          EQU 4
_RP_MISC_3                          EQU 5
_RP_MISC_4                          EQU 6
_RP_MISC_FLAG_1                     EQU 7
_RP_MISC_FLAG_2                     EQU 8
_RP_MISC_FLAG_3                     EQU 9
; Events
_RE_ACTIVATE                        EQU 0
_RE_CLICK_BOTH_SINGLE               EQU 1
_RE_CLICK_BOTH_DOUBLE               EQU 2
_RE_CLICK_LEFT_SINGLE               EQU 3
_RE_CLICK_LEFT_DOUBLE               EQU 4
_RE_CLICK_LEFT_DOWN                 EQU 5
_RE_CLICK_LEFT_UP                   EQU 6
_RE_CLICK_RIGHT_SINGLE              EQU 7
_RE_CLICK_RIGHT_DOUBLE              EQU 8
_RE_CLICK_RIGHT_DOWN                EQU 9
_RE_CLICK_RIGHT_UP                  EQU 10
_RE_DROPPED_INTO_LEFT               EQU 11
_RE_DROPPED_INTO_RIGHT              EQU 12
_RE_DRAG_LEFT_START                 EQU 13
_RE_DRAG_LEFT_STOP                  EQU 14
_RE_DRAG_RIGHT_START                EQU 15
_RE_DRAG_RIGHT_STOP                 EQU 16
_RE_FOCUS_GOT                       EQU 17
_RE_FOCUS_LOST                      EQU 18
_RE_FOCUS_SET                       EQU 19
_RE_HOVER                           EQU 20
_RE_KEYSTROKE                       EQU 21
_RE_WHEN_CREATED                    EQU 22
_RE_WHEN_DESTROYED                  EQU 23
_RE_REQUESTOR                       EQU 24
_RE_REFRESH                         EQU 25


;-----------------------------------------
;
; здддддддддддддддддддддддд©
; Ё _BORDER_BOX PARAMETERS Ё
; юдддддддддддддддддддддддды
; Properties
_BBP_ENABLED                        EQU 0
_BBP_VISIBLE                        EQU 1
_BBP_BACKGROUND                     EQU 2
_BBP_LIGHT_BORDER                   EQU 3
_BBP_SHADOW_BORDER                  EQU 4
_BBP_MISC_1                         EQU 5
_BBP_MISC_2                         EQU 6
_BBP_MISC_3                         EQU 7
_BBP_MISC_4                         EQU 8
_BBP_MISC_FLAG_1                    EQU 9
_BBP_MISC_FLAG_2                    EQU 10
_BBP_MISC_FLAG_3                    EQU 11
; Events
_BBE_ACTIVATE                       EQU 0
_BBE_CLICK_BOTH_SINGLE              EQU 1
_BBE_CLICK_BOTH_DOUBLE              EQU 2
_BBE_CLICK_LEFT_SINGLE              EQU 3
_BBE_CLICK_LEFT_DOUBLE              EQU 4
_BBE_CLICK_LEFT_DOWN                EQU 5
_BBE_CLICK_LEFT_UP                  EQU 6
_BBE_CLICK_RIGHT_SINGLE             EQU 7
_BBE_CLICK_RIGHT_DOUBLE             EQU 8
_BBE_CLICK_RIGHT_DOWN               EQU 9
_BBE_CLICK_RIGHT_UP                 EQU 10
_BBE_DROPPED_INTO_LEFT              EQU 11
_BBE_DROPPED_INTO_RIGHT             EQU 12
_BBE_DRAG_LEFT_START                EQU 13
_BBE_DRAG_LEFT_STOP                 EQU 14
_BBE_DRAG_RIGHT_START               EQU 15
_BBE_DRAG_RIGHT_STOP                EQU 16
_BBE_FOCUS_GOT                      EQU 17
_BBE_FOCUS_LOST                     EQU 18
_BBE_FOCUS_SET                      EQU 19
_BBE_HOVER                          EQU 20
_BBE_KEYSTROKE                      EQU 21
_BBE_WHEN_CREATED                   EQU 22
_BBE_WHEN_DESTROYED                 EQU 23
_BBE_REQUESTOR                      EQU 24
_BBE_REFRESH                        EQU 25


;-----------------------------------------
;
; здддддддддддддддддддддддд©
; Ё _TEXT_FIELD PARAMETERS Ё
; юдддддддддддддддддддддддды
; Properties
_TFP_ENABLED                        EQU 0
_TFP_VISIBLE                        EQU 1
_TFP_BORDER                         EQU 2
_TFP_ALIGNMENT                      EQU 3
_TFP_AUTO_SIZE                      EQU 4
_TFP_COLOR_BACKGROUND               EQU 5
_TFP_COLOR_FOREGROUND               EQU 6
_TFP_COLOR_SELECTED_BACKGROUND      EQU 7
_TFP_COLOR_SELECTED_FOREGROUND      EQU 8
_TFP_SOURCE_PTR                     EQU 9
_TFP_FONT_NAME                      EQU 10
_TFP_FONT_SIZE                      EQU 11
_TFP_FONT_TYPEFACE_BOLD             EQU 12
_TFP_FONT_TYPEFACE_DITHER           EQU 13
_TFP_FONT_TYPEFACE_ITALICS          EQU 14
_TFP_FONT_TYPEFACE_REVERSE          EQU 15
_TFP_FONT_TYPEFACE_STRIKETHROUGH    EQU 16
_TFP_FONT_TYPEFACE_UNDERLINE        EQU 17
_TFP_FONT_NAME_ID                   EQU 18
_TFP_MARGIN_LEFT                    EQU 19
_TFP_MARGIN_TOP                     EQU 20
_TFP_SELECTED_TEXT_START            EQU 21
_TFP_SELECTED_TEXT_END              EQU 22
_TFP_MISC_1                         EQU 23
_TFP_MISC_2                         EQU 24
_TFP_MISC_3                         EQU 25
_TFP_MISC_4                         EQU 26
_TFP_MISC_FLAG_1                    EQU 27
_TFP_MISC_FLAG_2                    EQU 28
_TFP_MISC_FLAG_3                    EQU 29
; Events
_TFE_ACTIVATE                       EQU 0
_TFE_CLICK_BOTH_SINGLE              EQU 1
_TFE_CLICK_BOTH_DOUBLE              EQU 2
_TFE_CLICK_LEFT_SINGLE              EQU 3
_TFE_CLICK_LEFT_DOUBLE              EQU 4
_TFE_CLICK_LEFT_DOWN                EQU 5
_TFE_CLICK_LEFT_UP                  EQU 6
_TFE_CLICK_RIGHT_SINGLE             EQU 7
_TFE_CLICK_RIGHT_DOUBLE             EQU 8
_TFE_CLICK_RIGHT_DOWN               EQU 9
_TFE_CLICK_RIGHT_UP                 EQU 10
_TFE_DROPPED_INTO_LEFT              EQU 11
_TFE_DROPPED_INTO_RIGHT             EQU 12
_TFE_DRAG_LEFT_START                EQU 13
_TFE_DRAG_LEFT_STOP                 EQU 14
_TFE_DRAG_RIGHT_START               EQU 15
_TFE_DRAG_RIGHT_STOP                EQU 16
_TFE_FOCUS_GOT                      EQU 17
_TFE_FOCUS_LOST                     EQU 18
_TFE_FOCUS_SET                      EQU 19
_TFE_HOVER                          EQU 20
_TFE_KEYSTROKE                      EQU 21
_TFE_WHEN_CREATED                   EQU 22
_TFE_WHEN_DESTROYED                 EQU 23
_TFE_REQUESTOR                      EQU 24
_TFE_REFRESH                        EQU 25