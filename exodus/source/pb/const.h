// const.h

typedef unsigned char			u8;
typedef unsigned short			u16;
typedef unsigned long			u32;
typedef char					s8;
typedef short					s16;
typedef long					s32;
typedef float					f32;
typedef double					f64;

// DT/NP/RP file system
#define _BOOTABLE_ENTRY			0x80
#define _EXODUS_INI				0x0
#define _DRIVER					0x1
#define _SPECIAL				0x2
#define _BOOTUP_BIN				0x3
#define _EXODUS_COM				0x4
#define _DT						0xfc
#define _NP						0xfd
#define _RP						0xfe
#define _BOOT_SECTOR			0xff

#define _BOOT_DT_object_type	0
#define _BOOT_DT_days			1
#define _BOOT_DT_seconds		5
#define _BOOT_DT_rp_offset		8
#define _BOOT_DT_entry_type		10
#define _BOOT_DT_np_offset		11

#define _BOOT_RP_length			0
#define _BOOT_RP_requestor		4
#define _BOOT_RP_main			8
// For the original version:
#define _BOOT_RP_start_head		12
#define _BOOT_RP_start_track	13
#define _BOOT_RP_start_sector	14
								// byte 15 is unused
#define _BOOT_RP_end_head		16
#define _BOOT_RP_end_track		17
#define _BOOT_RP_end_sector		18
								// byte 19 is unused
// For the new version:
#define _BOOT_RP_disk_offset	12
#define _BOOT_RP_nuserved		16
