#include "define.h"
#define KEY_DTYPE        char*          // Data type of keys
#define KEY_DTYPE_EQUALS string_equals  // Function used to compare KEY_DTYPE
#define KEY_HASH         string_hash    // Function to create hash value from key
#define VAL_DTYPE        short          // Data type of values
#define VAL_DTYPE_NULL   -404           // NULL definition corresponding to VAL_DTYPE
#define VAL_DTYPE_EQUALS short_equals   // Function used to compare VAL_DTYPE

// Struct for the hash pairs
typedef struct struct_HP {

	KEY_DTYPE key;    // Key
	VAL_DTYPE value;  // Value

} HP;

HP*   new_HP(           KEY_DTYPE key, VAL_DTYPE value);
void  free_HP(HP* pair);                                

BOOL  HP_equals(const void * a, const void * b);
