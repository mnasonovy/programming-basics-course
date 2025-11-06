#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <locale.h>

#include "test_loader.h"

#ifdef _WIN32
    #include <windows.h>
    #define GREEN   ""
    #define RED     ""
    #define YELLOW  ""
    #define RESET   ""
#else
    #define GREEN   "\033[1;32m"
    #define RED     "\033[1;31m"
    #define YELLOW  "\033[1;33m"
    #define RESET   "\033[0m"
#endif

#define TEST_DIR "../"

void list_tests(char files[][256], int *count) {
    DIR *dir = opendir(TEST_DIR);
    if (!dir) {
        perror("Не удалось открыть каталог тестов");
        return;
    }

    struct dirent *entry;
    *count = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, "_test.txt")) {
            snprintf(files[*count], 256, "%s%s", TEST_DIR, entry->d_name);
            (*count)++;
        }
    }
    closedir(dir);
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    char test_files[50][256];
    int test_count = 0;

    list_tests(test_files, &test_count);

    if (test_count == 0) {
        printf("%sНе найдено файлов тестов.%s\n", RED, RESET);
        return 1;
    }

    printf("%sНайденные тесты:%s\n", YELLOW, RESET);
    for (int i = 0; i < test_count; i++) {
        printf("%d) %s\n", i + 1, test_files[i]);
    }

    int choice = 0;
    printf("\nВведите номер теста для прохождения: ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > test_count) {
        printf("%sНеверный выбор.%s\n", RED, RESET);
        return 1;
    }

    Question questions[MAX_QUESTIONS];
    int total = load_questions(test_files[choice - 1], questions);

    if (total == 0) {
        printf("%sОшибка загрузки теста.%s\n", RED, RESET);
        return 1;
    }

    printf("\n%sЗагружено %d вопросов из %s%s\n",
           GREEN, total, test_files[choice - 1], RESET);
    printf("----------------------------------------\n");

    int correct_count = 0;

    for (int i = 0; i < total; i++) {
        printf("\n%d) %s\n", i + 1, questions[i].question);
        printf("A) %s\nB) %s\nC) %s\nD) %s\n",
               questions[i].options[0],
               questions[i].options[1],
               questions[i].options[2],
               questions[i].options[3]);

        char answer;
        printf("Ваш ответ: ");
        scanf(" %c", &answer);
        answer = toupper(answer);

        if (answer == questions[i].correct) {
            printf("%sВерно!%s\n", GREEN, RESET);
            correct_count++;
        } else {
            printf("%sНеверно.%s Правильный ответ: %s%c%s\n",
                   RED, RESET, GREEN, questions[i].correct, RESET);
        }
    }

    double percent = (double)correct_count / total * 100.0;
    printf("\n----------------------------------------\n");
    printf("Результат: %s%d%s из %d (%.1f%%)\n",
           GREEN, correct_count, RESET, total, percent);

    if (percent >= 80.0)
        printf("%sОтлично!%s\n", GREEN, RESET);
    else if (percent >= 50.0)
        printf("%sНеплохо,%s повтори материал.\n", YELLOW, RESET);
    else
        printf("%sНужно повторить теорию.%s\n", RED, RESET);

    return 0;
}
