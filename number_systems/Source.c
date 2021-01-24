#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

char* check_malloc(char* output) {
	if (output == NULL) {
		printf("\nMemory not allocated\n");
		return NULL;
	}
	return output;
}

char* transform (char* input, int in_base, int out_base) {
	char* output;
	long long int number = 0, new_number;
	double fraction = 0, new_fraction;
	int M = 1, i = 0, N = 0;
	while (input[i] && input[i]!='.' && input[i] != ',') {
		if (input[i] >= (int)'0' && input[i] <= (int)'9') {
			number = (input[i] - (int)'0') + number * in_base;
		}
		if (input[i] >= (int)'A' && input[i] <= (int)'Z') {
			number = (input[i] - (int)'A' + 10) + number * in_base;
		}
		i++;
	}

	int k = 1;
	while (input[i]) {
		if (input[i]=='.' || input[i] == ',') {
			i++;
			N++;
		}
		if (input[i] >= '0' && input[i] <= 57) {
			fraction = (input[i] - '0') + fraction * in_base;
		}
		if (input[i] >= (int)'A' && input[i] <= (int)'Z') {
			fraction = (input[i] - (int)'A' + 10) + fraction * in_base;
		}
		i++;
		k *= in_base;
	}
	fraction /= k;

	new_number = number;
	while (new_number / out_base ) {
		new_number /= out_base;
		M++;
	}

	new_fraction = fraction;
	while ((new_fraction*out_base)-(int)(new_fraction*out_base) && N<20 ) {
		new_fraction *= out_base;
		N++;
	}

	if (N == 0) {
		output = malloc(sizeof(char)*(M + 1));
		check_malloc(output);
		if (check_malloc(output) == NULL) {
			return NULL;
		}
		output[M] = 0;
	}else {
		output = malloc(sizeof(char)*(M + N + 2));
		if (check_malloc(output) == NULL) {
			return NULL;
		}
		output[M + N + 1] = 0;
		output[M] = '.';
	}

	i = M;
	while (i) {
		int p = number % out_base;
		if (p >= 10) {
			output[i - 1] = p + 55;
		}else {
			output[i - 1] = p + 48;
		}
		number /= out_base;
		i--;
	}

	i = 1;
	while (i <= N) {
		int q = (int)(fraction * out_base);
		if (q >= 10) {
			output[M + i] = q + 55;
		}else {
			output[M + i] = q + 48;
		}
		fraction = fraction * out_base - (int)(fraction * out_base);
		i++;
	}
	return output;
}

void free_output(char* output) {
	if (output != NULL) {
		free(output);
	}
}

int main() {
	char* output = transform("PREVEDMEDVED", 36, 2);
	assert(strcmp(output, "10111100001110011011101011010101010001010111010001011000110101")==0);
	free_output(output);

	output = transform("0", 10, 2);
	assert(strcmp(output, "0") == 0);
	free_output(output);

	output = transform("0,1", 10, 36);
	assert(strcmp(output, "0.3LLLLLLLLLLQSN8TD1P4") == 0);
	free_output(output);

	output = transform("HELLO.WORLD", 36, 2);
	assert(strcmp(output, "1101111100001010111011100.11101000011100101001") == 0);
	free_output(output);

	output = transform("HELLOWORLD", 36, 10);
	assert(strcmp(output, "1767707668033969") == 0);
	free_output(output);

	output = transform("1767707668033969", 10, 36);
	assert(strcmp(output, "HELLOWORLD") == 0);
	free_output(output);

	output = transform("1.1", 2, 10);
	assert(strcmp(output, "1.5") == 0);
	free_output(output);

	output = transform("211.02011", 3, 7);
	assert(strcmp(output, "31.14460355506152050200") == 0);
	free_output(output);

	output = transform("AB135.765C", 16, 9);
	assert(strcmp(output, "1277183.41403711276613258270") == 0);
	free_output(output);

	output = transform("0.34", 5, 15);
	assert(strcmp(output, "0.B6") == 0);
	free_output(output);

	_CrtDumpMemoryLeaks();
	return 0;
}