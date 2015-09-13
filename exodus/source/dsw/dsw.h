// dsw.h
//


typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned long  ulong;
typedef unsigned int   uint;

#define _LOCAL_IO_BUFFER_SIZE 4096
#define _LOCAL_LN_BUFFER_SIZE 4096
#define _LOCAL_ELN_BUFFER_SIZE 4096

FILE *gfh;

// Global variables
ushort io_buffer;
char *cmd_line_pathname;
ushort cmd_line_pathname_length;
char local_io_buffer[_LOCAL_IO_BUFFER_SIZE];
char local_ln_buffer[_LOCAL_LN_BUFFER_SIZE];
char local_eln_buffer[_LOCAL_ELN_BUFFER_SIZE];
char dot_asm[]=".asm\000";
char asm_filename[64];
char dot_lst[]=".lst\000";
char lst_filename[64];
char last_include[64];

// Relative path info
struct RELATIVE_PATH {
    char    filename[64];
};
struct RELATIVE_PATH rpath[10];
ushort rpath_count=0;

// XMS related data
ulong xms_func;
ulong xms_offset=0;
ulong line_offset=0;
ulong exec_to_line_offset=0;
ushort asm_mem;
ushort lst_mem;
ushort in_mem;
ushort out_mem;
ushort line_mem;
ushort kilobytes=4096;                                              // 4MB buffer
ushort load_file_count=0;


// The following structure is used locally on the stack by anything needing to move data to/from XMS
struct XMS_MOVE {
    ulong   length;
    ushort  src_handle;
    ulong   src_offset;
    ushort  dst_handle;
    ulong   dst_offset;
};



// File listings    (of files loaded)
struct LOAD_FILE {
    char    filename[64];
    ulong   source_start;
    ulong   source_end;
    ulong   line_start;
    ulong   line_end;
    ulong   total_lines;
    ulong   exec_to_line_start;
    ulong   exec_to_line_end;
};
struct LOAD_FILE load_files[50];


// Offset to the offset for each line in a file
struct LINE_NUM {
    ulong   line_offset;
};


// Offset to line number listing    (for debug trace)
struct EXEC_TO_LINE_NUM {
    ulong   line_number;                                            // Line number in the source file
    ulong   exec_offset;                                            // Offset in the executable file
};