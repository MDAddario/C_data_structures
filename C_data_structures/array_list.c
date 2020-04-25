#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array_list.h"

// Constructor
AL* new_AL(int capacity) {
	
	// Allocate the memory for an array list
	AL* list = (AL*)malloc(sizeof(AL));
	
	// Format the capacity
	if (capacity < 1)
		list->capacity = 10;
	else
		list->capacity = capacity;
	
	// Create the hidden array
	list->array = (DTYPE*)malloc(list->capacity * sizeof(DTYPE));
	
	// Start with zero elements
	list->size = 0;
	return list;
}

// Add element to the array list at given position
void AL_add_at(AL* list, DTYPE value, int index) {
	
	// Expand array if needed
	if (list->size == list->capacity) {
		list->capacity *= 2;
		list->array = (DTYPE*)realloc(list->array, list->capacity * sizeof(DTYPE));
	}
	
	// Displace all elements that are after the index
	for (int j = list->size - 1; j >= index; j--)
		list->array[j + 1] = list->array[j];
	
	// Add the value
	list->array[index] = value;
	list->size++;
	return;
}

// Add element to the start of the array list
void AL_add_start(AL* list, DTYPE value) {
	
	// Add to position zero
	AL_add_at(list, value, 0);
	return;
}

// Add element to the end of the array list
void AL_add_end(AL* list, DTYPE value) {
	
	// Add to position zero
	AL_add_at(list, value, list->size);
	return;
}

// Clear the list
void AL_clear(AL* list) {
	
	// Set size to zero
	list->size = 0;
	return;
}

// Check if the list contains a value
int AL_contains(AL* list, DTYPE value) {
	
	// Find index value
	int index = AL_index_of(list, value);
	
	// Value not in list
	if (index == -1)
		return 0
	
	// Value in list
	return 1;
}
}

// Return an element from the list
DTYPE AL_get(AL* list, int index) {
	
	// Retrieve element from array
	return list->array[index];
}

// Return the index corresponding to a value
int AL_index_of(AL* list, DTYPE value) {
	
	// Scan the array
	for (int j = 0; j < list->size; j++)
		if (list->array[j] == value)
			return j;
	return -1;
}

// Determine if array is empty
int AL_is_empty(AL* list) {

	return !array->size;
}

// Remove element at given index
void AL_remove_at(AL* list, int index) {
	
	// Shift all the elements back
	for (int j = index; j < list->size; j++)
		list->array[j] = list->array[j + 1];
	
	// Reduce the size
	list->size--;
	return;
}

// Remove a given value from list
int AL_remove_value(AL* list, DTYPE value) {
	
	// Find index value
	int index = AL_index_of(list, value);
	
	// Value not in list
	if (index == -1)
		return 0
	
	// Value in list
	AL_remove_at(list, j);
	return 1;
}

// Determine the size of the list
int AL_size(AL* list) {
	return list->size;
}

// Conduct unit tests for the array list package
int main(int argc, char* argv[]) {
	
	
	
	
	return 0;
}