#include <stdio.h>
#include <string.h>
#include "validations.h"

#define MAX_STR 100
#define MAX_LENGH 100
#define MIN_NSTR 2
#define MIN_LSTR 2

//Сортування за спаданням
void sortDesc(char **mass, int num) {
    for (int i = 0; i < num - 1; i++) {
        for (int j = i + 1; j < num; j++) {
            if (strcmp(mass[i], mass[j]) < 0) {
                char *tmp = mass[i];
                mass[i] = mass[j];
                mass[j] = tmp;
            }
        }
    }
}

void clearInputBuffer() {
    while (getchar() != '\n');
}

int main() {
    int n_str, str_size, valid, choise;

    do {
        //Ввід кількості рядків
        do {
            inputInt("Введіть кількість рядків (2–100): ", &n_str);
            valid = isPositiveInt(n_str) && (n_str >= MIN_NSTR && n_str <= MAX_STR);
            if (!valid)
                printf("Помилка! Рядків має бути від 2 до 100.\n");
        } while (!valid);

        //Ввід розміру рядка
        do {
            inputInt("Введіть розмір рядка (1–100): ", &str_size);
            valid = isPositiveInt(str_size) && (MIN_LSTR >= 1 && str_size <= MAX_LENGH);
            if (!valid)
                printf("Помилка! Розмір рядка має бути від 1 до 100.\n");
        } while (!valid);

        char list[n_str][str_size + 2];
        char *addr[n_str];

        for (int i = 0; i < n_str; i++) {
            int valid_input = 0;

            do {
                printf("\nВведіть рядок %d (макс %d символів): ", i + 1, str_size);

                if (fgets(list[i], str_size + 2, stdin) == NULL) {
                    printf("Помилка введення! Спробуйте ще раз.\n");
                    clearInputBuffer();
                    continue; 
                }

                // Якщо рядок занадто довгий 
                if (strchr(list[i], '\n') == NULL) {
                    printf("Рядок занадто довгий (макс %d символів). Спробуйте ще раз.\n", str_size);
                    clearInputBuffer();
                    valid_input = 0;
                } else {
                    list[i][strcspn(list[i], "\n")] = '\0';
                    addr[i] = list[i];
                    valid_input = 1; 
                }

            } while (valid_input == 0);
        }


        //Вивід до сортування
        printf("\nДо сортування:\n");
        for (int i = 0; i < n_str; i++) {
            printf("%s\n", addr[i]);
        }

        //Сортування
        sortDesc(addr, n_str);

        //Вивід після сортування
        printf("\nПісля сортування за спаданням:\n");
        for (int i = 0; i < n_str; i++) {
            printf("%s\n", addr[i]);
        }

        //Повторення
        inputInt("\nБажаєте повторити? (1 = так, 0 = ні): ", &choise);

    } while (choise == 1);

    return 0;
}
