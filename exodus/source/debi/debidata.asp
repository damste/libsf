; debidata.asp
;
; Data used by DEBI
;


;;============================
;; This is the screen that is the main Debi debugging screen
;
;   x,y
;  Úֲֲֲֲֲִִִִִִִִִִִִִִִִִִ¿    The DEBI_screen_table relates its structure to this logical arrangement of the screen.
;  ³0,0³1,0³2,0³3,0³4,0³5,0³    Each square represents a starting point for something to be displayed.  Internal logic
;  ֳִִִִִִִִִִִִִִִִִִֵֵֵֵֵ´    during this setup ensures that things only fit where they're supposed to.
;  ³0,1³1,1³2,1³3,1³4,1³5,1³
;  ֳִִִִִִִִִִִִִִִִִִֵֵֵֵֵ´    The letter identifies which part of the screen it is (as identified by its label)
;  ³0,2³1,2³2,2³3,2³4,2³5,2³
;  ֳִִִִִִִִִִִִִִִִִִֵֵֵֵֵ´    Each cell is x=15
;  ³0,3³1,3³2,3³3,3³4,3³5,3³                 y=9
;  ֳִִִִִִִִִִִִִִִִִִֵֵֵֵֵ´
;  ³0,4³1,4³2,4³3,4³4,4³5,4³
;  ֳִִִִִִִִִִִִִִִִִִֵֵֵֵֵ´
;  ³0,5³1,5³2,5³3,5³4,5³5,5³
;  ְֱֱֱֱֱִִִִִִִִִִִִִִִִִִÙ
;




; Upon entry into this algorithm no memory locations have been specified.  They will be updated during the first screen
; updating algorithm or possibly when DEBI is exited (saving the current state prior to continuing).
; Each of these items is 16-bytes in length.  One paragraph.  One happy paragraph. :)
DEBI_screen_table:
; CFSCA.2
                            db  _YES                                ; +00 Alterable?
                            db  _YES                                ; +01 Active?
                            dw  0                                   ; +02 +--Nuserved
                            dd  0                                   ; +04 +_ST_OBJECT_UL_HORIZONTAL
                            dd  0                                   ; +08 +_ST_OBJECT_UL_VERTICAL
                            dd  0ffffffffh                          ; +12 +_ST_MEMVAR_OFFSET
                            dd  offset DEBI_c_keyboard_objects      ; +16 +_ST_OBJECT_KBD_OFFSET
                            dd  0ffffffffh                          ; +20 +_ST_OBJECT_MEMORY_OFFSET
                            dd  offset DEBI_c_mouse_objects         ; +24 +_ST_OBJECT_MOUSE_OFFSET
                            dd  offset DEBI_c_screen_objects        ; +28 +_ST_OBJECT_SCREEN_OFFSET
; regs.1
                            db  _YES                                ; +00 Alterable?
                            db  _YES                                ; +01 Active?
                            dw  0                                   ; +02 +--Nuserved
                            dd  5*(15*8)                            ; +04 +_ST_OBJECT_UL_HORIZONTAL
                            dd  0                                   ; +08 +_ST_OBJECT_UL_VERTICAL
                            dd  0ffffffffh                          ; +12 +_ST_MEMVAR_OFFSET
                            dd  offset DEBI_keyboard_objects        ; +16 +_ST_OBJECT_KBD_OFFSET
                            dd  0ffffffffh                          ; +20 +_ST_OBJECT_MEMORY_OFFSET
                            dd  offset DEBI_p_mouse_objects         ; +24 +_ST_OBJECT_MOUSE_OFFSET
                            dd  offset DEBI_p_screen_objects        ; +28 +_ST_OBJECT_SCREEN_OFFSET
; fpu.2
                            db  _YES                                ; +00 Alterable?
                            db  _YES                                ; +01 Active?
                            dw  0                                   ; +02 +--Nuserved
                            dd  4*(15*8)                            ; +04 +_ST_OBJECT_UL_HORIZONTAL
                            dd  30*6                                ; +08 +_ST_OBJECT_UL_VERTICAL
                            dd  0ffffffffh                          ; +12 +_ST_MEMVAR_OFFSET
                            dd  offset DEBI_keyboard_objects        ; +16 +_ST_OBJECT_KBD_OFFSET
                            dd  0ffffffffh                          ; +20 +_ST_OBJECT_MEMORY_OFFSET
                            dd  offset DEBI_r_mouse_objects         ; +24 +_ST_OBJECT_MOUSE_OFFSET
                            dd  offset DEBI_r_screen_objects        ; +28 +_ST_OBJECT_SCREEN_OFFSET
; locals
                            db  _YES                                ; +00 Alterable?
                            db  _YES                                ; +01 Active?
                            dw  0                                   ; +02 +--Nuserved
                            dd  4*(15*8)                            ; +04 +_ST_OBJECT_UL_HORIZONTAL
                            dd  0*(13*6)                            ; +08 +_ST_OBJECT_UL_VERTICAL
                            dd  0ffffffffh                          ; +12 +_ST_MEMVAR_OFFSET
                            dd  offset DEBI_keyboard_objects        ; +16 +_ST_OBJECT_KBD_OFFSET
                            dd  0ffffffffh                          ; +20 +_ST_OBJECT_MEMORY_OFFSET
                            dd  offset DEBI_l_mouse_objects         ; +24 +_ST_OBJECT_MOUSE_OFFSET
                            dd  offset DEBI_l_screen_objects        ; +28 +_ST_OBJECT_SCREEN_OFFSET
; stack
                            db  _YES                                ; +00 Alterable?
                            db  _YES                                ; +01 Active?
                            dw  0                                   ; +02 +--Nuserved
                            dd  4*(15*8)                            ; +04 +_ST_OBJECT_UL_HORIZONTAL
                            dd  15*6                                ; +08 +_ST_OBJECT_UL_VERTICAL
                            dd  0ffffffffh                          ; +12 +_ST_MEMVAR_OFFSET
                            dd  offset DEBI_keyboard_objects        ; +16 +_ST_OBJECT_KBD_OFFSET
                            dd  0ffffffffh                          ; +20 +_ST_OBJECT_MEMORY_OFFSET
                            dd  offset DEBI_i_mouse_objects         ; +24 +_ST_OBJECT_MOUSE_OFFSET
                            dd  offset DEBI_i_screen_objects        ; +28 +_ST_OBJECT_SCREEN_OFFSET
; mem.3
                            db  _YES                                ; +00 Alterable?
                            db  _YES                                ; +01 Active?
                            dw  0                                   ; +02 +--Nuserved
                            dd  0                                   ; +04 +_ST_OBJECT_UL_HORIZONTAL
                            dd  2*(13*6)                            ; +08 +_ST_OBJECT_UL_VERTICAL
                            dd  0ffffffffh                          ; +12 +_ST_MEMVAR_OFFSET
                            dd  offset DEBI_keyboard_objects        ; +16 +_ST_OBJECT_KBD_OFFSET
                            dd  0ffffffffh                          ; +20 +_ST_OBJECT_MEMORY_OFFSET
                            dd  offset DEBI_n_mouse_objects         ; +24 +_ST_OBJECT_MOUSE_OFFSET
                            dd  offset DEBI_n_screen_objects        ; +28 +_ST_OBJECT_SCREEN_OFFSET
; mem.1
                            db  _YES                                ; +00 Alterable?
                            db  _YES                                ; +01 Active?
                            dw  0                                   ; +02 +--Nuserved
                            dd  3*(15*8)                            ; +04 +_ST_OBJECT_UL_HORIZONTAL
                            dd  2*(13*6)                            ; +08 +_ST_OBJECT_UL_VERTICAL
                            dd  0ffffffffh                          ; +12 +_ST_MEMVAR_OFFSET
                            dd  offset DEBI_keyboard_objects        ; +16 +_ST_OBJECT_KBD_OFFSET
                            dd  0ffffffffh                          ; +20 +_ST_OBJECT_MEMORY_OFFSET
                            dd  offset DEBI_m_mouse_objects         ; +24 +_ST_OBJECT_MOUSE_OFFSET
                            dd  offset DEBI_m_screen_objects        ; +28 +_ST_OBJECT_SCREEN_OFFSET
; mem.2
                            db  _YES                                ; +00 Alterable?
                            db  _YES                                ; +01 Active?
                            dw  0                                   ; +02 +--Nuserved
                            dd  0                                   ; +04 +_ST_OBJECT_UL_HORIZONTAL
                            dd  3*(13*6)                            ; +08 +_ST_OBJECT_UL_VERTICAL
                            dd  0ffffffffh                          ; +12 +_ST_MEMVAR_OFFSET
                            dd  offset DEBI_keyboard_objects        ; +16 +_ST_OBJECT_KBD_OFFSET
                            dd  0ffffffffh                          ; +20 +_ST_OBJECT_MEMORY_OFFSET
                            dd  offset DEBI_g_mouse_objects         ; +24 +_ST_OBJECT_MOUSE_OFFSET
                            dd  offset DEBI_g_screen_objects        ; +28 +_ST_OBJECT_SCREEN_OFFSET
; mem.2
                            db  _YES                                ; +00 Alterable?
                            db  _YES                                ; +01 Active?
                            dw  0                                   ; +02 +--Nuserved
                            dd  2*(15*8)                            ; +04 +_ST_OBJECT_UL_HORIZONTAL
                            dd  3*(13*6)                            ; +08 +_ST_OBJECT_UL_VERTICAL
                            dd  0ffffffffh                          ; +12 +_ST_MEMVAR_OFFSET
                            dd  offset DEBI_keyboard_objects        ; +16 +_ST_OBJECT_KBD_OFFSET
                            dd  0ffffffffh                          ; +20 +_ST_OBJECT_MEMORY_OFFSET
                            dd  offset DEBI_g_mouse_objects         ; +24 +_ST_OBJECT_MOUSE_OFFSET
                            dd  offset DEBI_g_screen_objects        ; +28 +_ST_OBJECT_SCREEN_OFFSET

                            db  3*_ST_LENGTH dup(_NO)               ; Allow space for the maximum of 15 windows on-screen
                                                                    ; at any one time.  That's 9 above, 3 below, plus the
                                                                    ; possibilty of 3 more = 15 items. :)

quick_watch_screen_object   db  _NO                                 ; +00 Alterable?
                            db  _YES                                ; +01 Active?
                            dw  0                                   ; +02 +--Nuserved
                            dd  4*(15*8)                            ; +04 +_ST_OBJECT_UL_HORIZONTAL
                            dd  3*(13*6)                            ; +08 +_ST_OBJECT_UL_VERTICAL
                            dd  0ffffffffh                          ; +12 +_ST_MEMVAR_OFFSET
                            dd  offset DEBI_keyboard_objects        ; +16 +_ST_OBJECT_KBD_OFFSET
                            dd  0ffffffffh                          ; +20 +_ST_OBJECT_MEMORY_OFFSET
                            dd  offset DEBI_j_mouse_objects         ; +24 +_ST_OBJECT_MOUSE_OFFSET
                            dd  offset DEBI_j_screen_objects        ; +28 +_ST_OBJECT_SCREEN_OFFSET

query_screen_object         db  _NO                                 ; +00 Alterable?
                            db  _YES                                ; +01 Active?
                            dw  0                                   ; +02 +--Nuserved
                            dd  0                                   ; +04 +_ST_OBJECT_UL_HORIZONTAL
                            dd  312                                 ; +08 +_ST_OBJECT_UL_VERTICAL
                            dd  0ffffffffh                          ; +12 +_ST_MEMVAR_OFFSET
                            dd  offset DEBI_keyboard_objects        ; +16 +_ST_OBJECT_KBD_OFFSET
                            dd  0ffffffffh                          ; +20 +_ST_OBJECT_MEMORY_OFFSET
                            dd  offset DEBI_k_mouse_objects         ; +24 +_ST_OBJECT_MOUSE_OFFSET
                            dd  offset DEBI_k_screen_objects        ; +28 +_ST_OBJECT_SCREEN_OFFSET

menu_bar_screen_object      db  _NO                                 ; +00 Alterable?
                            db  _YES                                ; +01 Active?
                            dw  0                                   ; +02 +--Nuserved
                            dd  0                                   ; +04 +_ST_OBJECT_UL_HORIZONTAL
                            dd  342                                 ; +08 +_ST_OBJECT_UL_VERTICAL
                            dd  0ffffffffh                          ; +12 +_ST_MEMVAR_OFFSET
                            dd  offset DEBI_keyboard_objects        ; +16 +_ST_OBJECT_KBD_OFFSET
                            dd  0ffffffffh                          ; +20 +_ST_OBJECT_MEMORY_OFFSET
                            dd  offset DEBI_o_mouse_objects         ; +24 +_ST_OBJECT_MOUSE_OFFSET
                            dd  offset DEBI_o_screen_objects        ; +28 +_ST_OBJECT_SCREEN_OFFSET
DEBI_screen_table_end:


DEBI_keyboard_objects:
    @FunctionHandlesObject  invDEBI_kbd_handler
    @End
