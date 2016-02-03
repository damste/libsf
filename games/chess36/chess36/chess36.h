//////////
//
// chess36.h
//
//////////
//
//


#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <png.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>




#define RGB(r,g,b)									 ((b & 0xff) << 16) | ((g & 0xff) << 8) | (r & 0xff)
#define RGBA(r,g,b,a)			((a & 0xff) << 24) | ((b & 0xff) << 16) | ((g & 0xff) << 8) | (r & 0xff)

#define _SQUARE_WIDTH			80
#define _SQUARE_HEIGHT			80

// Size of android devices
#define _SCREEN_WIDTH			480
#define _SCREEN_HEIGHT			854

// Mouse options
#define _MOUSE_OVER				1		// Mouse is hovering over the item
#define _MOUSE_DOWN				2		// Mouse button is being clicked
#define _MOUSE_NEUTRAL			3		// Mouse is away from the item
#define _MOUSE_IN_MENU			4		// Is the mouse somewhere in the menu area?

#define _NO_ACTIVITY			0
#define	_BOARD_ACTIVITY			1
#define	_MENU_ACTIVITY			2
#define	_MOUSE_ACTIVITY			128

// Used various places
#define _ERROR					-1
#define _EMPTY					0

#define _WHITE_PAWN				1
#define _WHITE_KNIGHT			2
#define _WHITE_BISHOP			3
#define _WHITE_ROOK				4
#define _WHITE_QUEEN			5
#define _WHITE_KING				6

#define _BLACK_PAWN				11
#define _BLACK_KNIGHT			12
#define _BLACK_BISHOP			13
#define _BLACK_ROOK				14
#define _BLACK_QUEEN			15
#define _BLACK_KING				16

#define _MAIN_MENU				1
#define _OPTIONS_MENU			2
#define _GAME_PLAY				3

#define _WHITE					1
#define _BLACK					2

#define _NORMAL					1
#define _LAST_MOVE				2
#define _THREATS1				3
#define _THREATS2				4
#define _CAPTURE				3		// When a piece is captured, it's in the threats1 color
#define _KING_IN_CHECK			3		// When the king is in check, it's the threats1 color
#define _CAPTURE_BACK			4		// When a piece can immediately capture back, it's in the threates2 color
#define _CANNOT_MOVE			4		// When a piece cannot move, its square shows up in red
#define _CANDIDATE				5
#define _OPPONENT_LAST_MOVE		6

typedef unsigned char			u8;
typedef unsigned short			u16;
typedef unsigned int			u32;
typedef char					s8;
typedef short					s16;
typedef int						s32;
typedef float					f32;
typedef double					f64;

struct XWindow
{
	Display*	display;
	Window		window;
	Screen*		screenptr;
	int			screennum;
	Visual*		visual;
	GC			gc;

	XImage*		ximage;
	u8*			virtualscreen;

	int			width;
	int			height;
	int			depth;
	int			pixelsize;
	int			screensize;

} __attribute__((packed));

struct SRGB24
{
	u8		blu;
	u8		grn;
	u8		red;
} __attribute__((packed));

struct SRGBA32
{
	u8		red;
	u8		grn;
	u8		blu;
	u8		alp;
} __attribute__((packed));

struct SBGRA32
{
	u8		blu;
	u8		grn;
	u8		red;
	u8		alp;
} __attribute__((packed));

struct SPNG
{
	png_structp		png;			// Pointer to loaded PNG buffer
	u8**			rows;			// Pointer to start of each row for loaded PNG buffer
	png_infop		info;			// Pointer to loaded PNG info

	// The following are used to hold variations of the originally loaded image, such as after a transformation (alpha and colorization)
	SRGBA32*		img1;			// Normal image
	SRGBA32*		img2;			// Highlighted image, for squares it's "last move"
	SRGBA32*		img3;			// Highlighted image, for squares it's "threats one move out"
	SRGBA32*		img4;			// Highlighted image, for squares it's "threats two moves out"
	SRGBA32*		img5;			// Highlighted image, for squares it's "candidate move" (not yet submitted)
	SRGBA32*		img6;			// Highlighted image, for squares it's "opponent's last move"

