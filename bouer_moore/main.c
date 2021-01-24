#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

char* my_strstr (char *hstck, const char *ndl) {
	int M = (int)strlen(ndl), N = (int)strlen(hstck);
	assert(M != 0 && N != 0);

	int d[256], match_arr[256];
	assert(match_arr != NULL);

	for (int i = 0; i < 256; i++)
		d[i] = M;

	for (int i = 0; i < M - 1; i++)
		d[ndl[i]] = M - 1 - i;
	

	for (int i = M - 1; i < N;){
		for (int k = i, j = M - 1; j >= 0; k--, j--){
			if (hstck[k] != ndl[j]){
				i += d[hstck[i]];
				break;
			}

			if (j == 0)
				return (hstck + k);
		}
	}
	return NULL;
}

size_t check_position(char *hstck, const char *ndl) {
	char* str = my_strstr(hstck, ndl);
	if (str != NULL)
		return my_strstr(hstck, ndl) - hstck;
	else return -1;
}

int main () {
	assert(check_position("rrrlerllea", "rrr") == 0);

	assert(check_position("rrrarlerlle", "rl") == 4);

	assert(check_position("rrrarllerle", "rle") == 8);

	assert(check_position("rrrarlerllerler", "rler") == 4);

	assert(check_position("rrrarlerlle", "rlerl") == 4);

	assert(check_position("aaarrrarlerlle", "rlerll") == 7);

	assert(check_position("rrrarlerlle", "ay") == -1);

	assert(check_position("arrarlerllerrr", "rrr") == 11);

	assert(check_position("arrrarlerllerlerllerlerlle", "rlerlle") == 5);

	assert(check_position("xcms supports analysis of LC/MS data from files in (AIA/ANDI) NetCDF, mzML/mzXML and mzData format. For the actual data import Bioconductor’s mzR is used. mzR...", "mzR") == 142);

	char *hstck;
	hstck = malloc(sizeof(char) * 1000000);
	if (hstck == 0) {
		printf("Memory not allocated\n");
		return 0;
	}
	for (int i = 0; i < 1000000; i++)
		hstck[i] = 'l';
	hstck[890000] = 'r'; hstck[890001] = 'l'; hstck[890002] = 'e'; hstck[890003] = 'r'; hstck[890004] = 'l'; hstck[890005] = 'l';
	assert(check_position(hstck, "rlerll") == 890000);
	free(hstck);

	return 0;
}