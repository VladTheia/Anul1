#include <stdbool.h>

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED


typedef struct stack Stack;
typedef struct stackItem StackItem;

typedef struct stack
{
	StackItem *firstItem;
} STACK;


typedef struct stackItem
{
	void *item;
	StackItem *next;
} STACKITEM;

Stack *stack_create();

void stack_push(Stack *stack, void *item);

void *stack_pop(Stack *stack);

bool stack_empty(Stack *stack);

#endif
