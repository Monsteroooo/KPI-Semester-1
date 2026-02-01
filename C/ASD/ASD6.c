#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 6

//Заповнення матриці випадковими числами
void matr_in(int arr[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            arr[i][j] = (rand() % 19) - 9; // діапазон [-9, 9]
        }
    }
}

//Вибір додатніх елементів головної діагоналі
int sort_dial(int arr[SIZE][SIZE], int res[SIZE]) {
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        if (arr[i][i] > 0) {
            res[count++] = arr[i][i];
        }
    }
    return count;
}

//Сортування Шелла (використаємо для побічної діагоналі)
void sort_shell(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

int main() {
    srand(time(NULL));

    int matrix[SIZE][SIZE];
    int diag_main[SIZE];
    int diag_side[SIZE];
    int count_main = 0;

    //Заповнення матриці
    matr_in(matrix);

    //Вивід матриці
    printf("Матриця:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }

    //Головна діагональ
    count_main = sort_dial(matrix, diag_main);

    printf("\nДодатні елементи головної діагоналі:\n");
    for (int i = 0; i < count_main; i++) {
        printf("%d ", diag_main[i]);
    }
    printf("\n");

    //Побічна діагональ
    for (int i = 0; i < SIZE; i++) {
        diag_side[i] = matrix[i][SIZE - 1 - i];
    }

    //Сортування побічної діагоналі за Шеллом
    sort_shell(diag_side, SIZE);

    printf("\nВідсортована побічна діагональ (Шелл):\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", diag_side[i]);
    }

    printf("\n");
    return 0;
}
