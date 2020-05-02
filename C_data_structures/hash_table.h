#include "define.h"
#include "array_list.h"
#include "linked_list.h"
#define KEY_DTYPE        char*          // Data type of keys
#define KEY_DTYPE_EQUALS string_equals  // Function used to compare KEY_DTYPE
#define KEY_HASH         string_hash    // Function to create hash value from key
#define VAL_DTYPE        int            // Data type of values
#define KEY_DTYPE_EQUALS int_equals     // Function used to compare VAL_DTYPE

// Struct for the array list
typedef struct struct_AL {

	AL_DTYPE* array;     // Underlying array
	AL_STYPE  size;      // Number of elements in the array
	AL_STYPE  capacity;  // Total capacity of the array

} AL;

AL*       new_AL(                                    AL_STYPE capacity);  
void      free_AL(         AL* list);                                     
BOOL      AL_add_at(       AL* list, AL_DTYPE value, AL_STYPE index);     
void      AL_add_start(    AL* list, AL_DTYPE value);                     
void      AL_add_end(      AL* list, AL_DTYPE value);                     
void      AL_clear(        AL* list);                                     
BOOL      AL_contains(     AL* list, AL_DTYPE value);                     
AL_DTYPE  AL_get(          AL* list,                 AL_STYPE index);     
AL_STYPE  AL_index_of(     AL* list, AL_DTYPE value);                     
BOOL      AL_is_empty(     AL* list);                                     
BOOL      AL_remove_at(    AL* list,                 AL_STYPE index);     
BOOL      AL_remove_start( AL* list);                                     
BOOL      AL_remove_end(   AL* list);                                     
BOOL      AL_remove_value( AL* list, AL_DTYPE value);                     
AL_STYPE  AL_size(         AL* list);                                     
