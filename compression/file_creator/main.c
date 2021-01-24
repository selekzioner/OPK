#include "file_creator.h"
#define _ARG_COUNT 4

void info() {
	printf("	Parameters:\n -r <file name> <size> - random file\n");
	printf("-s <file name> <size> - file with similar symbol\n");
}

int main(int argc, char* argv[]) {
	/*random_create("random_10000000.bin", 10000000);
	random_create("random_100000000.bin", 100000000);*/

	text_create("100000.txt", 100000);
	text_create("1000000.txt", 1000000);
	text_create("10000000.txt", 10000000);
	text_create("100000000.txt", 100000000);

	/*similar_create("similar_1000000.bin", 1000000);
	similar_create("similar_10000000.bin", 10000000);*/

	return 0;
}