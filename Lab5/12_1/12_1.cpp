#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

struct Date {
    unsigned int day : 5;
    unsigned int month : 4;
    unsigned int year : 12;
};

struct Contact {
    char fullName[50];
    Date birthDate;
    char address[100];
    char phone[20];
};

void readContact(Contact contacts[], int& size) {
    cout << "Введите Ф.И.О.: ";
    cin.getline(contacts[size].fullName, 50);
    cout << "Введите дату рождения (день месяц год): ";
    unsigned int d, m, y;
    cin >> d >> m >> y;
    contacts[size].birthDate = { d, m, y };
    cin.ignore();
    cout << "Введите адрес: ";
    cin.getline(contacts[size].address, 100);
    cout << "Введите телефон: ";
    cin.getline(contacts[size].phone, 20);
    size++;
}

void writeContacts(Contact contacts[], int size) {
    cout << left << setw(30) << "Ф.И.О." << setw(15) << "Дата рождения" << setw(30) << "Адрес" << setw(15) << "Телефон" << endl;
    for (int i = 0; i < size; i++) {
        cout << left << setw(30) << contacts[i].fullName << setw(2) << contacts[i].birthDate.day << "." << setw(2) << contacts[i].birthDate.month << "." << setw(10) << contacts[i].birthDate.year << setw(30) << contacts[i].address << setw(15) << contacts[i].phone << endl;
    }
}

int searchContact(Contact contacts[], int size, const char* lastName) {
    for (int i = 0; i < size; i++) {
        if (strncmp(contacts[i].fullName, lastName, strlen(lastName)) == 0) {
            return i;
        }
    }
    return -1;
}

void deleteContact(Contact contacts[], int& size, int index) {
    for (int i = index; i < size - 1; i++) {
        contacts[i] = contacts[i + 1];
    }
    size--;
}

int main() {
    setlocale(LC_ALL, "rus");
    Contact contacts[20];
    int size = 0, choice;
    do {
        cout << "\n1. Добавить контакт\n";
        cout << "2. Вывести контакты\n";
        cout << "3. Поиск по фамилии\n";
        cout << "4. Удалить контакт\n";
        cout << "0. Выход\n";
        cout << "Выберите операцию: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1:
            readContact(contacts, size);
            break;
        case 2:
            writeContacts(contacts, size);
            break;
        case 3: {
            cout << "Введите фамилию для поиска: ";
            char lastName[50];
            cin.getline(lastName, 50);
            int index = searchContact(contacts, size, lastName);
            if (index == -1) {
                cout << "Контакт не найден\n";
            }
            else {
                cout << "Контакт найден: " << index+1<< "\n";
            }
            break;
        }
        case 4:
            cout << "Введите номер контакта для удаления: ";
            int num;
            cin >> num;
            if (num > 0 && num <= size) {
                deleteContact(contacts, size, num - 1);
                cout << "Контакт удален\n";
            }
            else {
                cout << "Некорректный номер\n";
            }
            break;
        case 0:
            break;
        default:
            cout << "Неверный ввод\n";
            break;
        }
    } while (choice != 0);
    return 0;
}
