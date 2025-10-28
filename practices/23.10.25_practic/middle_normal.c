#include <stdio.h>
#include <math.h>

// Функция вычисляет середину отрезка и координаты точки на серединном перпендикуляре
void middleNormal(double x1, double y1, double x2, double y2,
                  double *xm, double *ym, double *xp, double *yp) {
    // Середина отрезка
    *xm = (x1 + x2) / 2.0;
    *ym = (y1 + y2) / 2.0;

    // Длина отрезка
    double dx = x2 - x1;
    double dy = y2 - y1;
    double L = sqrt(dx * dx + dy * dy);

    // Перпендикулярный вектор
    double nx = -dy;
    double ny = dx;

    // Нормализация вектора
    double nlen = sqrt(nx * nx + ny * ny);
    nx /= nlen;
    ny /= nlen;

    // Координаты точки на перпендикуляре на расстоянии L
    *xp = *xm + nx * L;
    *yp = *ym + ny * L;
}

int main(void) {
    double x1, y1, x2, y2;

    printf("Enter coordinates of two points on the plane:\n");
    printf("  Point A (x1 y1): ");
    if (scanf("%lf %lf", &x1, &y1) != 2) {
        printf("Error: invalid input for point A.\n");
        return 1;
    }

    printf("  Point B (x2 y2): ");
    if (scanf("%lf %lf", &x2, &y2) != 2) {
        printf("Error: invalid input for point B.\n");
        return 1;
    }

    // Проверка совпадения точек
    if (x1 == x2 && y1 == y2) {
        printf("Error: points coincide, line cannot be constructed.\n");
        return 1;
    }

    double xm, ym, xp, yp;
    middleNormal(x1, y1, x2, y2, &xm, &ym, &xp, &yp);

    printf("\n--- Results ---\n");
    printf("Midpoint: (%.3f, %.3f)\n", xm, ym);
    printf("Point on perpendicular: (%.3f, %.3f)\n", xp, yp);

    return 0;
}
