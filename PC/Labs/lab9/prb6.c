#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *cuv;
    int n;
} elem;

int main()
{
    elem v[100];
    for (int h = 0; h < 100; h++)
        v[h].cuv = malloc(100 * sizeof(char));
    int i = 0;
    FILE *f;
    f = fopen("inp", "r");
    fscanf(f, "%s", v[i].cuv);
    v[i].n = 1;
    i++;
  
    char *aux = malloc(100 * sizeof(char));
    int unic;
    while (fscanf(f, "%s", aux) != EOF) {
        unic = 0;
        for (int j = 0; j < i; j++)
            if (strcmp(aux,v[j].cuv) == 0) {
                (v[j].n)++;
                unic++;
            }
        if (unic == 0) {
            strcpy(v[i].cuv, aux);
            v[i].n = 1;
            i++;
        }
    }
    fclose(f);
    free(aux);

    for (int k = 0; k < i; k++)
        printf("%s %d\n", v[k].cuv, v[k].n);

    return 0;
}