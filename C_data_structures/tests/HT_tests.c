#include <stdio.h>
#include "testing.h"

int main() {

	// Conduct hash table unit tests
	printf("===== CONDUCTING HASH TABLE UNIT TESTS =====\n");

	// Create a hash table
	HT* table = new_HT(5);

	assert_STYPE(table->num_entries, 0, "Error 1");
	assert_STYPE(table->num_buckets, 5, "Error 2");

	// Random value pairs
	String* my_keys[] = {new_string("one"), new_string("two"), new_string("three"), new_string("four"), new_string("five")};
	Integer* my_values[] = {new_integer(1), new_integer(2), new_integer(3), new_integer(4), new_integer(5)};

	// put()
	for (STYPE i = 0; i < 3; i++)
		assert_NULL(HT_put(table, my_keys[i], my_values[i]), "Error 3");

	assert_STYPE(table->num_entries, 3, "Error 4");
	assert_STYPE(table->num_buckets, 5, "Error 5");

	assert_VAL_DTYPE(HT_put(table, new_string("one"), new_integer(404)), new_integer(1), "Error 6");
	assert_VAL_DTYPE(HT_put(table, new_string("one"), new_integer(1)), new_integer(404), "Error 7");

	assert_STYPE(table->num_entries, 3, "Error 8");
	assert_STYPE(table->num_buckets, 5, "Error 9");

	// get()
	for (STYPE i = 0; i < 3; i++)
		assert_VAL_DTYPE(HT_get(table, my_keys[i]), new_integer(i+1), "Error 10");

	for (STYPE i = 3; i < 5; i++)
		assert_NULL(HT_get(table, my_keys[i]), "Error 11");

	assert_STYPE(table->num_entries, 3, "Error 12");
	assert_STYPE(table->num_buckets, 5, "Error 13");

	// remove()
	for (STYPE i = 3; i < 5; i++)
		assert_NULL(HT_remove(table, my_keys[i]), "Error 14");

	assert_STYPE(table->num_entries, 3, "Error 15");
	assert_STYPE(table->num_buckets, 5, "Error 16");

	for (STYPE i = 0; i < 3; i++)
		assert_VAL_DTYPE(HT_remove(table, my_keys[i]), new_integer(i+1), "Error 17");

	assert_STYPE(table->num_entries, 0, "Error 18");
	assert_STYPE(table->num_buckets, 5, "Error 19");

	// rehash()
	for (STYPE i = 0; i < 4; i++)
		assert_NULL(HT_put(table, my_keys[i], my_values[i]), "Error 20");

	assert_STYPE(table->num_entries, 4, "Error 21");
	assert_STYPE(table->num_buckets, 10, "Error 22");

	for (STYPE i = 0; i < 4; i++)
		assert_VAL_DTYPE(HT_put(table, my_keys[i], my_values[i]), new_integer(i+1), "Error 22.5");
	for (STYPE i = 0; i < 4; i++)
		assert_VAL_DTYPE(HT_get(table, my_keys[i]), new_integer(i+1), "Error 23");
	for (STYPE i = 4; i < 5; i++)
		assert_NULL(HT_get(table, my_keys[i]), "Error 24");

	assert_STYPE(table->num_entries, 4, "Error 25");
	assert_STYPE(table->num_buckets, 10, "Error 26");

	for (STYPE i = 0; i < 4; i++)
		assert_VAL_DTYPE(HT_remove(table, my_keys[i]), new_integer(i+1), "Error 27");

	assert_STYPE(table->num_entries, 0, "Error 28");
	assert_STYPE(table->num_buckets, 10, "Error 29");

	for (STYPE i = 0; i < 5; i++)
		assert_NULL(HT_put(table, my_keys[i], my_values[i]), "Error 30");

	assert_STYPE(table->num_entries, 5, "Error 31");
	assert_STYPE(table->num_buckets, 10, "Error 32");

	/*
	// keys()
	String** keys = HT_keys(table);
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
	*/

	// Completes hash table unit tests
	printf("===== COMPLETED HASH TABLE UNIT TESTS =====\n");
	return 0;
}
