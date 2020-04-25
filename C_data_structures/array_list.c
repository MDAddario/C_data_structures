#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *   FOR THE MOMENT, ACCEPT THE FACT THAT WE ARE ONLY WORKING WITH INTEGERS
 */

// Struct for the array list
typedef struct struct_AL {

	int* array;		// Underlying array
	int size;		// Number of elements in the array
	int capacity;	// Total capacity of the array
	
} AL;

// Constructor
AL* new_AL(int capacity) {
	
	// Allocate the memory for an array list
	AL* list = (AL*)malloc(sizeof(AL));
	
	// Format the capacity
	if (capacity < 1)
		list.capacity = 10;
	else
		list.capacity = capacity;
	
	// Create the hidden array
	list.array = (int*)malloc(list.capacity * sizeof(int));
	
	// Start with zero elements
	list.size = 0;
	
	return list;
}

// Add element to the array list at given position
void AL_add_at(AL* list, int value, int index) {
	
	// Expand array if needed
	if (list.size == list.capacity) {
		list.capacity *= 2;
		list.array = (int*)realloc(list.array, list.capacity * sizeof(int));
	}
	
	// Displace all elements that are after the index
	for (int j = list.size - 1; j >= index; j--)
		list.array[j + 1] = list.array[j];
	
	// Add the value
	list.array[index] = value;
	list.size++;
	
	return;
}

// Add element to the start of the array list
void AL_add_start(AL* list, int value) {
	
	// Add to position zero
	AL_add_at(list, value, 0);
	return;
}

// Add element to the end of the array list
void AL_add_end(AL* list, int value) {
	
	// Add to position zero
	AL_add_at(list, value, list.size);
	return;
}

/*	"Method" list:
 *
 *	constructor()
 *	add_at()
 *	add_start()
 *	add_end()
 *	clear()
 *	clone()
 *	contains()
 *	get()
 *	index_of()
 *	is_empty()
 *	remove_at()
 *	remove_value()
 *	size()
 *	sort()
 */

// The main attraction
int main(int argc, char* argv[]) {
	
	
	
	
	
}