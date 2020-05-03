#include <stdio.h>
#include "testing.h"

int main() {

	// Conduct array list unit tests
	printf("===== CONDUCTING ARRAY LIST UNIT TESTS =====\n");

	// new_AL()
	STYPE AL_capacity = 0;
	AL* array_list = new_AL(AL_capacity);
	assert_STYPE(array_list->size, 0, "new_AL()");
	assert_STYPE(array_list->capacity, AL_DEFAULT_CAP, "new_AL()");

	AL_capacity = 431;
	array_list = new_AL(AL_capacity);
	assert_STYPE(array_list->size, 0, "new_AL()");
	assert_STYPE(array_list->capacity, AL_capacity, "new_AL()");

	for (STYPE j = 0; j < AL_capacity; j++)
		array_list->array[j] = new_integer(0);     // Ensure no segfaults

	// free_AL()
	printf("Testing memory management: ");
	for (STYPE i = 0; i < 10; i++) {
		for (STYPE j = 0; j < 1000000; j++) {
			AL* array_list_2 = new_AL(1000000);
			AL_free(array_list_2);
		}
		printf("%ld%% ", (i + 1) * 10);
	}
	printf("\n");

	STYPE AL_offsets[] = {1000, 2000, 3000};

	// AL_add_start()
	AL_DTYPE* AL_value;
	for (STYPE size = 1; size <= AL_capacity; size++) {

		AL_value = new_integer(size + AL_offsets[0]);
		AL_add_start(array_list, AL_value);
		assert_STYPE(array_list->size, size, "AL_add_start()");
		assert_STYPE(array_list->capacity, AL_capacity, "AL_add_start()");
	}

	for (STYPE index = 0; index < AL_capacity; index++) {

		AL_value = array_list->array[index];
		assert_AL_DTYPE(AL_value, new_integer(AL_offsets[0] + AL_capacity - index), "AL_add_start()");
		assert_STYPE(array_list->size, AL_capacity, "AL_add_start()");
		assert_STYPE(array_list->capacity, AL_capacity, "AL_add_start()");
	}

	// AL_add_end()
	for (STYPE size = 1; size <= AL_capacity; size++) {

		AL_value = new_integer(size + AL_offsets[1]);
		AL_add_end(array_list, AL_value);
		assert_STYPE(array_list->size, size + AL_capacity, "AL_end()");
		assert_STYPE(array_list->capacity, 2 * AL_capacity, "AL_end()");
	}

	for (STYPE index = 0; index < AL_capacity; index++) {

		AL_value = array_list->array[index + AL_capacity];
		assert_AL_DTYPE(AL_value, new_integer(AL_offsets[1] + index + 1), "AL_end()");
		assert_STYPE(array_list->size, 2 * AL_capacity, "AL_end()");
		assert_STYPE(array_list->capacity, 2 * AL_capacity, "AL_end()");
	}

	// AL_add_at()
	AL_add_at(array_list, new_integer(AL_offsets[2]), AL_capacity);
	assert_STYPE(array_list->size, 2 * AL_capacity + 1, "AL_add_at()");
	assert_STYPE(array_list->capacity, 4 * AL_capacity, "AL_add_at()");

	for (STYPE index = 0; index < AL_capacity; index++) {

		AL_value = array_list->array[index];
		assert_AL_DTYPE(AL_value, new_integer(AL_offsets[0] + AL_capacity - index), "AL_add_at()");
		AL_value = array_list->array[index + AL_capacity + 1];
		assert_AL_DTYPE(AL_value, new_integer(AL_offsets[1] + index + 1), "AL_add_at()");
	}
	AL_value = array_list->array[AL_capacity];
	assert_AL_DTYPE(AL_value, new_integer(AL_offsets[2]), "AL_add_at()");

	assert_BOOL(FALSE, AL_add_at(array_list, new_integer(AL_offsets[0]), -1), "AL_add_at()");
	assert_BOOL(FALSE, AL_add_at(array_list, new_integer(AL_offsets[0]), 2 * AL_capacity + 2), "AL_add_at()");

	// AL_get()
	for (STYPE index = 0; index < 2 * AL_capacity; index++) {

		AL_value = array_list->array[index];
		assert_AL_DTYPE(AL_value, AL_get(array_list, index), "AL_get()");
	}

	// AL_size()
	assert_STYPE(array_list->size, AL_size(array_list), "AL_size()");
	assert_STYPE(2 * AL_capacity + 1, AL_size(array_list), "AL_size()");

	// AL_clear()
	assert_BOOL(AL_is_empty(array_list), FALSE, "AL_is_empty()");
	AL_clear(array_list);
	assert_STYPE(AL_size(array_list), 0, "AL_clear()");

	// AL_is_empty()
	assert_BOOL(AL_is_empty(array_list), TRUE, "AL_is_empty()");

	for (STYPE size = 1; size <= AL_capacity; size++) {

		AL_value = new_integer(size + AL_offsets[0]);
		AL_add_start(array_list, AL_value);
		AL_value = new_integer(size + AL_offsets[1]);
		AL_add_end(array_list, AL_value);
	}

	for (STYPE index = 0; index < AL_capacity; index++) {

		AL_value = AL_get(array_list, index);
		assert_AL_DTYPE(AL_value, new_integer(AL_offsets[0] + AL_capacity - index), "AL_clear()");
		AL_value = AL_get(array_list, index + AL_capacity);
		assert_AL_DTYPE(AL_value, new_integer(AL_offsets[1] + index + 1), "AL_clear()");
		assert_STYPE(array_list->size, 2 * AL_capacity, "AL_clear()");
	}
	AL_add_at(array_list, new_integer(AL_offsets[2]), AL_capacity);
	AL_value = AL_get(array_list, AL_capacity);
	assert_AL_DTYPE(AL_value, new_integer(AL_offsets[2]), "AL_add_at()");

	// AL_index_of()
	STYPE AL_location;
	for (STYPE index = 0; index < AL_capacity; index++) {

		AL_location = AL_index_of(array_list, new_integer(AL_offsets[0] + AL_capacity - index));
		assert_STYPE(index, AL_location, "AL_index_of()");
		AL_location = AL_index_of(array_list, new_integer(AL_offsets[1] + index + 1));
		assert_STYPE(index + AL_capacity + 1, AL_location, "AL_index_of()");
	}
	AL_location = AL_index_of(array_list, new_integer(AL_offsets[2]));
	assert_STYPE(AL_capacity, AL_location, "AL_index_of()");

	// AL_contains()
	for (STYPE increment = 1; increment <= AL_capacity; increment++) {

		assert_BOOL(TRUE, AL_contains(array_list, new_integer(AL_offsets[0] + increment)), "AL_contains()");
		assert_BOOL(TRUE, AL_contains(array_list, new_integer(AL_offsets[1] + increment)), "AL_contains()");
		assert_BOOL(FALSE, AL_contains(array_list, new_integer(AL_offsets[0] - increment)), "AL_contains()");
		assert_BOOL(FALSE, AL_contains(array_list, new_integer(AL_offsets[1] - increment)), "AL_contains()");
	}
	assert_BOOL(TRUE, AL_contains(array_list, new_integer(AL_offsets[2])), "AL_contains()");

	// Pray this still holds
	assert_STYPE(array_list->size, 2 * AL_capacity + 1, "AL_prayers()");
	assert_STYPE(array_list->capacity, 4 * AL_capacity, "AL_prayers()");

	// AL_remove_at()
	assert_BOOL(FALSE, AL_remove_at(array_list, -1), "AL_remove_at()");
	assert_BOOL(FALSE, AL_remove_at(array_list, 2 * AL_capacity + 1), "AL_remove_at()");

	assert_BOOL(TRUE, AL_remove_at(array_list, AL_capacity), "AL_remove_at()");
	assert_STYPE(2 * AL_capacity, AL_size(array_list), "AL_remove_at()");
	assert_STYPE(2 * AL_capacity, array_list->size, "AL_remove_at()");
	assert_STYPE(4 * AL_capacity, array_list->capacity, "AL_remove_at()");

	for (STYPE index = 0; index < AL_capacity; index++) {

		AL_value = array_list->array[index];
		assert_AL_DTYPE(AL_value, new_integer(AL_offsets[0] + AL_capacity - index), "AL_remove_at()");
		AL_value = array_list->array[index + AL_capacity];
		assert_AL_DTYPE(AL_value, new_integer(AL_offsets[1] + index + 1), "AL_remove_at()");
	}

	// AL_remove_value()
	assert_BOOL(FALSE, AL_remove_value(array_list, new_integer(-1)), "AL_remove_value()");
	assert_BOOL(FALSE, AL_remove_value(array_list, new_integer(AL_offsets[2])), "AL_remove_value()");

	for (STYPE size = 1; size <= AL_capacity; size++) {

		AL_value = new_integer(size + AL_offsets[0]);
		assert_BOOL(TRUE, AL_remove_value(array_list, AL_value), "AL_remove_value()");
		assert_STYPE(array_list->size, 2 * AL_capacity - size, "AL_remove_value()");
		assert_STYPE(array_list->capacity, 4 * AL_capacity, "AL_remove_value()");
	}

	for (STYPE index = 0; index < AL_capacity; index++) {

		AL_value = AL_get(array_list, index);
		assert_AL_DTYPE(AL_value, new_integer(AL_offsets[1] + index + 1), "AL_remove_remove_value()");
	}

	// AL_remove_end()
	for (STYPE index = 0; index < AL_capacity; index++)
		assert_BOOL(TRUE, AL_remove_end(array_list), "AL_remove_end()");

	assert_STYPE(array_list->size, 0, "AL_remove_end()");
	assert_BOOL(TRUE, AL_is_empty(array_list), "AL_remove_end()");
	assert_BOOL(FALSE, AL_remove_end(array_list), "AL_remove_end()");

	// AL_remove_start()
	AL_add_end(array_list, new_integer(321));
	assert_BOOL(TRUE, AL_remove_start(array_list), "AL_remove_start()");

	assert_STYPE(array_list->size, 0, "AL_remove_start()");
	assert_BOOL(TRUE, AL_is_empty(array_list), "AL_remove_start()");
	assert_BOOL(FALSE, AL_remove_start(array_list), "AL_remove_start()");

	// Completes array list unit tests
	printf("===== COMPLETED ARRAY LIST UNIT TESTS =====\n");
	return 0;
}
