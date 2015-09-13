; debi_mac.asp
;
; Low-Level Debi Debugger defined macros
;
; This file consists of these groupings:
;   a)  common macros
;   b)  screen object macros
;   c)  mouse object macros
;




;; Macros common to all items
@Start      MACRO
    db  _START
  ; Total = 1
ENDM

@End    MACRO
    db  _END
  ; Total = 1
ENDM




;;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
;;
;; Screen Object Macros
;;
;;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

; * Note:  The constants are defined in debi_eq.asp
@DrawWindow     MACRO   name:req
; Draws the window for whatever item is specified
    db  _DRAW_WINDOW
    dd  offset name
  ; Total = 5
ENDM

@AlwaysDrawWindow     MACRO   name:req
; Always draws the window for whatever item is specified
    db  _DRAW_WINDOW_ALWAYS
    dd  offset name
  ; Total = 5
ENDM

@DrawDebiLogo_at_pixel      MACRO   x:req, y:req
; Indicates how big this item's block of memory is in the _sDEBI_objects memory area
    db  _DRAW_DEBI_LOGO
    dd  x
    dd  y
  ; Total = 9
ENDM

@ObjectMemSize  MACRO   size:req
; Indicates how big this item's block of memory is in the _sDEBI_objects memory area
    db  _OBJECT_MEM_SIZE
    db  size
  ; Total = 2
ENDM

;@ObjectMemDefault   MACRO   type:req, parm1:REQ, parm2
;; Indicates a default condition
;    db  _OBJECT_MEM_DEFAULT
;    db  type
;    dd  parm1
;    IFNB <parm2>
;        dd  parm2
;    ELSE
;        dd  0ffffffffh
;    ENDIF
;  ; Total = 10
;ENDM

@LoadTemp   MACRO   type:REQ, loffset:REQ
; Loads a temporary value from this item's portion of _sDEBI_objects memory
;
;       TYPE - indicates what type of temporary variable is being loaded
;    LOFFSET - offset in local memory where the pointer is taken from (usually 0 indicating the first item in temp space)
;
    db  _LOAD_TEMP
    db  type
    dd  loffset
  ; Total = 6
ENDM

@DisplayTemp_relative     MACRO   type:REQ, tempoffset:REQ, loffset:REQ, x:REQ, y:REQ
; Used to display some data from a temporary value.  Prior to use an @LoadTemp must've been issued to setup the far pointer to
; access the memory.
;
;       TYPE - indicates what type of variable is being displayed
; TEMPOFFSET - offset relative to the @LoadTemp far ptr
;    LOFFSET - offset in local memory where the comparison is made (to highlight if it has changed)
;          X - X coordinate (in characters) relative to upper-left corner of window
;          Y - Y coordinate (in characters) relative to upper-left corner of window
;
    db  _DISPLAY
    db  _TEMP_RELATIVE
    db  type
    dw  tempoffset
    db  loffset
    dd  x * FONT_X
    dd  y * FONT_Y
    dw  0               ; Nuserved
  ; Total = 16
ENDM

@DisplayEBP_relative    MACRO   type:REQ, ebpoffset:REQ, loffset:REQ, x:REQ, y:REQ
; Used to dipslay a dword value.  Note that the type argument specifies what kind of EBP relative item it is.
;
;      TYPE - indicates what type of variable is being displayed
; EBPOFFSET - offset relative to the current EBP (Refer to DEBI_debug in debi.asm for information on stack arrangement)
;   LOFFSET - offset in local memory where the comparison is made (to highlight if it has changed)
;         X - X coordinate (in characters) relative to upper-left corner of window
;         Y - Y coordinate (in characters) relative to upper-left corner of window
;
    db  _DISPLAY            ; +0
    db  _EBP_RELATIVE       ; +1
    db  type                ; +2
    dw  ebpoffset           ; +3
    db  loffset             ; +5
    dd  x * FONT_X          ; +6
    dd  y * FONT_Y          ; +10
    dw  0                   ; +14, Nuserved
  ; Total = 16
ENDM

