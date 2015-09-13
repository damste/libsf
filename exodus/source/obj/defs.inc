// defs.inc
//
// Exodus Object File Manager Definitions
//





// Keyboard definitions
#include "keylist.h"            // Constant definition of keylist
                                // Note, the keyboard variables (for macros) are defined in obj.c

// Variable definitions
typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned char uchar;


// Constant declarations for input routines
#define _INPUT_UPPER 0
#define _INPUT_LOWER 1
#define _INPUT_MIXED 2
#define _INPUT_NUMBERS 3
#define _INPUT_GET_A_KEY 4

#define _INPUT_HOOK_KEY_BEFORE 0
#define _INPUT_HOOK_KEY_AFTER 1

#define _INPUT_NO_SPACES 0
#define _INPUT_SPACES 1


// Miscellaneous
#define _INPUT 0
#define _SCREEN 1


// Constant definitions for variable sizing
#define MAX_INPUT 100
#define MAX_HOOKS 100
#define MAX_MACROS 15
#define MAX_KEYSTROKES 4000


// Function prototypes
void add_base_object(void);
void add_object(void);
void add_property(void);
void add_event(void);
void edit_base_object(void);
void edit_object(void);
void edit_property(void);
void edit_event(void);
void draw_base_objects(ushort);
void draw_objects(ushort);
void draw_properties(ushort);
void draw_events(ushort);
void save_file(void);
void pos_cursor(ushort, ushort);
void get_cursor(void);
ushort get_a_key(void);
void display_text(ushort, ushort, char *);
void display_text_length(ushort, ushort, char *, ushort);
void display_text_only(ushort, ushort, char *);
void display_far_text_length(ushort, ushort, char huge *, ushort);
void display_far_text_only_length(ushort, ushort, char huge *, ushort);
void main_screen(void);
void display_common_screen(void);
void base_object_screen(void);
void object_screen(void);
void object_property_screen(void);
void object_event_screen(void);
void clear_screen(void);
void get_input_insert_space(ushort);
void get_input_delete_char(ushort);
void full_strnset(char huge *, char, ushort);
void full_strnset_far(char huge *, char huge *, char);
void full_strncpy(char huge *, char huge *, ushort);
void set_cursor_size(void);
ushort verify_no_spaces_in_input(ushort);
char huge *item_save(int);
void item_restore(char huge *);
void draw_macro_window(void);
char huge *get_keystroke_text(ushort);
void load_macros(void);
void save_macros(void);

// Input prototypes
void reset_input(void);
void set_input(void);
void push_input(ushort, ushort, char huge *, ushort, char, char);
void push_input_hook_key(ushort, int, char huge *);
ushort get_input(void);
void edit_file(void);