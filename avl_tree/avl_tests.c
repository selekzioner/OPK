#include "avl_tests.h"
#include <time.h>

int int_cmp(Pointer a, Pointer b) {
	int int_a = *(int*)a, int_b = *(int*)b;

	if (int_a > int_b)
		return 1;
	else if (int_a < int_b)
		return -1;
	else
		return 0;
}

int double_cmp(Pointer a, Pointer b) {
	double double_a = *(double*)a, double_b = *(double*)b;

	if (double_a > double_b)
		return 1;
	else if (double_a < double_b)
		return -1;
	else
		return 0;
}

int Entry_cmp(Entry* a, Entry* b) {
	return strcmp(*(char**)a->key, *(char**)b->key);
}

void int_mult(Pointer a, Pointer b) {
	*(int*)a *= *(int*)b;
}

void double_mult(Pointer a, Pointer b) {
	*(double*)a *= *(double*)b;
}

void int_print_Tree(AVLTreeNode *node, int level) {
	if (node) {
		int_print_Tree(node->right, level + 1);
		for (int i = 0; i < level; i++)
			printf("   ");
		printf("%d\n", *(int*)node->data);
		int_print_Tree(node->left, level + 1);
	}
}

void double_print_Tree(AVLTreeNode *node, int level) {
	if (node) {
		double_print_Tree(node->right, level + 1);
		for (int i = 0; i < level; i++)
			printf("   ");
		printf("%lg\n", *(double*)node->data);
		double_print_Tree(node->left, level + 1);
	}
}

void Entry_print_Tree(AVLTreeNode *node, int level) {
	if (node) {
		Entry_print_Tree(node->right, level + 1);
		for (int i = 0; i < level; i++)
			printf("   ");
		Entry *x = (Entry*)node->data;
		printf("%s %d\n", *(char**)x->key, *(int*)x->value);
		Entry_print_Tree(node->left, level + 1);
	}
}

