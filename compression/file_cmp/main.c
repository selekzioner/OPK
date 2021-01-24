#include "file_cmp.h"

void info() {
	printf("	Parameters:\n <file name> <file name> compare files\n");
}

int main(int argc, char*argv[]) {
	if (argc == 3) {
		cmp(argv[1], argv[2]);
	}
	else {
		info();
	}
	//cmp("test7.pdf", "test7out.pdf");
	return 0;
}