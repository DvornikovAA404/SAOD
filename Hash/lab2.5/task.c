#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Функция для проверки, является ли число простым
bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Функция для вычисления хеша
unsigned int hash_function(char c, unsigned int m) {
    unsigned int h = 0; // Начальное значение хеша
    h = (h * 256 + (unsigned char)c) % m;
    return h;
}

// Функция для линейного пробирования
int linear_probe(int hashValue, int attempt, int m) {
    return (hashValue + attempt) % m;
}

// Функция для квадратичного пробирования
int quadratic_probe(int hashValue, int attempt, int m) {
    return (hashValue + attempt * attempt) % m;
}

// Функция для вставки ключа с линейным пробированием и подсчета коллизий
int insert_linear(char hashTable[], char key, int m) {
    unsigned int hashValue = hash_function(key, m);
    int attempt = 0;
    int collisions = 0;
    while (hashTable[hashValue] != '\0') {
        collisions++;
        hashValue = linear_probe(hashValue, ++attempt, m);
    }
    hashTable[hashValue] = key;
    return collisions;
}

// Функция для вставки ключа с квадратичным пробированием и подсчета коллизий
int insert_quadratic(char hashTable[], char key, int m) {
    unsigned int hashValue = hash_function(key, m);
    int attempt = 0;
    int collisions = 0;
    while (hashTable[hashValue] != '\0') {
        collisions++;
        hashValue = quadratic_probe(hashValue, ++attempt, m);
    }
    hashTable[hashValue] = key;
    return collisions;
}

// Функция для вывода хеш-таблицы
void printHashTable(char hashTable[], int m) {
    printf("| %-15s |", "Номер ячейки");
    for (int i = 0; i < m; i++) {
        printf("%4d |", i);
    }
    printf("\n");

    printf("| %-15s |", "Символ");
    for (int i = 0; i < m; i++) {
        if (hashTable[i] != '\0') {
            printf("  %c  |", hashTable[i]);
        } else {
            printf("     |");
        }
    }
    printf("\n\n");
}

// Функция для вывода заголовка таблицы
void printHeader() {
    printf("| %-25s | %-25s | %-20s | %-20s |\n",
           "Размер хеш-таблицы", "Количество исходных символов",
           "Количество коллизий (линейные пробы)", "Количество коллизий (квадратичные пробы)");
    printf("|-------------------------|-----------------------------|---------------------|---------------------|\n");
}

// Функция для вывода строки таблицы
void printRow(int tableSize, int initialSymbols, int linearCollisions, int quadraticCollisions) {
    printf("| %-25d | %-25d | %-20d | %-20d |\n",
           tableSize, initialSymbols, linearCollisions, quadraticCollisions);
}

int main() {
    // Найти 10 простых чисел между 11 и 101
    int primes[10];
    int index = 0;
    for (int i = 11; index < 10 && i <= 101; i++) {
        if (is_prime(i)) {
            primes[index++] = i;
        }
    }

    // Ключевое слово в английском транслите
    const char *key_string = "DVORNIKOVAND";
    int key_length = strlen(key_string);

    // Исследование коллизий для каждого размера хеш-таблицы
    printf("Исследование количества коллизий:\n");
    printHeader();

    for (int i = 0; i < 10; i++) {
        int m = primes[i];
        char hashTableLinear[m]; // Хеш-таблица для линейных проб
        char hashTableQuadratic[m]; // Хеш-таблица для квадратичных проб

        // Инициализация хеш-таблиц
        memset(hashTableLinear, '\0', sizeof(char) * m);
        memset(hashTableQuadratic, '\0', sizeof(char) * m);

        int totalLinearCollisions = 0;
        int totalQuadraticCollisions = 0;

        // Вставка ключей и подсчет коллизий
        for (int j = 0; j < key_length; j++) {
            totalLinearCollisions += insert_linear(hashTableLinear, key_string[j], m);
            totalQuadraticCollisions += insert_quadratic(hashTableQuadratic, key_string[j], m);
        }

        // Вывод хеш-таблиц
        printf("\nХеш-таблица с линейным пробированием (размер %d):\n", m);
        printHashTable(hashTableLinear, m);

        printf("Хеш-таблица с квадратичным пробированием (размер %d):\n", m);
        printHashTable(hashTableQuadratic, m);

        // Вывод результатов
        printRow(m, key_length, totalLinearCollisions, totalQuadraticCollisions);
    }

    return 0;
}
