#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <crtdbg.h>
#include <malloc.h>
#include <assert.h>

typedef void *Pointer;

typedef struct tSList {
	Pointer data;
	struct tSList *next;
} SList;

/* �������� � �����. ���������� ����� ������ ������. */
SList *slist_append(SList *list, Pointer data);

/* �������� � ������. ���������� ����� ������ ������. */
SList *slist_prepend(SList *list, Pointer data);

/* �������� ����� ���������� �������� */
void slist_insert(SList *sibling, Pointer data);

/* ������� ������� �� ������ � ���������� ������.
   ���������� ����� ������ ������. */
SList *slist_remove(SList *list, Pointer data);

/* ������� ��� �������� �� ������ �� ��������� data � ���������� ������.
   ���������� ����� ������ ������. */
SList *slist_remove_all(SList *list, Pointer data);

/* ������� �������, ��������� �� sibling.
   ���������� ������ �� ���������� �������� */
Pointer slist_remove_next(SList *sibling);

/* ���������� ���� ������ */
void slist_free(SList *list);

/* ���������� ����� ������ */
unsigned slist_length(SList *list);

/* ����������� ������. ���������� ������ ����� */
SList *slist_copy(SList *list);

/* ����������� ������. ���������� ����� ������ ������ (������ �����) */
SList *slist_reverse(SList *list);

/* ������������ ���� ������� (������������ list2 � list1).
   ���������� ��������� �� ������ ������������� ������ */
SList *slist_concat(SList *list1, SList *list2);

/* ����� ������. ������� func �� ������ ���� ���������� ��� ���������:
   data, ��������������� ������ �������� �������� ������, � user_data,
   ���������� ���������� ����� ������� */
void slist_foreach(SList *list,
	void(*func)(Pointer data, Pointer user_data), Pointer user_data);

/* ��������� ������� ������ */
SList *slist_last(SList *list);

/* n-� ������� ������ (��� 0). ���� n ������������, ��������
   ��������� � ����� (-1 -- ��������� � �.�.) */
SList *slist_nth(SList *list, int n);

/* ����� �������� �� ��������� ������ data (0 ���� �� ������) */
SList *slist_find(SList *haystack, Pointer needle);

/* ���������� ������ �������, ��� �������� compare_func ������ 0,
   ��������� ������ ������� ������ � needle */
SList *slist_find_custom(SList *haystack, Pointer needle,
	int(*compare_func)(Pointer a, Pointer b));

/* ���������� ������� �������� el � ������ ��� -1,
   ���� �� �� ������������ � ������ */
int slist_position(SList *list, SList *el);