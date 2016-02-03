//////////
//
// chess36.cpp
//
//////////
//
// Chess36, a 6x6 chess board variation sacrificing two pawns, one knight and one bishop,
// with some alternate rules for how the pawns, knight and bishop can move:
//
//		1)  Pawns can always only move one square, including the opening move.
//		2)  Since pawns cannot move two squares, no en passant.
//		3)  Bishops always start on black, so their movement each turn can either
//			be traditional, or they can move as a king (one square only side to
//			side or up and down).
//		4)  Knights can only move 2+1 if jumping over a piece, otherwise they
//			only move one square diagonally.
//		5)  Kings always start on white.
//		6)  Queens always start on black.
//		7)  No castling.
//
//




#include "chess36.h"
#include "8x16.h"
#include <signal.h>
#include <strings.h>

// Graphics used for pieces in the game
SPNG			gsPngKing;
SPNG			gsPngQueen;
SPNG			gsPngRook;
SPNG			gsPngBishop;
SPNG			gsPngKnight;
SPNG			gsPngPawn;
SPNG			gsPngBlack;
SPNG			gsPngWhite;
SPNG			gsPngEmpty;
SPNG			gsPngQuestion;

SPNG			gsPngKingSmall;
SPNG			gsPngQueenSmall;
SPNG			gsPngRookSmall;
SPNG			gsPngBishopSmall;
SPNG			gsPngKnightSmall;
SPNG			gsPngPawnSmall;
SPNG			gsPngEmptySmall;

SPNG			gsPngBottom;
SPNG			gsPngRainbow1;
SPNG			gsPngRainbow2;
SPNG			gsPngRainbow3;
SPNG			gsPngRainbow4;
SPNG			gsPngStrip1;
SPNG			gsPngStrip2;
SPNG			gsPngStrip3;
SPNG			gsPngStrip4;
SPNG			gsPngPromotion;

SPNG			gsPngRainbowButton1;
SPNG			gsPngRainbowButton2;
SPNG			gsPngRainbowButton3;
SPNG			gsPngRainbowButton4;
SPNG			gsPngRainbowButton5;
SPNG			gsPngRainbowButton6;
SPNG			gsPngStripButton1;
SPNG			gsPngStripButton2;

// Overlays for buttons (to use graphics rather than text)
SPNG			gsPngFirst;
SPNG			gsPngPrev;
SPNG			gsPngNext;
SPNG			gsPngLast;
SPNG			gsPngUndo;
SPNG			gsPngRedo;
SPNG			gsPngOptions;
SPNG			gsPngExit;


SBoard board =
{
	/* white pieces row 0, 1 */
	{/*row 0, a1*/_NORMAL,	/*b1*/_NORMAL,	/*c1*/_NORMAL,	/*d1*/_NORMAL,	/*e1*/_NORMAL,	/*f1*/_NORMAL	},	// row 0, a1..f1
	{/*row 1, a2*/_NORMAL,	/*b2*/_NORMAL,	/*c2*/_NORMAL,	/*d2*/_NORMAL,	/*e2*/_NORMAL,	/*f2*/_NORMAL	},	// row 1, a2..f6
	{/*row 2, a3*/_NORMAL,	/*b3*/_NORMAL,	/*c3*/_NORMAL,	/*d3*/_NORMAL,	/*e3*/_NORMAL,	/*f3*/_NORMAL	},	// row 2, a3..f3
	{/*row 3, a4*/_NORMAL,	/*b4*/_NORMAL,	/*c4*/_NORMAL,	/*d4*/_NORMAL,	/*e4*/_NORMAL,	/*f4*/_NORMAL	},	// row 3, a4..f4
	{/*row 4, a5*/_NORMAL,	/*b5*/_NORMAL,	/*c5*/_NORMAL,	/*d5*/_NORMAL,	/*e5*/_NORMAL,	/*f5*/_NORMAL	},	// row 4, a5..f5
	{/*row 5, a6*/_NORMAL,	/*b6*/_NORMAL,	/*c6*/_NORMAL,	/*d6*/_NORMAL,	/*e6*/_NORMAL,	/*f6*/_NORMAL	}	// row 5, a6..f6
	/* black pieces row 4, 5 */
};

SBoard pieces =
{
	{/*row 0, a1*/_EMPTY,	/*b1*/_EMPTY,	/*c1*/_EMPTY,	/*d1*/_EMPTY,	/*e1*/_EMPTY,	/*f1*/_EMPTY	},	// row 0, a1..f1
	{/*row 1, a2*/_EMPTY,	/*b2*/_EMPTY,	/*c2*/_EMPTY,	/*d2*/_EMPTY,	/*e2*/_EMPTY,	/*f2*/_EMPTY	},	// row 1, a2..f6
	{/*row 2, a3*/_EMPTY,	/*b3*/_EMPTY,	/*c3*/_EMPTY,	/*d3*/_EMPTY,	/*e3*/_EMPTY,	/*f3*/_EMPTY	},	// row 2, a3..f3
	{/*row 3, a4*/_EMPTY,	/*b4*/_EMPTY,	/*c4*/_EMPTY,	/*d4*/_EMPTY,	/*e4*/_EMPTY,	/*f4*/_EMPTY	},	// row 3, a4..f4
	{/*row 4, a5*/_EMPTY,	/*b5*/_EMPTY,	/*c5*/_EMPTY,	/*d5*/_EMPTY,	/*e5*/_EMPTY,	/*f5*/_EMPTY	},	// row 4, a5..f5
	{/*row 5, a6*/_EMPTY,	/*b6*/_EMPTY,	/*c6*/_EMPTY,	/*d6*/_EMPTY,	/*e6*/_EMPTY,	/*f6*/_EMPTY	}	// row 5, a6..f6
};

SCommand*		gsCommandRoot		= NULL;
SUndo*			gsUndoRoot			= NULL;
SUndo*			gsRedoRoot			= NULL;
SGameState*		gsGameState			= NULL;

s32				gnBoard				= 0;			// Indicates which board to display (0=current, anything less than 0 is a previous board)
u32				gnTurnColor			= _WHITE;
s32				gnLastRowClicked	= -1;
s32				gnLastColClicked	= -1;

// X-windows support
XWindow*		xwm;
volatile bool	gbFocus				= true;
int				gnMouseX;			// Horizontal coordinate
int				gnMouseY;			// Vertical coordinate
bool			gbMouseLeft;		// Is the left button involved
bool			gbMouseMiddle;		// Is the middle button involved
bool			gbMouseRight;		// Is the right button involved
bool			gbMouseDown;		// Is the mouse button pressed down (if false, then just released)

// Used for the game loop
bool			gbProgramIsRunning = false;




int main (int argc, char* argv[])
{
	printf ( (s8*) "Chess36 -- A 6x6 chess game. Faster to play. Not less challenging.\n");
	printf ( (s8*) "-----\n");
	printf ( (s8*) "Originally: 2011.12.19\n");
	printf ( (s8*) "  Released: 2012.07.07\n");
	printf ( (s8*) "   Version: 0.90 - This version still has bugs and unfinished components.\n");
	printf ( (s8*) "-----\n");
	printf ( (s8*) "Written by Rick C. Hodgin.\n");
	printf ( (s8*) "Send Chess36 questions via email to rick dot c dot hodgin at gmail dot com.\n");
	printf ( (s8*) "\n");
	printf ( (s8*) "-----\n");
	printf ( (s8*) "This project is free software licensed under the GNU General Public License v3.\n");
	printf ( (s8*) "For additional information on free (libre) software, visit www.fsf.org.\n");
	printf ( (s8*) "For information on the GNU GPLv3, visit http://gplv3.fsf.org.\n");
	printf ( (s8*) "Freedom, as in liberty.\n");
	printf ( (s8*) "-----\n");

	loadBoardPiecesAndGraphics();		// Loads the graphical images
	createChessWindow();				// Creates the chess game from its last saved state

	// Populate the buffer with the default board
	iDrawChessBoard();
	iResetChessPositions (pieces);
	iDrawPieces (pieces);
	iDrawMenu();

	// Tell X-windows to draw it
	drawContent(xwm);

	// Begin the game
	playChessGame();

	// Control will never return here, but the compiler requires this next line
	return 0;
}




void loadBoardPiecesAndGraphics (void)
{
	// Load the images
	loadPNG ( (s8*) "graphics/king.png",				gsPngKing);
	loadPNG ( (s8*) "graphics/queen.png",				gsPngQueen);
	loadPNG ( (s8*) "graphics/rook.png",				gsPngRook);
	loadPNG ( (s8*) "graphics/bishop.png",				gsPngBishop);
	loadPNG ( (s8*) "graphics/knight.png",				gsPngKnight);
	loadPNG ( (s8*) "graphics/pawn.png",				gsPngPawn);
	loadPNG ( (s8*) "graphics/black.png",				gsPngBlack);
	loadPNG ( (s8*) "graphics/white.png",				gsPngWhite);
	loadPNG ( (s8*) "graphics/empty.png",				gsPngEmpty);
	loadPNG ( (s8*) "graphics/question.png",			gsPngQuestion);
	loadPNG ( (s8*) "graphics/king_small.png",			gsPngKingSmall);
	loadPNG ( (s8*) "graphics/queen_small.png",			gsPngQueenSmall);
	loadPNG ( (s8*) "graphics/rook_small.png",			gsPngRookSmall);
	loadPNG ( (s8*) "graphics/bishop_small.png",		gsPngBishopSmall);
	loadPNG ( (s8*) "graphics/knight_small.png",		gsPngKnightSmall);
	loadPNG ( (s8*) "graphics/pawn_small.png",			gsPngPawnSmall);
	loadPNG ( (s8*) "graphics/empty_small.png",			gsPngEmptySmall);
	loadPNG ( (s8*) "graphics/bottom.png",				gsPngBottom);
	loadPNG ( (s8*) "graphics/rainbow1.png",			gsPngRainbow1);
	loadPNG ( (s8*) "graphics/rainbow2.png",			gsPngRainbow2);
	loadPNG ( (s8*) "graphics/rainbow3.png",			gsPngRainbow3);
	loadPNG ( (s8*) "graphics/rainbow3.png",			gsPngRainbow4);
	loadPNG ( (s8*) "graphics/strip1.png",				gsPngStrip1);
	loadPNG ( (s8*) "graphics/strip2.png",				gsPngStrip2);
	loadPNG ( (s8*) "graphics/strip3.png",				gsPngStrip3);
	loadPNG ( (s8*) "graphics/strip3.png",				gsPngStrip4);
	loadPNG ( (s8*) "graphics/promotion.png",			gsPngPromotion);
	loadPNG ( (s8*) "graphics/first.png",				gsPngFirst);
	loadPNG ( (s8*) "graphics/prev.png",				gsPngPrev);
	loadPNG ( (s8*) "graphics/next.png",				gsPngNext);
	loadPNG ( (s8*) "graphics/last.png",				gsPngLast);
	loadPNG ( (s8*) "graphics/undo.png",				gsPngUndo);
	loadPNG ( (s8*) "graphics/redo.png",				gsPngRedo);
	loadPNG ( (s8*) "graphics/options.png",				gsPngOptions);
	loadPNG ( (s8*) "graphics/exit.png",				gsPngExit);

	// Colorize the items for white and black characters
	iTransformColorize			(gsPngKing,			&gsPngKing.img1,			RGB (255, 255, 255),	true);
	iTransformColorizeInverted	(gsPngKing,			&gsPngKing.img2,			RGB (255, 255, 255),	true);
	iTransformColorize			(gsPngKing,			&gsPngKing.img3,			RGB (192, 0, 0),		true);
	iTransformColorize			(gsPngKing,			&gsPngKing.img4,			RGB (192, 0, 0),		true);

	iTransformColorize			(gsPngQueen,		&gsPngQueen.img1,			RGB (255, 255, 255),	true);
	iTransformColorizeInverted	(gsPngQueen,		&gsPngQueen.img2,			RGB (255, 255, 255),	true);
	iTransformColorize			(gsPngQueen,		&gsPngQueen.img3,			RGB (192, 0, 0),		true);
	iTransformColorize			(gsPngQueen,		&gsPngQueen.img4,			RGB (192, 0, 0),		true);

	iTransformColorize			(gsPngRook,			&gsPngRook.img1,			RGB (255, 255, 255),	true);
	iTransformColorizeInverted	(gsPngRook,			&gsPngRook.img2,			RGB (255, 255, 255),	true);
	iTransformColorize			(gsPngRook,			&gsPngRook.img3,			RGB (192, 0, 0),		true);
	iTransformColorize			(gsPngRook,			&gsPngRook.img4,			RGB (192, 0, 0),		true);

	iTransformColorize			(gsPngBishop,		&gsPngBishop.img1,			RGB (255, 255, 255),	true);
	iTransformColorizeInverted	(gsPngBishop,		&gsPngBishop.img2,			RGB (255, 255, 255),	true);
	iTransformColorize			(gsPngBishop,		&gsPngBishop.img3,			RGB (192, 0, 0),		true);
	iTransformColorize			(gsPngBishop,		&gsPngBishop.img4,			RGB (192, 0, 0),		true);

	iTransformColorize			(gsPngKnight,		&gsPngKnight.img1,			RGB (255, 255, 255),	true);
	iTransformColorizeInverted	(gsPngKnight,		&gsPngKnight.img2,			RGB (255, 255, 255),	true);
	iTransformColorize			(gsPngKnight,		&gsPngKnight.img3,			RGB (192, 0, 0),		true);
	iTransformColorize			(gsPngKnight,		&gsPngKnight.img4,			RGB (192, 0, 0),		true);

	iTransformColorize			(gsPngPawn,			&gsPngPawn.img1,			RGB (255, 255, 255),	true);
	iTransformColorizeInverted	(gsPngPawn,			&gsPngPawn.img2,			RGB (255, 255, 255),	true);
	iTransformColorize			(gsPngPawn,			&gsPngPawn.img3,			RGB (192, 0, 0),		true);
	iTransformColorize			(gsPngPawn,			&gsPngPawn.img4,			RGB (192, 0, 0),		true);

	iTransformColorize			(gsPngEmpty,		&gsPngEmpty.img1,			RGB (255, 255, 255),	true);
	iTransformColorizeInverted	(gsPngEmpty,		&gsPngEmpty.img2,			RGB (255, 255, 255),	true);
	iTransformColorize			(gsPngEmpty,		&gsPngEmpty.img3,			RGB (192, 0, 0),		true);
	iTransformColorize			(gsPngEmpty,		&gsPngEmpty.img4,			RGB (192, 0, 0),		true);

	iTransformCopy				(gsPngQuestion,		&gsPngQuestion.img1);

	iTransformColorize			(gsPngKingSmall,	&gsPngKingSmall.img1,		RGB (255, 255, 255), true);
	iTransformColorize			(gsPngQueenSmall,	&gsPngQueenSmall.img1,		RGB (255, 255, 255), true);
	iTransformColorize			(gsPngRookSmall,	&gsPngRookSmall.img1,		RGB (255, 255, 255), true);
	iTransformColorize			(gsPngBishopSmall,	&gsPngBishopSmall.img1,		RGB (255, 255, 255), true);
	iTransformColorize			(gsPngKnightSmall,	&gsPngKnightSmall.img1,		RGB (255, 255, 255), true);
	iTransformColorize			(gsPngPawnSmall,	&gsPngPawnSmall.img1,		RGB (255, 255, 255), true);
	iTransformColorize			(gsPngEmptySmall,	&gsPngEmptySmall.img1,		RGB (255, 255, 255), true);

	iTransformColorizeInverted	(gsPngKingSmall,	&gsPngKingSmall.img2,		RGB (255, 255, 255), true);
	iTransformColorizeInverted	(gsPngQueenSmall,	&gsPngQueenSmall.img2,		RGB (255, 255, 255), true);
	iTransformColorizeInverted	(gsPngRookSmall,	&gsPngRookSmall.img2,		RGB (255, 255, 255), true);
	iTransformColorizeInverted	(gsPngBishopSmall,	&gsPngBishopSmall.img2,		RGB (255, 255, 255), true);
	iTransformColorizeInverted	(gsPngKnightSmall,	&gsPngKnightSmall.img2,		RGB (255, 255, 255), true);
	iTransformColorizeInverted	(gsPngPawnSmall,	&gsPngPawnSmall.img2,		RGB (255, 255, 255), true);
	iTransformColorizeInverted	(gsPngEmptySmall,	&gsPngEmptySmall.img2,		RGB (255, 255, 255), true);

	// Colorize the black square for highlight operations
//	iTransformCopy								(gsPngBlack,	&gsPngBlack.img1);
	iTransformColorizeWithSpectrumAndBrightness	(gsPngBlack,	&gsPngBlack.img1,	RGB (112, 112, 164),	0.5,	1.5,	true);
	iTransformColorizeWithSpectrumAndBrightness	(gsPngBlack,	&gsPngBlack.img2,	RGB (64, 64, 255),		0.5,	1.5,	true);
	iTransformColorizeWithSpectrumAndBrightness	(gsPngBlack,	&gsPngBlack.img3,	RGB (255, 192, 128),	0.5,	2.0,	true);
	iTransformColorizeWithSpectrumAndBrightness	(gsPngBlack,	&gsPngBlack.img4,	RGB (235, 64, 64),		0.7,	1.3,	true);
	iTransformColorizeWithSpectrumAndBrightness	(gsPngBlack,	&gsPngBlack.img5,	RGB (64, 255, 64),		0.7,	1.7,	true);
	iTransformColorizeWithSpectrumAndBrightness	(gsPngBlack,	&gsPngBlack.img6,	RGB (255, 255, 0),		0.5,	1.3,	true);

	// Colorize the white square for highlight operations
//	iTransformCopy								(gsPngWhite,	&gsPngWhite.img1);
	iTransformColorizeWithSpectrumAndBrightness	(gsPngWhite,	&gsPngWhite.img1,	RGB (215, 215, 255),	1.2,	1.0,	true);
	iTransformColorizeWithSpectrumAndBrightness	(gsPngWhite,	&gsPngWhite.img2,	RGB (64, 64, 255),		1.2,	1.0,	true);
	iTransformColorizeWithSpectrumAndBrightness	(gsPngWhite,	&gsPngWhite.img3,	RGB (255, 192, 128),	1.5,	1.0,	true);
	iTransformColorizeWithSpectrumAndBrightness	(gsPngWhite,	&gsPngWhite.img4,	RGB (192, 64, 64),		1.2,	1.0,	true);
	iTransformColorizeWithSpectrumAndBrightness	(gsPngWhite,	&gsPngWhite.img5,	RGB (64, 215, 64),		1.2,	1.0,	true);
	iTransformColorizeWithSpectrumAndBrightness	(gsPngWhite,	&gsPngWhite.img6,	RGB (255, 255, 0),		1.2,	1.0,	true);

	iTransformCopy	(gsPngBottom,		&gsPngBottom.img1);
	iTransformCopy	(gsPngRainbow1,		&gsPngRainbow1.img1);
	iTransformCopy	(gsPngRainbow2,		&gsPngRainbow2.img1);
	iTransformCopy	(gsPngRainbow3,		&gsPngRainbow3.img1);
	iTransformCopy	(gsPngRainbow4,		&gsPngRainbow4.img1);
	iTransformCopy	(gsPngStrip1,		&gsPngStrip1.img1);
	iTransformCopy	(gsPngStrip2,		&gsPngStrip2.img1);
	iTransformCopy	(gsPngStrip3,		&gsPngStrip3.img1);
	iTransformCopy	(gsPngStrip4,		&gsPngStrip4.img1);
	iTransformCopy	(gsPngPromotion,	&gsPngPromotion.img1);

	iTransformCopy	(gsPngFirst,		&gsPngFirst.img1);
	iTransformCopy	(gsPngPrev,			&gsPngPrev.img1);
	iTransformCopy	(gsPngNext,			&gsPngNext.img1);
	iTransformCopy	(gsPngLast,			&gsPngLast.img1);
	iTransformCopy	(gsPngUndo,			&gsPngUndo.img1);
	iTransformCopy	(gsPngRedo,			&gsPngRedo.img1);
	iTransformCopy	(gsPngOptions,		&gsPngOptions.img1);
	iTransformCopy	(gsPngExit,			&gsPngExit.img1);

	// Create the buttons we'll use for normal navigation
	iCreateButtons ( (s8*) "$first",	(s8*) "first",
	                 (s8*) "$prev",		(s8*) "prev",
	                 (s8*) "$next",		(s8*) "next",
	                 (s8*) "$last",		(s8*) "last",
	                 (s8*) "$undo",		(s8*) "undo",
	                 (s8*) "$redo",		(s8*) "redo",
	                 (s8*) "$options",	(s8*) "options",
	                 (s8*) "$exit",		(s8*) "exit");

// For debugging, use to examine converted image:
//iCopyPngToBmp(gsPngButtonRight, &gsPngButtonRight.img2, (s8*)"graphics/button32.bmp");
}

