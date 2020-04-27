#include "define.h"
#define AL_DTYPE        double         // Data type of objects to store
#define AL_DTYPE_NULL   -393          // NULL definition corresponding to AL_DTYPE
#define AL_DTYPE_EQUALS double_equals  // Function used to compare AL_DTYPE values
#define AL_STYPE        long          // Data type of size of the underlying array
#define AL_DEFAULT_CAP     10         // Default capacity for array lists

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
