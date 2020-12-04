#include <stdio.h>
#include <stdlib.h>

void count(int n, int *v, int *zero, int *poz, int *neg)
{
    for (int i = 0; i < n; i++) {
        if(v[i] < 0)
            (*neg)++;
        if(*(v + i) == 0)
            (*zero)++;
        if(*(v + i) > 0)
            (*poz)++;
    }
}

int main()
{
    int n, zero = 0, poz = 0, neg = 0;

    FILE *f;
    f = fopen("inp", "r");
    fscanf(f, "%d", &n);
    int *v; 
    v = (int*)malloc(n);
    for(int i = 0; i < n; i++)
        fscanf(f, "%d", (v + i));
    fclose(f);

    count(n, v, &zero, &poz, &neg);

    f = fopen("out", "w");
    fprintf(f, "nule: %d\n", zero);
    fprintf(f, "pozitive: %d\n", poz);
    fprintf(f, "negative: %d\n", neg);
    fclose(f);
}