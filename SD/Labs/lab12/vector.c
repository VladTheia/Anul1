#include "vector.h"

#include <assert.h>
#include <malloc.h>
#include <stdarg.h>
#include <memory.h>

#define VECTOR_INITIAL_SIZE 10


/** Creaza un vector nou*/
Vector vec_init() {
	Vector v = (Vector)malloc(sizeof(struct _vector));
	assert(v);

	v->capacity = VECTOR_INITIAL_SIZE;
	v->data = (List*)malloc(v->capacity * sizeof(List));
	assert(v->data);

	v->size = 0;
	return v;
}

/** Elibereaza spatiul folosit de un vector. Returneaza NULL*/
Vector vec_free(Vector v) {
	if (v!= NULL) {
		free(v->data);
		free(v);
	}
	return NULL;
}

/** Se asigura ca zona de date are cel putin capacitatea minCapacity*/
void vec_ensureCapacity(Vector v, int minCapacity) {
	if (v->capacity >= minCapacity)
		return;

	int newCapacity = v->capacity;
	while(newCapacity < minCapacity) {
		newCapacity *=2;
	}
	v->capacity = newCapacity;
	v->data = (List*)realloc(v->data, v->capacity * sizeof(List));
	assert(v->data);

}

/** Adauga un element la sfarsitul vectorului */
Vector vec_add(Vector v, List value) {
	vec_ensureCapacity(v, v->size + 1);
	v->data[v->size] = value;
	v->size ++;
	return v;
}

/** Intoarce numarul de elemente din vector*/
int vec_size(Vector v) {
	return v->size;
}

/** Intoarce elementul de la indexul respectiv*/
List vec_at(Vector v, int index) {
	assert(index >=0 && index < v->size);
	return v->data[index];
}

Vector vec_set(Vector v, int index, List value) {
	assert(index >=0 && index < v->size);
	v->data[index] = value;
	return v;
}

Vector vec_clear(Vector v) {
	v->size = 0;
	return v;
}

void vec_print(Vector v) {
	int i =0;
	printf("[");
	for (i = 0; i < vec_size(v); ++i) {
		List l = vec_at(v, i);
		list_print(l);
		printf(", ");
	}
	printf("]");
}

Vector vec_make(int count, ...) {
	Vector v = vec_init();
	int i;
	va_list arguments;
	va_start( arguments, count );
	for (i = 0; i< count; ++i) {
		v = vec_add(v, va_arg ( arguments, List));
	}
	va_end(arguments);
	return v;

}

