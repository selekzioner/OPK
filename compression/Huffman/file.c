#include "file.h"

bool r_open_file(FILE** fp, char* name) {
	if ((fopen_s(fp, name, "rb") != 0) || (fgetc(*fp) == EOF)) {
		printf("Error: %s is empty file/file wasn't open.\n", name);
		return 0;
	}
	else {
		rewind(*fp);
		return 1;
	}
}

bool w_open_file(FILE** fp, char* name) {
	if (fopen_s(fp, name, "wb") != 0) {
		printf("Error: %s wasn't open.\n", name);
		return 0;
	}
	else {
		rewind(*fp);
		return 1;
	}
}
