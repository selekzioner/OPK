#include "tests.h"

static void insert_test(SList *list, Pointer data, int nth) {
	unsigned N = slist_length(list);
	slist_insert(slist_nth(list, nth), data);
	unsigned M = slist_length(list);

	assert(slist_nth(list, nth + 1)->data == data && N + 1 == M);
}

static void remove_test(SList *list, Pointer data) {
	int pos;
	SList *search_list = slist_find(list, data);
	if (search_list != NULL) {
		pos = slist_position(list, search_list);
	}
	unsigned N = slist_length(list);
	list = slist_remove(list, data);
	unsigned M = slist_length(list);
	if (search_list == 0)
		assert(M == N);
	else
		if (pos < N - 1)
			assert(slist_nth(list, pos)->data != data && N == M + 1);

	else
		assert(slist_nth(list, pos) == 0 && N == M + 1);
}

static void remove_all_test(SList *list, Pointer data) {
	list = slist_remove_all(list, data);

	assert(slist_find(list, data) == 0);
}

static void remove_next_test(SList *list, int nth) {
	if (list != NULL) {
		unsigned N = slist_length(list);
		Pointer data_cmp = slist_nth(list, nth + 1)->data;
		Pointer data = slist_remove_next(slist_nth(list, nth));
		unsigned M = slist_length(list);

		assert(data_cmp == data && N == M + 1);
	}
}

static void length_test(SList *list, unsigned len) {
	assert(slist_length(list) == len);
}

static void copy_test(SList *list) {
	SList *copy_list = slist_copy(list);
	SList *new_copy_list = copy_list, *new_list = list;
	for (; new_copy_list != NULL; new_copy_list = new_copy_list->next, new_list = new_list->next)
		assert(new_copy_list->data == new_list->data);
	slist_free(copy_list);
}

static void reverse_test(SList *list) {
	SList *cmp_list = NULL, *new_list = list;
	
	for (; new_list != NULL; new_list = new_list->next)
		cmp_list = slist_append(cmp_list, new_list->data);

	list = slist_reverse(list);

	for (int i = -1; list != NULL; list=list->next, i--)
		assert(list->data == slist_nth(cmp_list, i)->data);
	
	slist_free(cmp_list);
}

static void concat_test(SList *list1, SList *list2) {
	if (list1 != NULL)
		assert(slist_concat(list1, list2) == list1);
	else
		assert(slist_concat(list1, list2) == list2);
}

static void foreach_test(SList *list, void(*func)(Pointer data, Pointer user_data), Pointer user_data) {
	SList *cmp_list = NULL, *new_list = list;

	for (; new_list != NULL; new_list = new_list->next) {
		cmp_list = slist_append(cmp_list, new_list->data);
		func(cmp_list->data, user_data);
	}
	
	slist_foreach(list, func, user_data);

	for (; new_list != NULL; new_list = new_list->next) {
		func(new_list->data, user_data);
		assert(list->data == cmp_list->data);
	}
	slist_free(cmp_list);
}

static void last_test(SList *list, Pointer data) {
	if (list != NULL)
		assert(slist_position(list, slist_last(list)) == slist_length(list) - 1 && slist_last(list)->data == data);
	else
		assert(slist_last(list) == NULL);
}

static void nth_test(SList *list, int n, Pointer data) {
	if (list != NULL)
		assert(slist_nth(list, n)->data == data);
	else
		assert(slist_nth(list, n) == NULL);
}

static void find_test(SList *haystack, Pointer needle) {
	if (haystack != NULL)
		assert(slist_find(haystack, needle)->data == needle);
	else
		assert(slist_find(haystack, needle)==NULL);
}

static void find_custom_test(SList *haystack, Pointer needle,
	int(*compare_func)(Pointer a, Pointer b), Pointer data) {
	if (haystack != NULL)
		assert(slist_find_custom(haystack, needle, compare_func)->data == data);
	else
		assert(slist_find_custom(haystack, needle, compare_func) == NULL);
}

static void position_test(SList *list, SList *el, int pos) {
	if (list != NULL)
		assert(slist_position(list, el) == pos);
	else
		assert(slist_position(list, el) == -1);
} 

void tests() {
	length_test(0, 0);
	copy_test(0);
	concat_test(0, 0);
	last_test(0, 0);
	nth_test(0, 0, 0);
	find_test(0, 0);
	find_custom_test(0, 0, larger, 0);
	position_test(0, 0, 0);
	reverse_test(0);


	int arr[1000];
	SList* list = NULL; //create
	for (int i = 0; i < 1000; i++) {
		arr[i] = i;
		list = slist_append(list, &arr[i]);
		length_test(list, i+1);
		nth_test(list, i, &arr[i]);
	}

	int c = 5000; //insert
	for (int i = 50; i < 1000; i += 50)
		insert_test(list, &c, i);

	int tmp = 100000;
	remove_test(list, &c);
	remove_test(list, &tmp);
	remove_all_test(list, &c);
	remove_next_test(list, 998);
	length_test(list, 999);
	copy_test(list);
	concat_test(0, list);

	last_test(list, &arr[998]);
	nth_test(list, 50, &arr[50]);
	find_test(list, &arr[50]);
	find_custom_test(list, &arr[500], larger, &arr[501]);
	position_test(list, list->next, 1);
	reverse_test(list);
	c = 3; //foreach
	foreach_test(list, int_mult, &c);

	double d_arr[1000];
	SList* d_list = NULL; //create
	for (int i = 0; i < 1000; i++) {
		d_arr[i] = (double)i - 1.5;
		d_list = slist_append(d_list, &d_arr[i]);
	}

	double d = 5000.14; //insert
	for (int i = 50; i < 1000; i += 50)
		insert_test(d_list, &d, i);

	remove_test(d_list, &d);
	remove_all_test(d_list, &d);
	remove_next_test(d_list, 998);
	length_test(d_list, 999);
	copy_test(d_list);
	last_test(d_list, &d_arr[998]);
	nth_test(d_list, 50, &d_arr[50]);
	find_test(d_list, &d_arr[50]);
	find_custom_test(d_list, &d_arr[500], larger, &d_arr[501]);
	position_test(d_list, d_list->next, 1);
	reverse_test(d_list);

	SList *new_d_list = NULL; //concat
	for (int i = 0; i < 100; i++) {
		d_arr[i] = (double)i + 156.88;
		d_list = slist_append(d_list, &d_arr[i]);
	}
	concat_test(d_list, new_d_list);
	d = 3; //foreach
	foreach_test(d_list, double_mult, &d);


	char* s_arr[1000];
	SList* s_list = NULL; //create
	for (int i = 0; i < 1000; i++) {
		s_arr[i] = "abcde";
		s_list = slist_append(s_list, &s_arr[i]);
	}

	char* s = "fg"; //insert
	for (int i = 50; i < 1000; i += 50)
		insert_test(s_list, &s, i);

	remove_test(s_list, &s);
	remove_all_test(s_list, &s);
	remove_next_test(s_list, 998);
	length_test(s_list, 999);
	copy_test(s_list);
	last_test(s_list, &s_arr[998]);
	nth_test(s_list, 50, &s_arr[50]);
	find_test(s_list, &s_arr[50]);
	find_custom_test(s_list, &s_arr[500], larger, &s_arr[501]);
	position_test(s_list, s_list->next, 1);
	reverse_test(s_list);
	concat_test(s_list, 0);


	slist_free(list);
	slist_free(d_list);
	slist_free(s_list);
	assert(_CrtDumpMemoryLeaks() == 0);
}