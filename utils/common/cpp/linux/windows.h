//////////
//
// /libsf/utils/common/cpp/linux/windows.h
//
//////
//    _     _ _     _____ _____
//   | |   (_) |__ / ____|  ___|
//   | |   | | '_ \\___ \|  __|
//   | |___| | |_) |___) | |
//   |_____|_|_.__/_____/|_|
//
//   Liberty Software Foundation
// and the Village Freedom Project
//   __     _______     ____
//   \ \   / /  ___| __|  _ \
//    \ \ / /| |_ | '__| |_) |
//     \ V / |  _|| |  |  __/
//      \_/  |_|  |_|  |_|
//
//////
// Version 0.55
// Copyright (c) 2015 by Rick C. Hodgin
//////
// Last update:
//	Jan.17.2014
//////
// Change log:
//	Jan.17.2014 - Initial creation
//////
//
// This document is released as Liberty Software under a Repeat License, as governed
// by the Public Benefit License v1.0 or later (PBL).
//
// The PBL is a public domain license with a caveat:  self accountability unto God.
// You are free to use, copy, modify and share this software for any purpose, however,
// it is the desire of those working on this project that the software remain open.
// It is our request that you maintain it that way.  This is not a legal request unto
// our court systems, but rather a personal matter between you and God.  Our talents
// were received from God, and given to you through this forum.  And it is our wish
// that those talents reach out to as many as possible in a form allowing them to wield
// this content for their own betterment, as you are now considering doing.  And whereas
// we could've forced the issue through something like a copyleft-protected release, the
// truth is we are all giving an account of our lives unto God continually by the daily
// choices we make.  And here again is another case where you get to demonstrate your
// character unto God, and unto your fellow man.
//
// Jesus came to this Earth to set the captives free, to save men's eternal souls from
// the punishment demanded by our sin.  Each one of us is given the opportunity to
// receive Him in this world and be saved.  Whether we choose to receive Him, and follow
// Him, and purpose our lives on the goals He has for each of us (all of which are
// beneficial for all involved), is one way we reveal our character continually.  God
// sees straight through to the heart, bypassing all of the words, all of the facades.
// He is our Creator, and He knows who we are truly.
//
// Jesus is called "Christ" because He saves men from the eternal flames of Hell, the
// just punishment of rebellion against God (rebellion against truth) by eternal beings,
// which each of us are.
//
// Do not let His free gift escape you because of some desire to shortcut what is right
// in your life. Instead, do what is right, and do it because He is who He is, and what
// He has done to save us from such a fate.  Demonstrate to Him, to me, and to all of
// mankind, and to all of the Heavenly hosts, exactly who you are on the inside.  Receive
// Jesus Christ into your heart, learn of Him, of how He came here to guide us into that
// which is of His Kingdom and will be forever hereafter we leave this world.  Do this,
// and live.
//
// Every project released by Liberty Software Foundation will include a copy of the
// pbl.txt document, which can be found at http://www.libsf.org/licenses/.
//
// For additional information about this project, or to view the license, see:
//
//	http://www.libsf.org/
//	http://www.libsf.org/licenses/
//	http://www.visual-freepro.org/vjr/indexmain.html
//	http://www.visual-freepro.org/wiki/index.php/PBL
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//////
//  _       _         ___             _
// | |     (_)       |__ \           (_)
// | |      _  _ __     ) |__      __ _  _ __
// | |     | || '_ \   / / \ \ /\ / /| || '_ \
// | |____ | || | | | / /_  \ V  V / | || | | |
// |______||_||_| |_||____|  \_/\_/  |_||_| |_|
//     Linux to Windows -- Emulation Layer
//
//////////



#include "/libsf/utils/common/cpp/builder.h"
#include "/libsf/utils/common/cpp/datum.h"



//////////
// Constants used by windows.cpp
//////
	cu32	_CREATE_THREAD_DEFAULT_STACK_SIZE 		= (1024 * 1000);	// 1 Megabyte


// windows.h and windows.cpp will provide Linux-based simulation of Windows
// functionality for those features required by LibSF software.

#define	HDC					uptr
#define HBITMAP				uptr
#define HWND				uptr
#define HANDLE				uptr
#define HFONT				uptr
#define HRGN				uptr
#define HBRUSH				uptr
#define HINSTANCE			uptr
#define HACCEL				uptr
#define HICON				uptr
#define HCURSOR				uptr
#define HMENU				uptr
#define HGDIOBJ				uptr
#define HMODULE				uptr
#define WPARAM				uptr
#define LPARAM				uptr
#define ATOM				u16

#define BOOL				bool
#define CONST				const
#define VOID				void
#define SIZE_T				size_t

#define FALSE				false
#define TRUE				true

#define SHORT				u16
#define LONG				sptr
#define LONG_PTR			sptr*
#define ULONG_PTR			uptr*
#define _MAX_PATH			256
#define BYTE				u8
#define WORD				u16
#define LPWORD				WORD*
#define DWORD				u32
#define LPDWORD				DWORD*
#define UINT				uptr
#define UINT_PTR			uptr*
#define LPVOID				void*
#define LRESULT				sptr*
#define COLORREF			DWORD
#define LPSTR				s8*
#define IDispatch           void
union LARGE_INTEGER
{
	s64 QuadPart;
	struct {
		u32	LowPart;
		u32	HighPart;
	};
};

// TODO:  These values have not yet been populated with correct values, they're just placeholders for compilation
#define _S_IREAD            0
#define _S_IWRITE           1
#define _LK_NBLCK           2
#define _LK_UNLCK           3

#define RGB(r,g,b)			((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#define MAKEINTRESOURCE(i)	((uptr)(i))

#define __stdcall
#define WINAPI				__stdcall
#define CALLBACK			__stdcall

typedef LRESULT				(CALLBACK*	WNDPROC)				(HWND, UINT, WPARAM, LPARAM);
typedef VOID				(CALLBACK*	TIMERPROC)				(HWND, UINT, UINT_PTR, DWORD);
typedef DWORD				(__stdcall*	LPTHREAD_START_ROUTINE)	(LPVOID lpThreadParameter);


#define WINUSERAPI	/*__declspec(dllimport)*/
#define WINBASEAPI	/*__declspec(dllimport)*/
#define WINGDIAPI	/*__declspec(dllimport)*/
#define __in_opt
#define __in
#define __out_opt
#define __out
#define __inout
#define __deref
#define __drv_aliasesMem

#define IDI_JDEBI			-1
#define IDI_VJR				-2
#define IDC_VJR				-3

#define MB_OK				0x00000000L
#define MB_OKCANCEL			0x00000001L
#define MB_ABORTRETRYIGNORE 0x00000002L
#define MB_YESNOCANCEL		0x00000003L
#define MB_YESNO			0x00000004L
#define MB_RETRYCANCEL		0x00000005L
#define MB_CANCELTRYCONTINUE 0x00000006L
#define MB_ICONHAND			0x00000010L
#define MB_ICONQUESTION		0x00000020L
#define MB_ICONEXCLAMATION	0x00000030L
#define MB_ICONASTERISK		0x00000040L
#define MB_ICONWARNING		MB_ICONEXCLAMATION
#define MB_ICONERROR		MB_ICONHAND
#define MB_ICONINFORMATION	MB_ICONASTERISK
#define MB_ICONSTOP			MB_ICONHAND

#define IDC_ARROW           32512	// XC_arrow
#define IDC_IBEAM           32513	// XC_xterm
#define IDC_WAIT            32514	// XC_watch
#define IDC_CROSS           32515	// XC_cross
#define IDC_UPARROW         32516	// XC_center_ptr
#define IDC_SIZENWSE        32642	// XC_fleur
#define IDC_SIZENESW        32643	// XC_fleur
#define IDC_SIZEWE          32644	// XC_
#define IDC_SIZENS          32645	// XC_double_arrow
#define IDC_SIZEALL         32646	// XC_fleur
#define IDC_NO              32648	// XC_circle
#define IDC_HAND            32649	// XC_hand2
#define IDC_APPSTARTING     32650	// XC_left_ptr
#define IDC_HELP            32651	// XC_question_arrow
#define IDC_SIZE            IDC_SIZEALL
#define IDC_ICON            IDC_ARROW

