/*
*	Created by Nan Mihai on 11.03.2017
*	Copyright (c) 2017 Nan Mihai. All rights reserved.
*	Laborator 4 - Structuri de date
*	Grupa 312CC
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2016-2017, Seria CC
*/

#include "stack.h"

void drawStack(Stack stack, char *name) {
	int i, size;
	FILE *stream;
	char *buffer;

	if (stack == NULL || name == NULL)
		return;
	stream = fopen("stack.dot", "w");
	fprintf(stream, "digraph stack {\n");
	fprintf(stream, "rankdir=LR;\nnode [shape=record, style=filled, fillcolor=yellow];\n");
	i = 0;
	fprintf(stream, "\"node0\" [\n label = \"");
	size = stack->size;
	while (!isEmptyStack(stack)) {
		fprintf(stream, "|<f%d> %d", i++, top(stack));
		stack = pop(stack);
	}
	fprintf(stream, "\", shape = \"record\", fillcolor = \"yellow\"];\n}");
	fclose(stream);
	buffer = (char*) malloc(SIZE*sizeof(char));
	sprintf(buffer, "dot stack.dot | neato -n -Tpng -o %s.png", name);
	system(buffer);
	free(buffer);
	stack->size = size;
}

Stack initStack(int capacity) {
	Stack stack = (Stack) malloc(sizeof(struct stack));
	stack->data = (int*) malloc(capacity*sizeof(int));
	stack->size = 0;
	stack->capacity = capacity;
	return stack;
}

Stack ensureCapacity(Stack stack) {
	if (stack->size == stack->capacity) {
		stack->capacity = stack->capacity * 2;
		stack->data = (int*) realloc(stack->data, stack->capacity*sizeof(int));
	}
	return stack;
}

Stack push(Stack stack, int value) {
	stack = ensureCapacity(stack);
	stack->data[stack->size++] = value;
	return stack;
}

Stack pop(Stack stack) {
	stack->size--;
	return stack;
}

int isEmptyStack(Stack stack) {
	if(stack == NULL || stack->size == 0) {
		return 1;
	} else {
		return 0;
	}
}

int top(Stack stack) {
	if (!isEmptyStack(stack)) {
		return stack->data[stack->size-1];
	} else {
		return -1;
	}
}

Stack freeStack(Stack stack) {
	free(stack->data);
	free(stack);
	return NULL;
}

int main() {
	Stack stack;
	int i;

	stack = initStack(SIZE);
	for (i = 0; i < 5; i++) {
		stack = push(stack, i);
	}
	drawStack(stack, "stack1");

	printf("Elementul din varful stivei este: %d\n", top(stack));
	stack = push(stack, 10);
	drawStack(stack, "stack2");
	printf("Elementul din varful stivei este: %d\n", top(stack));
	stack = pop(stack);
	printf("Elementul din varful stivei este: %d\n", top(stack));

	stack = freeStack(stack);
	if (isEmptyStack(stack)) {
		printf("Stiva este vida!\n");
	}

	return 0;
}
