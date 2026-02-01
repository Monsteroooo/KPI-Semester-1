#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 300

const int FILE_SIGNATURE = 99887766;

typedef struct {
    char name[50];  
    float area;    
    int population; 
} record;

int inputInt(const char *msg, int *value) {
    char buf[MAX_LEN];
    char *end;

    for (int attempts = 0; attempts < 99; attempts++) {
        printf("%s", msg);

        if (!fgets(buf, sizeof(buf), stdin))
            return 0; // помилка читання

        *value = strtol(buf, &end, 10);

        // перевіряємо, що щось зчитано і немає зайвих символів
        if (end != buf && *end == '\n') {
            return 1; // успішно
        }

        printf("Помилка: введіть правильне ціле число\n");
    }
    printf("Забагато помилок!");
    return 0; // після 10 невдалих спроб
}

int inputFloat(const char *msg, float *value) {
    char buf[MAX_LEN];
    char *end;

    for (int attempts = 0; attempts < 99; attempts++) {
        printf("%s", msg);

        if (!fgets(buf, sizeof(buf), stdin))
            return 0;

        
        for (int i = 0; buf[i]; i++) {
            if (buf[i] == ',') buf[i] = '.';
        }

        *value = strtof(buf, &end);

        if (end != buf && *end == '\n') {
            return 1;
        }

        printf("Помилка: введіть правильне число до 6 символів після коми.\n");
    }
    printf("Забагато помилок!");
    return 0;
}

//Запитує ім'я файлу
void askFileName(char *buffer) {
    printf("Enter file name (example data): ");

    if (fgets(buffer, 100, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        } else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    } else {
        buffer[0] = '\0';
    }
}

//Функція перевірки чи є файл коректним
int isValidDataFile(char *filename) {
    FILE *f = fopen(filename, "rb");
    if (f == NULL) return 0;

    int sigCheck;
    if (fread(&sigCheck, sizeof(int), 1, f) != 1) {
        fclose(f);
        return 0; 
    }

    if (sigCheck != FILE_SIGNATURE) {
        fclose(f);
        return 0; 
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    long dataSize = size - sizeof(int); 

    fclose(f);

    if (dataSize % sizeof(record) != 0) return 0; 

    return 1;
}

//Виведення даних файлу на екран
void printFileContent(char *filename) {
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        printf("Error during opening file.\n");
        return;
    }

    fseek(f, 0, SEEK_END);
    if (ftell(f) == 0) {
        printf("File is empty!\n");
        fclose(f);
        return;
    }
    fseek(f, sizeof(int), SEEK_SET); // Пропускаємо сигнатуру

    record temp;
    int i = 1;
    
    printf("\n%-4s %-20s %-15s %-15s\n", "№", "Name", "Square (km^2)", "Population");
    printf("----------------------------------------------------------\n");
    
    while (fread(&temp, sizeof(record), 1, f) == 1) {
        printf("%-4d %-20s %-15.5f %-15d\n", i++, temp.name, temp.area, temp.population);
    }
    printf("----------------------------------------------------------\n");
    fclose(f);
}

//Запитати користувача, чи вивести дані
void askAndPrint(char *filename) {
    int choice;
    if (inputInt("\nDisplay file contents on screen? (1-Yes, 0-No): ", &choice)) {
        if (choice == 1) {
            printFileContent(filename);
        }
    }
}

