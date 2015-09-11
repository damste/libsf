// obj_hdr.h
//
// Object header - File structures for Exodus Object System
//




struct FILE_HDR {
    ulong   first_bo_offset;
    ulong   next_avail_offset;
    ulong   bo_records;
    ulong   o_records;
    ulong   prop_records;
    ulong   event_records;
    char    reserved[40];
};




struct BO_RECORD {
    char    status;
    char    name[80];
    char    create[80];
    char    redraw[80];
    char    process[80];
    char    key[20];
    char    create_filename[64];
    char    redraw_filename[64];
    char    process_filename[64];
    char    reserved[40];
    ulong   first_prop;
    ulong   first_event;
    ulong   next_bo;
    ulong   prev_bo;
    ulong   first_o;
};




struct O_RECORD {
    char    status;
    char    name[80];
    char    create[80];
    char    redraw[80];
    char    process[80];
    char    key[20];
    char    create_filename[64];
    char    redraw_filename[64];
    char    process_filename[64];
    char    reserved[48];
    ulong   next_o;
    ulong   prev_o;
    ulong   first_prop;
    ulong   first_event;
};




struct PROP_RECORD {
    char    status;
    char    name[80];
    char    process[80];
    char    key[20];
    char    default_value[35];
    char    reserved[244];
    ulong   next_prop;
    ulong   prev_prop;
};




struct EVENT_RECORD {
    char    status;
    char    name[80];
    char    key[20];
    char    reserved[240];
    ulong   next_event;
    ulong   prev_event;
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