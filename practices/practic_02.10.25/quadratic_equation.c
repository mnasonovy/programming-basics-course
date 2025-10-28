#include <stdio.h>  // для ввода-вывода 
#include <math.h>   // для функции sqrt()

int main() {
    double a, b, c;   // коэффициенты уравнения
    double D;         // дискриминант
    double x1, x2;    // корни

    // --- Ввод коэффициентов --- 
    printf("Enter coefficients a, b, c: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    // --- Проверка: a не равно 0 ---
    if (a == 0) {
        printf("This is not a quadratic equation (a = 0)!\n");
        return 0;
    }

    // --- Вычисляем дискриминант ---
    D = b * b - 4 * a * c;

    // --- Анализ дискриминанта ---
    if (D > 0) {
        x1 = (-b + sqrt(D)) / (2 * a);
        x2 = (-b - sqrt(D)) / (2 * a);
        printf("The equation has two real roots: x1 = %.2lf, x2 = %.2lf\n", x1, x2);
    }
    else if (D == 0) {
        x1 = -b / (2 * a);
        printf("The equation has one real root: x = %.2lf\n", x1);
    }
    else {
        printf("The equation has no real roots (D < 0)\n");
    }

    return 0;
}