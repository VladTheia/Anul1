/*
*	Created by Nan Mihai on 09.03.2017
*	Copyright (c) 2016 Nan Mihai. All rights reserved.
*	Laborator 3 - Structuri de date
*	Grupa 312CC
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2016-2017, Seria CC
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 	100

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

//Definitia structurii de date
typedef struct list {
	int value;
	struct list* next;
}*List;

//Functie care va deseneaza lista
void drawList(List l, char *name, int mid) {
	int i;
	FILE *stream;
	char *buffer;
	List tmp;

	if (l == NULL || name == NULL)
		return;
	stream = fopen("list.dot", "w");
	fprintf(stream, "digraph foo {\n");
	fprintf(stream, "rankdir=LR;\nnode [shape=record, style=filled, fillcolor=yellow];\n");
	tmp = l;
	i = 0;
	while (tmp != NULL) {
		if (mid == tmp->value) {
			fprintf(stream, "a%d [label=\"{ <data> %d | <ref>  }\", width=0.9, fillcolor=blue];\n", i, tmp->value);
		} else {
			fprintf(stream, "a%d [label=\"{ <data> %d | <ref>  }\", width=0.9];\n", i, tmp->value);
		}
		tmp = tmp->next;
		i++;
	}
	fprintf(stream, "b [label=\"NULL\", shape=box, fillcolor=red];\n");
	tmp = l;
	i = 0;
	while (tmp->next != NULL) {
		fprintf(stream, "a%d:ref:c -> a%d:data [arrowhead=vee, arrowtail=dot, dir=both, tailclip=false, arrowsize=0.9];", i, i+1);
		tmp = tmp->next;
		i++;
	}
	fprintf(stream, "a%d:ref:c -> b      [arrowhead=vee, arrowtail=dot, dir=both, tailclip=false];", i);
	fprintf(stream, "}\n");
	fclose(stream);
	buffer = (char*) malloc(SIZE*sizeof(char));
	sprintf(buffer, "dot list.dot | neato -n -Tpng -o %s.png", name);
	system(buffer);
	free(buffer);
}

//Problema 1 - 0 puncte
List initList(int value) {
	List node = (List)malloc(sizeof(struct list));
	node->value = value;
	node->next = NULL;
	return node;
}

//Problema 2 - 0 puncte
void printList(List l) {
	while(l->next != NULL) {
		printf("%d ", l->value);
	}	
	printf("\n");
}

//Problema 3 - 0.5 puncte
List addFirst(List l, int value) {
	List new = initList(value);
	new->next = l;
	return new;
}

//Problema 4 - 1 punct
List addLast(List l, int value) {
	if(l == NULL) {
		l = initList(value);
		return l;
	}
	List lastItem = initList(value);
	List temp = l;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = lastItem;
	return l;
}

//Problema 5 - 1.5 puncte
List addItem(List l, int x, int value) {
	List item = initList(value);
	List temp = l;
	while (temp->value != x) {
		temp = temp->next;
	}
	item->next = temp->next;
	temp->next = item;
	return l;
}

//Problema 6 - 2 puncte
List deleteItem(List l, int value) {
	List temp = l;
	if(temp != NULL)
		if(temp->next != NULL && temp->next->next != NULL) {
			while (temp->next->value != value) {
				temp = temp->next;
			}
	}
	List aux;
	aux = temp->next;
	temp->next = temp->next->next;
	free(aux);
	return l;
}

//Problema 7 - 1 punct
List deleteList(List l) {
	while(l != NULL) {
		List aux = l;
		l = l->next;
		free(aux);
	}
	return NULL;
}

//Problema 8 - 2 puncte
List reunion(List list1, List list2) {
	 List l = NULL;
	

	while (list1 != NULL && list2 != NULL) {
		if (list1->value == list2->value) {
			l = addLast(l, list1->value);
			list1 = list1->next;
			list2 = list2->next;
		} else
		if (list1->value > list2->value) {
			l = addLast(l, list2->value);
			list2 = list2->next;
		} else 
		if (list1->value < list2->value) {
			l = addLast(l, list1->value);
			list1 = list1->next;
		}
	}
	while(list1 != NULL) {
		l = addLast(l, list1->value);
		list1 = list1->next;
	}

	while (list2 != NULL)
	{
		l = addLast(l, list2->value);
		list2 = list2->next;
	}
	return l;
}

//Problema 9 - 2 puncte
int middle(List head) {
	List a = head;
	List b = head;
	if (head != NULL) {
		while(b != NULL && b->next != NULL) {
			b = b->next->next;
			a = a->next;
		}
	}
	return a->value;
}

int check(List l, int *vector, int size) {
	if(l == NULL && size == 0) {
		return 1;
	} else {
		int i = 0;
		while(l != NULL && i < size) {
			if(l->value != vector[i++]) {
				return 0;
			}
			l = l->next;
		}
		if(l == NULL && i == size) {
			return 1;
		} else {
			return 0;
		}
	}
}

static char *test_problema1() {
	int *v, size;
	size = 1;
	v = (int*) malloc(size*sizeof(int));
	v[0] = 5;
	List l = NULL;
	l = initList(5);
	drawList(l, "pb1_test1", -1);
	sd_assert("Problema1 - Test 1 picat", check(l, v, size));
	if(l != NULL) {
		free(l);
	}
	l = initList(10);
	v[0] = 10;
	drawList(l, "pb1_test2", -1);
	sd_assert("Problema1 - Test 2 picat", check(l, v, size));
	if(l != NULL) {
		free(l);
	}
	free(v);
	return 0;
}

static char *test_problema3() {
	int *v, size, i;
	List l = NULL;
	size = 5;
	v = (int*) malloc(size*sizeof(int));
	for(i = 1; i <= size; i++) {
		v[5-i] = rand() % 100;
		l = addFirst(l, v[5-i]);
	}
	drawList(l, "pb3_test1", -1);
	sd_assert("Problema 3 - Test 1 picat", check(l, v, size));
	if(l != NULL) {
		l = deleteList(l);
	}
	free(v);
	l = NULL;
	size = 15;
	v = (int*) malloc(size*sizeof(int));
	for(i = 1; i <= size; i++) {
		v[15-i] = rand() % 100;
		l = addFirst(l, v[15-i]);
	}
	drawList(l, "pb3_test2", -1);
	sd_assert("Problema 3 - Test 2 picat", check(l, v, size));
	if(l != NULL) {
		l = deleteList(l);
	}
	free(v);
	l = NULL;
	size = 50;
	v = (int*) malloc(size*sizeof(int));
	for(i = 1; i <= size; i++) {
		v[50-i] = rand() % 100;
		l = addFirst(l, v[50-i]);
	}
	drawList(l, "pb3_test3", -1);
	sd_assert("Problema 3 - Test 3 picat", check(l, v, size));
	if(l != NULL) {
		l = deleteList(l);
	}
	free(v);
	return 0;
}

static char *test_problema4() {
	int *v, size, i;
	List l = NULL;
	size = 10;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l = addLast(l, v[i]);
	}
	drawList(l, "pb4_test1", -1);
	sd_assert("Problema 4 - Test 1 picat", check(l, v, size));
	if(l != NULL) {
		l = deleteList(l);
	}
	v[0] = rand() % 100;
	for(i = 1; i < size; i++) {
		v[i] = rand() % 100;
		l = addLast(l, v[i]);
	}
	l = addFirst(l, v[0]);
	drawList(l, "pb4_test2", -1);
	sd_assert("Problema 4 - Test 2 picat", check(l, v, size));
	if(l != NULL) {
		l = deleteList(l);
	}
	free(v);
	size = 30;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < 10; i++) {
		v[i] = rand() % 100;
	}
	for(i = 10; i < size; i++) {
		v[i] = rand() % 100;
		l = addLast(l, v[i]);
	}
	for(i = 9; i >= 0; i--) {
		l = addFirst(l, v[i]);
	}
	drawList(l, "pb4_test3", -1);
	sd_assert("Problema 4 - Test 3 picat", check(l, v, size));
	if(l != NULL) {
		l = deleteList(l);
	}
	free(v);
	return 0;
}

static char *test_problema5() {
	int *v, size, i;
	List l = NULL;
	size = 10;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < size; i++) {
		v[i] = i;
		if(i != 5) {
			l = addLast(l, v[i]);
		}
	}
	l = addItem(l, v[4], v[5]);
	drawList(l, "pb5_test1", -1);
	sd_assert("Problema 5 - Test 1 picat", check(l, v, size));
	if(l != NULL) {
		l = deleteList(l);
	}
	free(v);
	l = NULL;
	size = 100;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < size; i++) {
		v[i] = i;
		if(i % 5 != 0 || i == 0) {
			l = addLast(l, v[i]);
		}
	}
	for(i = 5; i < size; i = i + 5) {
		l = addItem(l, v[i-1], v[i]);
	}
	drawList(l, "pb5_test2", -1);
	sd_assert("Problema 5 - Test 2 picat", check(l, v, size));
	if(l != NULL) {
		l = deleteList(l);
	}
	free(v);
	l = NULL;
	size = 200;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < size; i++) {
		v[i] = i;
		if(i % 2 != 0 || i == 0) {
			l = addLast(l, v[i]);
		}
	}
	for(i = 2; i < size; i = i + 2) {
		l = addItem(l, v[i-1], v[i]);
	}
	drawList(l, "pb5_test3", -1);
	sd_assert("Problema 5 - Test 3 picat", check(l, v, size));
	if(l != NULL) {
		l = deleteList(l);
	}
	free(v);
	return 0;
}

static char *test_problema6() {
	int count = 0, size, i, *v;
	size = 10;
	List l = NULL;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < 20; i++) {
		if(i % 2 == 0) {
			v[count++] = i;
		}
		l = addLast(l, i);
	}
	for(i = 0; i < 20; i++) {
		if(i % 2 != 0) {
			l = deleteItem(l, i);
		}
	}
	drawList(l, "pb6_test1", -1);
	sd_assert("Problema 6 - Test 1 picat", check(l, v, count));
	if(l != NULL) {
		l = deleteList(l);
	}
	free(v);
	size = 100;
	count = 0;
	l = NULL;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < 300; i++) {
		if(i % 3 == 0) {
			v[count++] = i;
		}
		l = addLast(l, i);
	}
	for(i = 0; i < 300; i++) {
		if(i % 3 != 0) {
			l = deleteItem(l, i);
		}
	}
	drawList(l, "pb6_test2", -1);
	sd_assert("Problema 6 - Test 2 picat", check(l, v, count));
	if(l != NULL) {
		l = deleteList(l);
	}
	free(v);
	return 0;
}

static char *test_problema8() {
	List l1 = NULL;
	List l2 = NULL, l = NULL;
	int *v, x, i, size;
	size = 20;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < 20; i++) {
		x = rand() % 3;
		if(x == 0) {
			l1 = addLast(l1, i);
		} else if(x == 1) {
			l2 = addLast(l2, i);
		} else {
			l1 = addLast(l1, i);
			l2 = addLast(l2, i);
		}
		v[i] = i;
	}
	l = reunion(l1, l2);
	drawList(l, "pb8_test1", -1);
	sd_assert("Problema 8 - Test 1 picat", check(l, v, size));
	if(l != NULL) {
		l = deleteList(l);
	}
	if(l1 != NULL) {
		l1 = deleteList(l1);
	}
	if(l2 != NULL) {
		l2 = deleteList(l2);
	}
	free(v);
	l1 = l2 = l = NULL;
	size = 1000;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < 1000; i++) {
		x = rand() % 3;
		if(x == 0) {
			l1 = addLast(l1, i);
		} else if(x == 1) {
			l2 = addLast(l2, i);
		} else {
			l1 = addLast(l1, i);
			l2 = addLast(l2, i);
		}
		v[i] = i;
	}
	l = reunion(l1, l2);
	drawList(l, "pb8_test2", -1);
	sd_assert("Problema 8 - Test 2 picat", check(l, v, size));
	if(l != NULL) {
		l = deleteList(l);
	}
	if(l1 != NULL) {
		l1 = deleteList(l1);
	}
	if(l2 != NULL) {
		l2 = deleteList(l2);
	}
	free(v);
	return 0;
}

static char *test_problema9() {
	List l = NULL;
	int i;
	for (i = 0; i < 10; i++) {
		l = addLast(l, i);
	}
	int mid = middle(l);
	drawList(l, "pb9_test1", mid);
	sd_assert("Problema 9 - Test 1 picat", mid == 5);
	l = deleteList(l);
	for (i = 0; i < 20; i++) {
		if (i < 10)
			l = addFirst(l, i);
		else
			l = addLast(l, i);
	}
	mid = middle(l);
	printf("%d\n", mid);
	drawList(l, "pb9_test2", mid);
	sd_assert("Problema 9 - Test 2 picat", mid == 10);
	return 0;
}

static char *test_problema7() {
	List l = NULL;
	int i;
	for (i = 0; i < 10; i++) {
		l = addLast(l, i);
	}
	l = deleteList(l);
	sd_assert("Problema 7 - Test 1 picat", l == NULL);
	for (i = 0; i < 100; i++) {
		if (i < 50)
			l = addFirst(l, i);
		else
			l = addLast(l, i);
	}
	l = deleteList(l);
	sd_assert("Problema 7 - Test 2 picat", l == NULL);
	return 0;
}

static char *all_tests() {
	sd_run_test(test_problema1, 0);
	sd_run_test(test_problema3, 0.5);
	sd_run_test(test_problema4, 1);
	sd_run_test(test_problema5, 1.5);
	sd_run_test(test_problema6, 2);
	sd_run_test(test_problema7, 1);
	sd_run_test(test_problema8, 2);
	sd_run_test(test_problema9, 2);
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
