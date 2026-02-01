//gcc KP7.c -o KP7 -lm 
#include <stdio.h>
#include <math.h>
#include "validations.h"

#define TAYLOR_EPS 1e-7
#define PI 3.14159265358979323846

// Приводить кут до діапазону [-PI, PI] для швидшої збіжності ряду
float normalize_angle(float x) {
    x = fmod(x, 2 * PI); 
    
    if (x > PI) x -= 2 * PI;
    if (x < -PI) x += 2 * PI;
    
    return x;
}

// SIN
float my_sin(float x) {
    x = normalize_angle(x); 
    float term = x;         
    float sum = x;
    int n = 1;

    do {
        // Рекурентна формула: (-1 * x^2) / ((2n)*(2n+1))
        term = -term * x * x / (2 * n * (2 * n + 1));
        sum += term;
        n++;
    } while (fabs(term) > TAYLOR_EPS);

    return sum;
}

// COS
float my_cos(float x) {
    x = normalize_angle(x);
    float term = 1.0;      
    float sum = 1.0;
    int n = 1;

    do {
        // Рекурентна формула: (-1 * x^2) / ((2n-1)*(2n))
        term = -term * x * x / ((2 * n - 1) * (2 * n));
        sum += term;
        n++;
    } while (fabs(term) > TAYLOR_EPS);

    return sum;
}

float (*sinPtr)(float) = my_sin;
float (*cosPtr)(float) = my_cos;

float eq1(float x, float y) {   
    return cosPtr(y/x) - 2 * sinPtr(1/x) + (1/x);
}

float eq2(float x, float y) {
    return sinPtr(log(x)) - cosPtr(log(x)) + y * log(x);
}

float derivativeEq1(float x, float y) {
   float a = 1e-5;
   float f_x = eq1(x, y);
   float f_x_plus_a = eq1(x + a, y);
    return (f_x_plus_a - f_x) / a;
}

float derivativeEq2(float x, float y) {
   float a = 1e-5;
   float f_x = eq2(x, y);
   float f_x_plus_a = eq2(x + a, y);
    return (f_x_plus_a - f_x) / a;
}

//МЕТОД ПОЛОВИННОГО ДІЛЕННЯ 
float bisection(float a, float b, float eps, int eqChoise, float y) {
    float x, fa, fx;
    do {
        x = (a + b) / 2;
        if (eqChoise == 1) {
            fa = eq1(a, y);
            fx = eq1(x, y);
        } else {
            fa = eq2(a, y);
            fx = eq2(x, y);
        }
        if (fa * fx > 0) a = x;
        else b = x;
    } while (fabs(b - a) > eps);
    printf("Корінь рівняння %d: %f\n", eqChoise, x);
    return x;
}

//МЕТОД НЬЮТОНА
float dot(float x, float e, int eqChoise, float y) {
    float delta = 0;
    do{
        if(eqChoise == 1){
            delta = eq1(x,y) / derivativeEq1(x,y);
            x = x - delta;
        }else{
            delta = eq2(x,y) / derivativeEq2(x,y);
            x = x - delta;
        }
    }while(fabs(delta)>e);
    printf("Корінь рівняння %d: %f\n", eqChoise, x);
    return x;
}


int main() {
    int eqChoice, method, choice = 1;
    float a, b, eps, y;
    int valid;

    do{
    //ВИБІР РІВНЯННЯ
    do {
        valid = 1;
        printf("Оберіть рівняння:\n");
        printf("1: cos(y/x) - 2sin(1/x) + 1/x = 0\n)\n");
        printf("2: sin(ln x) - cos(ln x) + y*ln x = 0\n");
        inputInt("Ваш вибір:", &eqChoice);
	if(eqChoice != 1 && eqChoice != 2){
		printf("Введіть число 1 або 2.\n");
		valid = 0;
	}
    } while (valid == 0);

    //ВИБІР МЕТОДУ 
    do {
        valid = 1;
        printf("Оберіть метод:\n");
        printf("1 – метод половинного ділення\n");
        printf("2 – метод Ньютона\n");
        inputInt("Ваш вибір:", &method);
	if(method != 1 && method != 2){
		printf("Введіть число 1 або 2.\n");
		valid = 0;
	}

    } while (valid == 0);

     //Ведення вільного члена
    do{
	valid = inputFloat("Введіть вільний член у:", &y);
    }while (valid == 0);

    //Введення точності
     do{
	valid = inputFloat("Введіть точність е додатнє число:", &eps);
    }while (valid == 0);

    //ВВЕДЕННЯ ПРОМІЖКУ a, b
    do {
        valid = 1; 
  	if(method == 1){
		printf("a+b/2 не може дорівнювати 0, та а не може дорівнювати 0 для першого рівняння. a > 0 та a+b/2 > 0 для другого рівняння. Функція на кінцях проміжку має бути рівзних знаків.\n");
		inputFloat("Введіть ліву межу а(не може бути 0):", &a);
		inputFloat("Введіть праву межу b:", &b);

		if(eq1(a,y) * eq1(b,y) > 0 && eqChoice == 1){
			printf("Для методу половинного ділення значення функції в a і b мають бути різних знаків!\n");
		valid = 0;
		}else if(eqChoice == 1){
			if(a == 0 || (a + b) / 2 == 0){
			printf("Рівняння 1 не визначене в таких межах\n");
			valid = 0;
			}
		}else if(eqChoice == 2){
			if(a <= 0 || b <= 0){
                printf("Рівняння 2 не визначене в таких межах\n");
                valid = 0;
            }
		}else if(eq2(a,y) * eq2(b,y) > 0 && eqChoice == 2){
            printf("Для методу половинного ділення значення функції в a і b мають бути різних знаків!\n");
        }else valid = 1;
	}else{
	//Умови для методу Ньютона
        // Умови для методу Ньютона
        printf("Для методу Ньютона введіть ізольований проміжок [a, b].\n");
        printf("Увага: точка b буде використана як початкове наближення!\n");
        
        inputFloat("Введіть ліву межу a:", &a);
        inputFloat("Введіть праву межу b:", &b);

        // Перевірка 1: Чи потрапляємо ми в область визначення
        if (eqChoice == 1 && (a == 0 || b == 0)) {
            printf("Помилка: Аргумент не може дорівнювати 0 для цього рівняння.\n");
            valid = 0;
        } 
        else if (eqChoice == 2 && (a <= 0 || b <= 0)) {
            printf("Помилка: Аргумент має бути > 0 для логарифма.\n");
            valid = 0;
        }
        // Перевірка 2: Чи є корінь на проміжку (різні знаки на кінцях)
        else {
            float fa, fb;
            if (eqChoice == 1) {
                fa = eq1(a, y);
                fb = eq1(b, y);
            } else {
                fa = eq2(a, y);
                fb = eq2(b, y);
            }

            if (fa * fb > 0) {
                printf("Помилка: Функція має однакові знаки на краях проміжку (%f та %f). Кореня не має.\n", fa, fb);
                valid = 0;
            } else {
                valid = 1; // Все добре
            }
        }
	}
    } while (valid == 0);


    float root;

    if (method == 1) {
        root = bisection(a, b, eps, eqChoice, y);
    }
    else {
        root = dot(b, eps, eqChoice, y);
    }

    inputInt("Бажаєте виконати ще один розрахунок?(1 - так 0 - ні):", &choice);
    }while(choice == 1);
    return 0;
}
