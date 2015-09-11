//////////
//
// pb.c
//
/////
//
// This routine puts the boot programs onto a floppy disk .img disk image file
//
//   boot.bin		- Boot sector loader
//   bootup.bin	  - Exodus Boot Loader
//   exodus.ini	  - Required to indicate what drivers are installed
//   xxxxxxx.drv	 - Any drivers required by exodus
//
// These items are placed in the first DT, NP and RP entries.  They must be sequential on the disk (meaning they start
// at sector 1 (DT) and continue in sector 2 (NP) and 3 (RP), with each variable file physically on the disk beginning at
// sector 4, and continuing until the full extent of the file has been loaded sequentially, one after the other).
//
// The only records that include NP records are the drivers themselves.  BOOT.COM, BOOTUP.COM and EXODUS.INI do not have names
// in the NP because their file types are uniquely identified in the DT structure records.  The other drivers do have names in
// the NP.  All files have entries in the RP, which identify main() and requestor(), along with physical disk offset and length.
//
//




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

#include "pb.h"
int gnSingleStepping = 0;


int main(int argc, char* argv[])
{
	int entry;
	u32 lnDiskOffset;
	
  // Initialize the buffers
	memset(dt_buffer, 0xff, sizeof(dt_buffer));
	memset(np_buffer, 0xff, sizeof(np_buffer));
	memset(rp_buffer, 0xff, sizeof(rp_buffer));
	dt_ptr		= &dt_buffer[0] + setu32(&dt_offset, 2);
	np_ptr		= &np_buffer[0] + setu32(&np_offset, 2);
	rp_ptr		= &rp_buffer[0] + setu32(&rp_offset, 2);

	entry = 0;
	do
	{	// Iterate through every entry
		printf("Loading %c|%s, ", data[entry].type, data[entry].filename);
		iLoadFile(&lnDiskOffset, entry);
		switch (data[entry].type)
		{
			case 'B':
			// It's the boot record (boot.bin)
				// Note: This one is always known to be 512 bytes
				// Note: This one does not have an entry in the DT
				data[entry].dt = _BOOT_SECTOR;
				lnDiskOffset = 2048;
				break;

			case 'L':
			// It's the boot loader (bootup.bin)
				data[entry].dt = _BOOTUP_BIN;
				break;

			case 'S':
			// It's a special loader (special.bin)
				data[entry].dt = _SPECIAL;
				break;

			case 'I':
			// It's exodus.ini
				data[entry].dt = _EXODUS_INI;
				break;

			case 'D':
			// It's a driver
				data[entry].dt = _DRIVER;
				break;

			case 'E':
			// It's EXODUS.COM
				data[entry].dt = _EXODUS_COM;
				break;

			default:
			// Who knows?
				printf("Unrecognized option %c\n", data[entry].type);
				exit(-1);
			
		}
		printf("ok\n");
		++entry;
	} while (data[entry].type != 0);
	
	
  // Write everything to its disk location
	entry = 0;
	do {
		iWriteFloppyFile(entry);
		if (data[entry].dt != _BOOT_SECTOR && data[entry].dt != _EXODUS_INI && data[entry].dt != _BOOTUP_BIN)
		{	// Update DNR
			update_dt(entry);
			update_np(entry);
			update_rp(entry);
		}
		++entry;
	} while (data[entry].type != 0);


  // Now, update the DT/NP/RP
	printf("Writing DT, ");
	iWriteFloppyFile(entry + 1);
	printf("NP, ");
	iWriteFloppyFile(entry + 2);
	printf("RP, ");
	iWriteFloppyFile(entry + 3);
	printf("ok.\n");
	
	// We're good
	printf("Finished successfully\n");
	return(0);
}




void iLoadFile(u32* diskOffset, u32 entry)
{
	u32 lnSize, num;
	FILE* lfh;
	
	lfh = fopen(data[entry].filename, "rb+");
	if (lfh == NULL)
	{
		printf("Unable to open file %s\n", data[entry].filename);
		exit(-1);
	}
	fseek(lfh, 0, SEEK_END);
	lnSize = ftell(lfh);
	fseek(lfh, 0, SEEK_SET);
	data[entry].data = (u8*)malloc(lnSize);
	if (data[entry].data == NULL)
	{
		printf("Unable to allocate %u bytes\n", (unsigned int)lnSize);
		exit(-1);
	}
	num = fread(data[entry].data, 1, lnSize, lfh);
	if (num != lnSize)
	{
		printf("Unable to read %u bytes from %s\n", (unsigned int)lnSize, data[entry].filename);
		exit(-1);
	}
	fclose(lfh);
	data[entry].length		= lnSize;
	data[entry].diskOffset	= *diskOffset;
	if (lnSize % 512 != 0)
		*diskOffset += (lnSize + 511) & 0xfffffe00;
	else
		*diskOffset += data[entry].length;
}