DEBI_screen_objects:
    @End
DEBI_mouse_objects:
    @End


DEBI_general_menu:
    @MenuItem               "ִִ Add Window ִִ"
    @MenuItem               "Descriptor"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_new_window_descriptor
    @MenuItem               "Regs.1"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_new_window_regs_1
    @MenuItem               "Regs.3"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_new_window_regs_3
    @MenuItem               "MMX"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_new_window_mmx
    @MenuItem               "FPU.1"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_new_window_fpu_1
    @MenuItem               "FPU.2"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_new_window_fpu_2
    @MenuItem               "FPU.Summary"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_new_window_fpu_summary
    @MenuItem               "FPU.SaveState"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_new_window_fpu_savestate
    @MenuItem               "Mem.1"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_new_window_mem_1
    @MenuItem               "Mem.2"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_new_window_mem_2
    @MenuItem               "Mem.3"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_new_window_mem_3
    @MenuItem               "Mem.4"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_new_window_mem_4
    @MenuItem               "Locals"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_new_window_locals
    @MenuItem               "Stack"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_new_window_stack
    @End


                                ;          11111111112222222222333333333344444
                                ;012345678901234567890123456789012345678901234
DEBI_a_window               db  "ֹֽ Descriptor …ֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽ»",0
                            db  "                                            ÷",0
                            db  "     60  56    52  48    44  40    36  32   ÷",0
                            db  "   Úֲֲ¿Úֲֲ¿  Úֲֲ¿Úֲֲ¿  Úֲֲ¿Úֲֲ¿  Úֲֲ¿Úֲֲ¿   ÷",0
                            db  "   תתתתתתתת  תתתתתתתת  תתתתתתתת  תתתתתתתת   ÷",0
                            db  "   תתתתתתתת  תתתתתתתת  תתתתתתתת  תתתתתתתת   ÷",0
                            db  "   ְֱֱÙְֱֱÙ  ְֱֱÙְֱֱÙ  ְֱֱÙְֱֱÙ  ְֱֱÙְֱֱÙ   ÷",0
                            db  "     28  24    20  16    12   8     4   0   ÷",0
                            db  "                                            ÷",0
                            db  255

; * Note:  Refer to debi_mac.asp for information on these macros.  Basically they correctly arrange the variables in the required
;          sizes (bytes, words, dwords) and expand the X & Y coordinates to x*8 and y*8.

                            dw  45 * FONT_X
                            dw  9  * FONT_Y - 1
