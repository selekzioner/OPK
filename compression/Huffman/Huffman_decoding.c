#include "Huffman.h"

static void d_print_info(Huffman_node* root) {
	if (root != NULL) {
		printf("Succesful decompressing.\n");
	}
	else {
		printf("Decompress error\n");
	}
}

static void node_decodings(Huffman_node *root, FILE* input, FILE* output, size_t len) {
	unsigned char mask[] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };
	Huffman_node *node = root;
	unsigned char buf = 0x00;
	if (node == NULL) {
		return;
	}
	else {
		for (unsigned int i = 0, count = 8; i < len; count++) {
			if (count == 8) {
				count = 0;
				buf = fgetc(input);
			}
			if (node->left == NULL && node->right == NULL) {
				fputc(node->data, output);
				node = root;
				count--;
				i++;
			}
			else {
				if ((buf & mask[count]) != 0) {
					node = node->right;
				}
				if ((buf & mask[count]) == 0) {
					node = node->left;
				}
			}
		}
	}
	fclose(input);
	fclose(output);
}

static void read_table(FILE* fp, unsigned int* freq_arr) {
	unsigned int table_size;
	fread(&table_size, sizeof(unsigned int), 1, fp);
	for (unsigned i = 0; i < table_size; i++) {
		unsigned char letter = fgetc(fp);
		fread(&freq_arr[letter], sizeof(unsigned int), 1, fp);
	}
}

void Huffman_decoding(unsigned char* compressed_file, unsigned char* output_file) {
	FILE *input = NULL, *output = NULL;
	if (r_open_file(&input, compressed_file) != 0 && w_open_file(&output, output_file) != 0) {
		unsigned int freq_arr[256] = { 0 };
		printf("Decompressing...\n");

		read_table(input, freq_arr);

		Huffman_node *root = NULL;
		tree_create(&root, freq_arr);

		size_t data_size;
		fread(&data_size, sizeof(size_t), 1, input);

		node_decodings(root, input, output, data_size);

		d_print_info(root);

		tree_destroy(root);
	}
}