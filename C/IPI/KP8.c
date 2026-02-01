#include <stdio.h>
#include "validations.h" 
#include <math.h>

#define PI 3.14159265358979323846

typedef struct{
    float Re;
    float Im;
} complex;

// Функція ділення комплексних чисел
complex division(complex first, complex second){
    
    complex result = {0, 0};
    float denom = second.Re * second.Re + second.Im * second.Im;
    
    if (denom == 0) return result;

    result.Re = (first.Re * second.Re + first.Im * second.Im) / denom;
    result.Im = (first.Im * second.Re - first.Re * second.Im) / denom;
    return result;
}

int main(){
    float fmin, fmax, df, R1, R2, L, C, f = 0, W;
    int valid = 0, choise = 0, number;
    
    // Змінні для обчислень
    complex Z_num, Z_den, Z_result;
    float reactance, wC_inv;
    float f0; // Резонансна частота

    do{
        //ВВЕДЕННЯ ДАНИХ
        // Вибір контура
        do{
            valid = inputInt("Введіть номер контура (1-4):", &number);
            if(valid == 0 || number > 4 || number < 1)
                printf("Введіть ціле число від 1 до 4!\n");
        }while(valid == 0);

        // Введення параметрів елементів
        do{
            valid = inputFloat("R1 (Ом):", &R1);
            if(!valid || R1 <= 0) printf("Має бути > 0!\n");
        }while(!valid);

        if(number == 3 || number == 4){
            do{
                valid = inputFloat("R2 (Ом):", &R2);
                if(!valid || R2 <= 0) printf("Має бути > 0!\n");
            }while(!valid);
        } else {
            R2 = 0;
        }

        do{
            valid = inputFloat("C (Ф):", &C);
            if(!valid || C <= 0) printf("Має бути > 0!\n");
        }while(!valid);

        do{
            valid = inputFloat("L (Гн):", &L);
            if(!valid || L <= 0) printf("Має бути > 0!\n");
        }while(!valid);

        // Введення частот
        do{
            do{
                valid = inputFloat("fmin (Гц):", &fmin);
                if(!valid) printf("Некоректне число!\n");
            }while(!valid);

            do{
                valid = inputFloat("fmax (Гц):", &fmax);
                if(!valid) printf("Некоректне число!\n");
            }while(!valid);

            if(fmin > fmax){
                printf("fmin має бути менше fmax!\n");
                valid = 0;
            } else valid = 1;
        }while(valid == 0);

        do{
            valid = inputFloat("df (Гц):", &df);
            if(!valid || df <= 0) printf("Крок має бути > 0!\n");
        }while(!valid);


        //РОЗРАХУНОК РЕЗОНАНСНОЇ ЧАСТОТИ (f0)
        f0 = 1.0 / (2.0 * PI * sqrt(L * C));
        
        printf("Резонансна частота f0 = %.4f Гц\n", f0);

        //ТАБЛИЦЯ
        printf("| %-10s | %-25s |\n", "f (Hz)", "Complex Z (Re + jIm)");
        printf("|------------|---------------------------|\n");

        float epsilon = df / 1000.0;

        for(f = fmin; f <= fmax + epsilon; f += df){
            W = 2 * PI * f;

            if(W == 0) {
                 printf("| %-10.2f | %-25s |\n", f, " - ");
                 continue;
            }

            // Спільні змінні
            wC_inv = 1.0 / (W * C);
            reactance = (W * L) - wC_inv;

            // Логіка вибору формули
            if(number == 1){ 
                Z_num.Re = L / C;
                Z_num.Im = -(R1 * wC_inv);
                Z_den.Re = R1;
                Z_den.Im = reactance;
            } else if(number == 2){
                Z_num.Re = L / C;
                Z_num.Im = (R1 * wC_inv); 
                Z_den.Re = R1;
                Z_den.Im = reactance;
            } else if(number == 3){
                Z_num.Re = R1 * R2;
                Z_num.Im = R1 * reactance;
                Z_den.Re = R1 + R2;
                Z_den.Im = reactance;
            } else if(number == 4){
                Z_num.Re = (R1 * R2) + (L / C);
                Z_num.Im = (W * L * R1) - (R2 * wC_inv);
                Z_den.Re = R1 + R2;
                Z_den.Im = reactance;
            }

            // Обчислення Z
            Z_result = division(Z_num, Z_den);

            // Вивід рядка таблиці без модуля
            char sign = (Z_result.Im >= 0) ? '+' : '-';
            printf("| %-10.2f | %9.4f %c j%-9.4f |\n", 
                   f, Z_result.Re, sign, fabs(Z_result.Im));
        }

        inputInt("\nПовторити? 1-так, 0-ні: ", &choise);

    }while(choise == 1);
    
    return 0;
}