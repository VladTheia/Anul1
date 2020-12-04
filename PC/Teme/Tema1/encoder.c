#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100
#define CARACTER 1
#define NUMAR 2
#define CUVANT 3

typedef struct {
	char * subsir;
 	double complexitate; 
 } STRUCTURA;

int citire(char ***sir_principal, int **tip, int *n)
{
	int n_coloane = MAX_LENGTH; //numarul maxim de caractere al unui cuvant
	int n_linii =2* MAX_LENGTH; //numarul de elemente citite de la tastatura
	*tip = calloc(MAX_LENGTH, sizeof(int)); //vector de salvare a tipului
	*sir_principal = calloc(n_linii, sizeof(char*)); //alocare dinamica pentru pointer-ul de vectori
	int i;
	for (i = 0; i < n_linii; i++)
		(*sir_principal)[i] = calloc(n_coloane, sizeof(char)); //alocare dinamica pentru fiecare vector
	i = 0;
	scanf("%s", (*sir_principal)[i]); //citirea primului element
	while (strcmp((*sir_principal)[i], "END") != 0) //citirea elementelor pana la intalnirea cuvanului "END"
	{
		if (strlen((*sir_principal)[i]) == 1)
		{
			if ((*sir_principal)[i][0] < '0' || (*sir_principal)[i][0] > '9') //verificam daca este caracter sau numar
				(*tip)[i] = CARACTER; //1 pentru caractere
			else
				(*tip)[i] = NUMAR; //2 pentru numere
		}
		else
		{
			int k = 0;
			if ((*sir_principal)[i][k] == '-'){ //pentru numere care incep cu -
				k++;
				(*tip)[i] = NUMAR;
				while ((*sir_principal)[i][k] != '\0')
				{
					if((*sir_principal)[i][k] < '0' || (*sir_principal)[i][k] > '9') //verificam existenta unui alt caracter decat o cifra in stringul citit
					{
						(*tip)[i] = CUVANT; //3 pentru cuvinte
						break;
					}
					k++;
				}
			}
			else
			{
				(*tip)[i] = NUMAR;
				while ((*sir_principal)[i][k] != '\0')
				{
					if ((*sir_principal)[i][k] < '0' || (*sir_principal)[i][k] > '9')
					{
						(*tip)[i] = CUVANT;
						break;
					}
					k++;
				}
			}
		}
		i++; //trecerea la urmatorul element
		scanf("%s", (*sir_principal)[i]);
	}
	*n = atoi((*sir_principal)[i - 1]); // aflarea lui n si convertirea lui in numar
	
	int k;
	int cuvinte = 0;
	int caractere = 0;
	int numere = 0;
	for(k = 0; k < i-1; k++)
	{
		if((*tip)[k] == CUVANT)
			cuvinte++;
		if((*tip)[k] == CARACTER)
			caractere++;
		if((*tip)[k] == NUMAR){
			numere++;
			//printf("numarul e %s\n", (*sir_principal)[k]);
		}
	}
	printf("%d %d %d\n", cuvinte, caractere, numere);


	return i-1;
}

void codificare_cuvant(char *cuvant, char *sir_codificat)
{
	int k = 0; //aflare numar caractere cuvant
	int ok = 0; //verificam existenta unei cifre
	while (cuvant[k] != '\0')
	{
		if (cuvant[k] >= '0' && cuvant[k] <= '9')
			ok = 1; //cuvantul contine o cifra
		k++;
	}

	int d;//cel mai mare divizor
	int j;
	for (j = 1; j <= k/2; j++)
	{
		if (k % j == 0)
			d = j;
	}
	char *aux1 = calloc(strlen(cuvant), sizeof(char));//string auxiliar
	char *aux2 = calloc(strlen(cuvant), sizeof(char));//string auxiliar	

	if (ok == 1)
	{
		strncpy(aux1, cuvant, d); //salvarea primelor d caractere intr-un auxiliar
		aux1[d] = '\0';
		strcpy(aux2, cuvant + d);
		strcpy(cuvant, aux2); //stergerea primelor d caractere din cuvant
		char *start = cuvant; //primul caracter
		char *sfarsit = cuvant + strlen(cuvant) - 1; //ultimul caracter
		char aux3;
		
		while (sfarsit > start) //interschimbare cuvinte
		{
			aux3 = *start;
			*start = *sfarsit;
			*sfarsit = aux3;

			++start;
			--sfarsit;
		}
		strcat(cuvant, aux1); //adaugarea caracterelor salvate anterior la sfarsitul sirului
	}
	else
	{
		strncpy(aux1, cuvant, d); //salvarea primelor d caractere intr-un auxiliar
		aux1[d] = '\0';
		strcpy(aux2, cuvant + d);
		strcpy(cuvant, aux2); //stergerea primelor d caractere din cuvant
		strcat(cuvant, aux1); //adaugarea caracterelor salvate anterior la sfarsitul sirului
	}
	
	strcat(sir_codificat, cuvant); //adaugarea cuvantului modificat la sir
	free(aux1);
	free(aux2);
}

