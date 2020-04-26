#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

// Constructor
LL* new_LL(ATYPE capacity) {

	// Allocate the memory for a linked list
	LL* list = (LL*)malloc(sizeof(LL));

	// Start with zero elements
	list->head = null;
	list->tail = null;
	list->size = 0;
	return list;
}

// Destructor
void free_LL(LL* list) {

	// Free all the nodes
	ND* node = list->head;
	ND* next;

	while (node != null) {

		next = node->next;
		free(node);
		node = next;
	}

	// Free the linked list
	free(list);
	return;
}

// Add element to the linked list at given position
BOOL LL_add_at(LL* list, DTYPE value, ATYPE index) {

	// Make sure index makes sense
	if (index > list->size || index < 0) {
		printf("Index specified for LL_add_at() is rubbish.\n");
		return FALSE;
	}

	// Handle head and tail separately
	if (index == 0) {
		LL_add_start(list, value);
		return TRUE;
	}
	if (index == list->size) {
		LL_add_end(list, value);
		return TRUE;
	}

	// Choose whether to start from the head or the tail
	ND* prev, next;
	if (index < list->size / 2) {

		prev = list->head;
		for (ATYPE j = 0; j < index - 1; j++)
			prev = prev->next;
		next = prev->next;

	}
	else {

		next = list->tail;
		for (ATYPE j = index; j < list->size - 1; j++)
			next = next->prev;
		prev = next->prev;

	}

	// Create new node
	ND* node = (ND*)malloc(sizeof(ND));
	node->prev = prev;
	node->next = next;
	node->element = value;

	// Connect the network
	prev->next = node;
	next->prev = node;
	list->size++;
	return TRUE;
}

// Add element to the start of the array list
void LL_add_start(LL* list, DTYPE value) {

	// Create new node
	ND* node = (ND*)malloc(sizeof(ND));
	node->prev = null;
	node->next = list->head;
	node->element = value;

	// Update the linked list
	list->head->prev = node;
	list->head = node;
	list->size++;
	return;
}

// Add element to the end of the array list
void LL_add_end(LL* list, DTYPE value) {

	// Create new node
	ND* node = (ND*)malloc(sizeof(ND));
	node->prev = list->tail;
	node->next = null;
	node->element = value;

	// Update the linked list
	list->tail->next = node;
	list->tail = node;
	list->size++;
	return;
}

// Clear the list
void LL_clear(LL* list) {

	// Set size to zero
	list->size = 0;
	return;
}

// Check if the list contains a value
BOOL LL_contains(LL* list, DTYPE value) {

	// Find index value
	ATYPE index = LL_index_of(list, value);

	// Value not in list
	if (index == -1)
		return FALSE;

	// Value in list
	return TRUE;
}

// Return an element from the list
DTYPE LL_get(LL* list, ATYPE index) {

	// Make sure index makes sense
	if (index >= list->size || index < 0) {
		printf("Index specified for LL_get() is rubbish.\n");
		return 0;
	}

	// Retrieve element from array
	return list->array[index];
}

// Return the index corresponding to a value
ATYPE LL_index_of(LL* list, DTYPE value) {

	// Scan the array
	for (ATYPE j = 0; j < list->size; j++)
		if (list->array[j] == value)
			return j;
	return -1;
}

// Determine if array is empty
BOOL LL_is_empty(LL* list) {

	return !list->size;
}

// Remove element at given index
BOOL LL_remove_at(LL* list, ATYPE index) {

	// Make sure index makes sense
	if (index >= list->size || index < 0) {
		printf("Index specified for LL_remove_at() is rubbish.\n");
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
BOOL LL_remove_value(LL* list, DTYPE value) {

	// Find index value
	ATYPE index = LL_index_of(list, value);

	// Value not in list
	if (index == -1)
		return FALSE;

	// Value in list
	return LL_remove_at(list, index);
}

// Determine the size of the list
ATYPE LL_size(LL* list) {
	return list->size;
}
