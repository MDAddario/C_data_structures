#include "define.h"
#define KEY_DTYPE         String          // Data type of keys
#define KEY_DTYPE_EQUALS  string_equals   // Function used to compare keys
#define KEY_DTYPE_FREE    string_free     // Function used to free keys
#define KEY_HASH          string_hash     // Function to create hash value from key
#define VAL_DTYPE         Integer         // Data type of values
#define VAL_DTYPE_EQUALS  integer_equals  // Function used to compare values
#define VAL_DTYPE_FREE    integer_free    // Function used to free values

// Struct for the hash pairs
typedef struct struct_HP {

	KEY_DTYPE* key;    // Key
	VAL_DTYPE* value;  // Value

} HP;

// Methods
HP*   new_HP(   KEY_DTYPE* key, VAL_DTYPE* value);
void  HP_free(  HP* pair);                      
BOOL  HP_equals(HP* a, HP* b);                  
