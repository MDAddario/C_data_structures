#include <stdlib.h>
#include "hash_pair.h"

// Constructor
HP* new_HP(KEY_DTYPE* key, VAL_DTYPE* value) {

	// Allocate the memory for a hash pair
	HP* pair = (HP*)malloc(sizeof(HP));

	// Set the fields
	pair->key   = key;
	pair->value = value;
	return pair;
}

// Destructor
void HP_free(HP* pair) {

	// Free the fields
	KEY_DTYPE_FREE(pair->key);
	VAL_DTYPE_FREE(pair->value);

	// Free the hash pair
	free(pair);
	return;
}

// Comparison operator
BOOL HP_equals(HP* a, HP* b) {
	return KEY_DTYPE_EQUALS(a->key, b->key) && VAL_DTYPE_EQUALS(a->value, b->value);
}