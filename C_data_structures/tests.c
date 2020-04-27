#include <stdio.h>
#include <stdlib.h>
#include "array_list.h"
#include "linked_list.h"

void assert_AL_STYPE(AL_STYPE a, AL_STYPE b, char* title) {

	if (!(a == b)) {
		printf("STYPE assertion failure at section %s.\n", title);
		exit(0);
	}
	return;
}

void assert_LL_STYPE(LL_STYPE a, LL_STYPE b, char* title) {

	if (!(a == b)) {
		printf("STYPE assertion failure at section %s.\n", title);
		exit(0);
	}
	return;
}

void assert_AL_DTYPE(AL_DTYPE a, AL_DTYPE b, char* title) {

	if (!(a == b)) {
		printf("DTYPE assertion failure at section %s.\n", title);
		exit(0);
	}
	return;
}

void assert_LL_DTYPE(LL_DTYPE a, LL_DTYPE b, char* title) {

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
	AL_STYPE AL_capacity = 0;
	AL* array_list = new_AL(AL_capacity);
	assert_AL_STYPE(array_list->size, 0, "new_AL()");
	assert_AL_STYPE(array_list->capacity, DEFAULT_CAP, "new_AL()");

	AL_capacity = 431;
	array_list = new_AL(AL_capacity);
	assert_AL_STYPE(array_list->size, 0, "new_AL()");
	assert_AL_STYPE(array_list->capacity, AL_capacity, "new_AL()");

	for (AL_STYPE j = 0; j < AL_capacity; j++)
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

	AL_DTYPE AL_offsets[] = {1000, 2000, 3000};

	// AL_add_start()
	AL_DTYPE AL_value;
	for (AL_STYPE size = 1; size <= AL_capacity; size++) {

		AL_value = (AL_DTYPE)size + AL_offsets[0];
		AL_add_start(array_list, AL_value);
		assert_AL_STYPE(array_list->size, size, "AL_add_start()");
		assert_AL_STYPE(array_list->capacity, AL_capacity, "AL_add_start()");
	}

	for (AL_STYPE index = 0; index < AL_capacity; index++) {

		AL_value = array_list->array[index];
		assert_AL_DTYPE(AL_value, AL_offsets[0] + AL_capacity - index, "AL_add_start()");
		assert_AL_STYPE(array_list->size, AL_capacity, "AL_add_start()");
		assert_AL_STYPE(array_list->capacity, AL_capacity, "AL_add_start()");
	}

	// AL_add_end()
	for (AL_STYPE size = 1; size <= AL_capacity; size++) {

		AL_value = (AL_DTYPE)size + AL_offsets[1];
		AL_add_end(array_list, AL_value);
		assert_AL_STYPE(array_list->size, size + AL_capacity, "AL_end()");
		assert_AL_STYPE(array_list->capacity, 2 * AL_capacity, "AL_end()");
	}

	for (AL_STYPE index = 0; index < AL_capacity; index++) {

		AL_value = array_list->array[index + AL_capacity];
		assert_AL_DTYPE(AL_value, AL_offsets[1] + index + 1, "AL_end()");
		assert_AL_STYPE(array_list->size, 2 * AL_capacity, "AL_end()");
		assert_AL_STYPE(array_list->capacity, 2 * AL_capacity, "AL_end()");
	}

	// AL_add_at()
	AL_add_at(array_list, AL_offsets[2], AL_capacity);
	assert_AL_STYPE(array_list->size, 2 * AL_capacity + 1, "AL_add_at()");
	assert_AL_STYPE(array_list->capacity, 4 * AL_capacity, "AL_add_at()");

	for (AL_STYPE index = 0; index < AL_capacity; index++) {

		AL_value = array_list->array[index];
		assert_AL_DTYPE(AL_value, AL_offsets[0] + AL_capacity - index, "AL_add_at()");
		AL_value = array_list->array[index + AL_capacity + 1];
		assert_AL_DTYPE(AL_value, AL_offsets[1] + index + 1, "AL_add_at()");
	}
	AL_value = array_list->array[AL_capacity];
	assert_AL_DTYPE(AL_value, AL_offsets[2], "AL_add_at()");

	assert_BOOL(FALSE, AL_add_at(array_list, AL_offsets[0], -1), "AL_add_at()");
	assert_BOOL(FALSE, AL_add_at(array_list, AL_offsets[0], 2 * AL_capacity + 2), "AL_add_at()");

	// AL_get()
	for (AL_STYPE index = 0; index < 2 * AL_capacity; index++) {

		AL_value = array_list->array[index];
		assert_AL_DTYPE(AL_value, AL_get(array_list, index), "AL_get()");
	}

	// AL_size()
	assert_AL_STYPE(array_list->size, AL_size(array_list), "AL_size()");
	assert_AL_STYPE(2 * AL_capacity + 1, AL_size(array_list), "AL_size()");

	// AL_clear()
	assert_BOOL(AL_is_empty(array_list), FALSE, "AL_is_empty()");
	AL_clear(array_list);
	assert_AL_STYPE(AL_size(array_list), 0, "AL_clear()");

	// AL_is_empty()
	assert_BOOL(AL_is_empty(array_list), TRUE, "AL_is_empty()");

	for (AL_STYPE size = 1; size <= AL_capacity; size++) {

		AL_value = (AL_DTYPE)size + AL_offsets[0];
		AL_add_start(array_list, AL_value);
		AL_value = (AL_DTYPE)size + AL_offsets[1];
		AL_add_end(array_list, AL_value);
	}

	for (AL_STYPE index = 0; index < AL_capacity; index++) {

		AL_value = AL_get(array_list, index);
		assert_AL_DTYPE(AL_value, AL_offsets[0] + AL_capacity - index, "AL_clear()");
		AL_value = AL_get(array_list, index + AL_capacity);
		assert_AL_DTYPE(AL_value, AL_offsets[1] + index + 1, "AL_clear()");
		assert_AL_STYPE(array_list->size, 2 * AL_capacity, "AL_clear()");
	}
	AL_add_at(array_list, AL_offsets[2], AL_capacity);
	AL_value = AL_get(array_list, AL_capacity);
	assert_AL_DTYPE(AL_value, AL_offsets[2], "AL_add_at()");

	// AL_index_of()
	AL_STYPE AL_location;
	for (AL_STYPE index = 0; index < AL_capacity; index++) {

		AL_location = AL_index_of(array_list, AL_offsets[0] + AL_capacity - index);
		assert_AL_STYPE(index, AL_location, "AL_index_of()");
		AL_location = AL_index_of(array_list, AL_offsets[1] + index + 1);
		assert_AL_STYPE(index + AL_capacity + 1, AL_location, "AL_index_of()");
	}
	AL_location = AL_index_of(array_list, AL_offsets[2]);
	assert_AL_STYPE(AL_capacity, AL_location, "AL_index_of()");

	// AL_contains()
	for (AL_DTYPE increment = 1; increment <= AL_capacity; increment++) {

		assert_BOOL(TRUE, AL_contains(array_list, AL_offsets[0] + increment), "AL_contains()");
		assert_BOOL(TRUE, AL_contains(array_list, AL_offsets[1] + increment), "AL_contains()");
		assert_BOOL(FALSE, AL_contains(array_list, AL_offsets[0] - increment), "AL_contains()");
		assert_BOOL(FALSE, AL_contains(array_list, AL_offsets[1] - increment), "AL_contains()");
	}
	assert_BOOL(TRUE, AL_contains(array_list, AL_offsets[2]), "AL_contains()");

	// Pray this still holds
	assert_AL_STYPE(array_list->size, 2 * AL_capacity + 1, "AL_prayers()");
	assert_AL_STYPE(array_list->capacity, 4 * AL_capacity, "AL_prayers()");

	// AL_remove_at()
	assert_BOOL(FALSE, AL_remove_at(array_list, -1), "AL_remove_at()");
	assert_BOOL(FALSE, AL_remove_at(array_list, 2 * AL_capacity + 1), "AL_remove_at()");

	assert_BOOL(TRUE, AL_remove_at(array_list, AL_capacity), "AL_remove_at()");
	assert_AL_STYPE(2 * AL_capacity, AL_size(array_list), "AL_remove_at()");
	assert_AL_STYPE(2 * AL_capacity, array_list->size, "AL_remove_at()");
	assert_AL_STYPE(4 * AL_capacity, array_list->capacity, "AL_remove_at()");

	for (AL_STYPE index = 0; index < AL_capacity; index++) {

		AL_value = array_list->array[index];
		assert_AL_DTYPE(AL_value, AL_offsets[0] + AL_capacity - index, "AL_remove_at()");
		AL_value = array_list->array[index + AL_capacity];
		assert_AL_DTYPE(AL_value, AL_offsets[1] + index + 1, "AL_remove_at()");
	}

	// AL_remove_value()
	assert_BOOL(FALSE, AL_remove_value(array_list, -1), "AL_remove_value()");
	assert_BOOL(FALSE, AL_remove_value(array_list, AL_offsets[2]), "AL_remove_value()");

	for (AL_STYPE size = 1; size <= AL_capacity; size++) {

		AL_value = (AL_DTYPE)size + AL_offsets[0];
		assert_BOOL(TRUE, AL_remove_value(array_list, AL_value), "AL_remove_value()");
		assert_AL_STYPE(array_list->size, 2 * AL_capacity - size, "AL_remove_value()");
		assert_AL_STYPE(array_list->capacity, 4 * AL_capacity, "AL_remove_value()");
	}

	for (AL_STYPE index = 0; index < AL_capacity; index++) {

		AL_value = AL_get(array_list, index);
		assert_AL_DTYPE(AL_value, AL_offsets[1] + index + 1, "AL_remove_remove_value()");
	}

	// AL_remove_end()
	for (AL_STYPE index = 0; index < AL_capacity; index++)
		assert_BOOL(TRUE, AL_remove_end(array_list), "AL_remove_end()");

	assert_AL_STYPE(array_list->size, 0, "AL_remove_end()");
	assert_BOOL(TRUE, AL_is_empty(array_list), "AL_remove_end()");
	assert_BOOL(FALSE, AL_remove_end(array_list), "AL_remove_end()");

	// AL_remove_start()
	AL_add_end(array_list, 321);
	assert_BOOL(TRUE, AL_remove_start(array_list), "AL_remove_start()");

	assert_AL_STYPE(array_list->size, 0, "AL_remove_start()");
	assert_BOOL(TRUE, AL_is_empty(array_list), "AL_remove_start()");
	assert_BOOL(FALSE, AL_remove_start(array_list), "AL_remove_start()");

	// Completes array list unit tests
	printf("===== COMPLETED ARRAY LIST UNIT TESTS =====\n");

/*****************************************************************/

/*****************************************************************/

	// Conduct linked list unit tests
	printf("===== CONDUCTING LINKED LIST UNIT TESTS =====\n");

	// new_LL()
	LL_STYPE LL_capacity = 421;
	LL* linked_list = new_LL();
	assert_LL_STYPE(linked_list->size, 0, "new_LL()");
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

	LL_DTYPE LL_offsets[] = {1000, 2000, 3000};

	// LL_add_start()
	LL_DTYPE LL_value;
	for (LL_STYPE size = 1; size <= LL_capacity; size++) {

		LL_value = (LL_DTYPE)size + LL_offsets[0];
		LL_add_start(linked_list, LL_value);
		assert_LL_STYPE(linked_list->size, size, "LL_add_start()");
	}

	for (LL_STYPE index = 0; index < LL_capacity; index++) {

		LL_value = LL_get(linked_list, index);
		assert_LL_DTYPE(LL_value, LL_offsets[0] + LL_capacity - index, "LL_add_start()");
		assert_LL_STYPE(linked_list->size, LL_capacity, "LL_add_start()");
	}

	// LL_add_end()
	for (LL_STYPE size = 1; size <= LL_capacity; size++) {

		LL_value = (LL_DTYPE)size + LL_offsets[1];
		LL_add_end(linked_list, LL_value);
		assert_LL_STYPE(linked_list->size, size + LL_capacity, "LL_end()");
	}

	for (LL_STYPE index = 0; index < LL_capacity; index++) {

		LL_value = LL_get(linked_list, index + LL_capacity);
		assert_LL_DTYPE(LL_value, LL_offsets[1] + index + 1, "LL_end()");
		assert_LL_STYPE(linked_list->size, 2 * LL_capacity, "LL_end()");
	}

	// LL_add_at()
	LL_add_at(linked_list, LL_offsets[2], LL_capacity);
	assert_LL_STYPE(linked_list->size, 2 * LL_capacity + 1, "LL_add_at()");

	for (LL_STYPE index = 0; index < LL_capacity; index++) {

		LL_value = LL_get(linked_list, index);
		assert_LL_DTYPE(LL_value, LL_offsets[0] + LL_capacity - index, "LL_add_at()");
		LL_value = LL_get(linked_list, index + LL_capacity + 1);
		assert_LL_DTYPE(LL_value, LL_offsets[1] + index + 1, "LL_add_at()");
	}
	LL_value = LL_get(linked_list, LL_capacity);
	assert_LL_DTYPE(LL_value, LL_offsets[2], "LL_add_at()");

	assert_BOOL(FALSE, LL_add_at(linked_list, LL_offsets[0], -1), "LL_add_at()");
	assert_BOOL(FALSE, LL_add_at(linked_list, LL_offsets[0], 2 * LL_capacity + 2), "LL_add_at()");

	// LL_get()
	for (LL_STYPE index = 0; index < 2 * LL_capacity; index++) {

		LL_value = LL_get(linked_list, index);
		assert_LL_DTYPE(LL_value, LL_get(linked_list, index), "LL_get()");
	}

	// LL_size()
	assert_LL_STYPE(linked_list->size, LL_size(linked_list), "LL_size()");
	assert_LL_STYPE(2 * LL_capacity + 1, LL_size(linked_list), "LL_size()");

	// LL_clear()
	assert_BOOL(LL_is_empty(linked_list), FALSE, "LL_is_empty()");
	LL_clear(linked_list);
	assert_LL_STYPE(LL_size(linked_list), 0, "LL_clear()");

	// LL_is_empty()
	assert_BOOL(LL_is_empty(linked_list), TRUE, "LL_is_empty()");

	for (LL_STYPE size = 1; size <= LL_capacity; size++) {

		LL_value = (LL_DTYPE)size + LL_offsets[0];
		LL_add_start(linked_list, LL_value);
		LL_value = (LL_DTYPE)size + LL_offsets[1];
		LL_add_end(linked_list, LL_value);
	}

	for (LL_STYPE index = 0; index < LL_capacity; index++) {

		LL_value = LL_get(linked_list, index);
		assert_LL_DTYPE(LL_value, LL_offsets[0] + LL_capacity - index, "LL_clear()");
		LL_value = LL_get(linked_list, index + LL_capacity);
		assert_LL_DTYPE(LL_value, LL_offsets[1] + index + 1, "LL_clear()");
		assert_LL_STYPE(linked_list->size, 2 * LL_capacity, "LL_clear()");
	}
	LL_add_at(linked_list, LL_offsets[2], LL_capacity);
	LL_value = LL_get(linked_list, LL_capacity);
	assert_LL_DTYPE(LL_value, LL_offsets[2], "LL_add_at()");

	// LL_index_of()
	LL_STYPE LL_location;
	for (LL_STYPE index = 0; index < LL_capacity; index++) {

		LL_location = LL_index_of(linked_list, LL_offsets[0] + LL_capacity - index);
		assert_LL_STYPE(index, LL_location, "LL_index_of()");
		LL_location = LL_index_of(linked_list, LL_offsets[1] + index + 1);
		assert_LL_STYPE(index + LL_capacity + 1, LL_location, "LL_index_of()");
	}
	LL_location = LL_index_of(linked_list, LL_offsets[2]);
	assert_LL_STYPE(LL_capacity, LL_location, "LL_index_of()");

	// LL_contains()
	for (LL_DTYPE increment = 1; increment <= LL_capacity; increment++) {

		assert_BOOL(TRUE, LL_contains(linked_list, LL_offsets[0] + increment), "LL_contains()");
		assert_BOOL(TRUE, LL_contains(linked_list, LL_offsets[1] + increment), "LL_contains()");
		assert_BOOL(FALSE, LL_contains(linked_list, LL_offsets[0] - increment), "LL_contains()");
		assert_BOOL(FALSE, LL_contains(linked_list, LL_offsets[1] - increment), "LL_contains()");
	}
	assert_BOOL(TRUE, LL_contains(linked_list, LL_offsets[2]), "LL_contains()");

	// Pray this still holds
	assert_LL_STYPE(linked_list->size, 2 * LL_capacity + 1, "LL_prayers()");

	// LL_remove_at()
	assert_BOOL(FALSE, LL_remove_at(linked_list, -1), "LL_remove_at()");
	assert_BOOL(FALSE, LL_remove_at(linked_list, 2 * LL_capacity + 1), "LL_remove_at()");

	assert_BOOL(TRUE, LL_remove_at(linked_list, LL_capacity), "LL_remove_at()");
	assert_LL_STYPE(2 * LL_capacity, LL_size(linked_list), "LL_remove_at()");
	assert_LL_STYPE(2 * LL_capacity, linked_list->size, "LL_remove_at()");

	for (LL_STYPE index = 0; index < LL_capacity; index++) {

		LL_value = LL_get(linked_list, index);
		assert_LL_DTYPE(LL_value, LL_offsets[0] + LL_capacity - index, "LL_remove_at()");
		LL_value = LL_get(linked_list, index + LL_capacity);
		assert_LL_DTYPE(LL_value, LL_offsets[1] + index + 1, "LL_remove_at()");
	}

	// LL_remove_value()
	assert_BOOL(FALSE, LL_remove_value(linked_list, -1), "LL_remove_value()");
	assert_BOOL(FALSE, LL_remove_value(linked_list, LL_offsets[2]), "LL_remove_value()");

	for (LL_STYPE size = 1; size <= LL_capacity; size++) {

		LL_value = (LL_DTYPE)size + LL_offsets[0];
		assert_BOOL(TRUE, LL_remove_value(linked_list, LL_value), "LL_remove_value()");
		assert_LL_STYPE(linked_list->size, 2 * LL_capacity - size, "LL_remove_value()");
	}

	for (LL_STYPE index = 0; index < LL_capacity; index++) {

		LL_value = LL_get(linked_list, index);
		assert_LL_DTYPE(LL_value, LL_offsets[1] + index + 1, "LL_remove_remove_value()");
	}

	// LL_remove_end()
	for (LL_STYPE index = 0; index < LL_capacity; index++)
		assert_BOOL(TRUE, LL_remove_end(linked_list), "LL_remove_end()");

	assert_LL_STYPE(linked_list->size, 0, "LL_remove_end()");
	assert_NULL(linked_list->head, "LL_remove_end()");
	assert_NULL(linked_list->tail, "LL_remove_end()");
	assert_BOOL(TRUE, LL_is_empty(linked_list), "LL_remove_end()");
	assert_BOOL(FALSE, LL_remove_end(linked_list), "LL_remove_end()");

	// LL_remove_start()
	LL_add_end(linked_list, 321);
	assert_BOOL(TRUE, LL_remove_start(linked_list), "LL_remove_start()");

	assert_LL_STYPE(linked_list->size, 0, "LL_remove_start()");
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
