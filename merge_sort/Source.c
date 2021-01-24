#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>

int int_cmp (void* x, void* y) {
	int a = *(int*)x;
	int b = *(int*)y;

	if (a > b)
		return 1;
	else if (a < b)
		return -1;
	else
		return 0;
}

int double_cmp (void* x, void* y) {
	double a = *(double*)x;
	double b = *(double*)y;

	if (a > b)
		return 1;
	else if (a < b)
		return -1;
	else
		return 0;
}

int char_cmp (void* x, void* y) {
	double a = *(char*)x;
	double b = *(char*)y;

	if (a > b)
		return 1;
	else if (a < b)
		return -1;
	else
		return 0;
}

void assign (size_t size, void* arr, void* t_arr) {
	for (size_t j = 0; j < size; j++)
		*((char*)t_arr + j) = *((char*)arr + j);
}

void merge (void* arr, size_t size, size_t frst, size_t lst, int(*cmp)(void *, void *), void* t_arr) {
	if (frst < lst) {

		merge (arr, size, frst, (frst + lst) / 2, cmp, t_arr);
		merge (arr, size, (frst + lst) / 2 + 1, lst, cmp, t_arr);

		size_t left = frst, mid = (frst + lst) / 2, right = mid + 1;

		for (size_t i = 0; i <= lst - frst; i++) {

			if ((left <= mid) && ((right > lst) || cmp((char*)arr + left * size, (char*)arr + right * size) < 0)) {
				assign(size, (char*)arr + left * size, (char*)t_arr + i * size);
				left++;
			}
			else {
				assign(size, (char*)arr + right * size, (char*)t_arr + i * size);
				right++;
			}
		}

		for (size_t i = frst; i <= lst; i++)
			assign(size, (char*)t_arr + (i - frst) * size, (char*)arr + i * size);
	}
}

void mergesort (void* arr, size_t count, size_t size, int(*cmp)(void *, void *)) {
	if (count != 0) {
		void* t_arr = malloc(size*count);
		if (t_arr == NULL) {
			printf("Memory not allocated!\n");
		} else {
			merge(arr, size, 0, count - 1, cmp, t_arr);
			free(t_arr);
		}
	}
}

bool check_sort(void* arr, size_t count, size_t size, int(*cmp)(void *, void *)) {

	mergesort(arr, count, size, cmp);

	for (size_t i = 1; i < count; i++) {
		if (cmp((char*)arr + (i - 1) * size, (char*)arr + (i)* size) > 0) {
			return false;
		}
	}
	return true;
}

int* gnr (int* arr, size_t size) {
	srand(time(NULL));
	for (size_t i = 0; i < size; i++) {
		arr[i] = rand() % 100;
	}
	return arr;
}

int* sorted (int* arr, size_t size) {
	for (size_t i = 0; i < size; i++)
		arr[i] = (int)i;
	return arr;
}

int* reverse (int* arr, size_t size) {
	for (size_t i = 0; i < size; i++)
		arr[i] = (int)(size - i);
	return arr;
}

int main () {

	assert(check_sort(NULL, 0, 8, char_cmp));

	char arr_1[] = { 'y', 'F', 'e', 'H', '7', 'r', 'e', 'r' };
	assert(check_sort(arr_1, 8, sizeof(arr_1[0]), char_cmp));

	char arr_2[] = { 'd' };
	assert(check_sort(arr_2, 1, sizeof(arr_2[0]), char_cmp));

	int arr_3[] = { 5, -7 };
	assert(check_sort(arr_3, 2, sizeof(arr_3[0]), int_cmp));

	long long int arr_4[] = { 5, -6, -10, 2,  -11111111111, 233435 };
	assert(check_sort(arr_4, 6, sizeof(arr_4[0]), int_cmp));

	double arr_5[] = { 4.5, 4.545, -124, 12, 4.54, 1.2, -1.2, 2.1, 5.7, 5 };
	assert(check_sort(arr_5, 10, sizeof(arr_5[0]), double_cmp));

	int arr_6[100000];
	assert(check_sort(gnr(arr_6, 100000), 100000, sizeof(arr_6[0]), int_cmp));

	int arr_7[10000];
	assert(check_sort(sorted(arr_7, 10000), 10000, sizeof(arr_7[0]), int_cmp));

	int arr_8[10000];
	assert(check_sort(reverse(arr_8, 10000), 10000, sizeof(arr_8[0]), int_cmp));

	_CrtDumpMemoryLeaks();
	return 0;
}