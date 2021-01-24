#include "dict_array.h"

void dict_array_add(dict_element* dict_array, int prefix, int character, int pos) {
	dict_array[pos].prefix = prefix;
	dict_array[pos].character = character;
}

int dict_array_prefix(dict_element* dict_array, int pos) {
	return dict_array[pos].prefix;
}

int dict_array_current(dict_element* dict_array, int pos) {
	return dict_array[pos].character;
}