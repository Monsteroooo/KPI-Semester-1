#include <stdio.h>
#include <math.h>

int main() {

float x, y;
char choose;

do{
printf("Введіть значення x: ");
if (scanf("%f", &x) != 1) {
    printf("Помилка введення! Будь ласка, введіть число.\n");
    while (getchar() != '\n');
    continue;
}
if (x < -1){
    y = 1.0 / pow (x, 2);
    printf("x < -1, y = 1 / x^2 = %f\n", y);
} else if (x == -1){
    y = 1;
    printf("x = -1, y = 1\n");
} else if(x > -1 && x < 2){
    y = pow(x, 2);
    printf("-1 < x < 2, y = x^2 = %f\n", y);
} else if (x >= 2){
    y = 4;
    printf("x >= 2, y = 4\n");
}

printf("Бажаєте продовжити? (y/n): ");
scanf(" %c", &choose);
} while (choose == 'y' || choose == 'Y');

return 0;



}