#define IDOK				1
#define IDCANCEL			2
#define IDABORT				3
#define IDRETRY				4
#define IDIGNORE			5
#define IDYES				6
#define IDNO				7
#define IDCLOSE				8
#define IDHELP				9
#define IDTRYAGAIN			10
#define IDCONTINUE			11
#define IDTIMEOUT			32000

#define WHITE_BRUSH			0
#define LTGRAY_BRUSH		1
#define GRAY_BRUSH			2
#define DKGRAY_BRUSH		3
#define BLACK_BRUSH			4
#define NULL_BRUSH			5
#define HOLLOW_BRUSH		NULL_BRUSH
#define WHITE_PEN			6
#define BLACK_PEN			7
#define NULL_PEN			8
#define OEM_FIXED_FONT		10
#define ANSI_FIXED_FONT		11
#define ANSI_VAR_FONT		12
#define SYSTEM_FONT			13
#define DEVICE_DEFAULT_FONT 14
#define DEFAULT_PALETTE		15
#define SYSTEM_FIXED_FONT   16

// Jan.18.2015 -- For PeekMessage(), may be useful to add in the future ... but VJr doesn't use them. :-)
// #define QS_KEY			0x0001
// #define QS_MOUSEMOVE		0x0002
// #define QS_MOUSEBUTTON	0x0004
// #define QS_POSTMESSAGE	0x0008
// #define QS_TIMER			0x0010
// #define QS_PAINT			0x0020
// #define QS_SENDMESSAGE	0x0040
// #define QS_HOTKEY		0x0080
// #define QS_ALLPOSTMESSAGE 0x0100
// #define QS_RAWINPUT		0x0400
// #define QS_MOUSE			(QS_MOUSEMOVE | QS_MOUSEBUTTON)
// #define QS_INPUT			(QS_MOUSE | QS_KEY | QS_RAWINPUT)
// #define QS_ALLEVENTS		(QS_INPUT | QS_POSTMESSAGE | QS_TIMER | QS_PAINT | QS_HOTKEY)
// #define QS_ALLINPUT		(QS_INPUT | QS_POSTMESSAGE | QS_TIMER | QS_PAINT | QS_HOTKEY | QS_SENDMESSAGE)
//
#define PM_NOREMOVE			0x0000
// #define PM_REMOVE		0x0001
// #define PM_NOYIELD		0x0002
// #define PM_QS_INPUT		(QS_INPUT << 16)
// #define PM_QS_POSTMESSAGE ((QS_POSTMESSAGE | QS_HOTKEY | QS_TIMER) << 16)
// #define PM_QS_PAINT		(QS_PAINT << 16)
// #define PM_QS_SENDMESSAGE (QS_SENDMESSAGE << 16)

#define IDI_APPLICATION		32512
#define IDI_ERROR			32513
#define IDI_QUESTION		32514
#define IDI_EXCLAMATION		32515
#define IDI_ASTERISK		32516
#define IDI_WINLOGO			32517
#define IDI_SHIELD			32518
#define IDI_HAND			IDI_ERROR
#define IDI_INFORMATION		IDI_ASTERISK
#define IDI_WARNING			IDI_EXCLAMATION

#define WM_NULL				0x0000
#define WM_CREATE			0x0001
#define WM_DESTROY			0x0002
#define WM_MOVE				0x0003
#define WM_SIZE				0x0005
#define WM_ACTIVATE			0x0006
#define WM_SETFOCUS			0x0007
#define WM_KILLFOCUS		0x0008
#define WM_ENABLE			0x000A
#define WM_SETREDRAW		0x000B
#define WM_SETTEXT			0x000C
#define WM_GETTEXT			0x000D
#define WM_GETTEXTLENGTH	0x000E
#define WM_PAINT			0x000F
#define WM_CLOSE			0x0010
#define WM_QUERYENDSESSION	0x0011
#define WM_QUERYOPEN		0x0013
#define WM_ENDSESSION		0x0016
#define WM_QUIT				0x0012
#define WM_ERASEBKGND		0x0014
#define WM_SYSCOLORCHANGE	0x0015
#define WM_SHOWWINDOW		0x0018
#define WM_WININICHANGE		0x001A
#define WM_KEYFIRST			0x0100
#define WM_KEYDOWN			0x0100
#define WM_KEYUP			0x0101
#define WM_CHAR				0x0102
#define WM_DEADCHAR			0x0103
#define WM_SYSKEYDOWN		0x0104
#define WM_SYSKEYUP			0x0105
#define WM_SYSCHAR			0x0106
#define WM_SYSDEADCHAR		0x0107
#define WM_UNICHAR			0x0109
#define WM_KEYLAST			0x0109
#define UNICODE_NOCHAR		0xFFFF
#define WM_INITDIALOG		0x0110
#define WM_COMMAND			0x0111
#define WM_SYSCOMMAND		0x0112
#define WM_TIMER			0x0113
#define WM_HSCROLL			0x0114
#define WM_VSCROLL			0x0115
#define WM_INITMENU			0x0116
#define WM_WINDOWPOSCHANGING 0x0046
#define WM_WINDOWPOSCHANGED	0x0047

#define WM_MOUSEFIRST		0x0200
#define WM_MOUSEMOVE		0x0200
#define WM_LBUTTONDOWN		0x0201
#define WM_LBUTTONUP		0x0202
#define WM_LBUTTONDBLCLK	0x0203
#define WM_RBUTTONDOWN		0x0204
#define WM_RBUTTONUP		0x0205
#define WM_RBUTTONDBLCLK	0x0206
#define WM_MBUTTONDOWN		0x0207
#define WM_MBUTTONUP		0x0208
#define WM_MBUTTONDBLCLK	0x0209
#define WM_MOUSEWHEEL		0x020A
#define WM_XBUTTONDOWN		0x020B
#define WM_XBUTTONUP		0x020C
#define WM_XBUTTONDBLCLK	0x020D
#define WM_MOUSELAST		0x020E
#define WM_NEXTMENU			0x0213
#define WM_SIZING			0x0214
#define WM_CAPTURECHANGED   0x0215
#define WM_MOVING			0x0216
#define WM_MOUSEHOVER		0x02A1
#define WM_MOUSELEAVE		0x02A3
#define WHEEL_DELTA			120
#define GET_WHEEL_DELTA_WPARAM(wParam)  ((u16)HIWORD(wParam))
#define WHEEL_PAGESCROLL	(UINT_MAX)

#define MK_LBUTTON			0x0001
#define MK_RBUTTON			0x0002
#define MK_SHIFT			0x0004
#define MK_CONTROL			0x0008
#define MK_MBUTTON			0x0010
#define MK_XBUTTON1			0x0020
#define MK_XBUTTON2			0x0040

