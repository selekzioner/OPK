#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "AVLTree.h"
#include "dict_array.h"
#define emptyPrefix -1

typedef struct dictionary_node_t {
	int pos;
	int prefix;
	int current;
}dictionary_node;

typedef struct dictionary_t {
	AVLTree* tree;
}dictionary;

void dictionary_init(dictionary* dict);

void dictionary_destroy(dictionary* dict);

void dictionary_add(dictionary* dict, int prefix, int character, int pos);

int dictionary_search(dictionary* dict, int prefix, int character);