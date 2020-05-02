#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

// Hash function for strings
AL_STYPE string_hash (char* string, AL_STYPE num_buckets) {
	return 0;
	//return Math.abs(key.hashCode())%this.numBuckets;
}

// Constructor
HT* new_HT(AL_STYPE capacity) {

	// Allocate the memory for the hash table
	HT* table = (HT*)malloc(sizeof(HT));

	// Initialize fields
	table->num_entries = 0;
	table->num_buckets = capacity;
	table->max_load    = 0.75;

	// Create the array list
	table->buckets = new_AL(table->num_buckets);

	// Construct the buckets
	for (AL_STYPE j = 0; j < table->num_buckets; j++)
		AL_add_end(table->buckets, new_LL());

	// Return the table
	return table;
}

// Destructor
void free_HT(HT* table) {

	// Free the buckets
	for (AL_STYPE j = 0; j < table->num_buckets; j++)
		free_LL(AL_get(table->buckets, j));

	// Free the array list
	free_AL(table->buckets);

	// Free the table
	free(table);
	return;
}

// Put a hash pair into the table
VAL_DTYPE HT_put(HT* table, KEY_DTYPE key, VAL_DTYPE value) {

	// Retrieve hash_value
	AL_STYPE hash_value = KEY_HASH(key, table->num_buckets);

	// Isolate the bucket in question
	LL* bucket = AL_get(table->buckets, hash_value);

	// Run through the bucket nodes
	ND* node = bucket->head;
	while (node != NULL) {

		// Extract the hash pair
		HP* pair = node->element;

		// Check if key already exists
		if (KEY_DTYPE_EQUALS((void*)&(pair->key), (void*)&(key))) {

			// Update value and return old value
			VAL_DTYPE old_value = pair->value;
			pair->value = value;
			return old_value;
		}

		node = node->next;
	}

	// Add hash_pair to bucket
	LL_add_end(bucket, new_HP(key, value));
	table->num_entries++;

	// Consider rehashing
	if (((double) table->num_entries) / table->num_buckets > table->max_load)
		HT_rehash(table);

	return VAL_DTYPE_NULL;
}

// Get a value from the table
VAL_DTYPE HT_get(HT* table, KEY_DTYPE key) {

	// Retrieve hash_value
	AL_STYPE hash_value = KEY_HASH(key, table->num_buckets);

	// Isolate the bucket in question
	LL* bucket = AL_get(table->buckets, hash_value);

	// Run through the bucket nodes
	ND* node = bucket->head;
	while (node != NULL) {

		// Extract the hash pair
		HP* pair = node->element;

		// Check if key already exists
		if (KEY_DTYPE_EQUALS((void*)&(pair->key), (void*)&(key))) {

			// Return value
			return pair->value;
		}

		node = node->next;
	}

	// Key doesn't exist
	return VAL_DTYPE_NULL;
}

// Remove a pair from the table
VAL_DTYPE HT_remove(HT* table, KEY_DTYPE key) {

	// Retrieve hash_value
	AL_STYPE hash_value = KEY_HASH(key, table->num_buckets);

	// Isolate the bucket in question
	LL* bucket = AL_get(table->buckets, hash_value);

	// Run through the bucket nodes
	ND* node = bucket->head;
	while (node != NULL) {

		// Extract the hash pair
		HP* pair = node->element;

		// Check if key already exists
		if (KEY_DTYPE_EQUALS((void*)&(pair->key), (void*)&(key))) {

			// Delete hash_pair and return value
			VAL_DTYPE value = pair->value;
			LL_remove_value(bucket, pair);
			table->num_entries--;
			return value;
		}

		node = node->next;
	}

	// Key doesn't exist
	return VAL_DTYPE_NULL;
}

// Add more buckets to the table to improve lookup times
void HT_rehash(HT* table) {

	// Double capacity
	table->num_buckets *= 2;

	// Construct the new buckets
	AL* new_buckets = new_AL(table->num_buckets);
	for (AL_STYPE j = 0; j < table->num_buckets; j++)
		AL_add_end(new_buckets, new_LL());

	// Migrate all the old hash_pairs
	for (AL_STYPE j = 0; j < table->num_buckets / 2; j++) {

		// Pick out the buckets one by one
		LL* old_bucket = AL_get(table->buckets, j);

		// Run through the bucket nodes
		ND* node = old_bucket->head;
		while (node != NULL) {

			// Extract the hash pair
			HP* pair = node->element;

			// Retrieve hash_value
			AL_STYPE hash_value = KEY_HASH(pair->key, table->num_buckets);

			// Isolate the bucket in question
			LL* new_bucket = AL_get(new_buckets, hash_value);

			// Add the hash_pair to the new bucket
			LL_add_end(new_bucket, pair);

			node = node->next;
		}
	}

	// Free the buckets
	for (AL_STYPE j = 0; j < table->num_buckets / 2; j++)
		free_LL(AL_get(table->buckets, j));

	// Free the array list
	free_AL(table->buckets);

	// Update the buckets
	table->buckets = new_buckets;
	return;
}

// Generate an array with all the keys in the table
KEY_DTYPE* HT_keys(HT* table) {

	return NULL;

	/*
	// Create the return array list
	ArrayList<K> keys = new ArrayList<>(this.numEntries);

	// Run through all the hashPairs
	for (LinkedList<HashPair<K,V>> bucket: this.buckets)
		for (HashPair<K,V> hashPair: bucket)
			keys.add(hashPair.getKey());

	return keys;
	*/
}

// Generate an array with all the values in the table
VAL_DTYPE* HT_values(HT* table) {

	return NULL;

	/*
	// Keep track of existing values
	MyHashTable<V, Boolean> duplicateChecker = new MyHashTable<>(this.numEntries);

	// Create the return array list
	ArrayList<V> values = new ArrayList<>(this.numEntries);

	// Run through all the hashPairs
	for (LinkedList<HashPair<K,V>> bucket: this.buckets)
		for (HashPair<K,V> hashPair: bucket) {

			// Get the value
			V value = hashPair.getValue();

			// Add unique copy to array list
			if (duplicateChecker.put(value, true) == null)
				values.add(value);
		}
	return values;
	*/
}