#define VK_LBUTTON			0x01
#define VK_RBUTTON			0x02
#define VK_CANCEL			0x03
#define VK_MBUTTON			0x04	/* NOT contiguous with L & RBUTTON */
#define VK_XBUTTON1			0x05	/* NOT contiguous with L & RBUTTON */
#define VK_XBUTTON2			0x06	/* NOT contiguous with L & RBUTTON */
#define VK_BACK				0x08
#define VK_TAB				0x09
#define VK_CLEAR			0x0C
#define VK_RETURN			0x0D
#define VK_SHIFT			0x10
#define VK_CONTROL			0x11
#define VK_MENU				0x12
#define VK_PAUSE			0x13
#define VK_CAPITAL			0x14
#define VK_KANA				0x15
#define VK_HANGEUL			0x15  /* old name - should be here for compatibility */
#define VK_HANGUL			0x15
#define VK_JUNJA			0x17
#define VK_FINAL			0x18
#define VK_HANJA			0x19
#define VK_KANJI			0x19
#define VK_ESCAPE			0x1B
#define VK_CONVERT			0x1C
#define VK_NONCONVERT		0x1D
#define VK_ACCEPT			0x1E
#define VK_MODECHANGE		0x1F
#define VK_SPACE			0x20
#define VK_PRIOR			0x21
#define VK_NEXT				0x22
#define VK_END				0x23
#define VK_HOME				0x24
#define VK_LEFT				0x25
#define VK_UP				0x26
#define VK_RIGHT			0x27
#define VK_DOWN				0x28
#define VK_SELECT			0x29
#define VK_PRINT			0x2A
#define VK_EXECUTE			0x2B
#define VK_SNAPSHOT			0x2C
#define VK_INSERT			0x2D
#define VK_DELETE			0x2E
#define VK_HELP				0x2F
#define VK_LWIN				0x5B
#define VK_RWIN				0x5C
#define VK_APPS				0x5D
#define VK_SLEEP			0x5F
#define VK_NUMPAD0			0x60
#define VK_NUMPAD1			0x61
#define VK_NUMPAD2			0x62
#define VK_NUMPAD3			0x63
#define VK_NUMPAD4			0x64
#define VK_NUMPAD5			0x65
#define VK_NUMPAD6			0x66
#define VK_NUMPAD7			0x67
#define VK_NUMPAD8			0x68
#define VK_NUMPAD9			0x69
#define VK_MULTIPLY			0x6A
#define VK_ADD				0x6B
#define VK_SEPARATOR		0x6C
#define VK_SUBTRACT			0x6D
#define VK_DECIMAL			0x6E
#define VK_DIVIDE			0x6F
#define VK_F1				0x70
#define VK_F2				0x71
#define VK_F3				0x72
#define VK_F4				0x73
#define VK_F5				0x74
#define VK_F6				0x75
#define VK_F7				0x76
#define VK_F8				0x77
#define VK_F9				0x78
#define VK_F10				0x79
#define VK_F11				0x7A
#define VK_F12				0x7B
#define VK_F13				0x7C
#define VK_F14				0x7D
#define VK_F15				0x7E
#define VK_F16				0x7F
#define VK_F17				0x80
#define VK_F18				0x81
#define VK_F19				0x82
#define VK_F20				0x83
#define VK_F21				0x84
#define VK_F22				0x85
#define VK_F23				0x86
#define VK_F24				0x87
#define VK_NUMLOCK			0x90
#define VK_SCROLL			0x91
#define VK_OEM_NEC_EQUAL	0x92   // '=' key on numpad
#define VK_OEM_FJ_JISHO		0x92   // 'Dictionary' key
#define VK_OEM_FJ_MASSHOU	0x93   // 'Unregister word' key
#define VK_OEM_FJ_TOUROKU	0x94   // 'Register word' key
#define VK_OEM_FJ_LOYA		0x95   // 'Left OYAYUBI' key
#define VK_OEM_FJ_ROYA		0x96   // 'Right OYAYUBI' key
#define VK_LSHIFT			0xA0
#define VK_RSHIFT			0xA1
#define VK_LCONTROL			0xA2
#define VK_RCONTROL			0xA3
#define VK_LMENU			0xA4
#define VK_RMENU			0xA5
#define VK_BROWSER_BACK		0xA6
#define VK_BROWSER_FORWARD	0xA7
#define VK_BROWSER_REFRESH	0xA8
#define VK_BROWSER_STOP		0xA9
#define VK_BROWSER_SEARCH	0xAA
#define VK_BROWSER_FAVORITES 0xAB
#define VK_BROWSER_HOME		0xAC
#define VK_VOLUME_MUTE		0xAD
#define VK_VOLUME_DOWN		0xAE
#define VK_VOLUME_UP		0xAF
#define VK_MEDIA_NEXT_TRACK	0xB0
#define VK_MEDIA_PREV_TRACK	0xB1
#define VK_MEDIA_STOP		0xB2
#define VK_MEDIA_PLAY_PAUSE	0xB3
#define VK_LAUNCH_MAIL		0xB4
#define VK_LAUNCH_MEDIA_SELECT 0xB5
#define VK_LAUNCH_APP1		0xB6
#define VK_LAUNCH_APP2		0xB7
#define VK_OEM_1			0xBA   // ';:' for US
#define VK_OEM_PLUS			0xBB   // '+' any country
#define VK_OEM_COMMA		0xBC   // ',' any country
#define VK_OEM_MINUS		0xBD   // '-' any country
#define VK_OEM_PERIOD		0xBE   // '.' any country
#define VK_OEM_2			0xBF   // '/?' for US
#define VK_OEM_3			0xC0   // '`~' for US
#define VK_OEM_4			0xDB  //  '[{' for US
#define VK_OEM_5			0xDC  //  '\|' for US
#define VK_OEM_6			0xDD  //  ']}' for US
#define VK_OEM_7			0xDE  //  ''"' for US
#define VK_OEM_8			0xDF
#define VK_OEM_AX			0xE1  //  'AX' key on Japanese AX kbd
#define VK_OEM_102			0xE2  //  "<>" or "\|" on RT 102-key kbd.
#define VK_ICO_HELP			0xE3  //  Help key on ICO
#define VK_ICO_00			0xE4  //  00 key on ICO
#define VK_PROCESSKEY		0xE5
#define VK_ICO_CLEAR		0xE6
#define VK_PACKET			0xE7
#define VK_OEM_RESET		0xE9
#define VK_OEM_JUMP			0xEA
#define VK_OEM_PA1			0xEB
#define VK_OEM_PA2			0xEC
#define VK_OEM_PA3			0xED
#define VK_OEM_WSCTRL		0xEE
#define VK_OEM_CUSEL		0xEF
#define VK_OEM_ATTN			0xF0
#define VK_OEM_FINISH		0xF1
#define VK_OEM_COPY			0xF2
#define VK_OEM_AUTO			0xF3
#define VK_OEM_ENLW			0xF4
#define VK_OEM_BACKTAB		0xF5
#define VK_ATTN				0xF6
#define VK_CRSEL			0xF7
#define VK_EXSEL			0xF8
#define VK_EREOF			0xF9
#define VK_PLAY				0xFA
#define VK_ZOOM				0xFB
#define VK_NONAME			0xFC
#define VK_PA1				0xFD
#define VK_OEM_CLEAR		0xFE

// WM_ACTIVATE sub-items
#define WA_INACTIVE			0
#define WA_ACTIVE			1
#define WA_CLICKACTIVE		2

#define CS_VREDRAW			0x0001
#define CS_HREDRAW			0x0002
#define CS_DBLCLKS			0x0008
#define CS_OWNDC			0x0020
#define CS_CLASSDC			0x0040
#define CS_PARENTDC			0x0080
#define CS_NOCLOSE			0x0200
#define CS_SAVEBITS			0x0800
#define CS_BYTEALIGNCLIENT  0x1000
#define CS_BYTEALIGNWINDOW  0x2000
#define CS_GLOBALCLASS		0x4000
#define CS_IME				0x00010000
#define CS_DROPSHADOW		0x00020000

#define IDC_ARROW			32512
#define IDC_IBEAM			32513
#define IDC_WAIT			32514
#define IDC_CROSS			32515
#define IDC_UPARROW			32516
#define IDC_SIZENWSE		32642
#define IDC_SIZENESW		32643
#define IDC_SIZEWE			32644
#define IDC_SIZENS			32645
#define IDC_SIZEALL			32646
#define IDC_NO				32648
#define IDC_HAND			32649
#define IDC_APPSTARTING		32650
#define IDC_HELP			32651
#define IDC_SIZE			IDC_SIZEALL
#define IDC_ICON			IDC_ARROW