void iWriteFloppyFile(u32 entry)
{
	u32 lnLength, num;


//	if (data[entry].dt == _DT)
//		gfh = fopen("../../run/dt.bin", "wb+");
//	else if (data[entry].dt == _NP)
//		gfh = fopen("../../run/np.bin", "wb+");
//	else if (data[entry].dt == _RP)
//		gfh = fopen("../../run/rp.bin", "wb+");
//	else
		gfh = fopen(floppy_filename, "rb+");
		
	if (!gfh)
	{
		printf("Unable to open %s disk image\n", floppy_filename);
		exit(-1);
	}
//	if (data[entry].dt == _DT)
//		fseek(gfh, 0, SEEK_SET);
//	else if (data[entry].dt == _NP)
//		fseek(gfh, 0, SEEK_SET);
//	else if (data[entry].dt == _RP)
//		fseek(gfh, 0, SEEK_SET);
//	else
		fseek(gfh, data[entry].diskOffset, SEEK_SET);
	
	lnLength	= data[entry].length;
	num			= fwrite(data[entry].data, 1, lnLength, gfh);
	if (num != lnLength)
	{
		printf("Unable to write %u bytes to %s at disk offset %u\n", (unsigned int)lnLength, floppy_filename, (unsigned int)data[entry].diskOffset);
		exit(-1);
	}

	if (data[entry].length % 512 != 0)
	{	// Round up to nearest 512 bytes
		fseek(gfh, data[entry].diskOffset + ((data[entry].length + 511) & 0xfffffe00), SEEK_SET);
		fwrite("", 0, 0, gfh);
	}
	fclose(gfh);
}




// Refer to "BOOT DT STRUCTURE" in ../common/equates.asp for info on these offsets
void update_dt(u32 entry)
{
	*(u8*)	(dt_ptr + _BOOT_DT_object_type)		= _BOOTABLE_ENTRY;
	*(u32*)	(dt_ptr + _BOOT_DT_days)			= 0;
	*(u32*)	(dt_ptr + _BOOT_DT_seconds)			= 0;
	*(u16*)	(dt_ptr + _BOOT_DT_rp_offset)		= (u16)((u32)rp_ptr - (u32)&rp_buffer - 2);
	*(u8*)	(dt_ptr + _BOOT_DT_entry_type)		= (u8)(data[entry].dt << 1 | data[entry].loadAtBoot);
	*(u16*)	(dt_ptr + _BOOT_DT_np_offset)		= (u16)((u32)np_ptr - (u32)&np_buffer - 2);
	dt_ptr += 16;
}




void update_np(u32 entry)
{
	u32 lnLength;
	
	lnLength = strlen(data[entry].np_name);
	*np_ptr = (u8)lnLength;
	memcpy(np_ptr + 1, data[entry].np_name, lnLength + 1);
	np_ptr += lnLength + 1;
}




// Refer to "BOOT RP STRUCTURE" in ../common/equates.asp
void update_rp(u32 entry)
{
	u8 shead, strack, ssector, ehead, etrack, esector;

	*(u32*)	(rp_ptr + _BOOT_RP_length)			= data[entry].length;
	*(u32*)	(rp_ptr + _BOOT_RP_requestor)		= *((u32*)(&data[entry].data) + 0);		// main()		offset is at offset 0
	*(u32*)	(rp_ptr + _BOOT_RP_main)			= *((u32*)(&data[entry].data) + 4);		// requestor()	offset is at offset 4

	// for the original format, the head/track/sector will be used
	iComputeHeadTrackSectors(entry, &shead, &strack, &ssector, &ehead, &etrack, &esector);
    *(u8*)	(rp_ptr + _BOOT_RP_start_head)		= shead;
    *(u8*)	(rp_ptr + _BOOT_RP_start_track)		= strack;
    *(u8*)	(rp_ptr + _BOOT_RP_start_sector)	= ssector;

    *(u8*)	(rp_ptr + _BOOT_RP_end_head)		= ehead;
    *(u8*)	(rp_ptr + _BOOT_RP_end_track)		= etrack;
    *(u8*)	(rp_ptr + _BOOT_RP_end_sector)		= esector;

	// for the new format, the following will be used:
	//*(u32*)	(rp_ptr + _BOOT_RP_disk_offset)		= data[entry].diskOffset;
	//*(u32*)	(rp_ptr + _BOOT_RP_nuserved)		= 0;
	rp_ptr += 20;
}

void iComputeHeadTrackSectors(u32 entry, u8* sheadp, u8* strackp, u8* ssectorp, u8* eheadp, u8* etrackp, u8* esectorp)
{
	iComputeHeadTrackSector(data[entry].diskOffset,								sheadp, strackp, ssectorp);
	iComputeHeadTrackSector(data[entry].diskOffset + data[entry].length + 511,	eheadp, etrackp, esectorp);
}


void iComputeHeadTrackSector(u32 offset, u8* headp, u8* trackp, u8* sectorp)
{
	u8 head, track, sector;
	u32 extent;

	// This is done very mechanically for visualization purposes.
	// There are far faster algorithms for obtaining this information

	sector	= 1;
	head	= 0;
	track	= 0;
	extent	= 0;
	while (extent < offset)
	{
        ++sector;
        extent += 512;
        if (sector > 18)
		{
            sector = 1;
            ++head;
            if (head > 1)
			{
                head = 0;
                ++track;
                if (track > 79)
				{
                  // We're at the end of disk
                  // Force a failure here
                  printf("Attempt to write data beyond end of disk.\n");
				  exit(-1);
                }
            }
        }
	}
	// When we get here, the sector, head and track were selected
	*headp		= head;
	*trackp		= track;
	*sectorp	= sector;
}

u32 setu32(u32* variable, u32 value)
{
	*variable = value;
	return(value);
}
