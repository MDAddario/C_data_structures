#include <stdio.h>
#include <stdlib.h>
#include "array_list.h"

// Constructor
AL* new_AL(ATYPE capacity) {

	// Allocate the memory for an array list
	AL* list = (AL*)malloc(sizeof(AL));

	// Format the capacity
	if (capacity < 1)
		list->capacity = DEFAULT_CAP;
	else
		list->capacity = capacity;

	// Create the hidden array
	list->array = (DTYPE*)malloc(list->capacity * sizeof(DTYPE));

	// Start with zero elements
	list->size = 0;
	return list;
}

// Destructor
void free_AL(AL* list) {

	// Free the underlying array
	free(list->array);

	// Free the array list
	free(list);
	return;
}

// Add element to the array list at given position
BOOL AL_add_at(AL* list, DTYPE value, ATYPE index) {

	// Make sure index makes sense
	if (index > list->size || index < 0) {
		printf("Index specified for AL_add_at() is rubbish.\n");
		return FALSE;
	}

	// Expand array if needed
	if (list->size == list->capacity) {
		list->capacity *= 2;
		list->array = (DTYPE*)realloc(list->array, list->capacity * sizeof(DTYPE));
	}

	// Displace all elements that are after the index
	for (ATYPE j = list->size - 1; j >= index; j--)
		list->array[j + 1] = list->array[j];

	// Add the value
	list->array[index] = value;
	list->size++;
	return TRUE;
}

// Add element to the start of the array list
void AL_add_start(AL* list, DTYPE value) {

	// Add to position zero
	AL_add_at(list, value, 0);
	return;
}

// Add element to the end of the array list
void AL_add_end(AL* list, DTYPE value) {

	// Add to last position
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
BOOL AL_contains(AL* list, DTYPE value) {

	// Find index value
	ATYPE index = AL_index_of(list, value);

	// Value not in list
	if (index == -1)
		return FALSE;

	// Value in list
	return TRUE;
}

// Return an element from the list
DTYPE AL_get(AL* list, ATYPE index) {

	// Retrieve element from array
	return list->array[index];
}

// Return the index corresponding to a value
ATYPE AL_index_of(AL* list, DTYPE value) {

	// Scan the array
	for (ATYPE j = 0; j < list->size; j++)
		if (list->array[j] == value)
			return j;
	return -1;
}

// Determine if array is empty
BOOL AL_is_empty(AL* list) {

	return !list->size;
}

// Remove element at given index
void AL_remove_at(AL* list, ATYPE index) {

	// Make sure index makes sense
	if (index >= list->size || index < 0) {
		printf("Index specified for AL_remove_at() is rubbish.\n");
		return FALSE;
	}

	// Shift all the elements back
	for (ATYPE j = index; j < list->size; j++)
		list->array[j] = list->array[j + 1];

	// Reduce the size
	list->size--;
	return TRUE;
}

// Remove a given value from list
BOOL AL_remove_value(AL* list, DTYPE value) {

	// Find index value
	ATYPE index = AL_index_of(list, value);

	// Value not in list
	if (index == -1)
		return FALSE;

	// Value in list
	AL_remove_at(list, index);
	return TRUE;
}

// Determine the size of the list
ATYPE AL_size(AL* list) {
	return list->size;
}