#define RGN_AND				1
#define RGN_OR				2
#define RGN_XOR				3
#define RGN_DIFF			4
#define RGN_COPY			5
#define RGN_MIN				RGN_AND
#define RGN_MAX				RGN_COPY

#define DT_TOP				0x00000000
#define DT_LEFT				0x00000000
#define DT_CENTER			0x00000001
#define DT_RIGHT			0x00000002
#define DT_VCENTER			0x00000004
#define DT_BOTTOM			0x00000008
#define DT_WORDBREAK		0x00000010
#define DT_SINGLELINE		0x00000020
#define DT_EXPANDTABS		0x00000040
#define DT_TABSTOP			0x00000080
#define DT_NOCLIP			0x00000100
#define DT_EXTERNALLEADING	0x00000200
#define DT_CALCRECT			0x00000400
#define DT_NOPREFIX			0x00000800
#define DT_INTERNAL			0x00001000
#define DT_EDITCONTROL		0x00002000
#define DT_PATH_ELLIPSIS	0x00004000
#define DT_END_ELLIPSIS		0x00008000
#define DT_MODIFYSTRING		0x00010000
#define DT_RTLREADING		0x00020000
#define DT_WORD_ELLIPSIS	0x00040000
#define DT_NOFULLWIDTHCHARBREAK 0x00080000
#define DT_HIDEPREFIX		0x00100000
#define DT_PREFIXONLY		0x00200000

#define TRANSPARENT			1
#define OPAQUE				2

#define OUT_DEFAULT_PRECIS	0
#define OUT_STRING_PRECIS	1
#define OUT_CHARACTER_PRECIS 2
#define OUT_STROKE_PRECIS	3
#define OUT_TT_PRECIS		4
#define OUT_DEVICE_PRECIS	5
#define OUT_RASTER_PRECIS	6
#define OUT_TT_ONLY_PRECIS	7
#define OUT_OUTLINE_PRECIS	8
#define OUT_SCREEN_OUTLINE_PRECIS 9
#define OUT_PS_ONLY_PRECIS	10

#define CLIP_DEFAULT_PRECIS	0
#define CLIP_CHARACTER_PRECIS 1
#define CLIP_STROKE_PRECIS	2
#define CLIP_MASK			0xf
#define CLIP_LH_ANGLES		(1<<4)
#define CLIP_TT_ALWAYS		(2<<4)
#define CLIP_DFA_DISABLE	(4<<4)
#define CLIP_EMBEDDED		(8<<4)

#define DEFAULT_QUALITY		0
#define DRAFT_QUALITY		1
#define PROOF_QUALITY		2
#define NONANTIALIASED_QUALITY 3
#define ANTIALIASED_QUALITY	4
#define CLEARTYPE_QUALITY	5
#define CLEARTYPE_NATURAL_QUALITY 6

#define DEFAULT_PITCH		0
#define FIXED_PITCH			1
#define VARIABLE_PITCH		2
#define MONO_FONT			8

#define ANSI_CHARSET		0
#define DEFAULT_CHARSET		1
//#define SYMBOL_CHARSET	2
//#define SHIFTJIS_CHARSET	128
//#define HANGEUL_CHARSET	129
//#define HANGUL_CHARSET	129
//#define GB2312_CHARSET	134
//#define CHINESEBIG5_CHARSET 136
#define OEM_CHARSET			255
//#define JOHAB_CHARSET		130
//#define HEBREW_CHARSET	177
//#define ARABIC_CHARSET	178
//#define GREEK_CHARSET		161
//#define TURKISH_CHARSET	162
//#define VIETNAMESE_CHARSET 163
//#define THAI_CHARSET		222
//#define EASTEUROPE_CHARSET 238
//#define RUSSIAN_CHARSET	204

#define FS_LATIN1			0x00000001L
#define FS_LATIN2			0x00000002L
#define FS_CYRILLIC			0x00000004L
#define FS_GREEK			0x00000008L
#define FS_TURKISH			0x00000010L
#define FS_HEBREW			0x00000020L
#define FS_ARABIC			0x00000040L
#define FS_BALTIC			0x00000080L
#define FS_VIETNAMESE		0x00000100L
#define FS_THAI				0x00010000L
#define FS_JISJAPAN			0x00020000L
#define FS_CHINESESIMP		0x00040000L
#define FS_WANSUNG			0x00080000L
#define FS_CHINESETRAD		0x00100000L
#define FS_JOHAB			0x00200000L
#define FS_SYMBOL			0x80000000L

#define FF_DONTCARE			(0<<4)  /* Don't care or don't know. */
#define FF_ROMAN			(1<<4)  /* Variable stroke width, serifed. Times Roman, Century Schoolbook, etc. */
#define FF_SWISS			(2<<4)  /* Variable stroke width, sans-serifed. Helvetica, Swiss, etc. */
#define FF_MODERN			(3<<4)  /* Constant stroke width, serifed or sans-serifed. Pica, Elite, Courier, etc. */
#define FF_SCRIPT			(4<<4)  /* Cursive, etc. */
#define FF_DECORATIVE		(5<<4)  /* Old English, etc. */

/* Font Weights */
#define FW_DONTCARE			0
#define FW_THIN				100
#define FW_EXTRALIGHT		200
#define FW_LIGHT			300
#define FW_NORMAL			400
#define FW_MEDIUM			500
#define FW_SEMIBOLD			600
#define FW_BOLD				700
#define FW_EXTRABOLD		800
#define FW_HEAVY			900

#define FW_ULTRALIGHT		FW_EXTRALIGHT
#define FW_REGULAR			FW_NORMAL
#define FW_DEMIBOLD			FW_SEMIBOLD
#define FW_ULTRABOLD		FW_EXTRABOLD
#define FW_BLACK			FW_HEAVY

#define WS_OVERLAPPED		0x00000000L
#define WS_POPUP			0x80000000L
#define WS_CHILD			0x40000000L
#define WS_MINIMIZE			0x20000000L
#define WS_VISIBLE			0x10000000L
#define WS_DISABLED			0x08000000L
#define WS_CLIPSIBLINGS		0x04000000L
#define WS_CLIPCHILDREN		0x02000000L
#define WS_MAXIMIZE			0x01000000L
#define WS_CAPTION			0x00C00000L	/* WS_BORDER | WS_DLGFRAME  */
#define WS_BORDER			0x00800000L
#define WS_DLGFRAME			0x00400000L
#define WS_VSCROLL			0x00200000L
#define WS_HSCROLL			0x00100000L
#define WS_SYSMENU			0x00080000L
#define WS_THICKFRAME		0x00040000L
#define WS_GROUP			0x00020000L
#define WS_TABSTOP			0x00010000L

#define WS_MINIMIZEBOX		0x00020000L
#define WS_MAXIMIZEBOX		0x00010000L

#define WS_TILED			WS_OVERLAPPED
#define WS_ICONIC			WS_MINIMIZE
#define WS_SIZEBOX			WS_THICKFRAME
#define WS_TILEDWINDOW		WS_OVERLAPPEDWINDOW

#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED	| \
							WS_CAPTION		| \
							WS_SYSMENU		| \
							WS_THICKFRAME	| \
							WS_MINIMIZEBOX	| \
							WS_MAXIMIZEBOX)

#define WS_POPUPWINDOW		(WS_POPUP		| \
							WS_BORDER		| \
							WS_SYSMENU)

#define WS_CHILDWINDOW		(WS_CHILD)

