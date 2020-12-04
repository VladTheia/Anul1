#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *f;
    f = fopen("inp", "r");
    int n;
    char *aux = malloc(100);
    fscanf(f, "%d", &n);
    char *v[n] = calloc(n * 100, sizeof(char));
    for (int i = 0; i < n; i++)
        fscanf(f, "%s", v[i]);
    
    int k = 0;
    char *unique[n] = calloc(n * 100, sizeof(char));
    int *count = calloc(n, sizeof(int));
    strcpy(unique[k], v[0]);
    count[k]++;
    k++;
    int ok = 0;
    for(int h = 0; h < k; h++)
        for (int j = 1; j < n; j++) {
            if (strcmp(v[i], unique[h]) == 0) {
                count[h]++;
                ok++;
            }
        }
}