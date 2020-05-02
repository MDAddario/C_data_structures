#include "define.h"
#include "array_list.h"
#include "linked_list.h"
#define KEY_DTYPE        char*          // Data type of keys
#define KEY_DTYPE_EQUALS string_equals  // Function used to compare KEY_DTYPE
#define KEY_HASH         string_hash    // Function to create hash value from key
#define VAL_DTYPE        int            // Data type of values
#define VAL_DTYPE_NULL   -393           // NULL definition corresponding to VAL_DTYPE
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

// Struct for the hash table
typedef struct struct_HT {

	AL_STYPE      num_entries;  // Number of pairs in the table
	AL_STYPE      num_buckets;  // Number of buckets
	static double max_load;     // Maximum load factor
	AL*           buckets;      // Array list of linked lists

} HT;

HT*        new_HT(                                               AL_STYPE capacity);
void       free_HT(   HT* table                                                   );
VAL_DTYPE  HT_put(    HT* table, KEY_DTYPE key, VAL_DTYPE value                   );
VAL_DTYPE  HT_get(    HT* table, KEY_DTYPE key                                    );
VAL_DTYPE  HT_remove( HT* table, KEY_DTYPE key                                    );
void       HT_rehash( HT* table                                                   );
KEY_DTYPE* HT_keys(   HT* table                                                   );
VAL_DTYPE* HT_values( HT* table                                                   );
