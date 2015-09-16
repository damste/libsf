// obj.inc
//
// Exodus Object Manager - include file
//

ushort break_here=0;




// Misc data
ushort max_rows;
char color=31;

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
ulong highlighted_base_object=-1;
ulong highlighted_object=-1;
ulong highlighted_property=-1;
ulong highlighted_event=-1;
struct CURSOR_POS cp;

// Data for displaying messages
char no_base_objects_text[]="��<no base objects>                       \000";
char no_objects_text[]=     "��<no objects>                            \000";
char no_properties_text[]=  "��<no properties>                                   \000";
char no_events_text[]=      "��<no events>                                       \000";
char empty_text[]="��                                                                                                                                    \000";

// The main screen
char text0[] ="������������������������������������������������������������������������������������������������������������������������������������ͻ\000";
char text1[] ="��̯� Exodus Object Manager                                                                                                May.12.2001 ���\000";
char text2[] ="��̯� Beatleworks, Inc. 2001                                                                                                           ���\000";
char text3[] ="��ȯϐ Base Objects ��������������������������ʯϐ Objects ��������������������������������ʯϐ F3:Properties ����������������������������������ʼ\000";
char text4[] ="��                                        �                                        �                                                  \000";
char text36[]="��                                        �                                        ̯ϐ F4:Events ����������������������������������������\000";
char text68[]="��������������������������������������������������������������������������������������������������������������������������������������\000";
char text69[]="��                                                                                                                                    \000";
char text75[]="������������������������������������������������������������������������������������������������������������������������������������ͻ\000";
char text76[]="��̯�                                                    Use the arrows to navigate                                                    ���\000";
char text77[]="��̯�   Ins:Add new                                                                                                  F10:Save changes  ���\000";
char text78[]="��̯� Enter:Edit                                                                                                 Esc Esc:Abort changes ���\000";
char text79[]="������������������������������������������������������������������������������������������������������������������������������������ʼ\000";

// Base object and object input screen
char xx_text0[] ="��������������������������������������������������������������������������������Ŀ\000";
char bo_text1[] ="�Base object name:                                                               �\000";
char o_text1[]  ="�Object name:                                                                    �\000";
char xx_text2[] ="����������������������������������������������������������������������������������\000";
char xx_text3[] ="�                                                                                �\000";
char bo_text4[] ="�Variable key:  (will appear as _boKEY_[base_object_name])                       �\000";
char o_text4[]  ="�Variable key:  (will appear as _oKEY_[object_name])                             �\000";
char xx_text5[] ="���������������������                                                            �\000";
char xx_text6[] ="�                                                                                �\000";
char xx_text7[] ="�Exodus create():                                                                �\000";
char xx_text8[] ="����������������������������������������������������������������������������������\000";
char xx_text9[] ="� File: ���������������������������������������������������������������� F5:Edit �\000";
char xx_text10[]="�                                                                                �\000";
char xx_text11[]="�Exodus redraw():                                                                �\000";
char xx_text12[]="����������������������������������������������������������������������������������\000";
char xx_text13[]="� File: ���������������������������������������������������������������� F5:Edit �\000";
char xx_text14[]="�                                                                                �\000";
char xx_text15[]="�Exodus process():                                                               �\000";
char xx_text16[]="����������������������������������������������������������������������������������\000";
char xx_text17[]="� File: ���������������������������������������������������������������� F5:Edit �\000";
char xx_text18[]="�                                                                                �\000";
char xx_text19[]="��������������������������������������������������������������������������������ĳ\000";
char xx_text20[]="�F10:Save changes                                                      Esc:Cancel�\000";
char xx_text21[]="����������������������������������������������������������������������������������\000";

// Property input screen
char op_text0[] ="��������������������������������������������������������������������������������Ŀ\000";
char op_text1[] ="�Property name:                                                                  �\000";
char op_text2[] ="����������������������������������������������������������������������������������\000";
char op_text3[] ="�                                                                                �\000";
char op_text4[] ="�Variable key:  (will appear as _key_[property_name])                            �\000";
char op_text5[] ="���������������������                                                            �\000";
char op_text6[] ="�                                                                                �\000";
char op_text7[] ="�Exodus process():                                                               �\000";
char op_text8[] ="����������������������������������������������������������������������������������\000";
char op_text9[] ="�                                                                                �\000";
char op_text10[]="�Default value:                                                                  �\000";
char op_text11[]="������������������������������������                                             �\000";
char op_text12[]="�                                                                                �\000";
char op_text13[]="��������������������������������������������������������������������������������ĳ\000";
char op_text14[]="�F10:Save changes                                                      Esc:Cancel�\000";
char op_text15[]="����������������������������������������������������������������������������������\000";

// Event input screen
char oe_text0[] ="��������������������������������������������������������������������������������Ŀ\000";
char oe_text1[] ="�Event name:                                                                     �\000";
char oe_text2[] ="����������������������������������������������������������������������������������\000";
char oe_text3[] ="�                                                                                �\000";
char oe_text4[] ="�Variable key:  (will appear as _key_[event_name])                               �\000";
char oe_text5[] ="���������������������                                                            �\000";
char oe_text6[] ="�                                                                                �\000";
char oe_text7[] ="��������������������������������������������������������������������������������ĳ\000";
char oe_text8[] ="�F10:Save changes                                                      Esc:Cancel�\000";
char oe_text9[] ="����������������������������������������������������������������������������������\000";

// Macro screen
char mac_text0[]="��������������������������Ŀ\000";
char mac_text1[]="�      Macro Assignment    �\000";
char mac_text2[]="��������������������������ĳ\000";
char mac_text3[]="�  Key:                    �\000";
char mac_text4[]="� Desc: ������������������ �\000";
char mac_text5[]="��������������������������ó\000";
char mac_text6[]="�F10:Continue    Esc:Cancel�\000";
char mac_text7[]="����������������������������\000";