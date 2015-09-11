//
// defs.inc
//


void derive_input_file_names(char *);
ushort allocate_xms_buffers(void);
ushort deallocate_xms_buffers(void);
ushort load_file(FILE *, ushort);
ushort identify_line_numbers(ushort);
ushort load_and_parse_include_files(void);
ushort identify_exec_to_line_numbers(void);
ushort XMS_to_conventional(ulong, struct XMS_MOVE *);
ushort conventional_to_XMS(ulong, struct XMS_MOVE *);
void push_relative_path(char *);