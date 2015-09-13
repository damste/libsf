; data32.asp
;
; Exodus data used in the 32-bit segment
;


;
; ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
; ³ invSetup_native_primative() ³
; ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
;
; These variables are used in the invSetup_native_primative() function
;
no_support_for_primative                db  "no support for primative"
code_gdt_offset                         dd  0                       ; used temporarily to hold permanent value of _csTEMP_PRIMATIVE
data_gdt_offset                         dd  0                       ; same, but for _dsTEMP_PRIMATIVE
main_gdt_offset                         dd  0                       ; same, but for _cgTEMP_PRIMATIVE_MAIN
requestor_gdt_offset                    dd  0                       ; same, but for _cgTEMP_PRIMATIVE_REQUESTOR
vga_kbd_support                         db  0                       ; Indicates whether or not basic VGA/keyboard support
                                                                    ; has been installed.  Will be set to 1 after both are
                                                                    ; available.

exodus_internal_text                    db  " (Exodus Internal)",0
unknown_function_text                   db  " (unknown)",0
unknown_user_function_text              db  " (unknown user function)",0
unknown_primative_text                  db  " (unknown primative)",0
error_loading_exodus_ini_1              db  " ERROR - An error occurred while parsing EXODUS.INI.",0
error_loading_exodus_ini_2              db  " ERROR - Exodus cannot find a required boot file: EXODUS.INI",0
error_loading_exodus_ini_3              db  " ERROR - Exodus found multiple EXODUS.INI files on the boot drive.",0
error_loading_exodus_ini_4              db  "          Please correct this problem and try booting again.",0
system_halted                           db  " System is stopped.  Please press RESET or power down to restart.",0
found_it_text                           db  " (found it!)",0

line_text                               db  "Line xxxxxx"
parse_expected_bracket_paren            db  "Expected [ or (",0
parse_expected_paren                    db  "Expected (",0
parse_unexpected_end_of_file            db  "Unexpected end of file",0
parse_bracket_group_name_too_long       db  "[] name is too long, can only be 4 characters",0

loading_primatives_displayed            db  _NO
loading_primatives                      db  "þ Loading primatives",0
loading_drivers                         db  "þ Loading drivers",0
next_item                               db  "  Ã ",0
last_item                               db  "  À ",0
comma_space                             db  ", ",0

; Boot screen
bootscreen_start:
  ;INCLUDE bootscrn.inc
  INCLUDE boot_scr.inc
bootscreen_end:


; These functions are required during bootup
;
_EXODUS_requestor                       dw  0
_VID_clear_screen_vga                   dw  0
_VID_display_decimal_in_edx_nr_vga      dw  _sEXODUS_REQUESTOR
_VID_display_string_ecx_nr_vga          dw  0f000h
_VID_display_string_ecx_vga             dw  0f000h
_VID_display_string_nr_vga              dw  0f000h
_VID_display_string_vga                 dw  0f000h
_VID_freeze_frame_vga                   dw  0f000h
_VID_position_cursor_vga                dw  0f000h
_VID_mono_enter_graphics_mode           dw  0f000h
_VID_g_mono_display_text                dw  0f000h
_VID_g_mono_display_text_mode           dw  0f000h
_VID_g_mono_clear_screen                dw  0f000h
_VID_g_set_font_8x8                     dw  0f000h
_VID_g_set_font_8x14                    dw  0f000h
_VID_g_set_font_16x16                   dw  0f000h
_VID_draw_logo                          dw  0f000h
_VID_requestor                          dw  0f000h
_VID_g_display_radix_in_edx_mono        dw  0f000h
_VID_freeze_frame_mono                  dw  0f000h
_VID_move_to_next_line_vga              dw  0f000h
_VID_set_attribute_vga                  dw  0f000h
_EXODUS_dot_com                         dw  0f000h
_VID_draw_exodus_boot_screen            dw  0f000h
                                        dw  0f000h
                                        dw  0f000h



