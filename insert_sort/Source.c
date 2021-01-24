#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

void replace (int* elm){
	int t = elm[0];
	elm[0] = elm[1];
	elm[1] = t;
}

void sort(int* parr, size_t size){
	for (size_t i = 1; i < size; i++)
		for (int j = i; j > 0 && parr[j - 1] > parr[j]; j--)
			replace(parr + j - 1);
}

bool check_sort(int* parr, size_t size) {
	for (size_t i = 0; i < size; i++) {
		if (parr[i - 1] > parr[i]) {
			return false;
		}
	}
	return true;
}

void gnr(int *arr, size_t n) {
	srand(time(NULL));
	for (size_t i = 0; i < n; i++)
		arr[i] = (rand() % n) + 1;
}

int main() {
	int array_1[] = {9, 2, 10000, 1, 22, 2, -999};
	sort(array_1, 7);
	assert(check_sort(array_1, 7));

	int array_2[] = {100000, -100000, 100000, -100000, 100000};
	sort(array_2, 5);
	assert(check_sort(array_2, 5));

	int array_3[] = {-1};
	sort(array_3, 1);
	assert(check_sort(array_3, 1));

	int array_4[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
	sort(array_4, 20);
	assert(check_sort(array_4, 20));

	int array_5[] = {300, 295, 68, 213, -777, -7, 864, -978, 57222, 1048, -5643};
	sort(array_5, 11);
	assert(check_sort(array_5, 11));

	int array_6[] = {1, -1};
	sort(array_6, 2);
	assert(check_sort(array_6, 2));

	int array_7[10];
	gnr(array_7, 10);
	sort(array_7, 10);
	assert(check_sort(array_7, 10));

	int array_8[20];
	gnr(array_8, 20);
	sort(array_8, 20);
	assert(check_sort(array_8, 20));

	return 0;
}