#include "queue.h"

Queue initQueue(int capacity) {
	Queue queue = (Queue) malloc(sizeof(struct queue));
	queue->head = queue->tail = 0;
	queue->size = 0;
	queue->capacity = capacity;
	queue->data = (int*) malloc(capacity*sizeof(int));
	return queue;
}

Queue enqueue(Queue queue, int value) {
	if(queue->capacity > queue->size) {
		//Adaug doar daca mai am loc
		queue->data[queue->tail] = value;
		queue->tail = (queue->tail + 1) % queue->capacity;
		queue->size++;
	}
	return queue;
}

int isEmptyQueue(Queue queue) {
	if(queue->size == 0) {
		return 1;
	} else {
		return 0;
	}
}

Queue dequeue(Queue queue) {
	if(!isEmptyQueue(queue)) {
		queue->head = (queue->head + 1) % queue->capacity;
		queue->size--;
	}
	return queue;
}

int first(Queue queue) {
	if(!isEmptyQueue(queue)) {
		return queue->data[queue->head];
	} else {
		return -1;
	}
}

Queue freeQueue(Queue queue) {
	free(queue->data);
	free(queue);
	return NULL;
}

int main(int argc, char **argv) {
	Queue queue;
	int i;

	queue = initQueue(SIZE);
	for (i = 0; i < SIZE; i++) {
		queue = enqueue(queue, i);
		if (i % 2 != 0) {
			printf("%d ", first(queue));
			queue = dequeue(queue);
		}
	}
	printf("\n");
	while(!isEmptyQueue(queue)) {
		printf("%d ", first(queue));
		queue = dequeue(queue);
	}
	printf("\n");

	for (i = 0; i < 3 * SIZE; i++) {
		queue = enqueue(queue, i);
		if (i % 2 != 0) {
			printf("%d ", first(queue));
			queue = dequeue(queue);
		}
	}
	printf("\n");
	while(!isEmptyQueue(queue)) {
		printf("%d ", first(queue));
		queue = dequeue(queue);
	}
	printf("\n");
	queue = freeQueue(queue);
	return 0;
}