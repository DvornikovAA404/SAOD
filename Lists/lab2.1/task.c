#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

typedef struct Node {
    int data;
    struct Node* next;
} Node;


Node* create_stack_asc(int n) {
    Node* top = NULL;
    for (int i = n; i >= 1; i--) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = i;
        new_node->next = top;
        top = new_node;
    }
    return top;
}

Node* create_stack_desc(int n) {
    Node* top = NULL;
    for (int i = 1; i <= n; i++) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = i;
        new_node->next = top;
        top = new_node;
    }
    return top;
}

Node* create_stack_random(int n, int min_val, int max_val) {
    Node* top = NULL;
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int num = rand() % (max_val - min_val + 1) + min_val;
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = num;
        new_node->next = top;
        top = new_node;
    }
    return top;
}


Node* create_queue_asc(int n) {
    Node* head = NULL;
    Node* tail = NULL;
    for (int i = 1; i <= n; i++) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = i;
        new_node->next = NULL;
        if (!tail) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    return head;
}

Node* create_queue_desc(int n) {
    Node* head = NULL;
    Node* tail = NULL;
    for (int i = n; i >= 1; i--) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = i;
        new_node->next = NULL;
        if (!tail) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    return head;
}

Node* create_queue_random(int n, int min_val, int max_val) {
    Node* head = NULL;
    Node* tail = NULL;
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int num = rand() % (max_val - min_val + 1) + min_val;
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = num;
        new_node->next = NULL;
        if (!tail) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    return head;
}


void print_list(Node* head) {
    Node* current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int checksum(Node* head) {
    int sum = 0;
    Node* current = head;
    while (current) {
        sum += current->data;
        current = current->next;
    }
    return sum;
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

void delete_list(Node** head) {
    Node* current = *head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}

void print_forward_recursive(Node* head) {
    if (!head) {
        printf("\n");
        return;
    }
    printf("%d ", head->data);
    print_forward_recursive(head->next);
}

void print_backward_recursive(Node* head) {
    if (!head) {
        return;
    }
    print_backward_recursive(head->next);
    printf("%d ", head->data);
}

int main() {
    Node* stack_asc = create_stack_asc(N);
    printf("Возрастающий стек: ");
    print_list(stack_asc);

    printf("Контрольная сумма возрастающего стека: %d\n", checksum(stack_asc));
    printf("Количество серий возрастающего стека: %d\n", count_series(stack_asc));
    printf("\n");

    Node* stack_desc = create_stack_desc(N);
    printf("Убывающий стек: ");
    print_list(stack_desc);
    printf("Контрольная сумма убывающего стека: %d\n", checksum(stack_desc));
    printf("Количество серий убывающего стека: %d\n", count_series(stack_desc));
    printf("\n");

    srand(time(NULL));

    Node* stack_rand = create_stack_random(N, 10, 20);
    printf("Случайный стек: ");
    print_list(stack_rand);
    printf("Контрольная сумма случайного стека: %d\n", checksum(stack_rand));
    printf("Количество серий случайного стека: %d\n", count_series(stack_rand));
    printf("\n");

    Node* queue_asc = create_queue_asc(N);
    printf("Возрастающая очередь: ");
    print_list(queue_asc); 
    printf("Контрольная сумма возрастающей очереди: %d\n", checksum(queue_asc));
    printf("Количество серий возрастающей очереди: %d\n", count_series(queue_asc));
    printf("\n");

    Node* queue_desc = create_queue_desc(N);
    printf("Убывающая очередь: ");
    print_list(queue_desc); 
    printf("Контрольная сумма убывающей очереди: %d\n", checksum(queue_desc));
    printf("Количество серий убывающей очереди: %d\n", count_series(queue_desc));
    printf("\n");
    srand(time(NULL));

    Node* queue_rand = create_queue_random(N, 0, 50);
    printf("Случайная очередь: ");
    print_list(queue_rand);
    printf("Контрольная сумма случайной очереди: %d\n", checksum(queue_rand));
    printf("Количество серий случайной очереди: %d\n", count_series(queue_rand));
    printf("\n");




    printf("\nРекурсивная печать возрастающего стека в прямом порядке: ");
    print_forward_recursive(stack_asc); 

    printf("Рекурсивная печать возрастающего стека в убывающем порядке: ");
    print_backward_recursive(stack_asc); 

    printf("\n");

    delete_list(&stack_asc);
    delete_list(&stack_desc);
    delete_list(&stack_rand);
    delete_list(&queue_asc);
    delete_list(&queue_desc);
    delete_list(&queue_rand);

    return 0;
}