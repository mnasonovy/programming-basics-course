#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 512
#define MAX_QUESTIONS 100

typedef struct {
    char question[256];
    char options[4][128];
    char correct;
} Question;

int load_questions(const char *filename, Question *questions) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "\033[1;31mОшибка при открытии файла: %s\033[0m\n", filename);
        return 0;
    }

    char line[MAX_LINE];
    int count = 0;
    while (fgets(line, sizeof(line), file) && count < MAX_QUESTIONS) {
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) < 5) continue;

        char *token = strtok(line, ";");
        if (!token) continue;
        strncpy(questions[count].question, token, sizeof(questions[count].question) - 1);
        questions[count].question[sizeof(questions[count].question) - 1] = '\0';

        for (int i = 0; i < 4; i++) {
            token = strtok(NULL, ";");
            if (token) {
                strncpy(questions[count].options[i], token, sizeof(questions[count].options[i]) - 1);
                questions[count].options[i][sizeof(questions[count].options[i]) - 1] = '\0';
            } else {
                questions[count].options[i][0] = '\0';
            }
        }

        token = strtok(NULL, ";");
        questions[count].correct = token ? token[0] : ' ';
        count++;
    }

    fclose(file);
    return count;
}
