#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Проверяем, что передано ровно 2 аргумента (a и b)
    if (argc != 3) {
        printf("Usage: %s <a> <b>\n", argv[0]);
        printf("Example: %s 2 4\n", argv[0]);
        return 1;
    }

    // Преобразуем аргументы из строк в числа
    double a = atof(argv[1]);
    double b = atof(argv[2]);

    // Решаем уравнение a*x + b = 0
    if (a == 0) {
        if (b == 0) {
            printf("Infinite number of solutions (any x fits)\n");
        } else {
            printf("No solutions\n");
        }
    } else {
        double x = -b / a;
        printf("Solution: x = %.2f\n", x);
    }

    return 0;
}