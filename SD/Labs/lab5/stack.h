/*
*	Created by Nan Mihai on 11.03.2017
*	Copyright (c) 2017 Nan Mihai. All rights reserved.
*	Laborator 4 - Structuri de date
*	Grupa 312CC
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2016-2017, Seria CC
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

typedef struct stack {
  int *data;
  int capacity;
  int size;
}*Stack;

Stack initStack(int capacity);
Stack ensureCapacity(Stack stack);
Stack push(Stack stack, int value);
Stack pop(Stack stack);
int isEmptyStack(Stack stack);
int top(Stack stack);
Stack freeStack(Stack stack);
void drawStack(Stack stack, char *name);
