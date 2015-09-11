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
char unknown_key[]="(0xתתתת)            \000";
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
char no_base_objects_text[]="¯<no base objects>                       \000";
char no_objects_text[]=     "¯<no objects>                            \000";
char no_properties_text[]=  "¯<no properties>                                   \000";
char no_events_text[]=      "¯<no events>                                       \000";
char empty_text[]="¯                                                                                                                                    \000";

// The main screen
char text0[] ="¯ֹֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽ»\000";
char text1[] ="¯ּ¯ס Exodus Object Manager                                                                                                May.12.2001 ¯÷\000";
char text2[] ="¯ּ¯ס Beatleworks, Inc. 2001                                                                                                           ¯÷\000";
char text3[] ="¯ָ¯ֿ Base Objects ”¯ÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊ¯ֿ Objects ”¯ÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊ¯ֿ F3:Properties ”¯ÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊ¼\000";
char text4[] ="¯                                        ּ                                        ּ                                                  \000";
char text36[]="¯                                        ּ                                        ּ¯ֿ F4:Events ”¯ִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִ\000";
char text68[]="¯ֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽ\000";
char text69[]="¯                                                                                                                                    \000";
char text75[]="¯ֹֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽֽ»\000";
char text76[]="¯ּ¯ס                                                    Use the arrows to navigate                                                    ¯÷\000";
char text77[]="¯ּ¯ס   Ins:Add new                                                                                                  F10:Save changes  ¯÷\000";
char text78[]="¯ּ¯ס Enter:Edit                                                                                                 Esc Esc:Abort changes ¯÷\000";
char text79[]="¯ָÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊÊ¼\000";

// Base object and object input screen
char xx_text0[] ="Úִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִ¿\000";
char bo_text1[] ="´Base object name:                                                               ³\000";
char o_text1[]  ="´Object name:                                                                    ³\000";
char xx_text2[] ="´תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת³\000";
char xx_text3[] ="´                                                                                ³\000";
char bo_text4[] ="´Variable key:  (will appear as _boKEY_[base_object_name])                       ³\000";
char o_text4[]  ="´Variable key:  (will appear as _oKEY_[object_name])                             ³\000";
char xx_text5[] ="´תתתתתתתתתתתתתתתתתתתת                                                            ³\000";
char xx_text6[] ="´                                                                                ³\000";
char xx_text7[] ="´Exodus create():                                                                ³\000";
char xx_text8[] ="´תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת³\000";
char xx_text9[] ="´ File: תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת F5:Edit ³\000";
char xx_text10[]="´                                                                                ³\000";
char xx_text11[]="´Exodus redraw():                                                                ³\000";
char xx_text12[]="´תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת³\000";
char xx_text13[]="´ File: תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת F5:Edit ³\000";
char xx_text14[]="´                                                                                ³\000";
char xx_text15[]="´Exodus process():                                                               ³\000";
char xx_text16[]="´תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת³\000";
char xx_text17[]="´ File: תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת F5:Edit ³\000";
char xx_text18[]="´                                                                                ³\000";
char xx_text19[]="´ִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִ³\000";
char xx_text20[]="´F10:Save changes                                                      Esc:Cancel³\000";
char xx_text21[]="ְֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳÙ\000";

// Property input screen
char op_text0[] ="Úִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִ¿\000";
char op_text1[] ="´Property name:                                                                  ³\000";
char op_text2[] ="´תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת³\000";
char op_text3[] ="´                                                                                ³\000";
char op_text4[] ="´Variable key:  (will appear as _key_[property_name])                            ³\000";
char op_text5[] ="´תתתתתתתתתתתתתתתתתתתת                                                            ³\000";
char op_text6[] ="´                                                                                ³\000";
char op_text7[] ="´Exodus process():                                                               ³\000";
char op_text8[] ="´תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת³\000";
char op_text9[] ="´                                                                                ³\000";
char op_text10[]="´Default value:                                                                  ³\000";
char op_text11[]="´תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת                                             ³\000";
char op_text12[]="´                                                                                ³\000";
char op_text13[]="´ִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִ³\000";
char op_text14[]="´F10:Save changes                                                      Esc:Cancel³\000";
char op_text15[]="ְֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳÙ\000";

// Event input screen
char oe_text0[] ="Úִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִ¿\000";
char oe_text1[] ="´Event name:                                                                     ³\000";
char oe_text2[] ="´תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת³\000";
char oe_text3[] ="´                                                                                ³\000";
char oe_text4[] ="´Variable key:  (will appear as _key_[event_name])                               ³\000";
char oe_text5[] ="´תתתתתתתתתתתתתתתתתתתת                                                            ³\000";
char oe_text6[] ="´                                                                                ³\000";
char oe_text7[] ="´ִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִ³\000";
char oe_text8[] ="´F10:Save changes                                                      Esc:Cancel³\000";
char oe_text9[] ="ְֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳÙ\000";

// Macro screen
char mac_text0[]="Úִִִִִִִִִִִִִִִִִִִִִִִִִִ¿\000";
char mac_text1[]="´      Macro Assignment    ³\000";
char mac_text2[]="´ִִִִִִִִִִִִִִִִִִִִִִִִִִ³\000";
char mac_text3[]="´  Key:                    ³\000";
char mac_text4[]="´ Desc: תתתתתתתתתתתתתתתתתת ³\000";
char mac_text5[]="´ֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳ³\000";
char mac_text6[]="´F10:Continue    Esc:Cancel³\000";
char mac_text7[]="ְֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳֳÙ\000";