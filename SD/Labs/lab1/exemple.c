#include <stdio.h>

void exemplul1(int nr) {
	if (nr == 0) {
		printf("A ajuns la cazul de baza!\n");
	} else {
		printf("1) Numarul este egal cu %d\n", nr);
		exemplul1(nr - 1);
		printf("2) Numarul este egal cu %d\n", nr);
	}
}

void exemplul2(int nr) {
	if (nr <= 0) {
		printf("A ajuns la cazul de baza!\n");
	} else {
		printf("1) Numarul este egal cu %d\n", nr);
		exemplul2(nr - 1);
		printf("2) Numarul este egal cu %d\n", nr);
		exemplul2(nr - 2);
		printf("3) Numarul este egal cu %d\n", nr);
	}
}

void exemplul3(int nr) {
	if (nr <= 0) {
		printf("A ajuns la cazul de baza!\n");
	} else {
		printf("1) Numarul este egal cu %d\n", nr);
		//IMPORTANT: Apelul de mai jos ar cicla!!!
		//	Decrementarea se face dupa ce este apelata functia exemplul3
		//cu valoarea actuala a lui nr.
		// exemplul3(nr--);
		exemplul3(--nr);
		printf("2) Numarul este egal cu %d\n", nr);
	}
}

void exemplul4(int nr) {
	if (nr == 0) {
		printf("A ajuns la cazul de baza!\n");
	} else {
		//IMPORTANT: Aveti mare grija la astfel de greseli!!!
		printf("1) Numarul este egal cu %d\n", nr);
		//Este apelata o alta functie (exemplul2) => 
		//Functia exemplul4 NU este recursiva!
		exemplul2(nr - 1);
		printf("2) Numarul este egal cu %d\n", nr);
		exemplul2(nr - 2);
		printf("3) Numarul este egal cu %d\n", nr);
	}
}

//Acest exemplu are caz de baza?
void exemplul5(int nr) {
	if (nr > 0) {
		exemplul5(--nr);
		printf("Numarul este egal cu %d\n", nr);
		exemplul5(--nr);
	}
}

int exemplul6(int nr) {
	if (nr % 2) 
		return (nr++);
	else
		return exemplul6(exemplul6(nr - 1));
}

int exemplul7(int a[], int nr) {
	int x;
	if(nr == 1)
		return a[0];
	else
		x = exemplul7(a, nr-1);
	if(x > a[nr-1])
		return x;
	else
		return a[nr-1];
}

int main(int argc, char **argv) {
	//Incercati sa intelegeti de unde provin valorile afisate
	printf("Primul exemplu\n");
	exemplul1(3);
	printf("________________________________________________________\n\n");
	printf("Al doilea exemplu\n");
	exemplul2(3);
	printf("________________________________________________________\n\n");
	printf("Al treilea exemplu\n");
	exemplul3(3);
	printf("________________________________________________________\n\n");
	printf("Al patrulea exemplu\n");
	exemplul4(3);
	printf("________________________________________________________\n\n");
	printf("Al cincilea exemplu\n");
	exemplul5(4);
	printf("________________________________________________________\n\n");
	printf("Al saselea exemplu\n");
	printf("1) Rezultatul este %d pentru 100\n", exemplul6(100));
	printf("2) Rezultatul este %d pentru 101\n", exemplul6(101));
	printf("________________________________________________________\n\n");
	printf("Al saptelea exemplu\n");
	int arr[] = {12, 10, 30, 50, 100};
	printf("Rezultatul este: %d\n", exemplul7(arr, 5));
	printf("________________________________________________________\n\n");
	return 0;
}