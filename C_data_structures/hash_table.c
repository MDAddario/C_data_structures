#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

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

// Retrieve key
KEY_DTYPE HP_get_key(HP* pair) {
	return HP->key;
}

// Retrieve value
VAL_DTYPE HP_get_value(HP* pair) {
	return HP->value;
}

// Set key
void HP_set_key(HP* pair, KEY_DTYPE key) {
	HP->key = key;
	return;
}

// Set value
void HP_set_value(HP* pair, VAL_DTYPE value) {
	HP->value = value;
	return;
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
		AL_add(table->buckets, new_LL());

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
	AS_TYPE hash_value = KEY_HASH(key, table->num_buckets);

	// Isolate the bucket in question
	LL* bucket = AL_get(table->buckets, hash_value);

	// Run through the bucket nodes
	ND* node = bucket->head;
	while (node != NULL) {

		// Extract the hash pair
		HP* pair = node->element;

		// Check if key already exists
		if (KEY_DTYPE_EQUALS((void*)&(pair->key), (void*)&(key)) {

			// Update value and return old value
			VAL_DTYPE old_value = pair->value;
			pair->value = value;
			return old_value;
		}

		node = node->next;
	}

	// Add hash_pair to bucket
	LL_add(bucket, new_HP(key, value));
	table->num_entries++;

	// Consider rehashing
	if (((double) table->num_entries) / table->num_buckets > max_load)
		HT_rehash(table);

	return VAL_DTYPE_NULL;
}

// Get a value from the table
VAL_DTYPE HT_get(HT* table, KEY_DTYPE key) {

	// Retrieve hash_value
	AS_TYPE hash_value = KEY_HASH(key, table->num_buckets);

	// Isolate the bucket in question
	LL* bucket = AL_get(table->buckets, hash_value);

	// Run through the bucket nodes
	ND* node = bucket->head;
	while (node != NULL) {

		// Extract the hash pair
		HP* pair = node->element;

		// Check if key already exists
		if (KEY_DTYPE_EQUALS((void*)&(pair->key), (void*)&(key)) {

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
	AS_TYPE hash_value = KEY_HASH(key, table->num_buckets);

	// Isolate the bucket in question
	LL* bucket = AL_get(table->buckets, hash_value);

	// Run through the bucket nodes
	ND* node = bucket->head;
	while (node != NULL) {

		// Extract the hash pair
		HP* pair = node->element;

		// Check if key already exists
		if (KEY_DTYPE_EQUALS((void*)&(pair->key), (void*)&(key)) {

			// Delete hash_pair and return value
			VAL_DTYPE value = pair->value;
			LL_remove(bucket, pair);
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
	this.numBuckets *= 2;

	// Construct the new buckets
	ArrayList<LinkedList<HashPair<K,V>>> newBuckets = new ArrayList<>(this.numBuckets);
	for (int i = 0; i < this.numBuckets; i++)
		newBuckets.add(new LinkedList<>());

	// Migrate all the old hashPairs
	for (LinkedList<HashPair<K,V>> oldBucket: this.buckets)
		for (HashPair<K,V> hashPair: oldBucket) {

			// Retrieve hashValue
			int hashValue = this.hashFunction(hashPair.getKey());

			// Isolate the new bucket in question
			LinkedList<HashPair<K,V>> newBucket = newBuckets.get(hashValue);

			// Add the hashPair to the new buckets
			newBucket.add(hashPair);
		}

	// Update the buckets
	this.buckets = newBuckets;

}

KEY_DTYPE* HT_keys(HT* table) {

	// Create the return array list
	ArrayList<K> keys = new ArrayList<>(this.numEntries);

	// Run through all the hashPairs
	for (LinkedList<HashPair<K,V>> bucket: this.buckets)
		for (HashPair<K,V> hashPair: bucket)
			keys.add(hashPair.getKey());

	return keys;

}

VAL_DTYPE* HT_values(HT* table) {

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

}
