#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

bool check_sort (int* arr, size_t size) {
	for (size_t i = 1; i < size; i++) {
		if (arr[i - 1] > arr[i]) {
			return false;
		}
	}
	return true;
}

void select_sort (int* arr, size_t size) {
	for (size_t i = 0; i < size - 1; i++){
		size_t min = i;
		for (size_t j = i + 1; j < size; j++){
			if (arr[j] < arr[min]){
				min = j;
			}
		}
		int tmp = arr[min];
		arr[min] = arr[i];
		arr[i] = tmp;
	}
}

void insert_sort (int* arr, size_t size) {
	for (size_t i = 1; i < size; i++)
		for (size_t j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
			int tmp = arr[j - 1];
			arr[j - 1] = arr[j];
			arr[j] = tmp;
		}
}

void bubble_sort (int* arr, size_t size) {
	bool t;
	for (size_t i = 0; i < size; i++) {
		t = false;
		for (size_t j = 0; j < size - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				t = true;
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
		if (!t)
			break;
	}
}

void coctail_sort (int* arr, size_t size){
	for (size_t i = 1; i < size; i++) {
		bool t = false;
		for (size_t j = 1; j < size - (i - 1); j++){
			if (arr[j - 1] > arr[j]){
				t = true;
				int tmp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = tmp;
			}
		}
		for (size_t j = size - i - 1; j > size - j; j--){
			if (arr[j - 1] > arr[j]){
				t = true;
				int tmp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = tmp;
			}
		}
		if (!t)
			break;
	}
}

int* gnr(int* arr, size_t size) {
	srand(time(NULL));
	for (size_t i = 0; i < size; i++) {
		arr[i] = rand() % 100;
	}
	return arr;
}

int* gnr_sorted(int* arr, size_t size) {
	for (size_t i = 0; i < size; i++) {
		arr[i] = (int)i;
	}
	return arr;
}

int* reverse(int* arr, size_t size){
	for (size_t i = 0; i < size; i++){
		arr[i] = (int)size - (int)i;
	}
	return arr;
}

int* equal_arr(int* arr, size_t size) {
	int* new_arr = malloc(sizeof(size_t)*size);
	if (new_arr == NULL) {
		printf("Memory not allocated!\n");
		return NULL;
	}
	for (size_t i = 0; i < size; i++) {
		new_arr[i] = arr[i];
	}
	return new_arr;
}

void measure (int* arr, size_t size, void sort(int*, size_t), char* name) {
	int* new_arr = equal_arr(arr, size);
	if (new_arr != NULL) {
		clock_t start = clock();
		sort(new_arr, size);
		clock_t end = clock();

		assert(check_sort(new_arr, size));

		double time = (double)(end - start) / CLOCKS_PER_SEC;

		printf("%s: %zd elements in %.3lf sec\n", name, size, time);

		free(new_arr);
	}
}

void sorts_measure(int* arr, size_t size, bool does_it_sort) {
	if (!does_it_sort)
		gnr(arr, size);
	measure(arr, size, select_sort, "Select sort");
	measure(arr, size, insert_sort, "Insert sort");
	measure(arr, size, bubble_sort, "Bubble sort");
	measure(arr, size, coctail_sort, "Coctail sort");
	printf("\n");
}

int main() {
	printf("Random arrays:\n");

	int arr_1[1000];
	sorts_measure(arr_1, 1000, false);
	
	int arr_2[5000];
	sorts_measure(arr_2, 5000, false);

	int arr_3[10000];
	sorts_measure(arr_3, 10000, false);

	int arr_4[25000];
	sorts_measure(arr_4, 25000, false);

	int arr_5[50000];
	sorts_measure(arr_5, 50000, false);

	int arr_6[100000];
	sorts_measure(arr_6, 100000, false);

	printf("Sorted arrays:\n");

	sorts_measure(gnr_sorted(arr_1, 1000), 1000, true);

	sorts_measure(gnr_sorted(arr_2, 5000), 5000, true);

	sorts_measure(gnr_sorted(arr_3, 10000), 10000, true);

	sorts_measure(gnr_sorted(arr_4, 25000), 25000, true);

	sorts_measure(gnr_sorted(arr_5, 50000), 50000, true);

	sorts_measure(gnr_sorted(arr_6, 100000), 100000, true);
	
	printf("Reverse arrays:\n");

	sorts_measure(reverse(arr_1, 1000), 1000, true);
	
	sorts_measure(reverse(arr_2, 5000), 5000, true);

	sorts_measure(reverse(arr_3, 10000), 10000, true);

	sorts_measure(reverse(arr_4, 25000), 25000, true);

	sorts_measure(reverse(arr_5, 50000), 50000, true);

	sorts_measure(reverse(arr_6, 100000), 100000, true);

	return 0;
}