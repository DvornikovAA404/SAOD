#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char firstName[50];
    char lastName[50];
    char phoneNumber[20];
    char address[100];
} PhoneBookEntry;

int CompareByFirstName(const PhoneBookEntry *a, const PhoneBookEntry *b) {
    return strcmp(a->firstName, b->firstName);
}

int CompareByLastName(const PhoneBookEntry *a, const PhoneBookEntry *b) {
    return strcmp(a->lastName, b->lastName);
}

void InsertSort(int *indexArray, int size, int (*compare)(const PhoneBookEntry *, const PhoneBookEntry *), const PhoneBookEntry *phoneBook) {
    for (int i = 1; i < size; i++) {
        int key = indexArray[i];
        int j = i - 1;
        while (j >= 0 && compare(&phoneBook[indexArray[j]], &phoneBook[key]) > 0) {
            indexArray[j + 1] = indexArray[j];
            j--;
        }
        indexArray[j + 1] = key;
    }
}

void PrintPhoneBookIndexed(const PhoneBookEntry *phoneBook, const int *indexArray, int size) {
    for (int i = 0; i < size; i++) {
        int idx = indexArray[i];
        printf("--------------------\n");
        printf("  Имя: %s\n", phoneBook[idx].firstName);
        printf("  Фамилия: %s\n", phoneBook[idx].lastName);
        printf("  Номер телефона: %s\n", phoneBook[idx].phoneNumber);
        printf("  Адрес: %s\n", phoneBook[idx].address);
    }
}

void FindAllMatches(const PhoneBookEntry *phoneBook, const int *indexArray, int size, const char *key, int (*compare)(const PhoneBookEntry *, const char *)) {
    int foundMatches[size];
    int matchCount = 0;

    for (int i = 0; i < size; i++) {
        if (compare(&phoneBook[indexArray[i]], key) == 0) {
            foundMatches[matchCount++] = indexArray[i];
        }
    }

    if (matchCount > 0) {
        printf("\nНайдено %d записей:\n", matchCount);
        for (int i = 0; i < matchCount; i++) {
            int idx = foundMatches[i];
            printf("--------------------\n");
            printf("  Имя: %s\n", phoneBook[idx].firstName);
            printf("  Фамилия: %s\n", phoneBook[idx].lastName);
            printf("  Номер телефона: %s\n", phoneBook[idx].phoneNumber);
            printf("  Адрес: %s\n", phoneBook[idx].address);
        }
    } else {
        printf("\nЗаписи с ключом '%s' не найдены.\n", key);
    }
}

int CompareByName(const PhoneBookEntry *entry, const char *name) {
    return strcmp(entry->firstName, name);
}

int CompareBySurname(const PhoneBookEntry *entry, const char *surname) {
    return strcmp(entry->lastName, surname);
}

int main() {
    PhoneBookEntry phoneBook[] = {
        {"Иван", "Иванов", "+79001234567", "Москва, ул. Ленина, д. 1"},
        {"Петр", "Петров", "+79009876543", "Санкт-Петербург, пр. Невский, д. 10"},
        {"Анна", "Сидорова", "+79101112233", "Казань, ул. Баумана, д. 5"},
        {"Иван", "Сидоров", "+79204445566", "Новосибирск, ул. Красная, д. 20"},
        {"Мария", "Иванова", "+79307778899", "Екатеринбург, ул. Мира, д. 15"}
    };

    int size = sizeof(phoneBook) / sizeof(phoneBook[0]);

    int indexByFirstName[size];
    int indexByLastName[size];
    for (int i = 0; i < size; i++) {
        indexByFirstName[i] = i;
        indexByLastName[i] = i;
    }

    InsertSort(indexByFirstName, size, CompareByFirstName, phoneBook);
    InsertSort(indexByLastName, size, CompareByLastName, phoneBook);

    printf("Исходный справочник:\n");
    PrintPhoneBookIndexed(phoneBook, indexByFirstName, size);

    printf("\nСправочник, отсортированный по имени:\n");
    PrintPhoneBookIndexed(phoneBook, indexByFirstName, size);

    printf("\nСправочник, отсортированный по фамилии:\n");
    PrintPhoneBookIndexed(phoneBook, indexByLastName, size);

    char searchKey[50];

    printf("\nВведите имя для поиска: ");
    scanf("%s", searchKey);
    FindAllMatches(phoneBook, indexByFirstName, size, searchKey, CompareByName);

    printf("\nВведите фамилию для поиска: ");
    scanf("%s", searchKey);
    FindAllMatches(phoneBook, indexByLastName, size, searchKey, CompareBySurname);

    return 0;
}