required_native_primatives              db  20, "VID_clear_screen_vga"
                                        db  33, "VID_display_decimal_in_edx_nr_vga"
                                        db  29, "VID_display_string_ecx_nr_vga"
                                        db  26, "VID_display_string_ecx_vga"
                                        db  25, "VID_display_string_nr_vga"
                                        db  22, "VID_display_string_vga"
                                        db  20, "VID_freeze_frame_vga"
                                        db  23, "VID_position_cursor_vga"
                                        db  28, "VID_mono_enter_graphics_mode"
                                        db  23, "VID_g_mono_display_text"
                                        db  28, "VID_g_mono_display_text_mode"
                                        db  23, "VID_g_mono_clear_screen"
                                        db  18, "VID_g_set_font_8x8"
                                        db  19, "VID_g_set_font_8x14"
                                        db  20, "VID_g_set_font_16x16"
                                        db  13, "VID_draw_logo"
                                        db  13, "VID_requestor"
                                        db  31, "VID_g_display_radix_in_edx_mono"
                                        db  21, "VID_freeze_frame_mono"
                                        db  25, "VID_move_to_next_line_vga"
                                        db  21, "VID_set_attribute_vga"
                                        db  14, "EXODUS_dot_com"
                                        db  27, "VID_draw_exodus_boot_screen"
                                        db  0ffh