DEBI_a_screen_objects:
;REMEMBER, objects may not line up with above (it's recently modified)
    @DrawWindow             DEBI_a_window
    @ObjectMemSize          12+8
    @LoadTemp               _FAR_MEMORY_PTR,  0
    @DisplayTemp_relative   _UPPER_NIBBLE,  7, 7+12,  2, 4
    @DisplayTemp_relative   _LOWER_NIBBLE,  7, 7+12,  7, 4
    @DisplayTemp_relative   _UPPER_NIBBLE,  6, 6+12, 12, 4
    @DisplayTemp_relative   _LOWER_NIBBLE,  6, 6+12, 17, 4
    @DisplayTemp_relative   _UPPER_NIBBLE,  5, 5+12, 22, 4
    @DisplayTemp_relative   _LOWER_NIBBLE,  5, 5+12, 27, 4
    @DisplayTemp_relative   _UPPER_NIBBLE,  4, 4+12, 32, 4
    @DisplayTemp_relative   _LOWER_NIBBLE,  4, 4+12, 37, 4
    @DisplayTemp_relative   _UPPER_NIBBLE,  3, 3+12,  2, 5
    @DisplayTemp_relative   _LOWER_NIBBLE,  3, 3+12,  7, 5
    @DisplayTemp_relative   _UPPER_NIBBLE,  2, 2+12, 12, 5
    @DisplayTemp_relative   _LOWER_NIBBLE,  2, 2+12, 17, 5
    @DisplayTemp_relative   _UPPER_NIBBLE,  1, 1+12, 22, 5
    @DisplayTemp_relative   _LOWER_NIBBLE,  1, 1+12, 27, 5
    @DisplayTemp_relative   _UPPER_NIBBLE,  0, 0+12, 32, 5
    @DisplayTemp_relative   _LOWER_NIBBLE,  0, 0+12, 37, 5
    @End

                          ; x1, y1, x2, y2, function() that handles it when this item is clicked
ALIGN
DEBI_a_mouse_objects:
    @Left_single_click       1,  0,  1,  0, invDEBI_object_close
    @Right_single_click      3,  0, 16,  0, invDEBI_descriptor_right_click
    @Left_drag_start         0,  0, 44,  0, invDEBI_object_drag_start
    @Hover                   1,  4, 42,  5, 12, invDEBI_descriptor_hover
    @End



                                ;          11111111112222222222333333333344444
                                ;012345678901234567890123456789012345678901234
DEBI_b_window               db  "ֹֽ Regs.3 …ֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽ»",0
                            db  "  eax תתתת.תת.תת   ds תתתת   ®error¯ תתתתתתתת ÷",0
                            db  "  ebx תתתת.תת.תת   es תתתת  eflags תתתתתתתת ÷",0
                            db  "  ecx תתתת.תת.תת   fs תתתת   ֳ ntת ofת acfת ÷",0
                            db  "  edx תתתת.תת.תת   gs תתתת   ֳ pfת sfת  ifת ÷",0
                            db  "  esi תתתת.תתתת              ְ dfת zfת  cfת ÷",0
                            db  "  edi תתתת.תתתת    ss תתתת                  ÷",0
                            db  " ®data¯ תתתתתתתת    esp תתתתתתתת   cs תתתת    ÷",0
                            db  "  ®imm¯ תתתתתתתת    ebp תתתתתתתת  eip תתתתתתתת÷",0
                            db  255

                            dw  45 * FONT_X
                            dw  9  * FONT_Y - 1
DEBI_b_screen_objects:
    @DrawWindow                   DEBI_b_window
    @ObjectMemSize       64
    @DisplayEBP_relative _16,     46, 2, 6, 1                       ; upper 16-bits of eax
    @DisplayEBP_relative _8,      45, 1,11, 1                       ; ah
    @DisplayEBP_relative _8,      44, 0,14, 1                       ; al

    @DisplayEBP_relative _16,     42, 6, 6, 2                       ; upper 16-bits of ebx
    @DisplayEBP_relative _8,      41, 5,11, 2                       ; bh
    @DisplayEBP_relative _8,      40, 4,14, 2                       ; bl

    @DisplayEBP_relative _16,     38,10, 6, 3                       ; upper 16-bits of ecx
    @DisplayEBP_relative _8,      37, 9,11, 3                       ; ch
    @DisplayEBP_relative _8,      36, 8,14, 3                       ; cl

    @DisplayEBP_relative _16,     34,14, 6, 4                       ; upper 16-bits of edx
    @DisplayEBP_relative _8,      33,13,11, 4                       ; dh
    @DisplayEBP_relative _8,      32,12,14, 4                       ; dl

    @DisplayEBP_relative _16,     30,18, 6, 5                       ; upper 16-bits of esi
    @DisplayEBP_relative _16,     28,16,11, 5                       ; si

    @DisplayEBP_relative _16,     26,22, 6, 6                       ; upper 16-bits of edi
    @DisplayEBP_relative _16,     24,20,11, 6                       ; di

    @DisplayEBP_relative _16,     20,24,22, 1                       ; ds
    @DisplayEBP_relative _16,     16,28,22, 2                       ; es
    @DisplayEBP_relative _16,     12,32,22, 3                       ; fs
    @DisplayEBP_relative _16,      8,36,22, 4                       ; gs
    @DisplayEBP_relative _16,      4,40,22, 6                       ; ss
    @DisplayEBP_relative _32,     -4,44,22, 7                       ; esp
    @DisplayEBP_relative _32,      0,48,22, 8                       ; ebp
    @DisplayEBP_relative _16,     56,52,36, 7                       ; cs
    @DisplayEBP_relative _32,     52,56,36, 8                       ; eip

    @DisplayEBP_relative _32,     48,48,35, 1                       ; <error code>
    @DisplayEBP_relative _32,     60,60,35, 2                       ; eflags
    @DisplayEBP_flag              60,64, _EFLAGS_NT, 31, 3, "nt"
    @DisplayEBP_flag              60,64, _EFLAGS_PF, 31, 4, "pf"
    @DisplayEBP_flag              60,64, _EFLAGS_DF, 31, 5, "df"
    @DisplayEBP_flag              60,64, _EFLAGS_OF, 35, 3, "of"
    @DisplayEBP_flag              60,64, _EFLAGS_SF, 35, 4, "sf"
    @DisplayEBP_flag              60,64, _EFLAGS_ZF, 35, 5, "zf"
    @DisplayEBP_flag              60,64,_EFLAGS_ACF, 39, 3, "acf"
    @DisplayEBP_flag              60,64, _EFLAGS_IF, 40, 4, "if"
    @DisplayEBP_flag              60,64, _EFLAGS_CF, 40, 5, "cf"
    @ObjectPostDisplay   _32,      1, 7, "data"
    @ObjectPostDisplay   _32,      2, 8, "imm"
    @End

                          ; x1, y1, x2, y2, function() that handles it when this item is clicked
ALIGN
DEBI_b_mouse_objects:
    @Left_single_click       1,  0,  1,  0, invDEBI_object_close
    @Right_single_click      3,  0, 12,  0, invDEBI_reg_3_right_click
    @Left_drag_start         0,  0, 44,  0, invDEBI_object_drag_start
    @Abandon_if_not          6,  1, 43,  8
    @Hover                   6,  1, 15,  1, 44, invDEBI_quick_watch_show_EBP_relative_32                        ; eax
    @Hover                   6,  2, 15,  2, 40, invDEBI_quick_watch_show_EBP_relative_32                        ; ebx
    @Hover                   6,  3, 15,  3, 36, invDEBI_quick_watch_show_EBP_relative_32                        ; ecx
    @Hover                   6,  4, 15,  4, 32, invDEBI_quick_watch_show_EBP_relative_32                        ; edx
    @Hover                   6,  5, 15,  5, 28, invDEBI_quick_watch_show_EBP_relative_32                        ; esi
    @Hover                   6,  6, 15,  6, 24, invDEBI_quick_watch_show_EBP_relative_32                        ; edi
    @Hover                  22,  1, 25,  1, 20, invDEBI_quick_watch_show_EBP_relative_selector                  ; ds
    @Hover                  22,  2, 25,  2, 16, invDEBI_quick_watch_show_EBP_relative_selector                  ; es
    @Hover                  22,  3, 25,  3, 12, invDEBI_quick_watch_show_EBP_relative_selector                  ; fs
    @Hover                  22,  4, 25,  4,  8, invDEBI_quick_watch_show_EBP_relative_selector                  ; gs
    @Hover                  22,  6, 25,  6,  4, invDEBI_quick_watch_show_EBP_relative_selector                  ; ss
    @Hover                  22,  7, 29,  7, -4, invDEBI_quick_watch_show_EBP_relative_32                        ; esp
    @Hover                  22,  8, 29,  8,  0, invDEBI_quick_watch_show_EBP_relative_32                        ; ebp
    @Hover                  36,  7, 39,  7, 56, invDEBI_quick_watch_show_EBP_relative_selector                  ; cs
    @Hover                  36,  8, 43,  8, 52, invDEBI_quick_watch_show_EBP_relative_32                        ; eip
    @Hover                  35,  2, 42,  2, 60, invDEBI_quick_watch_show_EBP_relative_32                        ; eflags
    @Hover                  31,  3, 33,  3, 60, invDEBI_quick_watch_show_EBP_relative_eflags, _EFLAGS_NT
    @Hover                  31,  4, 33,  4, 60, invDEBI_quick_watch_show_EBP_relative_eflags, _EFLAGS_PF
    @Hover                  31,  5, 33,  5, 60, invDEBI_quick_watch_show_EBP_relative_eflags, _EFLAGS_DF
    @Hover                  35,  3, 37,  3, 60, invDEBI_quick_watch_show_EBP_relative_eflags, _EFLAGS_OF
    @Hover                  35,  4, 37,  4, 60, invDEBI_quick_watch_show_EBP_relative_eflags, _EFLAGS_SF
    @Hover                  35,  5, 37,  5, 60, invDEBI_quick_watch_show_EBP_relative_eflags, _EFLAGS_ZF
    @Hover                  39,  3, 42,  3, 60, invDEBI_quick_watch_show_EBP_relative_eflags, _EFLAGS_ACF
    @Hover                  40,  4, 42,  4, 60, invDEBI_quick_watch_show_EBP_relative_eflags, _EFLAGS_IF
    @Hover                  40,  5, 42,  5, 60, invDEBI_quick_watch_show_EBP_relative_eflags, _EFLAGS_CF
    @Edit                    6,  1, 15,  1, 44, edit_dword                                                      ; eax
    @Edit                    6,  2, 15,  2, 40, edit_dword                                                      ; ebx
    @Edit                    6,  3, 15,  3, 36, edit_dword                                                      ; ecx
    @Edit                    6,  4, 15,  4, 32, edit_dword                                                      ; edx
    @Edit                    6,  5, 15,  5, 28, edit_dword                                                      ; esi
    @Edit                    6,  6, 15,  6, 24, edit_dword                                                      ; edi
    @Edit                   22,  1, 25,  1, 20, edit_word                                                       ; ds
    @Edit                   22,  2, 25,  2, 16, edit_word                                                       ; es
    @Edit                   22,  3, 25,  3, 12, edit_word                                                       ; fs
    @Edit                   22,  4, 25,  4,  8, edit_word                                                       ; gs
    @Edit                   22,  6, 25,  6,  4, edit_word                                                       ; ss
    @Edit                   22,  7, 29,  7, -4, edit_dword                                                      ; esp
    @Edit                   22,  8, 29,  8,  0, edit_dword                                                      ; ebp
    @Edit                   36,  7, 39,  7, 56, edit_word                                                       ; cs
    @Edit                   36,  8, 43,  8, 52, edit_dword                                                      ; eip
    @Edit                   35,  2, 42,  2, 60, edit_dword                                                      ; eflags
    @Edit                   31,  3, 33,  3, 60, edit_flags, _EFLAGS_NT
    @Edit                   31,  4, 33,  4, 60, edit_flags, _EFLAGS_PF
    @Edit                   31,  5, 33,  5, 60, edit_flags, _EFLAGS_DF
    @Edit                   35,  3, 37,  3, 60, edit_flags, _EFLAGS_OF
    @Edit                   35,  4, 37,  4, 60, edit_flags, _EFLAGS_SF
    @Edit                   35,  5, 37,  5, 60, edit_flags, _EFLAGS_ZF
    @Edit                   39,  3, 42,  3, 60, edit_flags, _EFLAGS_ACF
    @Edit                   40,  4, 42,  4, 60, edit_flags, _EFLAGS_IF
    @Edit                   40,  5, 42,  5, 60, edit_flags, _EFLAGS_CF
    @End


                                ;   00000000-112233445566.. mov     dx,fs:[esi+ebx+00eeddcc]
                                ;          11111111112222222222333333333344444444445555555555
                                ;012345678901234567890123456789012345678901234567890123456789
DEBI_c_window               db  "ֹֽ CFSCA.2 …ֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽ»",0
                            db  "ּּּּ                                                       ÷",0
                            db  254,24

DEBI_c_keyboard_objects:
    @FunctionHandlesObject  invDEBI_CFSCA_kbd_handler
    @End

                            dw  60 * FONT_X
                            dw  26 * FONT_Y - 1
DEBI_c_screen_objects:
    @DrawWindow             DEBI_c_window
    @ObjectMemSize          4
    @FunctionHandlesObject  invDEBI_cfsca_2_window
    @End

ALIGN
DEBI_c_mouse_objects:
    @Left_single_click       1,  0,  1,  0, invDEBI_object_close
    @Right_single_click      3,  0, 13,  0, invDEBI_cfsca_2_right_click
    @Left_drag_start         0,  0, 59,  0, invDEBI_object_drag_start
    @End


                                ;   00000000-112233445566.. mov     dx,fs:[esi+ebx+00eeddcc]
                                ;          11111111112222222222333333333344444444445555555555
                                ;012345678901234567890123456789012345678901234567890123456789
DEBI_d_window               db  "ֹֽ CFSCA.3 …ֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽ»",0
                            db  "ּּּּ                                                       ÷",0
                            db  254, 37

DEBI_d_keyboard_objects:
    @FunctionHandlesObject  invDEBI_CFSCA_kbd_handler
    @End

                            dw  60 * FONT_X
                            dw  39 * FONT_Y - 1
DEBI_d_screen_objects:
    @DrawWindow             DEBI_d_window
    @ObjectMemSize          4
    @FunctionHandlesObject  invDEBI_cfsca_3_window
    @End

ALIGN
DEBI_d_mouse_objects:
    @Left_single_click       1,  0,  1,  0, invDEBI_object_close
    @Right_single_click      3,  0, 13,  0, invDEBI_cfsca_3_right_click
    @Left_drag_start         0,  0, 59,  0, invDEBI_object_drag_start
    @End



                                ;          11111111112222222222333333333344444
                                ;012345678901234567890123456789012345678901234
DEBI_e_window               db  "ֹֽ FPU.Summary …ֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽ»",0
                            db  "st7 תתתתתתתתתתתתתתתתתתתתת³   cw תתתת.תתתת   ÷",0
                            db  "st6 תתתתתתתתתתתתתתתתתתתתת³   sw תתתת.תתתת   ÷",0
                            db  "st5 תתתתתתתתתתתתתתתתתתתתת³   tw תתתת.תתתת   ÷",0
                            db  "st4 תתתתתתתתתתתתתתתתתתתתת³  fcs תתתת.תתתת   ÷",0
                            db  "st3 תתתתתתתתתתתתתתתתתתתתת³ feip תתתתתתתת    ÷",0
                            db  "st2 תתתתתתתתתתתתתתתתתתתתת³  fds תתתת.תתתת   ÷",0
                            db  "st1 תתתתתתתתתתתתתתתתתתתתת³ fesi תתתתתתתת    ÷",0
                            db  "st0 תתתתתתתתתתתתתתתתתתתתת³ ®11011¯תתת תתתתתתתת÷",0
                            db  255

                            dw  45 * FONT_X
                            dw  9  * FONT_Y - 1
DEBI_e_screen_objects:
    @DrawWindow             DEBI_e_window
    @ObjectMemSize          108
    @DisplayEBP_relative    _16,            (-200 + 002h), 002h, 32, 1                                      ; upper 16-bits of cw
    @DisplayEBP_relative    _16,            (-200 + 000h), 000h, 37, 1                                      ; lower 16-bits of cw

    @DisplayEBP_relative    _16,            (-200 + 006h), 006h, 32, 2                                      ; upper 16-bits of sw
    @DisplayEBP_relative    _16,            (-200 + 004h), 004h, 37, 2                                      ; lower 16-bits of sw

    @DisplayEBP_relative    _16,            (-200 + 00ah), 00ah, 32, 3                                      ; upper 16-bits of tw
    @DisplayEBP_relative    _16,            (-200 + 008h), 008h, 37, 3                                      ; lower 16-bits of tw

    @DisplayEBP_relative    _16,            (-200 + 012h), 012h, 32, 4                                      ; upper 16-bits of fcs
    @DisplayEBP_relative    _16,            (-200 + 010h), 010h, 37, 4                                      ; lower 16-bits of fcs

    @DisplayEBP_relative    _32,            (-200 + 00ch), 00ch, 32, 5                                      ; feip

    @DisplayEBP_relative    _16,            (-200 + 01ah), 01ah, 32, 6                                      ; upper 16-bits of fds
    @DisplayEBP_relative    _16,            (-200 + 018h), 018h, 37, 6                                      ; lower 16-bits of fds

    @DisplayEBP_relative    _32,            (-200 + 014h), 014h, 32, 7                                      ; fesi
    @DisplayEBP_relative    _LOWER_NIBBLE3, (-200 + 013h), 013h, 32, 8                                      ; instruction
    @DisplayEBP_relative    _BINARY8,       (-200 + 012h), 012h, 36, 8

    @DisplayEBP_relative    _ADJ_FLOAT21,               7, 062h,  4, 1                                      ; st7
    @DisplayEBP_relative    _ADJ_FLOAT21,               6, 058h,  4, 2                                      ; st6
    @DisplayEBP_relative    _ADJ_FLOAT21,               5, 04eh,  4, 3                                      ; st5
    @DisplayEBP_relative    _ADJ_FLOAT21,               4, 044h,  4, 4                                      ; st4
    @DisplayEBP_relative    _ADJ_FLOAT21,               3, 03ah,  4, 5                                      ; st3
    @DisplayEBP_relative    _ADJ_FLOAT21,               2, 030h,  4, 6                                      ; st2
    @DisplayEBP_relative    _ADJ_FLOAT21,               1, 026h,  4, 7                                      ; st1
    @DisplayEBP_relative    _ADJ_FLOAT21,               0, 01ch,  4, 8                                      ; st0
    @End

                          ; x1, y1, x2, y2, function() that handles it when this item is clicked
ALIGN
DEBI_e_mouse_objects:
    @Left_single_click       1,  0,  1,  0, invDEBI_object_close
    @Right_single_click      3,  0, 17,  0, invDEBI_fpu_summary_right_click
    @Left_drag_start         0,  0, 44,  0, invDEBI_object_drag_start
    @Left_drag_start         4,  1, 24,  8, invDEBI_stx_drag_start
    @Left_drag_stop          4,  1, 24,  8, invDEBI_stx_drag_stop
    @Right_single_click      4,  1, 24,  8, invDEBI_fpu_menu
    @Abandon_if_not          4,  1, 43,  8
    @Hover                   4,  1, 24,  1, (-200 + 98), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   4,  2, 24,  2, (-200 + 88), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   4,  3, 24,  3, (-200 + 78), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   4,  4, 24,  4, (-200 + 68), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   4,  5, 24,  5, (-200 + 58), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   4,  6, 24,  6, (-200 + 48), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   4,  7, 24,  7, (-200 + 38), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   4,  8, 24,  8, (-200 + 28), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                  32,  1, 40,  1, (-200 + 00), invDEBI_quick_watch_show_fpu_cw
    @Hover                  32,  2, 40,  2, (-200 + 04), invDEBI_quick_watch_show_fpu_sw
    @Hover                  32,  3, 40,  3, (-200 + 08), invDEBI_quick_watch_show_fpu_tw
    @Hover                  32,  4, 39,  4, (-200 + 68), invDEBI_quick_watch_show_selector
    @Hover                  32,  5, 40,  5, (-200 + 58), invDEBI_quick_watch_show_EBP_relative_32
    @Hover                  32,  6, 39,  6, (-200 + 48), invDEBI_quick_watch_show_selector
    @Hover                  32,  7, 40,  7, (-200 + 38), invDEBI_quick_watch_show_EBP_relative_32
    @Hover                  32,  8, 43,  8, (-200 + 28), invDEBI_quick_watch_show_fpu_opcode
    @End

DEBI_fpu_menu:
    @MenuItem               "finit"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_fpu_finit
    @MenuItem               "fchs"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_fpu_swap_sign
    @MenuItem               "ffree"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_fpu_ffree
    @MenuBar
    @MenuItem               "+0.00000"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_fpu_force_0
    @MenuItem               "+1.00000"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_fpu_force_1
    @MenuItem               "+10.0000"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_fpu_force_10
    @MenuItem               "pi"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_fpu_force_pi
    @MenuBar
    @MenuItem               "fldz"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_fpu_fld_0
    @MenuItem               "fld1"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_fpu_fld_1
    @MenuItem               "fld +10.0000"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_fpu_fld_10
    @MenuItem               "fldpi"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_fpu_fld_pi
    @MenuBar
    @MenuItem               "fmulp st1,st0"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_fpu_fmulp
    @MenuItem               "fdivp st1,st0"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_fpu_fdivp
    @MenuItem               "fdivp st0,st1"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_fpu_fdivrp
    @MenuBar
    @MenuItem               "fsave"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_fpu_save
    @MenuItem               "frstor"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_fpu_restore
    @End


                                ;          11111111112222222222333333333344444
                                ;012345678901234567890123456789012345678901234
DEBI_f_window               db  "ֹֽ FPU.SaveState …ֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽ»",0
                            db  "+00´    null.cw תתתת.תתתת                   ÷",0
                            db  "+04´    null.sw תתתת.תתתת  Control Word (cw)÷",0
                            db  "+08´    null.tw תתתת.תתתת   ®xxxx¯RcPc®xx¯PUOZDI÷",0
                            db  "+0c´       feip תתתתתתתת    תתתתתתתתתתתתתתתת÷",0
                            db  "+10´null.op.fcs תתתת.תתתת                   ÷",0
                            db  "+14´       fesi תתתתתתתת    Status Word (sw)÷",0
                            db  "+18´   null.fds תתתת.תתתת   B3tos210ESPUOZDI÷",0
                            db  "   ´                        תתתתתתתתתתתתתתתת÷",0
                            db  "+62´7 תתתתתתתתתתתתתתתתתתתת³                 ÷",0
                            db  "+58´6 תתתתתתתתתתתתתתתתתתתת³   Tag Word (tw) ÷",0
                            db  "+43´5 תתתתתתתתתתתתתתתתתתתת³ 7766554433221100÷",0
                            db  "+44´4 תתתתתתתתתתתתתתתתתתתת³ תתתתתתתתתתתתתתתת÷",0
                            db  "+3a´3 תתתתתתתתתתתתתתתתתתתת³                 ÷",0
                            db  "+30´2 תתתתתתתתתתתתתתתתתתתת³     Opcode (op) ÷",0
                            db  "+26´1 תתתתתתתתתתתתתתתתתתתת³ ®11011¯תתתתתתתתתתת÷",0
                            db  "+1c´0 תתתתתתתתתתתתתתתתתתתת³                 ÷",0
                            db  255

                            dw  45 * FONT_X
                            dw  18 * FONT_Y - 1
DEBI_f_screen_objects:
    @DrawWindow             DEBI_f_window
    @ObjectMemSize          108
    @DisplayEBP_relative    _16,        (-200 + 002h), 002h, 16, 1                                          ; upper 16-bits of cw
    @DisplayEBP_relative    _16,        (-200 + 000h), 000h, 16, 1                                          ; lower 16-bits of cw

    @DisplayEBP_relative    _16,        (-200 + 006h), 006h, 16, 2                                          ; upper 16-bits of sw
    @DisplayEBP_relative    _16,        (-200 + 004h), 004h, 16, 2                                          ; lower 16-bits of sw

    @DisplayEBP_relative    _16,        (-200 + 00ah), 00ah, 16, 3                                          ; upper 16-bits of tw
    @DisplayEBP_relative    _16,        (-200 + 008h), 008h, 16, 3                                          ; lower 16-bits of tw

    @DisplayEBP_relative    _32,        (-200 + 010h), 010h, 16, 4                                          ; feip

    @DisplayEBP_relative    _16,        (-200 + 012h), 012h, 16, 5                                          ; opcode
    @DisplayEBP_relative    _16,        (-200 + 00ch), 00ch, 16, 5                                          ; fcs

    @DisplayEBP_relative    _32,        (-200 + 014h), 014h, 16, 6                                          ; fesi

    @DisplayEBP_relative    _16,        (-200 + 01ah), 01ah, 16, 7                                          ; upper 16-bits of fds
    @DisplayEBP_relative    _16,        (-200 + 018h), 018h, 16, 7                                          ; lower 16-bits of fds

    @DisplayEBP_relative    _TBYTE,     (-200 + 062h), 062h,  6, 10                                         ; st7
    @DisplayEBP_relative    _TBYTE,     (-200 + 058h), 058h,  6, 11                                         ; st6
    @DisplayEBP_relative    _TBYTE,     (-200 + 04eh), 04eh,  6, 12                                         ; st5
    @DisplayEBP_relative    _TBYTE,     (-200 + 044h), 044h,  6, 13                                         ; st4
    @DisplayEBP_relative    _TBYTE,     (-200 + 03ah), 03ah,  6, 14                                         ; st3
    @DisplayEBP_relative    _TBYTE,     (-200 + 030h), 030h,  6, 15                                         ; st2
    @DisplayEBP_relative    _TBYTE,     (-200 + 026h), 026h,  6, 16                                         ; st1
    @DisplayEBP_relative    _TBYTE,     (-200 + 01ch), 01ch,  6, 17                                         ; st0
    @DisplayEBP_relative    _BINARY16,  (-200 + 000h), 000h, 28, 4
    @DisplayEBP_relative    _BINARY16,  (-200 + 004h), 004h, 28, 8
    @DisplayEBP_relative    _BINARY16,  (-200 + 008h), 008h, 28, 12
    @DisplayEBP_relative    _BINARY11,  (-200 + 00ch), 00ch, 33, 15
    @End

                          ; x1, y1, x2, y2, function() that handles it when this item is clicked
ALIGN
DEBI_f_mouse_objects:
    @Left_single_click       1,  0,  1,  0, invDEBI_object_close
    @Right_single_click      3,  0, 17,  0, invDEBI_fpu_save_state_right_click
    @Left_drag_start         0,  0, 44,  0, invDEBI_object_drag_start
    @Left_drag_start         6,  9, 25, 16, invDEBI_stx_drag_start
    @Left_drag_stop          6,  9, 25, 16, invDEBI_stx_drag_stop
    @Right_single_click      6,  9, 25, 16, invDEBI_fpu_menu
    @Hover                  16,  1, 24,  1, (-200 + 00), invDEBI_quick_watch_show_fpu_cw
    @Hover                  16,  2, 24,  2, (-200 + 04), invDEBI_quick_watch_show_fpu_sw
    @Hover                  16,  3, 24,  3, (-200 + 08), invDEBI_quick_watch_show_fpu_tw
    @Edit                   16,  1, 24,  1, (-200 + 98), edit_word
    @Edit                   16,  2, 24,  2, (-200 + 88), edit_word
    @Edit                   16,  3, 24,  3, (-200 + 78), edit_word
    @Hover                  16,  4, 23,  4, (-200 + 68), invDEBI_quick_watch_show_EBP_relative_32
    @Hover                  16,  5, 24,  5, (-200 + 58), invDEBI_quick_watch_show_32_selector_separated
    @Hover                  16,  6, 23,  6, (-200 + 48), invDEBI_quick_watch_show_EBP_relative_32
    @Hover                  16,  7, 24,  7, (-200 + 38), invDEBI_quick_watch_show_32_selector_separated
    @Hover                  28,  4, 43,  4, (-200 + 00), invDEBI_quick_watch_show_fpu_cw
    @Hover                  28,  8, 43,  8, (-200 + 04), invDEBI_quick_watch_show_fpu_sw
    @Hover                  28, 12, 43, 12, (-200 + 08), invDEBI_quick_watch_show_fpu_tw
    @Edit                   28,  4, 43,  4, (-200 + 98), edit_binary_32
    @Edit                   28,  8, 43,  8, (-200 + 88), edit_binary_32
    @Edit                   28, 12, 43, 12, (-200 + 78), edit_binary_32
    @Hover                  33, 15, 43, 15, (-200 + 28), invDEBI_quick_watch_show_fpu_opcode
    @Hover                   6,  9, 25,  9, (-200 + 98), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   6, 10, 25, 10, (-200 + 88), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   6, 11, 25, 11, (-200 + 78), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   6, 12, 25, 12, (-200 + 68), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   6, 13, 25, 13, (-200 + 58), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   6, 14, 25, 14, (-200 + 48), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   6, 15, 25, 15, (-200 + 38), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   6, 16, 25, 16, (-200 + 28), invDEBI_quick_watch_show_EBP_relative_80
    @End


                                ;          11111111112222222222
                                ;012345678901234567890123456789
DEBI_g_window               db  "ֹֽ Mem.2 …ֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽ»",0      ; 0
                            db  "                             ÷",0      ; 1
                            db  "                             ÷",0      ; 2
                            db  "                             ÷",0      ; 3
                            db  "                             ÷",0      ; 4
                            db  "                             ÷",0      ; 5
                            db  "                             ÷",0      ; 6
                            db  "                             ÷",0      ; 7
                            db  "                             ÷",0      ; 8
                            db  "                             ÷",0      ; 9
                            db  "                             ÷",0      ; 10
                            db  "                             ÷",0      ; 11
                            db  "                             ÷",0      ; 12
                            db  255
                                                                    ;                  the editable variable should be)
                            dw  30 * FONT_X
                            dw  13 * FONT_Y - 1
