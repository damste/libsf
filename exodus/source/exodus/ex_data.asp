; ex_data.asp
;
; Exodus.com DATA items
;


; The desktop dimension itself is explicitly laid out so it can be modified during bootup
exodus_desktop:
        db  _DESKTOP
    desktop_top     dd  0
    desktop_left    dd  0
    desktop_width   dd  0
    desktop_height  dd  0
        db  _DP_ENABLED, 1                                          ; 1-yes, 0-no
        db  _DP_VISIBLE, 1
        db  _DP_BACKGROUND, 0,0,128                                 ; RGB, R=0, G=0, B=40 (out of 255)
        db  _DP_MENU_POSITION, 6                                    ; In the form of a clock; 12=top, 3=right, 6=bottom, 9=left
        db  _DP_MENU_HEIGHT
        dw   30                                                     ; 30 pixels (this is for the system tray
        db  _DP_MENU_AUTOHIDE, 0
        dw  _OBJECT_END


    exodus_bar_rectangle:
        db  _RECTANGLE
    ebr_top             dd  0
    ebr_left            dd  0
    ebr_width           dd  0
    ebr_height          dd  29
        db  _RP_BACKGROUND, 0, 255, 255                             ; bright cyan
        db  _RP_ENABLED, 1
        db  _RP_VISIBLE, 1
        dw  _OBJECT_END


    exodus_bar_line:
        db  _HLINE
    ebl_top             dd  0
    ebl_left            dd  0
    ebl_width           dd  0
        db  _HLP_BACKGROUND, 0, 0, 255                              ; bright blue
        db  _HLP_ENABLED, 1
        db  _HLP_VISIBLE, 1
        dw  _OBJECT_END


    exodus_button_border:
        db  _BORDER_BOX
    ebb_top             dd  0
    ebb_left            dd  1
    ebb_width           dd  125
    ebb_height          dd  25
        db  _BBP_BACKGROUND, 0, 225, 225                            ; bright cyan
        db  _BBP_LIGHT_BORDER, 255, 255, 255                        ; bright white
        db  _BBP_SHADOW_BORDER, 128, 128, 128                       ; grey
        db  _BBP_ENABLED, 1
        db  _BBP_VISIBLE, 1
        dw  _OBJECT_END


    exodus_button_text:
        db  _TEXT_FIELD
    ebt_top             dd  0
    ebt_left            dd  28
    ebt_width           dd  6*16
    ebt_height          dd  16
        db  _TFP_COLOR_BACKGROUND, 0, 225, 225                      ; bright cyan
        db  _TFP_COLOR_FOREGROUND, 0, 0, 128                        ; dark blue
        db  _TFP_FONT_NAME_ID
        dd      _BITMAP_16x16                                       ; Bitmap 16x16 font
        db  _TFP_ENABLED, 0
        db  _TFP_VISIBLE, 1
        db  _TFP_SOURCE_PTR
    ebt_segment         dw  -1
        dd  offset exodus_button
        dw  _OBJECT_END


    exodus_button_logo_rectangle:
        db  _RECTANGLE
    eblr_top            dd  0
    eblr_left           dd  3
    eblr_width          dd  24
    eblr_height         dd  22
        db  _RP_BACKGROUND, 0, 0, 0                                 ; black
        db  _RP_ENABLED, 1
        db  _RP_VISIBLE, 1
        dw  _OBJECT_END