#include "Huffman.h"

int Huffman_node_cmp(Pointer p, Pointer q) {
	Huffman_node* i = (Huffman_node*)p, *j = (Huffman_node*)q;
	unsigned a = i->freq, b = j->freq;
	if (a < b)
		return -1;
	else if (a > b)
		return 1;
	else
		return 0;
}

void Huffman_code_cpy(unsigned char* a, unsigned char* b, size_t len) {
	for (size_t i = 0; i < len; i++) {
		a[i] = b[i];
	}
}

static Huffman_node* node_create(unsigned char data, unsigned int freq) {
	Huffman_node* node = malloc(sizeof(Huffman_node));
	if (node == NULL) {
		printf("Error: memory wasn't allocated.\n");
		return NULL;
	}
	node->data = data;
	node->freq = freq;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void tree_create(Huffman_node** root, unsigned int* freq_arr) {
	Huffman_node* node;
	Stack node_stack;
	stack_create(&node_stack);
	for (unsigned i = 0; i < 256; i++) {
		if (freq_arr[i] != 0) {
			unsigned char letter = (unsigned char)i;
			node = node_create(letter, freq_arr[letter]);
			stack_push(&node_stack, (Pointer)node);
		}
	}
	sort_stack(&node_stack, Huffman_node_cmp);
	while (node_stack.size > 1) {
		Huffman_node *right = stack_pop(&node_stack);
		Huffman_node *left = stack_pop(&node_stack);
		node = node_create('*', left->freq + right->freq);
		node->left = left;
		node->right = right;
		stack_push(&node_stack, (Pointer)node);
		sort_stack(&node_stack, Huffman_node_cmp);
	}
	*root = stack_pop(&node_stack);
	stack_destroy(&node_stack);
}

void tree_destroy(Huffman_node *root) {
	if (root == NULL)
		return;
	tree_destroy(root->right);
	tree_destroy(root->left);
	free(root);
}

void table_destroy(code_table* table) {
	if (table == NULL) {
		return;
	}
	else if (table->encodings != NULL) {
		free(table->encodings);
	}
}

static unsigned maximum(unsigned int a, unsigned int b) {
	return a > b ? a : b;
}

unsigned int node_height(Huffman_node *node) {
	if (node == NULL) {
		return 0;
	}
	unsigned int height = 0;
	if (node->left != 0 || node->right != 0) {
		height = maximum(node->left != 0 ? node_height(node->left) : 0,
			node->right != 0 ? node_height(node->right) : 0) + 1;
	}
	return height;
}