#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

// Hash functions
STYPE integer_hash(Integer* wrapper, STYPE num_buckets) {
	return general_hash((STYPE)(wrapper->entry), num_buckets);
}

STYPE double_hash(Double* wrapper, STYPE num_buckets) {
	return general_hash((STYPE)(wrapper->entry), num_buckets);
}

STYPE string_hash(String* wrapper, STYPE num_buckets) {

	// Use the java hashcode
	STYPE size = strlen(wrapper->entry);
	STYPE hash_code = 0;

	for (STYPE j = 0; j < size; j++)
		hash_code = 31 * hash_code + wrapper->entry[j];

	return general_hash(hash_code, num_buckets);
}

STYPE general_hash(STYPE hash_code, STYPE num_buckets) {

	// Check for issues
	if (hash_code < 0) {
		printf("There is an issue with the hash code.\n");
		exit(0);
	}
	// Modulate by bucket number
	return hash_code % num_buckets;
}

// Constructor
HT* new_HT(STYPE capacity) {

	// Allocate the memory for the hash table
	HT* table = (HT*)malloc(sizeof(HT));

	// Initialize fields
	table->num_entries = 0;
	table->num_buckets = capacity;

	// Create the array list
	table->buckets = new_AL(table->num_buckets);

	// Construct the buckets
	for (STYPE j = 0; j < table->num_buckets; j++)
		AL_add_end(table->buckets, new_LL());

	// Return the table
	return table;
}

// Destructor
void HT_free(HT* table) {

	// Free the array list (this takes care of all nested structures)
	AL_free(table->buckets);

	// Free the table
	free(table);
}

// Put a hash pair into the table
VAL_DTYPE* HT_put(HT* table, KEY_DTYPE* key, VAL_DTYPE* value) {

	// Retrieve hash_value
	STYPE hash_value = HASH_FUNC(key, table->num_buckets);

	// Isolate the bucket in question
	LL* bucket = AL_get(table->buckets, hash_value);

	// Run through the bucket nodes
	ND* node = bucket->head;
	while (node != NULL) {

		// Extract the hash pair
		HP* pair = node->element;

		// Check if key already exists
		if (KEY_DTYPE_EQUALS(pair->key, key)) {

			// Update value and return old value
			VAL_DTYPE* old_value = pair->value;
			pair->value = value;
			return old_value;
		}

		node = node->next;
	}

	// Add hash_pair to bucket
	LL_add_end(bucket, new_HP(key, value));
	table->num_entries++;

	// Consider rehashing
	if (((double) table->num_entries) / table->num_buckets > MAX_LOAD)
		HT_rehash(table);

	return NULL;
}

// Get a value from the table
VAL_DTYPE* HT_get(HT* table, KEY_DTYPE* key) {

	// Retrieve hash_value
	STYPE hash_value = HASH_FUNC(key, table->num_buckets);

	// Isolate the bucket in question
	LL* bucket = AL_get(table->buckets, hash_value);

	// Run through the bucket nodes
	ND* node = bucket->head;
	while (node != NULL) {

		// Extract the hash pair
		HP* pair = node->element;

		// Check if key already exists
		if (KEY_DTYPE_EQUALS(pair->key, key)) {

			// Return value
			return pair->value;
		}

		node = node->next;
	}

	// Key doesn't exist
	return NULL;
}

// Remove a pair from the table
VAL_DTYPE* HT_remove(HT* table, KEY_DTYPE* key) {

	// Retrieve hash_value
	STYPE hash_value = HASH_FUNC(key, table->num_buckets);

	// Isolate the bucket in question
	LL* bucket = AL_get(table->buckets, hash_value);

	// Run through the bucket nodes
	ND* node = bucket->head;
	while (node != NULL) {

		// Extract the hash pair
		HP* pair = node->element;

		// Check if key already exists
		if (KEY_DTYPE_EQUALS(pair->key, (key))) {

			// Delete hash_pair and return value
			VAL_DTYPE* value = pair->value;
			LL_remove_value(bucket, pair);
			table->num_entries--;
			return value;
		}

		node = node->next;
	}

	// Key doesn't exist
	return NULL;
}

// Add more buckets to the table to improve lookup times
void HT_rehash(HT* table) {

	// Double capacity
	table->num_buckets *= 2;

	// Construct the new buckets
	AL* new_buckets = new_AL(table->num_buckets);
	for (STYPE j = 0; j < table->num_buckets; j++)
		AL_add_end(new_buckets, new_LL());

	// Migrate all the old hash_pairs
	for (STYPE j = 0; j < table->num_buckets / 2; j++) {

		// Pick out the buckets one by one
		LL* old_bucket = AL_get(table->buckets, j);

		// Run through the bucket nodes
		ND* node = old_bucket->head;
		while (node != NULL) {

			// Extract the hash pair
			HP* pair = node->element;

			// Retrieve new hash_value
			STYPE hash_value = HASH_FUNC(pair->key, table->num_buckets);

			// Isolate the bucket in question
			LL* new_bucket = AL_get(new_buckets, hash_value);

			// Add the hash_pair to the new bucket
			LL_add_end(new_bucket, pair);

			node = node->next;
		}
	}

	// Free the buckets
	for (STYPE j = 0; j < table->num_buckets / 2; j++)
		LL_free(AL_get(table->buckets, j));

	// Free the array list
	AL_free(table->buckets);

	// Update the buckets
	table->buckets = new_buckets;
}

// Generate an array with all the keys in the table
KEY_DTYPE** HT_keys(HT* table) {

	// Create the return array
	KEY_DTYPE** keys = (KEY_DTYPE**)malloc(table->num_entries * sizeof(KEY_DTYPE*));
	STYPE size = 0;

	// Run through all the hash pairs
	for (STYPE j = 0; j < table->num_buckets; j++) {

		// Pick the buckets
		LL* bucket = AL_get(table->buckets, j);

		// Run through the bucket
		ND* node = bucket->head;
		while (node != NULL) {

			// Extract the hash pair
			HP* pair = node->element;

			// Add the key to the array
			keys[size++] = pair->key;

			node = node->next;
		}
	}
	return keys;
}

// Generate an array with all the values in the table
VAL_DTYPE** HT_values(HT* table) {

	// Create the return array
	VAL_DTYPE** values = (VAL_DTYPE**)malloc(table->num_entries * sizeof(VAL_DTYPE*));
	STYPE size = 0;

	// Run through all the hash pairs
	for (STYPE j = 0; j < table->num_buckets; j++) {

		// Pick the buckets
		LL* bucket = AL_get(table->buckets, j);

		// Run through the bucket
		ND* node = bucket->head;
		while (node != NULL) {

			// Extract the hash pair
			HP* pair = node->element;

			// Add the key to the array
			values[size++] = pair->value;

			node = node->next;
		}
	}
	return values;
}
