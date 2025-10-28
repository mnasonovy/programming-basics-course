#include <stdio.h>
#include <math.h>

//--- модуль (длина вектора) ---
double absolute_value(double x, double y){
    return sqrt(x*x + y*y);
}

//--- скалярное произведение ---
double dot(double x_1, double y_1, double x_2, double y_2){
    return x_1*x_2 + y_1*y_2;
}

//--- умножение вектора на константу ---
void mult(double c, double x, double y, double *xr, double *yr){
    *xr = c * x;
    *yr = c * y;
}

//--- нормирование вектора ---
void normalize(double x, double y, double *xr, double *yr){
    double len = absolute_value(x, y);
    if (len == 0){
        *xr = 0;
        *yr = 0;
    } else {
        *xr = x / len;
        *yr = y / len;
    }
}

//--- биссектриса угла между двумя векторами ---
void bisector(double x_1, double y_1, double x_2, double y_2, double *xr, double *yr){
    double n_x_1, n_y_1, n_x_2, n_y_2;
    normalize(x_1, y_1, &n_x_1, &n_y_1);
    normalize(x_2, y_2, &n_x_2, &n_y_2);
    *xr = n_x_1 + n_x_2;
    *yr = n_y_1 + n_y_2;
}

int main(){
    double x_1, y_1, x_2, y_2;

    // Ввод координат векторов
    printf("Enter coordinates of the first vector (x1 y1): ");
    scanf("%lf %lf", &x_1, &y_1);
    printf("Enter coordinates of the second vector (x2 y2): ");
    scanf("%lf %lf", &x_2, &y_2);

    printf("\n--- Results ---\n");

    // 1. Модули
    printf("Length of the first vector: %.3f\n", absolute_value(x_1, y_1));
    printf("Length of the second vector: %.3f\n", absolute_value(x_2, y_2));

    // 2. Скалярное произведение
    printf("Dot product: %.3f\n", dot(x_1, y_1, x_2, y_2));

    // 3. Умножение на константу
    double c, m_x_1, m_y_1, m_x_2, m_y_2;
    printf("Enter the constant for multiplication: ");
    scanf("%lf", &c);
    mult(c, x_1, y_1, &m_x_1, &m_y_1);
    printf("Result of multiplying the first vector by %.2f: (%.3f, %.3f)\n", c, m_x_1, m_y_1);
    mult(c, x_2, y_2, &m_x_2, &m_y_2);
    printf("Result of multiplying the second vector by %.2f: (%.3f, %.3f)\n", c, m_x_2, m_y_2);

    // 4. Нормирование
    double n_x_1, n_y_1, n_x_2, n_y_2;
    normalize(x_1, y_1, &n_x_1, &n_y_1);
    printf("Normalized first vector: (%.3f, %.3f)\n", n_x_1, n_y_1);
    normalize(x_2, y_2, &n_x_2, &n_y_2);
    printf("Normalized second vector: (%.3f, %.3f)\n", n_x_2, n_y_2);

    // 5. Биссектриса
    double b_x, b_y;
    bisector(x_1, y_1, x_2, y_2, &b_x, &b_y);
    printf("Bisector vector: (%.3f, %.3f)\n", b_x, b_y);

    return 0;
}
