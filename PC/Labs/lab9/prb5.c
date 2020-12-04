#include <stdio.h>

typedef struct {
    int Re;
    int Im;
} complex;

complex adunare(complex a, complex b)
{
    complex z;
    z.Re = a.Re + b.Re;
    z.Im = a.Im + b.Im;

    return z;
}

complex inmultire(complex a, complex b)
{
    complex z;
    z.Re = a.Re * b.Re - a.Im * b.Im;
    z.Im = a.Re * b.Im + b.Re * a.Im;

    return z;
}

complex inmul_coef(float c, complex a)
{
    complex z;
    z.Re = c * a.Re;
    z.Im = c* a.Im;

    return z;
}

complex putere(complex a, int putere)
{
    complex z = a;
    
    if (putere == 0) {
        z.Re = 1;
        z.Im = 0;
        return z;
    }
    
    for (int i = 1; i < putere; i++)
        z = inmultire(z, a);

    return z;
}

void scrie(complex a)
{
    printf("(%d, %d)\n", a.Re, a.Im);
}

int main()
{
    complex z;
    printf("Partea reala: ");
    scanf("%d", &z.Re);
    printf("Partea Imaginara: ");
    scanf("%d", &z.Im);
    int grad;
    printf("Gradul polinomolui: ");
    scanf("%d", &grad);
    int c[grad + 1];
    printf("Coeficientii: ");
    for (int i = 0; i <= grad; i++)
        scanf("%d", &c[i]);

    complex p;
    p.Re = 0;
    p.Im = 0;

    for(int i = 0; i <= grad; i++)
        p = adunare( p, inmul_coef( c[i], putere(z, i) ) );

    scrie(p);
    
    return 0;
}