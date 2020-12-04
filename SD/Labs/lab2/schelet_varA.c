/*
*	Created by Nan Mihai on 02.03.2017
*	Copyright (c) 2017 Nan Mihai. All rights reserved.
*	Laborator 2 - Structuri de date
*	Grupa - 312aCC
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
int total_score = 0;

typedef struct pair {
	int min, max;
}*Pair;

//Problema 1
int suma_cifre(int nr) {
	if (nr != 0) {
		return nr % 10 + suma_cifre(nr / 10);
	}
	return 0;
}

//Problema 2
int binary_search(int *v, int start, int end, int x) {
	int mid = (start + end) / 2;

	if (start > end) {
		return -1;
	}
	if (v[mid] == x && (mid == 0 || v[mid - 1] < x)) {
		return mid;
	} else if (v[mid] >= x) {
		binary_search(v, start, mid - 1, x);
	} else if (v[mid] < x) {
		binary_search(v, mid + 1, end, x);
	}
}

//Problema 3
Pair min_max(int *v, int start, int end) {
	int mid;
	Pair p = (Pair) malloc(sizeof(struct pair));
	Pair p1, p2;
	if (start == end) {
		p->min = v[start];
		p->max = v[start];

		return p;
	} else {
		mid = (start + end) / 2;
		p1 = min_max(v, start, mid);
		p2 = min_max(v, mid + 1, end);
	}

	if (p1->min <= p2->min) {
		p->min = p1->min;
	} else {
		p->min = p2->min;
	}
	if (p1->max >= p2->max) {
		p->max = p1->max;
	} else {
		p->max = p2->max;
	}

	return p;
}

//Problema 4
void swap(int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int *v, int start, int end) {
	int pivot = start;
	int index = start;
	for (int i = start + 1; i <= end; i++) {
		if (v[i] < v[pivot]) {
			index = index + 1;
			swap(&v[i], &v[index]);
		}
	}
		swap(&v[start], &v[index]);
		return index;
}

void quick_sort(int *v, int start, int end) {
	int pivot;
	if (start < end) {
		pivot = partition(v, start, end);
		quick_sort(v, start, pivot - 1);
		quick_sort(v, pivot + 1, end);
	}
}

//Problema 5
int suma(int *v, int size) {
	static int s = 0;
	int mid;
	if (size == 1) {
		s = s + v[0];
	} else {
		mid = size / 2;
		s += suma(v, mid);
		s += suma(v + mid, mid);
	}

	return s;
}

static char *test_problema1() {
	sd_assert("Problema1 - Test1 picat", suma_cifre(7) == 7);
	sd_assert("Problema1 - Test2 picat", suma_cifre(50) == 5);
	sd_assert("Problema1 - Test3 picat", suma_cifre(99) == 18);
	sd_assert("Problema1 - Test4 picat", suma_cifre(11111) == 5);
	sd_assert("Problema1 - Test5 picat", suma_cifre(20202022) == 10);
	return 0;
}

static char *test_problema2() {
	int i, *v = (int*) malloc(100*sizeof(int));
	for(i = 0; i < 50; i++) {
		v[i] = 2*i;
	}
	sd_assert("Problema2 - Test1 picat", binary_search(v, 0, 49, 15) == -1);
	sd_assert("Problema2 - Test2 picat", binary_search(v, 0, 49, 20) == 10);
	sd_assert("Problema2 - Test3 picat", binary_search(v, 0, 49, 33) == -1);
	sd_assert("Problema2 - Test4 picat", binary_search(v, 0, 49, 34) == 17);
	sd_assert("Problema2 - Test5 picat", binary_search(v, 0, 49, 84) == 42);
	sd_assert("Problema2 - Test6 picat", binary_search(v, 0, 49, 0) == 0);
	sd_assert("Problema2 - Test7 picat", binary_search(v, 0, 49, -8912) == -1);
	for (i = 0; i < 10; i++) {
		v[i] = 10;
	}
	sd_assert("Problema2 - Test8 picat", binary_search(v, 0, 9, 10) == 0);
	for (i = 0; i < 10; i++) {
		if (i < 7) {
			v[i] = i;
		} else {
			v[i] = 15;
		}
	}
	sd_assert("Problema2 - Test9 picat", binary_search(v, 0, 9, 15) == 7);
	free(v);
	return 0;
}

static char *test_problema3() {
	int i, min, max, *v = (int*) malloc(100*sizeof(int));
	min = 101, max = -1;
	for(i = 0; i < 10; i++) {
		v[i] = rand() % 100;
		if(v[i] < min) {
			min = v[i];
		}
		if(v[i] > max) {
			max = v[i];
		}
	}
	Pair p;
	p = min_max(v, 0, 9);
	sd_assert("Problema3 - Test1 picat", p->min == min && p->max == max);
	min = 10001;
	max = -1;
	for(i = 0; i < 50; i++) {
		v[i] = rand() % 1000;
		if(v[i] < min) {
			min = v[i];
		}
		if(v[i] > max) {
			max = v[i];
		}
	}
	p = min_max(v, 0, 49);
	sd_assert("Problema3 - Test2 picat", p->min == min && p->max == max);
	min = 10001;
	max = -1;
	for(i = 0; i < 100; i++) {
		v[i] = rand() % 1000;
		if(v[i] < min) {
			min = v[i];
		}
		if(v[i] > max) {
			max = v[i];
		}
	}
	p = min_max(v, 0, 99);
	sd_assert("Problema3 - Test3 picat", p->min == min && p->max == max);
	free(v);
	return 0;
}

int isSorted(int *v, int nr) {
	int i;
	for(i = 0; i < nr - 1; i++) {
		if(v[i] > v[i+1]) {
			return 0;
		}
	}
	return 1;
}

static char *test_problema4() {
	int i, *v = (int*) malloc(100*sizeof(int));
	for(i = 0; i < 10; i++) {
		v[i] = rand();
	}
	quick_sort(v, 0, 9);
	for(i = 0; i < 10; i++)
		printf("%d ", v[i]);
	printf("\n");
	sd_assert("Problema4 - Test1 picat", isSorted(v, 10) == 1);
	for(i = 0; i < 50; i++) {
		v[i] = rand();
	}
	quick_sort(v, 0, 49);
	sd_assert("Problema4 - Test2 picat", isSorted(v, 50) == 1);
	for(i = 0; i < 50; i++) {
		if(i % 3 == 0)
			v[i] = -rand();
	}
	quick_sort(v, 0, 49);
	sd_assert("Problema4 - Test3 picat", isSorted(v, 50) == 1);
	for(i = 0; i < 100; i++) {
		if(i % 5 == 0)
			v[i] = -rand();
	}
	quick_sort(v, 0, 99);
	sd_assert("Problema4 - Test4 picat", isSorted(v, 50) == 1);
	free(v);
	return 0;
}

static char *test_problema5() {
	int i, *v = (int*) malloc(100*sizeof(int));
	for(i = 0; i < 7; i++) {
		v[i] = i+1;
	}
	sd_assert("Problema 5 - Test1 picat", suma(v, 7) == 16);
	for(i = 0; i < 13; i++) {
		v[i] = i;
	}
	sd_assert("Problema 5 - Test2 picat", suma(v, 13) == 46);
	for(i = 0; i < 50; i++) {
		v[i] = i;
	}
	sd_assert("Problema 5 - Test3 picat", suma(v, 50) == 763);
	free(v);
	return 0;
}

static char * all_tests() {
	sd_run_test(test_problema1, 1);
	sd_run_test(test_problema2, 2);
	sd_run_test(test_problema3, 2);
	sd_run_test(test_problema4, 3);
	sd_run_test(test_problema5, 2);
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
	printf("Punctajul obtinut este: %d\n", total_score);
	printf("Teste rulate: %d\n", tests_run);
	return result != 0;
}
