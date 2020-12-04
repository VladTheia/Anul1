#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

//Problema 1
int maxim(int v[], int nr) {
	if (nr == 1) {
		return v[0];
	} else {
		int max = maxim(v, nr-1);
		if (max > v[nr - 1]) 
			return max;
		else
			return v[nr - 1];
	}
}

//Problema 2
int factorial(int nr) {
	if (nr == 0) {
		return 1;
	} else {
		return factorial(nr - 1) * nr;
	}
}

//Problema 3
int putere(int baza, int exponent) {
	if (exponent == 0)
		return 1;
	if (exponent % 2 == 0) {
		int a = putere(baza, exponent / 2);
		return a * a;
	} else {
		int b = putere(baza, (exponent - 1) / 2);
		return baza * b * b;
	}
}

//Problema 4
int euclid(int a, int b) {
	if ( b != 0){
		return euclid(b, a%b);
	} else {
		return a;
	}
}

//Problema 5
int recurenta(int pozitie) {
	if (pozitie == 0) 
		return 0;
	if (pozitie == 1)
		return 1;
	return 4 * recurenta(pozitie - 1) - 3 * recurenta(pozitie - 2) + 1;
}

//Problema 6
/*void permutari(char* sir) {
	printf("%s", sir);
	permutari()
	return 0;
}*/

//Problema 7
void print_submultimi(int v[], int n, int *sequence);
void submultimi(int v[], int n, int index, int *sequence)
{
	if (index > n) {
		print_submultimi(v, n, sequence);
	}
	else {
		sequence[index] = 0;
		submultimi(v, n, index + 1, sequence);
		sequence[index] = 1;
		submultimi(v, n, index + 1, sequence);
	}
}

void print_submultimi(int v[], int n, int *sequence) {
	for (int i = 0; i < n; i++)
		if(sequence[i] == 1)
			printf("%d ", v[i]);
}

static char *test_problema1() {
	int v1[5], i, v2[10], v3[150];
	for(i = 0; i < 5; i++) {
		v1[i] = i;
	}
	sd_assert("Problema1 - Test1 picat", maxim(v1, 5) == 4);
	for(i = 0; i < 10; i++) {
		v2[i] = i;
	}
	v2[5] = 100;
	sd_assert("Problema1 - Test2 picat", maxim(v2, 10) == 100);
	int max = -99999;
	for(i = 0; i < 150; i++) {
		v3[i] = rand();
		if(v3[i] > max) {
			max = v3[i];
		}
	}
	sd_assert("Problema1 - Test2 picat", maxim(v3, 150) == max);
	return 0;
}

static char *test_problema2() {
	sd_assert("Problema2 - Test1 picat", factorial(3) == 6);
	sd_assert("Problema2 - Test2 picat", factorial(5) == 120);
	sd_assert("Problema2 - Test3 picat", factorial(9) == 362880);
	sd_assert("Problema2 - Test4 picat", factorial(7) == 5040);
	sd_assert("Problema2 - Test5 picat", factorial(11) == 39916800);
	return 0;
}

static char *test_problema3() {
	sd_assert("Problema3 - Test1 picat", putere(2, 3) == 8);
	sd_assert("Problema3 - Test2 picat", putere(15262078, 0) == 1);
	sd_assert("Problema3 - Test3 picat", putere(8, 4) == putere(2, 12));
	sd_assert("Problema3 - Test4 picat", putere(4, 4) == putere(2, 8));
	sd_assert("Problema3 - Test5 picat", putere(3, 2) == putere(2, 2) + putere(5, 1));
	return 0;
}

static char *test_problema4() {
	sd_assert("Problema4 - Test1 picat", euclid(8, 2) == 2);
	sd_assert("Problema4 - Test2 picat", euclid(124, 250) == 2);
	sd_assert("Problema4 - Test3 picat", euclid(947, 881) == 1);
	sd_assert("Problema4 - Test4 picat", euclid(51555,915240) == euclid(915240,51555));
	return 0;
}

static char *test_problema5() {
	sd_assert("Problema5 - Test1 picat", recurenta(7) == -3*recurenta(5) + 4*recurenta(6) + 1);
	sd_assert("Problema5 - Test2 picat", recurenta(12) == 4*recurenta(11) - 3*recurenta(10) + 1);
	sd_assert("Problema5 - Test3 picat", recurenta(13) == 1195735);
	return 0;
}

static char *all_tests() {
	sd_run_test(test_problema1, 2);
	sd_run_test(test_problema2, 2);
	sd_run_test(test_problema3, 2);
	sd_run_test(test_problema4, 2);
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

	printf("Introduceti numarul de elemente: ");
	int n;
	scanf("%d", &n);
	printf("Introduceti vectorul: ");
	int *v = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
		scanf("%d", &v[i]);
	int *sequence = malloc(n * sizeof(int));
	submultimi(v, n, 0, sequence);
}