//Do a literal copy of the PNG to the specified image
void iTransformCopy (SPNG& spng, SRGBA32** img)
{
	u32			lnx, lny;
	s8*			bd;
	SRGBA32*		lrgbs;
	SRGBA32*		lrgbd;

	// Initialize the output image for the specified size
	bd		= (s8*) malloc (spng.info->height * (spng.info->width * 4));
	*img	= (SRGBA32*) bd;

	// Copy each row
	for (lny = 0; lny < spng.info->height; lny++)
	{
		lrgbs	= (SRGBA32*) spng.rows[lny];
		lrgbd	= (SRGBA32*) (bd + (lny * spng.info->width * 4));

		for (lnx = 0; lnx < spng.info->width; lnx++)
		{
			lrgbd->alp		= lrgbs->alp;
			lrgbd->red		= lrgbs->red;
			lrgbd->grn		= lrgbs->grn;
			lrgbd->blu		= lrgbs->blu;

			++lrgbs;
			++lrgbd;
		}
	}
}

// Colors the source image
void iTransformColorize (SPNG& spng, SRGBA32** img, u32 foreColor, bool colorizeAlpha)
{
	u32			lnx, lny;
	f32			alp, red, grn, blu, k, mk, fred, fgrn, fblu;
	s8*			bd;
	SRGBA32*		lrgbs;
	SRGBA32*		lrgbd;

	// Grab the foreColor colors
	fred	= (f32) (  foreColor & 0x0000ff);
	fgrn	= (f32) ( (foreColor & 0x00ff00) >> 8);
	fblu	= (f32) ( (foreColor & 0xff0000) >> 16);

	// Initialize the output image for the specified size
	bd		= (s8*) malloc (spng.info->height * (spng.info->width * 4));
	*img	= (SRGBA32*) bd;

	// Copy and/or convert each line
	for (lny = 0; lny < spng.info->height; lny++)
	{
		lrgbs	= (SRGBA32*) spng.rows[lny];
		lrgbd	= (SRGBA32*) (bd + (lny * spng.info->width * 4));

		for (lnx = 0; lnx < spng.info->width; lnx++)
		{
			if (colorizeAlpha || lrgbs->alp == 255)
			{
				// Colorize with the alpha
				alp		= (f32) lrgbs->alp;
				red		= (f32) lrgbs->red;
				grn		= (f32) lrgbs->grn;
				blu		= (f32) lrgbs->blu;

				k		= ( (red * 0.35) + (grn * 0.54) + (blu * 0.11)) / 255.0;
				mk		= 1.0 - k;

				lrgbd->alp		= alp;
				lrgbd->red		= (u8) ( (fred * k) + (red * mk));
				lrgbd->grn		= (u8) ( (fgrn * k) + (grn * mk));
				lrgbd->blu		= (u8) ( (fblu * k) + (blu * mk));

			}

			else
			{
				// They're not colorizing alpha areas, so we leave those there
				lrgbd->alp	= lrgbs->alp;
				lrgbd->red	= lrgbs->red;
				lrgbd->grn	= lrgbs->grn;
				lrgbd->blu	= lrgbs->blu;
			}

			// Move to the next color item
			++lrgbs;
			++lrgbd;
		}
	}
}

// Colors the source image
void iTransformColorizeInverted (SPNG& spng, SRGBA32** img, u32 foreColor, bool colorizeAlpha)
{
	u32			lnx, lny;
	f32			alp, red, grn, blu, k, mk, fred, fgrn, fblu;
	s8*			bd;
	SRGBA32*	lrgbs;
	SRGBA32*	lrgbd;

	// Grab the foreColor colors
	fred	= (f32) (foreColor & 0x0000ff);
	fgrn	= (f32) ( (foreColor & 0x00ff00) >> 8);
	fblu	= (f32) ( (foreColor & 0xff0000) >> 16);

	// Initialize the output image for the specified size
	bd		= (s8*) malloc (spng.info->height * (spng.info->width * 4));
	*img	= (SRGBA32*) bd;

	// Copy and/or convert each line
	for (lny = 0; lny < spng.info->height; lny++)
	{
		lrgbs	= (SRGBA32*) spng.rows[lny];
		lrgbd	= (SRGBA32*) (bd + (lny * spng.info->width * 4));

		for (lnx = 0; lnx < spng.info->width; lnx++)
		{
			if (colorizeAlpha || lrgbs->alp == 255)
			{
				// Colorize with the alpha
				alp		= (f32) lrgbs->alp;
				red		= (f32) lrgbs->red;
				grn		= (f32) lrgbs->grn;
				blu		= (f32) lrgbs->blu;

				k		= ( (red * 0.35) + (grn * 0.54) + (blu * 0.11)) / 255.0;
				mk		= 1.0 - k;

				lrgbd->alp		= alp;
				lrgbd->red		= 255.0 - ( (u8) ( (fred * k) + (red * mk)));
				lrgbd->grn		= 255.0 - ( (u8) ( (fgrn * k) + (grn * mk)));
				lrgbd->blu		= 255.0 - ( (u8) ( (fblu * k) + (blu * mk)));
			}

			else
			{
				// They're not colorizing alpha areas, so we leave those there
				lrgbd->alp	= lrgbs->alp;
				lrgbd->red	= lrgbs->red;
				lrgbd->grn	= lrgbs->grn;
				lrgbd->blu	= lrgbs->blu;
			}

			// Move to the next color item
			++lrgbs;
			++lrgbd;
		}
	}
}

void iTransformColorizeWithSpectrumAndBrightness (SPNG& spng, SRGBA32** img, u32 foreColor, f32 spectrum, f32 brightness, bool colorizeAlpha)
{
	u32			lnx, lny;
	f32			alp, red, grn, blu, k, fred, fgrn, fblu;
	bool		useSpectrum, useBrightness;
	s8*			bd;
	SRGBA32*		lrgbs;
	SRGBA32*		lrgbd;

	// Grab the foreColor colors
	fred	= (f32) (  foreColor & 0x0000ff);
	fgrn	= (f32) ( (foreColor & 0x00ff00) >> 8);
	fblu	= (f32) ( (foreColor & 0xff0000) >> 16);

	// Initialize the output image for the specified size
	bd		= (s8*) malloc (spng.info->height * (spng.info->width * 4));
	*img	= (SRGBA32*) bd;

	// Determine the spectrum constant
	k				= 255.0 * (1.0 - spectrum);
	useSpectrum		= (spectrum != 1.0);
	useBrightness	= (brightness != 1.0);

	// Copy and colorize + contrast each line
	for (lny = 0; lny < spng.info->height; lny++)
	{
		lrgbs	= (SRGBA32*) spng.rows[lny];
		lrgbd	= (SRGBA32*) (bd + (lny * spng.info->width * 4));

		for (lnx = 0; lnx < spng.info->width; lnx++)
		{
			if (colorizeAlpha || lrgbs->alp == 255)
			{
				alp		= (f32) lrgbs->alp;
				red		= (f32) lrgbs->red;
				grn		= (f32) lrgbs->grn;
				blu		= (f32) lrgbs->blu;

				if (useSpectrum)
				{
					// Apply the spectrum adjustment, to take whatever the color is into the spectrum range
					red		= red * spectrum;
					grn		= grn * spectrum;
					blu		= blu * spectrum;
				}

				if (useBrightness)
				{
					// Apply the brightness
					red		= red * brightness;
					grn		= grn * brightness;
					blu		= blu * brightness;
				}

				if (useSpectrum)
				{
					// Adjust back into the spectrum
					red		= red + k;
					grn		= grn + k;
					blu		= blu + k;
				}

				// Verify each value is within the range
				red		= (red > 255.0) ? 255.0 : red;
				grn		= (grn > 255.0) ? 255.0 : grn;
				blu		= (blu > 255.0) ? 255.0 : blu;

				// Store the color
				lrgbd->alp	= (u8) alp;
				lrgbd->red	= (u8) ( (red / 255.0) * fred);
				lrgbd->grn	= (u8) ( (grn / 255.0) * fgrn);
				lrgbd->blu	= (u8) ( (blu / 255.0) * fblu);

			}

			else
			{
				// They're not colorizing alpha areas, so we leave those there
				lrgbd->alp	= lrgbs->alp;
				lrgbd->red	= lrgbs->red;
				lrgbd->grn	= lrgbs->grn;
				lrgbd->blu	= lrgbs->blu;
			}

			// Move to next color item
			++lrgbs;
			++lrgbd;
		}
	}
}

// Refer to rainbow*.png and strip*.png for position information
void iCreateButtons (s8* button1, s8* command1,
                     s8* button2, s8* command2,
                     s8* button3, s8* command3,
                     s8* button4, s8* command4,
                     s8* button5, s8* command5,
                     s8* button6, s8* command6,
                     s8* strip1, s8* scommand1,
                     s8* strip2, s8* scommand2)
{
	// Create rainbow buttons
	iCreateButton (gsPngRainbowButton1,	button1,	gsPngRainbow1,	gsPngRainbow2,	gsPngRainbow3,	gsPngRainbow4,	  0,  480,	  0, 1, 80, 80, RGB (255, 255, 255),	RGB (255, 0, 0));			// Build the rainbow 1 button, red
	iCreateButton (gsPngRainbowButton2,	button2,	gsPngRainbow1,	gsPngRainbow2,	gsPngRainbow3,	gsPngRainbow4,	  0,  480,	 80, 1, 80, 80, RGB (0, 0, 0),			RGB (255, 192, 128));		// Build the rainbow 2 button, orange
	iCreateButton (gsPngRainbowButton3,	button3,	gsPngRainbow1,	gsPngRainbow2,	gsPngRainbow3,	gsPngRainbow4,	  0,  480,	160, 1, 80, 80, RGB (0, 0, 0),			RGB (255, 255, 0));			// Build the rainbow 3 button, yellow
	iCreateButton (gsPngRainbowButton4,	button4,	gsPngRainbow1,	gsPngRainbow2,	gsPngRainbow3,	gsPngRainbow4,	  0,  480,	240, 1, 80, 80, RGB (0, 0, 0),			RGB (0, 255, 0));			// Build the rainbow 4 button, green
	iCreateButton (gsPngRainbowButton5,	button5,	gsPngRainbow1,	gsPngRainbow2,	gsPngRainbow3,	gsPngRainbow4,	  0,  480,	320, 1, 80, 80, RGB (255, 255, 255),	RGB (0, 0, 255));			// Build the rainbow 5 button, blue
	iCreateButton (gsPngRainbowButton6,	button6,	gsPngRainbow1,	gsPngRainbow2,	gsPngRainbow3,	gsPngRainbow4,	  0,  480,	400, 1, 80, 80, RGB (255, 255, 255),	RGB (148, 64, 192));		// Build the rainbow 6 button, violet

	gsPngRainbowButton1.buttonCommand	= command1;
	gsPngRainbowButton2.buttonCommand	= command2;
	gsPngRainbowButton3.buttonCommand	= command3;
	gsPngRainbowButton4.buttonCommand	= command4;
	gsPngRainbowButton5.buttonCommand	= command5;
	gsPngRainbowButton6.buttonCommand	= command6;

	// Create strip buttons
	iCreateButton (gsPngStripButton1,	strip1,		gsPngStrip1,	gsPngStrip2,	gsPngStrip3,	gsPngStrip4,	400,  694,	 0,  0, 80, 80, RGB (0, 0, 0),			RGB (0, 255, 255));			// Build the strip 1 button, cyan
	iCreateButton (gsPngStripButton2,	strip2,		gsPngStrip1,	gsPngStrip2,	gsPngStrip3,	gsPngStrip4,	400,  694,	 0, 80, 80, 80, RGB (255, 255, 255),	RGB (0, 0, 128));			// Build the strip 2 button, indigo

	gsPngStripButton1.buttonCommand		= scommand1;
	gsPngStripButton2.buttonCommand		= scommand2;
}

void iCreateButton (SPNG& spng, s8* text, SPNG& spng1, SPNG& spng2, SPNG& spng3, SPNG& spng4, u32 xOffset, u32 yOffset, u32 x, u32 y, u32 width, u32 height, u32 foreground, u32 background)
{
	bool lbDrawText;

	spng.info = (png_infop) malloc (sizeof (png_info));

	if (spng.info)
	{
		// Store the dimenions
		spng.info->width	= width;
		spng.info->height	= height;

		// Extract the images from the three templates
		iExtractRectangle (&spng.img1, spng1, x, y, width, height);												// Image is extracted from each template
		iExtractRectangle (&spng.img2, spng2, x, y, width, height);												// Image is extracted from each template
		iExtractRectangle (&spng.img3, spng3, x, y, width, height);												// Image is extracted from each template
		iExtractRectangle (&spng.img4, spng4, x, y, width, height);												// Image is extracted from each template

		// Use generic text for now, will load the graphics templates in future versions
		lbDrawText = true;

		if (text[0] == '$')
		{
			// They have specified an internal image/macro to overlay, rather than literal text
			if (strncasecmp (text + 1, "first", 5) == 0)
			{
				// They are specifying the "first" image
				lbDrawText = false;
				iOverlayImgToImgCenter (spng, spng.img1, gsPngFirst, gsPngFirst.img1, 0, 0, false, false);
				iOverlayImgToImgCenter (spng, spng.img2, gsPngFirst, gsPngFirst.img1, 0, 0, false, true);
				iOverlayImgToImgCenter (spng, spng.img4, gsPngFirst, gsPngFirst.img1, 0, 0, false, false);

			}

			else if (strncasecmp (text + 1, "prev", 4) == 0)
			{
				// They are specifying the "prev" image
				lbDrawText = false;
				iOverlayImgToImgCenter (spng, spng.img1, gsPngPrev, gsPngPrev.img1, 0, 0, false, false);
				iOverlayImgToImgCenter (spng, spng.img2, gsPngPrev, gsPngPrev.img1, 0, 0, false, true);
				iOverlayImgToImgCenter (spng, spng.img4, gsPngPrev, gsPngPrev.img1, 0, 0, false, false);

			}

			else if (strncasecmp (text + 1, "next", 4) == 0)
			{
				// They are specifying the "next" image
				lbDrawText = false;
				iOverlayImgToImgCenter (spng, spng.img1, gsPngNext, gsPngNext.img1, 0, 0, false, false);
				iOverlayImgToImgCenter (spng, spng.img2, gsPngNext, gsPngNext.img1, 0, 0, false, true);
				iOverlayImgToImgCenter (spng, spng.img4, gsPngNext, gsPngNext.img1, 0, 0, false, false);

			}

			else if (strncasecmp (text + 1, "last", 4) == 0)
			{
				// They are specifying the "last" image
				lbDrawText = false;
				iOverlayImgToImgCenter (spng, spng.img1, gsPngLast, gsPngLast.img1, 0, 0, false, false);
				iOverlayImgToImgCenter (spng, spng.img2, gsPngLast, gsPngLast.img1, 0, 0, false, true);
				iOverlayImgToImgCenter (spng, spng.img4, gsPngLast, gsPngLast.img1, 0, 0, false, false);

			}

			else if (strncasecmp (text + 1, "undo", 4) == 0)
			{
				// They are specifying the "undo" image
				lbDrawText = false;
				iOverlayImgToImgCenter (spng, spng.img1, gsPngUndo, gsPngUndo.img1, 0, 0, false, false);
				iOverlayImgToImgCenter (spng, spng.img2, gsPngUndo, gsPngUndo.img1, 0, 0, false, true);
				iOverlayImgToImgCenter (spng, spng.img4, gsPngUndo, gsPngUndo.img1, 0, 0, false, false);

			}

			else if (strncasecmp (text + 1, "redo", 4) == 0)
			{
				// They are specifying the "redo" image
				lbDrawText = false;
				iOverlayImgToImgCenter (spng, spng.img1, gsPngRedo, gsPngRedo.img1, 0, 0, false, false);
				iOverlayImgToImgCenter (spng, spng.img2, gsPngRedo, gsPngRedo.img1, 0, 0, false, true);
				iOverlayImgToImgCenter (spng, spng.img4, gsPngRedo, gsPngRedo.img1, 0, 0, false, false);

			}

			else if (strncasecmp (text + 1, "options", 7) == 0)
			{
				// They are specifying the "options" image
				lbDrawText = false;
				iOverlayImgToImgCenter (spng, spng.img1, gsPngOptions, gsPngOptions.img1, 0, 0, false, false);
				iOverlayImgToImgCenter (spng, spng.img2, gsPngOptions, gsPngOptions.img1, 0, 0, false, true);
				iOverlayImgToImgCenter (spng, spng.img4, gsPngOptions, gsPngOptions.img1, 0, 0, false, false);

			}

			else if (strncasecmp (text + 1, "exit", 4) == 0)
			{
				// They are specifying the "exit" image
				lbDrawText = false;
				iOverlayImgToImgCenter (spng, spng.img1, gsPngExit, gsPngExit.img1, 0, 0, false, false);
				iOverlayImgToImgCenter (spng, spng.img2, gsPngExit, gsPngExit.img1, 0, 0, false, true);
				iOverlayImgToImgCenter (spng, spng.img4, gsPngExit, gsPngExit.img1, 0, 0, false, false);
			}

			//else, it's an unknown, draw the text as it is specified
		}

		if (lbDrawText)
		{
			// Draw whatever text is specified over the button
			iDrawText (spng, spng.img1, text, strlen (text), RGB (255, 255, 255),	background, 1.0, false, false);
			iDrawText (spng, spng.img2, text, strlen (text), RGB (0, 0, 0),			background, 1.0, false, false);
			iDrawText (spng, spng.img3, text, strlen (text), RGB (255, 255, 255),	background, 1.0, false, false);
		}

		spng.buttonImage	= _MOUSE_NEUTRAL;
		spng.ulx			= xOffset + x;
		spng.uly			= yOffset + y;
		spng.lrx			= xOffset + x + width;
		spng.lry			= yOffset + y + height;

		// 25 images are created for animation of this component
		iCreateAnimationFromThreeImages (spng, 25, gsPngRainbow1, spng.img1, gsPngRainbow2, spng.img2, gsPngRainbow3, spng.img3);

	}

	else
	{
		printf ("Unable to create necessary controls.");
		exit (-1);
	}
}

