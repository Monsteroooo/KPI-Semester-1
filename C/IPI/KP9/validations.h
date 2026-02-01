
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 200

// ВАЛІДАЦІЯ НА СИМВОЛИ 


int inputInt(const char *msg, int *value) {
    char buf[MAX_LEN];
    char *end;

    for (int attempts = 0; attempts < 10; attempts++) {
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

    for (int attempts = 0; attempts < 10; attempts++) {
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

int inputDouble(const char *msg, double *value) {
    char buf[MAX_LEN];
    char *end;

    for (int attempts = 0; attempts < 10; attempts++) {
        printf("%s", msg);

        if (!fgets(buf, sizeof(buf), stdin))
            return 0;

        
        for (int i = 0; buf[i]; i++) {
            if (buf[i] == ',') buf[i] = '.';
        }

        *value = strtod(buf, &end);

        if (end != buf && *end == '\n') {
            return 1;
        }

        printf("Помилка: введіть правильне число до 15 символів після коми.\n");
    }
    printf("Забагато помилок!");
    return 0;
}

int inputLongDouble(const char *msg, long double *value) {
    char buf[MAX_LEN];
    char *end;

    for (int attempts = 0; attempts < 10; attempts++) {
        printf("%s", msg);

        if (!fgets(buf, sizeof(buf), stdin))
            return 0;

      
        for (int i = 0; buf[i]; i++) {
            if (buf[i] == ',') buf[i] = '.';
        }

        *value = strtold(buf, &end);

        if (end != buf && *end == '\n') {
            return 1;
        }

        printf("Помилка: введіть правильне число (long double)\n");
    }
    printf("Забагато помилок!");
    return 0;
}

//  ВАЛІДАЦІЯ НА ДОДАТНІСТЬ


int isPositiveInt(int value) {
    return value > 0;
}


int isPositiveFloat(float value) {
    return value > 0.0f;
}


int isPositiveDouble(double value) {
    return value > 0.0;
}


int isPositiveLongDouble(long double value) {
    return value > 0.0L;
}

//  ВАЛІДАЦІЯ НА НЕВІД'ЄМНІСТЬ 


int isNonNegativeInt(int value) {
    return value >= 0;
}


int isNonNegativeFloat(float value) {
    return value >= 0.0f;
}


int isNonNegativeDouble(double value) {
    return value >= 0.0;
}


int isNonNegativeLongDouble(long double value) {
    return value >= 0.0L;
}
//  ВАЛІДАЦІЯ НА ВІД'ЄМНІСТЬ


int isNegativeInt(int value) {
    return value < 0;
}


int isNegativeFloat(float value) {
    return value < 0.0f;
}


int isNegativeDouble(double value) {
    return value < 0.0;
}


int isNegativeLongDouble(long double value) {
    return value < 0.0L;
}

//ВАЛІДВЦІЯ НА НЕДОДАТНІСТЬ

int isNonPositiveInt(int value){
    return value <= 0;
}

int isNonPositiveFloat(float value){
    return value <= 0.0f;
}

int isNonPositiveDouble(double value){
    return value <= 0.0;
}

int isNonPositiveLongDouble(long double value){
    return value <= 0.0L;
}

//  ВАЛІДАЦІЯ НА НУЛЬ 


int isZeroInt(int value) {
    return value == 0;
}


int isZeroFloat(float value) {
    return value == 0.0f;
}


int isZeroDouble(double value) {
    return value == 0.0;
}


int isZeroLongDouble(long double value) {
    return value == 0.0L;
}