DEBI_g_screen_objects:
    @DrawWindow             DEBI_g_window
    @ObjectMemSize          4+2+96              ; +4 is for PTR, +2 is for offset, +96 is for data
    @FunctionHandlesObject  invDEBI_mem2_window
    @End

                          ; x1, y1, x2, y2, function() that handles it when this item is clicked
ALIGN
DEBI_g_mouse_objects:
    @Left_single_click       1,  0,  1,  0, invDEBI_object_close
    @Left_single_click       3,  0, 11,  0, invDEBI_address_expression
    @Right_single_click      3,  0, 11,  0, invDEBI_mem_2_right_click
    @Left_drag_start         0,  0, 29,  0, invDEBI_object_drag_start
    @Abandon_if_not          6,  1, 28, 12
    @Hover                   6,  1, 13,  1, 00+6, invDEBI_quick_watch_mem_32
    @Hover                  21,  1, 28,  1, 04+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  2, 13,  2, 08+6, invDEBI_quick_watch_mem_32
    @Hover                  21,  2, 28,  2, 12+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  3, 13,  3, 16+6, invDEBI_quick_watch_mem_32
    @Hover                  21,  3, 28,  3, 20+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  4, 13,  4, 24+6, invDEBI_quick_watch_mem_32
    @Hover                  21,  4, 28,  4, 28+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  5, 13,  5, 32+6, invDEBI_quick_watch_mem_32
    @Hover                  21,  5, 28,  5, 36+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  6, 13,  6, 40+6, invDEBI_quick_watch_mem_32
    @Hover                  21,  6, 28,  6, 44+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  7, 13,  7, 48+6, invDEBI_quick_watch_mem_32
    @Hover                  21,  7, 28,  7, 52+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  8, 13,  8, 56+6, invDEBI_quick_watch_mem_32
    @Hover                  21,  8, 28,  8, 60+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  8, 13,  9, 64+6, invDEBI_quick_watch_mem_32
    @Hover                  21,  8, 28,  9, 68+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  8, 13, 10, 72+6, invDEBI_quick_watch_mem_32
    @Hover                  21,  8, 28, 10, 76+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  8, 13, 11, 80+6, invDEBI_quick_watch_mem_32
    @Hover                  21,  8, 28, 11, 84+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  8, 13, 12, 88+6, invDEBI_quick_watch_mem_32
    @Hover                  21,  8, 28, 12, 92+6, invDEBI_quick_watch_mem_32
    @End



                                ;          11111111112222222222333333333344444444445555555555
                                ;012345678901234567890123456789012345678901234567890123456789
DEBI_h_window               db  "ֹֽ Mem.4 …ֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽ»",0        ; 0
                            db  "                                                           ÷",0        ; 1
                            db  "                                                           ÷",0        ; 2
                            db  "                                                           ÷",0        ; 3
                            db  "                                                           ÷",0        ; 4
                            db  "                                                           ÷",0        ; 5
                            db  "                                                           ÷",0        ; 6
                            db  "                                                           ÷",0        ; 7
                            db  "                                                           ÷",0        ; 8
                            db  "                                                           ÷",0        ; 9
                            db  "                                                           ÷",0        ; 10
                            db  "                                                           ÷",0        ; 11
                            db  "                                                           ÷",0        ; 12
                            db  255

                            dw  60 * FONT_X
                            dw  13 * FONT_Y - 1
DEBI_h_screen_objects:
    @DrawWindow             DEBI_h_window
    @ObjectMemSize          4+2+208             ; +4 is for PTR, +2 is for offset, +208 is for data
    @FunctionHandlesObject  invDEBI_mem4_window
    @End

                          ; x1, y1, x2, y2, function() that handles it when this item is clicked
ALIGN
DEBI_h_mouse_objects:
    @Left_single_click       1,  0,  1,  0, invDEBI_object_close
    @Right_single_click      3,  0, 11,  0, invDEBI_mem_4_right_click
    @Left_single_click       3,  0, 11,  0, invDEBI_address_expression
    @Left_drag_start         0,  0, 44,  0, invDEBI_object_drag_start
    @End



                                ;          11111
                                ;012345678901234
DEBI_i_window               db  "ֹֽ Stack …ֽֽ»",0
                            db  "+0034 תתתתתתתת÷",0
                            db  "+0030 תתתתתתתת÷",0
                            db  "+002c תתתתתתתת÷",0
                            db  "+0028 תתתתתתתת÷",0
                            db  "+0024 תתתתתתתת÷",0
                            db  "+0020 תתתתתתתת÷",0
                            db  "+001c תתתתתתתת÷",0
                            db  "+0018 תתתתתתתת÷",0
                            db  "+0014 תתתתתתתת÷",0
                            db  "+0010 תתתתתתתת÷",0
                            db  "+000c תתתתתתתת÷",0
                            db  "+0008 תתתתתתתת÷",0
                            db  "+0004 תתתתתתתת÷",0
                            db  "+0000 תתתתתתתת÷",0
                            db  255

                            dw  15 * FONT_X
                            dw  15 * FONT_Y - 1
DEBI_i_screen_objects:
    @DrawWindow             DEBI_i_window
    @ObjectMemSize          32
    @DisplayESP_through_EBP_relative   _32,  34h, 28, 6, 1
    @DisplayESP_through_EBP_relative   _32,  30h, 28, 6, 2
    @DisplayESP_through_EBP_relative   _32,  2ch, 28, 6, 3
    @DisplayESP_through_EBP_relative   _32,  28h, 28, 6, 4
    @DisplayESP_through_EBP_relative   _32,  24h, 28, 6, 5
    @DisplayESP_through_EBP_relative   _32,  20h, 28, 6, 6
    @DisplayESP_through_EBP_relative   _32,  1ch, 28, 6, 7
    @DisplayESP_through_EBP_relative   _32,  18h, 24, 6, 8
    @DisplayESP_through_EBP_relative   _32,  14h, 20, 6, 9
    @DisplayESP_through_EBP_relative   _32,  10h, 16, 6,10
    @DisplayESP_through_EBP_relative   _32,  0ch, 12, 6,11
    @DisplayESP_through_EBP_relative   _32,  08h,  8, 6,12
    @DisplayESP_through_EBP_relative   _32,  04h,  4, 6,13
    @DisplayESP_through_EBP_relative   _32,  00h,  0, 6,14
    @End

