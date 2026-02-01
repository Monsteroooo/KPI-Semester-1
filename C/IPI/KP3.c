
#include <stdio.h>
#include <math.h>
#include "validations.h"


int main() {
    float x, k, e, y0, S;
    int i, chooise = 1;

    do {

        
        // Введення k
        if (!inputFloat("Введіть k відмінне від нуля: ", &k)) return 0;
        if(k == 0){
            printf("Помилка: k не може бути нулем.\n");
            continue;
        } 
        
        // Якщо k > 0
       int valid_x = 0;
    do {
    valid_x = 1; 

    if (isPositiveFloat(k) == 1) {
        if (fmod(k, 2) == 0) {
            // парне k > 0
            inputFloat("Введіть x (x >= 0): ", &x);
            if (isNonNegativeFloat(x) == 0) {
                printf("Помилка: x має бути не від'ємним числом при k > 0 парне.\n");
                valid_x = 0;
            }
        } else {
            // непарне k > 0
            inputFloat("Введіть x (будь-яке дійсне число): ", &x);
        }
    } else {
        if (fmod(k, 2) == 0) {
            // парне k < 0
            inputFloat("Введіть x (x > 0): ", &x);
            if (isPositiveFloat(x) == 0) {
                printf("Помилка: x має бути додатнім числом при k < 0 парне.\n");
                valid_x = 0;
            }
        } else {
            // непарне k < 0
            inputFloat("Введіть x (будь-яке дійсне число окрім нуля): ", &x);
            if (x == 0) {
                printf("Помилка: x не може бути нулем при k < 0 непарне.\n");
                valid_x = 0;
            }
        }
    }

    } while (!valid_x);

        int valid = 1;
        do{
        if (!inputFloat("Введіть e (e > 0): ", &e)) return 1;
        if(!isPositiveFloat(e)){
            printf("е має бути додатнім \n");
            valid = 0;
        }else{
            valid = 1;
        }
        }while(valid == 0);

        y0 = 1;
        S = 1;
        i = 1;

        int max_iter = 1000;

        
        if (k > 0 && k < 1) {
            y0 = pow(x, 1.0 / k);
        }
        else if (k < 0) {
            y0 = 1.0 / pow(x, 1.0 / fabs(k));
        }
        else {
            while (fabs(S) > e && i < max_iter) {
                S = 1.0 / k * (x / pow(y0, k - 1) - y0);
                y0 = y0 + S;
                i++;
            }
        }


        if (i >= max_iter) {
            printf("Досягнуто максимум ітерацій. Рішення може бути неточним.\n");
        }

        // Вивід результатів
        printf("\nПочаткові дані:\n");
        printf("X = %f\n", x);
        printf("k = %f\n", k);
        printf("e = %f\n", e);

        printf("\nРезультати:\n");
        printf("Корінь рівняння: %f\n", y0);
        // printf("Кількість ітерацій: %d\n", i);
        // printf("Дельта: %f\n", fabs(S));

        printf("\nБажаєте виконати обчислення ще раз? (1/0): ");
        scanf("%d", &chooise);
        if (chooise != 1 && chooise != 0) {
            chooise = 0;
        }
        while (getchar() != '\n');

    } while (chooise == 1);

    return 0;
}