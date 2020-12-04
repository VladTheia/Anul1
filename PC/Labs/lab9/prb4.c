#include <stdio.h>
#include <stdlib.h>

int main()
{
    typedef struct {
        int *v;
        int cap;
        int n;
    } vector;
    vector vec;
    vec.v = malloc(100 * sizeof(int));
    for (int i = 0; i <= 100; i++) {
        vec.v[i] = i;
        for (int j = 0; j <= i; j++)
            printf("%d ", vec.v[j]);
        printf("\n");
    }

}