ALIGN
DEBI_i_mouse_objects:
    @Left_single_click       1,  0,  1,  0, invDEBI_object_close
    @Right_single_click      3,  0, 11,  0, invDEBI_stack_right_click
    @Left_drag_start         0,  0, 14,  0, invDEBI_object_drag_start
    @Abandon_if_not          6,  1, 13, 14
    @Hover                   6,  1, 13,  1, 52, invDEBI_quick_watch_stack_32
    @Hover                   6,  2, 13,  2, 48, invDEBI_quick_watch_stack_32
    @Hover                   6,  3, 13,  3, 44, invDEBI_quick_watch_stack_32
    @Hover                   6,  4, 13,  4, 40, invDEBI_quick_watch_stack_32
    @Hover                   6,  5, 13,  5, 36, invDEBI_quick_watch_stack_32
    @Hover                   6,  6, 13,  6, 32, invDEBI_quick_watch_stack_32
    @Hover                   6,  7, 13,  7, 28, invDEBI_quick_watch_stack_32
    @Hover                   6,  8, 13,  8, 24, invDEBI_quick_watch_stack_32
    @Hover                   6,  9, 13,  9, 20, invDEBI_quick_watch_stack_32
    @Hover                   6, 10, 13, 10, 16, invDEBI_quick_watch_stack_32
    @Hover                   6, 11, 13, 11, 12, invDEBI_quick_watch_stack_32
    @Hover                   6, 12, 13, 12, 08, invDEBI_quick_watch_stack_32
    @Hover                   6, 13, 13, 13, 04, invDEBI_quick_watch_stack_32
    @Hover                   6, 14, 13, 14, 00, invDEBI_quick_watch_stack_32
    @End



                                ;          11111111112222222222
                                ;012345678901234567890123456789
t_and_s_displayed           db  0
DEBI_j_window               db  "ֹֽ€ Quick watch „ֽֽֽֽֽֽֽֽֽֽֽֽ»",0
quick_12                    db  "                             ÷",0
quick_11                    db  "                             ÷",0
quick_10                    db  "                             ÷",0
quick_9                     db  "                             ÷",0
quick_8                     db  "                             ÷",0
quick_7                     db  "                             ÷",0
quick_6                     db  "                             ÷",0
quick_5                     db  "                             ÷",0
quick_4                     db  "                             ÷",0
quick_3                     db  "                             ÷",0
quick_2                     db  "                             ÷",0
quick_1                     db  "                             ÷",0
                            db  255

                            dw  30 * FONT_X
                            dw  13 * FONT_Y - 1
DEBI_j_screen_objects:
    @AlwaysDrawWindow       DEBI_j_window
    @ObjectMemSize          0
    @FunctionHandlesObject  invDEBI_quick_watch_window
    @End

ALIGN
DEBI_j_mouse_objects:
    @Left_single_click       2,  0, 16,  0, invDEBI_quick_watch_click
    @Right_single_click      2,  0, 16,  0, invDEBI_quick_watch_right_click
    @End



                                ;          11111111112222222222333333333344444444445555555555666666666677777777778888888888
                                ;012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789
DEBI_k_window               db  "ֹֽ€ Query „ֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽ»",0
query_3                     db  "                                                                                         ÷",0
query_2                     db  "Low-Level Debi(tm) Debugger for the Exodus Operating System                              ÷",0
query_1                     db  "(c) Beatleworks, Inc. 10.10.2010                                                         ÷",0
                            db  "ÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊ¼",0
                            db  255

                            dw  90 * FONT_X
                            dw  5  * FONT_Y - 1
DEBI_k_screen_objects:
    @AlwaysDrawWindow       DEBI_k_window
    @ObjectMemSize          0
    @FunctionHandlesObject  invDEBI_query_window
    @End

ALIGN
DEBI_k_mouse_objects:
    @Right_single_click      2,  0, 16,  0, invDEBI_query_right_click
    @End



                                ;          11111
                                ;012345678901234
DEBI_l_window               db  "ֹֽ Locals …ֽ»",0
                            db  " -004 תתתתתתתת÷",0
                            db  " -008 תתתתתתתת÷",0
                            db  " -00c תתתתתתתת÷",0
                            db  " -010 תתתתתתתת÷",0
                            db  " -014 תתתתתתתת÷",0
                            db  " -018 תתתתתתתת÷",0
                            db  " -01c תתתתתתתת÷",0
                            db  " -020 תתתתתתתת÷",0
                            db  " -024 תתתתתתתת÷",0
                            db  " -028 תתתתתתתת÷",0
                            db  " -02c תתתתתתתת÷",0
                            db  " -030 תתתתתתתת÷",0
                            db  " -034 תתתתתתתת÷",0
                            db  " -038 תתתתתתתת÷",0
                            db  255

                            dw  15 * FONT_X
                            dw  15 * FONT_Y - 1
DEBI_l_screen_objects:
    @DrawWindow             DEBI_l_window
    @ObjectMemSize          32
    @DisplayEBP_through_EBP_relative   _32, -04h,  0, 6, 1
    @DisplayEBP_through_EBP_relative   _32, -08h,  4, 6, 2
    @DisplayEBP_through_EBP_relative   _32, -0ch,  8, 6, 3
    @DisplayEBP_through_EBP_relative   _32, -10h, 12, 6, 4
    @DisplayEBP_through_EBP_relative   _32, -14h, 16, 6, 5
    @DisplayEBP_through_EBP_relative   _32, -18h, 20, 6, 6
    @DisplayEBP_through_EBP_relative   _32, -1ch, 24, 6, 7
    @DisplayEBP_through_EBP_relative   _32, -20h, 28, 6, 8
    @DisplayEBP_through_EBP_relative   _32, -24h, 28, 6, 9
    @DisplayEBP_through_EBP_relative   _32, -28h, 28, 6,10
    @DisplayEBP_through_EBP_relative   _32, -2ch, 28, 6,11
    @DisplayEBP_through_EBP_relative   _32, -30h, 28, 6,12
    @DisplayEBP_through_EBP_relative   _32, -34h, 28, 6,13
    @DisplayEBP_through_EBP_relative   _32, -38h, 28, 6,14
    @End

ALIGN
DEBI_l_mouse_objects:
    @Left_single_click       1,  0,  1,  0, invDEBI_object_close
    @Right_single_click      3,  0, 12,  0, invDEBI_locals_right_click
    @Left_drag_start         0,  0, 14,  0, invDEBI_object_drag_start
    @Abandon_if_not          6,  1, 13, 14
    @Hover                   6,  1, 13,  1,  -4, invDEBI_quick_watch_locals_32
    @Hover                   6,  2, 13,  2,  -8, invDEBI_quick_watch_locals_32
    @Hover                   6,  3, 13,  3, -12, invDEBI_quick_watch_locals_32
    @Hover                   6,  4, 13,  4, -16, invDEBI_quick_watch_locals_32
    @Hover                   6,  5, 13,  5, -20, invDEBI_quick_watch_locals_32
    @Hover                   6,  6, 13,  6, -24, invDEBI_quick_watch_locals_32
    @Hover                   6,  7, 13,  7, -28, invDEBI_quick_watch_locals_32
    @Hover                   6,  8, 13,  8, -32, invDEBI_quick_watch_locals_32
    @Hover                   6,  9, 13,  9, -36, invDEBI_quick_watch_locals_32
    @Hover                   6, 10, 13, 10, -40, invDEBI_quick_watch_locals_32
    @Hover                   6, 11, 13, 11, -44, invDEBI_quick_watch_locals_32
    @Hover                   6, 12, 13, 12, -48, invDEBI_quick_watch_locals_32
    @Hover                   6, 13, 13, 13, -52, invDEBI_quick_watch_locals_32
    @Hover                   6, 14, 13, 14, -56, invDEBI_quick_watch_locals_32
    @End



                                ;          11111
                                ;012345678901234
DEBI_m_window               db  "ֹֽ Mem.1 …ֽֽ»",0     ; 0
                            db  "              ÷",0     ; 1
                            db  "              ÷",0     ; 2
                            db  "              ÷",0     ; 3
                            db  "              ÷",0     ; 4
                            db  "              ÷",0     ; 5
                            db  "              ÷",0     ; 6
                            db  "              ÷",0     ; 7
                            db  "              ÷",0     ; 8
                            db  "              ÷",0     ; 9
                            db  "              ÷",0     ; 10
                            db  "              ÷",0     ; 11
                            db  "              ÷",0     ; 12
                            db  255

                            dw  15 * FONT_X
                            dw  13 * FONT_Y - 1
DEBI_m_screen_objects:
    @DrawWindow             DEBI_m_window
    @ObjectMemSize          4+2+48              ; +4 is for PTR, +2 is for offset, +48 is for data
    @FunctionHandlesObject  invDEBI_mem1_window
    @End

ALIGN
DEBI_m_mouse_objects:
    @Left_single_click       1,  0,  1,  0, invDEBI_object_close
    @Left_single_click       3,  0, 11,  0, invDEBI_address_expression
    @Right_single_click      3,  0, 11,  0, invDEBI_mem_1_right_click
    @Left_drag_start         0,  0, 14,  0, invDEBI_object_drag_start
    @Abandon_if_not          6,  1, 13, 12
    @Hover                   6,  1, 13,  1,  0+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  2, 13,  2,  4+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  3, 13,  3,  8+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  4, 13,  4, 12+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  5, 13,  5, 16+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  6, 13,  6, 20+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  7, 13,  7, 24+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  8, 13,  8, 28+6, invDEBI_quick_watch_mem_32
    @End



                                ;          11111111112222222222333333333344444
                                ;012345678901234567890123456789012345678901234
DEBI_n_window               db  "ֹֽ Mem.3 …ֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽ»",0       ; 0
                            db  "                                            ÷",0       ; 1
                            db  "                                            ÷",0       ; 2
                            db  "                                            ÷",0       ; 3
                            db  "                                            ÷",0       ; 4
                            db  "                                            ÷",0       ; 5
                            db  "                                            ÷",0       ; 6
                            db  "                                            ÷",0       ; 7
                            db  "                                            ÷",0       ; 8
                            db  "                                            ÷",0       ; 9
                            db  "                                            ÷",0       ; 10
                            db  "                                            ÷",0       ; 11
                            db  "                                            ÷",0       ; 12
                            db  255

                            dw  45 * FONT_X
                            dw  13 * FONT_Y - 1
DEBI_n_screen_objects:
    @DrawWindow             DEBI_n_window
    @ObjectMemSize          4+2+144             ; +4 is for PTR, +2 is for offset, +144 is for data
    @FunctionHandlesObject  invDEBI_mem3_window
    @End

ALIGN
DEBI_n_mouse_objects:
    @Left_single_click       1,  0,  1,  0, invDEBI_object_close
    @Right_single_click      3,  0, 11,  0, invDEBI_mem_3_right_click
    @Left_single_click       3,  0, 11,  0, invDEBI_address_expression
    @Left_drag_start         0,  0, 44,  0, invDEBI_object_drag_start
    @Abandon_if_not          6,  1, 43, 12
    @Hover                   6,  1, 13,  1,  0+6, invDEBI_quick_watch_mem_32        ; 00-28
    @Hover                   6,  2, 13,  2,  4+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  3, 13,  3,  8+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  4, 13,  4, 12+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  5, 13,  5, 16+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  6, 13,  6, 20+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  7, 13,  7, 24+6, invDEBI_quick_watch_mem_32
    @Hover                   6,  8, 13,  8, 28+6, invDEBI_quick_watch_mem_32
    @Hover                  21,  1, 28,  1, 32+6, invDEBI_quick_watch_mem_32        ; 32-60
    @Hover                  21,  2, 28,  2, 36+6, invDEBI_quick_watch_mem_32
    @Hover                  21,  3, 28,  3, 40+6, invDEBI_quick_watch_mem_32
    @Hover                  21,  4, 28,  4, 44+6, invDEBI_quick_watch_mem_32
    @Hover                  21,  5, 28,  5, 48+6, invDEBI_quick_watch_mem_32
    @Hover                  21,  6, 28,  6, 52+6, invDEBI_quick_watch_mem_32
    @Hover                  21,  7, 28,  7, 56+6, invDEBI_quick_watch_mem_32
    @Hover                  21,  8, 28,  8, 60+6, invDEBI_quick_watch_mem_32
    @Hover                  36,  1, 43,  1, 64+6, invDEBI_quick_watch_mem_32        ; 64-92
    @Hover                  36,  2, 43,  2, 68+6, invDEBI_quick_watch_mem_32
    @Hover                  36,  3, 43,  3, 72+6, invDEBI_quick_watch_mem_32
    @Hover                  36,  4, 43,  4, 76+6, invDEBI_quick_watch_mem_32
    @Hover                  36,  5, 43,  5, 80+6, invDEBI_quick_watch_mem_32
    @Hover                  36,  6, 43,  6, 84+6, invDEBI_quick_watch_mem_32
    @Hover                  36,  7, 43,  7, 88+6, invDEBI_quick_watch_mem_32
    @Hover                  36,  8, 43,  8, 92+6, invDEBI_quick_watch_mem_32
    @End



                                ;          11111111112222222222333333333344444444445555555555666666666677777777778888888888
                                ;012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789
