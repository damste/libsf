// ed.inc
//
// Exodus File Manager - include file
// This program is called ED because originally my BATCH file was called "ed".  But it quickly grew too complex for
// any sane person to try to use, so I created a function manager.
//

ushort break_here=0;




// Misc data
ushort max_rows;
char color=31;
int extra_space=10000;

// Data for load buffer
FILE *fh;
struct FILE_HDR header;
char huge *buf;
char huge *buf_end;
char huge *bptr;
char load_buf[2048];

// Data for get_a_key() routines
int getting_macro=0;
int running_macro=0;
int total_macros=0;
int defining_macro=0;
struct MACRO_RECORD macro[MAX_MACROS];
ushort huge *mac_keydata=NULL;
ushort huge *next_mac_keydata=NULL;
ushort huge *running_mac_keydata=NULL;
int running_keys_left=0;
char press_a_key[]="(press a key)       \000";
char unknown_key[]="(0x����)            \000";
char known_key[]  ="                    \000";

// Data for input() routines
ushort column=1;
ushort origin_column=1;
struct INPUT_RECORD input[MAX_INPUT];
struct INPUT_HOOK   input_hook[MAX_HOOKS];
ushort input_hook_count=0;
ushort input_count=0;
ushort current_input=0;
ushort insert_mode=1;
ushort _offset;

// Data for screen manipulation
ulong highlighted_file=-1;
ulong highlighted_function=-1;
struct CURSOR_POS cp;

// Data for displaying messages
char no_files_text[]="��<no files>                              \000";
char no_funcs_text[]="��<no functions>                          \000";
char empty_text[]="��                                                                                                                                    \000";

// The main screen                                            ��          ��
char text0[] ="������������������������������������������������������������������������������������������������������������������������������������ͻ\000";
char text1[] ="��̯� Exodus File/Function Manager                                                                                         May.28.2001 ���\000";
char text2[] ="��̯� Beatleworks, Inc. 2001                                                                                                           ���\000";
char text3[] ="��ȯϐ Files ��������������������������������������������ʯϐ Functions ��������������������������������������������������������������������ʼ\000";
char text4[] ="��                                                   �                                                                                \000";
char text75[]="������������������������������������������������������������������������������������������������������������������������������������ͻ\000";
char text76[]="��̯�                                                    Use the arrows to navigate                                                    ���\000";
char text77[]="��̯�   Ins:Add new                                                                                                  F10:Save changes  ���\000";
char text78[]="��̯� Enter:Edit                                                                                                 Esc Esc:Abort changes ���\000";
char text79[]="������������������������������������������������������������������������������������������������������������������������������������ʼ\000";

// Base object and object input screen
char xx_text0[]="��������������������������������������������������������������������������������Ŀ\000";
char fi_text1[]="�File name: (include full path)                                                  �\000";
char fu_text1[]="�Function name:                                                                  �\000";
char xx_text2[]="����������������������������������������������������������������������������������\000";
char xx_text3[]="�                                                                                �\000";
char xx_text4[]="��������������������������������������������������������������������������������ĳ\000";
char xx_text5[]="�F10:Save changes                                                      Esc:Cancel�\000";
char xx_text6[]="����������������������������������������������������������������������������������\000";

// Macro screen
char mac_text0[]="��������������������������Ŀ\000";
char mac_text1[]="�      Macro Assignment    �\000";
char mac_text2[]="��������������������������ĳ\000";
char mac_text3[]="�  Key:                    �\000";
char mac_text4[]="� Desc: ������������������ �\000";
char mac_text5[]="��������������������������ó\000";
char mac_text6[]="�F10:Continue    Esc:Cancel�\000";
char mac_text7[]="����������������������������\000";