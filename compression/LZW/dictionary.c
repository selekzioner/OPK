#include "dictionary.h"

static int node_cmp(Pointer x, Pointer y) {
	dictionary_node* a = (dictionary_node*)x;
	dictionary_node* b = (dictionary_node*)y;
	if (a->prefix < b->prefix) {
		return -1;
	}
	else if (a->prefix > b->prefix) {
		return 1;
	}
	else if (a->current < b->current) {
		return -1;
	}
	else if (a->current > b->current) {
		return 1;
	}
	else {
		return 0;
	}
}

static void node_destroy(Pointer data){
	dictionary_node* node = (dictionary_node*)data;
	free(node);
}

void dictionary_init(dictionary* dict) {
	dict->tree = avl_create(node_cmp);
	for (int i = 0; i < 256; i++) {
		dictionary_add(dict, emptyPrefix, i, i);
	}
}

void dictionary_destroy(dictionary* dict) {
	avl_destroy(dict->tree, node_destroy);
}

void dictionary_add(dictionary* dict, int prefix, int current, int pos) {
	dictionary_node *node;
	node = malloc(sizeof(dictionary_node));
	if (node == NULL) {
		printf("Error: Memory wasn't allocated.\n");
		return;
	}
	else {
		node->pos = pos;
		node->prefix = prefix;
		node->current = current;
		avl_insert(dict->tree, node);
	}
}

int dictionary_search(dictionary* dict, int prefix, int current) {
	dictionary_node *node = malloc(sizeof(dictionary_node));
	if (node == NULL) {
		printf("Error: Memory wasn't allocated.\n");
		return -1;
	}
	node->current = current;
	node->prefix = prefix;
	dictionary_node* found_node = (dictionary_node*)avl_find(dict->tree, node);
	free(node);
	if (found_node != NULL) {
		return found_node->pos;
	}
	else {
		return emptyPrefix;
	}
}