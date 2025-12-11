#include <stdio.h>
#include <stdlib.h>

// Структура для хранения элемента множества
typedef struct {
    int value;
    int M_bit;  // M-ый бит элемента
} Element;

// Функция для получения M-го бита числа
int getMBit(int num, int M) {
    return (num >> M) & 1;
}

// Функция для замены подпоследовательности
void replaceSubsequence(Element *arr, int n, int M) {
    int i, j;

    printf("\nИсходный массив:\n");
    for (i = 0; i < n; i++) {
        printf("Элемент: %d, M-ый бит (%d): %d\n", 
               arr[i].value, M, arr[i].M_bit);
    }

    // Проход по массиву для поиска строго возрастающих подпоследовательностей
    for (i = 0; i < n; i++) {
        // Проверяем, начинается ли здесь строго возрастающая подпоследовательность
        if (arr[i].M_bit == 0) {
            int start = i;
            int end = i;
            int count = 1;

            // Ищем конец строго возрастающей подпоследовательности
            while (end + 1 < n && arr[end + 1].M_bit == 0 && 
                   arr[end + 1].value > arr[end].value) {
                end++;
                count++;
            }

            // Если подпоследовательность состоит из более чем одного элемента
            if (count > 1) {
                printf("\nНайдена строго возрастающая подпоследовательность:\n");
                printf("Индексы: [%d..%d], длина: %d\n", start, end, count);
                printf("Элементы: ");
                for (j = start; j <= end; j++) {
                    printf("%d ", arr[j].value);
                }
                printf("\n");

                // Ищем предыдущий элемент с меньшим индексом
                int prevElement = -1;
                for (j = start - 1; j >= 0; j--) {
                    if (arr[j].M_bit == 0) {
                        prevElement = j;
                        break;
                    }
                }

                if (prevElement != -1) {
                    printf("Найден предыдущий элемент: arr[%d] = %d\n", 
                           prevElement, arr[prevElement].value);

                    // Замена: сдвигаем элементы
                    Element replacement = arr[prevElement];

                    // Сдвигаем элементы влево
                    for (j = prevElement; j < start; j++) {
                        arr[j] = arr[j + 1];
                    }

                    // Очищаем подпоследовательность (заменяем на один элемент)
                    arr[start] = replacement;

                    // Сдвигаем оставшиеся элементы влево
                    int removeCount = count - 1;
                    for (j = start + 1; j < n - removeCount; j++) {
                        arr[j] = arr[j + removeCount];
                    }

                    // Уменьшаем размер массива
                    n -= removeCount;

                    printf("После замены размер массива: %d\n", n);
                } else {
                    printf("Предыдущий элемент не найден\n");
                }

                // Пропускаем обработанный участок
                i = start;
            }
        }
    }

    printf("\n=== Результирующий массив ===\n");
    for (i = 0; i < n; i++) {
        printf("arr[%d] = %d (M-бит = %d)\n", i, arr[i].value, arr[i].M_bit);
    }
    printf("Итоговый размер: %d\n", n);
}

int main() {
    int n, M;
    int i;

    printf("Введите количество элементов в множестве: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Ошибка: количество элементов должно быть положительным\n");
        return 1;
    }

    Element *arr = (Element *)malloc(n * sizeof(Element));
    if (arr == NULL) {
        printf("Ошибка выделения памяти\n");
        return 1;
    }

    printf("Введите M (номер бита для проверки, начиная с 0): ");
    scanf("%d", &M);

    if (M < 0) {
        printf("Ошибка: M должно быть неотрицательным\n");
        free(arr);
        return 1;
    }

    printf("Введите %d целых чисел:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i].value);
        arr[i].M_bit = getMBit(arr[i].value, M);
    }

    replaceSubsequence(arr, n, M);

    free(arr);
    return 0;
}