#define WS_EX_DLGMODALFRAME	0x00000001L
#define WS_EX_NOPARENTNOTIFY 0x00000004L
#define WS_EX_TOPMOST		0x00000008L
#define WS_EX_ACCEPTFILES	0x00000010L
#define WS_EX_TRANSPARENT	0x00000020L
#define WS_EX_MDICHILD		0x00000040L
#define WS_EX_TOOLWINDOW	0x00000080L
#define WS_EX_WINDOWEDGE	0x00000100L
#define WS_EX_CLIENTEDGE	0x00000200L
#define WS_EX_CONTEXTHELP	0x00000400L
#define WS_EX_RIGHT			0x00001000L
#define WS_EX_LEFT			0x00000000L
#define WS_EX_RTLREADING	0x00002000L
#define WS_EX_LTRREADING	0x00000000L
#define WS_EX_LEFTSCROLLBAR	0x00004000L
#define WS_EX_RIGHTSCROLLBAR 0x00000000L
#define WS_EX_CONTROLPARENT	0x00010000L
#define WS_EX_STATICEDGE	0x00020000L
#define WS_EX_APPWINDOW		0x00040000L
#define WS_EX_OVERLAPPEDWINDOW (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE)
#define WS_EX_PALETTEWINDOW	(WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST)
#define WS_EX_LAYERED		0x00080000
#define WS_EX_NOINHERITLAYOUT 0x00100000L // Disable inheritence of mirroring by children
#define WS_EX_LAYOUTRTL		0x00400000L // Right to left mirroring
#define WS_EX_COMPOSITED	0x02000000L
#define WS_EX_NOACTIVATE	0x08000000L

#define SWP_NOSIZE			0x0001
#define SWP_NOMOVE			0x0002
#define SWP_NOZORDER		0x0004
#define SWP_NOREDRAW		0x0008
#define SWP_NOACTIVATE		0x0010
#define SWP_FRAMECHANGED	0x0020  /* The frame changed: send WM_NCCALCSIZE */
#define SWP_SHOWWINDOW		0x0040
#define SWP_HIDEWINDOW		0x0080
#define SWP_NOCOPYBITS		0x0100
#define SWP_NOOWNERZORDER   0x0200  /* Don't do owner Z ordering */
#define SWP_NOSENDCHANGING  0x0400  /* Don't send WM_WINDOWPOSCHANGING */
#define SWP_DRAWFRAME		SWP_FRAMECHANGED
#define SWP_NOREPOSITION	SWP_NOOWNERZORDER
#define SWP_DEFERERASE		0x2000
#define SWP_ASYNCWINDOWPOS  0x4000

#define HWND_TOP		((HWND)0)
#define HWND_BOTTOM		((HWND)1)
#define HWND_TOPMOST	((HWND)-1)
#define HWND_NOTOPMOST  ((HWND)-2)
#define HWND_MESSAGE	((HWND)-3)

#define SRCCOPY			(DWORD)0x00CC0020 /* dest = source				*/
#define SRCPAINT		(DWORD)0x00EE0086 /* dest = source OR dest		*/
#define SRCAND			(DWORD)0x008800C6 /* dest = source AND dest		*/
#define SRCINVERT		(DWORD)0x00660046 /* dest = source XOR dest		*/
#define SRCERASE		(DWORD)0x00440328 /* dest = source AND (NOT dest )   */
#define NOTSRCCOPY		(DWORD)0x00330008 /* dest = (NOT source)			*/
#define NOTSRCERASE		(DWORD)0x001100A6 /* dest = (NOT src) AND (NOT dest) */
#define MERGECOPY		(DWORD)0x00C000CA /* dest = (source AND pattern)	*/
#define MERGEPAINT		(DWORD)0x00BB0226 /* dest = (NOT source) OR dest	*/
#define PATCOPY			(DWORD)0x00F00021 /* dest = pattern				*/
#define PATPAINT		(DWORD)0x00FB0A09 /* dest = DPSnoo				*/
#define PATINVERT		(DWORD)0x005A0049 /* dest = pattern XOR dest		*/
#define DSTINVERT		(DWORD)0x00550009 /* dest = (NOT dest)			*/
#define BLACKNESS		(DWORD)0x00000042 /* dest = BLACK					*/
#define WHITENESS		(DWORD)0x00FF0062 /* dest = WHITE					*/

#define SW_HIDE			0
#define SW_SHOWNORMAL	1
#define SW_NORMAL		1
#define SW_SHOWMINIMIZED 2
#define SW_SHOWMAXIMIZED 3
#define SW_MAXIMIZE		3
#define SW_SHOWNOACTIVATE 4
#define SW_SHOW			5
#define SW_MINIMIZE		6
#define SW_SHOWMINNOACTIVE 7
#define SW_SHOWNA		8
#define SW_RESTORE		9
#define SW_SHOWDEFAULT	10
#define SW_FORCEMINIMIZE 11
#define SW_MAX			11

#define GWL_WNDPROC		(-4)
#define GWL_HINSTANCE	(-6)
#define GWL_HWNDPARENT	(-8)
#define GWL_STYLE		(-16)
#define GWL_EXSTYLE		(-20)
#define GWL_USERDATA	(-21)
#define GWL_ID			(-12)

#define DIB_RGB_COLORS	0 /* color table in RGBs */

#define SM_CXSCREEN		0
#define SM_CYSCREEN		1
#define SM_CXVSCROLL	2
#define SM_CYHSCROLL	3
#define SM_CYCAPTION	4
#define SM_CXBORDER		5
#define SM_CYBORDER		6
#define SM_CXDLGFRAME	7
#define SM_CYDLGFRAME	8
#define SM_CYVTHUMB		9
#define SM_CXHTHUMB		10
#define SM_CXICON		11
#define SM_CYICON		12
#define SM_CXCURSOR		13
#define SM_CYCURSOR		14
#define SM_CYMENU		15
#define SM_CXFULLSCREEN	16
#define SM_CYFULLSCREEN	17
#define SM_CYKANJIWINDOW 18
#define SM_MOUSEPRESENT	19
#define SM_CYVSCROLL	20
#define SM_CXHSCROLL	21
#define SM_DEBUG		22
#define SM_SWAPBUTTON	23
#define SM_RESERVED1	24
#define SM_RESERVED2	25
#define SM_RESERVED3	26
#define SM_RESERVED4	27
#define SM_CXMIN		28
#define SM_CYMIN		29
#define SM_CXSIZE		30
#define SM_CYSIZE		31
#define SM_CXFRAME		32
#define SM_CYFRAME		33
#define SM_CXMINTRACK	34
#define SM_CYMINTRACK	35
#define SM_CXDOUBLECLK	36
#define SM_CYDOUBLECLK	37
#define SM_CXICONSPACING 38
#define SM_CYICONSPACING 39
#define SM_MENUDROPALIGNMENT 40
#define SM_PENWINDOWS	41
#define SM_DBCSENABLED	42
#define SM_CMOUSEBUTTONS 43
#define SM_CXFIXEDFRAME	SM_CXDLGFRAME  /* ;win40 name change */
#define SM_CYFIXEDFRAME	SM_CYDLGFRAME  /* ;win40 name change */
#define SM_CXSIZEFRAME	SM_CXFRAME	/* ;win40 name change */
#define SM_CYSIZEFRAME	SM_CYFRAME	/* ;win40 name change */
#define SM_SECURE		44
#define SM_CXEDGE		45
#define SM_CYEDGE		46
#define SM_CXMINSPACING	47
#define SM_CYMINSPACING	48
#define SM_CXSMICON		49
#define SM_CYSMICON		50
#define SM_CYSMCAPTION	51
#define SM_CXSMSIZE		52
#define SM_CYSMSIZE		53
#define SM_CXMENUSIZE	54
#define SM_CYMENUSIZE	55
#define SM_ARRANGE		56
#define SM_CXMINIMIZED	57
#define SM_CYMINIMIZED	58
#define SM_CXMAXTRACK	59
#define SM_CYMAXTRACK	60
#define SM_CXMAXIMIZED	61
#define SM_CYMAXIMIZED	62
#define SM_NETWORK		63
#define SM_CLEANBOOT	67
#define SM_CXDRAG		68
#define SM_CYDRAG		69
#define SM_SHOWSOUNDS	70
#define SM_CXMENUCHECK	71   /* Use instead of GetMenuCheckMarkDimensions()! */
#define SM_CYMENUCHECK	72
#define SM_SLOWMACHINE	73
#define SM_MIDEASTENABLED 74
#define SM_MOUSEWHEELPRESENT 75
#define SM_XVIRTUALSCREEN 76
#define SM_YVIRTUALSCREEN 77
#define SM_CXVIRTUALSCREEN 78
#define SM_CYVIRTUALSCREEN 79
#define SM_CMONITORS	80
#define SM_SAMEDISPLAYFORMAT 81
#define SM_IMMENABLED	82
#define SM_CXFOCUSBORDER 83
#define SM_CYFOCUSBORDER 84
#define SM_TABLETPC		86
#define SM_MEDIACENTER	87
#define SM_STARTER		88
#define SM_SERVERR2		89
#define SM_MOUSEHORIZONTALWHEELPRESENT 91
#define SM_CXPADDEDBORDER 92
#define SM_DIGITIZER	94
#define SM_MAXIMUMTOUCHES 95
#define SM_CMETRICS		76
#define SM_REMOTESESSION 0x1000
#define SM_SHUTTINGDOWN	0x2000
#define SM_REMOTECONTROL 0x2001
#define SM_CARETBLINKINGENABLED 0x2002