@DisplayEBP_through_EBP_relative    MACRO   type:REQ, ebpoffset:REQ, loffset:REQ, x:REQ, y:REQ
; Used to dipslay a dword value.  Note that the type argument specifies what kind of EBP relative item it is.
;
;      TYPE - indicates what type of variable is being displayed
; EBPOFFSET - offset relative to the EBP derived from the stack (Refer to DEBI_debug() in debi.asm for info on stack arrangement)
;   LOFFSET - offset in local memory where the comparison is made (to highlight if it has changed)
;         X - X coordinate (in characters) relative to upper-left corner of window
;         Y - Y coordinate (in characters) relative to upper-left corner of window
;
    db  _DISPLAY
    db  _EBP_THROUGH_EBP_RELATIVE
    db  type
    dw  ebpoffset
    db  loffset
    dd  x * FONT_X
    dd  y * FONT_Y
    dw  0               ; Nuserved
  ; Total = 16
ENDM

@DisplayESP_through_EBP_relative    MACRO   type:REQ, ebpoffset:REQ, loffset:REQ, x:REQ, y:REQ
; Used to dipslay a dword value.  Note that the type argument specifies what kind of EBP relative item it is.
;
;      TYPE - indicates what type of variable is being displayed
; EBPOFFSET - offset relative to the EBP derived from the stack (Refer to DEBI_debug() in debi.asm for info on stack arrangement)
;   LOFFSET - offset in local memory where the comparison is made (to highlight if it has changed)
;         X - X coordinate (in characters) relative to upper-left corner of window
;         Y - Y coordinate (in characters) relative to upper-left corner of window
;
    db  _DISPLAY
    db  _ESP_THROUGH_EBP_RELATIVE
    db  type
    dw  ebpoffset
    db  loffset
    dd  x * FONT_X
    dd  y * FONT_Y
    dw  0               ; Nuserved
  ; Total = 16
ENDM

@DisplayEBP_flag    MACRO   ebpoffset:REQ, loffset:REQ, use_bit:REQ, x:REQ, y:REQ, string:REQ
; Used to display a flag.  Note that the EBP reference is an offset on the stack, the use_bit represents the bit pattern for the flag
;
;      TYPE - indicates what type of variable is being displayed
; EBPOFFSET - offset relative to the current EBP (Refer to DEBI_debug in debi.asm for information on stack arrangement)
;   LOFFSET - offset in local memory where the comparison is made (to highlight if it has changed)
;   USE_BIT - Indicates which bit in the DWORD quantity is to be examined
;         X - X coordinate (in characters) relative to upper-left corner of window
;         Y - Y coordinate (in characters) relative to upper-left corner of window
;    STRING - The string to display, note the last character is used to inidcate whether the flag is up  or down 
;
    db  _DISPLAY
    db  _EBP_RELATIVE_EFLAG
    dw  ebpoffset
    db  loffset
    dd  1 SHL use_bit           ; Get the bit pattern to extract this one bit
    dd  x * FONT_X
    dd  y * FONT_Y
    db  @SizeStr(string) - 2    ; The -2 is for the quotes, @SizeStr("test") returns 6
    db  string
    db  0                       ; Null terminate the string (for display purposes)
  ; Total = <varies per item>
ENDM

@ObjectPostDisplay      MACRO   type:REQ, x:REQ, y:REQ, string:REQ
; Used to display an object after all of the objects have been displayed.  This is done because this object references something
; that is calculated in another window.  The data item is identified by name (string) and may or may not be displayed once the
; entire processing has been completed.
;
;      TYPE - indicates what type of variable is being displayed
;         X - X coordinate (in characters) relative to upper-left corner of window
;         Y - Y coordinate (in characters) relative to upper-left corner of window
;    STRING - The string to look for.  Other windows will issue @ObjectPostObject that will be searched
;
    db  _POST_DISPLAY
    db  type
    dd  x * FONT_X
    dd  y * FONT_Y
    db  @SizeStr(string) - 2    ; The -2 is for the quotes, @SizeStr("test") returns 6
    db  string
  ; Total = <varies per item>
ENDM

@FunctionHandlesObject      MACRO   func:REQ
    db  _FUNCTION
    dd  offset func
  ; Total = 5
ENDM




