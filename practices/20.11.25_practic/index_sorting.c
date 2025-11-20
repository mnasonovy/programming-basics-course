#include <stdio.h>

int main() {
    int arr[] = {0, 1, 2, 3, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    int even[n], odd[n];
    int even_count = 0, odd_count = 0;

    // Разделение элементов на чётные и нечётные индексы
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {          // чётный индекс
            even[even_count] = arr[i];
            even_count++;
        } else {                   // нечётный индекс
            odd[odd_count] = arr[i];
            odd_count++;
        }
    }

    // Создание результирующего массива
    int result[n];
    int idx = 0;

    // Добавляем чётные элементы
    for (int i = 0; i < even_count; i++) {
        result[idx] = even[i];
        idx++;
    }

    // Добавляем нечётные элементы
    for (int i = 0; i < odd_count; i++) {
        result[idx] = odd[i];
        idx++;
    }

    // Вывод результата
    printf("Исходный массив: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\nПреобразованный массив: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }

    return 0;
}