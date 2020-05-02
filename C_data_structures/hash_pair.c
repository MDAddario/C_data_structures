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