DEBI_o_window               db  " € redraw „                                   € continue „  € break „  € over „  € step „ ",0
                            db  255

                            dw  90 * FONT_X
                            dw  1  * FONT_Y - 1
DEBI_o_screen_objects:
    @AlwaysDrawWindow       DEBI_o_window
    @ObjectMemSize  0
    @End

ALIGN
DEBI_o_mouse_objects:
    @Immediate              _LEFT_SINGLE_CLICK,  1,  0, 10,  0, invDEBI_clear_screen_and_redraw_windows
    @Immediate              _LEFT_SINGLE_CLICK, 46,  0, 57,  0, invDEBI_menu_continue_click
    @Immediate              _LEFT_SINGLE_CLICK, 60,  0, 68,  0, invDEBI_menu_break_click
    @Immediate              _LEFT_SINGLE_CLICK, 71,  0, 78,  0, invDEBI_menu_over_click
    @Immediate              _LEFT_SINGLE_CLICK, 81,  0, 88,  0, invDEBI_menu_step_click
    @End


                                ;          11111
                                ;012345678901234
DEBI_p_window               db  "ֹֽ Regs.1 …ֽ»",0
                            db  "  cs תתתת     ÷",0
                            db  " eip תתתתתתתת ÷",0
                            db  "ִִִִִִִִִִִִִִ÷",0
                            db  " eax תתתתתתתת ÷",0
                            db  " ebx תתתתתתתת ÷",0
                            db  " ecx תתתתתתתת ÷",0
                            db  " edx תתתתתתתת ÷",0
                            db  " esi תתתתתתתת ÷",0
                            db  " edi תתתתתתתת ÷",0
                            db  "ִִִִִִִִִִִִִִ÷",0
                            db  "  ds תתתת     ÷",0
                            db  "  es תתתת     ÷",0
                            db  "  fs תתתת     ÷",0
                            db  "  gs תתתת     ÷",0
                            db  "  ss תתתת     ÷",0
                            db  " esp תתתתתתתת ÷",0
                            db  " ebp תתתתתתתת ÷",0
                            db  "ִִִִִִִִִִִִִִ÷",0
                            db  " eflags       ÷",0
                            db  "   תתתתתתתת   ÷",0
                            db  "ִִִִִִִִִִִִִִ÷",0
                            db  " ntת ofת acfת ÷",0
                            db  " pfת sfת  ifת ÷",0
                            db  " dfת zfת  cfת ÷",0
                            db  "ִִִִִִִִִִִִִִ÷",0
                            db  " ®err¯ תתתתתתתת ÷",0
                            db  "®data¯ תתתתתתתת ÷",0
                            db  " ®imm¯ תתתתתתתת ÷",0
                            db  "              ÷",0
                            db  255

                            dw  15 * FONT_X
                            dw  30 * FONT_Y - 1
DEBI_p_screen_objects:
    @DrawWindow             DEBI_p_window
    @ObjectMemSize      64
    @DisplayEBP_relative _16,     56,52, 5, 1                       ; cs
    @DisplayEBP_relative _32,     52,56, 5, 2                       ; eip
    @DisplayEBP_relative _32,     44, 0, 5, 4                       ; upper 16-bits of eax
    @DisplayEBP_relative _32,     40, 4, 5, 5                       ; upper 16-bits of ebx
    @DisplayEBP_relative _32,     36, 8, 5, 6                       ; upper 16-bits of ecx
    @DisplayEBP_relative _32,     32,12, 5, 7                       ; upper 16-bits of edx
    @DisplayEBP_relative _32,     28,16, 5, 8                       ; upper 16-bits of esi
    @DisplayEBP_relative _32,     24,20, 5, 9                       ; upper 16-bits of edi
    @DisplayEBP_relative _16,     20,24, 5, 11                      ; ds
    @DisplayEBP_relative _16,     16,28, 5, 12                      ; es
    @DisplayEBP_relative _16,     12,32, 5, 13                      ; fs
    @DisplayEBP_relative _16,      8,36, 5, 14                      ; gs
    @DisplayEBP_relative _16,      4,40, 5, 15                      ; ss
    @DisplayEBP_relative _32,     -4,44, 5, 16                      ; esp
    @DisplayEBP_relative _32,      0,48, 5, 17                      ; ebp
    @DisplayEBP_relative _32,     60,60, 3, 20                      ; eflags
    @DisplayEBP_flag              60,64, _EFLAGS_NT,  1, 22, "nt"
    @DisplayEBP_flag              60,64, _EFLAGS_PF,  1, 23, "pf"
    @DisplayEBP_flag              60,64, _EFLAGS_DF,  1, 24, "df"
    @DisplayEBP_flag              60,64, _EFLAGS_OF,  5, 22, "of"
    @DisplayEBP_flag              60,64, _EFLAGS_SF,  5, 23, "sf"
    @DisplayEBP_flag              60,64, _EFLAGS_ZF,  5, 24, "zf"
    @DisplayEBP_flag              60,64,_EFLAGS_ACF,  9, 22, "acf"
    @DisplayEBP_flag              60,64, _EFLAGS_IF, 10, 23, "if"
    @DisplayEBP_flag              60,64, _EFLAGS_CF, 10, 24, "cf"
    @DisplayEBP_relative _32,     48,48, 5,26                       ; <error code>
    @ObjectPostDisplay   _32,      5, 25, "data"
    @ObjectPostDisplay   _32,      5, 26, "imm"
    @End

ALIGN
DEBI_p_mouse_objects:
    @Left_single_click       1,  0,  1,  0, invDEBI_object_close
    @Right_single_click      3,  0, 12,  0, invDEBI_reg_1_right_click
    @Left_drag_start         0,  0, 14,  0, invDEBI_object_drag_start
    @Abandon_if_not          1,  1, 13, 29
    @Hover                   5,  1,  8,  1, 56, invDEBI_quick_watch_show_EBP_relative_selector                  ; cs
    @Hover                   5,  2, 12,  2, 52, invDEBI_quick_watch_show_EBP_relative_32                        ; eip
    @Hover                   5,  4, 12,  4, 44, invDEBI_quick_watch_show_EBP_relative_32                        ; eax
    @Hover                   5,  5, 12,  5, 40, invDEBI_quick_watch_show_EBP_relative_32                        ; ebx
    @Hover                   5,  6, 12,  6, 36, invDEBI_quick_watch_show_EBP_relative_32                        ; ecx
    @Hover                   5,  7, 12,  7, 32, invDEBI_quick_watch_show_EBP_relative_32                        ; edx
    @Hover                   5,  8, 12,  8, 28, invDEBI_quick_watch_show_EBP_relative_32                        ; esi
    @Hover                   5,  9, 12,  9, 24, invDEBI_quick_watch_show_EBP_relative_32                        ; edi
    @Hover                   5, 11,  8, 11, 20, invDEBI_quick_watch_show_EBP_relative_selector                  ; ds
    @Hover                   5, 12,  8, 12, 16, invDEBI_quick_watch_show_EBP_relative_selector                  ; es
    @Hover                   5, 13,  8, 13, 12, invDEBI_quick_watch_show_EBP_relative_selector                  ; fs
    @Hover                   5, 14,  8, 14,  8, invDEBI_quick_watch_show_EBP_relative_selector                  ; gs
    @Hover                   5, 15,  8, 15,  4, invDEBI_quick_watch_show_EBP_relative_selector                  ; ss
    @Hover                   5, 16, 12, 16, -4, invDEBI_quick_watch_show_EBP_relative_32                        ; esp
    @Hover                   5, 17, 12, 17,  0, invDEBI_quick_watch_show_EBP_relative_32                        ; ebp
    @Hover                   3, 20, 10, 20, 60, invDEBI_quick_watch_show_EBP_relative_32                        ; eflags
    @Hover                   1, 21,  3, 22, 60, invDEBI_quick_watch_show_EBP_relative_eflags, _EFLAGS_NT
    @Hover                   1, 22,  3, 23, 60, invDEBI_quick_watch_show_EBP_relative_eflags, _EFLAGS_PF
    @Hover                   1, 23,  3, 24, 60, invDEBI_quick_watch_show_EBP_relative_eflags, _EFLAGS_DF
    @Hover                   5, 21,  7, 22, 60, invDEBI_quick_watch_show_EBP_relative_eflags, _EFLAGS_OF
    @Hover                   5, 22,  7, 23, 60, invDEBI_quick_watch_show_EBP_relative_eflags, _EFLAGS_SF
    @Hover                   5, 23,  7, 24, 60, invDEBI_quick_watch_show_EBP_relative_eflags, _EFLAGS_ZF
    @Hover                   9, 21, 12, 22, 60, invDEBI_quick_watch_show_EBP_relative_eflags, _EFLAGS_ACF
    @Hover                  10, 22, 12, 23, 60, invDEBI_quick_watch_show_EBP_relative_eflags, _EFLAGS_IF
    @Hover                  10, 23, 12, 24, 60, invDEBI_quick_watch_show_EBP_relative_eflags, _EFLAGS_CF
    @End



                                ;          11111
                                ;012345678901234
DEBI_q_window               db  "ֹֽ FPU.1 …ֽֽ»",0
                            db  "תתתתתתתתתתתתתת÷",0                                                         ; st0
                            db  "תתתתתתתתתתתתתת÷",0                                                         ; st1
                            db  "תתתתתתתתתתתתתת÷",0                                                         ; st2
                            db  "תתתתתתתתתתתתתת÷",0                                                         ; st3
                            db  "תתתתתתתתתתתתתת÷",0                                                         ; st4
                            db  "תתתתתתתתתתתתתת÷",0                                                         ; st5
                            db  "תתתתתתתתתתתתתת÷",0                                                         ; st6
                            db  "תתתתתתתתתתתתתת÷",0                                                         ; st7
                            db  255

                            dw  15 * FONT_X
                            dw  9  * FONT_Y - 1
DEBI_q_screen_objects:
    @DrawWindow             DEBI_q_window
    @ObjectMemSize          108
    @DisplayEBP_relative    _ADJ_FLOAT14,   7, 062h,  0, 1                                                  ; st7
    @DisplayEBP_relative    _ADJ_FLOAT14,   6, 058h,  0, 2                                                  ; st6
    @DisplayEBP_relative    _ADJ_FLOAT14,   5, 04eh,  0, 3                                                  ; st5
    @DisplayEBP_relative    _ADJ_FLOAT14,   4, 044h,  0, 4                                                  ; st4
    @DisplayEBP_relative    _ADJ_FLOAT14,   3, 03ah,  0, 5                                                  ; st3
    @DisplayEBP_relative    _ADJ_FLOAT14,   2, 030h,  0, 6                                                  ; st2
    @DisplayEBP_relative    _ADJ_FLOAT14,   1, 026h,  0, 7                                                  ; st1
    @DisplayEBP_relative    _ADJ_FLOAT14,   0, 01ch,  0, 8                                                  ; st0
    @End

ALIGN
DEBI_q_mouse_objects:
    @Left_single_click       1,  0,  1,  0, invDEBI_object_close
    @Right_single_click      3,  0, 11,  0, invDEBI_fpu_1_right_click
    @Left_drag_start         0,  0, 14,  0, invDEBI_object_drag_start
    @Left_drag_start         0,  1, 14,  8, invDEBI_stx_drag_start
    @Left_drag_stop          0,  1, 14,  8, invDEBI_stx_drag_stop
    @Right_single_click      0,  1, 13,  8, invDEBI_fpu_menu
    @Abandon_if_not          0,  1, 13,  8
    @Hover                   0,  1, 13,  1, (-200 + 98), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   0,  2, 13,  2, (-200 + 88), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   0,  3, 13,  3, (-200 + 78), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   0,  4, 13,  4, (-200 + 68), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   0,  5, 13,  5, (-200 + 58), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   0,  6, 13,  6, (-200 + 48), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   0,  7, 13,  7, (-200 + 38), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   0,  8, 13,  8, (-200 + 28), invDEBI_quick_watch_show_EBP_relative_80
    @End




                                ;          11111111112222222222
                                ;012345678901234567890123456789
