#include "file_cmp.h"

static bool r_open_file(FILE** fp, char* name) {
	if ((fopen_s(fp, name, "rb") != 0) || (fgetc(*fp) == EOF)) {
		printf("Error: %s is empty file/file wasn't open.\n", name);
		return 0;
	}
	else {
		rewind(*fp);
		return 1;
	}
}

void cmp(char* name_1, char* name_2) {
	FILE* fp_1, *fp_2;
	if (r_open_file(&fp_1, name_1) != 0 && r_open_file(&fp_2, name_2) != 0) {
		int get_1, get_2;
		while ((get_1 = fgetc(fp_1) != EOF) && (get_2 = fgetc(fp_2) != EOF)) {
			if (get_1 != get_2) {
				printf("Different files.\n");
			}
		}
		printf("Files are similar.\n");
		fclose(fp_1);
		fclose(fp_2);
	}
}