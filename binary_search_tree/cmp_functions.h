#pragma once
#include "BST.h"

typedef struct tEntry {
	Pointer key;
	Pointer value;
} Entry;

int int_cmp(Pointer a, Pointer b);

int double_cmp(Pointer a, Pointer b);

void int_mult(Pointer a, Pointer b);

void double_mult(Pointer a, Pointer b);

int Entry_cmp(Entry* a, Entry* b);