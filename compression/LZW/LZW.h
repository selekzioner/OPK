#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "dictionary.h"
#include "file.h"
#include "dict_array.h"

#define _DICT_SIZE 4096
#define _CODE_SIZE 12

typedef struct {
	int leftover;
	int leftoverBits;
}buffer;

typedef struct {
	size_t input_size;
	size_t compressed_size;
}size_of_files;

void LZW_encoding(char* input_file, char* compressed_file);

void LZW_decoding(char* compressed_file, char* output_file);
