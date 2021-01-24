#include "cmp_functions.h"

int larger(Pointer a, Pointer b) {
	return a <= b;
}

int smaller(Pointer a, Pointer b) {
	return a >= b;
}

void int_mult(Pointer a, Pointer b) {
	*(int*)a *= *(int*)b;
}

void double_mult(Pointer a, Pointer b) {
	*(double*)a *= *(double*)b;
}
