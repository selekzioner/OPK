#include "file_creator.h"

static bool w_open_file(FILE** fp, char* name) {
	if (fopen_s(fp, name, "wb") != 0) {
		printf("Error: %s wasn't open.\n", name);
		return 0;
	}
	else {
		rewind(*fp);
		return 1;
	}
}

void text_create(char* name, unsigned int count) {
	FILE* fp;
	srand(time(NULL));
	if (w_open_file(&fp, name) != 0) {
		while (count != 0) {
			unsigned char out = rand() % 97 + 31;
			fputc(out, fp);
			count--;
		}
	}
	fclose(fp);
}

void random_create(char* name, unsigned int count) {
	FILE* fp;
	srand(time(NULL));
	if (w_open_file(&fp, name) != 0) {
		while (count != 0) {
			unsigned char out = rand() % 256;
			fputc(out, fp);
			count--;
		}
	}
	fclose(fp);
}

void similar_create(char* name, unsigned int count) {
	FILE* fp;
	srand(time(NULL));
	unsigned char out = rand() % 256;
	if (w_open_file(&fp, name) != 0) {
		while (count != 0) {
			fputc(out, fp);
			count--;
		}
	}
	fclose(fp);
}