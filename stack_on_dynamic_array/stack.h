#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <crtdbg.h>
#include <assert.h>
#include <string.h>

#define INIT_SIZE 100

typedef void* Pointer;

typedef struct tStack {
	size_t size;
	size_t capacity;
	Pointer* data;
} Stack;

void stack_create(Stack *pstack);

void stack_destroy(Stack *pstack);

void stack_push(Stack *pstack, Pointer value);

size_t stack_size(Stack *pstack);

Pointer stack_pop(Stack *pstack);

Pointer stack_peek(Stack *pstack);