void codificare_caracter(char caracter, char *sir_codificat)
{
	if(strlen(sir_codificat) == 0)
	{
		sir_codificat[0] = caracter;
		sir_codificat[1] = '\0';
	}
	else
	{
		int i;
		int max, min ; //pastrarea numarul de aparitii al caracterelor cu numar maxim/minim de aparitii
		char char_max, char_min; //caracterele cu numar maxim/minim de aparitii
		int nr_aparitii[128] = {0};

		for (i = 0; i < strlen(sir_codificat); i++)
		{
			nr_aparitii[sir_codificat[i]]++; //determinarea numarului de aparitii al fiecarui caracter
		}

		max = nr_aparitii[sir_codificat[0]];
		min = nr_aparitii[sir_codificat[0]];
		char_max = sir_codificat[0];
		char_min = sir_codificat[0];

		for (i = 0; i < strlen(sir_codificat); i++)
		{
			if (max < nr_aparitii[sir_codificat[i]])
			{
				max = nr_aparitii[sir_codificat[i]];
				char_max = sir_codificat[i]; //algoritm de gasire a caracterului cu cele mai multe aparitii
			}
			if (min > nr_aparitii[sir_codificat[i]])
			{
				min = nr_aparitii[sir_codificat[i]];
				char_min = sir_codificat[i];//algoritm de gasire a caracterului cu cele mai putine aparitii
			}
		}
	
		char aux[4] = { char_max, caracter, char_min, '\0' };
		strcat(sir_codificat, aux); //adaugarea caracterului codificat la sir
	}
}

void codificare_numar(char *numar, char *sir_codificat)
{
	if (numar[0] == '-')
	{
		char *aux1 = calloc((strlen(numar) - 1), sizeof(char)); //string auxiliar
		strcpy(aux1, numar + 1);
		strcpy(numar, aux1);
		char *minim = calloc((strlen(numar) - 1), sizeof(char));
		strcpy(minim, numar);
		int i;
		for (i = 0; i < strlen(numar); i++)
		{
			char aux2[2] = { numar[0], '\0' };
			strcpy(aux1, numar + 1);
			strcpy(numar, aux1);	
			strcat(numar, aux2);
			if (strcmp(minim, numar) > 0)
				strcpy(minim, numar);
		}
		strcpy(numar, minim);
		free(aux1);
	}
	else
	{
		char *aux1 = calloc(strlen(numar), sizeof(char));
		char *maxim = calloc(strlen(numar), sizeof(char));
		strcpy(maxim, numar);
		int i;
		for (i = 0; i < strlen(numar); i++)
		{
			char aux2[2] = { numar[0], '\0' };
			strcpy(aux1, numar + 1);
			strcpy(numar, aux1);	
			strcat(numar, aux2);
			if (strcmp(maxim, numar) < 0)
				strcpy(maxim, numar);
		}
		strcpy(numar,maxim);
		free(aux1);
	}

	strcat(sir_codificat, numar);
}

int construire_sir(char **sir_codificat) 
{
	char **sir_principal;
	int *tip;
	int n;
	int nr = citire(&sir_principal, &tip, &n); //numar elemente
	int i;

	*sir_codificat = calloc(2*MAX_LENGTH * MAX_LENGTH, sizeof(char));
	for ( i = 0; i < nr; i++)
	{
		if (tip[i] == CUVANT)
			codificare_cuvant(sir_principal[i], *sir_codificat);
		if (tip[i] == CARACTER)
			codificare_caracter(sir_principal[i][0], *sir_codificat);
		if (tip[i] == NUMAR)
			codificare_numar(sir_principal[i], *sir_codificat);
	}
	printf("%s\n", *sir_codificat);

	free(sir_principal);
	free(tip);
	
	return n;
}

int comparare(const void *a, const void *b)
{
	return (((STRUCTURA*)a)->complexitate < ((STRUCTURA*)b)->complexitate);
}

void sortare_sir()
{
	char *sir_codificat;
	int n = construire_sir(&sir_codificat);
	STRUCTURA *s = calloc(n, sizeof(STRUCTURA));
	int i, k;
	int len = strlen(sir_codificat);
	double suma = 0;
	for (i = 0; i < n-1 ; i++)
	{
		suma = 0;
		s[i].subsir = calloc(len / n + 1, sizeof(char));
		strncpy(s[i].subsir, sir_codificat + i * (len / n), len / n);
		for(k = 0; k < strlen(s[i].subsir); k++)
			suma += s[i].subsir[k];
		s[i].complexitate = suma / strlen(s[i].subsir);
	}
	suma = 0;
	s[n-1].subsir = calloc(len / n +  len % n + 1, sizeof(char));
	strcpy(s[n-1].subsir, sir_codificat + i * (len / n));
	for(k = 0; k < strlen(s[n-1].subsir); k++)
		suma += s[n-1].subsir[k];

	s[n-1].complexitate = suma / strlen(s[n-1].subsir);
	qsort(s, n, sizeof(STRUCTURA), comparare);
	for (i= 0; i < n; i++)
	{
		if(i % 2 == 0)
		{
			printf("%s", s[i / 2].subsir);
		}
		else
		{
			printf("%s", s[n - 1 - i / 2].subsir);
		}
	}
	printf("\n");
	for(i = 0; i < n; i++)
	free(s[i].subsir);
	free(s);
	free(sir_codificat);
}

int main()
{
	sortare_sir();
	return 0;
}