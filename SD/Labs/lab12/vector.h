/*
 * vector.h
 *
 * This file defines a simple, dynamic, vector data structure that holds List elements
 *
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include "list.h"

/**
 * O structura de date reprezentand un vector.
 * */
typedef struct _vector {
	List* data;
	int capacity;
	int size;
}* Vector;


/** Creaza un vector nou*/
Vector vec_init();

/** Elibereaza spatiul folosit de un vector. Returneaza NULL*/
Vector vec_free(Vector v);

/** Se asigura ca zona de date are cel putin capacitatea minCapacity*/
void vec_ensureCapacity(Vector v, int minCapacity);

/** Adauga un element la sfarsitul vectorului */
Vector vec_add(Vector v, List value);

/** Seteaza valoare de la indexul 'index'.
 *  'index' trebuie sa fie mai mic decat size.
 *  Returneaza vectorul actualizat
 * */
Vector vec_set(Vector v, int index, List value);

/** Intoarce numarul de elemente din vector*/
int vec_size(Vector v);

/** Intoarce elementul de la indexul respectiv*/
List vec_at(Vector v, int index);

/** Sterge toate elementele din vector. Vectorul ramane gol dar alocat*/
Vector vec_clear(Vector v);

void vec_print(Vector v);

Vector vec_make(int count, ...);

#endif /* VECTOR_H_ */
