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
BOOL integer_equals(const void * a, const void * b) {

	// Cast into proper type
	Integer* one = (Integer*)a;
	Integer* two = (Integer*)b;

	// Compare
	return (one->entry == two->entry);
}

BOOL double_equals(const void * a, const void * b) {

	// Cast into proper type
	Double* one = (Double*)a;
	Double* two = (Double*)b;

	// Compare
	return (fabs(one->entry - two->entry) < EPSILON);
}

BOOL string_equals(const void * a, const void * b) {

	// Cast into proper type
	String* one = (String*)a;
	String* two = (String*)b;

	// Compare
	return !strcmp(one->entry, two->entry);
}

// Recyclers
void free_integer(Integer* wrapper) {

	free(wrapper);
	return;
}

void free_double(Double* wrapper) {

	free(wrapper);
	return;
}

void free_string(String* wrapper) {

	free(wrapper->entry);
	free(wrapper);
	return;
}

