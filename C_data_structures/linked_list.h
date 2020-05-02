#include "define.h"
#include "hash_pair.h"
#define LL_DTYPE        HP*             // Data type of objects to store
#define LL_DTYPE_NULL   NULL            // NULL definition corresponding to DTYPE
#define LL_DTYPE_EQUALS HP_equals       // Function used to compare LL_DTYPE values
#define LL_STYPE        long            // Data type of size of linked list

// Struct for the nodes
typedef struct struct_ND {

	struct struct_ND* prev;     // Previous node in LL
	struct struct_ND* next;     // Next node in LL
	LL_DTYPE          element;  // Element stored at node

} ND;

// Struct for linked list
typedef struct struct_LL {

	ND*      head;  // Head of linked list
	ND*      tail;  // Tail of linked list
	LL_STYPE size;  // Number of elements

} LL;

LL*       new_LL();                                                  
void      free_LL(         LL* list);                                
BOOL      LL_add_at(       LL* list, LL_DTYPE value, LL_STYPE index);
void      LL_add_start(    LL* list, LL_DTYPE value);                
void      LL_add_end(      LL* list, LL_DTYPE value);                
void      LL_clear(        LL* list);                                
BOOL      LL_contains(     LL* list, LL_DTYPE value);                
ND*       LL_get_node(     LL* list,                 LL_STYPE index);
LL_DTYPE  LL_get(          LL* list,                 LL_STYPE index);
LL_STYPE  LL_index_of(     LL* list, LL_DTYPE value);                
BOOL      LL_is_empty(     LL* list);                                
BOOL      LL_remove_at(    LL* list,                 LL_STYPE index);
BOOL      LL_remove_start( LL* list);                                
BOOL      LL_remove_end(   LL* list);                                
BOOL      LL_remove_value( LL* list, LL_DTYPE value);                
LL_STYPE  LL_size(         LL* list);                                
