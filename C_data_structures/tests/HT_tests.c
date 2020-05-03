#include <stdio.h>
#include "testing.h"

int main() {

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
	return 0;
}