	// Added for button objects
	u32				buttonImage;	// Image to display (1-6) for the button state
	s32				ulx;			// Upper-left X coordinate for the range where the mouse operates on this button
	s32				uly;			// Upper-left Y coordinate for the range where the mouse operates on this button
	s32				lrx;			// Lower-right X coordinate for the range where the mouse operates on this button
	s32				lry;			// Lower-right Y coordinate for the range where the mouse operates on this button
	s8*				buttonCommand;	// Command to execute when clicked

	// Added for animated objects, which are updated 25x per second
	SRGBA32**		animation;		// Pointer to list of SRGB32* buffers
	u32				frames;			// Number of buffers / frames there

	bool			active;			// Is the animation active?
	u32				counter;		// What is the current counter?
	u32				trigger;		// At what count is it triggered?
	u32				x;				// Where is it drawn (X coordinate)?
	u32				y;				// Where is it drawn (Y coordinate)?
};

struct SBitmapHead
{
	u16		type;
	u32		fileSize;
	u16		reserved1;
	u16		reserved2;
	u32		bitsOffset;
} __attribute__((packed));

struct SBitmapInfo
{
	u32		size;
	u32		width;
	u32		height;
	u16		planes;
	u16		bits;
	union
	{
		u32		compression;
		u32		actual_width;
	};
	u32		sizeImage;
	u32		xppm;
	u32		yppm;
	u32		colorsUsed;
	u32		colorsImportant;
} __attribute__((packed));

struct SBoardRow
{
	u32		x1;
	u32		x2;
	u32		x3;
	u32		x4;
	u32		x5;
	u32		x6;
};

struct SBoard
{
	SBoardRow	a;
	SBoardRow	b;
	SBoardRow	c;
	SBoardRow	d;
	SBoardRow	e;
	SBoardRow	f;
};

struct SLinkList
{
	void*		next;			// Next item in link list
	void*		prev;			// Prev item in link list
};

struct SCommand
{
	SLinkList	ll;				// Next/Prev items

	s8*			type;			// Type of command, such as "enter", "leave", "leftclick", etc.
	s8*			command;		// Identifier of what to do
};

struct SUndo
{
	SLinkList	ll;				// Next/Prev items

	u32			turn;			// Was it white or black's turn?
	u32			lastRow;		// last row clicked at the time of this move
	u32			lastCol;		// last col clicked at the time of this move
	SBoard		pieces;			// Arrangement of pieces on the board
	SBoard		board;			// The highlighted condition of the chess board itsel
};

struct SItem
{
	SLinkList	ll;				// Next/Prev items

	s32			x;				// x coordinate of upper-left corner
	s32			y;				// y-coordinate of upper-left corner
	SPNG*		neutral;		// Image to display when neutral
	SPNG*		over;			// Image to display when mouse is over it
	SPNG*		click;			// Image to dispaly when mouse is down
	s8*			command;		// Command to execute when clicked
};

struct SForm
{
	SLinkList	ll;				// Next/Prev items
	SItem*		firstItem;		// Pointer to the first item for this form
};

struct SGameState
{
	SLinkList	ll;				// Next/Prev items
	SForm*		form;			// First item for this form to draw
};

