#include <stdio.h>
#include <string.h>

#define BUFMAX 1005

int strcicmp(char const *a, char const *b)
{
    for (;; a++, b++) {
        int d = tolower(*a) - tolower(*b);
        if (d !=0 || !*a)
            return d;
    }
}

int main(int argc, char **argv)
{
    char buf[BUFMAX];
    int i = 0;
    int j = 0;
    FILE *f;
    f = fopen(argv[1], "r");
    while (fgets(buf,BUFMAX, f) != NULL) {
        i++; 
        if (strstr(buf, argv[2]) != NULL){
            printf("[%d] %s", i, buf);
            j++;
        }
    }
    fclose(f);
    printf("Numar total de linii: %d\n", j);

    return 0;
}