#include <math.h>
#include <string.h>
#include "define.h"

// Constructors
Integer* new_integer(int value) {

	// Allocate memory
	Integer* wrapper = (Integer*)malloc(sizeof(Integer));

	// Init field
	wrapper->value = value;

	return wrapper;
}

Double* new_double(double value) {

	// Allocate memory
	Double* wrapper = (Double*)malloc(sizeof(Double));

	// Init field
	wrapper->value = value;

	return wrapper;
}

String* new_string(char* value) {

	// Allocate memory
	String* wrapper = (String*)malloc(sizeof(String));

	// Copy the field value
	long size = strlen(value) + 1l; // Include the null character ofc
	wrapper->value = (char*)malloc(size * sizeof(char));
	strcpy(wrapper->value, value);

	return wrapper;
}

// Comparison methods
BOOL integer_equals(const void * a, const void * b) {

	// Cast into proper type
	Integer* one = (Integer*)a;
	Integer* two = (Integer*)b;

	// Compare
	return (one->value == two->value);
}

BOOL double_equals(const void * a, const void * b) {

	// Cast into proper type
	Double* one = (Double*)a;
	Double* two = (Double*)b;

	// Compare
	return (fabs(one->value - two->value) < EPSILON);
}

BOOL string_equals(const void * a, const void * b) {

	// Cast into proper type
	String* one = (String*)a;
	String* two = (String*)b;

	// Compare
	return !strcmp(one->value, two->value);
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

	free(wrapper->value);
	free(wrapper);
	return;
}

