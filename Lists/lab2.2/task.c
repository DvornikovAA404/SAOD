#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int C_f; // Счётчик сравнений
int M_f; // Счётчик перемещений

// Создание списков
Node* create_desc(int n) {
    Node* head = NULL;
    for (int i = n; i >= 1; i--) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = i;
        new_node->next = head;
        head = new_node;
        M_f++; // Учёт перемещений при создании
    }
    return head;
}

Node* create_asc(int n) {
    Node* head = NULL;
    for (int i = 1; i <= n; i++) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = i;
        new_node->next = head;
        head = new_node;
        M_f++; // Учёт перемещений при создании
    }
    return head;
}

Node* create_random(int n) {
    Node* head = NULL;
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int num = rand() % 1000 + 1;
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = num;
        new_node->next = head;
        head = new_node;
        M_f++; // Учёт перемещений при создании
    }
    return head;
}

// Удаление списка
void delete_list(Node** head) {
    Node* current = *head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
        M_f++; // Учёт перемещений при удалении
    }
    *head = NULL;
}

// Слияние и сортировка
Node* merge(Node* left, Node* right) {
    Node dummy;
    Node* tail = &dummy;
    dummy.next = NULL;

    while (left && right) {
        C_f++;
        if (left->data <= right->data) {
            tail->next = left;
            left = left->next;
        } else {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
        M_f++;
    }

    tail->next = left ? left : right;
    return dummy.next;
}

Node* mergeSort(Node* head) {
    if (!head || !head->next) return head;

    Node* slow = head;
    Node* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        M_f += 2; // Учёт перемещений указателей
    }
    Node* right = slow->next;
    slow->next = NULL;
    M_f += 2; // Учёт разрыва списка

    return merge(mergeSort(head), mergeSort(right));
}

// Форматирование таблицы
void printHeader() {
    printf("| %-5s | %-20s | %-7s | %-7s | %-7s |\n", 
           "N", "M+C теория", "Убыв.", "Случ.", "Возр.");
    printf("|-------|----------------|-------|-------|-------|\n");
}

void printRow(int n, int theory, int desc, int rand, int asc) {
    printf("| %-5d | %-14d | %-5d | %-5d | %-5d |\n", 
           n, theory, desc, rand, asc);
}

// Тестирование для всех типов данных
void testMergeSort() {
    int sizes[] = {100, 200, 300, 400, 500};
    printf("\nТрудоемкость сортировки прямого слияния\n");
    printHeader();

    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        int theory = n * (int)ceil(log2(n)) + n * (int)ceil(log2(n)) + n;
        int results[3] = {0}; // [Убыв., Случ., Возр.]

        // Тестирование для каждого типа
        for (int t = 0; t < 3; t++) {
            Node* list = NULL;
            switch(t) {
                case 0: list = create_desc(n); break;
                case 1: list = create_random(n); break;
                case 2: list = create_asc(n); break;
            }

            C_f = 0;
            M_f = 0;
            list = mergeSort(list);
            results[t] = C_f + M_f;
            delete_list(&list);
        }

        printRow(n, theory, results[0], results[1], results[2]);
    }
}

int main() {
    testMergeSort();
    return 0;
}