;;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
;;
;; Mouse Object Macros
;;
;;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
@Immediate  MACRO   type:REQ, x1:REQ, y1:REQ, x2:REQ, y2:REQ, func:REQ, datum
; Used when any click is recognized on these coordinates
;
;       X1 - X coordinate (in characters relative to upper-left corner of window) of the upper-left object
;       Y1 - Y coordinate (in characters relative to upper-left corner of window) of the upper-left object
;       X2 - X coordinate (in characters relative to upper-left corner of window) of the lower-right object
;       Y2 - Y coordinate (in characters relative to upper-left corner of window) of the lower-right object
;     FUNC - Function to call when this event is recognized
;
    db  _IMMEDIATE                  ; +0
    dd  x1 * FONT_X                 ; +1
    dd  y1 * FONT_Y                 ; +5
    dd  (x2 * FONT_X) + FONT_X - 1  ; +9
    dd  (y2 * FONT_Y) + FONT_Y - 1  ; +13
    dd  func                        ; +17
    dw  0ffffh                      ; +21
    IFNB <datum>
        dw  datum                   ; +23
        db  2 dup(0ffh)             ; +25
    ELSE
        db  4 dup(0ffh)             ; +23
    ENDIF
    db  type                        ; +27
  ; Total = 28
ENDM

@Any_click      MACRO   x1:REQ, y1:REQ, x2:REQ, y2:REQ, func:REQ, data1, data2, data3
; Used when any click is recognized on these coordinates
;
;       X1 - X coordinate (in characters relative to upper-left corner of window) of the upper-left object
;       Y1 - Y coordinate (in characters relative to upper-left corner of window) of the upper-left object
;       X2 - X coordinate (in characters relative to upper-left corner of window) of the lower-right object
;       Y2 - Y coordinate (in characters relative to upper-left corner of window) of the lower-right object
;     FUNC - Function to call when this event is recognized
;
    db  _ANY_CLICK                  ; +0
    dd  x1 * FONT_X                 ; +1
    dd  y1 * FONT_Y                 ; +5
    dd  (x2 * FONT_X) + FONT_X - 1  ; +9
    dd  (y2 * FONT_Y) + FONT_Y - 1  ; +13
    dd  func                        ; +17
    IFNB <data1>
        dd  data1                   ; +21
    ELSE
        dd  0ffffffffh
    ENDIF
    IFNB <data2>
        dw  data2                   ; +25
    ELSE
        dw  0ffffh
    ENDIF
    IFNB <data3>
        db  data3                   ; +27
    ELSE
        db  0ffh
    ENDIF
  ; Total = 28
ENDM

@Left_single_click  MACRO   x1:REQ, y1:REQ, x2:REQ, y2:REQ, func:REQ, data1, data2, data3
; Used when a left single-click is recognized on these coordinates
    db  _LEFT_SINGLE_CLICK          ; +0
    dd  x1 * FONT_X                 ; +1
    dd  y1 * FONT_Y                 ; +5
    dd  (x2 * FONT_X) + FONT_X - 1  ; +9
    dd  (y2 * FONT_Y) + FONT_Y - 1  ; +13
    dd  func                        ; +17
    IFNB <data1>
        dd  data1                   ; +21
    ELSE
        dd  0ffffffffh
    ENDIF
    IFNB <data2>
        dw  data2                   ; +25
    ELSE
        dw  0ffffh
    ENDIF
    IFNB <data3>
        db  data3                   ; +27
    ELSE
        db  0ffh
    ENDIF
  ; Total = 28
ENDM

@Left_double_click  MACRO   x1:REQ, y1:REQ, x2:REQ, y2:REQ, func:REQ, data1, data2, data3
; Used when a left double-click is recognized on these coordinates
    db  _LEFT_DOUBLE_CLICK          ; +0
    dd  x1 * FONT_X                 ; +1
    dd  y1 * FONT_Y                 ; +5
    dd  (x2 * FONT_X) + FONT_X - 1  ; +9
    dd  (y2 * FONT_Y) + FONT_Y - 1  ; +13
    dd  func                        ; +17
    IFNB <data1>
        dd  data1                   ; +21
    ELSE
        dd  0ffffffffh
    ENDIF
    IFNB <data2>
        dw  data2                   ; +25
    ELSE
        dw  0ffffh
    ENDIF
    IFNB <data3>
        db  data3                   ; +27
    ELSE
        db  0ffh
    ENDIF
  ; Total = 28