#define _SH_DENYRW		0x10	// deny read/write mode
#define _SH_DENYWR		0x20	// deny write mode
#define _SH_DENYRD		0x30	// deny read mode
#define _SH_DENYNO		0x40	// deny none mode
#define _SH_SECURE		0x80	// secure mode

#define _O_RDONLY		0x0000  // open for reading only
#define _O_WRONLY		0x0001  // open for writing only
#define _O_RDWR			0x0002  // open for reading and writing
#define _O_APPEND		0x0008  // writes done at eof
#define _O_CREAT		0x0100  // create and open file
#define _O_TRUNC		0x0200  // open and truncate
#define _O_EXCL			0x0400  // open only if file doesn't already exist
#define _O_TEXT			0x4000  // file mode is text (translated)
#define _O_BINARY		0x8000  // file mode is binary (untranslated)

#define DRIVERVERSION	0		// Device driver version
#define TECHNOLOGY		2		// Device classification
#define HORZSIZE		4		// Horizontal size in millimeters
#define VERTSIZE		6		// Vertical size in millimeters
#define HORZRES			8		// Horizontal width in pixels
#define VERTRES			10		// Vertical height in pixels
#define BITSPIXEL		12		// Number of bits per pixel
#define PLANES			14		// Number of planes
#define NUMBRUSHES		16		// Number of brushes the device has
#define NUMPENS			18		// Number of pens the device has
#define NUMMARKERS		20		// Number of markers the device has
#define NUMFONTS		22		// Number of fonts the device has
#define NUMCOLORS		24		// Number of colors the device supports
#define PDEVICESIZE 	26		// Size required for device descriptor
#define CURVECAPS		28		// Curve capabilities
#define LINECAPS		30		// Line capabilities
#define POLYGONALCAPS	32		// Polygonal capabilities
#define TEXTCAPS		34		// Text capabilities
#define CLIPCAPS		36		// Clipping capabilities
#define RASTERCAPS		38		// Bitblt capabilities
#define ASPECTX			40		// Length of the X leg
#define ASPECTY			42		// Length of the Y leg
#define ASPECTXY		44		// Length of the hypotenuse
#define LOGPIXELSX		88		// Logical pixels/inch in X
#define LOGPIXELSY		90		// Logical pixels/inch in Y
#define SIZEPALETTE		104		// Number of entries in physical palette
#define NUMRESERVED		106		// Number of reserved entries in palette
#define COLORRES		108		// Actual color resolution

#define DT_RASDISPLAY	1


#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)

struct RECT
{
	s32		left;
	s32		top;
	s32		right;
	s32		bottom;

} __attribute__((packed));
#define LPRECT RECT*

typedef struct tagPAINTSTRUCT
{
	HDC		hdc;
	BOOL	fErase;
	RECT	rcPaint;
	BOOL	fRestore;
	BOOL	fIncUpdate;
	BYTE	rgbReserved[32];

} __attribute__((packed)) PAINTSTRUCT, *PPAINTSTRUCT, *NPPAINTSTRUCT, *LPPAINTSTRUCT;

struct POINT
{
	s32		x;
	s32		y;

} __attribute__((packed));
#define LPPOINT POINT*

struct POINTS
{
	s16		x;
	s16		y;

} __attribute__((packed));
//#define LPPOINT POINTS*

typedef struct tagBITMAPFILEHEADER {
	u16		bfType;
	u32		bfSize;
	u16		bfReserved1;
	u16		bfReserved2;
	u32		bfOffBits;

} __attribute__((packed)) BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
	u32		biSize;
	s32		biWidth;
	s32		biHeight;
	u16		biPlanes;
	u16		biBitCount;
	u32		biCompression;
	u32		biSizeImage;
	s32		biXPelsPerMeter;
	s32		biYPelsPerMeter;
	u32		biClrUsed;
	u32		biClrImportant;

} __attribute__((packed)) BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagBITMAPINFO
{
	BITMAPINFOHEADER	bmiHeader;
} __attribute__((packed)) BITMAPINFO;

typedef pthread_mutex_t CRITICAL_SECTION;
#define LPCRITICAL_SECTION CRITICAL_SECTION*

typedef struct _SYSTEMTIME
{
	u16		wYear;
	u16		wMonth;
	u16		wDayOfWeek;
	u16		wDay;
	u16		wHour;
	u16		wMinute;
	u16		wSecond;
	u16		wMilliseconds;

} __attribute__((packed)) SYSTEMTIME;
#define LPSYSTEMTIME SYSTEMTIME*

typedef struct _FILETIME
{
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;

} __attribute__((packed)) FILETIME;
#define LPFILETIME FILETIME*

typedef struct tagWNDCLASSEX
{
	UINT		cbSize;
	UINT		style;
	union {
		uptr	_lpfnWndProc;
		WNDPROC	lpfnWndProc;
	};
	int			cbClsExtra;
	int			cbWndExtra;
	HINSTANCE   hInstance;
	HICON		hIcon;
	HCURSOR		hCursor;
	HBRUSH		hbrBackground;
	cs8*		lpszMenuName;
	cs8*		lpszClassName;
	HICON		hIconSm;

} __attribute__((packed)) WNDCLASSEX;
#define WNDCLASSEXA WNDCLASSEX

typedef struct _SECURITY_ATTRIBUTES
{
	DWORD		nLength;
	LPVOID		lpSecurityDescriptor;
	BOOL		bInheritHandle;

} __attribute__((packed)) SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

typedef struct tagMSG
{
	HWND		hwnd;
	UINT		message;
	WPARAM		wParam;
	LPARAM		lParam;
	DWORD		time;
	POINT		pt;

} __attribute__((packed)) MSG;
#define LPMSG MSG*

struct DIR;
struct dirent;
typedef struct _WIN32_FIND_DATAA
{
	DWORD		dwFileAttributes;
	FILETIME	ftCreationTime;
	FILETIME	ftLastAccessTime;
	FILETIME	ftLastWriteTime;
	DWORD		nFileSizeHigh;
	DWORD		nFileSizeLow;
	DWORD		dwReserved0;
	DWORD		dwReserved1;
	s8			cFileName[260];
	s8			cAlternateFileName[14];

	// For Linux (opendir, readdir, closedir)
	DIR*		dp;
	dirent*		dirp;

} __attribute__((packed)) WIN32_FIND_DATA;
#define LPWIN32_FIND_DATA WIN32_FIND_DATA*

