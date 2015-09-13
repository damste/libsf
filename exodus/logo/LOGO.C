// logo.c - Reads BMP file, converts it to the format used by the Boot Screen in Exodus






#include "stdlib.h"
#include "stdio.h"
#include "io.h"
#include "errno.h"
#include "string.h"
#include "malloc.h"


typedef unsigned short ushort;
typedef unsigned long ulong;
typedef unsigned char uchar;

#define RAMDAC_INDEX_READ   0x3c7
#define RAMDAC_INDEX_WRITE  0x3c8
#define RAMDAC_DATA         0x3c9


///////////////////////
//
// Structure of the first few bytes of a bitmap header
//
//
struct Bitmap_Header {
    ushort  type;
    ulong   size;
    ushort  reserved1;
    ushort  reserved2;
    ulong   bitmap_offset;
};




///////////////////////
//
// Structure of the "information section" of a bitmap header
//
//
struct Bitmap_Info {
    ulong   size;
    ulong   width;
    ulong   height;
    ushort  planes;
    ushort  bit_count;
    ulong   compression;
    ulong   image_size;
    ulong   x_pixels_per_meter;
    ulong   y_pixels_per_meter;
    ulong   colors_used;
    ulong   colors_important;
};




///////////////////////
//
// Structure of the stored palette information
//
//
struct RGB_Quad {
    uchar   blue;
    uchar   green;
    uchar   red;
    uchar   reserved;
};




///////////////////////
//
// Total overall structure of the BMP header
//
//
struct BMP_file {
    struct Bitmap_Header    header;
    struct Bitmap_Info      info;
    struct RGB_Quad         palette[256];
};

struct BMP_file bfile;




///////////////////////
//
// Structure used for converting the provided palette
// in the BMP file into the 0-19 locations required by Exodus
//
//
struct PALETTE_data {
    uchar   flag;
    uchar   original_color;
    uchar   new_color;
};

struct PALETTE_data pcount[256];            // Holds the counts of the palette used
struct RGB_Quad     new_palette[256];       // Holds the new Exodus palette conversion after the fact



///////////////////////
//
// Transfer buffer for reading/writing data from far segments
//
//
char buffer[1024];
char out_file[] = "boot_scr.inc";





