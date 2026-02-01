#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 6

// Заповнення матриці дійсними випадковими числами (float)
void matr_in(float arr[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // (float)rand() / RAND_MAX дає число від 0.0 до 1.0
            // Множимо на 18.0 і віднімаємо 9.0, щоб отримати діапазон [-9.0, 9.0]
            arr[i][j] = ((float)rand() / RAND_MAX) * 18.0 - 9.0;
        }
    }
}

void print_matrix(float arr[SIZE][SIZE]) {
    printf("Початкова матриця:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%6.2f ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Функція обходу спіраллю з центру
void spiral_print(float arr[SIZE][SIZE]) {
    printf("Обхід спіраллю (з центру):\n");

    // Стартова точка для 6x6, щоб спіраль йшла правильно:
    // Рядок 3, стовпець 2
    int r = 3;
    int c = 2;
    
    // Виводимо центральний елемент
    printf("%6.2f ", arr[r][c]);
    
    int elements_count = 1; // Лічильник виведених елементів
    int step = 1;           // Довжина кроку (1, 1, 2, 2, 3, 3...)
    int direction = 0;      // 0-Вправо, 1-Вгору, 2-Вліво, 3-Вниз

    while (elements_count < SIZE * SIZE) {
        // Виконуємо рух у поточному напрямку 'step' разів
        for (int i = 0; i < step; i++) {
            switch (direction) {
                case 0: c++; break; // Вправо
                case 1: r--; break; // Вгору
                case 2: c--; break; // Вліво
                case 3: r++; break; // Вниз
            }

            // Перевірка меж масиву перед виводом
            if (r >= 0 && r < SIZE && c >= 0 && c < SIZE) {
                printf("%6.2f ", arr[r][c]);
                elements_count++;
            }
        }

        // Зміна напрямку: 0->1->2->3->0...
        direction = (direction + 1) % 4;

        // Збільшуємо довжину кроку кожні 2 зміни напрямку (після Вгору і після Вниз)
        if (direction == 2 || direction == 0) {
            step++;
        }
    }
    printf("\n");
}

int main() {
    float arr[SIZE][SIZE];

    // Ініціалізація генератора випадкових чисел
    srand(time(NULL));

    // 1. Опис та ініціювання
    matr_in(arr);

    print_matrix(arr);

    // 2. Обхід масиву згідно з варіантом
    spiral_print(arr);

    return 0;
}