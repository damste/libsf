; keyboard.asp
;
; Exodus 104-keyboard driver
;

    r_ctrl_status       db  0
    r_shift_status      db  0
    r_alt_status        db  0
    l_ctrl_status       db  0
    l_shift_status      db  0
    l_alt_status        db  0
    caps_status         db  0
    num_status          db  0
    scroll_status       db  0
    l_win_status        db  0
    r_win_status        db  0
    win_menu_status     db  0

; These keys change some internal flags when they're depressed
  depress_keys:
                        db  036h
                        dd  offset r_shift_status
                        db  05ch
                        dd  offset r_alt_status
                        db  01dh
                        dd  offset l_ctrl_status
                        db  02ah
                        dd  offset l_shift_status
                        db  038h
                        dd  offset l_alt_status
                        db  054h
                        dd  offset l_win_status
                        db  055h
                        dd  offset r_win_status
                        db  056h
                        dd  offset win_menu_status
                        db  03ah
                        dd  offset caps_status + 80000000h
                        db  045h
                        dd  offset num_status + 80000000h
                        db  046h
                        dd  offset scroll_status + 80000000h
                        dw  0ffffffffh

; These keys change some internal flags when they're released
  release_keys:
                        db  05ah
                        dd  offset r_ctrl_status
                        db  036h
                        dd  offset r_shift_status
                        db  05ch
                        dd  offset r_alt_status
                        db  01dh
                        dd  offset l_ctrl_status
                        db  02ah
                        dd  offset l_shift_status
                        db  038h
                        dd  offset l_alt_status
                        db  054h
                        dd  offset l_win_status
                        db  055h
                        dd  offset r_win_status
                        db  056h
                        dd  offset win_menu_status
                        dw  0ffffffffh

