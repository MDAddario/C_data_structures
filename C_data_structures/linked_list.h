#define TRUE 1
#define FALSE 0
#define BOOL char    // Treat booleans
#define DTYPE short  // Data type of objects to store
#define ATYPE long   // Data type of size of linked list

/*
 *   NOTE THAT THE DTYPE MUST BE COMPARABLE VIA == OPERATION
 */

// Struct for the nodes
typedef struct struct_ND {

	struct struct_ND* prev;     // Previous node in LL
	struct struct_ND* next;     // Next node in LL
	DTYPE             element;  // Element stored at node

} ND;

// Struct for linked list
typedef struct struct_LL {

	ND*   head;   // Head of linked list
	ND*   tail;   // Tail of linked list
	ATYPE size;   // Number of elements

} LL;

LL*   new_LL(                                 ATYPE capacity);   // TESTED
void  free_LL(         LL* list);                                // TESTED
BOOL  LL_add_at(       LL* list, DTYPE value, ATYPE index);      // TESTED
void  LL_add_start(    LL* list, DTYPE value);                   // TESTED
void  LL_add_end(      LL* list, DTYPE value);                   // TESTED
void  LL_clear(        LL* list);                                // TESTED
BOOL  LL_contains(     LL* list, DTYPE value);                   // TESTED
DTYPE LL_get(          LL* list,              ATYPE index);      // TESTED
ATYPE LL_index_of(     LL* list, DTYPE value);                   // TESTED
BOOL  LL_is_empty(     LL* list);                                // TESTED
BOOL  LL_remove_at(    LL* list,              ATYPE index);      // TESTED
BOOL  LL_remove_start( LL* list);                                // TESTED
BOOL  LL_remove_end(   LL* list);                                // TESTED
BOOL  LL_remove_value( LL* list, DTYPE value);                   // TESTED
ATYPE LL_size(         LL* list);                                // TESTED
