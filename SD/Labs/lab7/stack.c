#include <stdlib.h>
#include "Stack.h"

Stack *stack_create()
{
	Stack *stack = malloc(sizeof(Stack));
	stack->firstItem = NULL;
	return stack;
}

bool stack_empty(Stack *stack)
{
	return stack->firstItem == NULL;
}

void stack_push(Stack *stack, void *item)
{
	StackItem *stackItem = malloc(sizeof(stackItem));
	stackItem->item = item;
	stackItem->next = stack->firstItem;
	stack->firstItem = stackItem;
}


void *stack_pop(Stack *stack)
{
	if (stack_empty(stack))
	{
		return NULL;
	}

	void *item = stack->firstItem->item;
	void *next = stack->firstItem->next;


	free(stack->firstItem);

	stack->firstItem = next;

	return item;


}
