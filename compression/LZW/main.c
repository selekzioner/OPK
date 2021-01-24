#include "LZW.h"
#include <time.h>
#define _ARG_COUNT 4

void info() {
	printf("\n	Parameters:\n");
	printf(" -c <input file> <compressed file> - compress file;\n");
	printf(" -u <compressed file> <output file> - decompress file.\n");
}

int main(int argc, char* argv[]) {
	/*if (argc != _ARG_COUNT && argc != 1 || (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-u") != 0)) {
		printf("Error: incorect using program.");
		info();
		return 0;
	}
	else if (argc == 1) {
		info();
		return 0;
	}
	else {
		if (strcmp(argv[1], "-c") == 0) {
			LZW_encoding(argv[2], argv[3]);
		}
		else if (strcmp(argv[1], "-u") == 0) {
			LZW_decoding(argv[2], argv[3]);
		}
	}*/
	LZW_encoding("seq.bin", "s.bin");

	/*start = clock();
	LZW_decoding("Voina_i_mir.bin", "Voina_i_mir_out.txt");
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("time: %.4lf sec\n", time);*/

	assert(_CrtDumpMemoryLeaks() == 0);
	return 0;
}