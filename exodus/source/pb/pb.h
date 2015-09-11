// pb.h
//
// Exodus PutBoot Header Definitions
//


#include "const.h"
#include "defs.h"


// Miscellaneous global variables
u8		dt_buffer[512];
u8		np_buffer[512];
u8		rp_buffer[512];
u32		dt_offset;
u32		np_offset;
u32		rp_offset;
u8*		dt_ptr;
u8*		np_ptr;
u8*		rp_ptr;

FILE*	gfh					= NULL;
s8		floppy_filename[]	= "../../run/floppy.img";


typedef struct SFiles
{
	char		type;
	char		filename[128];
	char		np_name[32];
	u8*			data;
	u32			length;
	u32			diskOffset;
	u8			dt;				// Type of dt entry
	u8			loadAtBoot;		// Should this entry be loaded during boot-time?
} sf;
// Valid type codes:
//		B - Boot sector
//		L - Exodus boot loader
//		S - Special boot loader
//		D - Driver required for load
//		I - Exodus.ini file
//		D - Exodus.drv
sf data[] = {
				{	'B',	"exec/boot.bin",		"boot sector",		0,	0,	0,	0,	1	},		/* This entry must ALWAYS be first */
				{	'L',	"exec/bootup.bin",		"bootup.bin",		0,	0,	0,	0,	1	},
				{	'I',	"exodus.ini",			"exodus.ini",		0,	0,	0,	0,	1	},
				{	'D',	"exec/vga.drv",			"vga.drv",			0,	0,	0,	0,	1	},
				{	'D',	"exec/bios.drv",		"bios.drv",			0,	0,	0,	0,	1	},
				{	'D',	"exec/kbd.drv",			"kbd.drv",			0,	0,	0,	0,	1	},
				{	'D',	"exec/mouseps2.drv",	"mouseps2.drv",		0,	0,	0,	0,	1	},
				{	'D',	"exec/debi.drv",		"debi.drv",			0,	0,	0,	0,	1	},
				{	'D',	"exec/x86.drv",			"x86.drv",			0,	0,	0,	0,	1	},
				{	'D',	"exec/cv.drv",			"cv.drv",			0,	0,	0,	0,	1	},
				{	'D',	"exec/disk.drv",		"disk.drv",			0,	0,	0,	0,	1	},
				{	'D',	"exec/exodus.drv",		"exodus.drv",		0,	0,	0,	0,	1	},
				{	0,		"end of list",			"null",				0,	0,	0,	0,	1	},
			/* entry stops here, so:
			 *	dt = entry + 0;
			 * 	np = entry + 1;
			 * 	rp = entry + 2; */
				{	0,		"DT",					"DT",				dt_buffer, 512, 512 * 1, _DT, 0 },
				{	0,		"NP",					"NP",				np_buffer, 512, 512 * 2, _NP, 0 },
				{	0,		"RP",					"RP",				rp_buffer, 512, 512 * 3, _RP, 0 }
			};
