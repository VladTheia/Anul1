/*
*	Created by Nan Mihai on 15.03.2018
*	Copyright (c) 2018 Nan Mihai. All rights reserved.
*	Laborator 4 - Structuri de date
*	Grupa 314CC
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2017-2018, Seria CC
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
	struct list* prev;
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
	i = 1;
	fprintf(stream, "a0 [label=\"NULL\", shape=box, fillcolor=red];\n");
	while (tmp != NULL) {
		if (mid == tmp->value) {
			fprintf(stream, "a%d [label=\"{ <ref1> | <data> %d | <ref2>  }\", width=0.9, fillcolor=blue];\n", i, tmp->value);
		} else {
			fprintf(stream, "a%d [label=\"{ <ref1> | <data> %d | <ref2>  }\", width=0.9];\n", i, tmp->value);
		}
		tmp = tmp->next;
		i++;
	}
	fprintf(stream, "b [label=\"NULL\", shape=box, fillcolor=red];\n");
	tmp = l;
	i = 1;
	fprintf(stream, "a0:e -> a1:ref1:c      [arrowhead=vee, arrowtail=dot, dir=both, tailclip=false, color=white];");
	fprintf(stream, "a1:ref1:c -> a0      [arrowhead=vee, arrowtail=dot, dir=both, tailclip=false];");
	while (tmp->next != NULL) {
		fprintf(stream, "a%d:ref2:c -> a%d:ref1:c [arrowhead=vee, arrowtail=dot, dir=both, tailclip=false, arrowsize=0.9, color=red];\n", i, i+1);
		fprintf(stream, "a%d:ref1:c -> a%d:ref2:c [arrowhead=vee, arrowtail=dot, dir=both, tailclip=false, arrowsize=0.9, color=blue];\n", i+1, i);
		tmp = tmp->next;
		i++;
	}
	fprintf(stream, "a%d:ref2:c -> b      [arrowhead=vee, arrowtail=dot, dir=both, tailclip=false];\n", i);
	fprintf(stream, "}\n");
	fclose(stream);
	buffer = (char*) malloc(SIZE*sizeof(char));
	sprintf(buffer, "dot list.dot | neato -n -Tpng -o %s.png", name);
	system(buffer);
	free(buffer);
}

//Problema 1 - 0.5p
List initList(int value) {
	List node;
	node = (List)malloc(sizeof(struct list));
	node->value = value;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

//Problema 2 - 1p
List addFirst(List l, int value) {
	List new = initList(value);
	if (l != NULL) {
		new->next = l;
		l->prev = new;
		return new;
	} else
	return initList(value);
}

//Problema 3 - 1p
List addLast(List l, int value) {
	List temp;
	if (l != NULL) {
		temp = l;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		List new = initList(value);
		new->prev = temp;
		temp->next = new;
		return l;
	} else
	return initList(value);
}

//Problema 4 - 1p
List addItem(List l, int x, int value) {
	List temp;
	if (l != NULL) {
		temp = l;
		while (temp->value != x) {
			temp = temp->next;
		}
		List new = initList(value);
		new->prev = temp;
		if(temp->next != NULL) 
			new->next = temp->next;
		temp->next = new;
		return l;
	} else
	return initList(value);
}

//Problema 5 - 2p
List deleteItem(List l, int value) {
	if (l != NULL) {
		List temp = l;
		if (temp->value == value) {
			l = temp->next;
			free(temp);
			return l;
		}
		while (temp->next->value != value)
			temp = temp->next;
		List aux = temp->next;
		List aux2 = aux->next;
		temp->next = aux2;
		if(aux2 != NULL)
			aux2->prev = temp;
		free(aux);
		return l;
	}
}

//Functie de afisare a listei
void printList(List l) {
	while (l != NULL) {
		printf("%d ", l->value);
		l = l->next;
	}
	printf("\n");
}

//Problema 6 - 1p
List deleteList(List l) {
	while (l != NULL)
	{
		List aux = l;
		l = l->next;
		free(aux);
	}
	return NULL;
}

//Problema 7 - 1p
List reverse(List list) {
	List temp = NULL;
	List current = list;
	while (current != NULL) {
		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = current->prev;
	}
	if (temp != NULL) 
		list = temp->prev;
	return list;
}

//Problema 8 - 2.5p
void print_pairs(List l, int x) {
	if (l != NULL) {
		List temp = l;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		List right = temp;
		List left = l;
		while (left != right) {
			int sum = left->value + right->value;
			if (sum == x) {
				printf("(%d, %d)", left->value, right->value);
				left = left->next;
				right = right->prev;
			} 
			if (sum > x) {
				right = right->prev;
			} 
			if (sum < x ) {
				left = left->next;
			}
		}
	}
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
	drawList(l, "prob1_test1", -1);
	sd_assert("Problema1 - Test1 picat", check(l, v, size));
	if(l != NULL) {
		free(l);
	}
	l = initList(10);
	v[0] = 10;
	drawList(l, "prob1_test2", -1);
	sd_assert("Problema1 - Test2 picat", check(l, v, size));
	if(l != NULL) {
		free(l);
	}
	free(v);
	return 0;
}

static char *test_problema2() {
	int *v, size, i;
	List l = NULL;
	size = 5;
	v = (int*) malloc(size*sizeof(int));
	for(i = 1; i <= size; i++) {
		v[5-i] = rand() % 100;
		l = addFirst(l, v[5-i]);
	}
	drawList(l, "prob2_test1", -1);
	sd_assert("Problema 2 - Test1 picat", check(l, v, size));
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
	drawList(l, "prob2_test2", -1);
	sd_assert("Problema 2 - Test2 picat", check(l, v, size));
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
	drawList(l, "prob2_test3", -1);
	sd_assert("Problema 2 - Test3 picat", check(l, v, size));
	if(l != NULL) {
		l = deleteList(l);
	}
	free(v);
	return 0;
}

static char *test_problema3() {
	int *v, size, i;
	List l = NULL;
	size = 10;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l = addLast(l, v[i]);
	}
	drawList(l, "prob3_test1", -1);
	sd_assert("Problema3 - Test1 picat", check(l, v, size));
	if(l != NULL) {
		l = deleteList(l);
	}
	v[0] = rand() % 100;
	for(i = 1; i < size; i++) {
		v[i] = rand() % 100;
		l = addLast(l, v[i]);
	}
	l = addFirst(l, v[0]);
	drawList(l, "prob3_test2", -1);
	sd_assert("Problema3 - Test2 picat", check(l, v, size));
	if(l != NULL) {
		l = deleteList(l);
	}
	free(v);
	size = 100;
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
	drawList(l, "prob3_test3", -1);
	sd_assert("Problema3 - Test3 picat", check(l, v, size));
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
		v[i] = i;
		if(i != 5) {
			l = addLast(l, v[i]);
		}
	}
	l = addItem(l, v[4], v[5]);
	drawList(l, "prob4_test1", -1);
	sd_assert("Problema4 - Test1 picat", check(l, v, size));
	if(l != NULL) {
		l = deleteList(l);
	}
	free(v);
	l = NULL;
	size = 1000;
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
	sd_assert("Problema4 - Test2 picat", check(l, v, size));
	if(l != NULL) {
		l = deleteList(l);
	}
	free(v);
	l = NULL;
	size = 10000;
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
	sd_assert("Problema4 - Test3 picat", check(l, v, size));
	if(l != NULL) {
		l = deleteList(l);
	}
	free(v);
	return 0;
}

static char *test_problema5() {
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
	drawList(l, "prob5_test1", -1);
	sd_assert("Problema5 - Test1 picat", check(l, v, count));
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
	drawList(l, "prob5_test2", -1);
	sd_assert("Problema5 - Test2 picat", check(l, v, count));
	if(l != NULL) {
		l = deleteList(l);
	}
	free(v);
	return 0;
}

static char *test_problema7() {
	List l = NULL;
	int *v, x, i, size;
	size = 100;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < 100; i++) {
		x = rand() % 1000;
		l = addLast(l, x);
		v[100-i-1] = x;
	}
	l = reverse(l);
	sd_assert("Problema7 - Test1 picat", check(l, v, size));
	if(l != NULL) {
		l = deleteList(l);
	}
	free(v);
	l = NULL;
	size = 1000;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < size; i++) {
		x = rand();
		l = addLast(l, x);
		v[size-i-1] = x;
	}
	l = reverse(l);
	sd_assert("Problema7 - Test2 picat", check(l, v, size));
	if(l != NULL) {
		l = deleteList(l);
	}
	free(v);
	l = NULL;
	size = 5000;
	v = (int*) malloc(size*sizeof(int));
	for(i = 0; i < size; i++) {
		x = rand();
		l = addLast(l, x);
		v[size-i-1] = x;
	}
	l = reverse(l);
	sd_assert("Problema7 - Test3 picat", check(l, v, size));
	if(l != NULL) {
		l = deleteList(l);
	}
	free(v);
	return 0;
}

static char *all_tests() {
	sd_run_test(test_problema1, 0.5);
	sd_run_test(test_problema2, 1);
	sd_run_test(test_problema3, 1);
	sd_run_test(test_problema4, 1);
	sd_run_test(test_problema5, 2);
	sd_run_test(test_problema7, 1);
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
	List l = initList(1);
	addLast(l, 2);
	addLast(l, 3);
	addLast(l, 4);
	addLast(l, 5);
	print_pairs(l, 6);
	return result != 0;
}