DEBI_r_window               db  "ֹֽ FPU.2 …ֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽ»",0
                            db  "st7³תתתתתתתתתתתתתתתתתתתת³פtag ץ÷",0                                        ; st7
                            db  "st6³תתתתתתתתתתתתתתתתתתתת³תתתת÷",0                                          ; st6
                            db  "st5³תתתתתתתתתתתתתתתתתתתת³פctrlץ÷",0                                        ; st5
                            db  "st4³תתתתתתתתתתתתתתתתתתתת³תתתת÷",0                                          ; st4
                            db  "st3³תתתתתתתתתתתתתתתתתתתת³פstatץ÷",0                                        ; st3
                            db  "st2³תתתתתתתתתתתתתתתתתתתת³תתתת÷",0                                          ; st2
                            db  "st1³תתתתתתתתתתתתתתתתתתתת³פ op ץ÷",0                                        ; st1
                            db  "st0³תתתתתתתתתתתתתתתתתתתת³תתתת÷",0                                          ; st0
                            db  255

                            dw  30 * FONT_X
                            dw  9  * FONT_Y - 1
DEBI_r_screen_objects:
    @DrawWindow             DEBI_r_window
    @ObjectMemSize          108
    @DisplayEBP_relative    _16,            (-200 + 008h), 008h, 25, 2                                      ; lower 16-bits of tw
    @DisplayEBP_relative    _16,            (-200 + 000h), 000h, 25, 4                                      ; lower 16-bits of cw
    @DisplayEBP_relative    _16,            (-200 + 004h), 004h, 25, 6                                      ; lower 16-bits of sw
    @DisplayEBP_relative    _FPU_OPCODE,    (-200 + 012h), 004h, 25, 8                                      ; opcode
    @DisplayEBP_relative    _ADJ_FLOAT20,               7, 062h,  4, 1                                      ; st7
    @DisplayEBP_relative    _ADJ_FLOAT20,               6, 058h,  4, 2                                      ; st6
    @DisplayEBP_relative    _ADJ_FLOAT20,               5, 04eh,  4, 3                                      ; st5
    @DisplayEBP_relative    _ADJ_FLOAT20,               4, 044h,  4, 4                                      ; st4
    @DisplayEBP_relative    _ADJ_FLOAT20,               3, 03ah,  4, 5                                      ; st3
    @DisplayEBP_relative    _ADJ_FLOAT20,               2, 030h,  4, 6                                      ; st2
    @DisplayEBP_relative    _ADJ_FLOAT20,               1, 026h,  4, 7                                      ; st1
    @DisplayEBP_relative    _ADJ_FLOAT20,               0, 01ch,  4, 8                                      ; st0
    @End

ALIGN
DEBI_r_mouse_objects:
    @Left_single_click       1,  0,  1,  0, invDEBI_object_close
    @Right_single_click      3,  0, 11,  0, invDEBI_fpu_2_right_click
    @Left_drag_start         0,  0, 29,  0, invDEBI_object_drag_start
    @Left_drag_start         4,  1, 23,  8, invDEBI_stx_drag_start
    @Left_drag_stop          4,  1, 23,  8, invDEBI_stx_drag_stop
    @Right_single_click      4,  1, 23,  8, invDEBI_fpu_menu
    @Abandon_if_not          0,  1, 28,  8
    @Hover                   4,  1, 23,  1, (-200 + 98), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   4,  2, 23,  2, (-200 + 88), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   4,  3, 23,  3, (-200 + 78), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   4,  4, 23,  4, (-200 + 68), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   4,  5, 23,  5, (-200 + 58), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   4,  6, 23,  6, (-200 + 48), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   4,  7, 23,  7, (-200 + 38), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                   4,  8, 23,  8, (-200 + 28), invDEBI_quick_watch_show_EBP_relative_80
    @Hover                  25,  2, 28,  2, (-200 + 08), invDEBI_quick_watch_show_fpu_tw
    @Hover                  25,  4, 28,  4, (-200 + 00), invDEBI_quick_watch_show_fpu_cw
    @Hover                  25,  6, 28,  6, (-200 + 04), invDEBI_quick_watch_show_fpu_sw
    @Hover                  25,  8, 28,  8, (-200 + 18), invDEBI_quick_watch_show_fpu_opcode
    @End



DEBI_mmx_menu:
    @MenuItem               "emms"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_emms
    @MenuItem               "emms/0"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_emms_zero
    @MenuItem               "pnot"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_pnot
    @MenuBar
    @MenuItem               "pror mmx,32"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_pror_mmx_32
    @MenuItem               "pror mmx,16"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_pror_mmx_16
    @MenuItem               "pror mmx,8"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_pror_mmx_8
    @MenuItem               "pror mmx,1"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_pror_mmx_1
    @MenuItem               "pshr mmx,1"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_pshr_mmx_1
    @MenuBar
    @MenuItem               "prol mmx,16"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_prol_mmx_16
    @MenuItem               "prol mmx,8"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_prol_mmx_8
    @MenuItem               "prol mmx,1"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_prol_mmx_1
    @MenuItem               "pshl mmx,1"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_pshl_mmx_1
    @MenuBar
    @MenuItem               "movq mmx,0000.0000.0000.0000"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_movq_0000_0000_0000_0000
    @MenuItem               "movq mmx,ffff.ffff.ffff.ffff"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_movq_ffff_ffff_ffff_ffff
    @MenuItem               "movq mmx,0000.ffff.ffff.ffff"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_movq_0000_ffff_ffff_ffff
    @MenuItem               "movq mmx,0000.0000.ffff.ffff"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_movq_0000_0000_ffff_ffff
    @MenuItem               "movq mmx,0000.0000.0000.ffff"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_movq_0000_0000_0000_ffff
    @MenuItem               "movq mmx,0000.0000.0000.0fff"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_movq_0000_0000_0000_0fff
    @MenuItem               "movq mmx,0000.0000.0000.00ff"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_movq_0000_0000_0000_00ff
    @MenuItem               "movq mmx,0000.0000.0000.000f"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_movq_0000_0000_0000_000f
    @MenuBar
    @MenuItem               "* L-pand, R-por, B-pandn"
    @MenuItem               "pand/or/andn mmx,ffff.תתתת.תתתת.תתתת"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_pand_ffff_0000_0000_0000
    @MenuItemEvent              _RIGHT_SINGLE_CLICK, invDEBI_mmx_por_ffff_0000_0000_0000
    @MenuItemEvent              _BOTH_SINGLE_CLICK, invDEBI_mmx_pandn_ffff_0000_0000_0000
    @MenuItem               "pand/or/andn mmx,תתתת.ffff.תתתת.תתתת"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_pand_0000_ffff_0000_0000
    @MenuItemEvent              _RIGHT_SINGLE_CLICK, invDEBI_mmx_por_0000_ffff_0000_0000
    @MenuItemEvent              _BOTH_SINGLE_CLICK, invDEBI_mmx_pandn_0000_ffff_0000_0000
    @MenuItem               "pand/or/andn mmx,תתתת.תתתת.ffff.תתתת"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_pand_0000_0000_ffff_0000
    @MenuItemEvent              _RIGHT_SINGLE_CLICK, invDEBI_mmx_por_0000_0000_ffff_0000
    @MenuItemEvent              _BOTH_SINGLE_CLICK, invDEBI_mmx_pandn_0000_0000_ffff_0000
    @MenuItem               "pand/or/andn mmx,תתתת.תתתת.תתתת.ffff"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_pand_0000_0000_0000_ffff
    @MenuItemEvent              _RIGHT_SINGLE_CLICK, invDEBI_mmx_por_0000_0000_0000_ffff
    @MenuItemEvent              _BOTH_SINGLE_CLICK, invDEBI_mmx_pandn_0000_0000_0000_ffff
    @MenuItem               "pand/or/andn mmx,תתתת.תתתת.תתתת.תfff"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_pand_0000_0000_0000_0fff
    @MenuItemEvent              _RIGHT_SINGLE_CLICK, invDEBI_mmx_por_0000_0000_0000_0fff
    @MenuItemEvent              _BOTH_SINGLE_CLICK, invDEBI_mmx_pandn_0000_0000_0000_0fff
    @MenuItem               "pand/or/andn mmx,תתתת.תתתת.תתתת.תתff"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_pand_0000_0000_0000_00ff
    @MenuItemEvent              _RIGHT_SINGLE_CLICK, invDEBI_mmx_por_0000_0000_0000_00ff
    @MenuItemEvent              _BOTH_SINGLE_CLICK, invDEBI_mmx_pandn_0000_0000_0000_00ff
    @MenuItem               "pand/or/andn mmx,תתתת.תתתת.תתתת.תתתf"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_pand_0000_0000_0000_000f
    @MenuItemEvent              _RIGHT_SINGLE_CLICK, invDEBI_mmx_por_0000_0000_0000_000f
    @MenuItemEvent              _BOTH_SINGLE_CLICK, invDEBI_mmx_pandn_0000_0000_0000_000f
    @MenuItem               "pand/or/andn mmx,ffff.ffff.תתתת.תתתת"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_pand_ffff_ffff_0000_0000
    @MenuItemEvent              _RIGHT_SINGLE_CLICK, invDEBI_mmx_por_ffff_ffff_0000_0000
    @MenuItemEvent              _BOTH_SINGLE_CLICK, invDEBI_mmx_pandn_ffff_ffff_0000_0000
    @MenuItem               "pand/or/andn mmx,תתתת.תתתת.ffff.ffff"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_pand_0000_0000_ffff_ffff
    @MenuItemEvent              _RIGHT_SINGLE_CLICK, invDEBI_mmx_por_0000_0000_ffff_ffff
    @MenuItemEvent              _BOTH_SINGLE_CLICK, invDEBI_mmx_pandn_0000_0000_ffff_ffff
    @MenuItem               "pand/or/andn mmx,ffff.תתתת.ffff.תתתת"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_pand_ffff_0000_ffff_0000
    @MenuItemEvent              _RIGHT_SINGLE_CLICK, invDEBI_mmx_por_ffff_0000_ffff_0000
    @MenuItemEvent              _BOTH_SINGLE_CLICK, invDEBI_mmx_pandn_ffff_0000_ffff_0000
    @MenuItem               "pand/or/andn mmx,תתתת.ffff.תתתת.ffff"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_mmx_pand_0000_ffff_0000_ffff
    @MenuItemEvent              _RIGHT_SINGLE_CLICK, invDEBI_mmx_por_0000_ffff_0000_ffff
    @MenuItemEvent              _BOTH_SINGLE_CLICK, invDEBI_mmx_pandn_0000_ffff_0000_ffff
    @End

                                ;          11111111112222222222
                                ;012345678901234567890123456789
DEBI_s_window               db  "ֹֽ MMX …ֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽ»",0
                            db  "   mm0 תתתת.תתתת.תתתת.תתתת   ÷",0
                            db  "   mm1 תתתת.תתתת.תתתת.תתתת   ÷",0
                            db  "   mm2 תתתת.תתתת.תתתת.תתתת   ÷",0
                            db  "   mm3 תתתת.תתתת.תתתת.תתתת   ÷",0
                            db  "   mm4 תתתת.תתתת.תתתת.תתתת   ÷",0
                            db  "   mm5 תתתת.תתתת.תתתת.תתתת   ÷",0
                            db  "   mm6 תתתת.תתתת.תתתת.תתתת   ÷",0
                            db  "   mm7 תתתת.תתתת.תתתת.תתתת   ÷",0
                            db  255

                            dw  30 * FONT_X
                            dw  9  * FONT_Y - 1
DEBI_s_screen_objects:
    @DrawWindow             DEBI_s_window
    @ObjectMemSize          108
    @DisplayEBP_relative    _16, (-200 + 28), 28,  22, 1                                                ; mm0
    @DisplayEBP_relative    _16, (-200 + 30), 30,  17, 1
    @DisplayEBP_relative    _16, (-200 + 32), 32,  12, 1
    @DisplayEBP_relative    _16, (-200 + 34), 34,  7,  1

    @DisplayEBP_relative    _16, (-200 + 38), 38,  22, 2                                                ; mm1
    @DisplayEBP_relative    _16, (-200 + 40), 40,  17, 2
    @DisplayEBP_relative    _16, (-200 + 42), 42,  12, 2
    @DisplayEBP_relative    _16, (-200 + 44), 44,  7,  2

    @DisplayEBP_relative    _16, (-200 + 48), 48,  22, 3                                                ; mm2
    @DisplayEBP_relative    _16, (-200 + 50), 50,  17, 3
    @DisplayEBP_relative    _16, (-200 + 52), 52,  12, 3
    @DisplayEBP_relative    _16, (-200 + 54), 54,  7,  3

    @DisplayEBP_relative    _16, (-200 + 58), 58,  22, 4                                                ; mm3
    @DisplayEBP_relative    _16, (-200 + 60), 60,  17, 4
    @DisplayEBP_relative    _16, (-200 + 62), 62,  12, 4
    @DisplayEBP_relative    _16, (-200 + 64), 64,  7,  4

    @DisplayEBP_relative    _16, (-200 + 68), 68,  22, 5                                                ; mm4
    @DisplayEBP_relative    _16, (-200 + 70), 70,  17, 5
    @DisplayEBP_relative    _16, (-200 + 72), 72,  12, 5
    @DisplayEBP_relative    _16, (-200 + 74), 74,  7,  5

    @DisplayEBP_relative    _16, (-200 + 78), 78,  22, 6                                                ; mm5
    @DisplayEBP_relative    _16, (-200 + 80), 80,  17, 6
    @DisplayEBP_relative    _16, (-200 + 82), 82,  12, 6
    @DisplayEBP_relative    _16, (-200 + 84), 84,  7,  6

    @DisplayEBP_relative    _16, (-200 + 88), 88,  22, 7                                                ; mm6
    @DisplayEBP_relative    _16, (-200 + 90), 90,  17, 7
    @DisplayEBP_relative    _16, (-200 + 92), 92,  12, 7
    @DisplayEBP_relative    _16, (-200 + 94), 94,  7,  7

    @DisplayEBP_relative    _16, (-200 + 98), 98,  22, 8                                                ; mm7
    @DisplayEBP_relative    _16, (-200 +100),100,  17, 8
    @DisplayEBP_relative    _16, (-200 +102),102,  12, 8
    @DisplayEBP_relative    _16, (-200 +104),104,  7,  8

    @End

