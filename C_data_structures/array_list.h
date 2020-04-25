#define TRUE 1
#define FALSE 0
#define DEFAULT_CAP 10
#define BOOL char   // Treat booleans
#define DTYPE long  // Data type of objects to store
#define ATYPE short // Data type for the size of the underlying array

/*
 *   NOTE THAT THE DTYPE MUST BE COMPARABLE VIA == OPERATION
 */

// Struct for the array list
typedef struct struct_AL {

	DTYPE* array;       // Underlying array
	ATYPE  size;        // Number of elements in the array
	ATYPE  capacity;    // Total capacity of the array

} AL;

AL*   new_AL(                                 ATYPE capacity);
void  free_AL(         AL* list);
void  AL_add_at(       AL* list, DTYPE value, ATYPE index);
void  AL_add_start(    AL* list, DTYPE value);
void  AL_add_end(      AL* list, DTYPE value);
void  AL_clear(        AL* list);
BOOL  AL_contains(     AL* list, DTYPE value);
DTYPE AL_get(          AL* list,              ATYPE index);
ATYPE AL_index_of(     AL* list, DTYPE value);
BOOL  AL_is_empty(     AL* list);
void  AL_remove_at(    AL* list,              ATYPE index);
BOOL  AL_remove_value( AL* list, DTYPE value);
ATYPE AL_size(         AL* list);
