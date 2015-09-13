// dsw.c - Debi Source Writer
//
// This routine puts creates a Debi compatible source code file used in debugging
//
//
//
//
//
//
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <math.h>
#include <malloc.h>

#include "dsw.h"
#include "defs.inc"


int main(int argc, char *argv[])
{
    FILE *fh_asm;
    FILE *fh_lst;
    ushort i, result;

    printf("DSW - [D]ebi [S]ource [W]riter by Beatleworks, Inc. 11.04.2001\n\n");
    if (argc != 2) {
        printf("  Syntax:  dsw file\n\n");
        goto quit;
    }

    _asm {
      // Reduce allocated memory to 64k
        mov     ax,cs
        mov     es,ax
        mov     ah,0x4a
        mov     bx,0x1000
        int     0x21
        jnc     please_continue
    }
    printf("Unable to allocate memory.  Terminating\n");
    goto quit;


  please_continue:
  // Get the two file names based off the one they've specified
    derive_input_file_names(argv[1]);

  // Open ASM file
    fh_asm = fopen(asm_filename,"rb+");
    if (fh_asm == NULL) {
        printf("Unable to open file '%s'\n",asm_filename);
        goto quit;
    }
    printf(".");



  // Open LST file
    fh_lst = fopen(lst_filename,"rb+");
    if (fh_lst == NULL) {
        printf("Unable to open file '%s'\n",lst_filename);
        goto quit;
    }
    printf(".");



  // Allocate XMS buffers for each file
    result = allocate_xms_buffers();
    if (result == 0) {
        printf("Unable to allocate necessary memory\n");
        goto quit;
    }



  // Read the contents of the specified source file
    strncpy(load_files[load_file_count].filename, asm_filename, strlen(asm_filename));
    result = load_file(fh_asm, asm_mem);                            // Loads entire file
    if (result == 0) {
        printf("Unable to load source file\n");
        goto quit_politely;
    }
  // Identify the line numbers in that file
    result = identify_line_numbers(asm_mem);                        // Uses current load_file_count record



  // Repeat the above process for all INCLUDE files
    result = load_and_parse_include_files();
    if (result == 0) {
        printf("Unable to load an INCLUDE source file %s\n", last_include);
        goto quit_politely;
    }
    printf("\nLoaded %u files\n",load_file_count);
    for (i=0; i<load_file_count; i++) {
        if (i+1 < load_file_count) {
            printf(" Ã ");
        } else {
            printf(" À ");
        }
        printf("%s, %lu bytes, %lu lines\n",load_files[i].filename, load_files[i].source_end - load_files[i].source_start, (load_files[i].line_end - load_files[i].line_start) / sizeof(struct LINE_NUM));
    }
    printf("-----\n");
    printf("Total bytes = %lu\n",xms_offset);
    printf("Total lines = %lu\n",line_offset / sizeof(struct LINE_NUM));



  // Read the contents of the LIST file
    ++load_file_count;
    strncpy(load_files[load_file_count].filename, lst_filename, strlen(lst_filename));
    result = load_file(fh_lst, lst_mem);
    result = identify_exec_to_line_numbers();



  quit_politely:
    result = deallocate_xms_buffers();
    if (result == 0) {
        printf("Memory could not be freed\n");
    }
  quit:
    exit(0);
}



#include "extras.c"