typedef struct tagTEXTMETRICA
{
	LONG		tmHeight;
	LONG		tmAscent;
	LONG		tmDescent;
	LONG		tmInternalLeading;
	LONG		tmExternalLeading;
	LONG		tmAveCharWidth;
	LONG		tmMaxCharWidth;
	LONG		tmWeight;
	LONG		tmOverhang;
	LONG		tmDigitizedAspectX;
	LONG		tmDigitizedAspectY;
	BYTE		tmFirstChar;
	BYTE		tmLastChar;
	BYTE		tmDefaultChar;
	BYTE		tmBreakChar;
	BYTE		tmItalic;
	BYTE		tmUnderlined;
	BYTE		tmStruckOut;
	BYTE		tmPitchAndFamily;
	BYTE		tmCharSet;

} __attribute__((packed)) TEXTMETRIC;
#define LPTEXTMETRIC TEXTMETRIC*

typedef struct tagCREATESTRUCT
{
	LPVOID		lpCreateParams;
	HINSTANCE	hInstance;
	HMENU		hMenu;
	HWND		hwndParent;
	int			cy;
	int			cx;
	int			y;
	int			x;
	LONG		style;
	cs8*		lpszName;
	cs8*		lpszClass;
	DWORD		dwExStyle;

} __attribute__((packed)) CREATESTRUCT;
#define LPCREATESTRUCT CREATESTRUCT*

#define _memcmp(l,r,s)		strncmp((cs8*)l, (cs8*)r, s)
#define _memicmp(l,r,s)		strncasecmp((cs8*)l, (cs8*)r, s)
#define _sopen				sopen
#define _dup				dup
#define _read				read
#define _write				write
#define _close				close
#define _lseek				lseek
#define _lseeki64			lseek64
#define _telli64			telli64

// TODO:  These values have not yet been populated with correct values, they're just placeholders for compilation
int                         _creat                  (char* tcPathname, int access);
int                         _creat                  (const char* tcPathname, int access);
s64                         _filelengthi64          (int fileno);
int                         _locking                (int fileno, int mode, int length);
int                         sopen                   (char* tcFilename, int access, int sharing, int shareAccess);
int                         GetDoubleClickTime      (void);
int                         QueryPerformanceCounter (LARGE_INTEGER* ticks);
int                         QueryPerformanceFrequency(LARGE_INTEGER* freq);

WINUSERAPI	HWND WINAPI CreateWindowEx(	__in		DWORD dwExStyle,
										__in_opt	cs8* lpClassName,
										__in_opt	cs8* lpWindowName,
										__in		DWORD dwStyle,
										__in		int X,
										__in		int Y,
										__in		int nWidth,
										__in		int nHeight,
										__in_opt	HWND hWndParent,
										__in_opt	HMENU hMenu,
										__in_opt	HINSTANCE hInstance,
										__in_opt	LPVOID lpParam);

#define CreateWindow(lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam) \
		CreateWindowEx(0L,	lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)
#define CreateWindowA(lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam) \
		CreateWindowEx(0L,	lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)

