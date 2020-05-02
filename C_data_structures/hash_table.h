#include "array_list.h"
#define HASH_FUNC string_hash  // Function to create hash value from key
#define MAX_LOAD  0.75         // Maximum load factor (avg. entries per bucket)

// Hash functions
STYPE integer_hash(Integer* wrapper, STYPE num_buckets);
STYPE double_hash (Double*  wrapper, STYPE num_buckets);
STYPE string_hash (String*  wrapper, STYPE num_buckets);
STYPE general_hash(STYPE  hash_code, STYPE num_buckets);

// Struct for the hash table
typedef struct struct_HT {

	STYPE  num_entries;  // Number of pairs in the table
	STYPE  num_buckets;  // Number of buckets
	AL*    buckets;      // Array list of linked lists

} HT;

HT*         new_HT(                                                 STYPE capacity);
void        HT_free(   HT* table);                                                  
VAL_DTYPE*  HT_put(    HT* table, KEY_DTYPE* key, VAL_DTYPE* value);                
VAL_DTYPE*  HT_get(    HT* table, KEY_DTYPE* key);                                  
VAL_DTYPE*  HT_remove( HT* table, KEY_DTYPE* key);                                  
void        HT_rehash( HT* table);                                                  
KEY_DTYPE** HT_keys(   HT* table);                                                  
VAL_DTYPE** HT_values( HT* table);                                                  
