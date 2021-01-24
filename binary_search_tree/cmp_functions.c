#include "cmp_functions.h"

int int_cmp(Pointer a, Pointer b) {
	int int_a = *(int*)a, int_b = *(int*)b;

	if (int_a > int_b)
		return 1;
	else if (int_a < int_b)
		return -1;
	else
		return 0;
}

int double_cmp(Pointer a, Pointer b) {
	double double_a = *(double*)a, double_b = *(double*)b;

	if (double_a > double_b)
		return 1;
	else if (double_a < double_b)
		return -1;
	else
		return 0;
}

void int_mult(Pointer a, Pointer b) {
	*(int*)a *= *(int*)b;
}

void double_mult(Pointer a, Pointer b) {
	*(double*)a *= *(double*)b;
}

int Entry_cmp(Entry* a, Entry* b) {
	return strcmp(*(char**)a->key, *(char**)b->key);
}

