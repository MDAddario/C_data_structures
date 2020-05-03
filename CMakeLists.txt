# cmake_minimum_required(VERSION <specify CMake version here>)
project(C_data_structures C)

set(CMAKE_C_STANDARD 11)

include_directories(C_data_structures)

add_executable(C_data_structures
				C_data_structures/define.c
				C_data_structures/define.h
				C_data_structures/hash_pair.c
				C_data_structures/hash_pair.h
				C_data_structures/linked_list.c
				C_data_structures/linked_list.h
				C_data_structures/array_list.c
				C_data_structures/array_list.h
				C_data_structures/hash_table.c
				C_data_structures/hash_table.h
				C_data_structures/tests/testing.c
				C_data_structures/tests/testing.h
				C_data_structures/tests/HT_tests.c)