ALIGN
DEBI_s_mouse_objects:
    @Left_single_click       1,  0,  1,  0, invDEBI_object_close
    @Right_single_click      3,  0,  9,  0, invDEBI_mmx_right_click
    @Left_drag_start         0,  0, 29,  0, invDEBI_object_drag_start
    @Left_drag_start         7,  1, 25,  8, invDEBI_mmx_drag_start
    @Left_drag_stop          7,  1, 25,  8, invDEBI_mmx_drag_stop
    @Right_single_click      7,  1, 25,  8, invDEBI_mmx_menu
    @Abandon_if_not          7,  1, 25,  8
    @Hover                   7,  1, 25,  1, (-200 + 98), invDEBI_quick_watch_show_EBP_relative_64
    @Hover                   7,  2, 25,  2, (-200 + 88), invDEBI_quick_watch_show_EBP_relative_64
    @Hover                   7,  3, 25,  3, (-200 + 78), invDEBI_quick_watch_show_EBP_relative_64
    @Hover                   7,  4, 25,  4, (-200 + 68), invDEBI_quick_watch_show_EBP_relative_64
    @Hover                   7,  5, 25,  5, (-200 + 58), invDEBI_quick_watch_show_EBP_relative_64
    @Hover                   7,  6, 25,  6, (-200 + 48), invDEBI_quick_watch_show_EBP_relative_64
    @Hover                   7,  7, 25,  7, (-200 + 38), invDEBI_quick_watch_show_EBP_relative_64
    @Hover                   7,  8, 25,  8, (-200 + 28), invDEBI_quick_watch_show_EBP_relative_64
    @End


DEBI_cfsca_menu:
    @MenuItem               "ִִ Change to ִִ"
    @MenuItem               "CFSCA.1"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_change_window_cfsca_1
    @MenuItem               "CFSCA.2"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_change_window_cfsca_2
    @MenuItem               "CFSCA.3"
    @MenuItemEvent              _LEFT_SINGLE_CLICK, invDEBI_change_window_cfsca_3
    @End

                                ;   00000000-112233445566.. mov     dx,fs:[esi+ebx+00eeddcc]
                                ;          11111111112222222222333333333344444444445555555555
                                ;012345678901234567890123456789012345678901234567890123456789
DEBI_t_window               db  "ֹֽ cfsca.1 …ֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽ»",0
                            db  "ּּּּ                                                       ÷",0
                            db  254,11

DEBI_t_keyboard_objects:
    @FunctionHandlesObject  invDEBI_CFSCA_kbd_handler
    @End

                            dw  60 * FONT_X
                            dw  13 * FONT_Y - 1
DEBI_t_screen_objects:
    @DrawWindow             DEBI_t_window
    @ObjectMemSize          4
    @FunctionHandlesObject  invDEBI_cfsca_1_window
    @End

ALIGN
DEBI_t_mouse_objects:
    @Left_single_click       1,  0,  1,  0, invDEBI_object_close
    @Right_single_click      3,  0, 13,  0, invDEBI_cfsca_1_right_click
    @Left_drag_start         0,  0, 59,  0, invDEBI_object_drag_start
    @End

                                ;
DEBI_z_window               db  "                              ",0
                            db  254,3

DEBI_z_keyboard_objects:
    @End

                            dw  30 * FONT_X
                            dw  3  * FONT_Y - 1
DEBI_z_screen_objects:
    @DrawWindow             DEBI_z_window
    @FunctionHandlesObject  invDEBI_logo_window
    @End

DEBI_z_mouse_objects:
    @End


;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
exp_screen_object           db  _NO                                 ; +00 Alterable?
                            db  _YES                                ; +01 Active?
                            dw  0                                   ; +02 +--Nuserved
                            dd  0                                   ; +04 +_ST_OBJECT_UL_HORIZONTAL (assigned internally)
                            dd  0                                   ; +08 +_ST_OBJECT_UL_VERTICAL (assigned internally)
                            dd  0ffffffffh                          ; +12 +_ST_MEMVAR_OFFSET
                            dd  offset exp_screen_keyboard_objects  ; +16 +_ST_OBJECT_KBD_OFFSET
                            dd  0ffffffffh                          ; +20 +_ST_OBJECT_MEMORY_OFFSET
                            dd  offset exp_screen_mouse_objects     ; +24 +_ST_OBJECT_MOUSE_OFFSET
                            dd  offset exp_screen_screen_objects    ; +28 +_ST_OBJECT_SCREEN_OFFSET

; The following list is used to copy memory from a window's options to local memory variables for editing
DEBI_exp_memvar_list        dd  offset text_22                      ; Offset of the editable variable
                            dd  sizeof text_22 - 1                  ; Length
                            dd  offset disp_22
                            dd  sizeof disp_22 - 1
                            dd  offset live
                            dd  1
                            dd  offset indirect
                            dd  1
                            dd  offset show_addresses
                            dd  1
                            dd  offset ascii_char
                            dd  1
                            dd  offset _byte
                            dd  1
                            dd  offset _word
                            dd  1
                            dd  offset _dword
                            dd  1
                            dd  offset _qword
                            dd  1
                            dd  offset float32
                            dd  1
                            dd  offset float64
                            dd  1
                            dd  offset float80
                            dd  1
                            dd  offset hexadecimal
                            dd  1
                            dd  offset decimal
                            dd  1
                            dd  offset octal
                            dd  1
                            dd  offset binary
                            dd  1
                            dd  -1                                  ; List terminator (appears where the offset to

                                ;          1111111111222222222233333333334
                                ;01234567890123456789012345678901234567890
exp_screen_window           db  "Úִִִ¿פ Address Expression to Display ץÚִִִ¿",0   ; 0
                            db  "´פ                                       ץ³",0   ; 1
                            db  "´פ      Address: ץ                      פ ץ³",0   ; 2
                            db  "´פ Displacement: ץ                      פ ץ³",0   ; 3
                            db  "´פ               ("
live                        db  " ) Live?               ץ³",0   ; 4
                            db  "´פ               ("
indirect                    db  " ) Indirect?           ץ³",0   ; 5
                            db  "´פ               ("
show_addresses              db  " ) Show addresses?     ץ³",0   ; 6
                            db  "´פ                                       ץ³",0   ; 7
                            db  "´פ Window display:                       ץ³",0   ; 8
                            db  "´פ   ("
ascii_char                  db  " ) ASCII char                      ץ³",0   ; 9
                            db  "´פ   ("
_byte                       db  " ) Byte*                           ץ³",0   ; 10
                            db  "´פ   ("
_word                       db  " ) Word*                           ץ³",0   ; 11
                            db  "´פ   ("
_dword                      db  " ) Dword*                          ץ³",0   ; 12
                            db  "´פ   ("
_qword                      db  " ) Qword*                          ץ³",0   ; 13
                            db  "´פ   ("
float32                     db  " ) Float32                         ץ³",0   ; 14
                            db  "´פ   ("
float64                     db  " ) Float64                         ץ³",0   ; 15
                            db  "´פ   ("
float80                     db  " ) Float80                         ץ³",0   ; 16
                            db  "´פ                                       ץ³",0   ; 17
                            db  "´פ * Window type:  ("
hexadecimal                 db  " ) Hexadecimal       ץ³",0   ; 18
                            db  "´פ                 ("
decimal                     db  " ) Decimal           ץ³",0   ; 19
                            db  "´פ                 ("
octal                       db  " ) Octal             ץ³",0   ; 20
                            db  "´פ                 ("
binary                      db  " ) Binary            ץ³",0   ; 21
                            db  "´פֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳץ³",0   ; 22
                            db  "´פ                                       ץ³",0   ; 23
                            db  "´פ          ˆ OK      ˆ CANCEL         ץ³",0   ; 24
                            db  "´פ                                       ץ³",0   ; 25
                            db  "ְֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳÙ",0   ; 26
                            db  255
_EXP_SCREEN_WIDTH           EQU 40
_EXP_SCREEN_HEIGHT          EQU 27

text_22                     db  22 dup(32),0                        ; Default to an empty expression
disp_22                     db  22 dup(32),0                         ; Default to an empty expression

                            dw  40 * FONT_X
                            dw  27 * FONT_Y - 1
exp_screen_screen_objects:
    @AlwaysDrawWindow       exp_screen_window
    @End

exp_screen_keyboard_objects:
    @Start
exp_screen_keyboard_top_object:
text_22_object:
    @DEBI_textbox           16,  2, 22, text_22
    @DEBI_function          38,  2,  null_function, invDEBI_clear_text_22, null_function, null_function
disp_22_object:
    @DEBI_textbox           16,  3, 22, disp_22
    @DEBI_function          38,  3,  null_function, invDEBI_clear_disp_22,  null_function, null_function
    @DEBI_checkbox          16,  4,  1, live, 1
    @DEBI_checkbox          16,  5,  1, indirect, 1
    @DEBI_checkbox          16,  6,  1, show_addresses, 1
    @DEBI_checkbox           4,  9,  1, ascii_char, 1
    @DEBI_checkbox           4, 10,  1, _byte, 1
    @DEBI_checkbox           4, 11,  1, _word, 1
    @DEBI_checkbox           4, 12,  1, _dword, 1
    @DEBI_checkbox           4, 13,  1, _qword, 1
    @DEBI_checkbox           4, 14,  1, float32, 1
    @DEBI_checkbox           4, 15,  1, float64, 1
    @DEBI_checkbox           4, 16,  1, float80, 1
    @DEBI_checkbox          18, 18,  1, hexadecimal, 1
    @DEBI_checkbox          18, 19,  1, decimal, 1
    @DEBI_checkbox          18, 20,  1, octal, 1
    @DEBI_checkbox          18, 21,  1, binary, 1

    @DEBI_button            11, 24,  1, invDEBI_exp_screen_ok, 2
    @DEBI_button            22, 24,  1, invDEBI_kbd_input_cancel, 2
    @End

exp_screen_mouse_objects:
    @Any_click              16, 2, 37, 2, invDEBI_object_setFocus, text_22_object
    @Any_click              16, 3, 37, 3, invDEBI_object_setFocus, disp_22_object
    @Left_single_click      38, 2, 38, 2, invDEBI_input_clear_var_click, text_22, 22
    @Left_single_click      38, 3, 38, 3, invDEBI_input_clear_var_click, disp_22, 22
    @Left_single_click      16, 4, 24, 4, invDEBI_checkbox_mouse_handler, live
    @Left_single_click      16, 5, 28, 5, invDEBI_checkbox_mouse_handler, indirect
    @Left_single_click      16, 6, 34, 6, invDEBI_checkbox_mouse_handler, show_addresses
    @Left_single_click       4, 9, 17, 9, invDEBI_checkbox_mouse_handler, ascii_char
    @Left_single_click       4,10, 12,10, invDEBI_checkbox_mouse_handler, _byte
    @Left_single_click       4,11, 12,11, invDEBI_checkbox_mouse_handler, _word
    @Left_single_click       4,12, 13,12, invDEBI_checkbox_mouse_handler, _dword
    @Left_single_click       4,13, 13,13, invDEBI_checkbox_mouse_handler, _qword

    @Left_single_click       4,14, 14,14, invDEBI_checkbox_mouse_handler, float32
    @Left_single_click       4,15, 14,15, invDEBI_checkbox_mouse_handler, float64
    @Left_single_click       4,16, 14,16, invDEBI_checkbox_mouse_handler, float80

    @Left_single_click      18,18, 32,18, invDEBI_checkbox_mouse_handler, hexadecimal
    @Left_single_click      18,19, 28,19, invDEBI_checkbox_mouse_handler, decimal
    @Left_single_click      18,20, 26,20, invDEBI_checkbox_mouse_handler, octal
    @Left_single_click      18,21, 27,21, invDEBI_checkbox_mouse_handler, binary

    @Left_single_click      11,24, 16,24, invDEBI_exp_screen_ok
    @Left_single_click      22,24, 31,24, invDEBI_kbd_input_cancel
    @End
