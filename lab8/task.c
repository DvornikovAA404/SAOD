#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char firstName[50];
    char lastName[50];
    char phoneNumber[20];
    char address[100];
} PhoneBookEntry;

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

    PrintPhoneBook(phoneBook, size);

    return 0;
}