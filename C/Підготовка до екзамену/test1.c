#include <stdio.h>
#include <string.h>
#include "validations.h"

#define MAX_STR_LENGTH 40
#define MIN_STR_LENGTH 1
#define NUM_STRINGS 3

int main(){
    char mass [NUM_STRINGS][MAX_STR_LENGTH + 2]; // +2 для символу нового рядка та нульового символу
    char *addr[NUM_STRINGS];

    // Введення рядків
    for(int i = 0; i < NUM_STRINGS; i++){
        int valid_input = 0;
        do {
            printf("Введіть рядок %d (макс %d символів): ", i+1, MAX_STR_LENGTH);
            if(fgets(mass[i], MAX_STR_LENGTH + 2, stdin) == NULL){
                printf("Помилка введення! Спробуйте ще раз.\n");
                continue; 
            }else if(strlen(mass[i]) < MIN_STR_LENGTH || strlen(mass[i]) > MAX_STR_LENGTH){
                printf("Неправильна довжина рядка! Спробуйте ще раз.\n");
            }else if(mass[i][0] == '\n'){
                printf("Рядок не може бути порожнім! Спробуйте ще раз.\n");
            }else {
                valid_input = 1;
            }
        }while(valid_input == 0);
    }

     for (int i = 0; i < NUM_STRINGS; i++) {
        addr[i] = mass[i];
    }

     for (int i = 0; i < NUM_STRINGS - 1; i++) {
        for (int j = i + 1; j < NUM_STRINGS; j++) {
            if (strcmp(addr[i], addr[j]) > 0) {
                char *tmp = addr[i];
                addr[i] = addr[j];
                addr[j] = tmp;
            }
        }
    }

    printf("\nВідсортовані рядки:\n");
    for(int i = 0; i < NUM_STRINGS; i++){
        printf("%s", addr[i]);
    }
    return 0;
}