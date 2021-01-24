#pragma once
#include <stdio.h>

typedef struct {
	int prefix;
	int character;
} dict_element;

void dict_array_add(dict_element* dict_array, int prefix, int character, int pos);

int dict_array_prefix(dict_element* dict_array, int pos);

int dict_array_current(dict_element* dict_array, int pos);