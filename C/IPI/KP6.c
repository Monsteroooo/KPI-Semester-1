#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "validations.h"

// Перевірка діагонального домінування
int isDiagonallyDominant(float **a, int n) {
    for (int i = 0; i < n; i++) {
        float sum = 0;
        for (int j = 0; j < n; j++) {
            if (i != j)
                sum += fabs(a[i][j]);
        }
        if (fabs(a[i][i]) <= sum)
            return 0;
    }
    return 1;
}

// Розв’язання СЛАР методом Якобі
int solveSLAE(float **a, float *b, float *x, int n, double eps) {
    float *prev = calloc(n, sizeof(float));
    if (prev == NULL) {
        printf("Помилка виділення пам’яті!\n");
        return 0;
    }

    // Початкове наближення xp[i] = b[i] / a[i][i]
    for (int i = 0; i < n; i++) {
        prev[i] = b[i] / a[i][i];
    }

    int iter = 0, maxIter = 1000;
    double diff;

    do {
        diff = 0;

        // Обчислення нового вектора x
        for (int i = 0; i < n; i++) {
            float sum = b[i];
            for (int j = 0; j < n; j++) {
                if (i != j)
                    sum -= a[i][j] * prev[j];
            }
            x[i] = sum / a[i][i];
        }

        // Обчислення різниці
        for (int i = 0; i < n; i++) {
            diff += fabs(x[i] - prev[i]);
            prev[i] = x[i];
        }

        iter++;

    } while (diff > eps && iter < maxIter);

    printf("\nРозв’язок знайдено за %d ітерацій\n", iter);

    for (int i = 0; i < n; i++) {
        printf("x[%d] = %.6f\n", i + 1, x[i]);
    }

    if (iter >= maxIter) {
        printf("УВАГА: досягнуто максимум ітерацій, можлива розбіжність!\n");
    }

    free(prev);
    return 1;
}

int main() {
    int n, solved;
    double eps;
    int choice = 1;
    int valid;

    do {
        // Введення кількості рівнянь
        do {
            valid = inputInt("Введіть кількість рівнянь та змінних(1–10): ", &n);
            if (!valid || n < 1 || n > 10) {
                printf("Помилка: введіть число від 1 до 10!\n");
                valid = 0;
            }
        } while (!valid);

        // Введення точності
        do {
            valid = inputDouble("Введіть точність epsilon (> 0): ", &eps);
            if (!valid || !isPositiveDouble(eps)) {
                printf("Помилка: введіть додатне дійсне число!\n");
                valid = 0;
            }
        } while (!valid);

        // Виділення пам’яті
        float **slar = malloc(n * sizeof(float *));
        float *b = malloc(n * sizeof(float));
        float *x = calloc(n, sizeof(float));

        if (!slar || !b || !x) {
            printf("Помилка виділення пам’яті!\n");
            free(slar);
            free(b);
            free(x);
            continue;
        }

        for (int i = 0; i < n; i++) {
            slar[i] = calloc(n, sizeof(float)); 
        }

        // Введення коефіцієнтів n×n
        int validSystem = 0;
        do {
            printf("\nВведіть коефіцієнти системи (%d рівнянь):\n", n);

            for (int i = 0; i < n; i++) {
                printf("Рівняння %d:\n", i + 1);

                for (int j = 0; j < n; j++) {
                    printf("  Коефіцієнт при x%d: ", j + 1);
                    inputFloat("", &slar[i][j]);
                }

                printf("  Вільний член b%d: ", i + 1);
                inputFloat("", &b[i]);
            }

            // Вивід системи
            printf("\nВаша система рівнянь:\n");
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    printf("%6.2f ", slar[i][j]);
                }
                printf("| %6.2f\n", b[i]);
            }

            // Перевірка діагональної домінантності
            if (!isDiagonallyDominant(slar, n)) {
                printf("\nПомилка: система не є діагонально домінантною.\n");
                printf("Введіть коефіцієнти ще раз.\n");
            } else {
                validSystem = 1;
            }

        } while (!validSystem);

        // Обчислення
        do {
            solved = solveSLAE(slar, b, x, n, eps);
        } while (solved == 0);

        // Звільнення пам’яті
        for (int i = 0; i < n; i++)
        free(slar[i]);
        free(slar);
        free(b);
        free(x);

        inputInt("\nБажаєте повторити? (1 - так, 0 - ні): ", &choice);
        printf("\n");

    } while (choice == 1);

    return 0;
}
