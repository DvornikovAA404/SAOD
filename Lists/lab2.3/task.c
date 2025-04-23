#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int M_f = 0; // Счётчик перемещений

// Создание списков
Node* create_desc(int n) {
    Node* head = NULL;
    for (int i = n; i >= 1; i--) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = i;
        new_node->next = head;
        head = new_node;
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
    }
    *head = NULL;
}

// Цифровая сортировка (LSD для 4-байтовых чисел)
Node* digitalSort(Node* head, int reverse) {
    const int BITS = 32; // Для 4-байтовых чисел
    Node* buckets[2][10] = {0}; // 10 корзин для каждой цифры (0-9)
    int current_bit = 0;

    for (int bit = 0; bit < BITS; bit++) {
        Node* current = head;
        while (current) {
            int digit = (current->data >> current_bit) & 0x1; // Для примера: битовая сортировка
            Node* next = current->next;
            current->next = buckets[reverse][digit];
            buckets[reverse][digit] = current;
            M_f++;
            current = next;
        }

        // Сборка списка обратно
        head = NULL;
        Node** tail = &head;
        for (int i = 0; i < 10; i++) {
            Node* bucket = reverse ? buckets[reverse][9 - i] : buckets[reverse][i];
            while (bucket) {
                *tail = bucket;
                tail = &(bucket->next);
                bucket = bucket->next;
            }
        }
        current_bit++;
    }
    return head;
}

// Проверка контрольной суммы
int checksum(Node* head) {
    int sum = 0;
    Node* current = head;
    while (current) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}

// Подсчёт серий
int count_series(Node* head) {
    if (!head) return 0;
    int count = 1;
    int prev = head->data;
    Node* current = head->next;
    while (current) {
        if (current->data < prev) count++;
        prev = current->data;
        current = current->next;
    }
    return count;
}

// Форматирование таблицы
void printHeader() {
    printf("| %-5s | %-11s | %-7s | %-7s | %-7s |\n", 
           "N", "Теория (M)", "Убыв.", "Случ.", "Возр.");
    printf("|-------|-------------|---------|---------|---------|\n");
}

void printRow(int n, int theory, int desc, int rand, int asc) {
    printf("| %-5d | %-11d | %-7d | %-7d | %-7d |\n", 
           n, theory, desc, rand, asc);
}

// Тестирование для всех типов данных
void testDigitalSort() {
    int sizes[] = {100, 200, 300, 400, 500};
    printf("\nТрудоемкость цифровой сортировки DigitalSort\n");
    printHeader();

    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        int theory = n; // M = const * n (const = 1 для примера)
        int results[3] = {0}; // [Убыв., Случ., Возр.]

        // Тестирование для каждого типа
        for (int t = 0; t < 3; t++) {
            Node* list = NULL;
            switch(t) {
                case 0: list = create_desc(n); break;
                case 1: list = create_random(n); break;
                case 2: list = create_asc(n); break;
            }

            M_f = 0;
            list = digitalSort(list, 0); // Прямой порядок
            results[t] = M_f;

            // Проверка сортировки
            printf("N=%d, Тип=%d: Контр. сумма=%d, Серий=%d\n", 
                   n, t, checksum(list), count_series(list));
            delete_list(&list);
        }

        printRow(n, theory, results[0], results[1], results[2]);
    }
}

int main() {
    testDigitalSort();
    return 0;
}