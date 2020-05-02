#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "define.h"

// Constructors
Integer* new_integer(int entry) {

	// Allocate memory
	Integer* wrapper = (Integer*)malloc(sizeof(Integer));

	// Init field
	wrapper->entry = entry;

	return wrapper;
}

Double* new_double(double entry) {

	// Allocate memory
	Double* wrapper = (Double*)malloc(sizeof(Double));

	// Init field
	wrapper->entry = entry;

	return wrapper;
}

String* new_string(char* entry) {

	// Allocate memory
	String* wrapper = (String*)malloc(sizeof(String));

	// Copy the field entry
	long size = strlen(entry) + 1l; // Include the null character ofc
	wrapper->entry = (char*)malloc(size * sizeof(char));
	strcpy(wrapper->entry, entry);

	return wrapper;
}

// Comparison methods
BOOL integer_equals(Integer* a, Integer* b) {
	return a->entry == b->entry;
}

BOOL double_equals(Double* a, Double* b) {
	return fabs(a->entry - b->entry) < EPSILON;
}

BOOL string_equals(String* a, String* b) {
	return !strcmp(a->entry, b->entry);
}

// Recyclers
void integer_free(Integer* wrapper) {

	free(wrapper);
	return;
}

void double_free(Double* wrapper) {

	free(wrapper);
	return;
}

void string_free(String* wrapper) {

	free(wrapper->entry);
	free(wrapper);
	return;
}