void test () {
	//INT
	int int_arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }, equal_int_arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }, s = 2;
	AVLTree *tree = avl_create(&int_cmp);
	for (int i = 0; i < 10; i++) //insert
		assert(avl_insert(tree, &int_arr[i]) == NULL);
	assert(avl_size(tree) == 10);
	assert(avl_insert(tree, &s) == &int_arr[2]);
	assert(avl_insert(tree, &int_arr[2]) == &s);
	//int_print_Tree(tree->root, 0);
	assert(avl_check(tree));

	for (int i = 0; i < 10; i++) //find
		assert(avl_find(tree, &int_arr[i]) == &int_arr[i]);

	for (int i = 0; i < 5; i++) //delete
		assert(avl_delete(tree, &int_arr[i]) == &int_arr[i]);
	//int_print_Tree(tree->root, 0);
	assert(avl_check(tree));
	assert(avl_size(tree) == 5);
	for (int i = 0; i < 5; i++)
		assert(avl_find(tree, &int_arr[i]) == NULL);
	for (int i = 0; i < 5; i++)
		assert(avl_delete(tree, &int_arr[i]) == NULL);

	avl_foreach(tree, &int_mult, &s); //foreach
	for (int i = 5; i < 10; i++)
		assert(int_arr[i] == s * equal_int_arr[i]);
	//int_print_Tree(tree->root, 0);
	assert(avl_check(tree));

	avl_clear(tree);
	assert(_CrtDumpMemoryLeaks() != 0 && tree->root == NULL);

	avl_destroy(tree);

	//BIG TREE WITH INT
	int big_arr[100000], equal_big_arr[100000];
	for (int i = 0; i < 100000; i++)
		big_arr[i] = equal_big_arr[i] = i;

	for (int k = 100000; k > 1; k--) {
		int a = rand() % 100;
		int q = rand() % 1000;
		int j = (a * 1000) + q;
		int t = big_arr[k - 1];
		equal_big_arr[k - 1] = big_arr[k - 1] = big_arr[j];
		equal_big_arr[j] = big_arr[j] = t;
	}

	tree = avl_create(&int_cmp);

	clock_t start = clock();
	for (int i = 0; i < 100000; i++) //insert
		assert(avl_insert(tree, &big_arr[i]) == NULL);
	clock_t end = clock();
	printf("insert=%.2lf\n", (double)(end - start) / 1000);
	assert(avl_check(tree));
	//int_print_Tree(tree->root, 0);
	printf("%d\n", tree->root->height);
	assert(avl_size(tree) == 100000);

	for (int i = 0; i < 100000; i++) //find
		assert(avl_find(tree, &big_arr[i]) == &big_arr[i]);

	avl_foreach(tree, &int_mult, &s); //foreach
	for (int i = 0; i < 100000; i++)
		assert(big_arr[i] == s * equal_big_arr[i]);
	assert(avl_check(tree));
	clock_t start1 = clock();
	for (int i = 100000 - 1; i >= 0; i--) //delete
		assert(avl_delete(tree, &big_arr[i]) == &big_arr[i]);
	clock_t end1 = clock();
	printf("delete=%.2lf\n", (double)(end1 - start1) / 1000);
	assert(avl_check(tree));
	assert(avl_size(tree) == 0);
	for (int i = 0; i < 100000; i++)
		assert(avl_delete(tree, &big_arr[i]) == NULL);
	for (int i = 0; i < 100000; i++)
		assert(avl_find(tree, &big_arr[i]) == NULL);

	avl_clear(tree);
	assert(_CrtDumpMemoryLeaks() != 0 && tree->root == NULL);

	avl_destroy(tree);

	//DOUBLE
	double double_arr[] = { 11.3, 24.55, 56.1, 999.999, 0.05, 0, 999.99 }, equal_double_arr[] = { 11.3, 24.55, 56.1, 999.999, 0.05, 0, 999.99 };
	tree = avl_create(&double_cmp);
	for (int i = 0; i < 7; i++) //insert
		assert(avl_insert(tree, &double_arr[i]) == NULL);
	//double_print_Tree(tree->root, 0);
	assert(avl_check(tree));
	assert(avl_size(tree) == 7);

	for (int i = 0; i < 7; i++) //find
		assert(avl_find(tree, &double_arr[i]) == &double_arr[i]);

	for (int i = 0; i < 3; i++) //delete
		assert(avl_delete(tree, &double_arr[i]) == &double_arr[i]);
	//double_print_Tree(tree->root, 0);
	assert(avl_check(tree));
	assert(avl_size(tree) == 4);

	double d = 2;
	avl_foreach(tree, &double_mult, &d); //foreach
	for (int i = 3; i < 7; i++)
		assert(double_arr[i] == d * equal_double_arr[i]);
	//double_print_Tree(tree->root, 0);
	assert(avl_check(tree));

	avl_clear(tree);
	assert(_CrtDumpMemoryLeaks() != 0 && tree->root == NULL);

	avl_destroy(tree);

	//STRING
	AVLTree* tree_T;
	char *r_key = "a", *x_key = "b", *y_key = "a", *z_key = "abc", *k_key = "xsz";
	int r_val = 3, x_val = 7, y_val = 8, z_val = 17, k_val = 5;
	Entry root, x, y, z, k;
	root.key = &r_key; root.value = &r_val;
	x.key = &x_key; x.value = &x_val;
	y.key = &y_key; y.value = &y_val;
	z.key = &z_key; z.value = &z_val;
	k.key = &k_key; k.value = &k_val;
	tree_T = avl_create(&Entry_cmp);
	assert(avl_insert(tree_T, &root) == NULL);
	assert(avl_insert(tree_T, &x) == NULL);
	assert(avl_insert(tree_T, &y) == &root);
	assert(avl_insert(tree_T, &z) == NULL);
	assert(avl_insert(tree_T, &k) == NULL);
	assert(avl_size(tree) == 3);
	//Entry_print_Tree(tree->root, 0);
	assert(avl_check(tree));
	avl_clear(tree_T);
	assert(_CrtDumpMemoryLeaks() != 0 && tree_T->root == NULL);
	avl_destroy(tree_T);

	assert(_CrtDumpMemoryLeaks() == 0);
}