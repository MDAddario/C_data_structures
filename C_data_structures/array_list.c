#include <stdio.h>
#include <stdlib.h>
#include "array_list.h"

// Constructor
AL* new_AL(AL_STYPE capacity) {

	// Allocate the memory for an array list
	AL* list = (AL*)malloc(sizeof(AL));

	// Format the capacity
	if (capacity < 1)
		list->capacity = DEFAULT_CAP;
	else
		list->capacity = capacity;

	// Create the hidden array
	list->array = (AL_DTYPE*)malloc(list->capacity * sizeof(AL_DTYPE));

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
BOOL AL_add_at(AL* list, AL_DTYPE value, AL_STYPE index) {

	// Make sure index makes sense
	if (index > list->size || index < 0) {
		printf("Index specified for AL_add_at() is rubbish.\n");
		return FALSE;
	}

	// Expand array if needed
	if (list->size == list->capacity) {
		list->capacity *= 2;
		list->array = (AL_DTYPE*)realloc(list->array, list->capacity * sizeof(AL_DTYPE));
	}

	// Displace all elements that are after the index
	for (AL_STYPE j = list->size - 1; j >= index; j--)
		list->array[j + 1] = list->array[j];

	// Add the value
	list->array[index] = value;
	list->size++;
	return TRUE;
}

// Add element to the start of the array list
void AL_add_start(AL* list, AL_DTYPE value) {

	// Add to position zero
	AL_add_at(list, value, 0);
	return;
}

// Add element to the end of the array list
void AL_add_end(AL* list, AL_DTYPE value) {

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
BOOL AL_contains(AL* list, AL_DTYPE value) {

	// Find index value
	AL_STYPE index = AL_index_of(list, value);

	// Value not in list
	if (index == INDEX_NOT_FOUND)
		return FALSE;

	// Value in list
	return TRUE;
}

// Return an element from the list
AL_DTYPE AL_get(AL* list, AL_STYPE index) {

	// Make sure index makes sense
	if (index >= list->size || index < 0) {
		printf("Index specified for AL_get() is rubbish.\n");
		return AL_DTYPE_NULL;
	}

	// Retrieve element from array
	return list->array[index];
}

// Return the index corresponding to a value
AL_STYPE AL_index_of(AL* list, AL_DTYPE value) {

	// Scan the array
	for (AL_STYPE j = 0; j < list->size; j++)
		if (list->array[j] == value)
			return j;
	return INDEX_NOT_FOUND;
}

// Determine if array is empty
BOOL AL_is_empty(AL* list) {

	return !AL_size(list);
}

// Remove element at given index
BOOL AL_remove_at(AL* list, AL_STYPE index) {

	// Ensure there is a value to remove
	if (AL_is_empty(list)) {
		printf("Cannot remove elements from an empty list.\n");
		return FALSE;
	}

	// Make sure index makes sense
	if (index >= list->size || index < 0) {
		printf("Index specified for AL_remove_at() is rubbish.\n");
		return FALSE;
	}

	// Shift all the elements back
	for (AL_STYPE j = index; j < list->size; j++)
		list->array[j] = list->array[j + 1];

	// Reduce the size
	list->size--;
	return TRUE;
}

// Remove first value
BOOL AL_remove_start(AL* list) {

	return AL_remove_at(list, 0);
}

// Remove last value
BOOL AL_remove_end(AL* list) {

	return AL_remove_at(list, list->size - 1);
}

// Remove a given value from list
BOOL AL_remove_value(AL* list, AL_DTYPE value) {

	// Find index value
	AL_STYPE index = AL_index_of(list, value);

	// Value not in list
	if (index == INDEX_NOT_FOUND)
		return FALSE;

	// Value in list
	return AL_remove_at(list, index);
}

// Determine the size of the list
AL_STYPE AL_size(AL* list) {
	return list->size;
}
