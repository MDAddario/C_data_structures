#include "linked_list.h"
#define AL_DTYPE        Integer          // Data type of objects to store
#define AL_DTYPE_EQUALS integer_equals   // Function used to compare objects
#define AL_DTYPE_FREE   integer_free     // Function used to free objects
#define AL_DEFAULT_CAP  10          // Default capacity for array lists

// Struct for the array list
typedef struct struct_AL {

	AL_DTYPE** array;     // Underlying array
	STYPE      size;      // Number of elements in the array
	STYPE      capacity;  // Total capacity of the array

} AL;

AL*        new_AL(                                     STYPE capacity);
void       AL_free(         AL* list);                                 
BOOL       AL_add_at(       AL* list, AL_DTYPE* value, STYPE index);   
void       AL_add_start(    AL* list, AL_DTYPE* value);                
void       AL_add_end(      AL* list, AL_DTYPE* value);                
void       AL_clear(        AL* list);                                 
BOOL       AL_contains(     AL* list, AL_DTYPE* value);                
AL_DTYPE*  AL_get(          AL* list,                  STYPE index);   
STYPE      AL_index_of(     AL* list, AL_DTYPE* value);                
BOOL       AL_is_empty(     AL* list);                                 
BOOL       AL_remove_at(    AL* list,                  STYPE index);   
BOOL       AL_remove_start( AL* list);                                 
BOOL       AL_remove_end(   AL* list);                                 
BOOL       AL_remove_value( AL* list, AL_DTYPE* value);                
STYPE      AL_size(         AL* list);                                 
BOOL       AL_equals(       AL* a, AL* b);                             