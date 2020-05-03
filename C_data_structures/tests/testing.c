#include <stdio.h>
#include <stdlib.h>
#include "testing.h"

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
