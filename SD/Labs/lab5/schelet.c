/*
*	Created by Nan Mihai on 16.03.2017
*	Copyright (c) 2017 Nan Mihai. All rights reserved.
*	Laborator 4 - Structuri de date
*	Grupa 312CC
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2016-2017, Seria CC
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE	100

#define sd_assert(message, test) \
	do { \
		if (!(test)) \
			return message; \
	} while (0)

#define sd_run_test(test, score) \
	do { \
		char *message = test(); \
		tests_run++; \
		if (message) \
			return message; \
		else \
			total_score += score; \
	} while (0)

int tests_run = 0;
float total_score = 0;

typedef struct node {
	int value;
	struct node* next;
}*Node;

//Definitia structurii de date pentru stiva
typedef struct stack {
	Node top;
	int size;
}*Stack;

//Definitia structurii de date pentru coada
typedef struct queue {
	Node head, tail;
	int size;
}*Queue;

typedef struct list {
	int value;
	struct list* next;
	int first;
}*CircularList;

Node initNode(int value) {
	Node new = (Node)malloc(sizeof(struct node));
	new->value = value;
	new->next = NULL;
	return new;
}

Node freeNode(Node node) {
	while (node != NULL)
	{
		Node aux = node;
		node = node->next;
		free(aux);
	}
	return NULL;
}


/**
 * Problema 1 - Stiva
 */
Stack initStack(int value) {
	Stack new = (Stack)malloc(sizeof(struct stack));
	new->top = initNode(value);
	new->size = 1;
	return new;
}

int isEmptyStack(Stack stack) {
	if (stack != NULL)
		return (stack->size == 0);
	return 1;
}

Stack push(Stack stack, int value) {
	if (stack != NULL) {
		Node node = initNode(value);
		node->next = stack->top;
		stack->top = node;
		(stack->size)++;
		return stack;
	}
	Stack new = initStack(value);
	return new;
}

Stack pop(Stack stack) {
	if (stack != NULL && stack->top != NULL) {
		Node tmp = stack->top;
		stack->top = stack->top->next;
		free(tmp);
	}
	(stack->size)--;
	return stack;
}

int top(Stack stack) {
	int value = -1;
	if (stack != NULL && stack->top != NULL) {
		value = stack->top->value;
	}
	return value;
}

Stack freeStack(Stack stack) {
	while (stack->top != NULL) {
		Node aux = stack->top;
		stack->top = stack->top->next;
		free(aux);
	}
	return NULL;
}

/**
 * Problema 2 - Coada
 */
Queue initQueue(int value) {
	Queue new = (Queue)malloc(sizeof(struct queue));
	new->head = initNode(value);
	new->tail = new->head;
	new->size = 1;
	return new;
}

Queue enqueue(Queue queue, int value) {
	if (queue != NULL) {
		Node new = initNode(value);
		queue->tail->next = new;
		queue->tail = new;
		(queue->size)++;
		return queue;
	}
	return initQueue(value);
}

int isEmptyQueue(Queue queue) {
	if (queue != NULL)
		return (queue->size == 0);
	return 1;
}

Queue dequeue(Queue queue) {
	if (queue != NULL && queue->head != NULL) {
		Node tmp = queue->head;
		queue->head = queue->head->next;
		free(tmp);
	}
	(queue->size)--;
	return queue;
}

int first(Queue queue) {
	int value = -1;
	if (queue != NULL && queue->head != NULL) {
		value = queue->head->value;
	}
	return value;
}

Queue freeQueue(Queue queue) {
	while (queue->head != NULL) {
		queue = dequeue(queue);
	}
	return NULL;
}

/**
 * Problema 3 - Ce stuctura de date puteti utiliza?
 */
int checkExpression(const char* exp) {
	Stack stack;
	for (unsigned int i = 0; i < strlen(exp); i++) {
		if (exp[i] == '[')
			stack = push(stack, 1);
		else if (exp[i] == '(')
			stack = push(stack, 2);

		if (exp[i] == ']' && top(stack) == 1)
			stack = pop(stack);
		else if(exp[i] == ')' && top(stack) == 2)
			stack = pop(stack);
	} 
	return (isEmptyStack(stack));
}

/**
 * Bonus - Lista circulara simplu inlantuita
 */
int josephus(int number, const char *verse) {
	return 0;
}

int checkStack(Stack stack, int *vect, int len) {
	int i;
	if (stack == NULL) {
		return 0;
	}
	if (stack->size != len) {
		return 0;
	} else {
		for (i = len - 1; i >= 0; i--) {
			if (vect[i] != top(stack)) {
				printf("%d - %d\n", vect[i], top(stack));
				return 0;
			}
			stack = pop(stack);
		}
		return 1;
	}
}

int checkQueue(Queue queue, int *vect, int len) {
	int i;
	if (queue == NULL) {
		return 0;
	}
	if (queue->size != len) {
		return 0;
	} else {
		for (i = 0; i < len; i++) {
			if (vect[i] != first(queue)) {
				return 0;
			}
			queue = dequeue(queue);
		}
		return 1;
	}
}

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

