#define DTYPE int
/*
 *   NOTE THAT THE DTYPE MUST BE COMPARABLE VIA == OPERATION
 */

// Struct for the array list
typedef struct struct_AL {

	DTYPE* array;	// Underlying array
	int size;		// Number of elements in the array
	int capacity;	// Total capacity of the array
	
} AL;

AL*   new_AL(                   int capacity);
void  AL_add_at(      AL* list, DTYPE value, int index);
void  AL_add_start(   AL* list, DTYPE value);
void  AL_add_end(     AL* list, DTYPE value);
void  AL_clear(       AL* list);
int   AL_contains(    AL* list, DTYPE value);
DTYPE AL_get(         AL* list, int index);
int   AL_index_of(    AL* list, DTYPE value);
int   AL_is_empty(    AL* list);
int   AL_remove_at(   AL* list, int index);
int   AL_remove_value(AL* list, DTYPE value);
int   AL_size(        AL* list);
