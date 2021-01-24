#include "SList.h"

/*+ �������� � �����. ���������� ����� ������ ������. */
SList *slist_append(SList *list, Pointer data) {
	if (list == NULL)
		return slist_prepend(list, data);
	else {
		SList* new_list = malloc(sizeof(SList));
		assert(new_list != NULL);
		new_list->data = data;
		slist_last(list)->next = new_list;
		new_list->next = NULL;
		return list;
	}
}

/*+ �������� � ������. ���������� ����� ������ ������. */
SList *slist_prepend(SList *list, Pointer data) {
	SList* new_list = malloc(sizeof(SList));
	assert(new_list != NULL);
	new_list->data = data;
	new_list->next = list;
	list = new_list;
	return list;
}

/*+ �������� ����� ���������� �������� */
void slist_insert(SList *sibling, Pointer data) {
	assert(sibling != NULL);
	SList* new_list = malloc(sizeof(SList));
	assert(new_list != NULL);
	new_list->data = data;
	new_list->next = sibling->next;
	sibling->next = new_list;
}

/*+ ������� ������� �� ������ � ���������� ������.
   ���������� ����� ������ ������. */
SList *slist_remove(SList *list, Pointer data) {
	assert(list != NULL);

	SList *new_list = list;
	if (list->data == data) {
		list = list->next;
		free(new_list);
	}
	else {
		for (; new_list->next != NULL; new_list = new_list->next)
			if (new_list->next->data == data)
				break;
		SList *tmp_list = new_list->next;
		if (new_list->next == NULL)
			return list;
		new_list->next = new_list->next->next;
		free(tmp_list);
	}
	return list;
}

/* +������� ��� �������� �� ������ �� ��������� data � ���������� ������.
   ���������� ����� ������ ������. */
SList *slist_remove_all(SList *list, Pointer data) {
	assert(list != NULL);

	SList *new_list;
	while (list->data == data) {
		new_list = list;
		list = list->next;
		free(new_list);
	}
	new_list = list;
	for (; new_list->next != NULL; )
		if (new_list->next->data == data) {
			SList *tmp_list = new_list->next;
			new_list->next = new_list->next->next;
			free(tmp_list);
		}
		else 
			new_list = new_list->next;
	
	return list;
}

/*+ ������� �������, ��������� �� sibling.
   ���������� ������ �� ���������� �������� */
Pointer slist_remove_next(SList *sibling) {
	assert(sibling != NULL && sibling->next != NULL);
	SList* new_list = sibling->next;
	sibling->next = new_list->next;
	Pointer data = new_list->data;
	free(new_list);
	return data;
}

/*+ ���������� ���� ������ */
void slist_free(SList *list) {
	while (list != NULL) {
		SList* new_list = list->next;
		free(list);
		list = new_list;
	}
}

/*+ ���������� ����� ������ */
unsigned slist_length(SList *list) {
	unsigned count = 0;
	for (; list != NULL; list = list->next, count++);
	return count;
}

/*+ ����������� ������. ���������� ������ �����*/
SList *slist_copy(SList *list) {
	SList* new_list = NULL;
	for (; list != NULL; list = list->next)
		new_list = slist_append(new_list, list->data);

	return new_list;
}

/*+ ����������� ������. ���������� ����� ������ ������ (������ �����) */
SList *slist_reverse(SList *list) {
	unsigned N = slist_length(list);
	Pointer *tmp_arr = malloc(sizeof(Pointer) * N);
	SList *tmp_list = list;
	for (unsigned i = 0; tmp_list != NULL; i++, tmp_list = tmp_list->next)
		tmp_arr[i] = tmp_list->data;

	tmp_list = list;
	for (unsigned i = N - 1; tmp_list != NULL; i--, tmp_list = tmp_list->next)
		tmp_list->data = tmp_arr[i];

	free(tmp_arr);
	return list;
}

/*+ ������������ ���� ������� (������������ list2 � list1).
   ���������� ��������� �� ������ ������������� ������ */
SList *slist_concat(SList *list1, SList *list2) {
	if (list1 == NULL)
		return list2;
	else {
		slist_last(list1)->next = list2;
		return list1;
	}
}

/* ����� ������. ������� func �� ������ ���� ���������� ��� ���������:
   data, ��������������� ������ �������� �������� ������, � user_data,
   ���������� ���������� ����� ������� */
void slist_foreach(SList *list,
	void(*func)(Pointer data, Pointer user_data), Pointer user_data) {
	assert(list != NULL);

	SList *new_list = list;
	for (; new_list != NULL; new_list = new_list->next)
		func(new_list->data, user_data);
}

/*+ ��������� ������� ������ */
SList *slist_last(SList *list) {
	if (list != NULL)
		for (; list->next != NULL; list = list->next);
	return list;
}

/*+ n-� ������� ������ (��� 0). ���� n ������������, ��������
   ��������� � ����� (-1 -- ��������� � �.�.) */
SList *slist_nth(SList *list, int n) {
	if (n < 0) 
		n = slist_length(list) + n;
	int count = 0;
	for (; count != n && list != NULL; list = list->next, count++);
	return list;
}

/*+ ����� �������� �� ��������� ������ data (0 ���� �� ������) */
SList *slist_find(SList *haystack, Pointer needle) {
	for (; haystack != NULL; haystack = haystack->next)
		if (haystack->data == needle)
			break;
	return haystack;
}

/*+ ���������� ������ �������, ��� �������� compare_func ������ 0,
   ��������� ������ ������� ������ � needle */
SList *slist_find_custom(SList *haystack, Pointer needle, 
	int(*compare_func)(Pointer a, Pointer b)) {
	for (; haystack != NULL; haystack = haystack->next)
		if (compare_func(haystack->data, needle) == 0)
			break;
	return haystack;
}

/*+ ���������� ������� �������� el � ������ ��� -1,
   ���� �� �� ������������ � ������ */
int slist_position(SList *list, SList *el) {
	size_t count = 0;
	for (; list != NULL; list = list->next, count++)
		if (list->data == el->data && list->next == el->next)
			return count;
	return -1;
}