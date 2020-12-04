#include <stdio.h>

typedef struct {
    float x, y;
} Punct;

int main()
{
    Punct p;

    printf("Introduceti x: ");
    scanf("%f", &p.x);
    printf("Introduceti y: ");
    scanf("%f", &p.y);

    printf("(%.2f, %.2f)\n", p.x, p.y);

    return 0;
}