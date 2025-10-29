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
        perror("\033[1;31mОшибка при открытии файла\033[0m");
        return 0;
    }

    char line[MAX_LINE];
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) < 5) continue;

        char *token = strtok(line, ";");
        if (!token) continue;
        strncpy(questions[count].question, token, sizeof(questions[count].question));

        for (int i = 0; i < 4; i++) {
            token = strtok(NULL, ";");
            if (token)
                strncpy(questions[count].options[i], token, sizeof(questions[count].options[i]));
            else
                strcpy(questions[count].options[i], "");
        }

        token = strtok(NULL, ";");
        questions[count].correct = token ? token[0] : ' ';
        count++;
    }

    fclose(file);
    return count;
}
