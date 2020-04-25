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

/*****************************************************************/

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

	// free_AL()
	AL* list_2 = new_AL(capacity);
	free_AL(list_2);

	// AL_add_start()
	for (ATYPE size = 1; size <= capacity; size++) {

		DTYPE value = (DTYPE)size + 100;
		AL_add_start(list, value);
		assert_ATYPE(list->size, size, "AL_add_start()");
		assert_ATYPE(list->capacity, capacity, "AL_add_start()");
	}

	// AL_get()
	for (ATYPE index = 0; index < capacity; index++) {

		DTYPE value = AL_get(list, index);
		assert_DTYPE(value, 100 + capacity - index, "AL_get()");
		assert_ATYPE(list->size, capacity, "AL_get()");
		assert_ATYPE(list->capacity, capacity, "AL_get()");
	}

	// AL_add_end()
	for (ATYPE size = 1; size <= capacity; size++) {

		DTYPE value = (DTYPE)size + 200;
		AL_add_end(list, value);
		assert_ATYPE(list->size, size + capacity, "AL_end()");
		assert_ATYPE(list->capacity, 2 * capacity, "AL_end()");
	}

	// AL_get()
	for (ATYPE index = 0; index < capacity; index++) {

		DTYPE value = AL_get(list, index + capacity);
		assert_DTYPE(value, 200 + index + 1, "AL_get()");
		assert_ATYPE(list->size, 2 * capacity, "AL_get()");
		assert_ATYPE(list->capacity, 2 * capacity, "AL_get()");
	}



/*****************************************************************/

	// All tests pass
	printf("===== ALL TESTS HAVE PASSED! =====\n");
	return 0;
}