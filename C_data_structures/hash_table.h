#include "array_list.h"
#define KEY_HASH string_hash     // Function to create hash value from key

// Hash functions
AL_STYPE  string_hash (char* string, AL_STYPE num_buckets);

// Struct for the hash table
typedef struct struct_HT {

	AL_STYPE  num_entries;  // Number of pairs in the table
	AL_STYPE  num_buckets;  // Number of buckets
	double    max_load;     // Maximum load factor
	AL*       buckets;      // Array list of linked lists

} HT;

HT*        new_HT(                                               AL_STYPE capacity);
void       free_HT(   HT* table                                                   );
VAL_DTYPE  HT_put(    HT* table, KEY_DTYPE key, VAL_DTYPE value                   );
VAL_DTYPE  HT_get(    HT* table, KEY_DTYPE key                                    );
VAL_DTYPE  HT_remove( HT* table, KEY_DTYPE key                                    );
void       HT_rehash( HT* table                                                   );
KEY_DTYPE* HT_keys(   HT* table                                                   );
VAL_DTYPE* HT_values( HT* table                                                   );
