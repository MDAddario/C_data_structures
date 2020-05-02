#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

void assert_STYPE(STYPE a, STYPE b, char* title) {

	if (a != b) {
		printf("STYPE assertion failure at section %s.\n", title);
		exit(0);
	}
}

void assert_AL_DTYPE(AL_DTYPE* a, AL_DTYPE* b, char* title) {

	if (!AL_DTYPE_EQUALS(a, b)) {
		printf("AL DTYPE assertion failure at section %s.\n", title);
		exit(0);
	}
}

void assert_LL_DTYPE(LL_DTYPE* a, LL_DTYPE* b, char* title) {

	if (!LL_DTYPE_EQUALS(a, b)) {
		printf("LL DTYPE assertion failure at section %s.\n", title);
		exit(0);
	}
}

void assert_BOOL(BOOL a, BOOL b, char* title) {

	if (a != b) {
		printf("BOOL assertion failure at section %s.\n", title);
		exit(0);
	}
}

void assert_NULL(void* ptr, char* title) {

	if (ptr != NULL) {
		printf("NULL assertion failure at section %s.\n", title);
		exit(0);
	}
}

int main() {

/*****************************************************************/

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

		AL_location = AL_index_of(array_list, new_integer(AL_offsets[0]) + AL_capacity - index);
		assert_STYPE(index, AL_location, "AL_index_of()");
		AL_location = AL_index_of(array_list, new_integer(AL_offsets[1]) + index + 1);
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

/*****************************************************************/

/*****************************************************************/
	/*
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

	*/
/*****************************************************************/
	/*
	// Conduct hash table unit tests
	printf("===== CONDUCTING HASH TABLE UNIT TESTS =====\n");

	// Create a hash table
	HT* table = new_HT(5);

	if (table->num_entries != 0)
		printf("Error 1");
	if (table->num_buckets != 5)
		printf("Error 2");

	// Random value pairs
	char* my_keys[] = {"one", "two", "three", "four", "five"};
	int my_values[] = {1, 2, 3, 4, 5};

	// put()
	for (int i = 0; i < 3; i++)
		if (HT_put(table, my_keys[i], my_values[i]) != VAL_DTYPE_NULL)
			printf("Error 3");

	if (table->num_entries != 3)
		printf("Error 4");
	if (table->num_buckets != 5)
		printf("Error 5");

	if (HT_put(table, "one", 404) != 1)
		printf("Error 6");
	if (HT_put(table, "one", 1) != 404)
		printf("Error 7");

	if (table->num_entries != 3)
		printf("Error 8");
	if (table->num_buckets != 5)
		printf("Error 9");

	// get()
	for (int i = 0; i < 3; i++)
		if (HT_get(table, my_keys[i]) != i + 1)
			printf("Error 10");
	for (int i = 3; i < 5; i++)
		if (HT_get(table, my_keys[i]) != VAL_DTYPE_NULL)
			printf("Error 11");

	if (table->num_entries != 3)
		printf("Error 12");
	if (table->num_buckets != 5)
		printf("Error 13");

	// remove()
	for (int i = 3; i < 5; i++)
		if (HT_remove(table, my_keys[i]) != VAL_DTYPE_NULL)
			printf("Error 14");

	if (table->num_entries != 3)
		printf("Error 15");
	if (table->num_buckets != 5)
		printf("Error 16");

	for (int i = 0; i < 3; i++)
		if (HT_remove(table, my_keys[i]) != i + 1)
			printf("Error 17");

	if (table->num_entries != 0)
		printf("Error 18");
	if (table->num_buckets != 5)
		printf("Error 19");

	// rehash()
	for (int i = 0; i < 4; i++)
		if (HT_put(table, my_keys[i], my_values[i]) != VAL_DTYPE_NULL)
			printf("Error 20");

	if (table->num_entries != 4)
		printf("Error 21");
	if (table->num_buckets != 10)
		printf("Error 22");

	for (int i = 0; i < 4; i++)
		if (HT_put(table, my_keys[i], my_values[i]) != i + 1)
			printf("Error 22.5");
	for (int i = 0; i < 4; i++)
		if (HT_get(table, my_keys[i]) != i + 1)
			printf("Error 23");
	for (int i = 4; i < 5; i++)
		if (HT_get(table, my_keys[i]) != VAL_DTYPE_NULL)
			printf("Error 24");

	if (table->num_entries != 4)
		printf("Error 25");
	if (table->num_buckets != 10)
		printf("Error 26");

	for (int i = 0; i < 4; i++)
		if (HT_remove(table, my_keys[i]) != i + 1)
			printf("Error 27");

	if (table->num_entries != 0)
		printf("Error 28");
	if (table->num_buckets != 10)
		printf("Error 29");

	for (int i = 0; i < 5; i++)
		if (HT_put(table, my_keys[i], my_values[i]) != VAL_DTYPE_NULL)
			printf("Error 30");

	if (table->num_entries != 5)
		printf("Error 31");
	if (table->num_buckets != 10)
		printf("Error 32");

	/*
	// keys()
	ArrayList<String> keys = table.keys();
	if (keys.size() != 5)
		printf("Error 33");
	for (int i = 0; i < 5; i++)
		if (!keys.contains(my_keys[i]))
			printf("Error 34");

	// values()
	if (HT_put(table, "duplicate", 3) != NULL)
		printf("Error 34.3");
	if (table->num_entries != 6)
		printf("Error 34.5");
	if (table->num_buckets != 10)
		printf("Error 34.8");

	ArrayList<Integer> values = table.values();
	if (values.size() != 5)
		printf("Error 35");
	for (int i = 0; i < 5; i++)
		if (!values.contains(my_values[i]))
			printf("Error 36");

	if (HT_remove(table, "duplicate") != 3)
		printf("Error 36.3");
	if (table->num_entries != 5)
		printf("Error 36.5");
	if (table->num_buckets != 10)
		printf("Error 36.8");

	// Completes hash table unit tests
	printf("===== COMPLETED HASH TABLE UNIT TESTS =====\n");
	*/
/*****************************************************************/

	// All tests pass
	printf("\n===== ALL TESTS HAVE PASSED! =====\n");
	return 0;
}
