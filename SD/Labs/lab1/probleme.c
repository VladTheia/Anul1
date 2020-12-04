/*
*	Created by Nan Mihai on 15.02.2018
*	Copyright (c) 2016 Nan Mihai. All rights reserved.
*	Laborator 1 - Structuri de date (Probleme pregatitoare)
*	Grupa 314CC
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2017-2018, Seria CC
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define sd_assert(message, test) \
	do { \
		if (!(test)) \
			return message; \
	} while (0)

#define sd_run_test(test) \
	do { \
		char *message = test(); \
		tests_run++; \
		if (message) \
			return message; \
	} while (0)

int tests_run = 0;

//Problema 1
/*
*	Cerinta: Implementati o functie recursiva care sa verifice daca un numar 
* natural este par sau impar. (va intoarce 0 pentru numerele pare si 1 pentru
* cele impare)
*/
int paritate(int nr) {
	return -1;
}

//Problema 2
/*
*	Cerinta: Implementati o functie recursiva care primeste doua numere natu-
* rale (x si y) ca argumente si calculeaza urmatoarea suma:
* ((1 + 2 … + x-1 + x) +y)
*/
int suma(int x, int y) {
	return -1;
}

//Problema 3
/*
*	Cerinta: Implementati o functie recursiva care sa primeasca un numar natu-
* ral si sa afiseze codificarea sa binara.
* Exemplu: Pentru 21 se va afisa 10101
*/
void codificare_binara(int nr) {
	printf("UNDEFINED");
}

//Problema 4
/*
*	Cerinta: Scrieti o functie recursiva care sa primeasca doua numere naturale
* x si y ca argumente si sa returneze produsul lor (x * y).
* Exemplu: 4 * 3 => 12
*/
int inmultire(int x, int y) {
	return -1;
}

//Problema 5
/*
*	Cerinta: Scrieti o functie recursiva care sa primeasca doua numere naturale
* x si y ca argumente si sa returneze x la puterea y (x ^ y).
* Exemplu: 4 ^ 3 => 64
*/
int putere(int x, int y) {
	return -1;
}

static char *test_problema1() {
	sd_assert("Problema1 - Test1 picat", paritate(5) == 1);
	sd_assert("Problema1 - Test2 picat", paritate(5551) == 1);
	sd_assert("Problema1 - Test3 picat", paritate(9990) == 0);
	sd_assert("Problema1 - Test4 picat", paritate(1208) == 0);
	return 0;
}

static char *test_problema2() {
	sd_assert("Problema2 - Test1 picat", suma(5, 10) == 25);
	sd_assert("Problema2 - Test2 picat", suma(55, 102) == 1642);
	sd_assert("Problema2 - Test3 picat", suma(42, 17) == 920);
	sd_assert("Problema2 - Test4 picat", suma(19, 22) == 212);
	return 0;
}

static char *test_problema3() {
	printf("Problema 3: pentru 21 reprezentarea binara determinata este: ");
	codificare_binara(21);
	printf(", iar rezultatul dorit este: 10101!\n");
	printf("Problema 3: pentru 42 reprezentarea binara determinata este: ");
	codificare_binara(42);
	printf(", iar rezultatul dorit este: 101010!\n");
	printf("Problema 3: pentru 7 reprezentarea binara determinata este: ");
	codificare_binara(7);
	printf(", iar rezultatul dorit este: 111!\n");
	return 0;
}

static char *test_problema4() {
	sd_assert("Problema4 - Test1 picat", inmultire(5, 10) == 50);
	sd_assert("Problema4 - Test2 picat", inmultire(5, 7) == 35);
	sd_assert("Problema4 - Test3 picat", inmultire(12, 12) == 144);
	sd_assert("Problema4 - Test4 picat", inmultire(19, 22) == 418);
	return 0;
}

static char *test_problema5() {
	sd_assert("Problema5 - Test1 picat", putere(5, 4) == 625);
	sd_assert("Problema5 - Test2 picat", putere(3, 5) == 243);
	sd_assert("Problema5 - Test3 picat", putere(12, 3) == 1728);
	sd_assert("Problema5 - Test4 picat", putere(2, 22) == 4194304);
	return 0;
}


static char *all_tests() {
	sd_run_test(test_problema1);
	sd_run_test(test_problema2);
	sd_run_test(test_problema3);
	sd_run_test(test_problema4);
	sd_run_test(test_problema5);
	return 0;
 }

int main() {
	srand(time(NULL));
	char *result = all_tests();
	if (result != 0) {
		printf("%s\n", result);
	} else {
		printf("Toate testele au trecut! Felicitari!\n");
	}
	printf("Teste rulate: %d\n", tests_run);
	return result != 0;
}