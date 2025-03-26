#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char firstName[50];
    char lastName[50];
    char phoneNumber[20];
    char address[100];
} PhoneBookEntry;

int CompareByName(const PhoneBookEntry *a, const PhoneBookEntry *b) {
    int cmp = strcmp(a->firstName, b->firstName);
    if (cmp != 0) return cmp;
    return strcmp(a->lastName, b->lastName);
}

int CompareByPhone(const PhoneBookEntry *a, const PhoneBookEntry *b) {
    return strcmp(a->phoneNumber, b->phoneNumber);
}

void InsertSort(PhoneBookEntry *phoneBook, int size, int (*compare)(const PhoneBookEntry *, const PhoneBookEntry *)) {
    for (int i = 1; i < size; i++) {
        PhoneBookEntry key = phoneBook[i];
        int j = i - 1;
        while (j >= 0 && compare(&phoneBook[j], &key) > 0) {
            phoneBook[j + 1] = phoneBook[j];
            j--;
        }
        phoneBook[j + 1] = key;
    }
}

void PrintPhoneBook(const PhoneBookEntry *phoneBook, int size) {
    for (int i = 0; i < size; i++) {
        printf("--------------------\n");
        printf("  Имя: %s\n", phoneBook[i].firstName);
        printf("  Фамилия: %s\n", phoneBook[i].lastName);
        printf("  Номер телефона: %s\n", phoneBook[i].phoneNumber);
        printf("  Адрес: %s\n", phoneBook[i].address);
    }
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

    printf("Исходный справочник:\n");
    PrintPhoneBook(phoneBook, size);

    int choice;
    printf("\nВыберите ключ сортировки:\n");
    printf("1 - По имени и фамилии\n");
    printf("2 - По номеру телефона\n");
    printf("Введите ваш выбор: ");
    scanf("%d", &choice);

    if (choice == 1) {
        InsertSort(phoneBook, size, CompareByName);
        printf("\nСправочник отсортирован по имени и фамилии:\n");
    } else if (choice == 2) {
        InsertSort(phoneBook, size, CompareByPhone);
        printf("\nСправочник отсортирован по номеру телефона:\n");
    } else {
        printf("Неверный выбор. Сортировка не выполнена.\n");
        return 1;
    }

    PrintPhoneBook(phoneBook, size);

    return 0;
}