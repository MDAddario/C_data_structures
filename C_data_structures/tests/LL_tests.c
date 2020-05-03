#include <stdio.h>
#include "testing.h"

int main() {

	// Conduct linked list unit tests
	printf("===== CONDUCTING LINKED LIST UNIT TESTS =====\n");

	// new_LL()
	STYPE LL_capacity = 421;
	LL* linked_list = new_LL();
	assert_STYPE(linked_list->size, 0, "new_LL()");
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
	for (STYPE size = 1; size <= LL_capacity; size++) {

		LL_value = (LL_DTYPE)size + LL_offsets[0];
		LL_add_start(linked_list, LL_value);
		assert_STYPE(linked_list->size, size, "LL_add_start()");
	}

	for (STYPE index = 0; index < LL_capacity; index++) {

		LL_value = LL_get(linked_list, index);
		assert_LL_DTYPE(LL_value, LL_offsets[0] + LL_capacity - index, "LL_add_start()");
		assert_STYPE(linked_list->size, LL_capacity, "LL_add_start()");
	}

	// LL_add_end()
	for (STYPE size = 1; size <= LL_capacity; size++) {

		LL_value = (LL_DTYPE)size + LL_offsets[1];
		LL_add_end(linked_list, LL_value);
		assert_STYPE(linked_list->size, size + LL_capacity, "LL_end()");
	}

	for (STYPE index = 0; index < LL_capacity; index++) {

		LL_value = LL_get(linked_list, index + LL_capacity);
		assert_LL_DTYPE(LL_value, LL_offsets[1] + index + 1, "LL_end()");
		assert_STYPE(linked_list->size, 2 * LL_capacity, "LL_end()");
	}

	// LL_add_at()
	LL_add_at(linked_list, LL_offsets[2], LL_capacity);
	assert_STYPE(linked_list->size, 2 * LL_capacity + 1, "LL_add_at()");

	for (STYPE index = 0; index < LL_capacity; index++) {

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
	for (STYPE index = 0; index < 2 * LL_capacity; index++) {

		LL_value = LL_get(linked_list, index);
		assert_LL_DTYPE(LL_value, LL_get(linked_list, index), "LL_get()");
	}

	// LL_size()
	assert_STYPE(linked_list->size, LL_size(linked_list), "LL_size()");
	assert_STYPE(2 * LL_capacity + 1, LL_size(linked_list), "LL_size()");

	// LL_clear()
	assert_BOOL(LL_is_empty(linked_list), FALSE, "LL_is_empty()");
	LL_clear(linked_list);
	assert_STYPE(LL_size(linked_list), 0, "LL_clear()");

	// LL_is_empty()
	assert_BOOL(LL_is_empty(linked_list), TRUE, "LL_is_empty()");

	for (STYPE size = 1; size <= LL_capacity; size++) {

		LL_value = (LL_DTYPE)size + LL_offsets[0];
		LL_add_start(linked_list, LL_value);
		LL_value = (LL_DTYPE)size + LL_offsets[1];
		LL_add_end(linked_list, LL_value);
	}

	for (STYPE index = 0; index < LL_capacity; index++) {

		LL_value = LL_get(linked_list, index);
		assert_LL_DTYPE(LL_value, LL_offsets[0] + LL_capacity - index, "LL_clear()");
		LL_value = LL_get(linked_list, index + LL_capacity);
		assert_LL_DTYPE(LL_value, LL_offsets[1] + index + 1, "LL_clear()");
		assert_STYPE(linked_list->size, 2 * LL_capacity, "LL_clear()");
	}
	LL_add_at(linked_list, LL_offsets[2], LL_capacity);
	LL_value = LL_get(linked_list, LL_capacity);
	assert_LL_DTYPE(LL_value, LL_offsets[2], "LL_add_at()");

	// LL_index_of()
	STYPE LL_location;
	for (STYPE index = 0; index < LL_capacity; index++) {

		LL_location = LL_index_of(linked_list, LL_offsets[0] + LL_capacity - index);
		assert_STYPE(index, LL_location, "LL_index_of()");
		LL_location = LL_index_of(linked_list, LL_offsets[1] + index + 1);
		assert_STYPE(index + LL_capacity + 1, LL_location, "LL_index_of()");
	}
	LL_location = LL_index_of(linked_list, LL_offsets[2]);
	assert_STYPE(LL_capacity, LL_location, "LL_index_of()");

	// LL_contains()
	for (LL_DTYPE increment = 1; increment <= LL_capacity; increment++) {

		assert_BOOL(TRUE, LL_contains(linked_list, LL_offsets[0] + increment), "LL_contains()");
		assert_BOOL(TRUE, LL_contains(linked_list, LL_offsets[1] + increment), "LL_contains()");
		assert_BOOL(FALSE, LL_contains(linked_list, LL_offsets[0] - increment), "LL_contains()");
		assert_BOOL(FALSE, LL_contains(linked_list, LL_offsets[1] - increment), "LL_contains()");
	}
	assert_BOOL(TRUE, LL_contains(linked_list, LL_offsets[2]), "LL_contains()");

	// Pray this still holds
	assert_STYPE(linked_list->size, 2 * LL_capacity + 1, "LL_prayers()");

	// LL_remove_at()
	assert_BOOL(FALSE, LL_remove_at(linked_list, -1), "LL_remove_at()");
	assert_BOOL(FALSE, LL_remove_at(linked_list, 2 * LL_capacity + 1), "LL_remove_at()");

	assert_BOOL(TRUE, LL_remove_at(linked_list, LL_capacity), "LL_remove_at()");
	assert_STYPE(2 * LL_capacity, LL_size(linked_list), "LL_remove_at()");
	assert_STYPE(2 * LL_capacity, linked_list->size, "LL_remove_at()");

	for (STYPE index = 0; index < LL_capacity; index++) {

		LL_value = LL_get(linked_list, index);
		assert_LL_DTYPE(LL_value, LL_offsets[0] + LL_capacity - index, "LL_remove_at()");
		LL_value = LL_get(linked_list, index + LL_capacity);
		assert_LL_DTYPE(LL_value, LL_offsets[1] + index + 1, "LL_remove_at()");
	}

	// LL_remove_value()
	assert_BOOL(FALSE, LL_remove_value(linked_list, -1), "LL_remove_value()");
	assert_BOOL(FALSE, LL_remove_value(linked_list, LL_offsets[2]), "LL_remove_value()");

	for (STYPE size = 1; size <= LL_capacity; size++) {

		LL_value = (LL_DTYPE)size + LL_offsets[0];
		assert_BOOL(TRUE, LL_remove_value(linked_list, LL_value), "LL_remove_value()");
		assert_STYPE(linked_list->size, 2 * LL_capacity - size, "LL_remove_value()");
	}

	for (STYPE index = 0; index < LL_capacity; index++) {

		LL_value = LL_get(linked_list, index);
		assert_LL_DTYPE(LL_value, LL_offsets[1] + index + 1, "LL_remove_remove_value()");
	}

	// LL_remove_end()
	for (STYPE index = 0; index < LL_capacity; index++)
		assert_BOOL(TRUE, LL_remove_end(linked_list), "LL_remove_end()");

	assert_STYPE(linked_list->size, 0, "LL_remove_end()");
	assert_NULL(linked_list->head, "LL_remove_end()");
	assert_NULL(linked_list->tail, "LL_remove_end()");
	assert_BOOL(TRUE, LL_is_empty(linked_list), "LL_remove_end()");
	assert_BOOL(FALSE, LL_remove_end(linked_list), "LL_remove_end()");

	// LL_remove_start()
	LL_add_end(linked_list, 321);
	assert_BOOL(TRUE, LL_remove_start(linked_list), "LL_remove_start()");

	assert_STYPE(linked_list->size, 0, "LL_remove_start()");
	assert_NULL(linked_list->head, "LL_remove_start()");
	assert_NULL(linked_list->tail, "LL_remove_start()");
	assert_BOOL(TRUE, LL_is_empty(linked_list), "LL_remove_start()");
	assert_BOOL(FALSE, LL_remove_start(linked_list), "LL_remove_start()");

	// Completes linked list unit tests
	printf("===== COMPLETED LINKED LIST UNIT TESTS =====\n");
	return 0;
}
