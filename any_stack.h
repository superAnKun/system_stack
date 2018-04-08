#ifndef __ANY_STACK_
#define __ANY_STACK_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_OK 1
#define STACK_ERROR 0
typedef struct Stack
{
	char* data;
	int data_size;
	int top, size;
} Stack;

#define init_stack(n, T) (__init_stack(n, sizeof(T)))
#define push_stack(s, data) (__push_stack(s, (char*)(data)))
#define top_stack(s, T)((T*)__top_stack(s))

Stack* __init_stack(int n, int data_size)
{
	Stack* s = (Stack*)malloc(sizeof(Stack));
	s->data = (char*)malloc(n * data_size);
	s->data_size = data_size;
	s->top = -1;
	s->size = n;
	return s;
}

int __push_stack(Stack* s, char* val)
{
	if (s->size - 1 == s->top) return STACK_ERROR;
	s->top++;
	memcpy(s->data + s->top * s->data_size, val, s->data_size);
	return STACK_OK;
}

int empty_stack(Stack* s)
{
	return s->top == -1;
}

int pop_stack(Stack* s)
{
	if (empty_stack(s)) return STACK_ERROR;
	s->top--;
	return STACK_OK;
}

char* __top_stack(Stack* s)
{
	if (empty_stack(s)) return NULL;
	return s->data + s->top * s->data_size;
}

void clear(Stack* s)
{
	if (s == NULL) return ;
	free(s->data);
	free(s);
}

#endif




