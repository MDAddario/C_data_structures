#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

// Constructor
AL* new_AL(AL_STYPE capacity) {
}

// Destructor
void free_HP(AL* list) {
	return;
}

    public MyHashTable(int initialCapacity) {

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
    
    public int size() {
        return this.numEntries;
    }
    
    public boolean isEmpty() {
        return this.numEntries == 0;
    }
    
    public int numBuckets() {
        return this.numBuckets;
    }
    
    /**
     * Returns the buckets variable. Useful for testing  purposes.
     */
    public ArrayList<LinkedList< HashPair<K,V> > > getBuckets(){
        return this.buckets;
    }
    
    /**
     * Given a key, return the bucket position for the key. 
     */
    public int hashFunction(K key) {
        int hashValue = Math.abs(key.hashCode())%this.numBuckets;
        return hashValue;
    }
    
    /**
     * Takes a key and a value as input and adds the corresponding HashPair
     * to this HashTable. Expected average run time  O(1)
     */
    public V put(K key, V value) {

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
    
    
    /**
     * Get the value corresponding to key. Expected average runtime O(1)
     */
    
    public V get(K key) {

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
    
    /**
     * Remove the HashPair corresponding to key . Expected average runtime O(1) 
     */
    public V remove(K key) {

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
    
    
    /** 
     * Method to double the size of the hashtable if load factor increases
     * beyond MAX_LOAD_FACTOR.
     * Made public for ease of testing.
     * Expected average runtime is O(m), where m is the number of buckets
     */
    public void rehash() {

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
    
    
    /**
     * Return a list of all the keys present in this hashtable.
     * Expected average runtime is O(m), where m is the number of buckets
     */
    
    public ArrayList<K> keys() {

        // Create the return array list
        ArrayList<K> keys = new ArrayList<>(this.numEntries);

        // Run through all the hashPairs
        for (LinkedList<HashPair<K,V>> bucket: this.buckets)
            for (HashPair<K,V> hashPair: bucket)
                keys.add(hashPair.getKey());

    	return keys;
    }
    
    /**
     * Returns an ArrayList of unique values present in this hashtable.
     * Expected average runtime is O(m) where m is the number of buckets
     */
    public ArrayList<V> values() {

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