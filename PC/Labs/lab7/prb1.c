#include <stdio.h>

void swap(int *pa, int *pb)
{
    int x;
    x = *pa;
    *pa = *pb;
    *pb = x;

}

int main()
{
    int a, b;
 
    FILE *f;
    f = fopen("inp1", "r");
    fscanf(f, "%d%d", &a, &b);
    fclose(f);

    swap(&a, &b);

    FILE *f2;
    f2 = fopen("out1", "w");
    fprintf(f2, "%d %d\n", a, b);
    fclose(f2);

    return 0;
}