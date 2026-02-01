#include "validations.h"
#include <math.h>
#include <stdio.h>
//
#define Pi 3.14159265358979323846
#define MAX_ITER 1000

double sin_Taylor(double x_rad, double epsilon);
double cos_Taylor(double x_rad, double epsilon);
double degreeToRadian(double degree);

int main(){
    double x1, x2, Taylor_res, div, e, d, n, table_value_sin, table_value_cos;
    int val, chooise, valid;
do{
    
        do{
            inputDouble("Введіть x1: ", &x1);
        if(0 < x1 < 1e-15){
            valid = 0;
            printf("Помилка: введіть правильне число до 15 символів після коми.\n");
        }else if (-1e-15 < x1 < 0){
            valid = 0;
            printf("Помилка: введіть правильне число до 15 символів після коми.\n");
        }else valid = 1;
        
        }while(valid == 0);
        do{
        inputDouble("Введіть x2: ", &x2);
        if(x2 < 1e-15){
            valid = 0;
            printf("Помилка: введіть правильне число до 15 символів після коми.\n");
        }else valid = 1;
        }while(valid == 0);
    
    do{
        val = 0;
    if (x1 < x2){
        inputDouble("Введіть крок d більше нуля: ", &d);
        if(!isPositiveDouble(d)) {
            printf("d має бути дадатнім! \n");
            val = 0;
        }else val = 1;
    }else if(x1 > x2){
        inputDouble("Введіть крок d менше нуля: ", &d);
        if(!isNegativeDouble(d)){
             printf("d має бути від'ємним! \n");
             val = 0;
            }else val = 1;
    }else{
        inputDouble("Введіть довільний крок d: ", &d);
        val = 1;
    }
    }while(val == 0);

    do{
        val = 0;
        inputDouble("Введіть точність e (e > 0): ", &e);
        if(!isPositiveDouble(e)) {
            printf("e має бути додатнім! \n");
            val = 0;
        }else val = 1;

    }while(val == 0);

    printf("Розрахунок для якої функції бахаєте виконати? 1 - синус 0 - косинус: ");
    scanf("%d", &chooise);
    while (getchar() != '\n');

    Taylor_res = 1;
    if(chooise == 1){   // СИНУС
    if(x1 != x2){
        printf("---------------------------------------------------------------\n");
        printf("|     x     |   sin_Taylor(x)   |     sin(x)     |   Δ = |a-b| |\n");
        printf("---------------------------------------------------------------\n");

        for(double x = x1; ((x <= x2 && d > 0) || (x >= x2 && d < 0)); x += d){
            n = degreeToRadian(x);
            Taylor_res = sin_Taylor(n, e);
            table_value_sin = sin(n);
            div = fabs(table_value_sin - Taylor_res);
            printf("| %10.5f | %17.10f | %15.10f | %15.10f |\n", x, Taylor_res, table_value_sin, div);
        }

        printf("---------------------------------------------------------------\n");
    } else {
        n = degreeToRadian(x1);
        Taylor_res = sin_Taylor(n, e);
        table_value_sin = sin(n);
        div = fabs(table_value_sin - Taylor_res);
        printf("---------------------------------------------------------------\n");
        printf("|     x     |   sin_Taylor(x)   |     sin(x)     |   Δ = |a-b| |\n");
        printf("---------------------------------------------------------------\n");
        printf("| %10.5f | %17.10f | %15.10f | %15.10f |\n", x1, Taylor_res, table_value_sin, div);
        printf("---------------------------------------------------------------\n");
    }

} else {   // КОСИНУС
    if(x1 != x2){
        printf("---------------------------------------------------------------\n");
        printf("|     x     |   cos_Taylor(x)   |     cos(x)     |   Δ = |a-b| |\n");
        printf("---------------------------------------------------------------\n");

        for(double x = x1; ((x <= x2 && d > 0) || (x >= x2 && d < 0)); x += d){
            n = degreeToRadian(x);
            Taylor_res = cos_Taylor(n, e);
            table_value_cos = cos(n);
            div = fabs(table_value_cos - Taylor_res);
            printf("| %10.5f | %17.10f | %15.10f | %15.10f |\n", x, Taylor_res, table_value_cos, div);
        }

        printf("---------------------------------------------------------------\n");
    } else {
        n = degreeToRadian(x1);
        Taylor_res = cos_Taylor(n, e);
        table_value_cos = cos(n);
        div = fabs(table_value_cos - Taylor_res);
        printf("---------------------------------------------------------------\n");
        printf("|     x     |   cos_Taylor(x)   |     cos(x)     |   Δ = |a-b| |\n");
        printf("---------------------------------------------------------------\n");
        printf("| %10.5f | %17.10f | %15.10f | %15.10f |\n", x1, Taylor_res, table_value_cos, div);
        printf("---------------------------------------------------------------\n");
    }
}

    
    inputInt("Бажаєте продовжити? 1 - так, 0 - ні: ", &chooise);
}while(chooise == 1);
    
}

double degreeToRadian(double degree){
    return degree * (Pi / 180);
}

double sin_Taylor(double x_rad, double epsilon){
    double result = x_rad;
    double delta = result;
    int n = 1;

    while(fabs(delta) >= epsilon && n < MAX_ITER){
        delta = -delta * x_rad * x_rad / ((2 * n) * (2 * n + 1));
        result += delta;
        n++;
    }
    return result;
}

double cos_Taylor(double x_rad, double epsilon){
    double term = 1; // перший член ряду
    double sum = term;
    int n = 1;

    while (fabs(term) >= epsilon && n < MAX_ITER){
        term = -term * x_rad * x_rad / ((2 * n - 1) * (2 * n)); 
        sum += term;
        n++;
    }
    return sum;
}