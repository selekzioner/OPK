#include "AVLTree.h"

static unsigned height(AVLTreeNode* node){
	if (node != NULL)
		return node->height;
	else
		return 0;
}

static int height_difference(AVLTreeNode* node){
	if (node != NULL)
		return height(node->right) - height(node->left);
	else 
		return 0;
}

static void correct_height(AVLTreeNode* node){
	if (node != NULL) {
		unsigned h_left = height(node->left), h_right = height(node->right);
		if (h_left > h_right)
			node->height = h_left + 1;
		else
			node->height = h_right + 1;
	}
}

static AVLTreeNode* rot_right(AVLTreeNode* p){
	AVLTreeNode* q = p->left;
	p->left = q->right;
	q->right = p;
	correct_height(p);
	correct_height(q);
	return q;
}

static AVLTreeNode* rot_left(AVLTreeNode* q){
	AVLTreeNode* p = q->right;
	q->right = p->left;
	p->left = q;
	correct_height(q);
	correct_height(p);
	return p;
}

static AVLTreeNode* balance(AVLTreeNode* node){
	correct_height(node);
	if (height_difference(node) == 2){
		if (height_difference(node->right) < 0)
			node->right = rot_right(node->right);
		return rot_left(node);
	}

	if (height_difference(node) == -2){
		if (height_difference(node->left) > 0)
			node->left = rot_left(node->left);
		return rot_right(node);
	}
	else
		return node;
}

static AVLTreeNode *correct_balance1(AVLTreeNode *node) {
	if (node == NULL)
		return 0;
	node->right = correct_balance1(node->right);
	node->left = correct_balance1(node->left);
	return balance(node);
}

static AVLTreeNode* correct_balance(AVLTreeNode *node, Pointer data, int cmp(Pointer, Pointer)) {
	if (node == NULL)
		return 0;
	else if (cmp(node->data, data) == -1)
		node->right = correct_balance(node->right, data, cmp);
	else if (cmp(node->data, data) == 1)
		node->left = correct_balance(node->left, data, cmp);

	return balance(node);
}

AVLTree *avl_create(CmpFunc cmp_func) {
	AVLTree *tree = malloc(sizeof(AVLTree));
	if (tree == NULL) {
		printf("Memory wasn't allocated");
		return NULL;
	}
	tree->root = NULL;
	tree->cmp_func = cmp_func;
	tree->count = 0;
	return tree;
}

void avl_clear(AVLTree *tree, void Destructor(Pointer data)) {
	if (tree->root == NULL)
		return;
	AVLTreeNode *left = tree->root->left, *right = tree->root->right, *root = tree->root;
	Destructor(tree->root->data);
	tree->root = left;
	avl_clear(tree, Destructor);
	tree->root = right;
	avl_clear(tree, Destructor);
	free(root);
}

void avl_destroy(AVLTree *tree, void Destructor(Pointer data)) {
	avl_clear(tree, Destructor);
	free(tree);
}

size_t avl_size(AVLTree *tree) {
	return tree->count;
}

Pointer avl_find(AVLTree *tree, Pointer data) {
	const AVLTreeNode *current_node = tree->root;
	for (;;) {
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

Pointer avl_insert(AVLTree *tree, Pointer data) {
	AVLTreeNode *node = tree->root, **ptr = &tree->root;

	for (;;) {
		if (*ptr == NULL) {
			*ptr = malloc(sizeof(AVLTreeNode));
			if (*ptr == NULL) {
				printf("Memory wasn't allocated\n");
				return NULL;
			}
			(*ptr)->data = data;
			(*ptr)->left = (*ptr)->right = NULL;
			tree->count++;

			tree->root = correct_balance(tree->root, data, *tree->cmp_func);
			return NULL;
		}

		else if ((*tree->cmp_func)((*ptr)->data, data) == 0) {
			Pointer tmp = (*ptr)->data;
			(*ptr)->data = data;
			return tmp;
		}

		else if ((*tree->cmp_func)((*ptr)->data, data) == -1) 
			ptr = &(*ptr)->right;
		
		else
			ptr = &(*ptr)->left;
	}
}

Pointer avl_delete(AVLTree *tree, Pointer data) {
	AVLTreeNode *node = tree->root, **ptr = &tree->root;

	for (;;) {
		if (node == NULL)
			return 0;
		else if ((*tree->cmp_func)(node->data, data) == 0)
			break;
		else if ((*tree->cmp_func)(node->data, data) == -1) {
			ptr = &node->right;
			node = node->right;
		}
		else {
			ptr = &node->left;
			node = node->left;
		}
	}

	if (node->right == NULL)
		*ptr = node->left;
	else {
		AVLTreeNode *y = node->right;
		if (node->right->left == NULL) {
			node->right->left = node->left;
			*ptr = node->right;
		}
		else {
			AVLTreeNode *x = y->left;
			while (x->left != NULL) {
				y = x;
				x = y->left;
			}

			y->left = x->right;
			x->left = node->left;
			x->right = node->right;
			*ptr = x;
		}
	}

	tree->count--;
	Pointer return_data = node->data;
	free(node);
	tree->root = correct_balance(tree->root, data, *tree->cmp_func);
	return return_data;
}

static void avl_traversal(AVLTreeNode *node,
	void(*foreach_func)(Pointer data, Pointer extra_data), Pointer extra_data) {
	if (node == NULL)
		return;
	avl_traversal(node->right, foreach_func, extra_data);
	avl_traversal(node->left, foreach_func, extra_data);
	(*foreach_func)(node->data, extra_data);
}

void avl_foreach(AVLTree *tree, 
	void(*foreach_func)(Pointer data, Pointer extra_data), Pointer extra_data) {
	avl_traversal(tree->root, foreach_func, extra_data);
}

static int avl_check_node(AVLTreeNode *node) {
	int check = 1;
	if (node == NULL)
		return 1;
	check *= avl_check_node(node->right);
	check *= avl_check_node(node->left);
	int diff = height_difference(node);
	return (-1 <= diff && diff <= 1);
}

int avl_check(AVLTree *tree) {
	return avl_check_node(tree->root);
}