//Сортування записів
void sortFile(char *filename) {
    FILE *f = fopen(filename, "r+b"); 
    if (f == NULL) {
        printf("Unable to open file for sorting\n");
        return;
    }

    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);
    
    if (fileSize < sizeof(int)) {
        printf("The file is corrupted or empty..\n");
        fclose(f);
        return;
    }
    
    int count = (fileSize - sizeof(int)) / sizeof(record);
    
    if (count < 2) {
        printf("There are not enough records in the file (found: %d).\n", count);
        fclose(f);
        return;
    }

    int sortType = 0;
    int valid = 0;
    do {
        printf("\nSelect the field for sorting:\n");
        printf("1 - By name\n");
        printf("2 - By area\n");
        printf("3 - By population\n");
        if (inputInt("Your choice: ", &sortType) && sortType >= 1 && sortType <= 3) {
            valid = 1;
        } else {
            printf("Error: select 1, 2 or 3.\n");
        }
    } while (!valid);

    int sortOrder = 0;
    valid = 0;
    do {
        printf("\nSelect the sorting order:\n");
        printf("1 - By growth\n");
        printf("2 - By decline\n");
        if (inputInt("Your choice: ", &sortOrder) && sortOrder >= 1 && sortOrder <= 2) {
            valid = 1;
        } else {
            printf("Error: select 1 or 2.\n");
        }
    } while (!valid);

    printf("Sorting...\n");

    record rec1, rec2;
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            
            long offset = sizeof(int) + (j * sizeof(record));
            
            fseek(f, offset, SEEK_SET);
            fread(&rec1, sizeof(record), 1, f); 
            fread(&rec2, sizeof(record), 1, f);

            int needSwap = 0;

            if (sortType == 1) { 
                int cmp = strcmp(rec1.name, rec2.name);
                if (sortOrder == 1 && cmp > 0) needSwap = 1; 
                if (sortOrder == 2 && cmp < 0) needSwap = 1; 
            } 
            else if (sortType == 2) { 
                if (sortOrder == 1 && rec1.area > rec2.area) needSwap = 1;
                if (sortOrder == 2 && rec1.area < rec2.area) needSwap = 1;
            } 
            else if (sortType == 3) {
                if (sortOrder == 1 && rec1.population > rec2.population) needSwap = 1;
                if (sortOrder == 2 && rec1.population < rec2.population) needSwap = 1;
            }

            if (needSwap == 1) {
                fseek(f, offset, SEEK_SET); 
                fwrite(&rec2, sizeof(record), 1, f); 
                fwrite(&rec1, sizeof(record), 1, f); 
            }
        }
    }

    printf("The file has been successfully sorted!\n");
    fclose(f);
}

int updateFileSelection(char *currentFile) {
    int change = 1; 

    if (strlen(currentFile) > 0) {
        printf("\n----------------------------------\n");
        printf("Current file: [%s]\n", currentFile);
        inputInt("Work with it (0) or choose another (1)? : ", &change);
    }

    if (change == 1) {
        char tempName[100];
        askFileName(tempName); 

        if (isValidDataFile(tempName)) {
            strcpy(currentFile, tempName);
            printf("File '%s' chosed.\n", currentFile);
            return 1;
        } else {
            printf("Error: File not found or corrupted.\n");
            return 0;
        }
    }
    return 1; 
}

