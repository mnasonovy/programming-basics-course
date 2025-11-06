#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    double val;
    struct Node* next;
} Node;

// Добавление элемента в конец списка
Node* append(Node* head, double value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = value;
    newNode->next = NULL;

    if (head == NULL) return newNode;

    Node* temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
    return head;
}

// Сортировка по убыванию абсолютного значения (стабильная)
Node* sortByAbs(Node* head) {
    if (!head) return head;

    Node* i = head;
    while (i != NULL) {
        Node* j = i->next;
        while (j != NULL) {
            if (fabs(j->val) > fabs(i->val)) {
                double tmp = i->val;
                i->val = j->val;
                j->val = tmp;
            }
            j = j->next;
        }
        i = i->next;
    }
    return head;
}

// Освобождение памяти
void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    Node* head = NULL;
    double x;
    char ch;

    // Ввод в одну строку
    while (scanf("%lf", &x) == 1) {
        head = append(head, x);
        ch = getchar();
        if (ch == '\n' || ch == EOF) break;
        ungetc(ch, stdin);
    }

    // Сортировка по убыванию модуля
    head = sortByAbs(head);

    // Вывод результата
    Node* current = head;
    while (current != NULL) {
        printf("%g", current->val);
        if (current->next != NULL) printf(" ");
        current = current->next;
    }

    freeList(head);
    return 0;
}
