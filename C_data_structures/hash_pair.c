#include <stdio.h>
#include <stdlib.h>
#include "hash_pair.h"

// Constructor
HP* new_HP(KEY_DTYPE key, VAL_DTYPE value) {

	// Allocate the memory for a hash pair
	HP* pair = (HP*)malloc(sizeof(HP));

	// Set the fields
	pair->key = key;
	pair->value = value;
	return pair;
}

// Destructor
void free_HP(HP* pair) {

	// Free the hash pair
	free(pair);
	return;
}

// Comparison operator
BOOL HP_equals(const void * a, const void * b) {

	return KEY_DTYPE_EQUALS((void*)&(((HP*)a)->key), (void*)&(((HP*)b)->key))
	    && VAL_DTYPE_EQUALS((void*)&(((HP*)a)->value), (void*)&(((HP*)b)->value));
}