static char *test_problema1() {
	int i, val, *vect, count = 0;
	vect = (int*) malloc(10*sizeof(int));
	Stack stack = NULL;
	for (i = 0; i < 10; i++) {
		val = rand() % 100;
		stack = push(stack, val);
		vect[i] = val;
	}
	//drawStack(stack, "prob1_test1");
	sd_assert ("Problema 1 - Test1 picat!", checkStack(stack, vect, 10));
	free(vect);
	stack = freeStack(stack);
	stack = NULL;
	vect = (int*) malloc(100*sizeof(int));
	for (i = 0; i < 100; i++) {
		val = rand() % 100;
		stack = push(stack, val);
		if(i % 2 != 0) {
			stack = pop(stack);
		} else {
			vect[i/2] = val;
		}
	}
	//drawStack(stack, "prob1_test2");
	sd_assert ("Problema 1 - Test2 picat!", checkStack(stack, vect, 50));
	free(vect);
	stack = freeStack(stack);
	stack = NULL;
	vect = (int*) malloc(1000*sizeof(int));
	for(i = 0; i < 1000; i++) {
		val = rand() % 5000;
		stack = push(stack, val);
		vect[count++] = val;
		if(val % 3 == 0) {
			stack = pop(stack);
			if(count > 0) {
				count--;
			}
			stack = pop(stack);
			if(count > 0) {
				count--;
			}
		}
	}
	sd_assert ("Problema 1 - Test3 picat!", checkStack(stack, vect, count));
	free(vect);
	stack = freeStack(stack);
	return 0;
}

static char *test_problema2() {
	int i, val, *vect, count = 0;
	vect = (int*) malloc(10*sizeof(int));
	Queue queue = NULL;
	for(i = 0; i < 10; i++) {
		val = rand() % 100;
		queue = enqueue(queue, val);
		vect[i] = val;
	}
	sd_assert ("Problema 2 - Test1 picat!", checkQueue(queue, vect, 10));
	free(vect);
	queue = freeQueue(queue);
	queue = NULL;
	vect = (int*) malloc(100*sizeof(int));
	for(i = 0; i < 100; i++) {
		val = rand() % 100;
		queue = enqueue(queue, val);
		if(i > 10 && i < 20) {
			queue = dequeue(queue);
		} 
		if(i >= 9) {
			vect[count++] = val;
		}
	}
	sd_assert ("Problema 2 - Test2 picat!", checkQueue(queue, vect, count));
	free(vect);
	queue = freeQueue(queue);
	queue = NULL;
	vect = (int*) malloc(1000*sizeof(int));
	count = 0;
	for(i = 0; i < 1000; i++) {
		val = rand() % 5000;
		queue = enqueue(queue, val);
		if(i > 100 && i < 300) {
			queue = dequeue(queue);
		} 
		if(i >= 199) {
			vect[count++] = val;
		}
	}
	sd_assert ("Problema 2 - Test3 picat!", checkQueue(queue, vect, count));
	free(vect);
	queue = freeQueue(queue);
	return 0;
}

static char *test_bonus() {
	sd_assert ("Problema 3 - Test1 picat!", josephus(10, "ala bala portocala bala ala\0") == 3);
	sd_assert ("Problema 3 - Test2 picat!", josephus(25, "Ciresica are mere, Ciresel vine si cere!\n\0") == 15);
	sd_assert ("Problema 3 - Test3 picat!", josephus(100, "Ala bala portocala\nToata casa-i alandala\0") == 68);
	sd_assert ("Problema 3 - Test4 picat!", josephus(7, "una mia suta lei ia te rog pe cine vrei din gramada cu purcei") == 1);
	sd_assert ("Problema 3 - Test5 picat!", josephus(250, "Intr-un castel de ciocolata  Traia o zana fermecata Ce culoare avea rochea de pe ea?\0") == 162);
	return 0;
}

static char *test_problema3() {
	sd_assert ("Bonus - Test1 picat!", checkExpression("[(([])([])()())]\0") == 1);
	sd_assert ("Bonus - Test2 picat!", checkExpression("(((([([([])])]))))\0") == 1);
	sd_assert ("Bonus - Test3 picat!", checkExpression("(([])((([()]))()))\0") == 1);
	sd_assert ("Bonus - Test4 picat!", checkExpression("((((((()))[]))))))(((((([]))))))))((((()[])))))))[]]]]]]]][[[[](((((((((((())\0") == 0);
	sd_assert ("Bonus - Test5 picat!", checkExpression("[](()(((([]((((())[]))))))))((((((((()((((()))))))((((((((())()))\0") == 0);
	sd_assert ("Bonus - Test6 picat!", checkExpression(")))))])))([[()(()())]]((((((((\0") == 0);
	return 0;
}

static char *all_tests() {
	sd_run_test(test_problema1, 3);
	sd_run_test(test_problema2, 3);
	sd_run_test(test_problema3, 2);
	sd_run_test(test_bonus, 4);
	return 0;
 }

int main() {
	srand(time(NULL));
	char *result = all_tests();
	if (result != 0) {
		printf("%s\n", result);
	}
	else {
		printf("Toate testele au trecut! Felicitari!\n");
	}
	printf("Punctajul obtinut este: %.2lf\n", total_score);
	printf("Teste rulate: %d\n", tests_run);
	return result != 0;
}
