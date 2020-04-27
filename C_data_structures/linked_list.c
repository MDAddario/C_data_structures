#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

// Constructor
LL* new_LL() {

	// Allocate the memory for a linked list
	LL* list = (LL*)malloc(sizeof(LL));

	// Start with zero elements
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return list;
}

// Destructor
void free_LL(LL* list) {

	// Free all the nodes
	LL_clear(list);

	// Free the linked list
	free(list);
	return;
}

// Add element to the linked list at given position
BOOL LL_add_at(LL* list, LL_DTYPE value, LL_STYPE index) {

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

	// Isolate neighboring nodes
	ND* next = LL_get_node(list, index);
	ND* prev = next->prev;

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
void LL_add_start(LL* list, LL_DTYPE value) {

	// Create new node
	ND* node = (ND*)malloc(sizeof(ND));
	node->prev = NULL;
	node->element = value;

	// Update the linked list
	if (LL_is_empty(list)) {

		node->next = NULL;
		list->head = node;
		list->tail = node;

	} else {

		node->next = list->head;
		list->head->prev = node;
		list->head = node;
	}

	list->size++;
	return;
}

// Add element to the end of the array list
void LL_add_end(LL* list, LL_DTYPE value) {

	// If array is empty, add at start
	if (LL_is_empty(list)) {
		LL_add_start(list, value);
		return;
	}

	// Create new node
	ND* node = (ND*)malloc(sizeof(ND));
	node->prev = list->tail;
	node->next = NULL;
	node->element = value;

	// Update the linked list
	list->tail->next = node;
	list->tail = node;
	list->size++;
	return;
}

// Clear the list
void LL_clear(LL* list) {

	// Free all the nodes
	ND* node = list->head;
	ND* next;

	while (node != NULL) {

		next = node->next;
		free(node);
		node = next;
	}

	// Set size to zero
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return;
}

// Check if the list contains a value
BOOL LL_contains(LL* list, LL_DTYPE value) {

	// Find index value
	LL_STYPE index = LL_index_of(list, value);

	// Value not in list
	if (index == INDEX_NOT_FOUND)
		return FALSE;

	// Value in list
	return TRUE;
}

// Return a node from the list
ND* LL_get_node(LL* list, LL_STYPE index) {

	// Make sure index makes sense
	if (index >= list->size || index < 0) {
		printf("Index specified for LL_get_node() is rubbish.\n");
		return NULL;
	}

	// Choose whether to start from the head or the tail
	ND* node;
	if (index < list->size / 2) {

		node = list->head;
		for (LL_STYPE j = 0; j < index; j++)
			node = node->next;

	} else {

		node = list->tail;
		for (LL_STYPE j = index; j < list->size - 1; j++)
			node = node->prev;

	}
	return node;
}

// Return an element from the list
LL_DTYPE LL_get(LL* list, LL_STYPE index) {

	// Locate the node
	ND* node = LL_get_node(list, index);

	if (node == NULL)
		return LL_DTYPE_NULL;
	return node->element;
}

// Return the index corresponding to a value
LL_STYPE LL_index_of(LL* list, LL_DTYPE value) {

	// Run through the nodes
	ND* node = list->head;
	LL_STYPE index = 0;

	while (node != NULL) {

		if (LL_DTYPE_EQUALS((void*)&(node->element), (void*)&(value)))
			return index;
		node = node->next;
		index++;
	}
	return INDEX_NOT_FOUND;
}

// Determine if array is empty
BOOL LL_is_empty(LL* list) {

	return !LL_size(list);
}

// Remove element at given index
BOOL LL_remove_at(LL* list, LL_STYPE index) {

	// Ensure there is a value to remove
	if (LL_is_empty(list)) {
		printf("Cannot remove elements from an empty list.\n");
		return FALSE;
	}

	// Make sure index makes sense
	if (index >= list->size || index < 0) {
		printf("Index specified for LL_remove_at() is rubbish.\n");
		return FALSE;
	}

	// Handle head and tail separately
	if (index == 0) 
		return LL_remove_start(list);

	if (index == list->size - 1)
		return LL_remove_end(list);

	// Find the node to remove
	ND* node = LL_get_node(list, index);
	ND* prev = node->prev;
	ND* next = node->next;

	// Re-stitch the network
	free(node);
	prev->next = next;
	next->prev = prev;

	// Reduce the size
	list->size--;
	return TRUE;
}

// Remove first value
BOOL LL_remove_start(LL* list) {

	// Ensure there is a value to remove
	if (LL_is_empty(list)) {
		printf("Cannot remove elements from an empty list.\n");
		return FALSE;
	}

	// Deal with single remaining node
	if (LL_size(list) == 1) {

		free(list->head);
		list->head = NULL;
		list->tail = NULL;

	} else {

		// Isolate and free the head
		ND* head = list->head;
		list->head = list->head->next;
		free(head);
	}

	list->size--;
	return TRUE;
}

// Remove last value
BOOL LL_remove_end(LL* list) {

	// Ensure there is a value to remove
	if (LL_is_empty(list)) {
		printf("Cannot remove elements from an empty list.\n");
		return FALSE;
	}

	// Deal with single remaining node
	if (LL_size(list) == 1)
		return LL_remove_start(list);

	// Isolate and free the tail
	ND* tail = list->tail;
	list->tail = list->tail->prev;
	free(tail);
	list->size--;

	return TRUE;
}

// Remove a given value from list
BOOL LL_remove_value(LL* list, LL_DTYPE value) {

	// Find index value
	LL_STYPE index = LL_index_of(list, value);

	// Value not in list
	if (index == INDEX_NOT_FOUND)
		return FALSE;

	// Value in list
	return LL_remove_at(list, index);
}

// Determine the size of the list
LL_STYPE LL_size(LL* list) {
	return list->size;
}