ENDM

@Right_single_click  MACRO   x1:REQ, y1:REQ, x2:REQ, y2:REQ, func:REQ, data1, data2, data3
; Used when a right single-click is recognized on these coordinates
    db  _RIGHT_SINGLE_CLICK         ; +0
    dd  x1 * FONT_X                 ; +1
    dd  y1 * FONT_Y                 ; +5
    dd  (x2 * FONT_X) + FONT_X - 1  ; +9
    dd  (y2 * FONT_Y) + FONT_Y - 1  ; +13
    dd  func                        ; +17
    IFNB <data1>
        dd  data1                   ; +21
    ELSE
        dd  0ffffffffh
    ENDIF
    IFNB <data2>
        dw  data2                   ; +25
    ELSE
        dw  0ffffh
    ENDIF
    IFNB <data3>
        db  data3                   ; +27
    ELSE
        db  0ffh
    ENDIF
  ; Total = 28
ENDM

@Right_double_click  MACRO   x1:REQ, y1:REQ, x2:REQ, y2:REQ, func:REQ, data1, data2, data3
; Used when a right double-click is recognized on these coordinates
    db  _RIGHT_DOUBLE_CLICK         ; +0
    dd  x1 * FONT_X                 ; +1
    dd  y1 * FONT_Y                 ; +5
    dd  (x2 * FONT_X) + FONT_X - 1  ; +9
    dd  (y2 * FONT_Y) + FONT_Y - 1  ; +13
    dd  func                        ; +17
    IFNB <data1>
        dd  data1                   ; +21
    ELSE
        dd  0ffffffffh
    ENDIF
    IFNB <data2>
        dw  data2                   ; +25
    ELSE
        dw  0ffffh
    ENDIF
    IFNB <data3>
        db  data3                   ; +27
    ELSE
        db  0ffh
    ENDIF
  ; Total = 28
ENDM

@Both_single_click  MACRO   x1:REQ, y1:REQ, x2:REQ, y2:REQ, func:REQ, data1, data2, data3
; Used when a both single-click is recognized on these coordinates
    db  _BOTH_SINGLE_CLICK          ; +0
    dd  x1 * FONT_X                 ; +1
    dd  y1 * FONT_Y                 ; +5
    dd  (x2 * FONT_X) + FONT_X - 1  ; +9
    dd  (y2 * FONT_Y) + FONT_Y - 1  ; +13
    dd  func                        ; +17
    IFNB <data1>
        dd  data1                   ; +21
    ELSE
        dd  0ffffffffh
    ENDIF
    IFNB <data2>
        dw  data2                   ; +25
    ELSE
        dw  0ffffh
    ENDIF
    IFNB <data3>
        db  data3                   ; +27
    ELSE
        db  0ffh
    ENDIF
  ; Total = 28
ENDM

@Both_double_click  MACRO   x1:REQ, y1:REQ, x2:REQ, y2:REQ, func:REQ, data1, data2, data3
; Used when a both double-click is recognized on these coordinates
    db  _BOTH_DOUBLE_CLICK          ; +0
    dd  x1 * FONT_X                 ; +1
    dd  y1 * FONT_Y                 ; +5
    dd  (x2 * FONT_X) + FONT_X - 1  ; +9
    dd  (y2 * FONT_Y) + FONT_Y - 1  ; +13
    dd  func                        ; +17
    IFNB <data1>
        dd  data1                   ; +21
    ELSE
        dd  0ffffffffh
    ENDIF
    IFNB <data2>
        dw  data2                   ; +25
    ELSE
        dw  0ffffh
    ENDIF
    IFNB <data3>
        db  data3                   ; +27
    ELSE
        db  0ffh
    ENDIF
  ; Total = 28
ENDM

