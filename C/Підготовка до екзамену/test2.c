#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validations.h" // Припускаємо, що inputInt тут

const int FILE_SIGNATURE = 99887766;

typedef struct{
    char name[50];
} record;

// Функція для очищення буфера після введення чисел
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(){
    int choice;
    char filename[100] = "datafile.bin";

    do{
        printf("\n--- Menu ---\n");
        printf("1. Create File (Reset)\n");
        printf("2. Add record\n");
        printf("3. Read records\n");
        printf("4. Exit\n");

        inputInt("Enter your choice: ", &choice);
        // Очищаємо буфер після введення числа!
        // Якщо inputInt цього не робить, розкоментуйте рядок нижче:
        // clearBuffer(); 

        if(choice == 1){
            printf("Creating file...\n");
            FILE *f = fopen(f, "w");
        } else if(choice == 2){

        } else if(choice == 3){
           
        } else if(choice == 4){
            printf("Exiting...\n");
            return 0;
        }
    } while(choice != 4);
}