// obj_hdr.h
//
// Object header - File structures for Exodus Object System
//




struct FILE_HDR {
    ulong   first_file_offset;
    ulong   next_avail_offset;
    ulong   file_records;
    ulong   func_records;
    char    reserved[48];
};




struct FILE_RECORD {
    char    status;
    char    name[80];
    char    reserved[19];
    ulong   prev_file;
    ulong   next_file;
    ulong   first_func;
};




struct FUNC_RECORD {
    char    status;
    char    name[80];
    char    reserved[23];
    ulong   next_func;
    ulong   prev_func;
};




struct INPUT_RECORD {
    ushort  y;
    ushort  x;
    char far *ptr;
    ushort  length;
    char    type;
    char    verify;
};




struct INPUT_HOOK {
    int     item;
    char    type;
    char far *fptr;
    char    data[8];
};




struct MACRO_RECORD {
    ushort  key;
    ushort  num_keys;
    ushort  start_offset;
    char    desc[18];
    char    reserved[8];
};




struct CURSOR_POS {
    int     y;
    int     x;
};