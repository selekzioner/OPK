#include "BST.h"

BST *bst_create(CmpFunc cmp_func) {
	BST *tree = malloc(sizeof(BST));
	if (tree == NULL) {
		printf("Memory wasn't allocated");
		return NULL;
	}

	tree->root = NULL;
	tree->cmp_func = cmp_func;
	tree->count = 0;
	return tree;
}

void bst_clear(BST *tree) {
if (tree->root == NULL)
		return;
	BSTNode *left = tree->root->left, *right = tree->root->right, *root = tree->root;
	tree->root = left;
	bst_clear(tree);
	tree->root = right;
	bst_clear(tree);
	free(root);
}

void bst_destroy(BST *tree) {
	bst_clear(tree);
	free(tree);
}

size_t bst_size(BST *tree) {
	return tree->count;
}

Pointer bst_find(BST *tree, Pointer data) {
	const BSTNode *current_node = tree->root;
	for (;;){
		if (current_node == NULL)
			return 0;

		else if ((*tree->cmp_func)(current_node->data, data) == 0)
			return current_node->data;

		else if ((*tree->cmp_func)(current_node->data, data) == -1)
			current_node = current_node->right;

		else 
			current_node = current_node->left;
	}
}

Pointer bst_insert(BST *tree, Pointer data) {
	BSTNode *current_node = tree->root, **node_ptr = &tree->root;
	for (;;){
		if (current_node == NULL) {
			*node_ptr = malloc(sizeof(BSTNode));
			if (node_ptr == NULL) {
				printf("Memory wasn't allocated");
				return NULL;
			}
			current_node = *node_ptr;
			assert(current_node != NULL);
			current_node->data = data;
			current_node->left = current_node->right = NULL;
			tree->count++;
			return NULL;
		}
		else if ((*tree->cmp_func)(current_node->data, data) == 0) {
			Pointer tmp = current_node->data;
			current_node->data = data;
			return tmp;
		}

		else if ((*tree->cmp_func)(current_node->data, data) == -1) {
			node_ptr = &current_node->right;
			current_node = current_node->right;
		}
		
		else {
			node_ptr = &current_node->left;
			current_node = current_node->left; 
			
		}
	}
}

Pointer bst_delete(BST *tree, Pointer data) {
	BSTNode **node_ptr = &tree->root, *node = tree->root;
	
	for (;;){
		if (node == NULL)
			return 0;
		else if ((*tree->cmp_func)(node->data, data) == 0)
			break;
		else if ((*tree->cmp_func)(node->data, data) == -1){
			node_ptr = &node->right;
			node = node->right;
		}
		else {
			node_ptr = &node->left;
			node = node->left;
		}
	}

	if (node->right == NULL) 
		*node_ptr = node->left;
	else {
		BSTNode *y = node->right;
		if (node->right->left == NULL) {
			node->right->left = node->left;
			*node_ptr = node->right;
		}
		else {
			BSTNode *x = y->left;
			while (x->left != NULL) {
				y = x;
				x = y->left;
			}
			
			y->left = x->right;
			x->left = node->left;
			x->right = node->right;
			*node_ptr = x;
		}
	}

	tree->count--;
	Pointer return_data = node->data;
	free(node);
	return return_data;
}

static void bst_traversal(BSTNode *node, void(*foreach_func)(Pointer data, Pointer extra_data), Pointer extra_data) {
	if (node == NULL)
		return;
	bst_traversal(node->right, foreach_func, extra_data);
	bst_traversal(node->left, foreach_func, extra_data);
	(*foreach_func)(node->data, extra_data);
}

void bst_foreach(BST *tree, void(*foreach_func)(Pointer data, Pointer extra_data), Pointer extra_data) {
	bst_traversal(tree->root, foreach_func, extra_data);
	
	/*Stack stack;
	stack_create(&stack);
	BSTNode *node = tree->root;

	for (;;){
		while (node != NULL){
			stack_push(&stack, node);
			node = node->left;
		}
		if (stack.size == 0)
			break;
		node = stack_pop(&stack);
		(*foreach_func)(node->data, extra_data);
		node = node->right;
	}

	stack_destroy(&stack);*/
}