void iExtractRectangle (SRGBA32** rgbd, SPNG& spng, u32 x, u32 y, u32 width, u32 height)
{
	u32			lnx, lny;
	SRGBA32*		lrgbs;
	SRGBA32*		lrgbd;

	// Allocate memory for our output buffer
	*rgbd = (SRGBA32*) malloc (width * height * 4);

	if (*rgbd)
	{
		// Extract the rectangle
		for (lny = 0; lny < height; lny++)
		{
			lrgbs = spng.img1	+ ( (y + lny)	* spng.info->width)		+ x;
			lrgbd = *rgbd		+ (lny			* width);

			for (lnx = 0; lnx < width; lnx++)
			{
				if (lny + y < spng.info->height && lnx + x < spng.info->width)
				{
					lrgbd->alp = lrgbs->alp;
					lrgbd->red = lrgbs->red;
					lrgbd->grn = lrgbs->grn;
					lrgbd->blu = lrgbs->blu;
				}

				++lrgbs;
				++lrgbd;
			}
		}
	}
}

void iCreateAnimationFromThreeImages (SPNG& spngd, u32 frames, SPNG& spng1, SRGBA32* img1, SPNG& spng2, SRGBA32* img2, SPNG& spng3, SRGBA32* img3)
{
	// Not used in version 1.0
}

u32 iLighten (u32 colors, f32 percent)
{
	f32 red, grn, blu;

	blu	= (f32) ( (colors & 0xff0000) >> 16)	* percent;
	grn	= (f32) ( (colors & 0x00ff00) >> 8)		* percent;
	red	= (f32)   (colors & 0x0000ff)			* percent;

	if (blu > 255.0)	blu = 255.0;

	if (grn > 255.0)	grn = 255.0;

	if (red > 255.0)	red = 255.0;

	return ( (u32) ( ( (u32) blu << 16) + ( (u32) grn << 8) + ( (u32) red)));
}

void iDrawText (SPNG& spng, SRGBA32* img, s8* text, u32 length, u32 foreground, u32 background, f32 transparency, bool opaque, bool dither)
{
	u8		ditherValue, thisBitmask, fred, fgrn, fblu, bred, bgrn, bblu;
	s32		x, y, offset, lx, ly, fontWidth, fontHeight;
	f32		alp, malp;
	u8*		lxFontBase;						// Base of the character set for the specified font
	u8*		lxThisBase;						// Base of this character
	SRGBA32*	lrgb;

	ditherValue		= 0x55;					// Binary pattern 01010101

	// Grab background color in RGB
	bblu			= (background & 0xff0000) >> 16;
	bgrn			= (background & 0x00ff00) >> 8;
	bred			= (background & 0x0000ff);
	// Grab foreground color in RGB
	fblu			= (foreground & 0xff0000) >> 16;
	fgrn			= (foreground & 0x00ff00) >> 8;
	fred			= (foreground & 0x0000ff);

	// We only use 8x16 bitmap font
	fontWidth	= 8;
	fontHeight	= 16;
	lxFontBase	= &gcFont8x16[0];

	// Determine offsets into the image for this
	x			= (spng.info->width - (length * 8)) / 2;
	y			= (spng.info->height - 16) / 2;

	// For every character, draw it
	for (offset = 0; offset < (s32) length; offset++)
	{
		// Grab the start of the font data for this character
		lxThisBase = lxFontBase + ( (u32) text[offset] * fontHeight);

		// Draw this character
		for (ly = 0; ly < fontHeight; ly++)
		{
			if (y + ly < (s32) spng.info->height)
			{
				lrgb			= (SRGBA32*) ( (s8*) img + ( (y + ly) * (spng.info->width * 4)) + (x * 4) + (offset * fontWidth * 4));
				thisBitmask		= lxThisBase[ly];

				if (dither)
					thisBitmask &= ditherValue;		// Apply dither mask

				for (lx = 0; lx < fontWidth && x + lx + (offset * fontWidth) < (s32) spng.info->width; lx++)
				{
					alp		= ( (f32) (lrgb->alp) / 255.0) * transparency;
					malp	= 1.0 - alp;

					if (thisBitmask & 0x80)
					{
						// Foreground color (bit is turned on)
						lrgb->red = (u8) ( ( (f32) fred * alp) + ( (f32) lrgb->red * malp));
						lrgb->grn = (u8) ( ( (f32) fgrn * alp) + ( (f32) lrgb->red * malp));
						lrgb->blu = (u8) ( ( (f32) fblu * alp) + ( (f32) lrgb->red * malp));

					}

					else
					{
						// Background color (bit is turned off)
						if (opaque)
						{
							lrgb->red = (u8) ( ( (f32) bred * alp) + ( (f32) lrgb->red * malp));
							lrgb->grn = (u8) ( ( (f32) bgrn * alp) + ( (f32) lrgb->red * malp));
							lrgb->blu = (u8) ( ( (f32) bblu * alp) + ( (f32) lrgb->red * malp));
						}
					}

					// Move over for the next bit
					thisBitmask <<= 1;

					// Move right to next pixel
					++lrgb;
				}

				if (dither)
				{
					// Flip the bits for dithering
					ditherValue = ~ditherValue;
				}
			}
		}
	}
}

void iCopyImgToImg (SPNG& spngd, SRGBA32* rgbd, s32 ulxd, s32 ulyd, s32 width, s32 height, SPNG& spngs, SRGBA32* rgbs, s32 ulxs, s32 ulys, bool repeat, bool inverted)
{
	s32			lnx, lny, count;
	SRGBA32*		lrgbs;
	SRGBA32*		lrgbd;

	count = 0;

	while (count < width)
	{
		for (lny = 0; lny < (s32) spngs.info->height; lny++)
		{
			lrgbs	= (SRGBA32*) ( (s8*) rgbs + ( (ulys + lny) * spngs.info->width * 4) + (ulxs * 4));
			lrgbd	= (SRGBA32*) ( (s8*) rgbd + ( (ulyd + lny) * spngd.info->width * 4) + ( (count + ulxd) * 4));

			for (lnx = 0; count + lnx < width &&
			        ulxd + lnx < (s32) spngd.info->width;
			        lnx++)
			{
				if (ulyd + lny < (s32) spngd.info->height && ulys + lny < (s32) spngs.info->height && ulxs + lnx < (s32) spngs.info->width)
				{
					// Copy the pixels, source to destination
					lrgbd->alp = lrgbs->alp;

					if (inverted)
					{
						// The colors are inverted
						lrgbd->red		= 255 - lrgbs->red;
						lrgbd->grn		= 255 - lrgbs->grn;
						lrgbd->blu		= 255 - lrgbs->blu;

					}

					else
					{
						// Normal colors
						lrgbd->red		= lrgbs->red;
						lrgbd->grn		= lrgbs->grn;
						lrgbd->blu		= lrgbs->blu;
					}

				}

				else
				{
					// Not valid any longer in the source, so fill destination with alpha = 0 and black
					lrgbd->alp		= 0;

					if (inverted)
					{
						// The colors are inverted
						lrgbd->red		= 255;
						lrgbd->grn		= 255;
						lrgbd->blu		= 255;

					}

					else
					{
						// Normal colors
						lrgbd->red		= 0;
						lrgbd->grn		= 0;
						lrgbd->blu		= 0;
					}
				}

				++lrgbs;
				++lrgbd;
			}
		}

		count += spngs.info->width;

		if (!repeat)
			break;	// When we get here, we're done because we're not repeating regardless of whether or not we reached the end
	}

	// When we get here, it's been copied
}

void iOverlayImgToImgCenter (SPNG& spngd, SRGBA32* rgbd, SPNG& spngs, SRGBA32* rgbs, s32 ulxs, s32 ulys, bool repeat, bool inverted)
{
	s32  llxd, llyd, width, height;

	llxd	= (spngd.info->width	- spngs.info->width)	/ 2;
	llyd	= (spngd.info->height	- spngs.info->height)	/ 2;
	width	= spngs.info->width;
	height	= spngs.info->height;

	iOverlayImgToImg (spngd, rgbd, llxd, llyd, width, height, spngs, rgbs, ulxs, ulys, repeat, inverted);
}

void iOverlayImgToImg (SPNG& spngd, SRGBA32* rgbd, s32 ulxd, s32 ulyd, s32 width, s32 height, SPNG& spngs, SRGBA32* rgbs, s32 ulxs, s32 ulys, bool repeat, bool inverted)
{
	s32			lnx, lny, count;
	f32			alp, malp;
	SRGBA32*		lrgbs;
	SRGBA32*		lrgbd;

	count = 0;

	while (count < width)
	{
		for (lny = 0; lny < (s32) spngs.info->height; lny++)
		{
			if (lny + ulyd >= 0)
			{
				lrgbs	= (SRGBA32*) ( (s8*) rgbs + ( (ulys + lny) * spngs.info->width * 4) + (ulxs * 4));
				lrgbd	= (SRGBA32*) ( (s8*) rgbd + ( (ulyd + lny) * spngd.info->width * 4) + ( (count + ulxd) * 4));

				for (lnx = 0; count + lnx < width &&
				        ulxd + lnx < (s32) spngd.info->width;
				        lnx++)
				{
					if (lnx + ulxd >= 0 && ulyd + lny < (s32) spngd.info->height && ulys + lny < (s32) spngs.info->height && ulxs + lnx < (s32) spngs.info->width)
					{
						// Copy the pixels, source to destination
						alp				= (f32) lrgbs->alp / 255.0;
						malp			= 1.0 - alp;
						lrgbd->alp		= (u8) ( ( (f32) lrgbs->alp * alp) + (lrgbd->alp * malp));

						if (inverted)
						{
							// The colors are inverted
							lrgbd->red		= (u8) ( ( (f32) (255 - lrgbs->red) * alp) + (lrgbd->red * malp));
							lrgbd->grn		= (u8) ( ( (f32) (255 - lrgbs->grn) * alp) + (lrgbd->grn * malp));
							lrgbd->blu		= (u8) ( ( (f32) (255 - lrgbs->blu) * alp) + (lrgbd->blu * malp));

						}

						else
						{
							// Normal colors
							lrgbd->red		= (u8) ( ( (f32) lrgbs->red * alp) + (lrgbd->red * malp));
							lrgbd->grn		= (u8) ( ( (f32) lrgbs->grn * alp) + (lrgbd->grn * malp));
							lrgbd->blu		= (u8) ( ( (f32) lrgbs->blu * alp) + (lrgbd->blu * malp));
						}
					}

					++lrgbs;
					++lrgbd;
				}
			}
		}

		count += spngs.info->width;

		if (!repeat)
			break;	// When we get here, we're done because we're not repeating regardless of whether or not we reached the end
	}

	// When we get here, it's been copied
}

void iCopyPngToBmp24 (SPNG& spng, SRGBA32** img, s8* filename)
{
	u32				lny, lnx;
	f32				alp, malp;
	SBitmapHead		bh;		// Bitmap header
	SBitmapInfo		bi;		// Bitmap info
	s8*				bd;		// Bitmap daa
	SRGBA32*		lrgbs;	// PNG data (ARGB source)
	SRGB24*			lrgbd;	// BMP data (RGB destination)
	FILE*			lfh;

	// Build the bitmap info
	bi.size				= sizeof (bi);
	bi.width			= spng.info->width;
	bi.height			= spng.info->height;
	bi.planes			= 1;
	bi.bits				= 24;
	bi.actual_width	= spng.info->width * 3;

	if (bi.actual_width % 4 != 0)
	{
		// Round up to the nearest dword
		bi.actual_width += 4 - (bi.actual_width % 4);
	}

	bi.sizeImage		= bi.height * bi.actual_width;
	bi.xppm				= 3270;
	bi.yppm				= 3270;
	bi.colorsUsed		= 0;
	bi.colorsImportant	= 0;

	// Build the bitmap header
	bh.type			= 0x4d42;
	bh.fileSize		= sizeof (bh) + sizeof (bi) + bi.sizeImage;
	bh.reserved1	= 0;
	bh.reserved2	= 0;
	bh.bitsOffset	= sizeof (bh) + sizeof (bi);

	// Create the output buffer
	bd = (s8*) malloc (bi.sizeImage);

	// Copy the bits from the img source to the bitmap
	for (lny = 0; lny < bi.height; lny++)
	{
		// Grab the offsets for this data row
		//lrgbs		= (SRGBA32*)spng.rows[lny];
		lrgbs		= (SRGBA32*) ( ( (s8*) *img) + (lny * spng.info->width * 4));
		lrgbd		= (SRGB24*) (bd  + ( (bi.height - lny - 1) * bi.actual_width));

		for (lnx = 0; lnx < bi.width; lnx++)
		{
			// Copy this one
			alp				= (f32) lrgbs->alp / 255.0;
			malp			= 1.0 - alp;
			lrgbd->red		= (u8) ( ( (f32) lrgbs->red * alp) + (255.0 * malp));
			lrgbd->grn		= (u8) ( ( (f32) lrgbs->grn * alp) + (255.0 * malp));
			lrgbd->blu		= (u8) ( ( (f32) lrgbs->blu * alp) + (255.0 * malp));

			// Move to next pixel
			++lrgbs;
			++lrgbd;
		}
	}

	// Save it do disk
	bi.compression	= 0;
	lfh = fopen (filename, "wb+");
	if (lfh)
	{
		fwrite (&bh, 1, sizeof (bh), lfh);
		fwrite (&bi, 1, sizeof (bi), lfh);
		fwrite (bd, 1, bi.sizeImage, lfh);
		fclose (lfh);

	}

	else
	{
		printf("Unable to create file %s\n", filename);

	}
	free (bd);
}


void iCopyPngToBmp32 (SPNG& spng, SRGBA32** img, s8* filename)
{
	u32				lny, lnx;
	SBitmapHead		bh;		// Bitmap header
	SBitmapInfo		bi;		// Bitmap info
	s8*				bd;		// Bitmap data
	SBGRA32*		lrgbs;	// PNG data (BGRA source)
	SRGBA32*		lrgbd;	// BMP data (ARGB destination)
	FILE*			lfh;

	// Build the bitmap info
	bi.size				= sizeof (bi);
	bi.width			= spng.info->width;
	bi.height			= spng.info->height;
	bi.planes			= 1;
	bi.bits				= 32;
	bi.sizeImage		= bi.height * bi.width * 4;
	bi.xppm				= 3270;
	bi.yppm				= 3270;
	bi.colorsUsed		= 0;
	bi.colorsImportant	= 0;

	// Build the bitmap header
	bh.type			= 0x4d42;
	bh.fileSize		= sizeof (bh) + sizeof (bi) + bi.sizeImage;
	bh.reserved1	= 0;
	bh.reserved2	= 0;
	bh.bitsOffset	= sizeof (bh) + sizeof (bi);

	// Create the output buffer
	bd = (s8*) malloc (bi.sizeImage);

	// Copy the bits from the img source to the bitmap
	for (lny = 0; lny < bi.height; lny++)
	{
		// Grab the offsets for this data row
		//lrgbs		= (SRGBA32*)spng.rows[lny];
		lrgbs		= (SBGRA32*) ( ( (s8*) *img) + (lny * spng.info->width * 4));
		lrgbd		= (SRGBA32*) (bd  + ( (bi.height - lny - 1) * bi.width * 4));

		for (lnx = 0; lnx < bi.width; lnx++)
		{
			// Copy this one
			lrgbd->alp		= lrgbs->alp;
			lrgbd->red		= lrgbs->red;
			lrgbd->grn		= lrgbs->grn;
			lrgbd->blu		= lrgbs->blu;

			// Move to next pixel
			++lrgbs;
			++lrgbd;
		}
	}

	// Save it do disk
	bi.compression	= 0;
	lfh = fopen (filename, "wb+");
	if (lfh)
	{
		fwrite (&bh, 1, sizeof (bh), lfh);
		fwrite (&bi, 1, sizeof (bi), lfh);
		fwrite (bd, 1, bi.sizeImage, lfh);
		fclose (lfh);

	}

	else
	{
		printf("Unable to create file %s\n", filename);

	}
	free (bd);
}

void createChessWindow (void)
{
	xwm = (XWindow*)malloc(sizeof(XWindow));
	if (initXWindow (xwm, 480, 854, 24, (char*) "Chess36 by Rick C. Hodgin", true))
	{
		printf ("Unable to create X-window for GUI\n");
		exit (-1);
	}

	// Set it so it's not resizeable
	XSizeHints hints;
	hints.flags			= PSize | PMinSize | PMaxSize;
	hints.min_width		= xwm->width;
	hints.max_width		= xwm->width;
	hints.base_width	= xwm->width;
	hints.min_height	= xwm->height;
	hints.max_height	= xwm->height;
	hints.base_height	= xwm->height;
	XSetWMNormalHints (xwm->display, xwm->window, &hints);
	// X-window is created
}

void iDrawChessBoard (void)
{
	u32			row, col;
	SBoard*		saveBoard	= NULL;
	SBoard*		savePieces	= NULL;

	iSwapForPriorBoard (&saveBoard, &savePieces);

	// Update any check values
	iHighlightKingInCheckPiecesOnBoard (pieces, board, _WHITE);
	iHighlightKingInCheckPiecesOnBoard (pieces, board, _BLACK);

	// Draw the board
	for (row = 0; row < 6; row++)
	{
		for (col = 0; col < 6; col++)
		{
			if (row % 2 != 0)
			{
				// Odd rows start with white
				if (col % 2 == 0)
				{
					// Evens are white
					iBitBlt (col * _SQUARE_WIDTH, (5 - row) * _SQUARE_HEIGHT, _SQUARE_WIDTH, _SQUARE_HEIGHT, gsPngWhite, iGetBoardImage (row, col, false));
				}

				else
				{
					iBitBlt (col * _SQUARE_WIDTH, (5 - row) * _SQUARE_HEIGHT, _SQUARE_WIDTH, _SQUARE_HEIGHT, gsPngBlack, iGetBoardImage (row, col, true));
				}

			}

			else
			{
				// Even rows start with black
				if (col % 2 == 0)
				{
					// Evens are black
					iBitBlt (col * _SQUARE_WIDTH, (5 - row) * _SQUARE_HEIGHT, _SQUARE_WIDTH, _SQUARE_HEIGHT, gsPngBlack, iGetBoardImage (row, col, true));
				}

				else
				{
					iBitBlt (col * _SQUARE_WIDTH, (5 - row) * _SQUARE_HEIGHT, _SQUARE_WIDTH, _SQUARE_HEIGHT, gsPngWhite, iGetBoardImage (row, col, false));
				}
			}
		}
	}

	iSwapToCurrentBoard (&saveBoard, &savePieces);
}

