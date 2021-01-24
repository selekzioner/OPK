#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

void strclear(char *str){
	int i = 0, j = 0;
	while (str[j]){
		while (isspace(str[j]) && isspace(str[j+1])) {
			j++;
		}
		str[i] = str[j];
		i++;
		j++;
	}
	str[i] = 0;
}

int main() {

	char buf9[] = "a           b"; //test 1
	strclear(buf9);
	assert(strcmp(buf9, "a b") == 0);
	 
	char *super = malloc(1000000 * sizeof(char)); //test 2
	if (super == NULL) {
		printf("Out of memory\n");
		return 1;
	}
	for (int i = 0; i < 1000000; i++) {
		super[i] = ' ';
	}
	super[0] = 'a';
	super[999998] = 'b';
	super[999999] = '\0';
	strclear(super);
	assert(strcmp(super, "a b") == 0);
	free(super);

	char buf[] = "ab       0    cd       "; //test 3
	strclear(buf);
	assert(strcmp(buf, "ab 0 cd ") == 0);

	char buf1[] = "      f       sd       ";//test 4
	strclear(buf1);
	assert(strcmp(buf1, " f sd ") == 0);

	char buf2[] = "ab"; //test 5
	strclear(buf2);
	assert(strcmp(buf2, "ab") == 0);

	char buf3[] = "   "; //test 6
	strclear(buf3);
	assert(strcmp(buf3, " ") == 0);

	_CrtDumpMemoryLeaks();
	return 0;
}