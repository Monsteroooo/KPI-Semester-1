
#include <stdio.h>

#define MAS_LEN 8


void arr_1(char arr[], int length);
void arr_2(char arr[], int length);
void arr_3(char arr1[], char arr2[], char arr3[], int length);
int find_first_smaller(char arr[], int length, char symbol);

int main() {
    char arr1[MAS_LEN], arr2[MAS_LEN], arr3[MAS_LEN];
    char input;
    int index, choise;
    do{
    arr_1(arr1, MAS_LEN);
    arr_2(arr2, MAS_LEN);
    arr_3(arr1, arr2, arr3, MAS_LEN);

    printf("Масив arr3:\n");
    for (int i = 0; i < MAS_LEN; i++) {
        printf("%d -> %c\n", (int)arr3[i], arr3[i]);
    }
    
    printf("\nВведіть один символ: ");
    scanf(" %c", &input);

    // Пошук першого символу, меншого за введений
    index = find_first_smaller(arr3, MAS_LEN, input);

    if (index != -1) {
        printf("\nПерше входження символу, меншого за '%c': '%c' (код %d), індекс %d\n",
               input, arr3[index], arr3[index], index + 1);
    } else {
        printf("\nУ масиві немає символів, менших за '%c'\n", input);
    }
    
    printf("\nЯкщо бажаєте повторити, натисніть 1: ");
    scanf("%d", &choise);
    }while(choise == 1);
    return 0;
}

void arr_1(char arr[], int length) {
    for (int i = 0; i < length; i++) {
        arr[i] = i * i + 76;
    }
}

void arr_2(char arr[], int length) {
    for (int i = 0; i < length; i++) {
        arr[i] = 85 - i;
    }
}

void arr_3(char arr1[], char arr2[], char arr3[], int length) {
    int k = 0; 
    for (int i = 0; i < length; i++) {
        int code1 = arr1[i];
        int code2 = arr2[i];

        if (code1 % 5 == 0 && k < length) {
            arr3[k] = arr1[i];
            k++;
        }
        if (code2 % 5 == 0 && k < length) {
            arr3[k] = arr2[i];
            k++;
        }
    }

    for (int i = k; i < length; i++) {
        arr3[i] = ' ';
    }
}

int find_first_smaller(char arr[], int length, char symbol) {
    for (int i = 0; i < length; i++) {
        if (arr[i] < symbol) {
            return i; 
        }
    }
    return -1; 
}