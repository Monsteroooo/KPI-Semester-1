#include <math.h>
#include <stdio.h>

float areaCalculation(float a, float l);


int main() {
    float a, l, S, S0;
    int n;

    printf("Введіть основу рівнобедреного трикутника a: ");
    scanf("%f", &a);
    printf("Введіть бічну сторону рівнобедреного трикутника l: ");
    scanf("%f", &l);
    printf("Введіть кількість граней n: ");
    scanf("%d", &n);
    S0 = areaCalculation(a, l);
    printf("Площа трикутника: %f\n", S0);
    S = S0 * n;
    printf("Площа бічної поверхні n-кутної піраміди: %f\n", S);
}

float areaCalculation(float a, float l) {
    float x = a / 4 * sqrt(4 * l * l - a * a);
    return x;
}