;_KBD_get_a_key                          dw  0f000h     ;    db  13, "KBD_get_a_key"
;_VID_display_decimal_in_edx_vga         dw  0f000h     ;    db  30, "VID_display_decimal_in_edx_vga"
;_VID_display_hex_string_ecx_nr_vga      dw  0f000h     ;    db  33, "VID_display_hex_string_ecx_nr_vga"
;_VID_display_hex_string_ecx_ro_vga      dw  0f000h     ;    db  33, "VID_display_hex_string_ecx_ro_vga"
;_VID_display_hex_string_ecx_vga         dw  0f000h     ;    db  30, "VID_display_hex_string_ecx_vga"
;_VID_display_hexidecimal_in_edx_nr_vga  dw  0f000h     ;    db  37, "VID_display_hexidecimal_in_edx_nr_vga"
;_VID_display_hexidecimal_in_edx_vga     dw  0f000h     ;    db  34, "VID_display_hexidecimal_in_edx_vga"
;_VID_display_radix_in_edx_nr_vga        dw  0f000h     ;    db  31, "VID_display_radix_in_edx_nr_vga"
;_VID_display_radix_in_edx_vga           dw  0f000h     ;    db  28, "VID_display_radix_in_edx_vga"
;_VID_get_cursor_vga                     dw  0f000h     ;    db  18, "VID_get_cursor_vga"
;_VID_move_to_next_line_vga              dw  0f000h     ;    db  25, "VID_move_to_next_line_vga"
;_VID_set_attribute_vga                  dw  0f000h     ;    db  21, "VID_set_attribute_vga"
;_VID_set_registers_for_vga              dw  0f000h     ;    db  25, "VID_set_registers_for_vga"
;_VID_clear_screen_mono                  dw  0f000h     ;    db  21, "VID_clear_screen_mono"
;_VID_display_decimal_in_edx_mono        dw  0f000h     ;    db  31, "VID_display_decimal_in_edx_mono"
;_VID_display_decimal_in_edx_nr_mono     dw  0f000h     ;    db  34, "VID_display_decimal_in_edx_nr_mono"
;_VID_display_hex_string_ecx_mono        dw  0f000h     ;    db  31, "VID_display_hex_string_ecx_mono"
;_VID_display_hex_string_ecx_nr_mono     dw  0f000h     ;    db  34, "VID_display_hex_string_ecx_nr_mono"
;_VID_display_hex_string_ecx_ro_mono     dw  0f000h     ;    db  34, "VID_display_hex_string_ecx_ro_mono"
;_VID_display_hexidecimal_in_edx_mono    dw  0f000h     ;    db  35, "VID_display_hexidecimal_in_edx_mono"
;_VID_display_hexidecimal_in_edx_nr_mono dw  0f000h     ;    db  38, "VID_display_hexidecimal_in_edx_nr_mono"
;_VID_display_radix_in_edx_mono          dw  0f000h     ;    db  29, "VID_display_radix_in_edx_mono"
;_VID_display_radix_in_edx_nr_mono       dw  0f000h     ;    db  32, "VID_display_radix_in_edx_nr_mono"
;_VID_display_string_ecx_mono            dw  0f000h     ;    db  27, "VID_display_string_ecx_mono"
;_VID_display_string_ecx_nr_mono         dw  0f000h     ;    db  30, "VID_display_string_ecx_nr_mono"
;_VID_display_string_mono                dw  0f000h     ;    db  23, "VID_display_string_mono"
;_VID_display_string_nr_mono             dw  0f000h     ;    db  26, "VID_display_string_nr_mono"
;_VID_get_cursor_mono                    dw  0f000h     ;    db  19, "VID_get_cursor_mono"
;_VID_move_to_next_line_mono             dw  0f000h     ;    db  26, "VID_move_to_next_line_mono"
;_VID_position_cursor_mono               dw  0f000h     ;    db  24, "VID_position_cursor_mono"
;_VID_set_attribute_mono                 dw  0f000h     ;    db  22, "VID_set_attribute_mono"
;_VID_set_registers_for_mono             dw  0f000h     ;    db  26, "VID_set_registers_for_mono"
;_VID_clear_screen_both                  dw  0f000h     ;    db  21, "VID_clear_screen_both"
;_VID_display_decimal_in_edx_both        dw  0f000h     ;    db  31, "VID_display_decimal_in_edx_both"
;_VID_display_decimal_in_edx_nr_both     dw  0f000h     ;    db  34, "VID_display_decimal_in_edx_nr_both"
;_VID_display_hex_string_ecx_both        dw  0f000h     ;    db  31, "VID_display_hex_string_ecx_both"
;_VID_display_hex_string_ecx_nr_both     dw  0f000h     ;    db  34, "VID_display_hex_string_ecx_nr_both"
;_VID_display_hex_string_ecx_ro_both     dw  0f000h     ;    db  34, "VID_display_hex_string_ecx_ro_both"
;_VID_display_hexidecimal_in_edx_both    dw  0f000h     ;    db  35, "VID_display_hexidecimal_in_edx_both"
;_VID_display_hexidecimal_in_edx_nr_both dw  0f000h     ;    db  38, "VID_display_hexidecimal_in_edx_nr_both"
;_VID_display_string_both                dw  0f000h     ;    db  23, "VID_display_string_both"
;_VID_display_radix_in_edx_nr_both       dw  0f000h     ;    db  32, "VID_display_radix_in_edx_nr_both"
;_VID_display_string_ecx_both            dw  0f000h     ;    db  27, "VID_display_string_ecx_both"
;_VID_display_string_ecx_nr_both         dw  0f000h     ;    db  30, "VID_display_string_ecx_nr_both"
;_VID_display_string_nr_both             dw  0f000h     ;    db  26, "VID_display_string_nr_both"
;_VID_freeze_frame_both                  dw  0f000h     ;    db  21, "VID_freeze_frame_both"
;_VID_move_to_next_line_both             dw  0f000h     ;    db  26, "VID_move_to_next_line_both"
;_VID_position_cursor_both               dw  0f000h     ;    db  24, "VID_position_cursor_both"
;_VID_set_attribute_both                 dw  0f000h     ;    db  22, "VID_set_attribute_both"
;_VID_mono_enter_text_mode               dw  0f000h     ;    db  24, "VID_mono_enter_text_mode"



;
; Displays a message when an Exodus bootup device doesn't properly identify itself
; But, this is only displayed before VGA and KBD support is available.
; After that the invSetup_native_primates() function takes control and allows selective non-install, etc.
;
failed                                  db  "FAILED",13,10
                                        db  13,10
                                        db  " An Exodus Driver failed to initialize properly",13,10
                                        db  " This was before VGA and keyboard support was available (to allow user action)",13,10
                                        db  " For this reason Exodus cannot continue to boot",13,10
                                        db  13,10
                                        db  13,10
                                        db  13,10
                                        db  13,10
                                        db  13,10
                                        db  13,10
                                        db  "-----",13,10
                                        db  " Please attempt to correct this problem and try again",13,10
                                        db  13,10
                                        db  " If the problem persists, you can reach us online (use a friend's computer)",13,10
                                        db  "  Ã http://www.beatleworks.com/boot_trouble",13,10
                                        db  "  À boot_trouble@beatleworks.com",13,10
failed_end:
