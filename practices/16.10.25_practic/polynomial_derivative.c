#include <stdio.h>
#include <stdlib.h>

// Программа вычисляет значение многочлена и его производной в заданной точке x
// с использованием алгоритма Горнера

int main(void) {
    int n;

    // --- Ввод степени многочлена ---
    printf("Enter the degree of the polynomial (n): ");
    scanf("%d", &n);

    // --- Выделение памяти под (n + 1) коэффициентов ---
    double *a = (double *)malloc((n + 1) * sizeof(double));
    if (a == NULL) {
        printf("Error: not enough memory.\n");
        return 1;
    }

    // --- Ввод коэффициентов a[0] до a[n] ---
    printf("Enter %d coefficients (from a[0] to a[%d]):\n", n + 1, n);
    for (int i = 0; i <= n; ++i) {
        printf("a[%d] = ", i);
        scanf("%lf", &a[i]);
    }

    // --- Ввод точки x ---
    double x;
    printf("Enter the value of x: ");
    scanf("%lf", &x);

    // --- Переменные для вычисления ---
    double b = a[n]; // значение многочлена
    double c = 0.0;  // значение производной

    // --- Алгоритм Горнера ---
    for (int k = n - 1; k >= 0; --k) {
        c = c * x + b;    // новое значение производной
        b = b * x + a[k]; // новое значение самого многочлена
    }

    // --- Вывод результатов ---
    printf("\n--- Results ---\n");
    printf("P(x)  = %.6lf\n", b);
    printf("P'(x) = %.6lf\n", c);

    // --- Освобождение памяти ---
    free(a);
    return 0;
}