@Left_drag_start    MACRO   x1:REQ, y1:REQ, x2:REQ, y2:REQ, func:REQ, data1, data2, data3
; Used when a left-drag is started in these coordinates
    db  _LEFT_DRAG_START            ; +0
    dd  x1 * FONT_X                 ; +1
    dd  y1 * FONT_Y                 ; +5
    dd  (x2 * FONT_X) + FONT_X - 1  ; +9
    dd  (y2 * FONT_Y) + FONT_Y - 1  ; +13
    dd  func                        ; +17
    IFNB <data1>
        dd  data1                   ; +21
    ELSE
        dd  0ffffffffh
    ENDIF
    IFNB <data2>
        dw  data2                   ; +25
    ELSE
        dw  0ffffh
    ENDIF
    IFNB <data3>
        db  data3                   ; +27
    ELSE
        db  0ffh
    ENDIF
  ; Total = 28
ENDM

@Right_drag_start    MACRO   x1:REQ, y1:REQ, x2:REQ, y2:REQ, func:REQ, data1, data2, data3
; Used when a right-drag is started in these coordinates
    db  _RIGHT_DRAG_START           ; +0
    dd  x1 * FONT_X                 ; +1
    dd  y1 * FONT_Y                 ; +5
    dd  (x2 * FONT_X) + FONT_X - 1  ; +9
    dd  (y2 * FONT_Y) + FONT_Y - 1  ; +13
    dd  func                        ; +17
    IFNB <data1>
        dd  data1                   ; +21
    ELSE
        dd  0ffffffffh
    ENDIF
    IFNB <data2>
        dw  data2                   ; +25
    ELSE
        dw  0ffffh
    ENDIF
    IFNB <data3>
        db  data3                   ; +27
    ELSE
        db  0ffh
    ENDIF
  ; Total = 28
ENDM

@Left_drag_stop     MACRO   x1:REQ, y1:REQ, x2:REQ, y2:REQ, func:REQ, data1, data2, data3
; Used when a left-drag is stopped if it started in these coordinates
    db  _LEFT_DRAG_STOP             ; +0
    dd  x1 * FONT_X                 ; +1
    dd  y1 * FONT_Y                 ; +5
    dd  (x2 * FONT_X) + FONT_X - 1  ; +9
    dd  (y2 * FONT_Y) + FONT_Y - 1  ; +13
    dd  func                        ; +17
    IFNB <data1>
        dd  data1                   ; +21
    ELSE
        dd  0ffffffffh
    ENDIF
    IFNB <data2>
        dw  data2                   ; +25
    ELSE
        dw  0ffffh
    ENDIF
    IFNB <data3>
        db  data3                   ; +27
    ELSE
        db  0ffh
    ENDIF
  ; Total = 28
ENDM

@Right_drag_stop    MACRO   x1:REQ, y1:REQ, x2:REQ, y2:REQ, func:REQ, data1, data2, data3
; Used when a right-drag is stopped if it was started in these coordinates
    db  _RIGHT_DRAG_STOP            ; +0
    dd  x1 * FONT_X                 ; +1
    dd  y1 * FONT_Y                 ; +5
    dd  (x2 * FONT_X) + FONT_X - 1  ; +9
    dd  (y2 * FONT_Y) + FONT_Y - 1  ; +13
    dd  func                        ; +17
    IFNB <data1>
        dd  data1                   ; +21
    ELSE
        dd  0ffffffffh
    ENDIF
    IFNB <data2>
        dw  data2                   ; +25
    ELSE
        dw  0ffffh
    ENDIF
    IFNB <data3>
        db  data3                   ; +27
    ELSE
        db  0ffh
    ENDIF
  ; Total = 28
ENDM

@Hover          MACRO   x1:REQ, y1:REQ, x2:REQ, y2:REQ, loffset:REQ, func:REQ, datum
; Used when the mouse is hovering over these coordinates
    db  _HOVER                      ; +0
    dd  x1 * FONT_X                 ; +1
    dd  y1 * FONT_Y                 ; +5
    dd  (x2 * FONT_X) + FONT_X - 1  ; +9
    dd  (y2 * FONT_Y) + FONT_Y - 1  ; +13
    dd  func                        ; +17
    dw  lowword(offset loffset)     ; +21
    IFNB <datum>
        dw  datum                   ; +23
        db  3 dup(0ffh)             ; +25
    ELSE
        db  5 dup(0ffh)             ; +23
    ENDIF
  ; Total = 28
