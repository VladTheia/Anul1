#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *my_replace(char *s, char *s1, char *s2)
{
    char *aux = malloc(100);
    strncpy(aux, s, strlen(s) - strlen(strstr(s, s1)));
    strcat(aux, s2);
    strcat(aux, strstr(s, s1) + strlen(s1));
    strcpy(s, aux);
}

int main()
{
    char *s1 = malloc(10);
    char *s2 = malloc(10);
    char *s = malloc(100);

    FILE *f;
    f = fopen("inp", "r");
    fgets(s, 100, f);
    fscanf(f, "%s%s", s1, s2);
    fclose(f);

    my_replace(s, s1, s2);

    f = fopen("out", "w");
    fprintf(f, "%s", s);
    fclose(f);

    return 0;
}