WINUSERAPI	UINT_PTR WINAPI		SetTimer				(__in_opt HWND hWnd, __in s32 nIDEvent, __in UINT uElapse, sptr lpTimerFunc);
WINUSERAPI	int		WINAPI		MessageBox				(__in_opt HWND hWnd, __in_opt cs8* lpText, __in_opt cs8* lpCaption, __in UINT uType);
#define MessageBoxA MessageBox
WINBASEAPI	HANDLE	WINAPI		CreateThread			(__in_opt LPSECURITY_ATTRIBUTES lpThreadAttributes, __in SIZE_T dwStackSize, __in LPTHREAD_START_ROUTINE lpStartAddress, __in_opt __deref __drv_aliasesMem LPVOID lpParameter, __in DWORD dwCreationFlags, __out_opt LPDWORD lpThreadId);
WINBASEAPI	VOID	WINAPI		ExitThread				(__in DWORD dwExitCode);
WINUSERAPI	BOOL	WINAPI		GetClassInfoExA			(__in_opt HINSTANCE hInstance, __in cs8* lpszClass, __out WNDCLASSEXA* lpwcx);
#define GetClassInfoEx GetClassInfoExA
WINUSERAPI	ATOM	WINAPI		RegisterClassExA		(__in CONST WNDCLASSEX* lpwcx);
#define RegisterClassEx RegisterClassExA
WINUSERAPI	BOOL	WINAPI		GetMessage				(__out LPMSG lpMsg, __in_opt HWND hWnd, __in UINT wMsgFilterMin, __in UINT wMsgFilterMax);
WINUSERAPI	BOOL	WINAPI		TranslateMessage		(__in CONST MSG *lpMsg);
WINUSERAPI	LRESULT	WINAPI		DispatchMessage			(__in CONST MSG *lpMsg);
WINUSERAPI	BOOL	WINAPI		PeekMessage				(__out MSG* lpMsg, __in_opt HWND hWnd, __in UINT wMsgFilterMin, __in UINT wMsgFilterMax, __in UINT wRemoveMsg);
LRESULT CALLBACK				DefWindowProc			(__in HWND hWnd, __in UINT Msg, __in WPARAM wParam, __in LPARAM lParam);
WINUSERAPI	BOOL	WINAPI		PostMessage				(__in_opt HWND hWnd, __in UINT Msg, __in WPARAM wParam, __in LPARAM lParam);
WINUSERAPI	HWND	WINAPI		GetDesktopWindow		(VOID);
WINUSERAPI	BOOL	WINAPI		GetClientRect			(__in HWND hWnd, __out LPRECT lpRect);
WINUSERAPI	BOOL	WINAPI		GetWindowRect			(__in HWND hWnd, __out LPRECT lpRect);
WINUSERAPI	BOOL	WINAPI		SetRect					(__out LPRECT lprc, __in int xLeft, __in int yTop, __in int xRight, __in int yBottom);
WINGDIAPI	HGDIOBJ	WINAPI		SelectObject			(__in HDC hdc, __in HGDIOBJ h);
WINGDIAPI	COLORREF WINAPI		SetTextColor			(__in HDC hdc, __in COLORREF color);
WINGDIAPI	int		WINAPI		SetBkMode				(__in HDC hdc, __in int mode);
WINUSERAPI	int		WINAPI		DrawText				(__in HDC hdc, cs8* lpchText, __in int cchText, __inout LPRECT lprc, __in UINT format);
WINBASEAPI	DWORD	WINAPI		GetTickCount			(VOID);
WINBASEAPI	VOID	WINAPI		InitializeCriticalSection(__out LPCRITICAL_SECTION lpCriticalSection);
WINBASEAPI	VOID	WINAPI		EnterCriticalSection	(__inout LPCRITICAL_SECTION lpCriticalSection);
WINBASEAPI	BOOL	WINAPI		TryEnterCriticalSection	(__inout LPCRITICAL_SECTION lpCriticalSection);
WINBASEAPI	VOID	WINAPI		LeaveCriticalSection	(__inout LPCRITICAL_SECTION lpCriticalSection);
WINBASEAPI	VOID	WINAPI		DeleteCriticalSection	(__inout LPCRITICAL_SECTION lpCriticalSection);
WINUSERAPI	VOID	WINAPI		PostQuitMessage			(__in int nExitCode);
WINUSERAPI	HCURSOR	WINAPI		LoadCursor				(__in_opt HINSTANCE hInstance, __in uptr lpCursorName);
WINBASEAPI	HMODULE	WINAPI		GetModuleHandle			(__in_opt cs8* lpModuleName);
WINUSERAPI	int		WINAPI		SetWindowRgn			(__in HWND hWnd, __in_opt HRGN hRgn, __in BOOL bRedraw);
WINUSERAPI	BOOL	WINAPI		KillTimer				(__in_opt HWND hWnd, __in sptr uIDEvent);
WINGDIAPI	BOOL	WINAPI		DeleteDC				( __in HDC hdc);
WINGDIAPI	BOOL	WINAPI		DeleteObject			( __in HGDIOBJ ho);
WINUSERAPI	BOOL	WINAPI		DestroyWindow			(__in HWND hWnd);
WINUSERAPI	BOOL	WINAPI		ShowWindow				(__in HWND hWnd, __in int nCmdShow);
WINBASEAPI	VOID	WINAPI		Sleep					(__in DWORD dwMilliseconds);
WINUSERAPI	BOOL	WINAPI		SetWindowPos			(__in HWND hWnd, __in_opt HWND hWndInsertAfter, __in int X, __in int Y, __in int cx, __in int cy, __in UINT uFlags);
WINUSERAPI	BOOL	WINAPI		GetCursorPos			(__out LPPOINT lpPoint);
WINGDIAPI	HRGN	WINAPI		CreateRectRgn			(__in int x1, __in int y1, __in int x2, __in int y2);
WINUSERAPI	int		WINAPI		GetWindowRgn			(__in HWND hWnd, __in HRGN hRgn);
WINGDIAPI	BOOL	WINAPI		PtInRegion				(__in HRGN hrgn, __in int x, __in int y);
WINUSERAPI	HDC		WINAPI		BeginPaint				(__in HWND hWnd, __out LPPAINTSTRUCT lpPaint);
WINUSERAPI	BOOL	WINAPI		EndPaint				(__in HWND hWnd, __in CONST PAINTSTRUCT *lpPaint);
WINGDIAPI	BOOL	WINAPI		BitBlt					( __in HDC hdc, __in int x, __in int y, __in int cx, __in int cy, __in_opt HDC hdcSrc, __in int x1, __in int y1, __in DWORD rop);
WINUSERAPI	HICON	WINAPI		LoadIcon				(__in_opt HINSTANCE hInstance, __in uptr lpIconName);
WINUSERAPI	BOOL	WINAPI		CopyRect				(__out RECT* lprcDst, __in CONST RECT *lprcSrc);
WINUSERAPI	BOOL	WINAPI		InflateRect				(__inout RECT* lprc, __in int dx, __in int dy);
WINUSERAPI	LONG	WINAPI		GetWindowLongA			(__in HWND hWnd, __in int nIndex);
#define GetWindowLong GetWindowLongA
WINUSERAPI	LONG	WINAPI		SetWindowLongA			(__in HWND hWnd, __in int nIndex,__in LONG dwNewLong);
#define SetWindowLong SetWindowLongA
WINUSERAPI	BOOL	WINAPI		InvalidateRect			(__in_opt HWND hWnd, __in_opt CONST RECT *lpRect, __in BOOL bErase);
WINUSERAPI	HMENU	WINAPI		GetMenu					(__in HWND hWnd);
WINUSERAPI	BOOL	WINAPI		SetMenu					(__in HWND hWnd, __in_opt HMENU hMenu);
WINGDIAPI	HRGN	WINAPI		CreateRectRgnIndirect	( __in CONST RECT *lprect);
WINUSERAPI	BOOL	WINAPI		PtInRect				(__in CONST RECT *lprc, __in POINT pt);
WINUSERAPI	SHORT	WINAPI		GetAsyncKeyState		(__in int vKey);
WINUSERAPI	SHORT	WINAPI		GetKeyState				(__in int nVirtKey);
WINUSERAPI	BOOL	WINAPI		AdjustWindowRect		(__inout LPRECT lpRect, __in DWORD dwStyle, __in BOOL bMenu);
WINUSERAPI	BOOL	WINAPI		GetKeyboardState		(BYTE lpKeyState[256]);
WINUSERAPI	int		WINAPI		ToAscii					(__in UINT uVirtKey, __in UINT uScanCode, CONST BYTE lpKeyState[256], __out LPWORD lpChar, __in UINT uFlags);
WINGDIAPI	int		WINAPI		CombineRgn				(__in_opt HRGN hrgnDst, __in_opt HRGN hrgnSrc1, __in_opt HRGN hrgnSrc2, __in int iMode);
WINGDIAPI	HBRUSH	WINAPI		CreateSolidBrush		(__in COLORREF color);
WINUSERAPI	int		WINAPI		FillRect				(__in HDC hDC, __in CONST RECT *lprc, __in HBRUSH hbr);
WINUSERAPI	int		WINAPI		FrameRect				(__in HDC hDC, __in CONST RECT *lprc,__in HBRUSH hbr);
WINBASEAPI	VOID	WINAPI		GetSystemTime			(__out LPSYSTEMTIME lpSystemTime);
WINBASEAPI	VOID	WINAPI		GetSystemTimeAsFileTime	(__out LPFILETIME lpSystemTimeAsFileTime);
WINBASEAPI	VOID	WINAPI		GetLocalTime			(__out LPSYSTEMTIME lpSystemTime);
WINUSERAPI	HWND	WINAPI		GetActiveWindow			(VOID);
WINGDIAPI	COLORREF WINAPI		SetBkColor				(__in HDC hdc, __in COLORREF color);
WINUSERAPI	HDC		WINAPI		GetDC					(__in_opt HWND hWnd);
WINGDIAPI	HDC		WINAPI		CreateCompatibleDC		( __in_opt HDC hdc);
WINGDIAPI	HBITMAP	WINAPI		CreateDIBSection		(__in_opt HDC hdc, __in CONST BITMAPINFO* lpbmi, __in UINT usage, VOID **ppvBits, __in_opt HANDLE hSection, __in DWORD offset);
s64								_atoi64					(cs8* string);
WINUSERAPI	int		WINAPI		GetSystemMetrics		(__in int nIndex);
WINUSERAPI	BOOL	WINAPI		OffsetRect				(__inout LPRECT lprc, __in int dx, __in int dy);
WINBASEAPI	DWORD	WINAPI		GetCurrentDirectory		(__in DWORD nBufferLength, s8 lpBuffer[_MAX_PATH]);
int								sopen					(cs8* tcPathname, s32 mode, s32 sharing);
s64								telli64					(s32 fileno);
WINBASEAPI	HANDLE	WINAPI		FindFirstFile			(__in cs8* lpFileName, __out LPWIN32_FIND_DATA lpFindFileData);
WINBASEAPI	BOOL	WINAPI		FindNextFile			(__in HANDLE hFindFile, __out LPWIN32_FIND_DATA lpFindFileData);
WINBASEAPI	DWORD	WINAPI		GetFullPathName			(__in cs8* lpFileName, __in DWORD nBufferLength, s8 lpBuffer[_MAX_PATH], s8** lpFilePart);
WINBASEAPI	DWORD	WINAPI		GetTempPath				(__in DWORD nBufferLength, s8 lpBuffer[_MAX_PATH]);
WINBASEAPI	UINT	WINAPI		GetTempFileName			(__in cs8* lpPathName, __in cs8* lpPrefixString, __in UINT uUnique, s8 lpTempFileName[_MAX_PATH]);
WINGDIAPI	int		WINAPI		GetDeviceCaps			(__in_opt HDC hdc, __in int index);
WINBASEAPI	int		WINAPI		MulDiv					(__in int nNumber, __in int nNumerator, __in int nDenominator);
WINGDIAPI	HFONT	WINAPI		CreateFont				( __in int cHeight, __in int cWidth, __in int cEscapement, __in int cOrientation, __in int cWeight, __in DWORD bItalic, __in DWORD bUnderline, __in DWORD bStrikeOut, __in DWORD iCharSet, __in DWORD iOutPrecision, __in DWORD iClipPrecision, __in DWORD iQuality, __in DWORD iPitchAndFamily, __in_opt cs8* pszFaceName);
WINGDIAPI	BOOL	WINAPI		GetTextMetricsA			(__in HDC hdc, __out LPTEXTMETRIC lptm);
WINGDIAPI	HGDIOBJ	WINAPI		GetStockObject			(__in DWORD obj);
