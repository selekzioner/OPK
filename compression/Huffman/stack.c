#include "stack.h"

void stack_create(Stack *pstack) {
	pstack->size = 0;
	pstack->capacity = 0;
	pstack->data = NULL;
}

void stack_destroy(Stack *pstack) {
	if (pstack == NULL) {
		return;
	}
	else if (pstack->data == NULL) {
		return;
	}
	else {
		free(pstack->data);
	}
}

void stack_push(Stack *pstack, Pointer value) {
	assert(pstack->size <= pstack->capacity);

	if (pstack->capacity == 0) {

		size_t new_capacity = INIT_SIZE;
		pstack->data = malloc(sizeof(Pointer) * new_capacity);

		if (pstack->data == NULL) {
			printf("Error: memory wasn't allocated.\n");
			return;
		}
		else
			pstack->capacity = new_capacity;
	}

	else if (pstack->size == pstack->capacity) {
		size_t new_capacity = pstack->capacity * 2;
		Pointer *new_data = realloc(pstack->data, sizeof(Pointer) * new_capacity);

		if (new_data == NULL) {
			printf("Error: memory wasn't allocated.\n");
			return;
		}
		else {
			pstack->data = new_data;
			pstack->capacity = new_capacity;
		}
	}

	assert(pstack->size < pstack->capacity);
	pstack->data[pstack->size] = value;
	pstack->size++;
}

size_t stack_size(Stack *pstack) {
	return pstack->size;
}

Pointer stack_pop(Stack *pstack) {
	assert(pstack->size <= pstack->capacity);
	if (pstack->size != 0) {
		pstack->size--;
		return pstack->data[pstack->size];
	}
	else {
		return 0;
	}
}

Pointer stack_peek(Stack *pstack) {
	assert(pstack->size <= pstack->capacity);
	if (pstack->size != 0) {
		return pstack->data[pstack->size - 1];
	}
	else {
		return 0;
	}
}

void sort_stack(Stack *stack, int cmp_func(Pointer, Pointer)) {
	for (unsigned i = 1; i < stack->size; i++) {
		for (unsigned j = i; j > 0 && cmp_func(stack->data[j - 1], stack->data[j]) == -1; j--) {
			Pointer t = stack->data[j - 1];
			stack->data[j - 1] = stack->data[j];
			stack->data[j] = t;
		}
	}
}