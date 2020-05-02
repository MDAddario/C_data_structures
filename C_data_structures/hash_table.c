#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

// Constructor
AL* new_AL(AL_STYPE capacity) {

	// Initialize fields
	this.numEntries = 0;
	this.numBuckets = initialCapacity;

	// Take care of an annoying case
	if (this.numBuckets <= 0)
		this.numBuckets = 10;

	this.buckets = new ArrayList<>(this.numBuckets);

	// Construct the buckets
	for (int i = 0; i < this.numBuckets; i++)
		this.buckets.add(new LinkedList<>());

}

// Destructor
void free_HP(AL* list) {
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
