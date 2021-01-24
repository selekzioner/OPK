#include <math.h>
#include <time.h>
#include "stack.h"

void check_incr_capacity(Stack* stck, int i, int cnt) {
	if (i == INIT_SIZE * pow(2, cnt)) {
		assert(stck->capacity == i);
		cnt++;
	}
}

void check_decr_capacity(Stack* stck, int i, int cnt) {
	if (i == INIT_SIZE * pow(2, cnt)) {
		assert(stck->capacity == 2 * i);
		cnt--;
	}
}

int main() {
	Stack stck;
	stack_create(&stck); //test 0
	clock_t start = clock();
	for (int i = 1, cnt = 0; i <= 10; i++) {
		stack_push(&stck, (Pointer)i);
	}
	clock_t end = clock();
	double time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("10: %lg\n", time);
	stack_destroy(&stck);

	stack_create(&stck); //test 1
	start = clock();
	for (int i = 1, cnt = 0; i <= 100; i++) {
		stack_push(&stck, (Pointer)i);
	}
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("100: %lg\n", time);
	stack_destroy(&stck);

	stack_create(&stck); //test 1
	start = clock();
	for (int i = 1, cnt = 0; i <= 1000; i++) {
		stack_push(&stck, (Pointer)i);
	}
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("1000: %lg\n", time);
	stack_destroy(&stck);

	stack_create(&stck); //test 1
	start = clock();
	for (int i = 1, cnt = 0; i <= 10000; i++) {
		stack_push(&stck, (Pointer)i);
	}
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("10000: %lg\n", time);
	stack_destroy(&stck);

	stack_create(&stck); //test 1
	start = clock();
	for (int i = 1, cnt = 0; i <= 100000; i++) {
		stack_push(&stck, (Pointer)i);
	}
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("100000: %lg\n", time);
	stack_destroy(&stck);

	stack_create(&stck); //test 2
	start = clock();
	for (int i = 1, cnt = 0; i <= 1000000; i++) {
		stack_push(&stck, (Pointer)i);
	}
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("1000000: %lg\n", time);
	stack_destroy(&stck);
	
	stack_create(&stck); //test 2
	start = clock();
	for (int i = 1, cnt = 0; i <= 10000000; i++) {
		stack_push(&stck, (Pointer)i);
	}
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("10000000: %lg\n", time);
	stack_destroy(&stck);

	stack_create(&stck); //test 2
	start = clock();
	for (int i = 1, cnt = 0; i <= 100000000; i++) {
		stack_push(&stck, (Pointer)i);
		check_incr_capacity(&stck, i, cnt);
		assert(stack_size(&stck) == i);
	}
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("100000000: %lg\n", time);
	stack_destroy(&stck);

	/*stack_create(&stck); //test 2
	start = clock();
	for (int i = 1, cnt = 0; i <= 1000000000; i++) {
		stack_push(&stck, (Pointer)i);
		check_incr_capacity(&stck, i, cnt);
		assert(stack_size(&stck) == i);
	}
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("1000000000: %lg\n", time);
	stack_destroy(&stck);*/

	stack_create(&stck); //test 3
	char* str = "abcd";
	stack_push(&stck, str);
	assert(strcmp((char*)stack_peek(&stck), str) == 0);
	assert(strcmp((char*)stack_pop(&stck), str) == 0);
	stack_destroy(&stck);


	stack_create(&stck); //test 4
	for (int i = 1, cnt = 0; i < 256; i++) {
		stack_push(&stck, (Pointer)(char)i);
		check_incr_capacity(&stck, i, cnt);
	}
	for (int i = 255, cnt = 0; i > 0; i--) {
		assert((char)stack_peek(&stck) == (char)i);
		assert((char)stack_pop(&stck) == (char)i);
		check_decr_capacity(&stck, i, cnt);
	}
	stack_destroy(&stck);


	stack_create(&stck); //test 5
	for (int i = 1, cnt = 0; i <= 1000; i++) {
		stack_push(&stck, (Pointer)(-i));
		check_incr_capacity(&stck, (-i), cnt);
	}
	for (int i = 1000, cnt = 0; i >= 0; i--) {
		assert((int)stack_peek(&stck) == -i);
		assert((int)stack_pop(&stck) == -i);
		check_decr_capacity(&stck, i, cnt);
	}
	stack_destroy(&stck);
	

	assert(_CrtDumpMemoryLeaks()==0);
	return 0;
}