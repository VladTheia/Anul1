#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *substr(char *src, int n, char *dest)
{
    strncpy(dest, src, n);
}

int main()
{
    char *text = malloc(100);
    int a, b;

    FILE *f;
    f = fopen("inp", "r");
    fgets(text, 100, f);
    fscanf(f, "%d%d", &a, &b);
    fclose(f);

    char *dest = malloc(b);
    substr(text + a, b, dest);

    f = fopen("out", "w");
    fprintf(f, "%s", dest);
    fclose(f);

    return 0;
}