ENDM

@Edit           MACRO   x1:REQ, y1:REQ, x2:REQ, y2:REQ, loffset:REQ, type:REQ, datum
; Used when a left-click is recognized on an item that can be edited
    db  _EDIT                       ; +0
    dd  x1 * FONT_X                 ; +1
    dd  y1 * FONT_Y                 ; +5
    dd  (x2 * FONT_X) + FONT_X - 1  ; +9
    dd  (y2 * FONT_Y) + FONT_Y - 1  ; +13
    dd  type                        ; +17
    dw  lowword(offset loffset)     ; +21
    IFNB <datum>
        dw  datum                   ; +23
        db  3 dup(0ffh)             ; +25
    ELSE
        db  5 dup(0ffh)             ; +23
    ENDIF
  ; Total = 28
ENDM

@Abandon_if_not     MACRO   x1:REQ, y1:REQ, x2:REQ, y2:REQ
; Used in a lengthy list.  If the coordinates are not within this range then the rest of the lengthy list is not checked
    db  _ABANDON_IF_NOT             ; +0
    dd  x1 * FONT_X                 ; +1
    dd  y1 * FONT_Y                 ; +5
    dd  (x2 * FONT_X) + FONT_X - 1  ; +9
    dd  (y2 * FONT_Y) + FONT_Y - 1  ; +13
    db  11 dup(0ffh)                ; +17
  ; Total = 28
ENDM





;;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
;;
;; Menu Item Macros
;;
;;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

@MenuItem       MACRO   text:REQ
    db  _MENU_ITEM
    db  @SizeStr(text) - 2      ; The -2 is for the quotes, @SizeStr("test") returns 6
    db  text
ENDM

@MenuItemEvent      MACRO   type:REQ, var:REQ
    db  _MENU_ITEM_EVENT
    db  type
    dd  offset var
ENDM

@MenuBar        MACRO
    db  _MENU_BAR
ENDM





;;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
;;
;; Input Item Macros
;;
;;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

; Offsets for these items are in called _DEBI_* and are in DEBI_MAC.ASP
@DEBI_textbox       MACRO   x:REQ, y:REQ, len:REQ, var:REQ
    db  _KO_TEXTBOX             ; +0
    dd  x * FONT_X              ; +1
    dd  y * FONT_Y              ; +5
    dd  len                     ; +9
    dd  offset var              ; +13
    db  7 dup(0ffh)             ; +21
  ; Total = 24
ENDM

@DEBI_checkbox      MACRO   x:REQ, y:REQ, len:REQ, var:REQ, x_offset:REQ
    db  _KO_CHECKBOX            ; +0
    dd  x * FONT_X              ; +1
    dd  y * FONT_Y              ; +5
    dd  len                     ; +9
    dd  offset var              ; +13
    db  x_offset                ; +17
    db  6 dup(0ffh)             ; +18
  ; Total = 24
ENDM

@DEBI_button        MACRO   x:REQ, y:REQ, len:REQ, func:REQ, x_offset:REQ
    db  _KO_BUTTON              ; +0
    dd  x * FONT_X              ; +1
    dd  y * FONT_Y              ; +5
    dd  len                     ; +9
    dd  func                    ; +13
    db  x_offset                ; +17
    db  6 dup(0ffh)             ; +18
  ; Total = 24
ENDM

@DEBI_function      MACRO   x:REQ, y:REQ, func_mouse:REQ, func_kbd:REQ, func_refresh:REQ, func_activate:REQ
    db  _KO_FUNCTION            ; +0
    dw  x * FONT_X              ; +1
    dw  y * FONT_Y              ; +3
    dd  offset func_mouse       ; +5,  * Note:  This function is called to process a mouse request
    dd  offset func_kbd         ; +9,  * Note:  This function is entirely custom and is called for all screen updating
    dd  offset func_refresh     ; +13, * Note:  This function is entirely custom and is called for all screen updating
    dd  offset func_activate    ; +17, * Note:  This function is entirely custom and is called for all screen updating
    db  3 dup(0ffh)             ; +21
  ; Total = 24
ENDM