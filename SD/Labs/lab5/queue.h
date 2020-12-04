#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct queue {
	int *data;
	int capacity, size;
	int head, tail;
}*Queue;

Queue initQueue(int capacity);
Queue enqueue(Queue queue, int value);
int isEmptyQueue(Queue queue);
Queue dequeue(Queue queue);
int first(Queue queue);
Queue freeQueue(Queue queue);