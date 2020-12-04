#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct point {
	int x, y;
} Point;

typedef Point T;

typedef struct queue {
	T *data;
	int capacity, size;
	int head, tail;
}*Queue;

Queue initQueue(int capacity);
Queue enqueue(Queue queue, T value);
int isEmpty(Queue queue);
Queue dequeue(Queue queue);
T first(Queue queue);
Queue freeQueue(Queue queue);
