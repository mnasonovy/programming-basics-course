#ifndef TEST_LOADER_H
#define TEST_LOADER_H

#define MAX_LINE 512
#define MAX_QUESTIONS 100

typedef struct {
    char question[256];
    char options[4][128];
    char correct;
} Question;

int load_questions(const char *filename, Question *questions);

#endif
