#include "define.h"
#include "array_list.h"
#include "linked_list.h"
#define KEY_DTYPE        char*          // Data type of keys
#define KEY_DTYPE_EQUALS string_equals  // Function used to compare KEY_DTYPE
#define KEY_HASH         string_hash    // Function to create hash value from key
#define VAL_DTYPE        int            // Data type of values
#define KEY_DTYPE_EQUALS int_equals     // Function used to compare VAL_DTYPE

// Struct for the hash pairs
typedef struct struct_HP {

	KEY_DTYPE key;    // Key
	VAL_DTYPE value;  // Value

} HP;

HP*        new_HP(                 KEY_DTYPE key, VAL_DTYPE value);....
void       free_HP(      HP* pair);....................................
KEY_DTYPE  HP_get_key(   HP* pair);....................................
VAL_DTYPE  HP_get_value( HP* pair);....................................
void       HP_set_key(   HP* pair, KEY_DTYPE key);.....................
void       HP_set_value( HP* pair,                VAL_DTYPE value);....
