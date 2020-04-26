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

	capacity = 431;
	list = new_AL(capacity);
	assert_ATYPE(list->size, 0, "new_AL()");
	assert_ATYPE(list->capacity, capacity, "new_AL()");

	for (ATYPE j = 0; j < capacity; j++)
		list->array[j] = 0;     // Ensure no segfaults

	// free_AL()
	printf("Testing memory management: ");
	for (int i = 0; i < 10; i++) {
		for (long j = 0; j < 1000000; j++) {
			AL* list_2 = new_AL(1000000);
			free_AL(list_2);
		}
		printf("%d%% ", (i + 1) * 10);
	}
	printf("\n");

	DTYPE offsets[] = {1000, 2000, 3000};

	// AL_add_start()
	DTYPE value;
	for (ATYPE size = 1; size <= capacity; size++) {

		value = (DTYPE)size + offsets[0];
		AL_add_start(list, value);
		assert_ATYPE(list->size, size, "AL_add_start()");
		assert_ATYPE(list->capacity, capacity, "AL_add_start()");
	}

	for (ATYPE index = 0; index < capacity; index++) {

		value = list->array[index];
		assert_DTYPE(value, offsets[0] + capacity - index, "AL_add_start()");
		assert_ATYPE(list->size, capacity, "AL_add_start()");
		assert_ATYPE(list->capacity, capacity, "AL_add_start()");
	}

	// AL_add_end()
	for (ATYPE size = 1; size <= capacity; size++) {

		value = (DTYPE)size + offsets[1];
		AL_add_end(list, value);
		assert_ATYPE(list->size, size + capacity, "AL_end()");
		assert_ATYPE(list->capacity, 2 * capacity, "AL_end()");
	}

	for (ATYPE index = 0; index < capacity; index++) {

		value = list->array[index + capacity];
		assert_DTYPE(value, offsets[1] + index + 1, "AL_end()");
		assert_ATYPE(list->size, 2 * capacity, "AL_end()");
		assert_ATYPE(list->capacity, 2 * capacity, "AL_end()");
	}

	// AL_add_at()
	AL_add_at(list, offsets[2], capacity);
	assert_ATYPE(list->size, 2 * capacity + 1, "AL_add_at()");
	assert_ATYPE(list->capacity, 4 * capacity, "AL_add_at()");

	for (ATYPE index = 0; index < capacity; index++) {

		value = list->array[index];
		assert_DTYPE(value, offsets[0] + capacity - index, "AL_add_at()");
		value = list->array[index + capacity + 1];
		assert_DTYPE(value, offsets[1] + index + 1, "AL_add_at()");
	}
	value = list->array[capacity];
	assert_DTYPE(value, offsets[2], "AL_add_at()");

	// AL_get()
	for (ATYPE index = 0; index < 4 * capacity; index++) {

		value = list->array[index];
		assert_DTYPE(value, AL_get(list, index), "AL_get()");
	}

	// Hardcoded testing case
	if (capacity == 5) {
		assert_DTYPE(1005, AL_get(list, 0), "AL_hard()");
		assert_DTYPE(1004, AL_get(list, 1), "AL_hard()");
		assert_DTYPE(1003, AL_get(list, 2), "AL_hard()");
		assert_DTYPE(1002, AL_get(list, 3), "AL_hard()");
		assert_DTYPE(1001, AL_get(list, 4), "AL_hard()");
		assert_DTYPE(3000, AL_get(list, 5), "AL_hard()");
		assert_DTYPE(2001, AL_get(list, 6), "AL_hard()");
		assert_DTYPE(2002, AL_get(list, 7), "AL_hard()");
		assert_DTYPE(2003, AL_get(list, 8), "AL_hard()");
		assert_DTYPE(2004, AL_get(list, 9), "AL_hard()");
		assert_DTYPE(2005, AL_get(list, 10), "AL_hard()");
	}

	// AL_size()
	assert_ATYPE(list->size, AL_size(list), "AL_size()");
	assert_ATYPE(2 * capacity + 1, AL_size(list), "AL_size()");

	// AL_clear()
	AL_clear(list);
	assert_ATYPE(AL_size(list), 0, "AL_clear()");

	// AL_is_empty()
	assert_BOOL(AL_is_empty(list), TRUE, "AL_is_empty()");
	list->size = 2 * capacity + 1;
	assert_BOOL(AL_is_empty(list), FALSE, "AL_is_empty()");

	// AL_index_of()
	ATYPE location;
	for (ATYPE index = 0; index < capacity; index++) {

		location = AL_index_of(list, offsets[0] + capacity - index);
		assert_ATYPE(index, location, "AL_index_of()");
		location = AL_index_of(list, offsets[1] + index + 1);
		assert_ATYPE(index + capacity + 1, location, "AL_index_of()");
	}
	location = AL_index_of(list, offsets[2]);
	assert_ATYPE(capacity, location, "AL_index_of()");

	// AL_contains()
	for (DTYPE increment = 1; increment <= capacity; increment++) {

		assert_BOOL(TRUE, AL_contains(list, offsets[0] + increment), "AL_contains()");
		assert_BOOL(TRUE, AL_contains(list, offsets[1] + increment), "AL_contains()");
		assert_BOOL(FALSE, AL_contains(list, offsets[0] - increment), "AL_contains()");
		assert_BOOL(FALSE, AL_contains(list, offsets[1] - increment), "AL_contains()");
	}
	assert_BOOL(TRUE, AL_contains(list, offsets[2]), "AL_contains()");

	// Pray this still holds
	assert_ATYPE(list->size, 2 * capacity + 1, "AL_prayers()");
	assert_ATYPE(list->capacity, 4 * capacity, "AL_prayers()");

/*****************************************************************/

	// All tests pass
	printf("===== ALL TESTS HAVE PASSED! =====\n");
	return 0;
}