int main() {
    int main_choice = 0;
    int sub_choice = 0;
    int valid_input = 0;
    int main_run = 1; 
    
    FILE *file;
    char currentFile[100] = ""; 

    do {
        printf("\n=== MAIN MENU ===\n");
        printf("1 - File Operations\n");
        printf("2 - Record Operations\n");
        printf("3 - Exit\n");
        
        do {
            valid_input = inputInt("Your choice: ", &main_choice);
            if (main_choice < 1 || main_choice > 3) valid_input = 0;
        } while (valid_input == 0);

        if (main_choice == 1) {
            int sub_run = 1; 
            do {
                printf("\n--- File Menu ---\n");
                printf("1 - Create New\n");
                printf("2 - Read Existing\n");
                printf("3 - Delete File\n");
                printf("4 - Back\n");

                do {
                    valid_input = inputInt("Your choice: ", &sub_choice);
                    if (sub_choice < 1 || sub_choice > 4) valid_input = 0;
                } while (valid_input == 0);

                if (sub_choice == 1) {
                    askFileName(currentFile);
                    FILE *checkFile = fopen(currentFile, "rb");
                    int allowCreate = 1; 

                    if (checkFile != NULL) {
                        fclose(checkFile);
                        printf("\nWARNING: File already exists!\n");
                        int overwrite = 0;
                        inputInt("Overwrite? (1-Yes, 0-No): ", &overwrite);
                        if (overwrite != 1) allowCreate = 0;
                    }

                    if (allowCreate == 1) {
                        file = fopen(currentFile, "wb"); 
                        if (file == NULL) {
                            printf("Creation error.\n");
                        } else {
                            fwrite(&FILE_SIGNATURE, sizeof(int), 1, file);
                            printf("File created.\n");
                            fclose(file);
                            askAndPrint(currentFile); 
                        }
                    } 
                } else if (sub_choice == 2) {
                   askFileName(currentFile);
                     if (isValidDataFile(currentFile)) {
                        printf("File is valid.\n");
                        askAndPrint(currentFile);
                    } else {
                        printf("File is invalid.\n");
                        currentFile[0] = '\0';
                    }
                }else if (sub_choice == 3) {
                    askFileName(currentFile);
                    if (remove(currentFile) == 0) printf("File deleted.\n");
                    else printf("Deletion error.\n");
                }else if (sub_choice == 4) {
                    sub_run = 0;
                }
            } while (sub_run == 1); 
        } 
        
        else if (main_choice == 2) {
            int sub_run = 1;
            do {
                printf("\n--- Records Menu ---\n");
                printf("1 - Add Record\n");
                printf("2 - Sort Records\n");
                printf("3 - Insert into Sorted\n");
                printf("4 - Delete Record (by name)\n"); 
                printf("5 - Back\n");

                do {
                    valid_input = inputInt("Your choice: ", &sub_choice);
                    if (sub_choice < 1 || sub_choice > 5) valid_input = 0;
                } while (valid_input == 0);

                if (sub_choice == 1) {
                    if (updateFileSelection(currentFile)) {
                        file = fopen(currentFile, "ab"); 
                        if (file == NULL) {
                            printf("Error opening file.\n");
                        } else {
                            record newRec;
                            
                            do {
                                printf("Enter name: ");
                                if (fgets(newRec.name, sizeof(newRec.name), stdin) == NULL) {
                                    valid_input = 0;
                                } else {
                                    newRec.name[strcspn(newRec.name, "\n")] = 0;
                                    if (strlen(newRec.name) == 0) valid_input = 0;
                                    else valid_input = 1;
                                }
                            } while (valid_input == 0);

                    
                            do {
                                valid_input = inputFloat("Enter area (sq. km): ", &newRec.area);
                                if (valid_input == 1) {
                                    if (newRec.area < 0.00001) {
                                        printf("Error: Area must be strictly greater than 0.\n");
                                        valid_input = 0;
                                    }
                                }
                            } while (valid_input == 0);

                     
                            do {
                                valid_input = inputInt("Enter population: ", &newRec.population);
                                if (valid_input == 1) {
                                    if (newRec.population <= 0) {
                                        printf("Error: Population must be a positive number.\n");
                                        valid_input = 0;
                                    }
                                }
                            } while (valid_input == 0);

                            fwrite(&newRec, sizeof(record), 1, file);
                            fclose(file);
                            printf("Record added.\n");
                        }
                    }
                }else if (sub_choice == 2) {
                    if(updateFileSelection(currentFile)) {
                        sortFile(currentFile);
                        askAndPrint(currentFile);
                    }
                }else if (sub_choice == 3) {
                    if (updateFileSelection(currentFile)) {
                        record newRec;
                        
                        do {
                            printf("Enter name to insert: ");
                            fgets(newRec.name, sizeof(newRec.name), stdin);
                            newRec.name[strcspn(newRec.name, "\n")] = 0;
                            if (strlen(newRec.name) == 0) valid_input = 0;
                            else valid_input = 1;
                        } while (valid_input == 0);

             
                        do {
                            valid_input = inputFloat("Enter area (sq. km): ", &newRec.area);
                            if (valid_input == 1) {
                                if (newRec.area < 0.00001) {
                                    printf("Error: Area must be strictly greater than 0.\n");
                                    valid_input = 0;
                                }
                            }
                        } while (valid_input == 0);

             
                        do {
                            valid_input = inputInt("Enter population: ", &newRec.population);
                            if (valid_input == 1) {
                                if (newRec.population <= 0) {
                                    printf("Error: Population must be a positive number.\n");
                                    valid_input = 0;
                                }
                            }
                        } while (valid_input == 0);

                        // Insertion settings
                        int sortType = 0;
                        int sortOrder = 0;
                        int valid_sort = 0;

                        printf("\n--- INSERTION SETTINGS ---\n");
                        printf("Specify how the file is currently sorted.\n");
                        
                        do {
                            printf("\nCriterion:\n1 - By Name\n2 - By Area\n3 - By Population\n");
                            if (inputInt("Your choice: ", &sortType) && sortType >= 1 && sortType <= 3) {
                                valid_sort = 1;
                            } else printf("Choose 1-3.\n");
                        } while (!valid_sort);

                        valid_sort = 0;
                        do {
                            printf("\nOrder:\n1 - Ascending\n2 - Descending\n");
                            if (inputInt("Your choice: ", &sortOrder) && sortOrder >= 1 && sortOrder <= 2) {
                                valid_sort = 1;
                            } else printf("Choose 1 or 2.\n");
                        } while (!valid_sort);

                        FILE *f = fopen(currentFile, "rb");
                        FILE *temp = fopen("temp.bin", "wb"); 

                        if (f && temp) {
                            int sig;
                            if (fread(&sig, sizeof(int), 1, f) == 1) {
                                fwrite(&sig, sizeof(int), 1, temp);
                            } 

                            record curRec;
                            int inserted = 0;

                            while (fread(&curRec, sizeof(record), 1, f) == 1) {
                                int condition = 0;

                                if (inserted == 0) {
                                    if (sortType == 1) { // NAME
                                        int cmp = strcmp(newRec.name, curRec.name);
                                        if (sortOrder == 1 && cmp < 0) condition = 1;
                                        if (sortOrder == 2 && cmp > 0) condition = 1;
                                    } 
                                    else if (sortType == 2) { // AREA
                                        if (sortOrder == 1 && newRec.area < curRec.area) condition = 1;
                                        if (sortOrder == 2 && newRec.area > curRec.area) condition = 1;
                                    } 
                                    else if (sortType == 3) { // POPULATION
                                        if (sortOrder == 1 && newRec.population < curRec.population) condition = 1;
                                        if (sortOrder == 2 && newRec.population > curRec.population) condition = 1;
                                    }
                                }

                                if (condition == 1) {
                                    fwrite(&newRec, sizeof(record), 1, temp); 
                                    inserted = 1; 
                                }
                                
                                fwrite(&curRec, sizeof(record), 1, temp);
                            }

                            if (inserted == 0) {
                                fwrite(&newRec, sizeof(record), 1, temp);
                            }

                            fclose(f);
                            fclose(temp);
                            remove(currentFile);            
                            rename("temp.bin", currentFile); 
                            
                            printf("Record inserted.\n");
                            askAndPrint(currentFile);
                        } else {
                            if (f) fclose(f);
                            if (temp) fclose(temp);
                        }
                    }
                } 
                else if (sub_choice == 4) {
                    if (updateFileSelection(currentFile)) {
                        
                     
                        askAndPrint(currentFile);

                        char targetName[50];
                        printf("\nEnter region/city name to delete: ");
                        fgets(targetName, sizeof(targetName), stdin);
                        targetName[strcspn(targetName, "\n")] = 0; // Remove \n

                        FILE *f = fopen(currentFile, "rb");
                        FILE *temp = fopen("temp_del.bin", "wb");

                        if (f && temp) {
                            int sig;
                            if (fread(&sig, sizeof(int), 1, f) == 1) {
                                fwrite(&sig, sizeof(int), 1, temp);
                            }

                            record curRec;
                            int found = 0;

                            while (fread(&curRec, sizeof(record), 1, f) == 1) {
                                if (strcmp(curRec.name, targetName) != 0) {
                                    fwrite(&curRec, sizeof(record), 1, temp);
                                } else {
                                    found++; 
                                }
                            }

                            fclose(f);
                            fclose(temp);

                            if (found > 0) {
                                remove(currentFile); 
                                rename("temp_del.bin", currentFile); 
                                printf("Records deleted: %d\n", found);
                                askAndPrint(currentFile);
                            } else {
                                remove("temp_del.bin"); 
                                printf("Record with name '%s' not found.\n", targetName);
                            }
                        } else {
                            printf("File access error.\n");
                            if (f) fclose(f);
                            if (temp) fclose(temp);
                        }
                    }
                }
                else if (sub_choice == 5) sub_run = 0; 
            } while (sub_run == 1);
        }else if (main_choice == 3) {
            main_run = 0; 
        }
    } while (main_run == 1);

    return 0;
}