; These keys are part of extended two-byte keystroke codes
    extended_keys       db  01ch                    ; enter
                        dd  0ffffffffh
                        db  01dh                    ; right_ctrl
                        dd  offset r_ctrl_status
                        db  035h                    ; gray_slash
                        dd  0ffffffffh
                        db  038h                    ; right_alt
                        dd  offset r_alt_status
                        db  047h                    ; home
                        dd  0ffffffffh
                        db  048h                    ; up
                        dd  0ffffffffh
                        db  049h                    ; pgup
                        dd  0ffffffffh
                        db  04bh                    ; left
                        dd  0ffffffffh
                        db  04dh                    ; right
                        dd  0ffffffffh
                        db  04fh                    ; end
                        dd  0ffffffffh
                        db  050h                    ; down
                        dd  0ffffffffh
                        db  051h                    ; pgdn
                        dd  0ffffffffh
                        db  052h                    ; ins
                        dd  0ffffffffh
                        db  053h                    ; del
                        dd  0ffffffffh
                        dw  0ffffh

                        ; ASCII in SCAN order
    raw_key_set         dw  00000h      ; 00, null
                        dw  0001Bh      ; 01, Escape
                        dw  00031h      ; 02, 1
                        dw  00032h      ; 03, 2
                        dw  00033h      ; 04, 3
                        dw  00034h      ; 05, 4
                        dw  00035h      ; 06, 5
                        dw  00036h      ; 07, 6
                        dw  00037h      ; 08, 7
                        dw  00038h      ; 09, 8
                        dw  00039h      ; 0a, 9
                        dw  00030h      ; 0b, 0
                        dw  0002dh      ; 0c, -
                        dw  0003dh      ; 0d, =
                        dw  00e08h      ; 0e, bksp
                        dw  00f09h      ; 0f, tab
                        dw  00071h      ; 10, q
                        dw  00077h      ; 11, w
                        dw  00065h      ; 12, e
                        dw  00072h      ; 13, r
                        dw  00074h      ; 14, t
                        dw  00079h      ; 15, y
                        dw  00075h      ; 16, u
                        dw  00069h      ; 17, i
                        dw  0006Fh      ; 18, o
                        dw  00070h      ; 19, p
                        dw  0005bh      ; 1a, [
                        dw  0005dh      ; 1b, ]
                        dw  01c0dh      ; 1c, enter
                        dw  0f000h      ; 1d, ctrl
                        dw  00061h      ; 1e, a
                        dw  00073h      ; 1f, s
                        dw  00064h      ; 20, d
                        dw  00066h      ; 21, f
                        dw  00067h      ; 22, g
                        dw  00068h      ; 23, h
                        dw  0006ah      ; 24, j
                        dw  0006bh      ; 25, k
                        dw  0006ch      ; 26, l
                        dw  0003bh      ; 27, ;
                        dw  00027h      ; 28, '
                        dw  00060h      ; 29, `
                        dw  0f000h      ; 2a, l_shift
                        dw  0005ch      ; 2b, \
                        dw  0007ah      ; 2c, z
                        dw  00078h      ; 2d, x
                        dw  00063h      ; 2e, c
                        dw  00076h      ; 2f, v
                        dw  00062h      ; 30, b
                        dw  0006eh      ; 31, n
                        dw  0006dh      ; 32, m
                        dw  0002ch      ; 33, ,
                        dw  0002eh      ; 34, .
                        dw  0002fh      ; 35, /
                        dw  0f000h      ; 36, r_shift
                        dw  0002ah      ; 37, prtsc
                        dw  0f000h      ; 38, alt
                        dw  00020h      ; 39, spc
                        dw  0f000h      ; 3a, caps
                        dw  03b00h      ; 3b, f1
                        dw  03c00h      ; 3c, f2
                        dw  03d00h      ; 3d, f3
                        dw  03e00h      ; 3e, f4
                        dw  03f00h      ; 3f, f5
                        dw  04000h      ; 40, f6
                        dw  04100h      ; 41, f7
                        dw  04200h      ; 42, f8
                        dw  04300h      ; 43, f9
                        dw  04400h      ; 44, f10
                        dw  0f000h      ; 45, numlck
                        dw  0f000h      ; 46, scrlock
                        dw  04700h      ; 47, home
                        dw  04800h      ; 48, up
                        dw  04900h      ; 49, pgup
                        dw  04a2dh      ; 4a, gray-
                        dw  04b00h      ; 4b, left
                        dw  04c00h      ; 4c, center
                        dw  04d00h      ; 4d, right
                        dw  04e2bh      ; 4e, gray+
                        dw  04f00h      ; 4f, end
                        dw  05000h      ; 50, down
                        dw  05100h      ; 51, pgdn
                        dw  05200h      ; 52, ins
                        dw  05300h      ; 53, del
                        dw  0f000h      ; 54, nothing
                        dw  0f000h      ; 55, nothing
                        dw  0f000h      ; 56, nothing
                        dw  08500h      ; 57, f11
                        dw  08600h      ; 58, f12
                        dw  0ffffh

                        ; ASCII in SCAN order
    caps_raw_key_set    dw  00000h      ; 00, null
                        dw  0001Bh      ; 01, Escape
                        dw  00031h      ; 02, 1
                        dw  00032h      ; 03, 2
                        dw  00033h      ; 04, 3
                        dw  00034h      ; 05, 4
                        dw  00035h      ; 06, 5
                        dw  00036h      ; 07, 6
                        dw  00037h      ; 08, 7
                        dw  00038h      ; 09, 8
                        dw  00039h      ; 0a, 9
                        dw  00030h      ; 0b, 0
                        dw  0002dh      ; 0c, -
                        dw  0003dh      ; 0d, =
                        dw  00e08h      ; 0e, bksp
                        dw  00f09h      ; 0f, tab
                        dw  00051h      ; 10, Q
                        dw  00057h      ; 11, W
                        dw  00045h      ; 12, E
                        dw  00052h      ; 13, R
                        dw  00054h      ; 14, T
                        dw  00059h      ; 15, Y
                        dw  00055h      ; 16, U
                        dw  00049h      ; 17, I
                        dw  0004Fh      ; 18, O
                        dw  00050h      ; 19, P
                        dw  0005bh      ; 1a, [
                        dw  0005dh      ; 1b, ]
                        dw  01c0dh      ; 1c, enter
                        dw  0f000h      ; 1d, ctrl
                        dw  00041h      ; 1e, A
                        dw  00053h      ; 1f, S
                        dw  00044h      ; 20, D
                        dw  00046h      ; 21, F
                        dw  00047h      ; 22, G
                        dw  00048h      ; 23, H
                        dw  0004ah      ; 24, J
                        dw  0004bh      ; 25, K
                        dw  0004ch      ; 26, L
                        dw  0003bh      ; 27, ;
                        dw  00027h      ; 28, '
                        dw  00060h      ; 29, `
                        dw  0f000h      ; 2a, l_shift
                        dw  0005ch      ; 2b, \
                        dw  0005ah      ; 2c, Z
                        dw  00058h      ; 2d, X
                        dw  00043h      ; 2e, C
                        dw  00056h      ; 2f, V
                        dw  00042h      ; 30, B
                        dw  0004eh      ; 31, N
                        dw  0004dh      ; 32, M
                        dw  0002ch      ; 33, ,
                        dw  0002eh      ; 34, .
                        dw  0002fh      ; 35, /
                        dw  0f000h      ; 36, r_shift
                        dw  0002ah      ; 37, prtsc
                        dw  0f000h      ; 38, alt
                        dw  00020h      ; 39, spc
                        dw  0f000h      ; 3a, caps
                        dw  03b00h      ; 3b, f1
                        dw  03c00h      ; 3c, f2
                        dw  03d00h      ; 3d, f3
                        dw  03e00h      ; 3e, f4
                        dw  03f00h      ; 3f, f5
                        dw  04000h      ; 40, f6
                        dw  04100h      ; 41, f7
                        dw  04200h      ; 42, f8
                        dw  04300h      ; 43, f9
                        dw  04400h      ; 44, f10
                        dw  0f000h      ; 45, numlck
                        dw  0f000h      ; 46, scrlock
                        dw  04700h      ; 47, home
                        dw  04800h      ; 48, up
                        dw  04900h      ; 49, pgup
                        dw  04a2dh      ; 4a, gray-
                        dw  04b00h      ; 4b, left
                        dw  04c00h      ; 4c, center
                        dw  04d00h      ; 4d, right
                        dw  04e2bh      ; 4e, gray+
                        dw  04f00h      ; 4f, end
                        dw  05000h      ; 50, down
                        dw  05100h      ; 51, pgdn
                        dw  05200h      ; 52, ins
                        dw  05300h      ; 53, del
                        dw  00000h      ; 54, nothing
                        dw  00000h      ; 55, nothing
                        dw  00000h      ; 56, nothing
                        dw  08500h      ; 57, f11
                        dw  08600h      ; 58, f12
                        dw  0ffffh

                        ; SHIFT+Keystroke SCAN/ASCII Conversion
    shift_key_set       dw  00000h      ; 00, null
                        dw  0001Bh      ; 01, esc
                        dw  00021h      ; 02, !
                        dw  00040h      ; 03, @
                        dw  00023h      ; 04, #
                        dw  00024h      ; 05, $
                        dw  00025h      ; 06, %
                        dw  0005eh      ; 07, ^
                        dw  00026h      ; 08, &
                        dw  0002ah      ; 09, *
                        dw  00028h      ; 0a, (
                        dw  00029h      ; 0b, )
                        dw  0005fh      ; 0c, _
                        dw  0002bh      ; 0d, +
                        dw  00e08h      ; 0e, bksp
                        dw  00f09h      ; 0f, baktab
                        dw  00051h      ; 10, Q
                        dw  00057h      ; 11, W
                        dw  00045h      ; 12, E
                        dw  00052h      ; 13, R
                        dw  00054h      ; 14, T
                        dw  00059h      ; 15, Y
                        dw  00055h      ; 16, U
                        dw  00049h      ; 17, I
                        dw  0004Fh      ; 18, O
                        dw  00050h      ; 19, P
                        dw  0007bh      ; 1a, {
                        dw  0007dh      ; 1b, }
                        dw  01c0dh      ; 1c, enter
                        dw  001f0h      ; 1d, ctrl
                        dw  00041h      ; 1e, A
                        dw  00053h      ; 1f, S
                        dw  00044h      ; 20, D
                        dw  00046h      ; 21, F
                        dw  00047h      ; 22, G
                        dw  00048h      ; 23, H
                        dw  0004ah      ; 24, J
                        dw  0004bh      ; 25, K
                        dw  0004ch      ; 26, L
                        dw  0003ah      ; 27, :
                        dw  00022h      ; 28, "
                        dw  0007eh      ; 29, ~
                        dw  003f0h      ; 2a, l_shift
                        dw  0007ch      ; 2b, |
                        dw  0005ah      ; 2c, Z
                        dw  00058h      ; 2d, X
                        dw  00043h      ; 2e, C
                        dw  00056h      ; 2f, V
                        dw  00042h      ; 30, B
                        dw  0004eh      ; 31, N
                        dw  0004dh      ; 32, M
                        dw  0003ch      ; 33, <
                        dw  0003eh      ; 34, >
                        dw  0003fh      ; 35, ?
                        dw  004f0h      ; 36, r_shift
                        dw  0002ah      ; 37, prtsc
                        dw  005f0h      ; 38, alt
                        dw  00020h      ; 39, spc
                        dw  007f0h      ; 3a, caps
                        dw  05400h      ; 3b, f1
                        dw  05500h      ; 3c, f2
                        dw  05600h      ; 3d, f3
                        dw  05700h      ; 3e, f4
                        dw  05800h      ; 3f, f5
                        dw  05900h      ; 40, f6
                        dw  05a00h      ; 41, f7
                        dw  05b00h      ; 42, f8
                        dw  05c00h      ; 43, f9
                        dw  05d00h      ; 44, f10
                        dw  008f0h      ; 45, numlck
                        dw  009f0h      ; 46, scrlock
                        dw  00037h      ; 47, 7
                        dw  00038h      ; 48, 8
                        dw  00039h      ; 49, 9
                        dw  0002dh      ; 4a, -
                        dw  00034h      ; 4b, 4
                        dw  00035h      ; 4c, 5
                        dw  00036h      ; 4d, 6
                        dw  0002bh      ; 4e, +
                        dw  00031h      ; 4f, 1
                        dw  00032h      ; 50, 2
                        dw  00033h      ; 51, 3
                        dw  00030h      ; 52, 0
                        dw  0002eh      ; 53, .
                        dw  00000h      ; 54, nothing
                        dw  00000h      ; 55, nothing
                        dw  00000h      ; 56, nothing
                        dw  08700h      ; 57, f11
                        dw  08800h      ; 58, f12
                        dd  0ffffh

                        ; SHIFT+Keystroke SCAN/ASCII Conversion
    caps_shift_key_set  dw  00000h      ; 00, null
                        dw  0001Bh      ; 01, esc
                        dw  00021h      ; 02, !
                        dw  00040h      ; 03, @
                        dw  00023h      ; 04, #
                        dw  00024h      ; 05, $
                        dw  00025h      ; 06, %
                        dw  0005eh      ; 07, ^
                        dw  00026h      ; 08, &
                        dw  0002ah      ; 09, *
                        dw  00028h      ; 0a, (
                        dw  00029h      ; 0b, )
                        dw  0005fh      ; 0c, _
                        dw  0002bh      ; 0d, +
                        dw  00e08h      ; 0e, bksp
                        dw  00f09h      ; 0f, baktab
                        dw  00071h      ; 10, q
                        dw  00077h      ; 11, w
                        dw  00065h      ; 12, e
                        dw  00072h      ; 13, r
                        dw  00074h      ; 14, t
                        dw  00079h      ; 15, y
                        dw  00075h      ; 16, u
                        dw  00069h      ; 17, i
                        dw  0006Fh      ; 18, o
                        dw  00070h      ; 19, p
                        dw  0007bh      ; 1a, {
                        dw  0007dh      ; 1b, }
                        dw  01c0dh      ; 1c, enter
                        dw  001f0h      ; 1d, ctrl
                        dw  00061h      ; 1e, a
                        dw  00073h      ; 1f, s
                        dw  00064h      ; 20, d
                        dw  00066h      ; 21, f
                        dw  00067h      ; 22, g
                        dw  00068h      ; 23, h
                        dw  0006ah      ; 24, j
                        dw  0006bh      ; 25, k
                        dw  0006ch      ; 26, l
                        dw  0003ah      ; 27, :
                        dw  00022h      ; 28, "
                        dw  0007eh      ; 29, ~
                        dw  003f0h      ; 2a, l_shift
                        dw  0007ch      ; 2b, |
                        dw  0007ah      ; 2c, z
                        dw  00078h      ; 2d, x
                        dw  00063h      ; 2e, c
                        dw  00076h      ; 2f, v
                        dw  00062h      ; 30, b
                        dw  0006eh      ; 31, n
                        dw  0006dh      ; 32, m
                        dw  0003ch      ; 33, <
                        dw  0003eh      ; 34, >
                        dw  0003fh      ; 35, ?
                        dw  004f0h      ; 36, r_shift
                        dw  0002ah      ; 37, prtsc
                        dw  005f0h      ; 38, alt
                        dw  00020h      ; 39, spc
                        dw  007f0h      ; 3a, caps
                        dw  05400h      ; 3b, f1
                        dw  05500h      ; 3c, f2
                        dw  05600h      ; 3d, f3
                        dw  05700h      ; 3e, f4
                        dw  05800h      ; 3f, f5
                        dw  05900h      ; 40, f6
                        dw  05a00h      ; 41, f7
                        dw  05b00h      ; 42, f8
                        dw  05c00h      ; 43, f9
                        dw  05d00h      ; 44, f10
                        dw  008f0h      ; 45, numlck
                        dw  009f0h      ; 46, scrlock
                        dw  00037h      ; 47, 7
                        dw  00038h      ; 48, 8
                        dw  00039h      ; 49, 9
                        dw  0002dh      ; 4a, -
                        dw  00034h      ; 4b, 4
                        dw  00035h      ; 4c, 5
                        dw  00036h      ; 4d, 6
                        dw  0002bh      ; 4e, +
                        dw  00031h      ; 4f, 1
                        dw  00032h      ; 50, 2
                        dw  00033h      ; 51, 3
                        dw  00030h      ; 52, 0
                        dw  0002eh      ; 53, .
                        dw  00000h      ; 54, nothing
                        dw  00000h      ; 55, nothing
                        dw  00000h      ; 56, nothing
                        dw  08700h      ; 57, f11
                        dw  08800h      ; 58, f12
                        dd  0ffffh

                        ; ALT+Keystroke SCAN/ASCII Conversion
    alt_keys            dw  00100h      ; 00, null
                        dw  07800h      ; 01, esc
                        dw  07900h      ; 02, !
                        dw  07a00h      ; 03, @
                        dw  07b00h      ; 04, #
                        dw  07c00h      ; 05, $
                        dw  07d00h      ; 06, %
                        dw  07e00h      ; 07, ^
                        dw  07f00h      ; 08, &
                        dw  08000h      ; 09, *
                        dw  08100h      ; 0a, (
                        dw  08200h      ; 0b, )
                        dw  08300h      ; 0c, _
                        dw  00e00h      ; 0d, +
                        dw  00e00h      ; 0e, bksp
                        dw  0a500h      ; 0f, baktab
                        dw  01100h      ; 10, q
                        dw  01200h      ; 11, w
                        dw  01300h      ; 12, e
                        dw  01400h      ; 13, r
                        dw  01500h      ; 14, t
                        dw  01600h      ; 15, y
                        dw  01700h      ; 16, u
                        dw  01800h      ; 17, i
                        dw  01900h      ; 18, o
                        dw  01a00h      ; 19, p
                        dw  01b00h      ; 1a, {
                        dw  01c00h      ; 1b, }
                        dw  01c00h      ; 1c, enter
                        dw  0f000h      ; 1d, ctrl
                        dw  01e00h      ; 1e, a
                        dw  01f00h      ; 1f, s
                        dw  02000h      ; 20, d
                        dw  02100h      ; 21, f
                        dw  02200h      ; 22, g
                        dw  02300h      ; 23, h
                        dw  02400h      ; 24, j
                        dw  02500h      ; 25, k
                        dw  02600h      ; 26, l
                        dw  02700h      ; 27, :
                        dw  02800h      ; 28, "
                        dw  02900h      ; 29, ~
                        dw  0f000h      ; 2a, l_shift
                        dw  00000h      ; 2b, |
                        dw  02c00h      ; 2c, z
                        dw  02d00h      ; 2d, x
                        dw  02e00h      ; 2e, c
                        dw  02f00h      ; 2f, v
                        dw  03000h      ; 30, b
                        dw  03100h      ; 31, n
                        dw  03200h      ; 32, m
                        dw  03300h      ; 33, <
                        dw  03400h      ; 34, >
                        dw  03400h      ; 35, ?
                        dw  0f000h      ; 36, r_shift
                        dw  00000h      ; 37, prtsc
                        dw  0f000h      ; 38, alt
                        dw  02000h      ; 39, spc
                        dw  0f000h      ; 3a, caps
                        dw  06800h      ; 3b, f1
                        dw  06900h      ; 3c, f2
                        dw  06a00h      ; 3d, f3
                        dw  06b00h      ; 3e, f4
                        dw  06c00h      ; 3f, f5
                        dw  06d00h      ; 40, f6
                        dw  06e00h      ; 41, f7
                        dw  06f00h      ; 42, f8
                        dw  07000h      ; 43, f9
                        dw  07100h      ; 44, f10
                        dw  0f000h      ; 45, numlck
                        dw  0f000h      ; 46, scrlock
                        dw  09700h      ; 47, home
                        dw  09800h      ; 48, up
                        dw  09900h      ; 49, pgup
                        dw  00af0h      ; 4a, gray-
                        dw  09b00h      ; 4b, left
                        dw  00000h      ; 4c, center
                        dw  09d00h      ; 4d, right
                        dw  00bf0h      ; 4e, gray+
                        dw  09f00h      ; 4f, end
                        dw  0a000h      ; 50, down
                        dw  0a100h      ; 51, pgdn
                        dw  0a200h      ; 52, ins
                        dw  0a300h      ; 53, del
                        dw  00000h      ; 54, nothing
                        dw  00000h      ; 55, nothing
                        dw  00000h      ; 56, nothing
                        dw  08b00h      ; 57, f11
                        dw  08c00h      ; 58, f12
                        dw  0ffffh

                        ; CTRL+Keystroke SCAN/ASCII Conversion
    ctrl_keys           dw  00000h      ; 00, null
                        dw  0001Bh      ; 01, esc
                        dw  00000h      ; 02, 1
                        dw  00300h      ; 03, 2
                        dw  00000h      ; 04, 3
                        dw  00000h      ; 05, 4
                        dw  00000h      ; 06, 5
                        dw  0001eh      ; 07, 6
                        dw  00000h      ; 08, 7
                        dw  00000h      ; 09, 8
                        dw  00000h      ; 0a, 9
                        dw  00000h      ; 0b, 0
                        dw  0001fh      ; 0c, -
                        dw  00000h      ; 0d, =
                        dw  0007fh      ; 0e, bksp
                        dw  09400h      ; 0f, tab
                        dw  00011h      ; 10, q
                        dw  00017h      ; 11, w
                        dw  00005h      ; 12, e
                        dw  00012h      ; 13, r
                        dw  00014h      ; 14, t
                        dw  00019h      ; 15, y
                        dw  00015h      ; 16, u
                        dw  00009h      ; 17, i
                        dw  0000fh      ; 18, o
                        dw  00010h      ; 19, p
                        dw  0001bh      ; 1a, [
                        dw  0001ch      ; 1b, ]
                        dw  0000ah      ; 1c, enter
                        dw  001f0h      ; 1d, ctrl
                        dw  00001h      ; 1e, a
                        dw  00013h      ; 1f, s
                        dw  00004h      ; 20, d
                        dw  00006h      ; 21, f
                        dw  00007h      ; 22, g
                        dw  00008h      ; 23, h
                        dw  0000ah      ; 24, j
                        dw  0000bh      ; 25, k
                        dw  0000ch      ; 26, l
                        dw  00000h      ; 27, ;
                        dw  00000h      ; 28, '
                        dw  00000h      ; 29, `
                        dw  003f0h      ; 2a, l_shift
                        dw  0001ch      ; 2b, \
                        dw  0001ah      ; 2c, z
                        dw  00018h      ; 2d, x
                        dw  00003h      ; 2e, c
                        dw  00016h      ; 2f, v
                        dw  00002h      ; 30, b
                        dw  0000eh      ; 31, n
                        dw  0000dh      ; 32, m
                        dw  00000h      ; 33, ,
                        dw  00000h      ; 34, .
                        dw  00000h      ; 35, /
                        dw  004f0h      ; 36, r_shift
                        dw  00010h      ; 37, prtsc
                        dw  005f0h      ; 38, alt
                        dw  00020h      ; 39, spc
                        dw  007f0h      ; 3a, caps
                        dw  05e00h      ; 3b, f1
                        dw  05f00h      ; 3c, f2
                        dw  06000h      ; 3d, f3
                        dw  06100h      ; 3e, f4
                        dw  06200h      ; 3f, f5
                        dw  06300h      ; 40, f6
                        dw  06400h      ; 41, f7
                        dw  06500h      ; 42, f8
                        dw  06600h      ; 43, f9
                        dw  06700h      ; 44, f10
                        dw  008f0h      ; 45, numlck
                        dw  009f0h      ; 46, scrlock
                        dw  07700h      ; 47, home
                        dw  08d00h      ; 48, up
                        dw  08400h      ; 49, pgup
                        dw  00af0h      ; 4a, gray-
                        dw  07300h      ; 4b, left
                        dw  00000h      ; 4c, center
                        dw  07400h      ; 4d, right
                        dw  00bf0h      ; 4e, gray+
                        dw  07500h      ; 4f, end
                        dw  09100h      ; 50, down
                        dw  07600h      ; 51, pgdn
                        dw  09200h      ; 52, ins
                        dw  09300h      ; 53, del
                        dw  00000h      ; 54, nothing
                        dw  00000h      ; 55, nothing
                        dw  00000h      ; 56, nothing
                        dw  08900h      ; 57, f11
                        dw  08a00h      ; 58, f12
                        dw  0ffffh