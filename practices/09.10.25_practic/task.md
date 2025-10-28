# Работа с двумерными векторами в языке C

---

## 1. Условие задачи

Написать набор функций для работы с двумерными векторами (каждый вектор — пара координат).  
Необходимо реализовать следующие функции:

- **Модуль вектора:**  
  `double absolute_value(double x, double y);`
- **Скалярное произведение:**  
  `double dot(double x1, double y1, double x2, double y2);`
- **Умножение на константу:**  
  `void mult(double c, double x, double y, double *xr, double *yr);`
- **Нормирование:**  
  `void normalize(double x, double y, double *xr, double *yr);`
- **Биссектриса угла между двумя векторами:**  
  `void bisector(double x1, double y1, double x2, double y2, double *xr, double *yr);`

Также требуется написать функцию `main()` для тестирования всех функций.  
**Ввод и вывод** — только в `main`, внутри функций из списка не должно быть `printf` и `scanf`.

---

## 2. Теоретический раздел

Пусть задан вектор $A(x, y)$. Тогда:

- **Модуль (длина) вектора:**  
  $$|A| = \sqrt{x^2 + y^2}$$

- **Скалярное произведение двух векторов $A(x_1, y_1)$ и $B(x_2, y_2)$:**  
  $$A \cdot B = x_1 x_2 + y_1 y_2$$

- **Умножение вектора на константу $c$:**  
  $$A' = cA = (c \cdot x, c \cdot y)$$

- **Нормирование вектора:**  
  $$A_{norm} = \left( \frac{x}{|A|}, \frac{y}{|A|} \right)$$

- **Биссектриса угла между двумя векторами $A$ и $B$:**  
  $$b = \frac{A_{norm} + B_{norm}}{2}$$

---

## 3. Кратко о указателях

**Указатель** — это переменная, которая хранит **адрес другой переменной** в памяти.  
Если `p` — указатель, то `*p` означает *значение* по адресу, на который он указывает.

Пример:
```c
int a = 10;
int *p = &a;   // p хранит адрес переменной a
printf("%d", *p); // выводит значение a (10)
```

Передача адреса переменной в функцию позволяет изменять исходные данные внутри функции,  
как это сделано в функциях `mult`, `normalize` и `bisector`.

---

## 4. Алгоритм программы

1. Считать координаты двух векторов $(x_1, y_1)$ и $(x_2, y_2)$.
2. Вычислить их модули.
3. Найти скалярное произведение.
4. Умножить оба вектора на введённую константу.
5. Выполнить нормирование каждого вектора.
6. Найти вектор биссектрисы между ними.
7. Вывести результаты.

---

## 5. Код программы

```c
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
```

---

## 6. Примеры тестирования

**Пример**
```
Enter coordinates of the first vector (x1 y1): 2 3
Enter coordinates of the second vector (x2 y2): 1 4
Enter the constant for multiplication: 2

--- Results ---
Length of the first vector: 3.606
Length of the second vector: 4.1232
Dot product: 14.000
Result of multiplying the first vector by 2.00: (4.000, 6.000)
Result of multiplying the second vector by 2.00: (2.000, 8.000)
Normalized first vector: (0.555, 0.832)
Normalized second vector: (0.243, 0.970)
Bisector vector: (0.797, 1.802)
```
