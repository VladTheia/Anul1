#include <stdio.h>

char *strdel(char *p, int n); //sterge n caratere din pozitia n
{
    strcpy(p + n, NULL);

    return p;
}

char *strins(char *p, char *s)
{
    char v[strlen(p) + strlen(s)];
    strcpy(v, p);
    strcat(v, s);
    strcpy(p, v);

    return p;
}

int main()
{
    char *text = malloc(3000);
    char *a = malloc(20);
    char *b = malloc(20);
    FILE *f;
    f =fopen("inp", "r");
    fgets(text, 3000, f);
    fgets(a, 20, f);
    fgets(b, 20, f);
    fclose(f);

    

    return 0;
}