///////////////////////
///////////////////////
///////////////////////
//
// START OF PROGRAM
//
//
///////////////////////
///////////////////////
///////////////////////
void main(int argc,char *argv[])
{
    FILE *stream;
    FILE *stream_out;
    ushort i, j, count, numread, size, num_to_write;
    char far *bdata;
    char far *tptr;
    char far *vptr;
    char *tbufptr;
    char c, r, g, b, total_colors;

///////////////////////
//
// See what they did on the command line
//
//
    if (argc != 2) {
        argv[1] = (char *)"boot_scr.bmp";
    }
    if ((stream = fopen(argv[1],"rb")) == NULL) {
        printf("File %s not found\n\n",argv[1]);
        exit;
    }
    if ((stream_out = fopen(out_file,"wb+")) == NULL) {
        printf("File %s could not be created\n\n",out_file);
        exit;
    }
    numread = fread(&bfile.header.type, 1, sizeof(bfile), stream);


///////////////////////
//
// Verify integrity
//
//
    if (bfile.header.type != 0x4d42) {
        printf("File is not a BMP\n");
        exit;
    }
    if (bfile.info.width != 320) {
        printf("File is not 320 pixel wide\n");
        exit;
    }
    if (bfile.info.height != 200) {
        printf("File is not 200 pixels tall\n");
        exit;
    }
    if (bfile.info.planes != 1) {
        printf("Not a 1-plane bitmap\n");
        exit;
    }
    if (bfile.info.bit_count != 8) {
        printf("Not an 8-bit bitmap\n");
        exit;
    }


///////////////////////
//
// Load the file into memory
//
// This portion of the program loads the file into memory.
// It does it in sizeof(buffer) chunks because we're reading
// from near memory into a memory buffer that was allocated
// as a far buffer (because there is most likely not enough
// memory in the 64k chunk this program will be running in).
//
//
    size = (ushort)bfile.info.image_size;
    if ((bdata = (char far *)_fmalloc(size)) == NULL) {
        printf("Unable to allocate %u bytes of data\n",size);
    }
  // Read the file in 1K chunks
    tptr = bdata;
    for (i=0; i<size;) {
        numread = fread((char *)buffer, 1, sizeof(buffer), stream);
        if (numread != sizeof(buffer)) {
            printf("Unable to read data portion of %u bytes at offset %u\n",sizeof(buffer), i);
            exit;
        }
        i += numread;
        tbufptr = (char *)buffer;
        for (j=0; j<numread; j++) {
            *tptr++ = *tbufptr++;
        }
    }


///////////////////////
//
// Enter mode 13h (320x200 with 256 colors)
//
//
    _asm {
        // Enter mode 13h (320x200)
        mov     ax,013h
        int     10h

        // Clear the mode 13h screen
        push    es
        mov     ax,0xa000
        mov     es,ax
        xor     di,di
        xor     al,al
        mov     cx,320*200
        rep     stosb
        pop     es
    }


///////////////////////
//
// Draw the data
//
// This portion of the program draws the bitmap into video
// memory.  It is worth noting that the bitmap is stored
// backwards in the BMP file (for whatever fucking reason!!!)
//
//
    tptr = bdata;
    vptr = (char far *)0xa0000000 + 320*200 - 1;
    for (i=0; i<size;) {
        for (j=320; j>0; j--) {
            *vptr-- = *(tptr+j-1);
        }
        tptr += 320;
        i += 320;
    }


///////////////////////
//
// Update the VGA palette
//
// This portion of the program adjusts the palette registers
// in the VGA so the data on-screen matches what the bitmap
// is saying it should be set to (most likely not the
// default palette)
//
//
    _asm {
        mov     dx,RAMDAC_INDEX_WRITE
        xor     ax,ax
        out     dx,al
    }
    for (i=0; i<256; i++) {
        r = bfile.palette[i].red >> 2;
        g = bfile.palette[i].green >> 2;
        b = bfile.palette[i].blue >> 2;
        _asm {
            mov     dx,RAMDAC_DATA
            mov     al,r        // Red
            out     dx,al
            mov     al,g        // Green
            out     dx,al
            mov     al,b        // Blue
            out     dx,al
        }
    }


///////////////////////
//
// Now, determine how many colors are used
//
// This portion of the program determines how many colors
// are actually being used on-screen at this time.  It does
// this by setting the bytes in a 256-element array to 1 if
// that byte is used, and then counting the number that were
// set.  It is done this way because many colors can be used
// literally thousands of times
//
//

  // Initialize the array
    for (i=0; i<256; i++) {
        pcount[j].flag = 0;
        pcount[j].original_color = 0;
        pcount[j].new_color = 0;
    }

  // Based on actual colors used, populate the array
    vptr = (char far *)0xa0000000;
    for (i=0; i<320*200; i++) {
        j = ((ushort)*vptr++) & 0xff;
        pcount[j].flag = 1;
        pcount[j].original_color = i & 0xff;
    }

  // Count the number of colors used
    j = 0;
    for (i=0; i<256; i++) {
        if (pcount[i].flag != 0) {
            ++j;
        }
    }
    if (j > 20) {
        _asm {
            mov     ax,03h
            int     10h
        }
        printf("More than 20 colors are in use!\n");
        exit;
    }
    total_colors = j & 0xff;
    // We're good to go

  // Adjust the palette down
    j = 0;
    for (i=0; i<256; i++) {
        if (pcount[i].flag != 0) {
            pcount[i].new_color = j;
            ++j;
        }
    }


///////////////////////
//
// Now, modify the palette to match the new formation
//
// This portion of the program adjusts the palette to the new
// locations somewhere between 0 and 19 (inclusive)
//
//
    for (i=0; i<256; i++) {
        if (pcount[i].flag!= 0) {
            j = pcount[i].new_color & 0xff;
            new_palette[j].red   = bfile.palette[i].red >> 2;
            new_palette[j].green = bfile.palette[i].green >> 2;
            new_palette[j].blue  = bfile.palette[i].blue >> 2;
        }
    }
    // Finish initializing the rest of the palette to 0,0,0
    for (++j; j<256; j++) {
        new_palette[j].red   = 0;
        new_palette[j].green = 0;
        new_palette[j].blue  = 0;
    }


///////////////////////
//
// Now, reset the palette
//
// This portion of the program resets the palette in the VGA palette
// registers so the data appears correctly on the screen
//
//
    _asm {
        mov     dx,RAMDAC_INDEX_WRITE
        xor     ax,ax
        out     dx,al
    }
    for (i=0; i<256; i++) {
        r = new_palette[i].red;
        g = new_palette[i].green;
        b = new_palette[i].blue;
        _asm {
            mov     dx,RAMDAC_DATA
            mov     al,r        // Red
            out     dx,al
            mov     al,g        // Green
            out     dx,al
            mov     al,b        // Blue
            out     dx,al
        }
    }


///////////////////////
//
// Now, update the data on the screen to its new value
//
// This portion of the program converts the bytes in the video
// memory to their new color locations in the palette between 0
// and 19 (inclusive) so the data appears correctly on the screen
//
//
    vptr = (char far *)0xa0000000;
    for (i=0; i<320*200; i++) {
        j = ((ushort)*vptr) & 0xff;
        *vptr++ = pcount[j].new_color;
    }


///////////////////////
//
// Now, write the modified palette information to the output file
// in the Exodus specified format
//
//
  // Store the palette
    tptr = bdata;
    *tptr++ = total_colors;
    for (i=0; i<total_colors; i++) {
        *tptr++ = new_palette[i].red;
        *tptr++ = new_palette[i].green;
        *tptr++ = new_palette[i].blue;
    }

  // Store the data from the screen
    vptr = (char far *)0xa0000000;
    while (vptr < (char far *)0xa000fa00) {
        c = *vptr++;
        count = 1;
        while (*vptr == c && count < 255 && vptr < (char far *)0xa000fa00) {
            ++vptr;
            ++count;
        }
        *tptr++ = count & 0xff;
        *tptr++ = c;
    }

  // Write the boot_scr.inc file in 1024k chunks
    num_to_write = (ushort)(tptr - bdata);
    tptr = bdata;
    i = 0;
    while (i < num_to_write) {
      // Write the data in hex digits
        tbufptr = (char *)buffer;
        *tbufptr++ = 'd';
        *tbufptr++ = 'b';
        *tbufptr++ = ' ';
        for (j=0; j<20 && i<num_to_write; j++) {
            ++i;
            c = *tptr++;
            *tbufptr++ = '0';       // Prefix the hex digit
          // Do most significant nibble
            if (((c & 0xf0) >> 4) > 9) {
                // It's a hex digit
                *tbufptr++ = ((c & 0xf0) >> 4) + 'a'-10;
            } else {
                *tbufptr++ = ((c & 0xf0) >> 4) + '0';
            }
          // Do least significant nibble
            if ((c & 0xf) > 9) {
                // It's a hex digit
                *tbufptr++ = (c & 0xf) + 'a'-10;
            } else {
                *tbufptr++ = (c & 0xf) + '0';
            }
            *tbufptr++ = 'h';
            if (j != 19 && i < num_to_write) {
              // More data will follow, store the comma
                *tbufptr++ = ',';
            } else {
              // Add CR/LF combo
                *tbufptr++ = 0xd;
                *tbufptr++ = 0xa;
            }
        }
        numread = fwrite(buffer, 1, (ushort)(tbufptr - (char *)buffer), stream_out);
    }


///////////////////////
//
// We're finished!
//
// Now, we're done.  We wait for a key, and then retire
// gently back into our text screen merely displaying the
// word "successful" with an exclamation point immediately
// following as if to indicate the wonderful nature of
// a job well done.
//
//
    _asm {
        xor     ax,ax
        int     16h

        mov     ax,03h
        int     10h
    }

    printf("Successful!\n\n");
    exit;
}