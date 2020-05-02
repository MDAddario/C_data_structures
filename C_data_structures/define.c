#include "define.h"

BOOL short_equals(const void * a, const void * b) {
	return (*(short*)a == *(short*)b);
}

BOOL int_equals(const void * a, const void * b) {
	return (*(int*)a == *(int*)b);
}

BOOL long_equals(const void * a, const void * b) {
	return (*(long*)a == *(long*)b);
}

BOOL double_equals(const void * a, const void * b) {
	return (fabs(*(double*)a - *(double*)b) < EPSILON);
}
