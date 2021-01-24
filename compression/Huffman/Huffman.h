#pragma once
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "stack.h"
#include "file.h"

typedef struct Huffman_node {
	unsigned char data;
	unsigned freq;
	struct Huffman_node *left, *right;
}Huffman_node;

typedef struct code_table {
	unsigned char* encodings;
	unsigned char max_len, len[256];
}code_table;


int Huffman_node_cmp(Pointer p, Pointer q);

void Huffman_code_cpy(unsigned char* a, unsigned char* b, size_t len);

void tree_create(Huffman_node** root, unsigned int* freq_arr);

void tree_destroy(Huffman_node *root);

void table_destroy(code_table* table);

unsigned int node_height(Huffman_node *node);

void Huffman_encoding(unsigned char* input_file, unsigned char* compressed_file);

void Huffman_decoding(unsigned char* compressed_file, unsigned char* input_file);