void iSwapForPriorBoard (SBoard** saveBoard, SBoard** savePieces)
{
	s32		i, count;
	SUndo*	su;

	if (gsUndoRoot != NULL && gnBoard < 0)
	{
		// We have to go backwards to show a prior board
		// Find the last board
		su = gsUndoRoot;

		while (su->ll.next != NULL)
			su = (SUndo*) su->ll.next;

		// When we get here, we're on the last board
		count = 0;

		for (i = gnBoard + 1; su->ll.prev != NULL && i < 0; i++)
		{
			// Iterate forward until we reach the end of the line, or our board
			su = (SUndo*) su->ll.prev;
			--count;
		}

		// When we get here, su is pointing to the board to display
		if (i != 0)
		{
			// They tried to go too far backwards, so we are just at the beginning
			// Set the gnBoard value to whatever that is
			gnBoard = count;
		}

		// Now, swap the board and pieces out temporarily (for this render only)
		*saveBoard	= NULL;
		*savePieces	= NULL;
		*saveBoard	= (SBoard*) malloc (sizeof (SBoard));

		if (*saveBoard)
		{
			*savePieces	= (SBoard*) malloc (sizeof (SBoard));

			if (*savePieces)
			{
				// We're good, save our current boards for restoration after the render
				memcpy (*saveBoard,	&board,			sizeof (SBoard));
				memcpy (*savePieces,	&pieces,		sizeof (SBoard));
				memcpy (&board,		&su->board,		sizeof (SBoard));
				memcpy (&pieces,		&su->pieces,	sizeof (SBoard));

			}

			else
			{
				free (*saveBoard);
				*saveBoard = NULL;
			}
		}
	}
}

void iSwapToCurrentBoard (SBoard** saveBoard, SBoard** savePieces)
{
	if (*saveBoard != NULL && *savePieces != NULL)
	{
		// Restore the board and pieces
		memcpy (&board,	*saveBoard,		sizeof (SBoard));
		memcpy (&pieces,	*savePieces,	sizeof (SBoard));
		free (*saveBoard);
		free (*savePieces);
		*saveBoard	= NULL;
		*savePieces	= NULL;
	}
}

SRGBA32* iGetBoardImage (u32 row, u32 col, bool isBlack)
{
	u32			style;
	SBoardRow*	br;

	switch (col)
	{
		default:
		case 0:
			br = &board.a;
			break;

		case 1:
			br = &board.b;
			break;

		case 2:
			br = &board.c;
			break;

		case 3:
			br = &board.d;
			break;

		case 4:
			br = &board.e;
			break;

		case 5:
			br = &board.f;
			break;
	}

	switch (row)
	{
		default:
		case 0:
			style  = br->x1;
			break;

		case 1:
			style = br->x2;
			break;

		case 2:
			style = br->x3;
			break;

		case 3:
			style = br->x4;
			break;

		case 4:
			style = br->x5;
			break;

		case 5:
			style = br->x6;
			break;
	}

	if (gnBoard < 0)
	{
		// For prior boards, we always show just the pieces
		if (isBlack)
			return (gsPngBlack.img1);

		else
			return (gsPngWhite.img1);

	}

	else
	{
		switch (style)
		{
			default:
			case _NORMAL:
				if (isBlack)
					return (gsPngBlack.img1);

				else
					return (gsPngWhite.img1);

				break;

			case _LAST_MOVE:
				if (isBlack)
					return (gsPngBlack.img2);

				else
					return (gsPngWhite.img2);

				break;

			case _THREATS1:
				if (isBlack)
					return (gsPngBlack.img3);

				else
					return (gsPngWhite.img3);

				break;

			case _THREATS2:
				if (isBlack)
					return (gsPngBlack.img4);

				else
					return (gsPngWhite.img4);

				break;

			case _CANDIDATE:
				if (isBlack)
					return (gsPngBlack.img5);

				else
					return (gsPngWhite.img5);

				break;

			case _OPPONENT_LAST_MOVE:
				if (isBlack)
					return (gsPngBlack.img6);

				else
					return (gsPngWhite.img6);

				break;
		}
	}
}

void iResetChessBoard (void)
{
	board.a.x1 = _NORMAL;
	board.a.x2 = _NORMAL;
	board.a.x3 = _NORMAL;
	board.a.x4 = _NORMAL;
	board.a.x5 = _NORMAL;
	board.a.x6 = _NORMAL;

	board.b.x1	= _NORMAL;
	board.b.x2 = _NORMAL;
	board.b.x3 = _NORMAL;
	board.b.x4 = _NORMAL;
	board.b.x5 = _NORMAL;
	board.b.x6 = _NORMAL;

	board.c.x1	= _NORMAL;
	board.c.x2 = _NORMAL;
	board.c.x3 = _NORMAL;
	board.c.x4 = _NORMAL;
	board.c.x5 = _NORMAL;
	board.c.x6 = _NORMAL;

	board.d.x1	= _NORMAL;
	board.d.x2 = _NORMAL;
	board.d.x3 = _NORMAL;
	board.d.x4 = _NORMAL;
	board.d.x5 = _NORMAL;
	board.d.x6 = _NORMAL;

	board.e.x1	= _NORMAL;
	board.e.x2 = _NORMAL;
	board.e.x3 = _NORMAL;
	board.e.x4 = _NORMAL;
	board.e.x5 = _NORMAL;
	board.e.x6 = _NORMAL;

	board.f.x1	= _NORMAL;
	board.f.x2 = _NORMAL;
	board.f.x3 = _NORMAL;
	board.f.x4 = _NORMAL;
	board.f.x5 = _NORMAL;
	board.f.x6 = _NORMAL;
}

void iResetChessPositions (SBoard& tpieces)
{
	tpieces.a.x1	= _WHITE_ROOK;
	tpieces.a.x2	= _WHITE_PAWN;
	tpieces.a.x3	= _EMPTY;
	tpieces.a.x4	= _EMPTY;
	tpieces.a.x5	= _BLACK_PAWN;
	tpieces.a.x6	= _BLACK_ROOK;

	tpieces.b.x1	= _WHITE_KNIGHT;
	tpieces.b.x2	= _WHITE_PAWN;
	tpieces.b.x3	= _EMPTY;
	tpieces.b.x4	= _EMPTY;
	tpieces.b.x5	= _BLACK_PAWN;
	tpieces.b.x6	= _BLACK_BISHOP;

	tpieces.c.x1	= _WHITE_QUEEN;
	tpieces.c.x2	= _WHITE_PAWN;
	tpieces.c.x3	= _EMPTY;
	tpieces.c.x4	= _EMPTY;
	tpieces.c.x5	= _BLACK_PAWN;
	tpieces.c.x6	= _BLACK_KING;

	tpieces.d.x1	= _WHITE_KING;
	tpieces.d.x2	= _WHITE_PAWN;
	tpieces.d.x3	= _EMPTY;
	tpieces.d.x4	= _EMPTY;
	tpieces.d.x5	= _BLACK_PAWN;
	tpieces.d.x6	= _BLACK_QUEEN;

	tpieces.e.x1	= _WHITE_BISHOP;
	tpieces.e.x2	= _WHITE_PAWN;
	tpieces.e.x3	= _EMPTY;
	tpieces.e.x4	= _EMPTY;
	tpieces.e.x5	= _BLACK_PAWN;
	tpieces.e.x6	= _BLACK_KNIGHT;

	tpieces.f.x1	= _WHITE_ROOK;
	tpieces.f.x2	= _WHITE_PAWN;
	tpieces.f.x3	= _EMPTY;
	tpieces.f.x4	= _EMPTY;
	tpieces.f.x5	= _BLACK_PAWN;
	tpieces.f.x6	= _BLACK_ROOK;
}

void iDrawPieces (SBoard& tpieces)
{
	bool		checkmate;
	s32			row, col, rowKing, colKing;
	SBoard*		saveBoard	= NULL;
	SBoard*		savePieces	= NULL;

	iSwapForPriorBoard (&saveBoard, &savePieces);

	// See if we're in checkmate
	iFindPiece ( (gnTurnColor == _WHITE) ? _WHITE_KING : _BLACK_KING, &rowKing, &colKing);
	checkmate = isKingInCheckmate (pieces, rowKing, colKing);

	// Draw the board
	for (row = 0; row < 6; row++)
	{
		for (col = 0; col < 6; col++)
		{
			if (!iIsBoardPieceEmpty (tpieces, row, col))
			{
				iBitBltCenter (col * _SQUARE_WIDTH, (5 - row) * _SQUARE_HEIGHT, _SQUARE_WIDTH, _SQUARE_HEIGHT, iGetBoardPieceSPNG (tpieces, row, col), iGetBoardPieceImg (tpieces, row, col, checkmate));
			}
		}
	}

	iSwapToCurrentBoard (&saveBoard, &savePieces);
}

void iDrawMenu (void)
{
	u32 x, y, width, height;

	x		= 0;
	y		= _SQUARE_HEIGHT * 6;
	width	= _SCREEN_WIDTH;
	height	= _SCREEN_HEIGHT - (_SQUARE_HEIGHT * 6);

	// Copy the bottom image
	iFillRectangle (x, y, x + width, y + height, RGBA (0, 0, 0, 0));
	iBitBlt (x, y, width, height, gsPngBottom, gsPngBottom.img1);

	// Overlay any captured pieces
	iOverlayCapturedPieces();

	// Overlay the control buttons
	iOverlayButtons();

//	// Overlay based on the options we're one
//	switch (gnGameState)
//	{
//		case _MAIN_MENU:		// New, Load, Options
//			iDrawMenuMain();
//			break;
//
//		case _OPTIONS_MENU:		// Sound, Volume, Labels, Captures, Moves, Color, Intensity
//			iDrawMenuOptions();
//			break;
//
//		case _GAME_PLAY:		// Undo, Prev, Next, Dangers, Save, Resign, Offer Draw, Submit, Cancel, Mute, End, Next Game, Games
//			iDrawMenuGamePlay();
//			break;
//	}
}

void iOverlayCapturedPieces (void)
{
	u32 i, left, top, count, spacer;

	// Draw the pieces
	spacer	= 0;
	left	= 4;
	top		= _SCREEN_HEIGHT - 4 - ( (gsPngKingSmall.info->height + spacer) * 4) - 14;

	// Do white
	if (!iFindPiece (_WHITE_KING, NULL, NULL))
		iBitBlt (left, top, gsPngKingSmall.info->width, gsPngKingSmall.info->height, gsPngKingSmall, gsPngKingSmall.img1);
	else
		iBitBltTransparent (0.1, left, top, gsPngKingSmall.info->width, gsPngKingSmall.info->height, gsPngKingSmall, gsPngKingSmall.img1);
	left += gsPngKingSmall.info->width + spacer;

	if (!iFindPiece (_WHITE_QUEEN, NULL, NULL))
		iBitBlt (left, top, gsPngQueenSmall.info->width, gsPngQueenSmall.info->height, gsPngQueenSmall, gsPngQueenSmall.img1);
	else
		iBitBltTransparent (0.1, left, top, gsPngQueenSmall.info->width, gsPngQueenSmall.info->height, gsPngQueenSmall, gsPngQueenSmall.img1);
	left += gsPngQueenSmall.info->width + spacer;

	count = iCountPieces (_WHITE_ROOK);
	if (count < 2)
		iBitBlt (left, top, gsPngRookSmall.info->width, gsPngRookSmall.info->height, gsPngRookSmall, gsPngRookSmall.img1);
	else
		iBitBltTransparent (0.1, left, top, gsPngRookSmall.info->width, gsPngRookSmall.info->height, gsPngRookSmall, gsPngRookSmall.img1);
	left += gsPngRookSmall.info->width + spacer;

	if (count < 1)
		iBitBlt (left, top, gsPngRookSmall.info->width, gsPngRookSmall.info->height, gsPngRookSmall, gsPngRookSmall.img1);
	else
		iBitBltTransparent (0.1, left, top, gsPngRookSmall.info->width, gsPngRookSmall.info->height, gsPngRookSmall, gsPngRookSmall.img1);
	left += gsPngRookSmall.info->width + spacer;

	if (!iFindPiece (_WHITE_BISHOP, NULL, NULL))
		iBitBlt (left, top, gsPngBishopSmall.info->width, gsPngBishopSmall.info->height, gsPngBishopSmall, gsPngBishopSmall.img1);
	else
		iBitBltTransparent (0.1, left, top, gsPngBishopSmall.info->width, gsPngBishopSmall.info->height, gsPngBishopSmall, gsPngBishopSmall.img1);
	left += gsPngBishopSmall.info->width + spacer;

	if (!iFindPiece (_WHITE_KNIGHT, NULL, NULL))
		iBitBlt (left, top, gsPngKnightSmall.info->width, gsPngKnightSmall.info->height, gsPngKnightSmall, gsPngKnightSmall.img1);
	else
		iBitBltTransparent (0.1, left, top, gsPngKnightSmall.info->width, gsPngKnightSmall.info->height, gsPngKnightSmall, gsPngKnightSmall.img1);

	left	= 4;
	top		= _SCREEN_HEIGHT - 4 - ( (gsPngKingSmall.info->height + spacer) * 3) - 14;
	count = iCountPieces (_WHITE_PAWN);
	while (count < 6)
	{
		// For every pawn that's captured, draw one
		iBitBlt (left, top, gsPngPawnSmall.info->width, gsPngPawnSmall.info->height, gsPngPawnSmall, gsPngPawnSmall.img1);
		left += gsPngPawnSmall.info->width + spacer;
		++count;
	}

	// Show the remaining pawns
	count = iCountPieces (_WHITE_PAWN);
	for (i = 0; i < count; i++)
	{
		iBitBltTransparent (0.1, left, top, gsPngPawnSmall.info->width, gsPngPawnSmall.info->height, gsPngPawnSmall, gsPngPawnSmall.img1);
		left += gsPngPawnSmall.info->width + spacer;
	}


	// Do black
	left	= 4;
	top		= _SCREEN_HEIGHT - 4 - ( (gsPngKingSmall.info->height + spacer) * 2) - 4;
	if (!iFindPiece (_BLACK_KING, NULL, NULL))
		iBitBlt (left, top, gsPngKingSmall.info->width, gsPngKingSmall.info->height, gsPngKingSmall, gsPngKingSmall.img2);
	else
		iBitBltTransparent (0.1, left, top, gsPngKingSmall.info->width, gsPngKingSmall.info->height, gsPngKingSmall, gsPngKingSmall.img2);

	left += gsPngKingSmall.info->width + spacer;
	if (!iFindPiece (_BLACK_QUEEN, NULL, NULL))
		iBitBlt (left, top, gsPngQueenSmall.info->width, gsPngQueenSmall.info->height, gsPngQueenSmall, gsPngQueenSmall.img2);
	else
		iBitBltTransparent (0.1, left, top, gsPngQueenSmall.info->width, gsPngQueenSmall.info->height, gsPngQueenSmall, gsPngQueenSmall.img2);
	left += gsPngQueenSmall.info->width + spacer;

	count = iCountPieces (_BLACK_ROOK);
	if (count < 2)
		iBitBlt (left, top, gsPngRookSmall.info->width, gsPngRookSmall.info->height, gsPngRookSmall, gsPngRookSmall.img2);
	else
		iBitBltTransparent (0.1, left, top, gsPngRookSmall.info->width, gsPngRookSmall.info->height, gsPngRookSmall, gsPngRookSmall.img2);
	left += gsPngRookSmall.info->width + spacer;

	if (count < 1)
		iBitBlt (left, top, gsPngRookSmall.info->width, gsPngRookSmall.info->height, gsPngRookSmall, gsPngRookSmall.img2);
	else
		iBitBltTransparent (0.1, left, top, gsPngRookSmall.info->width, gsPngRookSmall.info->height, gsPngRookSmall, gsPngRookSmall.img2);
	left += gsPngRookSmall.info->width + spacer;

	if (!iFindPiece (_BLACK_BISHOP, NULL, NULL))
		iBitBlt (left, top, gsPngBishopSmall.info->width, gsPngBishopSmall.info->height, gsPngBishopSmall, gsPngBishopSmall.img2);
	else
		iBitBltTransparent (0.1, left, top, gsPngBishopSmall.info->width, gsPngBishopSmall.info->height, gsPngBishopSmall, gsPngBishopSmall.img2);
	left += gsPngBishopSmall.info->width + spacer;

	if (!iFindPiece (_BLACK_KNIGHT, NULL, NULL))
		iBitBlt (left, top, gsPngKnightSmall.info->width, gsPngKnightSmall.info->height, gsPngKnightSmall, gsPngKnightSmall.img2);
	else
		iBitBltTransparent (0.1, left, top, gsPngKnightSmall.info->width, gsPngKnightSmall.info->height, gsPngKnightSmall, gsPngKnightSmall.img2);

	left	= 4;
	top		= _SCREEN_HEIGHT - 4 - ( (gsPngKingSmall.info->height + spacer) * 1) - 4;
	count = iCountPieces (_BLACK_PAWN);
	while (count < 6)
	{
		// For every pawn that's captured, draw one
		iBitBlt (left, top, gsPngPawnSmall.info->width, gsPngPawnSmall.info->height, gsPngPawnSmall, gsPngPawnSmall.img2);
		left += gsPngPawnSmall.info->width + spacer;
		++count;
	}

	// Show the remaining pawns
	count = iCountPieces (_BLACK_PAWN);
	for (i = 0; i < count; i++)
	{
		iBitBltTransparent (0.1, left, top, gsPngPawnSmall.info->width, gsPngPawnSmall.info->height, gsPngPawnSmall, gsPngPawnSmall.img2);
		left += gsPngPawnSmall.info->width + spacer;
	}
}

void iOverlayButtons (void)
{
	// Draw the rainbow buttons
	iDisplayButton (gsPngRainbowButton1);
	iDisplayButton (gsPngRainbowButton2);
	iDisplayButton (gsPngRainbowButton3);
	iDisplayButton (gsPngRainbowButton4);
	iDisplayButton (gsPngRainbowButton5);
	iDisplayButton (gsPngRainbowButton6);

	// Draw the strip buttons
	iDisplayButton (gsPngStripButton1);
	iDisplayButton (gsPngStripButton2);
}

