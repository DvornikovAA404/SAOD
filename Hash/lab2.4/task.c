#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEBUG 0
typedef struct Node {
    char key;
    struct Node* next;
} Node;

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

unsigned int hash_function(char c, unsigned int m) {
    unsigned int h = 0; 
    h = (h * 256 + (unsigned char)c) % m;
    return h;
}

Node* createNode(char key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

void insert(Node* hashTable[], char key, int m) {
    unsigned int hashValue = hash_function(key, m);
    Node* newNode = createNode(key);
    newNode->next = hashTable[hashValue];
    hashTable[hashValue] = newNode;
}

int count_collisions(Node* hashTable[], const char* key_string, int m) {
    int collisions = 0;
    int key_length = strlen(key_string);

    for (int i = 0; i < m; i++) {
        hashTable[i] = NULL; 
    }

    for (int i = 0; i < key_length; i++) {
        insert(hashTable, key_string[i], m);
    }

    for (int i = 0; i < m; i++) {
        int count = 0;
        Node* current = hashTable[i];
        while (current != NULL) {
            count++;
            current = current->next;
        }
        if (count > 1) collisions += (count - 1);
    }

    return collisions;
}

void printHashTable(Node* hashTable[], int m) {
    printf("Содержимое хеш-таблицы:\n");
    for (int i = 0; i < m; i++) {
        printf("Индекс %d: ", i);
        Node* current = hashTable[i];
        while (current != NULL) {
            printf("%c -> ", current->key);
            current = current->next;
        }
        printf("NULL\n");
    }
}

void search(Node* hashTable[], char key, int m) {
    unsigned int hashValue = hash_function(key, m);
    Node* current = hashTable[hashValue];
    int position = 0;

    while (current != NULL) {
        if (current->key == key) {
            printf("Элемент '%c' найден в списке %d на позиции %d.\n", key, hashValue, position);
            return;
        }
        current = current->next;
        position++;
    }

    printf("Элемент '%c' не найден.\n", key);
}

void printHeader() {
    printf("| %-20s | %-25s | %-20s |\n",
           "Размер хеш-таблицы", "Количество исходных символов", "Количество коллизий");
    printf("|--------------------|-----------------------------|---------------------|\n");
}

void printRow(int tableSize, int initialSymbols, int collisions) {
    printf("| %-20d | %-25d | %-20d |\n",
           tableSize, initialSymbols, collisions);
}

int main() {
    int primes[10];
    int index = 0;
    for (int i = 11; index < 10 && i <= 101; i++) {
        if (is_prime(i)) {
            primes[index++] = i;
        }
    }

    const char *key_string = "DVORNIKOVAND";
    int key_length = strlen(key_string);

    printf("Исследование количества коллизий:\n");
    printHeader();

    Node* hashTable[101];
    for (int i = 0; i < 10; i++) {
        int m = primes[i];
        int collisions = count_collisions(hashTable, key_string, m);
        printRow(m, key_length, collisions);
    }

    int m = 17;
    for (int i = 0; i < m; i++) {
        hashTable[i] = NULL;
    }

    for (int i = 0; i < key_length; i++) {
        insert(hashTable, key_string[i], m);
    }
    if(DEBUG){
    printHashTable(hashTable, m);
    }
 
    printf("\nПоиск элементов:\n");
    search(hashTable, 'D', m);
    search(hashTable, 'V', m);
    search(hashTable, 'A', m);
    search(hashTable, 'X', m); 

    for (int i = 0; i < m; i++) {
        Node* current = hashTable[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}