void		loadBoardPiecesAndGraphics					(void);
void		iTransformCopy								(SPNG& spng, SRGBA32** img);
void		iTransformColorize							(SPNG& spng, SRGBA32** img, u32 foreColor, bool colorizeAlpha);
void		iTransformColorizeInverted					(SPNG& spng, SRGBA32** img, u32 foreColor, bool colorizeAlpha);
void		iTransformColorizeWithSpectrumAndBrightness	(SPNG& spng, SRGBA32** img, u32 foreColor, f32 spectrum, f32 brightness, bool colorizeAlpha);
void		iCreateButtons								(s8* button1, s8* command1, s8* button2, s8* command2, s8* button3, s8* command3, s8* button4, s8* command4, s8* button5, s8* command5, s8* button6, s8* command6, s8* strip1, s8* scommand1, s8* strip2, s8* scommand2);
void		iCreateButton								(SPNG& spng, s8* text, SPNG& spng1, SPNG& spng2, SPNG& spng3, SPNG& spng4, u32 xOffset, u32 yOffset, u32 x, u32 y, u32 width, u32 height, u32 foreground, u32 background);
void		iExtractRectangle							(SRGBA32** rgbd, SPNG& spng, u32 x, u32 y, u32 width, u32 height);
void		iCreateAnimationFromThreeImages				(SPNG& spngd, u32 frames, SPNG& spng1, SRGBA32* img1, SPNG& spng2, SRGBA32* img2, SPNG& spng3, SRGBA32* img3);
u32			iLighten									(u32 colors, f32 percent);
void		iDrawText									(SPNG& spng,  SRGBA32* img, s8* text, u32 length, u32 foreground, u32 background, f32 transparency, bool opaque, bool dither);
void		iCopyImgToImg								(SPNG& spngd, SRGBA32* dest, s32 ulxd, s32 ulyd, s32 width, s32 height, SPNG& spngs, SRGBA32* source, s32 ulxs, s32 ulys, bool repeat, bool inverted);
void		iOverlayImgToImgCenter						(SPNG& spngd, SRGBA32* dest, SPNG& spngs, SRGBA32* source, s32 ulxs, s32 ulys, bool repeat, bool inverted);
void		iOverlayImgToImg							(SPNG& spngd, SRGBA32* dest, s32 ulxd, s32 ulyd, s32 width, s32 height, SPNG& spngs, SRGBA32* source, s32 ulxs, s32 ulys, bool repeat, bool inverted);
void		createChessWindow							(void);
void		iDrawChessBoard								(void);
void		iSwapForPriorBoard							(SBoard** saveBoard, SBoard** savePieces);
void		iSwapToCurrentBoard							(SBoard** saveBoard, SBoard** savePieces);
SRGBA32*	iGetBoardImage								(u32 row, u32 col, bool isBlack);
void		iResetChessBoard							(void);
void		iResetChessPositions						(SBoard& tpieces);
void		iDrawPieces									(SBoard& tpieces);
void		iDrawMenu									(void);
void		iOverlayCapturedPieces						(void);
void		iOverlayButtons								(void);
void		iDisplayButton								(SPNG& spng);
bool		iFindPiece									(u32 piece, s32* row, s32* col);
u32			iCountPieces								(u32 piece);
void		iDrawMenuMain								(void);
void		iDrawMenuOptions							(void);
void		iDrawMenuGamePlay							(void);
void		iBitBltCenter								(u32 x, u32 y, u32 width, u32 height, SPNG& spng, SRGBA32* img);
void		iBitBlt										(u32 x, u32 y, u32 width, u32 height, SPNG& spng, SRGBA32* img);
void		iBitBltTransparent							(f32 transparency, u32 x, u32 y, u32 width, u32 height, SPNG& spng, SRGBA32* img);
void		iRectangle									(u32 ulx, u32 uly, u32 lrx, u32 lry, u32 color);
void		iFillRectangle								(u32 ulx, u32 uly, u32 lrx, u32 lry, u32 color);
void		playChessGame								(void);
void		loadPNG										(s8* name, SPNG& spng);
void		iCopyPngToBmp24								(SPNG& spng, SRGBA32** imgc, s8* filename);
void		iCopyPngToBmp32								(SPNG& spng, SRGBA32** imgc, s8* filename);
u32			iGetBoardPiece								(SBoard& tpieces, s32 row, s32 col);
u32			iGetBoardPieceColor							(SBoard& tpieces, s32 row, s32 col);
u32			iGetPieceColor								(u32 piece);
u32			iGetOpponentPieceColor						(u32 piece);
void		iSetBoardPiece								(SBoard& tpieces, u32 piece, s32 row, s32 col);
SPNG&		iGetBoardPieceSPNG							(SBoard& tpieces, s32 row, s32 col);
SRGBA32*	iGetBoardPieceImg							(SBoard& tpieces, s32 row, s32 col, bool checkmate);
bool		iIsBoardPieceEmpty							(SBoard& tpieces, s32 row, s32 col);
void		iSetChessSquare								(u32 style, s32 row, s32 col);
u32			iGetChessSquare								(s32 row, s32 col);
void		iToggleChessSquare							(s32 row, s32 col);
bool		iMoveIfValid								(SBoard& tpieces, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo, bool checkKingInCheck);
bool		iHighlightMovesIfPieceClickedIsValidToMove	(SBoard& tpieces, s32 rowFrom, s32 colFrom);
bool		isItThisPiecesTurn							(u32 piece);
bool		canThisPieceMoveHere						(SBoard& tpieces, u32 piece, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo, bool checkForInCheck);
bool		canPawnMoveHere								(SBoard& tpieces, u32 color, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo, bool checkForInCheck);
bool		canKnightMoveHere							(SBoard& tpieces, u32 color, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo, bool checkForInCheck);
bool		isAnotherPieceAdjacent						(SBoard& tpieces, s32 row, s32 col);
bool		canBishopMoveHere							(SBoard& tpieces, u32 color, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo, bool checkForInCheck);
bool		iTestUpDownRightLeftMoves					(SBoard& tpieces, u32 delta, bool& upValid, bool& rtValid, bool& dnValid, bool& ltValid, u32 colorOpponent, u32 colorFrom, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo, bool checkForInCheck);
bool		iTestDiagonalMoves							(SBoard& tpieces, u32 delta, bool& ulValid, bool& urValid, bool& lrValid, bool& llValid, u32 colorOpponent, u32 colorFrom, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo, bool checkForInCheck);
bool		iFarMoveTest								(SBoard& tpieces, bool& variable, s32 rowDelta, s32 colDelta, u32 colorOpponent, u32 colorFrom, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo, bool checkForInCheck);
bool		canRookMoveHere								(SBoard& tpieces, u32 color, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo, bool checkForInCheck);
bool		canQueenMoveHere							(SBoard& tpieces, u32 color, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo, bool checkForInCheck);
bool		canKingMoveHere								(SBoard& tpieces, u32 color, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo);
void		iCopyBoard									(SBoard& dest, SBoard& source);
bool		willMovingThisPiecePutKingInCheck			(SBoard& tpieces, u32 color, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo);
bool		isKingInCheck								(SBoard& tpieces, s32 rowKing, s32 colKing);
void		iHighlightKingInCheckPiecesOnBoard			(SBoard& tpieces, SBoard& board, u32 color);
bool		isKingInCheckmate							(SBoard& tpieces, s32 rowKing, s32 colKing);
bool		iGetKingRowAndCol							(SBoard& tpieces, u32 colorKing, s32& rowKing, s32& colKing);
bool		isRowAndColValid							(s32 row, s32 col);
void		iSaveUndo									(SBoard& tpieces, SBoard& tboard);
void		iDoUndo										(SBoard& tpieces, SBoard& tboard);
void		iDoRedo										(SBoard& tpieces, SBoard& tboard);
bool		iCheckMouseMovement							(void);
u32			iCheckButton								(SPNG& spng);
void		iQueueCommand								(s8* type, s8* command);
void		iExecuteCommands							(void);
void		iFirstClicked								(void);
void		iPrevClicked								(void);
void		iNextClicked								(void);
void		iLastClicked								(void);
void		iUndoClicked								(void);
void		iRedoClicked								(void);
void		iOptionsClicked								(void);
void		iExitClicked								(void);
void		iRefresh									(void);


// x11.cpp
int			initXWindow									(XWindow* xw, int width, int height, int bpp, char *title, bool createbuffer);
void		drawContent									(XWindow* xw);
void		onBreak										(int arg);
void		clearKeyboardBuffer							(XWindow* xw);
