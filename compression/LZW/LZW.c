#include "LZW.h"

static void c_info(size_of_files* size) {
	if (size->compressed_size == 0 || size->input_size == 0) {
		printf("Compressing error.\n");
		return;
	}
	else {
		printf("Succesful compressing.\n");
		double compress = ((double)size->compressed_size / (double)size->input_size) * 100;
		printf("Compression: %lg %c\n\n", compress, '%');
	}
}

static void d_info() {
	printf("Succesful decompressing.\n\n");
}

static void LZW_output(FILE* output, buffer* b, int code, size_of_files* size) {
	if (b->leftover > 0) {
		int prefix = (b->leftoverBits << (_CODE_SIZE - 8)) + (code >> 8);
		fputc(prefix, output);
		fputc(code, output);
		b->leftover = 0;
		size->compressed_size += 2;
	}
	else {
		b->leftoverBits = code & 0x0f;
		b->leftover = 1;
		fputc(code >> (_CODE_SIZE - 8), output);
		size->compressed_size++;
	}
}

static int LZW_input(FILE * input, buffer* b) {
	int code = fgetc(input);
	if (code == EOF) {
		return EOF;
	}
	if (b->leftover > 0) {
		code = (b->leftoverBits << 8) + code;
		b->leftover = 0;
	}
	else {
		int nextCode = fgetc(input);
		b->leftoverBits = nextCode & 0x0f;
		b->leftover = 1;
		code = (code << (_CODE_SIZE - 8)) + (nextCode >> (_CODE_SIZE - 8));
	}
	return code;
}

void LZW_encoding(char* input_file, char* compressed_file) {
	FILE *input = NULL, *output = NULL;
	if (r_open_file(&input, input_file) != 0 && w_open_file(&output, compressed_file) != 0) {
		printf("Compressing...\n");
		size_of_files size;
		dictionary dict;
		dictionary_init(&dict);
		int codes_count = 256;
		buffer b;
		b.leftover = 0;

		int prefix = fgetc(input), current;
		if (prefix == EOF) {
			return;
		}
		else {
			size.input_size = 1;
			size.compressed_size = 0;
			while ((current = fgetc(input)) != EOF) {
				size.input_size++;
				int index = dictionary_search(&dict, prefix, current);
				if (index != -1) {
					prefix = index;
				}
				else {
					LZW_output(output, &b, prefix, &size);
					if (codes_count < _DICT_SIZE) {
						dictionary_add(&dict, prefix, current, codes_count);
						codes_count++;
					}
					prefix = current;
				}
			}
			LZW_output(output, &b, prefix, &size);
			if (b.leftover > 0) {
				fputc(b.leftoverBits << (_CODE_SIZE - 8), output);
				size.compressed_size++;
			}
			c_info(&size);
			dictionary_destroy(&dict);
			fclose(input);
			fclose(output);
		}
	}
}

static int decode(dict_element* dictionaryArray, int code, FILE* fp) {
	int current, prefix;
	if (code > 255) {
		current = dict_array_current(dictionaryArray, code);
		prefix = decode(dictionaryArray, dict_array_prefix(dictionaryArray, code), fp);
	}
	else {
		current = code;
		prefix = code;
	}
	fputc(current, fp);
	return prefix;
}

void LZW_decoding(char* compressed_file, char* output_file) {
	FILE *input = NULL, *output = NULL;
	if (r_open_file(&input, compressed_file) != 0 && w_open_file(&output, output_file) != 0) {
		printf("Decompressing...\n");
		dict_element dict_array[_DICT_SIZE];
		int prefix; int current;
		int codes_count = 256;
		buffer b;
		b.leftover = 0;
		
		prefix = LZW_input(input, &b);
		if (prefix == EOF) {
			return;
		}
		else {
			fputc(prefix, output);
			while ((current = LZW_input(input, &b)) != EOF) {
				int first_byte;
				if (current >= codes_count) {
					first_byte = decode(dict_array, prefix, output);
					fputc(first_byte, output);
				}
				else {
					first_byte = decode(dict_array, current, output);
				}
				if (codes_count < _DICT_SIZE) {
					dict_array_add(dict_array, prefix, first_byte, codes_count);
					codes_count++;
				}
				prefix = current;
			}
			d_info();
			fclose(input);
			fclose(output);
		}
	}
}