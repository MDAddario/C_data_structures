#include <stdio.h>
#include <stdlib.h>
#include "array_list.h"
#include "linked_list.h"

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

void assert_NULL(ND* node, char* title) {

	if (!(node == NULL)) {
		printf("NULL assertion failure at section %s.\n", title);
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
	AL* array_list = new_AL(capacity);
	assert_ATYPE(array_list->size, 0, "new_AL()");
	assert_ATYPE(array_list->capacity, DEFAULT_CAP, "new_AL()");

	capacity = 431;
	array_list = new_AL(capacity);
	assert_ATYPE(array_list->size, 0, "new_AL()");
	assert_ATYPE(array_list->capacity, capacity, "new_AL()");

	for (ATYPE j = 0; j < capacity; j++)
		array_list->array[j] = 0;     // Ensure no segfaults

	// free_AL()
	printf("Testing memory management: ");
	for (int i = 0; i < 10; i++) {
		for (long j = 0; j < 1000000; j++) {
			AL* array_list_2 = new_AL(1000000);
			free_AL(array_list_2);
		}
		printf("%d%% ", (i + 1) * 10);
	}
	printf("\n");

	DTYPE offsets[] = {1000, 2000, 3000};

	// AL_add_start()
	DTYPE value;
	for (ATYPE size = 1; size <= capacity; size++) {

		value = (DTYPE)size + offsets[0];
		AL_add_start(array_list, value);
		assert_ATYPE(array_list->size, size, "AL_add_start()");
		assert_ATYPE(array_list->capacity, capacity, "AL_add_start()");
	}

	for (ATYPE index = 0; index < capacity; index++) {

		value = array_list->array[index];
		assert_DTYPE(value, offsets[0] + capacity - index, "AL_add_start()");
		assert_ATYPE(array_list->size, capacity, "AL_add_start()");
		assert_ATYPE(array_list->capacity, capacity, "AL_add_start()");
	}

	// AL_add_end()
	for (ATYPE size = 1; size <= capacity; size++) {

		value = (DTYPE)size + offsets[1];
		AL_add_end(array_list, value);
		assert_ATYPE(array_list->size, size + capacity, "AL_end()");
		assert_ATYPE(array_list->capacity, 2 * capacity, "AL_end()");
	}

	for (ATYPE index = 0; index < capacity; index++) {

		value = array_list->array[index + capacity];
		assert_DTYPE(value, offsets[1] + index + 1, "AL_end()");
		assert_ATYPE(array_list->size, 2 * capacity, "AL_end()");
		assert_ATYPE(array_list->capacity, 2 * capacity, "AL_end()");
	}

	// AL_add_at()
	AL_add_at(array_list, offsets[2], capacity);
	assert_ATYPE(array_list->size, 2 * capacity + 1, "AL_add_at()");
	assert_ATYPE(array_list->capacity, 4 * capacity, "AL_add_at()");

	for (ATYPE index = 0; index < capacity; index++) {

		value = array_list->array[index];
		assert_DTYPE(value, offsets[0] + capacity - index, "AL_add_at()");
		value = array_list->array[index + capacity + 1];
		assert_DTYPE(value, offsets[1] + index + 1, "AL_add_at()");
	}
	value = array_list->array[capacity];
	assert_DTYPE(value, offsets[2], "AL_add_at()");

	assert_BOOL(FALSE, AL_add_at(array_list, offsets[0], -1), "AL_add_at()");
	assert_BOOL(FALSE, AL_add_at(array_list, offsets[0], 2 * capacity + 2), "AL_add_at()");

	// AL_get()
	for (ATYPE index = 0; index < 2 * capacity; index++) {

		value = array_list->array[index];
		assert_DTYPE(value, AL_get(array_list, index), "AL_get()");
	}

	// AL_size()
	assert_ATYPE(array_list->size, AL_size(array_list), "AL_size()");
	assert_ATYPE(2 * capacity + 1, AL_size(array_list), "AL_size()");

	// AL_clear()
	assert_BOOL(AL_is_empty(array_list), FALSE, "AL_is_empty()");
	AL_clear(array_list);
	assert_ATYPE(AL_size(array_list), 0, "AL_clear()");

	// AL_is_empty()
	assert_BOOL(AL_is_empty(array_list), TRUE, "AL_is_empty()");

	for (ATYPE size = 1; size <= capacity; size++) {

		value = (DTYPE)size + offsets[0];
		AL_add_start(array_list, value);
		value = (DTYPE)size + offsets[1];
		AL_add_end(array_list, value);
	}

	for (ATYPE index = 0; index < capacity; index++) {

		value = AL_get(array_list, index);
		assert_DTYPE(value, offsets[0] + capacity - index, "AL_clear()");
		value = AL_get(array_list, index + capacity);
		assert_DTYPE(value, offsets[1] + index + 1, "AL_clear()");
		assert_ATYPE(array_list->size, 2 * capacity, "AL_clear()");
	}
	AL_add_at(array_list, offsets[2], capacity);
	value = AL_get(array_list, capacity);
	assert_DTYPE(value, offsets[2], "AL_add_at()");

	// AL_index_of()
	ATYPE location;
	for (ATYPE index = 0; index < capacity; index++) {

		location = AL_index_of(array_list, offsets[0] + capacity - index);
		assert_ATYPE(index, location, "AL_index_of()");
		location = AL_index_of(array_list, offsets[1] + index + 1);
		assert_ATYPE(index + capacity + 1, location, "AL_index_of()");
	}
	location = AL_index_of(array_list, offsets[2]);
	assert_ATYPE(capacity, location, "AL_index_of()");

	// AL_contains()
	for (DTYPE increment = 1; increment <= capacity; increment++) {

		assert_BOOL(TRUE, AL_contains(array_list, offsets[0] + increment), "AL_contains()");
		assert_BOOL(TRUE, AL_contains(array_list, offsets[1] + increment), "AL_contains()");
		assert_BOOL(FALSE, AL_contains(array_list, offsets[0] - increment), "AL_contains()");
		assert_BOOL(FALSE, AL_contains(array_list, offsets[1] - increment), "AL_contains()");
	}
	assert_BOOL(TRUE, AL_contains(array_list, offsets[2]), "AL_contains()");

	// Pray this still holds
	assert_ATYPE(array_list->size, 2 * capacity + 1, "AL_prayers()");
	assert_ATYPE(array_list->capacity, 4 * capacity, "AL_prayers()");

	// AL_remove_at()
	assert_BOOL(FALSE, AL_remove_at(array_list, -1), "AL_remove_at()");
	assert_BOOL(FALSE, AL_remove_at(array_list, 2 * capacity + 1), "AL_remove_at()");

	assert_BOOL(TRUE, AL_remove_at(array_list, capacity), "AL_remove_at()");
	assert_ATYPE(2 * capacity, AL_size(array_list), "AL_remove_at()");
	assert_ATYPE(2 * capacity, array_list->size, "AL_remove_at()");
	assert_ATYPE(4 * capacity, array_list->capacity, "AL_remove_at()");

	for (ATYPE index = 0; index < capacity; index++) {

		value = array_list->array[index];
		assert_DTYPE(value, offsets[0] + capacity - index, "AL_remove_at()");
		value = array_list->array[index + capacity];
		assert_DTYPE(value, offsets[1] + index + 1, "AL_remove_at()");
	}

	// AL_remove_value()
	assert_BOOL(FALSE, AL_remove_value(array_list, -1), "AL_remove_value()");
	assert_BOOL(FALSE, AL_remove_value(array_list, offsets[2]), "AL_remove_value()");

	for (ATYPE size = 1; size <= capacity; size++) {

		value = (DTYPE)size + offsets[0];
		assert_BOOL(TRUE, AL_remove_value(array_list, value), "AL_remove_value()");
		assert_ATYPE(array_list->size, 2 * capacity - size, "AL_remove_value()");
		assert_ATYPE(array_list->capacity, 4 * capacity, "AL_remove_value()");
	}

	for (ATYPE index = 0; index < capacity; index++) {

		value = AL_get(array_list, index);
		assert_DTYPE(value, offsets[1] + index + 1, "AL_remove_remove_value()");
	}

	// AL_remove_end()
	for (ATYPE index = 0; index < capacity; index++)
		assert_BOOL(TRUE, AL_remove_end(array_list), "AL_remove_end()");

	assert_ATYPE(array_list->size, 0, "AL_remove_end()");
	assert_BOOL(TRUE, AL_is_empty(array_list), "AL_remove_end()");
	assert_BOOL(FALSE, AL_remove_end(array_list), "AL_remove_end()");

	// AL_remove_start()
	AL_add_end(array_list, 321);
	assert_BOOL(TRUE, AL_remove_start(array_list), "AL_remove_start()");

	assert_ATYPE(array_list->size, 0, "AL_remove_start()");
	assert_BOOL(TRUE, AL_is_empty(array_list), "AL_remove_start()");
	assert_BOOL(FALSE, AL_remove_start(array_list), "AL_remove_start()");

	// Completes array list unit tests
	printf("===== COMPLETED ARRAY LIST UNIT TESTS =====\n");

/*****************************************************************/

/*****************************************************************/

	// Conduct linked list unit tests
	printf("===== CONDUCTING LINKED LIST UNIT TESTS =====\n");

	// new_LL()
	LL* linked_list = new_LL();
	assert_ATYPE(linked_list->size, 0, "new_LL()");
	assert_NULL(linked_list->head, "new_LL()");
	assert_NULL(linked_list->tail, "new_LL()");

	// free_LL()
	printf("Testing memory management: ");
	for (int i = 0; i < 10; i++) {
		LL* linked_list_2 = new_LL();
		for (long j = 0; j < 1000000; j++) {
			LL_add_end(linked_list_2, 321);
		}
		free_LL(linked_list_2);
		printf("%d%% ", (i + 1) * 10);
	}
	printf("\n");

	// LL_add_start()
	for (ATYPE size = 1; size <= capacity; size++) {

		value = (DTYPE)size + offsets[0];
		LL_add_start(linked_list, value);
		assert_ATYPE(linked_list->size, size, "LL_add_start()");
	}

	for (ATYPE index = 0; index < capacity; index++) {

		value = LL_get(linked_list, index);
		assert_DTYPE(value, offsets[0] + capacity - index, "LL_add_start()");
		assert_ATYPE(linked_list->size, capacity, "LL_add_start()");
	}

	// LL_add_end()
	for (ATYPE size = 1; size <= capacity; size++) {

		value = (DTYPE)size + offsets[1];
		LL_add_end(linked_list, value);
		assert_ATYPE(linked_list->size, size + capacity, "LL_end()");
	}

	for (ATYPE index = 0; index < capacity; index++) {

		value = LL_get(linked_list, index + capacity);
		assert_DTYPE(value, offsets[1] + index + 1, "LL_end()");
		assert_ATYPE(linked_list->size, 2 * capacity, "LL_end()");
	}

	// LL_add_at()
	LL_add_at(linked_list, offsets[2], capacity);
	assert_ATYPE(linked_list->size, 2 * capacity + 1, "LL_add_at()");

	for (ATYPE index = 0; index < capacity; index++) {

		value = LL_get(linked_list, index);
		assert_DTYPE(value, offsets[0] + capacity - index, "LL_add_at()");
		value = LL_get(linked_list, index + capacity + 1);
		assert_DTYPE(value, offsets[1] + index + 1, "LL_add_at()");
	}
	value = LL_get(linked_list, capacity);
	assert_DTYPE(value, offsets[2], "LL_add_at()");

	assert_BOOL(FALSE, LL_add_at(linked_list, offsets[0], -1), "LL_add_at()");
	assert_BOOL(FALSE, LL_add_at(linked_list, offsets[0], 2 * capacity + 2), "LL_add_at()");

	// LL_get()
	for (ATYPE index = 0; index < 2 * capacity; index++) {

		value = LL_get(linked_list, index);
		assert_DTYPE(value, LL_get(linked_list, index), "LL_get()");
	}

	// LL_size()
	assert_ATYPE(linked_list->size, LL_size(linked_list), "LL_size()");
	assert_ATYPE(2 * capacity + 1, LL_size(linked_list), "LL_size()");

	// LL_clear()
	assert_BOOL(LL_is_empty(linked_list), FALSE, "LL_is_empty()");
	LL_clear(linked_list);
	assert_ATYPE(LL_size(linked_list), 0, "LL_clear()");

	// LL_is_empty()
	assert_BOOL(LL_is_empty(linked_list), TRUE, "LL_is_empty()");

	for (ATYPE size = 1; size <= capacity; size++) {

		value = (DTYPE)size + offsets[0];
		LL_add_start(linked_list, value);
		value = (DTYPE)size + offsets[1];
		LL_add_end(linked_list, value);
	}

	for (ATYPE index = 0; index < capacity; index++) {

		value = LL_get(linked_list, index);
		assert_DTYPE(value, offsets[0] + capacity - index, "LL_clear()");
		value = LL_get(linked_list, index + capacity);
		assert_DTYPE(value, offsets[1] + index + 1, "LL_clear()");
		assert_ATYPE(linked_list->size, 2 * capacity, "LL_clear()");
	}
	LL_add_at(linked_list, offsets[2], capacity);
	value = LL_get(linked_list, capacity);
	assert_DTYPE(value, offsets[2], "LL_add_at()");

	// LL_index_of()
	for (ATYPE index = 0; index < capacity; index++) {

		location = LL_index_of(linked_list, offsets[0] + capacity - index);
		assert_ATYPE(index, location, "LL_index_of()");
		location = LL_index_of(linked_list, offsets[1] + index + 1);
		assert_ATYPE(index + capacity + 1, location, "LL_index_of()");
	}
	location = LL_index_of(linked_list, offsets[2]);
	assert_ATYPE(capacity, location, "LL_index_of()");

	// LL_contains()
	for (DTYPE increment = 1; increment <= capacity; increment++) {

		assert_BOOL(TRUE, LL_contains(linked_list, offsets[0] + increment), "LL_contains()");
		assert_BOOL(TRUE, LL_contains(linked_list, offsets[1] + increment), "LL_contains()");
		assert_BOOL(FALSE, LL_contains(linked_list, offsets[0] - increment), "LL_contains()");
		assert_BOOL(FALSE, LL_contains(linked_list, offsets[1] - increment), "LL_contains()");
	}
	assert_BOOL(TRUE, LL_contains(linked_list, offsets[2]), "LL_contains()");

	// Pray this still holds
	assert_ATYPE(linked_list->size, 2 * capacity + 1, "LL_prayers()");

	// LL_remove_at()
	assert_BOOL(FALSE, LL_remove_at(linked_list, -1), "LL_remove_at()");
	assert_BOOL(FALSE, LL_remove_at(linked_list, 2 * capacity + 1), "LL_remove_at()");

	assert_BOOL(TRUE, LL_remove_at(linked_list, capacity), "LL_remove_at()");
	assert_ATYPE(2 * capacity, LL_size(linked_list), "LL_remove_at()");
	assert_ATYPE(2 * capacity, linked_list->size, "LL_remove_at()");

	for (ATYPE index = 0; index < capacity; index++) {

		value = LL_get(linked_list, index);
		assert_DTYPE(value, offsets[0] + capacity - index, "LL_remove_at()");
		value = LL_get(linked_list, index + capacity);
		assert_DTYPE(value, offsets[1] + index + 1, "LL_remove_at()");
	}

	// LL_remove_value()
	assert_BOOL(FALSE, LL_remove_value(linked_list, -1), "LL_remove_value()");
	assert_BOOL(FALSE, LL_remove_value(linked_list, offsets[2]), "LL_remove_value()");

	for (ATYPE size = 1; size <= capacity; size++) {

		value = (DTYPE)size + offsets[0];
		assert_BOOL(TRUE, LL_remove_value(linked_list, value), "LL_remove_value()");
		assert_ATYPE(linked_list->size, 2 * capacity - size, "LL_remove_value()");
	}

	for (ATYPE index = 0; index < capacity; index++) {

		value = LL_get(linked_list, index);
		assert_DTYPE(value, offsets[1] + index + 1, "LL_remove_remove_value()");
	}

	// LL_remove_end()
	for (ATYPE index = 0; index < capacity; index++)
		assert_BOOL(TRUE, LL_remove_end(linked_list), "LL_remove_end()");

	assert_ATYPE(linked_list->size, 0, "LL_remove_end()");
	assert_NULL(linked_list->head, "LL_remove_end()");
	assert_NULL(linked_list->tail, "LL_remove_end()");
	assert_BOOL(TRUE, LL_is_empty(linked_list), "LL_remove_end()");
	assert_BOOL(FALSE, LL_remove_end(linked_list), "LL_remove_end()");

	// LL_remove_start()
	LL_add_end(linked_list, 321);
	assert_BOOL(TRUE, LL_remove_start(linked_list), "LL_remove_start()");

	assert_ATYPE(linked_list->size, 0, "LL_remove_start()");
	assert_NULL(linked_list->head, "LL_remove_start()");
	assert_NULL(linked_list->tail, "LL_remove_start()");
	assert_BOOL(TRUE, LL_is_empty(linked_list), "LL_remove_start()");
	assert_BOOL(FALSE, LL_remove_start(linked_list), "LL_remove_start()");

	// Completes linked list unit tests
	printf("===== COMPLETED LINKED LIST UNIT TESTS =====\n");

/*****************************************************************/
/*****************************************************************/

	// All tests pass
	printf("\n===== ALL TESTS HAVE PASSED! =====\n");
	return 0;
}
