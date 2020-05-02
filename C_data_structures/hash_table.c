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
		free(AL_get(table->buckets, j));

	// Free the array list
	free(table->buckets);

	// Free the table
	free(table);
	return;
}

VAL_DTYPE HT_put(HT* table, KEY_DTYPE key, VAL_DTYPE value) {

	// Retrieve hashValue
	int hashValue = this.hashFunction(key);

	// Isolate the bucket in question
	LinkedList<HashPair<K,V>> bucket = this.buckets.get(hashValue);

	// Check if key already exists
	for (HashPair<K,V> hashPair: bucket) {
		if (hashPair.getKey().equals(key)) {

			// Update value and return old value
			V oldValue = hashPair.getValue();
			hashPair.setValue(value);
			return oldValue;
		}
	}

	// Add hashPair to bucket
	bucket.add(new HashPair<>(key, value));
	this.numEntries += 1;

	// Consider rehashing
	if (((double) this.numEntries) / this.numBuckets > MAX_LOAD_FACTOR)
		this.rehash();

	return null;

}

VAL_DTYPE HT_get(HT* table, KEY_DTYPE key) {

	// Retrieve hashValue
	int hashValue = this.hashFunction(key);

	// Isolate the bucket in question
	LinkedList<HashPair<K,V>> bucket = this.buckets.get(hashValue);

	// Check if key already exists
	for (HashPair<K,V> hashPair: bucket) {
		if (hashPair.getKey().equals(key)) {

			return hashPair.getValue();
		}
	}
	// Key doesn't exist
	return null;

}

VAL_DTYPE HT_remove(HT* table, KEY_DTYPE key) {

	// Retrieve hashValue
	int hashValue = this.hashFunction(key);

	// Isolate the bucket in question
	LinkedList<HashPair<K,V>> bucket = this.buckets.get(hashValue);

	// Check if key already exists
	for (HashPair<K,V> hashPair: bucket) {
		if (hashPair.getKey().equals(key)) {

			// Delete hashPair and return value
			V value = hashPair.getValue();
			bucket.remove(hashPair);
			this.numEntries -= 1;
			return value;
		}
	}
	// Key doesn't exist
	return null;

}

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
