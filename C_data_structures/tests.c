#include <stdio.h>
#include <stdlib.h>
#include "array_list.h"

void assert_ATYPE(ATYPE a, ATYPE b, char* title) {

	if (!(a == b)) {
		printf("ATYPE assertion failure at section %s.\n", title);
		exit(0);
	}
	return;
}

void assert_DTYPE(DTYPE a, DTYPE b, char* title) {

	if (!(a == b)) {
		printf("DTYPE assertion failure at section %s.\n", title);
		exit(0);
	}
	return;
}

void assert_BOOL(BOOL a, BOOL b, char* title) {

	if (!(a == b)) {
		printf("BOOL assertion failure at section %s.\n", title);
		exit(0);
	}
	return;
}

int main() {

	// Conduct array list unit tests
	printf("===== CONDUCTING ARRAY LIST UNIT TESTS =====\n");

	// new_AL()
	ATYPE capacity = 0;
	AL* list = new_AL(capacity);
	assert_ATYPE(list->size, 0, "new_AL()");
	assert_ATYPE(list->capacity, DEFAULT_CAP, "new_AL()");

	capacity = 5;
	list = new_AL(capacity);
	assert_ATYPE(list->size, 0, "new_AL()");
	assert_ATYPE(list->capacity, capacity, "new_AL()");

	for (ATYPE j = 0; j < capacity; j++)
		list->array[j] = 0;     // Ensure no segfaults

	// All tests pass
	printf("===== ALL TESTS HAVE PASSED! =====\n");
	return 0;
}