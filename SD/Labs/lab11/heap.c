#include "heap.h"
#include <math.h>

Heap initHeap(int (*compare_func)(const void *, const void *))
{
	Heap h;
	h = calloc(1, sizeof(struct heap));
	h->size = 0;
	h->capacity = MAX;
	h->compare_func = compare_func;
	return h;
}

Heap siftDown(Heap h, int index)
{
	int maxIndex = index;
	int l = 2 * index + 1;
	if (l <= h->size && h->vector[l] > h->vector[maxIndex])
		maxIndex = l;
	int r = 2 * index + 2;
	if (r <= h->size && h->vector[r] > h->vector[maxIndex])
		maxIndex = r;
	if (index != maxIndex)
	{
		swapAndSiftDown(h, index, maxIndex);
		return siftDown(h, maxIndex);
	}
	return h;
}

Heap siftUp(Heap h, int index)
{
	while (index > 1 && h->vector[(int)floor((index - 1) / 2)] < h->vector[index])
	{
		swapAndSiftDown(h, (int)floor((index - 1) / 2), index);
		index = (int)floor((index - 1) / 2);
	}
	return h;
}

Heap swapAndSiftDown(Heap h, int parent, int child)
{

	int aux = h->vector[parent];
	h->vector[parent] = h->vector[child];
	h->vector[child] = aux;
	return h;
}

Heap insertHeap(Heap h, Type element)
{
	if (h->size == h->capacity)
		return h;
	h->vector[h->size] = element;
	h->size++;
	return siftUp(h, h->size - 1);
}

Type extractMax(Heap h)
{
	int result = h->vector[0];
	h->vector[0] = h->vector[h->size - 1];
	h->size--;
	siftDown(h, 0);
	return result;
}

Heap freeHeap(Heap h)
{
	free(h);
	h = NULL;
	return h;
}
