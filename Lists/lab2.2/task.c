#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int C_f; 
int M_f; 

Node* create_desc(int n) {
    Node* head = NULL;
    for (int i = n; i >= 1; i--) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = i;
        new_node->next = head;
        head = new_node;
        M_f++; 
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
        M_f++;
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
        M_f++;
    }
    return head;
}

void delete_list(Node** head) {
    Node* current = *head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
        M_f++;
    }
    *head = NULL;
}

Node* merge(Node* left, Node* right) {
    Node dummy;
    Node* tail = &dummy;
    dummy.next = NULL;

    while (left && right) {
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

Node* split_series(Node* head, int k) {
    if (!head) return NULL;
    Node* current = head;
    while (current->next && k > 1) {
        current = current->next;
        k--;
        M_f++;
    }
    Node* next_part = current->next;
    current->next = NULL;
    M_f++;
    return next_part;
}

Node* MergeSort(Node* head) {
    int n = 0;
    Node* tmp = head;
    while (tmp) {
        n++;
        tmp = tmp->next;
        M_f++;
    }

    Node* sorted = head;
    for (int k = 1; k < n; k *= 2) {
        Node dummy;
        Node* tail = &dummy;
        dummy.next = NULL;

        while (sorted) {
            Node* left = sorted;
            Node* right = split_series(left, k);
            sorted = split_series(right, k);

            Node* merged = merge(left, right);
            tail->next = merged;
            while (tail->next) {
                tail = tail->next;
                M_f++;
            }
        }
        sorted = dummy.next;
    }
    return sorted;
}

void printHeader() {
    printf("| %-5s | %-20s | %-7s | %-7s | %-7s |\n", 
           "N", "M+C теория", "Убыв.", "Случ.", "Возр.");
    printf("|-------|----------------|-------|-------|-------|\n");
}

void printRow(int n, int theory, int desc, int rand, int asc) {
    printf("| %-5d | %-14d | %-5d | %-5d | %-5d |\n", 
           n, theory, desc, rand, asc);
}

int count_series(Node* head) {
    if (!head) return 0;
    int count = 1;
    int prev = head->data;
    Node* current = head->next;
    while (current) {
        if (current->data < prev) {
            count++;
            prev = current->data;
        }
        current = current->next;
    }
    return count;
}

void testMergeSort() {
    int sizes[] = {100, 200, 300, 400, 500};
    printf("\nТрудоемкость сортировки прямого слияния\n");
    printHeader();

    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        int theory = 3.0 * n * log2(n);
        int results[3] = {0};

        for (int t = 0; t < 3; t++) {
            Node* list = NULL;
            switch(t) {
                case 0: list = create_desc(n); break;
                case 1: list = create_random(n); break;
                case 2: list = create_asc(n); break;
            }

            C_f = 0;
            M_f = 0;
            list = MergeSort(list);
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