void iDisplayButton (SPNG& spng)
{
	bool		lbDrawTest;
	SRGBA32*		img;

	if (gnMouseY >= _SQUARE_HEIGHT * 6)
		lbDrawTest = true;
	else
		lbDrawTest = false;

	switch (spng.buttonImage)
	{
		case 1:
			if (!lbDrawTest)
				return;

			img = spng.img1;
			break;

		case 2:
			if (!lbDrawTest)
				return;

			img = spng.img2;
			break;

		case 3:
			if (lbDrawTest)		img = spng.img4;
			else				img = spng.img3;
			break;

		case 4:
			img = spng.img4;
			break;

		case 5:
			img = spng.img5;
			break;

		case 6:
			img = spng.img6;
			break;

		default:
			return;
	}

	iBitBlt (spng.ulx, spng.uly, spng.lrx - spng.ulx, spng.lry - spng.uly, spng, img);
}

bool iFindPiece (u32 piece, s32* row, s32* col)
{
	u32 pieceAt, rowAt, colAt;

	for (rowAt = 0; rowAt < 6; rowAt++)
	{
		for (colAt = 0; colAt < 6; colAt++)
		{
			pieceAt = iGetBoardPiece (pieces, rowAt, colAt);

			if (pieceAt == piece)
			{
				// This is it
				if (row)
					*row = rowAt;

				if (col)
					*col = colAt;

				return (true);
			}
		}
	}

	// If we get here, not found
	return (false);
}

u32 iCountPieces (u32 piece)
{
	u32 pieceAt, rowAt, colAt, count;

	count = 0;

	for (rowAt = 0; rowAt < 6; rowAt++)
	{
		for (colAt = 0; colAt < 6; colAt++)
		{
			pieceAt = iGetBoardPiece (pieces, rowAt, colAt);

			if (pieceAt == piece)
			{
				// This is it
				++count;
			}
		}
	}

	return (count);
}

void iDrawMenuMain (void)
{
}

void iDrawMenuOptions (void)
{
}

void iDrawMenuGamePlay (void)
{
}

u32 iGetBoardPiece (SBoard& tpieces, s32 row, s32 col)
{
	u32			piece;
	SBoardRow*	br;

	switch (col)
	{
		case 0:
			br = &tpieces.a;
			break;

		case 1:
			br = &tpieces.b;
			break;

		case 2:
			br = &tpieces.c;
			break;

		case 3:
			br = &tpieces.d;
			break;

		case 4:
			br = &tpieces.e;
			break;

		case 5:
			br = &tpieces.f;
			break;

		default:
			return (_EMPTY);
	}

	switch (row)
	{
		case 0:
			piece = br->x1;
			break;

		case 1:
			piece = br->x2;
			break;

		case 2:
			piece = br->x3;
			break;

		case 3:
			piece = br->x4;
			break;

		case 4:
			piece = br->x5;
			break;

		case 5:
			piece = br->x6;
			break;

		default:
			return (_EMPTY);
	}

	return (piece);
}

u32 iGetBoardPieceColor (SBoard& tpieces, s32 row, s32 col)
{
	u32			piece;
	SBoardRow*	br;

	switch (col)
	{
		case 0:
			br = &tpieces.a;
			break;

		case 1:
			br = &tpieces.b;
			break;

		case 2:
			br = &tpieces.c;
			break;

		case 3:
			br = &tpieces.d;
			break;

		case 4:
			br = &tpieces.e;
			break;

		case 5:
			br = &tpieces.f;
			break;

		default:
			return (_EMPTY);
	}

	switch (row)
	{
		case 0:
			piece = br->x1;
			break;

		case 1:
			piece = br->x2;
			break;

		case 2:
			piece = br->x3;
			break;

		case 3:
			piece = br->x4;
			break;

		case 4:
			piece = br->x5;
			break;

		case 5:
			piece = br->x6;
			break;

		default:
			return (_EMPTY);
	}

	return (iGetPieceColor (piece));
}

u32 iGetPieceColor (u32 piece)
{
	switch (piece)
	{
		case _BLACK_PAWN:
		case _BLACK_KNIGHT:
		case _BLACK_BISHOP:
		case _BLACK_ROOK:
		case _BLACK_QUEEN:
		case _BLACK_KING:
			return (_BLACK);

		case _WHITE_PAWN:
		case _WHITE_KNIGHT:
		case _WHITE_BISHOP:
		case _WHITE_ROOK:
		case _WHITE_QUEEN:
		case _WHITE_KING:
			return (_WHITE);

		default:
			// There isn't a piece there
			return (_EMPTY);
	}
}

u32 iGetOpponentPieceColor (u32 piece)
{
	// Looking for the opponent's color, not the piece's color
	// Note:  The constants used for this could be tested.
	// Note:  Everything above 10 is black
	switch (piece)
	{
		case _BLACK_PAWN:
		case _BLACK_KNIGHT:
		case _BLACK_BISHOP:
		case _BLACK_ROOK:
		case _BLACK_QUEEN:
		case _BLACK_KING:
			return (_WHITE);

		case _WHITE_PAWN:
		case _WHITE_KNIGHT:
		case _WHITE_BISHOP:
		case _WHITE_ROOK:
		case _WHITE_QUEEN:
		case _WHITE_KING:
			return (_BLACK);

		default:
			// There isn't a piece there
			return (_EMPTY);
	}
}

void iSetBoardPiece (SBoard& tpieces, u32 piece, s32 row, s32 col)
{
	SBoardRow*	br;
	u32*		piecep;

	switch (col)
	{
		case 0:
			br = &tpieces.a;
			break;

		case 1:
			br = &tpieces.b;
			break;

		case 2:
			br = &tpieces.c;
			break;

		case 3:
			br = &tpieces.d;
			break;

		case 4:
			br = &tpieces.e;
			break;

		case 5:
			br = &tpieces.f;
			break;

		default:
			return;
	}

	switch (row)
	{
		case 0:
			piecep = &br->x1;
			break;

		case 1:
			piecep = &br->x2;
			break;

		case 2:
			piecep = &br->x3;
			break;

		case 3:
			piecep = &br->x4;
			break;

		case 4:
			piecep = &br->x5;
			break;

		case 5:
			piecep = &br->x6;
			break;

		default:
			return;
	}

	// Update the piece there
	*piecep = piece;
}

SPNG& iGetBoardPieceSPNG (SBoard& tpieces, s32 row, s32 col)
{
	switch (iGetBoardPiece (tpieces, row, col))
	{
		default:
		case _EMPTY:
			return (gsPngEmpty);
			break;

		case _BLACK_PAWN:
		case _WHITE_PAWN:
			return (gsPngPawn);
			break;

		case _BLACK_KNIGHT:
		case _WHITE_KNIGHT:
			return (gsPngKnight);
			break;

		case _BLACK_BISHOP:
		case _WHITE_BISHOP:
			return (gsPngBishop);
			break;

		case _BLACK_ROOK:
		case _WHITE_ROOK:
			return (gsPngRook);
			break;

		case _BLACK_QUEEN:
		case _WHITE_QUEEN:
			return (gsPngQueen);
			break;

		case _BLACK_KING:
		case _WHITE_KING:
			return (gsPngKing);
			break;
	}
}

SRGBA32* iGetBoardPieceImg (SBoard& tpieces, s32 row, s32 col, bool checkmate)
{
	u32		piece;

	piece = iGetBoardPiece (tpieces, row, col);

	if (checkmate && iGetPieceColor (piece) == gnTurnColor)
	{
		// We are in checkmate, and we're drawing the turn of whose it is that is in checkmate
		switch (piece)
		{
				// Return checkmated color
			default:
			case _EMPTY:
				return (gsPngEmpty.img1);
				break;

			case _BLACK_PAWN:
				return (gsPngPawn.img2);
				break;

			case _WHITE_PAWN:
				return (gsPngPawn.img1);
				break;

			case _BLACK_KNIGHT:
				return (gsPngKnight.img2);
				break;

			case _WHITE_KNIGHT:
				return (gsPngKnight.img1);
				break;

			case _BLACK_BISHOP:
				return (gsPngBishop.img2);
				break;

			case _WHITE_BISHOP:
				return (gsPngBishop.img1);
				break;

			case _BLACK_ROOK:
				return (gsPngRook.img2);
				break;

			case _WHITE_ROOK:
				return (gsPngRook.img1);
				break;

			case _BLACK_QUEEN:
				return (gsPngQueen.img2);
				break;

			case _WHITE_QUEEN:
				return (gsPngQueen.img1);
				break;

			case _BLACK_KING:
				return (gsPngKing.img4);
				break;

			case _WHITE_KING:
				return (gsPngKing.img3);
				break;
		}

	}

	else
	{
		// Just regular piece
		switch (piece)
		{
				// Return normal color
			default:
			case _EMPTY:
				return (gsPngEmpty.img1);
				break;

			case _BLACK_PAWN:
				return (gsPngPawn.img2);
				break;

			case _WHITE_PAWN:
				return (gsPngPawn.img1);
				break;

			case _BLACK_KNIGHT:
				return (gsPngKnight.img2);
				break;

			case _WHITE_KNIGHT:
				return (gsPngKnight.img1);
				break;

			case _BLACK_BISHOP:
				return (gsPngBishop.img2);
				break;

			case _WHITE_BISHOP:
				return (gsPngBishop.img1);
				break;

			case _BLACK_ROOK:
				return (gsPngRook.img2);
				break;

			case _WHITE_ROOK:
				return (gsPngRook.img1);
				break;

			case _BLACK_QUEEN:
				return (gsPngQueen.img2);
				break;

			case _WHITE_QUEEN:
				return (gsPngQueen.img1);
				break;

			case _BLACK_KING:
				return (gsPngKing.img2);
				break;

			case _WHITE_KING:
				return (gsPngKing.img1);
				break;
		}
	}
}

bool iIsBoardPieceEmpty (SBoard& tpieces, s32 row, s32 col)
{
	return (iGetBoardPiece (tpieces, row, col) == _EMPTY);
}

void iSetChessSquare (u32 style, s32 row, s32 col)
{
	SBoardRow*	br;
	u32*		stylep;

	switch (col)
	{
		case 0:
			br = &board.a;
			break;

		case 1:
			br = &board.b;
			break;

		case 2:
			br = &board.c;
			break;

		case 3:
			br = &board.d;
			break;

		case 4:
			br = &board.e;
			break;

		case 5:
			br = &board.f;
			break;

		default:
			return;
	}

	switch (row)
	{
		case 0:
			stylep  = &br->x1;
			break;

		case 1:
			stylep = &br->x2;
			break;

		case 2:
			stylep = &br->x3;
			break;

		case 3:
			stylep = &br->x4;
			break;

		case 4:
			stylep = &br->x5;
			break;

		case 5:
			stylep = &br->x6;
			break;

		default:
			return;
	}

	*stylep = style;
}

u32 iGetChessSquare (s32 row, s32 col)
{
	SBoardRow*	br;
	u32*		stylep;

	switch (col)
	{
		case 0:
			br = &board.a;
			break;

		case 1:
			br = &board.b;
			break;

		case 2:
			br = &board.c;
			break;

		case 3:
			br = &board.d;
			break;

		case 4:
			br = &board.e;
			break;

		case 5:
			br = &board.f;
			break;

		default:
			return (_ERROR);
	}

	switch (row)
	{
		case 0:
			stylep  = &br->x1;
			break;

		case 1:
			stylep = &br->x2;
			break;

		case 2:
			stylep = &br->x3;
			break;

		case 3:
			stylep = &br->x4;
			break;

		case 4:
			stylep = &br->x5;
			break;

		case 5:
			stylep = &br->x6;
			break;

		default:
			return (_ERROR);
	}

	return (*stylep);
}

void iToggleChessSquare (s32 row, s32 col)
{
	SBoardRow*	br;
	u32*		stylep;

	switch (col)
	{
		case 0:
			br = &board.a;
			break;

		case 1:
			br = &board.b;
			break;

		case 2:
			br = &board.c;
			break;

		case 3:
			br = &board.d;
			break;

		case 4:
			br = &board.e;
			break;

		case 5:
			br = &board.f;
			break;

		default:
			return;
	}

	switch (row)
	{
		case 0:
			stylep  = &br->x1;
			break;

		case 1:
			stylep = &br->x2;
			break;

		case 2:
			stylep = &br->x3;
			break;

		case 3:
			stylep = &br->x4;
			break;

		case 4:
			stylep = &br->x5;
			break;

		case 5:
			stylep = &br->x6;
			break;

		default:
			return;
	}

	*stylep += 1;

	if (*stylep > _OPPONENT_LAST_MOVE)
		*stylep = _NORMAL;
}

void iBitBltCenter (u32 x, u32 y, u32 width, u32 height, SPNG& spng, SRGBA32* img)
{
	u32 xoffset, yoffset;

	if (spng.info->width < width)
	{
		// Center it
		xoffset = (width - spng.info->width) / 2;
	}

	else
	{
		// Always left-justify it
		xoffset = 0;
	}

	if (spng.info->height < height)
	{
		// Center it
		yoffset = (height - spng.info->height) / 2;
	}

	else
	{
		// Always top-justify it
		yoffset = 0;
	}

	iBitBlt (x + xoffset, y + yoffset, width, height, spng, img);
}

void iBitBlt (u32 x, u32 y, u32 width, u32 height, SPNG& spng, SRGBA32* img)
{
	iBitBltTransparent (1.0, x, y, width, height, spng, img);
}

void iBitBltTransparent (f32 transparency, u32 x, u32 y, u32 width, u32 height, SPNG& spng, SRGBA32* img)
{
	u32 lnx, lny;
	f32 sred, sgrn, sblu, alp, malp, dred, dgrn, dblu;
	SRGBA32* lrgbs;
	SBGRA32* lrgbd;

	for (lny = 0; lny < height; lny++)
	{
		if (lny < spng.info->height)
		{
			lrgbd	= (SBGRA32*) (xwm->virtualscreen + ( (y + lny) * xwm->width * 4) + (x * 4));
			lrgbs	= (SRGBA32*) ( (s8*) img + (lny * spng.info->width * 4));

			for (lnx = 0; lnx < width; lnx++)
			{
				if (lnx < spng.info->width)
				{
					alp		= (f32) (lrgbs->alp / 255.0) * transparency;
					sred	= (f32) lrgbs->red;
					sgrn	= (f32) lrgbs->grn;
					sblu	= (f32) lrgbs->blu;
					malp	= 1.0 - alp;

					dred	= (f32) lrgbd->red;
					dgrn	= (f32) lrgbd->grn;
					dblu	= (f32) lrgbd->blu;

					if (alp != 0.0)
					{
						// This pixel has some influence on the underlying pixel
						if (alp != 1.0)
						{
							// Overlay by alpha
							lrgbd->red	= (u8) ( (dred * malp) + (sred * alp));
							lrgbd->grn	= (u8) ( (dgrn * malp) + (sgrn * alp));
							lrgbd->blu	= (u8) ( (dblu * malp) + (sblu * alp));

						}

						else
						{
							// It's fully opaque
							lrgbd->red	= (u8) sred;
							lrgbd->grn	= (u8) sgrn;
							lrgbd->blu	= (u8) sblu;
						}
					}
				}

				++lrgbd;
				++lrgbs;
			}
		}
	}
}

void iRectangle (u32 ulx, u32 uly, u32 lrx, u32 lry, u32 color)
{
	u8			red, grn, blu;
	u32			lny, lnx, width, height;
	SRGBA32*		lrgb;

	red	= (color & 0x0000ff);
	grn	= ( (color & 0x00ff00) >> 8);
	blu	= ( (color & 0xff0000) >> 16);

	width	= lrx - ulx;
	height	= lry - uly;

	for (lny = 0; lny < height; lny++)
	{
		lrgb = (SRGBA32*) (xwm->virtualscreen	+ ( (lny + uly) * xwm->width * 4) + (ulx * 4));

		if (lny == 0 || lny == height - 1)
		{
			// Solid line
			for (lnx = 0; lnx < width; lnx++)
			{
				lrgb->red	= red;
				lrgb->grn	= grn;
				lrgb->blu	= blu;
				++lrgb;
			}

		}

		else
		{
			// Just left and right sides
			// Left side
			lrgb->red	= red;
			lrgb->grn	= grn;
			lrgb->blu	= blu;

			lrgb += width;
			lrgb->red	= red;
			lrgb->grn	= grn;
			lrgb->blu	= blu;

		}
	}
}

void iFillRectangle (u32 ulx, u32 uly, u32 lrx, u32 lry, u32 color)
{
	u8			red, grn, blu;
	u32			lny, lnx, width, height;
	SRGBA32*		lrgb;

	red	= (color & 0x0000ff);
	grn	= ( (color & 0x00ff00) >> 8);
	blu	= ( (color & 0xff0000) >> 16);

	width	= lrx - ulx;
	height	= lry - uly;

	for (lny = 0; lny < height; lny++)
	{
		lrgb = (SRGBA32*) (xwm->virtualscreen	+ ( (lny + uly) * xwm->width * 4) + (ulx * 4));

		for (lnx = 0; lnx < width; lnx++)
		{
			lrgb->red	= red;
			lrgb->grn	= grn;
			lrgb->blu	= blu;
			++lrgb;
		}
	}
}

void loadPNG (s8* name, SPNG& spng)
{
	u32		sig;
	FILE*	lfp;

	if ( (lfp = fopen (name, "rb")) == NULL)
		exit (-1);

	spng.png = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!spng.png)
	{
		// An error
		fclose (lfp);
		printf ("Unable to open %s\n", name);
		exit (-1);
	}

	spng.info = png_create_info_struct (spng.png);

	if (!spng.info)
	{
		// An error
		fclose (lfp);
		png_destroy_read_struct (&spng.png, png_infopp_NULL, png_infopp_NULL);
		printf ("Unable to open %s\n", name);
		exit (-1);
	}

	png_init_io	(spng.png, lfp);
	sig = 0;
	png_set_sig_bytes	(spng.png, sig);
	png_read_png		(spng.png, spng.info, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, png_voidp_NULL);
	fclose (lfp);

	// Grab the array of rows for the PNG
	spng.rows = png_get_rows (spng.png, spng.info);
}

