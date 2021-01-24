#include "Huffman.h"

static void statistics_of_letters(FILE* fp, unsigned int* freq_arr, size_t* data_size) {
	for (size_t i = 0; ; i++) {
		int tmp = fgetc(fp);
		if (tmp == EOF) {
			break;
		}
		unsigned char letter = (unsigned char)tmp;
		freq_arr[letter]++;
		*data_size = i + 1;
	}
	rewind(fp);
}

static void print_info(code_table* table, size_t input_size, unsigned int* freq_arr) {
	if (table->encodings != NULL) {
		printf("Succesful compressing.\n");
		size_t file_size = 0;
		unsigned table_size = sizeof(unsigned int) + sizeof(size_t);
		for (int i = 0; i < 256; i++) {
			if (freq_arr[i] != 0) {
				file_size += table->len[i] * freq_arr[i];
				table_size += sizeof(unsigned char) + sizeof(int);
			}
		}
		printf("Size of code table: %lu bytes\n", table_size);
		double comp;
		if (file_size % 8 != 0) {
			file_size = file_size / 8 + 1;
		}
		else {
			file_size = file_size / 8;
		}
		comp = 100 * (double)(table_size + file_size) / (double)(input_size);
		printf("Size of compressed data: %zu bytes\n", file_size);
		printf("Compression: %lg %c\n", comp, '%');
	}
	else {
		printf("Compress error\n");
	}
}

static void node_encodings(Huffman_node *node, code_table* table, unsigned char* code_buf, size_t max_len, unsigned pos) {
	if (node == NULL) {
		return;
	}
	if (node->left != 0) {
		code_buf[pos] = 0;
		node_encodings(node->left, table, code_buf, max_len, pos + 1);
	}
	if (node->right != 0) {
		code_buf[pos] = 1;
		node_encodings(node->right, table, code_buf, max_len, pos + 1);
	}
	if (node->left == 0 || node->right == 0) {
		table->len[node->data] = pos;
		Huffman_code_cpy(table->encodings + (max_len * node->data), code_buf, pos);
	}
}

static void table_create(code_table* table, Huffman_node* root, unsigned int* freq_arr) {
	table->max_len = node_height(root);
	table->encodings = malloc(sizeof(unsigned char) * table->max_len * 256);
	unsigned char* code_buf = malloc(table->max_len * sizeof(unsigned char));
	if (table->encodings == NULL || code_buf == NULL) {
		printf("Error: Memory wasn't allocated\n");
		return;
	}
	node_encodings(root, table, code_buf, table->max_len, 0);
	free(code_buf);
}

static void write_table(code_table* table, FILE* fp, unsigned int* freq_arr) {
	unsigned int table_size = 0;
	for (unsigned i = 0; i < 256; i++) {
		if (freq_arr[i] != 0) {
			table_size++;
		}
	}
	fwrite(&table_size, sizeof(unsigned int), 1, fp);
	for (unsigned int i = 0; i < 256; i++) {
		if (freq_arr[i] != 0) {
			fwrite(&(unsigned char)i, 1, 1, fp);
			fwrite(&freq_arr[i], sizeof(unsigned int), 1, fp);
		}
	}
}

static void Huffman_output(FILE* output, FILE* input, code_table* table, unsigned int* freq_arr, size_t data_size) {
	unsigned char mask[] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };
	unsigned char buf = 0x00;
	int count = 0;
	write_table(table, output, freq_arr);
	fwrite(&data_size, sizeof(size_t), 1, output);
	for (size_t i = 0; i < data_size; i++) {
		int tmp = fgetc(input);
		if (tmp == EOF) {
			break;
		}
		unsigned char letter = (unsigned char)tmp;
		for (unsigned int j = 0; j < table->len[letter]; j++, count++) {
			if (count == 8) {
				count = 0;
				fputc(buf, output);
				buf = 0x00;
			}
			if (table->encodings[table->max_len * letter + j] != 0) {
				buf |= mask[count];
			}
		}
	}
	fputc(buf, output);
	fclose(output);
	fclose(input);
}

void Huffman_encoding(unsigned char* input_file, unsigned char* compressed_file) {
	FILE *input = NULL, *output = NULL;
	size_t data_size = 0;
	if (r_open_file(&input, input_file) != 0 && w_open_file(&output, compressed_file) != 0) {
		unsigned int freq_arr[256] = {0};
		printf("Compressing...\n");
		statistics_of_letters(input, freq_arr, &data_size);

		Huffman_node *root = NULL;
		tree_create(&root, freq_arr);

		code_table table;
		table_create(&table, root, freq_arr);

		Huffman_output(output, input, &table, freq_arr, data_size);

		print_info(&table, data_size, freq_arr);

		tree_destroy(root);
		table_destroy(&table);
	}
}