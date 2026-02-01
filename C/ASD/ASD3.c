#include <stdio.h>
#include <math.h>
#include <conio.h>

int main()
{
    float x, E, S, a;
    int n;

    x = 1;
    E = 0.0000000000000000001;
    a = 1.0;     // перший член ряду (a0)
    S = 1.0;     // початкова сума (S0)
    n = 1;

    while (a >= E) {
        a = a * (x * x) / ((2 * n - 1) * (2 * n)); // рекурентна формула
        S += a;
        n++;
    }

    printf("S = %f\n", S);
    printf("n = %d\n", n);

    return 0;
}