//////////
//
// In order to be a valid move:
//
//		1) Piece has to be the right color
//		2) The piece must have a valid move
//		3) Moving the piece has to not put the king in check
//
/////
bool iMoveIfValid (SBoard& tpieces, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo, bool checkKingInCheck)
{
	bool	lbOkayToMove, lbUpdateBoard;
	u32		piece, color;

	piece			= iGetBoardPiece (tpieces, rowFrom, colFrom);
	color			= iGetPieceColor (piece);
	lbOkayToMove	= false;

	if (isItThisPiecesTurn (piece))
	{
		// It is this piece's turn, so we've passed #1
		if (canThisPieceMoveHere (tpieces, piece, rowFrom, colFrom, rowTo, colTo, checkKingInCheck))
		{
			// This piece can move here
			lbOkayToMove		= true;
			lbUpdateBoard		= true;
			iSaveUndo (tpieces, board);

			if (piece == _WHITE_PAWN || piece == _BLACK_PAWN)
			{
				// See if a pawn has reached the other side
				if (color == _WHITE && rowTo == 5)
				{
					// The white pawn has reached the other side
					piece = _WHITE_QUEEN;	// Auto-promote to queen

				}

				else if (color == _BLACK && rowTo == 0)
				{
					// The black pawn has reached the white side
					piece = _BLACK_QUEEN;	// Auto-promote to queen
				}

			}

			else if (colFrom == colTo && (piece == _WHITE_KING || piece == _BLACK_KING))
			{
				// A king has reached the other side, wherever it moved to, make that square now have a queen
				if (color == _WHITE && rowTo == 5)
				{
					// Bring back a queen
					lbUpdateBoard = false;
					iSetBoardPiece (tpieces,	_WHITE_QUEEN,	rowTo,	colTo);

				}

				else if (color == _BLACK && rowTo == 0)
				{
					// Bring back a queen
					lbUpdateBoard = false;
					iSetBoardPiece (tpieces,	_BLACK_QUEEN,	rowTo,	colTo);
				}
			}

			if (lbUpdateBoard)
			{
				// We only update by moving the piece if it WAS NOT a king reaching the other side
				iSetBoardPiece (tpieces,		_EMPTY,		rowFrom,	colFrom);
				iSetBoardPiece (tpieces,		piece,		rowTo,		colTo);
			}

			iResetChessBoard();
			gnLastRowClicked	= -1;
			gnLastColClicked	= -1;

			// It's now the other side's turn
			gnTurnColor = (gnTurnColor == _WHITE) ? _BLACK : _WHITE;
		}
	}

	// If we get here, it's not valid
	return (lbOkayToMove);
}

bool iHighlightMovesIfPieceClickedIsValidToMove (SBoard& tpieces, s32 rowFrom, s32 colFrom)
{
	u32		piece, toPiece;
	s32		rowTo, colTo;
	bool	lbHighlighted;

	// Reset every color to its _NORMAL state
	iResetChessBoard();

	// Find out what piece is at that position
	piece = iGetBoardPiece (tpieces, rowFrom, colFrom);

	// Make sure it's this piece's color's turn
	lbHighlighted = false;

	if (isItThisPiecesTurn (piece))
	{
		// It is this piece's turn, so highlight all of the valid moves
		for (rowTo = 0; rowTo < 6; rowTo++)
		{
			for (colTo = 0; colTo < 6; colTo ++)
			{
				if (! (rowTo == rowFrom && colTo == colFrom))
				{
					// This is not the piece's position itself, so we see if it can move here
					if (canThisPieceMoveHere (tpieces, piece, rowFrom, colFrom, rowTo, colTo, true))
					{
						// It can move here, highlight it
						toPiece = iGetBoardPiece (tpieces, rowTo, colTo);

						if (toPiece != _EMPTY)
						{
							// If this piece moves here, it will take an opponent's piece
							iSetChessSquare (_CANDIDATE, rowTo, colTo);
							lbHighlighted = true;

						}

						else
						{
							// Just a normal move
							iSetChessSquare (_CANDIDATE, rowTo, colTo);
							lbHighlighted = true;
						}
					}
				}
			}
		}
	}

	if (lbHighlighted)
	{
		// There's at least one position that can be moved to
		// Also highlight the current piece's position
		iSetChessSquare (_CANDIDATE, rowFrom, colFrom);
		lbHighlighted = true;
	}

	// Return the status of whether or not anything was highlighted (meaning there's at least one valid move)
	return (lbHighlighted);
}

bool canThisPieceMoveHere (SBoard& tpieces, u32 piece, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo, bool checkForInCheck)
{
	switch (piece)
	{
			// Pawns can only move forward, unless they can attack sideways, then they can move sideways
		case _WHITE_PAWN:
			return (canPawnMoveHere (tpieces, _WHITE, rowFrom, colFrom, rowTo, colTo, checkForInCheck));

		case _BLACK_PAWN:
			return (canPawnMoveHere (tpieces, _BLACK, rowFrom, colFrom, rowTo, colTo, checkForInCheck));

			// Knights can only move diagonal one, or up/down two and over one, or over one and up/down two
		case _WHITE_KNIGHT:
			return (canKnightMoveHere (tpieces, _WHITE, rowFrom, colFrom, rowTo, colTo, checkForInCheck));

		case _BLACK_KNIGHT:
			return (canKnightMoveHere (tpieces, _BLACK, rowFrom, colFrom, rowTo, colTo, checkForInCheck));

			// Bishops can only move diagonal, or up/down/right/left one square
		case _WHITE_BISHOP:
			return (canBishopMoveHere (tpieces, _WHITE, rowFrom, colFrom, rowTo, colTo, checkForInCheck));

		case _BLACK_BISHOP:
			return (canBishopMoveHere (tpieces, _BLACK, rowFrom, colFrom, rowTo, colTo, checkForInCheck));

			// Rooks can only move up/down/right/left
		case _WHITE_ROOK:
			return (canRookMoveHere (tpieces, _WHITE, rowFrom, colFrom, rowTo, colTo, checkForInCheck));

		case _BLACK_ROOK:
			return (canRookMoveHere (tpieces, _BLACK, rowFrom, colFrom, rowTo, colTo, checkForInCheck));

			// Queens can move anywhere diagonal or up/down/right/left
		case _WHITE_QUEEN:
			return (canQueenMoveHere (tpieces, _WHITE, rowFrom, colFrom, rowTo, colTo, checkForInCheck));

		case _BLACK_QUEEN:
			return (canQueenMoveHere (tpieces, _BLACK, rowFrom, colFrom, rowTo, colTo, checkForInCheck));

			// Kings can only move one square in any direction
		case _WHITE_KING:
			return (canKingMoveHere (tpieces, _WHITE, rowFrom, colFrom, rowTo, colTo));

		case _BLACK_KING:
			return (canKingMoveHere (tpieces, _BLACK, rowFrom, colFrom, rowTo, colTo));

	}

	return (false);
}

// Note:  All right/left references are from the point of view of the piece, as looking from its king to its opponent's king
//        So "right" is always toward their initial bishop side, and "left" is always toward their initial knight side
bool canPawnMoveHere (SBoard& tpieces, u32 colorFrom, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo, bool checkForInCheck)
{
	u32 pieceTo, colorTo, colorToCheck;
	s32 colRight, colLeft;

	colRight	= colFrom + 1;
	colLeft		= colFrom - 1;
	pieceTo		= iGetBoardPiece (tpieces, rowTo, colTo);
	colorTo		= iGetPieceColor (pieceTo);

	if (colorFrom == _WHITE)
	{
		// White pawns can only move one row to a higher numbered one, as they are always moving toward black
		if (rowFrom < 5 && rowTo - rowFrom == 1)
		{
			// A move may be possible, we'll continue checking below
			colorToCheck = _BLACK;

		}

		else
		{
			// A move the distance they're desiring is not possible
			return (false);
		}

	}

	else
	{
		// Black pawns can only move one row to a lower numbered one, as they are always moving toward white
		if (rowFrom > 0 && rowFrom - rowTo == 1)
		{
			// A move may be possible, we'll continue checking below
			colorToCheck = _WHITE;

		}

		else
		{
			// A move the distance they're desiring is not possible
			return (false);
		}
	}

	// Make sure the move is valid
	if (colFrom == colTo)
	{
		// Moving straight ahead in the same column, row to row
		// The piece there MUST be empty
		if (iGetBoardPiece (tpieces, rowTo, colTo) == _EMPTY)
		{
			// It can move there, but only if it won't put the king in check
			if (checkForInCheck)
				return (!willMovingThisPiecePutKingInCheck (tpieces, gnTurnColor, rowFrom, colFrom, rowTo, colTo));

			else
				return (true);

		}

		else
		{
			return (false);	// The piece there is not empty, so it cannot move there
		}

	}

	else
	{
		// It can move to another column
		// It must only be moving one column, and it must be attacking an opponent's piece there
		if (pieceTo != _EMPTY && colorTo == colorToCheck)
		{
			// The pieces are different color, so it can be used
			if (colTo == colRight)
			{
				// They're attacking to their right
				if (checkForInCheck)
					return (!willMovingThisPiecePutKingInCheck (tpieces, gnTurnColor, rowFrom, colFrom, rowTo, colTo));

				else
					return (true);

			}

			else if (colTo == colLeft)
			{
				// They're attacking to their left
				if (checkForInCheck)
					return (!willMovingThisPiecePutKingInCheck (tpieces, gnTurnColor, rowFrom, colFrom, rowTo, colTo));

				else
					return (true);

			}

			else
			{
				// They're trying to move too many squares away
				return (false);
			}

		}

		else
		{
			// They're trying to move to an invalid square
			return (false);
		}
	}

	return (false);
}

//////////
// Due to the 6x6 board and there being only one knight, knights move differently than
// in traditional chess.  If a piece is immediately adjacent (in any of the 8 squares
// around it), then it moves in the traditional way.  If there are no pieces immdiately
// adjacent, then it can only move like a king, one square in any direction.
//
//	If a piece IS immediately adjacent (piece is in z location), moves traditionally (to x):
//											1 = (row + 2, col - 1)
//			. x . x .		. 1 . 2 .		2 = (row + 2, col + 1)
//			x z z z x		8 . . . 3       3 = (row + 1, col + 2)
//			. z N z .		. . N . .       4 = (row - 1, col + 2)
//			x z z z x		7 . . . 4       5 = (row - 2, col + 1)
//			. x . x .		. 6 . 5 .       6 = (row - 2, col - 1)
//							                7 = (row - 1, col - 2)
//							                8 = (row + 1, col - 2)
//
//
//	If no piece is adjacent, moves one square up/down/right/left/diagonal (to x):
//											a = (row + 1, col - 1)
//			. . . . .		. . . . .		b = (row + 1, col + 0)
//			. x x x .		. a b c .       c = (row + 1, col + 1)
//			. x N x .		. h N d .       d = (row + 0, col + 1)
//			. x x x .		. g f e .       e = (row - 1, col + 1)
//			. . . . .		. . . . .       f = (row - 1, col + 0)
//							                g = (row - 1, col - 1)
//							                h = (row + 0, col - 1)
//
bool canKnightMoveHere (SBoard& tpieces, u32 colorFrom, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo, bool checkForInCheck)
{
	bool	lbCheck;
	u32		pieceTo, colorTo, colorOpponent;

	pieceTo			= iGetBoardPiece (tpieces, rowTo, colTo);
	colorTo			= iGetPieceColor (pieceTo);
	colorOpponent	= iGetOpponentPieceColor (pieceTo);

	// See if there is a piece immediately adjacent (can be piece of same color, or opponent's color)
	lbCheck = true;

	if (isAnotherPieceAdjacent (tpieces, rowFrom, colFrom))
	{
		// There is a piece adjacent, so it moves traditionally
		// Check every combination in turn
		if (rowTo == rowFrom + 2 && colTo == colFrom - 1)  	// 1
		{
		}
		else if (rowTo == rowFrom + 2 && colTo == colFrom + 1)  	// 2
		{
		}
		else if (rowTo == rowFrom + 1 && colTo == colFrom + 2)  	// 3
		{
		}
		else if (rowTo == rowFrom - 1 && colTo == colFrom + 2)  	// 4
		{
		}
		else if (rowTo == rowFrom - 2 && colTo == colFrom + 1)  	// 5
		{
		}
		else if (rowTo == rowFrom - 2 && colTo == colFrom - 1)  	// 6
		{
		}
		else if (rowTo == rowFrom - 1 && colTo == colFrom - 2)  	// 7
		{
		}
		else if (rowTo == rowFrom + 1 && colTo == colFrom - 2)  	// 8
		{
		}
		else
		{
			lbCheck = false;
		}

	}

	else
	{
		// No piece is adjacent, so it can only move like a king, one square in any direction
		if (rowTo == rowFrom + 1 && colTo == colFrom - 1)  	// a
		{
		}
		else if (rowTo == rowFrom + 1 && colTo == colFrom + 0)  	// b
		{
		}
		else if (rowTo == rowFrom + 1 && colTo == colFrom + 1)  	// c
		{
		}
		else if (rowTo == rowFrom + 0 && colTo == colFrom + 1)  	// d
		{
		}
		else if (rowTo == rowFrom - 1 && colTo == colFrom + 1)  	// e
		{
		}
		else if (rowTo == rowFrom - 1 && colTo == colFrom + 0)  	// f
		{
		}
		else if (rowTo == rowFrom - 1 && colTo == colFrom - 1)  	// g
		{
		}
		else if (rowTo == rowFrom + 0 && colTo == colFrom - 1)  	// h
		{
		}
		else
		{
			lbCheck = false;
		}

	}

	if (lbCheck)
	{
		// It's a valid move, assuming it's going to move to either an empty spot or an opponent's piece
		if (pieceTo == _EMPTY || colorFrom != colorTo)
		{
			// The destination move is good, but we may need to check the test for the king in check
			if (checkForInCheck)
				return (!willMovingThisPiecePutKingInCheck (tpieces, gnTurnColor, rowFrom, colFrom, rowTo, colTo));

			else
				return (true);
		}
	}

	// If we get here, it is not a valid move
	return (false);
}

bool isAnotherPieceAdjacent (SBoard& tpieces, s32 row, s32 col)
{
	u32		piece1, piece2, piece3;

	// Check row below
	piece1	= iGetBoardPiece (tpieces, row - 1, col - 1);
	piece2	= iGetBoardPiece (tpieces, row - 1, col + 0);
	piece3	= iGetBoardPiece (tpieces, row - 1, col + 1);

	if (piece1 != _EMPTY || piece2 != _EMPTY || piece3 != _EMPTY)
		return (true);

	// Check this row
	piece1	= iGetBoardPiece (tpieces, row, col - 1);
//	piece2	= iGetBoardPiece (tpieces, row, col + 0);	// This is itself, so we don't check it
	piece3	= iGetBoardPiece (tpieces, row, col + 1);

	if (piece1 != _EMPTY || /*piece2 != _EMPTY ||*/ piece3 != _EMPTY)
		return (true);

	// Check the row above
	piece1	= iGetBoardPiece (tpieces, row + 1, col - 1);
	piece2	= iGetBoardPiece (tpieces, row + 1, col + 0);
	piece3	= iGetBoardPiece (tpieces, row + 1, col + 1);

	if (piece1 != _EMPTY || piece2 != _EMPTY || piece3 != _EMPTY)
		return (true);

	// If we get here, no pieces adjacent
	return (false);
}

//////////
// Due to the 6x6 board and there being only one bishop, bishops move differently than
// in traditional chess.  Bishops can move either traditionally, or a single square
// up/down/right/left, to allow it to move from white to black, or black to white.
//
//											a = (analyzed as part of diagonal test)
//											b = (row + 1, col + 0)
//			  . x .  		  . b .         c = (analyzed as part of diagonal test)
//			  x B x  		  h B d         d = (row + 0, col + 1)
//			  . x .  		  . f .         e = (analyzed as part of diagonal test)
//											f = (row - 1, col + 0)
//							                g = (analyzed as part of diagonal test)
//							                h = (row + 0, col - 1)
//
bool canBishopMoveHere (SBoard& tpieces, u32 colorFrom, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo, bool checkForInCheck)
{
	bool	lbCheck, ulValid, urValid, lrValid, llValid;
	u32		pieceFrom, pieceTo, colorTo, colorOpponent, delta;

	pieceFrom		= iGetBoardPiece (tpieces, rowFrom,	colFrom);
	pieceTo			= iGetBoardPiece (tpieces, rowTo,	colTo);
	colorTo			= iGetPieceColor (pieceTo);
	colorOpponent	= iGetOpponentPieceColor (pieceFrom);

	lbCheck = true;

	if (rowTo == rowFrom + 1 && colTo == colFrom + 0)  			// b
	{
	}
	else if (rowTo == rowFrom + 0 && colTo == colFrom + 1)  	// d
	{
	}
	else if (rowTo == rowFrom - 1 && colTo == colFrom + 0)  	// f
	{
	}
	else if (rowTo == rowFrom + 0 && colTo == colFrom - 1)  	// h
	{
	}
	else
	{
		// It may be moving further diagonally than a single square
		ulValid	= true;
		urValid	= true;
		lrValid	= true;
		llValid	= true;

		for (delta = 1; delta < 6; delta++)
		{
			// Iterate for each delta from the specified spot
			if (iTestDiagonalMoves (tpieces, delta, ulValid, urValid, lrValid, llValid, colorOpponent, colorFrom, rowFrom, colFrom, rowTo, colTo, checkForInCheck))
				return (true);
		}

		// IF we get here, we didn't find the square, so it's not valid
		lbCheck = false;
	}

	if (lbCheck)
	{
		// It's a valid move, assuming it's going to move to either an empty spot or an opponent's piece
		if (pieceTo == _EMPTY || colorFrom != colorTo)
		{
			// The destination move is good, but we may need to check the test for the king in check
			return (!willMovingThisPiecePutKingInCheck (tpieces, gnTurnColor, rowFrom, colFrom, rowTo, colTo));
		}
	}

	// If we get here, it is not a valid move
	return (false);
}

// Rooks move in the traditional way
bool canRookMoveHere (SBoard& tpieces, u32 colorFrom, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo, bool checkForInCheck)
{
	bool	lbCheck, upValid, rtValid, dnValid, ltValid;
	u32		pieceFrom, pieceTo, colorTo, colorOpponent, delta;

	pieceFrom		= iGetBoardPiece (tpieces, rowFrom,	colFrom);
	pieceTo			= iGetBoardPiece (tpieces, rowTo,	colTo);
	colorTo			= iGetPieceColor (pieceTo);
	colorOpponent	= iGetOpponentPieceColor (pieceFrom);

	lbCheck = true;

	if (rowTo == rowFrom + 1 && colTo == colFrom + 0)  	// b
	{
	}
	else if (rowTo == rowFrom + 0 && colTo == colFrom + 1)  	// d
	{
	}
	else if (rowTo == rowFrom - 1 && colTo == colFrom + 0)  	// f
	{
	}
	else if (rowTo == rowFrom + 0 && colTo == colFrom - 1)  	// h
	{
	}
	else
	{
		// It may be moving further diagonally than a single square
		upValid	= true;		// path up
		rtValid	= true;		// path right
		dnValid	= true;		// path down
		ltValid	= true;		// path left

		for (delta = 1; delta < 6; delta++)
		{
			// Iterate for each delta from the specified spot
			if (iTestUpDownRightLeftMoves (tpieces, delta, upValid, rtValid, dnValid, ltValid, colorOpponent, colorFrom, rowFrom, colFrom, rowTo, colTo, checkForInCheck))
				return (true);
		}

		// IF we get here, we didn't find the square, so it's not valid
		lbCheck = false;
	}

	if (lbCheck)
	{
		// It's a valid move, assuming it's going to move to either an empty spot or an opponent's piece
		if (pieceTo == _EMPTY || colorFrom != colorTo)
		{
			// The destination move is good, but we may need to check the test for the king in check
			return (!willMovingThisPiecePutKingInCheck (tpieces, gnTurnColor, rowFrom, colFrom, rowTo, colTo));
		}
	}

	// If we get here, it is not a valid move
	return (false);
}

