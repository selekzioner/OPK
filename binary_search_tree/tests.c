#include "tests.h"

void int_print_BST(Pointer data, Pointer a) {
	printf("%d ", *(int*)data);
}

void print_Entry(Pointer a, Pointer b) {
	Entry* x = (Entry*)a;
	printf("%s %d\n", *(char**)x->key, *(int*)x->value);
}

void Entry_print_Tree(BSTNode *node, int level) {
	if (node) {
		Entry_print_Tree(node->right, level + 1);
		for (int i = 0; i < level; i++)
			printf("   ");
		Entry *x = (Entry*)node->data;
		printf("%s %d\n", *(char**)x->key, *(int*)x->value);
		Entry_print_Tree(node->left, level + 1);
	}
}

void tests() {
	BST *tree = bst_create(&int_cmp);
	int arr[] = { 5, 10, 3, 4, 1, 6, 7, 8, 9, 2 }, equal_arr[] = { 5, 10, 3, 4, 1, 6, 7, 8, 9, 2 }, s = 10;

	for (int k = 0; k < 10; k++)//insert
		assert(bst_insert(tree, &arr[k]) == NULL);
	assert(bst_insert(tree, &s) == &arr[1]);
	assert(bst_insert(tree, &arr[1]) == &s);

	//bst_foreach(tree, &int_print_BST, NULL);

	assert(bst_size(tree) == 10);//size

	for (int k = 0; k < 10; k++)//find
		assert(bst_find(tree, &arr[k]) == &arr[k]);

	int c = 2;//foreach
	bst_foreach(tree, &int_mult, &c);
	for (int k = 0; k < 10; k++)
		assert(*(int*)bst_find(tree, &arr[k]) == c * equal_arr[k]);

	for (int k = 0; k < 5; k++)//delete
		assert(bst_delete(tree, &arr[k]) == &arr[k]);
	assert(bst_size(tree) == 5);
	for (int k = 0; k < 5; k++)
		assert(bst_find(tree, &arr[k]) == NULL);

	bst_clear(tree);
	assert(tree->root == NULL);
	bst_destroy(tree);


	BST *double_tree = bst_create(&double_cmp);
	double d_arr[] = { 5, 10, 3, 4, 1, 6, 7, 8, 9, 2 }, equal_d_arr[] = { 5, 10, 3, 4, 1, 6, 7, 8, 9, 2 };

	for (int k = 0; k < 10; k++)//insert
		assert(bst_insert(double_tree, &d_arr[k]) == NULL);

	assert(bst_size(double_tree) == 10);//size

	for (int k = 0; k < 10; k++)//find
		assert(bst_find(double_tree, &d_arr[k]) == &d_arr[k]);

	for (int k = 0; k < 5; k++)//delete
		assert(bst_delete(double_tree, &d_arr[k]) == &d_arr[k]);
	assert(bst_size(double_tree) == 5);
	for (int k = 0; k < 5; k++)
		assert(bst_find(double_tree, &d_arr[k]) == NULL);

	double d = 2;//foreach
	bst_foreach(double_tree, &double_mult, &d);
	for (int k = 5; k < 10; k++) {
		double_mult(&equal_d_arr[k], &d);
		assert(*(double*)bst_find(double_tree, &d_arr[k]) == equal_d_arr[k]);
	}

	bst_clear(double_tree);
	assert(double_tree->root == NULL);
	bst_destroy(double_tree);

	BST *big_tree = bst_create(&int_cmp);
	int b_arr[1000], equal_b_arr[1000];

	for (int k = 0, q = 500, p=501; k < 1000; k ++, q--, p++) {
		if (k % 2 == 0)
			equal_b_arr[k] = b_arr[k] = q;
		if (k % 2 == 1)
			equal_b_arr[k] = b_arr[k] = p;
	}

	for (int k = 0; k < 1000; k++)//insert
		assert(bst_insert(big_tree, &b_arr[k]) == NULL);

	assert(bst_size(big_tree) == 1000);//size

	for (int k = 0; k < 1000; k++)//find
		assert(bst_find(big_tree, &b_arr[k]) == &b_arr[k]);

	for (int k = 0; k < 500; k++)//delete
		assert(bst_delete(big_tree, &b_arr[k]) == &b_arr[k]);
	assert(bst_size(big_tree) == 500);
	for (int k = 0; k < 500; k++)
		assert(bst_find(big_tree, &b_arr[k]) == NULL);

	c = 2;//foreach
	bst_foreach(big_tree, &int_mult, &c);
	for (int k = 500; k < 1000; k++)
		assert(*(int*)bst_find(big_tree, &b_arr[k]) == c * equal_b_arr[k]);

	bst_clear(big_tree);
	assert(big_tree->root == NULL);
	bst_destroy(big_tree);

	BST* tree_T;
	char *r_key = "a", *x_key = "b", *y_key = "a", *z_key = "abc", *k_key = "xsz";
	int r_val = 3, x_val = 7, y_val = 8, z_val = 17, k_val = 5;
	Entry root, x, y, z, k;
	root.key = &r_key; root.value = &r_val;
	x.key = &x_key; x.value = &x_val;
	y.key = &y_key; y.value = &y_val;
	z.key = &z_key; z.value = &z_val;
	k.key = &k_key; k.value = &k_val;
	/*root = { "a", 3 };
	x = { "b", 7 };
	y = { "a", 8 };
	z = { "abc", 17 };
	k = { "xsz", 5 };*/
	tree_T = bst_create(&Entry_cmp);
	assert(bst_insert(tree_T, &root) == NULL);
	assert(bst_insert(tree_T, &x) == NULL);
	Entry_print_Tree(tree_T->root, 0);
	printf("\n");
	assert(bst_insert(tree_T, &y) == &root);
	Entry_print_Tree(tree_T->root, 0);
	printf("\n");
	assert(bst_insert(tree_T, &z) == NULL);
	assert(bst_insert(tree_T, &k) == NULL);
	Entry_print_Tree(tree_T->root, 0);
	//bst_foreach(tree_T, &print_Entry, NULL);
	bst_destroy(tree_T);

	assert(_CrtDumpMemoryLeaks() == 0);
}
