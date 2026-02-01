#include <stdio.h>
#include <math.h>
#include <conio.h>

int main() {
    float a, b, c, P, S, ha, hb, hc, ma, mb, mc, Ba, Bb, Bc, p;
    int choice;

    do {
        // Ввід користувача + перевірка на символи + перевірка на додатність
        printf("Введіть довжину сторони a:\n ");
        if (scanf("%f", &a) != 1) {
            printf("a - має бути числом цілим або з крапкою! Спробуйте ще раз.\n");
            while (getchar() != '\n');
        } else if (a <= 0) {
            printf("a - має бути додатнім і не нульовим. Спробуйте ще раз.\n");
        } else {
            printf("Введіть довжину сторони b:\n ");
            if (scanf("%f", &b) != 1) {
                printf("b - має бути числом цілим або з крапкою! Спробуйте ще раз.\n");
                while (getchar() != '\n');
            } else if (b <= 0) {
                printf("b - має бути додатнім і не нульовим. Спробуйте ще раз.\n");
            } else {
                printf("Введіть довжину сторони c:\n ");
                if (scanf("%f", &c) != 1) {
                    printf("c - має бути числом цілим або з крапкою! Спробуйте ще раз.\n");
                    while (getchar() != '\n');
                } else if (c <= 0) {
                    printf("c - має бути додатнім і не нульовим. Спробуйте ще раз.\n");
                } else if (a + b <= c || a + c <= b || b + c <= a) {
                    printf("Трикутник з такими сторонами не існує.\n");
                } else {
                    // Розрахунки
                    P = a + b + c;
                    p = P / 2;
                    S = sqrt(p * (p - a) * (p - b) * (p - c));
                    ha = (2 * S) / a;
                    hb = (2 * S) / b;
                    hc = (2 * S) / c;
                    ma = 0.5 * sqrt(2 * b * b + 2 * c * c - a * a);
                    mb = 0.5 * sqrt(2 * a * a + 2 * c * c - b * b);
                    mc = 0.5 * sqrt(2 * a * a + 2 * b * b - c * c);
                    Ba = (2 * sqrt(b * c * p * (p - a))) / (b + c);
                    Bb = (2 * sqrt(a * c * p * (p - b))) / (a + c);
                    Bc = (2 * sqrt(a * b * p * (p - c))) / (a + b);

                    // Вивід результатів
                    printf("Площа = %.3f\n", S);
                    printf("Периметр = %.3f\n", P);
                    printf("Висота проведена до а = %.3f\n", ha);
                    printf("Висота проведена до b = %.3f\n", hb);
                    printf("Висота проведена до c = %.3f\n", hc);
                    printf("Медіана проведена до a = %.3f\n", ma);
                    printf("Медіана проведена до b = %.3f\n", mb);
                    printf("Медіана проведена до c = %.3f\n", mc);
                    printf("Бісектриса проведена до a = %.3f\n", Ba);
                    printf("Бісектриса проведена до b = %.3f\n", Bb);
                    printf("Бісектриса проведена до c = %.3f\n", Bc);
                }
            }
        }
        printf("Бажаєте виконати ще один розрахунок? (1/0): ");
        choice = getch();
        printf("\n");
    } while (choice == '1');

    return 0;
}

// Додати перевірку на експоненціальні числа
// Додати перевірку на числа через кому