// Queens move in the traditional way
bool canQueenMoveHere (SBoard& tpieces, u32 colorFrom, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo, bool checkForInCheck)
{
	bool	lbCheck, ulValid, urValid, lrValid, llValid, upValid, rtValid, dnValid, ltValid;
	u32		pieceFrom, pieceTo, colorTo, colorOpponent, delta;

	pieceFrom		= iGetBoardPiece (tpieces, rowFrom,	colFrom);
	pieceTo			= iGetBoardPiece (tpieces, rowTo,	colTo);
	colorTo			= iGetPieceColor (pieceTo);
	colorOpponent	= iGetOpponentPieceColor (pieceFrom);

	lbCheck = true;

	if (rowTo == rowFrom + 1 && colTo == colFrom + 0)  	// b
	{
	}
	else if (rowTo == rowFrom + 0 && colTo == colFrom + 1)  	// d
	{
	}
	else if (rowTo == rowFrom - 1 && colTo == colFrom + 0)  	// f
	{
	}
	else if (rowTo == rowFrom + 0 && colTo == colFrom - 1)  	// h
	{
	}
	else
	{
		// It may be moving further diagonally than a single square
		ulValid	= true;		// upper-left path
		urValid	= true;		// upper-right path
		lrValid	= true;		// lower-right path
		llValid	= true;		// lower-left path
		upValid	= true;		// path up
		rtValid	= true;		// path right
		dnValid	= true;		// path down
		ltValid	= true;		// path left

		for (delta = 1; delta < 6; delta++)
		{
			// Iterate for each delta from the specified spot
			if (iTestUpDownRightLeftMoves (tpieces, delta, upValid, rtValid, dnValid, ltValid, colorOpponent, colorFrom, rowFrom, colFrom, rowTo, colTo, checkForInCheck))
				return (true);

			if (iTestDiagonalMoves (tpieces, delta, ulValid, urValid, lrValid, llValid, colorOpponent, colorFrom, rowFrom, colFrom, rowTo, colTo, checkForInCheck))
				return (true);
		}

		// IF we get here, we didn't find the square, so it's not valid
		lbCheck = false;
	}

	if (lbCheck)
	{
		// It's a valid move, assuming it's going to move to either an empty spot or an opponent's piece
		if (pieceTo == _EMPTY || colorFrom != colorTo)
		{
			// The destination move is good, but we may need to check the test for the king in check
			return (!willMovingThisPiecePutKingInCheck (tpieces, gnTurnColor, rowFrom, colFrom, rowTo, colTo));
		}
	}

	// If we get here, it is not a valid move
	return (false);
}

//											a = (row + 1, col - 1)
//											b = (row + 1, col + 0)
//			  x x x  		  a b c         c = (row + 1, col + 1)
//			  x K x  		  h K d         d = (row + 0, col + 1)
//			  x x x  		  g f e         e = (row - 1, col + 1)
//											f = (row - 1, col + 0)
//							                g = (row - 1, col - 1)
//							                h = (row + 0, col - 1)
bool canKingMoveHere (SBoard& tpieces, u32 colorFrom, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo)
{
	bool	lbCheck;
	u32		pieceTo, colorTo, colorOpponent;

	pieceTo			= iGetBoardPiece (tpieces, rowTo, colTo);
	colorTo			= iGetPieceColor (pieceTo);
	colorOpponent	= iGetOpponentPieceColor (pieceTo);

	lbCheck = true;

	if (rowTo == rowFrom + 1 && colTo == colFrom - 1)  	// a
	{
	}
	else if (rowTo == rowFrom + 1 && colTo == colFrom + 0)  	// b
	{
	}
	else if (rowTo == rowFrom + 1 && colTo == colFrom + 1)  	// c
	{
	}
	else if (rowTo == rowFrom + 0 && colTo == colFrom + 1)  	// d
	{
	}
	else if (rowTo == rowFrom - 1 && colTo == colFrom + 1)  	// e
	{
	}
	else if (rowTo == rowFrom - 1 && colTo == colFrom + 0)  	// f
	{
	}
	else if (rowTo == rowFrom - 1 && colTo == colFrom - 1)  	// g
	{
	}
	else if (rowTo == rowFrom + 0 && colTo == colFrom - 1)  	// h
	{
	}
	else
	{
		lbCheck = false;
	}

	if (lbCheck)
	{
		// It's a valid move, assuming it's going to move to either an empty spot or an opponent's piece
		if (pieceTo == _EMPTY || colorFrom != colorTo)
		{
			// The destination move is good, but we may need to check the test for the king in check
			return (!willMovingThisPiecePutKingInCheck (tpieces, gnTurnColor, rowFrom, colFrom, rowTo, colTo));
		}
	}

	// If we get here, it is not a valid move
	return (false);
}

bool iTestUpDownRightLeftMoves (SBoard& tpieces, u32 delta, bool& upValid, bool& rtValid, bool& dnValid, bool& ltValid, u32 colorOpponent, u32 colorFrom, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo, bool checkForInCheck)
{
	bool result;
	u32 rowDelta, colDelta;

	if (upValid)
	{
		// We're still tracing the up path
		rowDelta	= rowFrom + delta;
		colDelta	= colFrom + 0;
		result		= iFarMoveTest (tpieces, upValid, rowDelta, colDelta, colorOpponent, colorFrom, rowFrom, colFrom, rowTo, colTo, checkForInCheck);

		if (result)
			return (true);	// It was found
	}

	if (rtValid)
	{
		// We're still tracing the right path
		rowDelta	= rowFrom + 0;
		colDelta	= colFrom + delta;
		result		= iFarMoveTest (tpieces, rtValid, rowDelta, colDelta, colorOpponent, colorFrom, rowFrom, colFrom, rowTo, colTo, checkForInCheck);

		if (result)
			return (true);	// It was found
	}

	if (dnValid)
	{
		// We're still tracing the down path
		rowDelta	= rowFrom - delta;
		colDelta	= colFrom + 0;
		result		= iFarMoveTest (tpieces, dnValid, rowDelta, colDelta, colorOpponent, colorFrom, rowFrom, colFrom, rowTo, colTo, checkForInCheck);

		if (result)
			return (true);	// It was found
	}

	if (ltValid)
	{
		// We're still tracing the left path
		rowDelta	= rowFrom + 0;
		colDelta	= colFrom - delta;
		result		= iFarMoveTest (tpieces, ltValid, rowDelta, colDelta, colorOpponent, colorFrom, rowFrom, colFrom, rowTo, colTo, checkForInCheck);

		if (result)
			return (true);	// It was found
	}

	return (false);
}

bool iTestDiagonalMoves (SBoard& tpieces, u32 delta, bool& ulValid, bool& urValid, bool& lrValid, bool& llValid, u32 colorOpponent, u32 colorFrom, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo, bool checkForInCheck)
{
	bool result;
	u32 rowDelta, colDelta;

	if (ulValid)
	{
		// We're still tracing the upper-left path
		rowDelta	= rowFrom + delta;
		colDelta	= colFrom - delta;
		result		= iFarMoveTest (tpieces, ulValid, rowDelta, colDelta, colorOpponent, colorFrom, rowFrom, colFrom, rowTo, colTo, checkForInCheck);

		if (result)
			return (true);	// It was found
	}

	if (urValid)
	{
		// We're still tracing the upper-right path
		rowDelta	= rowFrom + delta;
		colDelta	= colFrom + delta;
		result		= iFarMoveTest (tpieces, urValid, rowDelta, colDelta, colorOpponent, colorFrom, rowFrom, colFrom, rowTo, colTo, checkForInCheck);

		if (result)
			return (true);	// It was found
	}

	if (lrValid)
	{
		// We're still tracing the lower-right path
		rowDelta	= rowFrom - delta;
		colDelta	= colFrom + delta;
		result		= iFarMoveTest (tpieces, lrValid, rowDelta, colDelta, colorOpponent, colorFrom, rowFrom, colFrom, rowTo, colTo, checkForInCheck);

		if (result)
			return (true);	// It was found
	}

	if (llValid)
	{
		// We're still tracing the lower-left path
		rowDelta	= rowFrom - delta;
		colDelta	= colFrom - delta;
		result		= iFarMoveTest (tpieces, llValid, rowDelta, colDelta, colorOpponent, colorFrom, rowFrom, colFrom, rowTo, colTo, checkForInCheck);

		if (result)
			return (true);	// It was found
	}

	return (false);
}

bool iFarMoveTest (SBoard& tpieces, bool& variable,
                   s32 rowDelta,	s32 colDelta,		u32 colorOpponent,		u32 colorFrom,
                   s32 rowFrom,		s32 colFrom,
                   s32 rowTo,		s32 colTo,			bool checkForInCheck)
{
	u32 pieceDelta, colorDelta;

	if (isRowAndColValid (rowDelta, colDelta))
	{
		// Still tracing this path
		pieceDelta	= iGetBoardPiece (tpieces, rowDelta, colDelta);
		colorDelta	= iGetPieceColor (pieceDelta);

		if (rowDelta == rowTo && colDelta == colTo)
		{
			// This is the target destination
			if (pieceDelta == _EMPTY)
			{
				// This move is valid
				if (checkForInCheck)
					return (!willMovingThisPiecePutKingInCheck (tpieces, gnTurnColor, rowFrom, colFrom, rowDelta/*rowTo*/, colDelta/*colTo*/));

				else
					return (true);

			}

			else if (colorDelta == colorOpponent)
			{
				// This move is valid (and terminating for this path, as it would capture a piece)
				if (checkForInCheck)
					return (!willMovingThisPiecePutKingInCheck (tpieces, gnTurnColor, rowFrom, colFrom, rowDelta/*rowTo*/, colDelta/*colTo*/));

				else
					return (true);

			}

			else
			{
				// No longer valid down this path
				variable = false;
			}

		}

		else
		{
			// This wasn't the piece they're wanting
			// See if the path is still valid (it is if it's empty)
			if (pieceDelta != _EMPTY)
				variable = false;	// There's something here, which means it terminates the path of the bishop
		}

	}

	else
	{
		// We're done tracing this path
		variable = false;
	}

	return (false);
}

void iCopyBoard (SBoard& dest, SBoard& source)
{
	u32 piece;
	s32 row, col;

	for (row = 0; row < 6; row++)
	{
		for (col = 0; col < 6; col++)
		{
			piece = iGetBoardPiece (source, row, col);
			iSetBoardPiece (dest, piece, row, col);
		}
	}
}

bool willMovingThisPiecePutKingInCheck (SBoard& tpieces, u32 colorKing, s32 rowFrom, s32 colFrom, s32 rowTo, s32 colTo)
{
	s32		rowKing, colKing;
	u32		piece, pieceTo;
	SBoard	candidate;

	// Copy the specified board to our candidate board
	iCopyBoard (candidate, tpieces);

	// Make the specified move on the candidate board
	// Grab the piece they're moving from
	piece	= iGetBoardPiece (candidate,	rowFrom,	colFrom);
	pieceTo	= iGetBoardPiece (candidate,	rowTo,		colTo);

	// Move it to its new location
	iSetBoardPiece (candidate, _EMPTY,	rowFrom,	colFrom);
	iSetBoardPiece (candidate, piece,	rowTo,		colTo);

//////////
// Note:  We don't get the position of the king until after the move
//        is made, because it could be the king that was moved.
//////
	rowKing	= -1;	// Added to keep compiler from complaining
	colKing = -1;	// Added to keep compiler from complaining

	if (iGetKingRowAndCol (candidate, colorKing, rowKing, colKing))
		return (isKingInCheck (candidate, rowKing, colKing));		// Checking our candidate board, which has the move specified

	else
		return (false);
}

bool isKingInCheck (SBoard& tpieces, s32 rowKing, s32 colKing)
{
	s32		row, col;
	u32		piece, color, colorOpponent;

	piece			= iGetBoardPiece (tpieces, rowKing, colKing);
	color			= iGetPieceColor (piece);
	colorOpponent	= iGetOpponentPieceColor (piece);

	// See if moves from the opponent's pieces to this color's king are valid
	// If so, the king will be in check
	for (row = 0; row < 6; row++)
	{
		for (col = 0; col < 6; col++)
		{
			piece	= iGetBoardPiece (tpieces, row, col);
			color	= iGetPieceColor (piece);

			if (color == colorOpponent)
			{
				// This piece is the opponent's color
				if (canThisPieceMoveHere (tpieces, piece, row, col, rowKing, colKing, true))
				{
					// And it can move to where the king is, which will place the king in check
					return (true);
					// Note:  There may be more than one way the king is in check.  We simply
					//        check until we find at least one, and return true or false.  For
					//        the isKingCheckmated()function, it does the count of each possible
					//        check position, and sees if there are any moves which will take it
					//        out of check.  If not, then it's mated.
				}
			}
		}
	}

	// If we get here, there are no valid moves from any of
	// the opponent's pieces to the the current color's king
	// The king WILL NOT be in check
	return (false);
}

void iHighlightKingInCheckPiecesOnBoard (SBoard& tpieces, SBoard& board, u32 color)
{
	bool	lbFoundOne;
	s32		rowFrom, colFrom, rowKing, colKing;
	u32		piece, colorOpponent;

	rowKing			= -1;		// Added to suppress compiler warning
	colKing			= -1;		// Added to suppress compiler warning
	iGetKingRowAndCol (tpieces, color, rowKing, colKing);
	piece			= iGetBoardPiece (tpieces, rowKing, colKing);
	colorOpponent	= iGetOpponentPieceColor (piece);

	// See if moves from the opponent's pieces to this color's king are valid
	// If so, the king will be in check
	lbFoundOne = false;

	for (rowFrom = 0; rowFrom < 6; rowFrom++)
	{
		for (colFrom = 0; colFrom < 6; colFrom++)
		{
			piece	= iGetBoardPiece (tpieces, rowFrom, colFrom);
			color	= iGetPieceColor (piece);

			if (color == colorOpponent)
			{
				// This piece is the opponent's color
				if (canThisPieceMoveHere (tpieces, piece, rowFrom, colFrom, rowKing, colKing, true))
				{
					// And it can move to where the king is, which will place the king in check
					lbFoundOne = true;

					// Update the color if it's not already highlighted using some other color
					if (iGetChessSquare (rowFrom, colFrom) == _NORMAL)
						iSetChessSquare (_KING_IN_CHECK, rowFrom, colFrom);
				}
			}
		}
	}

	if (lbFoundOne)
	{
		// Also highlight the king, to indicate the source of the threats
		if (iGetChessSquare (rowKing, colKing) == _NORMAL)
			iSetChessSquare (_KING_IN_CHECK, rowKing, colKing);
	}
}

bool isKingInCheckmate (SBoard& tpieces, s32 rowKing, s32 colKing)
{
	u32		piece, color, colorKing;
	s32		rowFrom, colFrom, rowTo, colTo;

	// Are we in check?  If not, we can't be in checkmate
	if (!isKingInCheck (tpieces, rowKing, colKing))
		return (false);

	// We are in check, so let's see if moving any piece on the board gets us out of check
	colorKing = iGetBoardPieceColor (tpieces, rowKing, colKing);

	for (rowFrom = 0; rowFrom < 6; rowFrom++)
	{
		for (colFrom = 0; colFrom < 6; colFrom++)
		{
			piece	= iGetBoardPiece (tpieces, rowFrom, colFrom);
			color	= iGetPieceColor (piece);

			if (color == colorKing)
			{
				// It's the right color
				// See if moving this piece anywhere does anything to take the king out of check
				for (rowTo = 0; rowTo < 6; rowTo++)
				{
					for (colTo = 0; colTo < 6; colTo++)
					{
						if (rowTo != rowFrom && colTo != colFrom)
						{
							if (canThisPieceMoveHere (tpieces, piece, rowFrom, colFrom, rowTo, colTo, true))
							{
								// We've found at least one move that will take the king out of check
								return (false);		// King is NOT in checkmate
							}
						}
					}
				}

				// If we get here, moving that piece did nothing to take us out of check
				// Continue trying with other pieces
			}
		}
	}

	// When we get here, there are no pieces that can be moved to take the king out of check
	// Checkmate
	return (true);
}

bool iGetKingRowAndCol (SBoard& tpieces, u32 colorKing, s32& rowKing, s32& colKing)
{
	u32 piece, color;
	s32 row, col;

	for (row = 0; row < 6; row++)
	{
		for (col = 0; col < 6; col++)
		{
			piece	= iGetBoardPiece (tpieces, row, col);
			color	= iGetPieceColor (piece);

			if (color == colorKing)
			{
				// It's the right color
				if (piece == _WHITE_KING || piece == _BLACK_KING)
				{
					// And it's a king
					rowKing = row;
					colKing = col;
					return (true);
				}
			}
		}
	}

	// If we get here, the king wasn't found... this shouldn't happen, but for candidate boards, test boards, etc., it might
	return (false);
}

bool isRowAndColValid (s32 row, s32 col)
{
	if (row < 0 || row > 5)
		return (false);

	if (col < 0 || col > 5)
		return (false);

	return (true);
}

bool isItThisPiecesTurn (u32 piece)
{
	if (gnTurnColor == _WHITE)
	{
		// It's white's turn
		switch (piece)
		{
			case _WHITE_PAWN:
			case _WHITE_KNIGHT:
			case _WHITE_BISHOP:
			case _WHITE_ROOK:
			case _WHITE_QUEEN:
			case _WHITE_KING:
				return (true);
				break;
		}

	}

	else if (gnTurnColor == _BLACK)
	{
		// It's black turn
		switch (piece)
		{
			case _BLACK_PAWN:
			case _BLACK_KNIGHT:
			case _BLACK_BISHOP:
			case _BLACK_ROOK:
			case _BLACK_QUEEN:
			case _BLACK_KING:
				return (true);
				break;
		}

	}

	else
	{
		// Game's over, or hasn't started yet
	}

	return (false);
}

// When an undo is appended, any redos are removed
void iSaveUndo (SBoard& tpieces, SBoard& tboard)
{
	SUndo*	suLast;
	SUndo*	suNew;
	SUndo*	suRedo;
	SUndo**	suUpdate;

	if (gsUndoRoot == NULL)
	{
		// We're saving the first board
		suLast		= NULL;
		suUpdate	= &gsUndoRoot;
	}
	else
	{
		// We're adding to the chain, find the last one
		suLast = gsUndoRoot;

		while (suLast->ll.next != NULL)
			suLast = (SUndo*) suLast->ll.next;

		suUpdate = (SUndo**) (&suLast->ll.next);
	}

	// Create the new buffer
	suNew = (SUndo*) malloc (sizeof (SUndo));

	if (suNew)
	{
		// Update the chain
		*suUpdate			= suNew;
		suNew->ll.next		= NULL;					// This is the last undo item
		suNew->ll.prev		= suLast;				// Save the pointer to the previous one
		suNew->turn			= gnTurnColor;			// Update the turn (whatever turn it is now is updated)
		suNew->lastRow		= gnLastRowClicked;		// Save the last clicked row
		suNew->lastCol		= gnLastColClicked;		// Save the last clicked column

		// Update the pieces and board
		memcpy (&suNew->pieces,	&tpieces,	sizeof (suNew->pieces));
		memcpy (&suNew->board,	&tboard, 	sizeof (suNew->board));

		// Remove any redos that exist
		if (gsRedoRoot != NULL)
		{
			suRedo = gsRedoRoot;

			while (suRedo != NULL)
			{
				// Grab the current record, and grab the pointer to the next one
				suLast = suRedo;
				suRedo = (SUndo*) suLast->ll.next;

				// Release the current record
				free (suLast);
			}

			// Reset the redo entries
			gsRedoRoot = NULL;
		}

	}
	else
	{
		// An error allocating memory
		printf ("Unable to allocate memory for undo\n");
	}
}

void iDoUndo (SBoard& tpieces, SBoard& tboard)
{
	SUndo*	suLast;

	if (gsUndoRoot != NULL)
	{
		// Find the last one
		suLast = gsUndoRoot;

		while (suLast->ll.next != NULL)
			suLast = (SUndo*) suLast->ll.next;

		// Right now, suLast is the last one
		gnTurnColor			= suLast->turn;
		gnLastRowClicked	= suLast->lastRow;
		gnLastColClicked	= suLast->lastCol;

		// Update the pieces and board
		memcpy (&tpieces,	&suLast->pieces,	sizeof (suLast->pieces));
		memcpy (&tboard, 	&suLast->board,		sizeof (suLast->board));

		// Close this undo item, as it's no longer used
		if (suLast->ll.prev == NULL)
		{
			// This was the first one
			gsUndoRoot = NULL;

		}
		else
		{
			// Update the one before this one
			( (SUndo*) (suLast->ll.prev)) ->ll.next = NULL;
		}

		// Move this entry to the head of the redo list
		if (gsRedoRoot == NULL)
		{
			// This is the first redo record
			gsRedoRoot			= suLast;
			suLast->ll.next		= NULL;
			suLast->ll.prev		= NULL;

		}
		else
		{
			// Prepending to the existing redo record chain
			gsRedoRoot->ll.prev	= suLast;			// Current record points to new record
			suLast->ll.next		= gsRedoRoot;		// New record points forward to current record
			suLast->ll.prev		= NULL;				// New record points back to nothing
			gsRedoRoot			= suLast;			// Make the new record the current record
		}
	}
}

void iDoRedo (SBoard& tpieces, SBoard& tboard)
{
	SUndo*	suLast;
	SUndo*	suNextRedo;

	if (gsRedoRoot != NULL)
	{
		// Right now, suLast is the last turn the user made, so move it from the redo pile onto the undo pile
		gnTurnColor			= gsRedoRoot->turn;
		gnLastRowClicked	= gsRedoRoot->lastRow;
		gnLastColClicked	= gsRedoRoot->lastCol;

		// Update the pieces and board
		memcpy (&tpieces,	&gsRedoRoot->pieces,	sizeof (gsRedoRoot->pieces));
		memcpy (&tboard, 	&gsRedoRoot->board,		sizeof (gsRedoRoot->board));

		// Move this move to the undo list
		if (gsUndoRoot == NULL)
		{
			// This is the first undo
			gsUndoRoot	= gsRedoRoot;
			suNextRedo	= (SUndo*) gsRedoRoot->ll.next;

		}
		else
		{
			// We're appending to the chain
			suLast = gsUndoRoot;

			while (suLast->ll.next != NULL)
				suLast = (SUndo*) suLast->ll.next;

			suLast->ll.next		= gsRedoRoot;
			gsRedoRoot->ll.prev	= suLast;
			suNextRedo			= (SUndo*) gsRedoRoot->ll.next;
			gsRedoRoot->ll.next	= NULL;

			if (suNextRedo != NULL)
				suNextRedo->ll.prev	= NULL;
		}

		// Move the redo forward
		gsRedoRoot = suNextRedo;
	}
}

bool iCheckMouseMovement (void)
{
	u32 changed;

	changed	 = iCheckButton (gsPngRainbowButton1);
	changed	|= iCheckButton (gsPngRainbowButton2);
	changed	|= iCheckButton (gsPngRainbowButton3);
	changed	|= iCheckButton (gsPngRainbowButton4);
	changed	|= iCheckButton (gsPngRainbowButton5);
	changed	|= iCheckButton (gsPngRainbowButton6);
	changed	|= iCheckButton (gsPngStripButton1);
	changed	|= iCheckButton (gsPngStripButton2);

	if (changed != _NO_ACTIVITY)
	{
		// Something changed, update it visually
		if ( (changed & _BOARD_ACTIVITY) != 0)
		{
			// Redraw the board
			iDrawChessBoard();
			iDrawPieces (pieces);
		}

		if ( (changed & _MENU_ACTIVITY) != 0)
		{
			// Redraw the menu
			iDrawMenu();
		}

		// Tell X-windows to draw it
		drawContent(xwm);
	}

	return (changed != _NO_ACTIVITY);
}

u32 iCheckButton (SPNG& spng)
{
	u32 activity;

	activity = _NO_ACTIVITY;

	switch (spng.buttonImage)
	{
		case _MOUSE_NEUTRAL:
		case _MOUSE_IN_MENU:

			// We're looking to see if the mouse is over or clicked down on this item
			if (gnMouseX > spng.ulx && gnMouseX <= spng.lrx && gnMouseY > spng.uly && gnMouseY <= spng.lry)
			{
				// The mouse is within this space
				if (gbMouseDown && gbMouseLeft)
				{
					// And they're left-clicking on this item
					spng.buttonImage = _MOUSE_DOWN;
					iQueueCommand ( (s8*) "leftclick", spng.buttonCommand);
					activity = _MOUSE_ACTIVITY + _MENU_ACTIVITY;

				}

				else
				{
					// They're not left-clicking (they may be right-clicking or middle-clicking, but we ignore those)
					spng.buttonImage = _MOUSE_OVER;
					iQueueCommand ( (s8*) "enter", spng.buttonCommand);
					activity = _MOUSE_ACTIVITY + _MENU_ACTIVITY;
				}

			} else if (gnMouseY >= _SQUARE_HEIGHT * 6) {
				// We're in the menu area, so we need to display the _MOUSE_IN_MENU option
				if (spng.buttonImage != _MOUSE_IN_MENU)
				{
					spng.buttonImage = _MOUSE_IN_MENU;
					activity = _MENU_ACTIVITY;
				}

			} else {
				// We're not in the menu area
				if (spng.buttonImage != _MOUSE_NEUTRAL)
				{
					spng.buttonImage = _MOUSE_NEUTRAL;
					activity = _MENU_ACTIVITY;
				}

			}

			// If we get here, it's not in bounds
			break;


		case _MOUSE_OVER:
			if (gnMouseX > spng.ulx && gnMouseX <= spng.lrx && gnMouseY > spng.uly && gnMouseY <= spng.lry)
			{
				// The mouse is still within this space
				if (gbMouseDown && gbMouseLeft)
				{
					// And they're left-clicking on this item
					spng.buttonImage = _MOUSE_DOWN;
					spng.buttonImage = _MOUSE_DOWN;
					iQueueCommand ( (s8*) "leftclick", spng.buttonCommand);
					activity = _MOUSE_ACTIVITY + _MENU_ACTIVITY;
				}

			}

			else
			{
				// They're no longer in bounds (not over the object)
				if (gnMouseY >= _SQUARE_HEIGHT * 6) {
					// We're in the menu area, so we need to display the _MOUSE_IN_MENU option
					if (spng.buttonImage != _MOUSE_IN_MENU)
					{
						spng.buttonImage = _MOUSE_IN_MENU;
						activity = _MENU_ACTIVITY;
					}

				} else {
					// No longer in the square, nor anywhere in the menu area
					if (spng.buttonImage != _MOUSE_NEUTRAL)
					{
						spng.buttonImage = _MOUSE_NEUTRAL;
						iQueueCommand ( (s8*) "leave", spng.buttonCommand);
						activity = _MOUSE_ACTIVITY + _MENU_ACTIVITY;
					}
				}
			}

			break;


		case _MOUSE_DOWN:
			if (gnMouseX > spng.ulx && gnMouseX <= spng.lrx && gnMouseY > spng.uly && gnMouseY <= spng.lry)
			{
				// The mouse is still within this space
				if (! (gbMouseDown && gbMouseLeft))
				{
					// They're no longer left-clicking on this object
					spng.buttonImage = _MOUSE_OVER;
					activity = _MOUSE_ACTIVITY + _MENU_ACTIVITY;
				}

			}
			else
			{
				if (gnMouseY >= _SQUARE_HEIGHT * 6) {
					// We're in the menu area, so we need to display the _MOUSE_IN_MENU option
					if (spng.buttonImage != _MOUSE_IN_MENU)
					{
						spng.buttonImage = _MOUSE_IN_MENU;
						activity = _MENU_ACTIVITY;
					}

				} else {
					// No longer in the square, nor anywhere in the menu area
					// They're no longer in bounds (not over the object)
					if (spng.buttonImage != _MOUSE_NEUTRAL)
					{
						spng.buttonImage = _MOUSE_NEUTRAL;
						iQueueCommand ( (s8*) "leave", spng.buttonCommand);
						activity = _MOUSE_ACTIVITY + _MENU_ACTIVITY;
					}
				}
			}

			break;
	}

	return (activity);
}

void iQueueCommand (s8* type, s8* command)
{
	SCommand*	scLast;
	SCommand*	scNew;
	SCommand**	scUpdate;

	if (gsCommandRoot == NULL)
	{
		// We're saving the first board
		scLast		= NULL;
		scUpdate	= &gsCommandRoot;

	}

	else
	{
		// We're adding to the chain, find the last one
		scLast = gsCommandRoot;

		while (scLast->ll.next != NULL)
			scLast = (SCommand*) scLast->ll.next;

		scUpdate = (SCommand**) (&scLast->ll.next);
	}

	// Create the new buffer
	scNew = (SCommand*) malloc (sizeof (SCommand));

	if (scNew)
	{
		// Update the chain
		*scUpdate			= scNew;
		scNew->ll.next		= NULL;					// This is the last undo item
		scNew->ll.prev		= scLast;				// Save the pointer to the previous one
		scNew->type			= type;
		scNew->command		= command;

	}

	else
	{
		// An error allocating memory
		printf ("Unable to allocate memory for queue command\n");
	}
}

void iExecuteCommands (void)
{
	u32			length;
	SCommand*	sc;
	SCommand*	scLast;

	sc = gsCommandRoot;

	while (sc != NULL)
	{
		// Execute this command
		length = strlen (sc->type);

		if (length == 5 && strncasecmp (sc->type, (s8*) "enter", 5) == 0)
		{
			// enter type
			// Currently, nothing is processed, but in the future animations will be signaled

		}
		else if (length == 5 && strncasecmp (sc->type, (s8*) "leave", 5) == 0)
		{
			// leave type
			// Currently, nothing is processed, but in the future animations will be signaled

		}
		else if (length == 9 && strncasecmp (sc->type, (s8*) "leftclick", 9) == 0)
		{
			// left click type
			// See what they clicked on
			length = strlen (sc->command);

			if (length == 5 && strncasecmp (sc->command, (s8*) "first", 5) == 0)
			{
				// Clicked on the "first" button
				iFirstClicked();

			}
			else if (length == 4)
			{
				if (strncasecmp (sc->command, (s8*) "prev", 4) == 0)
				{
					// Clicked on the "prev" button
					iPrevClicked();
				}

				else if (strncasecmp (sc->command, (s8*) "next", 4) == 0)
				{
					// Clicked on the "next" button
					iNextClicked();
				}

				else if (strncasecmp (sc->command, (s8*) "last", 4) == 0)
				{
					// Clicked on the "last" button
					iLastClicked();
				}

				else if (strncasecmp (sc->command, (s8*) "undo", 4) == 0)
				{
					// Clicked on the "undo" button
					iUndoClicked();
				}

				else if (strncasecmp (sc->command, (s8*) "redo", 4) == 0)
				{
					// Clicked on the "redo" button
					iRedoClicked();
				}

				else if (strncasecmp (sc->command, (s8*) "exit", 4) == 0)
				{
					// Clicked on the "exit" button
					iExitClicked();
				}
			}

			else if (length == 7 && strncasecmp (sc->command, (s8*) "options", 7) == 0)
			{
				// Clicked on the "options" button
				iOptionsClicked();
			}

			else
			{
				// Unknown command
				printf ("Ignoring unknown command: %s\n", sc->command);
			}

		}

		else
		{
			// unknown, ignoring it
			printf ("Ignorning unknown command type: %s\n", sc->type);
		}

		// Move to next item
		scLast	= sc;
		sc		= (SCommand*) sc->ll.next;
		free (scLast);
	}

	// All done
	gsCommandRoot = NULL;
}

void iFirstClicked (void)
{
	gnBoard = -5000;		// Assume a maximum of 5000 moves
	iRefresh();
}

void iPrevClicked (void)
{
	--gnBoard;
	iRefresh();
}

void iNextClicked (void)
{
	++gnBoard;

	if (gnBoard > 0)
		gnBoard = 0;

	iRefresh();
}

void iLastClicked (void)
{
	gnBoard = 0;
	iRefresh();
}

void iUndoClicked (void)
{
	iDoUndo (pieces, board);
	iRefresh();
}

void iRedoClicked (void)
{
	iDoRedo (pieces, board);
	iRefresh();
}

void iOptionsClicked (void)
{
//	k = 5;
}

void iExitClicked (void)
{
	gbProgramIsRunning = false;
}

void iRefresh (void)
{
	iDrawChessBoard();
	iDrawPieces (pieces);
	iDrawMenu();
	drawContent(xwm);
}

void playChessGame (void)
{
	bool		shiftkey, capskey, ctrlkey, altkey, winkey, keydown, lbUpdate;
	u32			piece, color, colorBoard;
	s32			row, col;
	XEvent		ev;
	XKeyEvent*	kev;
	long		xKey;

	signal (SIGHUP, onBreak);
	signal (SIGINT, onBreak);
	signal (SIGQUIT, onBreak);
	signal (SIGTERM, onBreak);

	// Save the initial board as the top-most undo
	iSaveUndo (pieces, board);

	// Begin the game from a new game
	gbProgramIsRunning = true;

	while (gbProgramIsRunning)
	{
		XNextEvent (xwm->display, &ev);

		switch (ev.type)
		{
			case KeyPress:
			case KeyRelease:
				kev		= (XKeyEvent*) &ev;
				xKey	= XLookupKeysym (kev, 0);
				keydown = (ev.type == KeyPress);

				// States for keys already down:
				// 1 shift, 2 caps lock, 4 ctrl, 8 alt, 64 windows
				shiftkey	= kev->state & 1;		// 1 shiftkey
				capskey		= kev->state & 2;		// 2 capskey
				ctrlkey		= kev->state & 4;		// 4 ctrlkey
				altkey		= kev->state & 8;		// 8 altkey
				winkey		= kev->state & 64;		// 64 winkey

				switch (xKey)
				{
					case XK_Escape:
						if (!shiftkey && !ctrlkey && !altkey)
							gbProgramIsRunning = false;

						break;
				}

				clearKeyboardBuffer(xwm);
				break;

			case Expose:
				drawContent(xwm);
				break;

			case ButtonPress:
			case ButtonRelease:
				gbMouseDown = (ev.type == ButtonPress);

				if (ev.xbutton.button == Button1)	gbMouseLeft		= true;
				else								gbMouseLeft		= false;

				if (ev.xbutton.button == Button2)	gbMouseMiddle	= true;
				else								gbMouseMiddle	= false;

				if (ev.xbutton.button == Button3)	gbMouseRight	= true;
				else								gbMouseRight	= false;

				// Find out in where it was clicked
				if (gnMouseY <= _SQUARE_HEIGHT * 6 && gnMouseX <= _SQUARE_WIDTH * 6)
				{
					// It was clicked on the board
					if (gnBoard < 0)
					{
						// Reset to the current board first
						gnBoard		= 0;
						lbUpdate	= true;

					}

					else
					{
						// We can process the event
						if (gbMouseDown && gbMouseLeft)
						{
							// It was a left-click, and it was going down (not releasing)
							row			= ( (_SQUARE_HEIGHT * 6) - gnMouseY) / _SQUARE_HEIGHT;		// White is at bottom, which means row 0 is at bottom
							col			= gnMouseX / _SQUARE_WIDTH;
							piece		= iGetBoardPiece (pieces, row, col);
							color		= iGetPieceColor (piece);
							colorBoard	= iGetChessSquare (row, col);
							lbUpdate	= false;

							if (gnLastRowClicked != -1 && iMoveIfValid (pieces, gnLastRowClicked, gnLastColClicked, row, col, true))
							{
								// The piece has been moved
								lbUpdate = true;

							}

							else
							{
								// See what piece they're clicking on, and highlight it if it's a valid piece to move
								lbUpdate = true;

								if (gnLastRowClicked == row && gnLastColClicked == col)
								{
									// They're turning off the auto-highlighting, as they clicked on the last piece they clicked on
									iResetChessBoard();
									gnLastRowClicked = -1;
									gnLastColClicked = -1;

								}

								else if (iHighlightMovesIfPieceClickedIsValidToMove (pieces, row, col))
								{
									// The piece clicked on has valid moves, so they're now highlighted
									gnLastRowClicked = row;
									gnLastColClicked = col;

								}

								else
								{
									// The highlighted piece has no valid moves
									if (color == gnTurnColor)
									{
										// They clicked on a piece that's theirs, but they cannot move it
										iResetChessBoard();

										// Show that square in red (if it hasn't already previously been shown)
										if (colorBoard != _CANNOT_MOVE)
											iSetChessSquare (_CANNOT_MOVE, row, col);
									}

									gnLastRowClicked = -1;
									gnLastColClicked = -1;
								}
							}
						}

						if (lbUpdate)
							iRefresh();		// The board has been updated in such a way as it needs to be redrawn
					}

				}

				else
				{
					// It was clicked in the bottom area
					if (iCheckMouseMovement())
					{
						// There was some mouse movement
						// See if there are any commands to execute
						iExecuteCommands();
					}
				}

				break;

			case MotionNotify:
				gnMouseX = ev.xmotion.x;
				gnMouseY = ev.xmotion.y;

				if (iCheckMouseMovement())
				{
					// There was some mouse movement
					// See if there are any commands to execute
					iExecuteCommands();
				}

				break;

			case EnterNotify:
			case FocusIn:
				gbFocus		= true;
				break;

			case LeaveNotify:
			case FocusOut:
				gbFocus		= false;

				gnMouseX	= 0;
				gnMouseY	= 0;

				if (iCheckMouseMovement())
				{
					// There was some mouse movement
					// See if there are any commands to execute
					iExecuteCommands();
				}
				break;
		}
	}
}
