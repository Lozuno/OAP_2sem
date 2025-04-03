#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

union NotebookEntry {
    char lastName[50];
    char firstName[50];
    char middleName[50];
    char birthDate[15];
    char address[100];
    char phone[20];
    char workplace[50];
    char position[50];
};

void writeToFile(const char* filename) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }
    NotebookEntry entry;
    char lastName[50], firstName[50], middleName[50], birthDate[15], address[100], phone[20], workplace[50], position[50];

    cout << "Введите фамилию: ";
    cin >> lastName;
    strncpy_s(entry.lastName, lastName, sizeof(entry.lastName) - 1);
    fout << entry.lastName << "\t";

    cout << "Введите имя: ";
    cin >> firstName;
    strncpy_s(entry.firstName, firstName, sizeof(entry.firstName) - 1);
    fout << entry.firstName << "\t";

    cout << "Введите отчество: ";
    cin >> middleName;
    strncpy_s(entry.middleName, middleName, sizeof(entry.middleName) - 1);
    fout << entry.middleName << "\t";

    cout << "Введите дату рождения (ДД.ММ.ГГГГ): ";
    cin >> birthDate;
    strncpy_s(entry.birthDate, birthDate, sizeof(entry.birthDate) - 1);
    fout << entry.birthDate << "\t";

    cout << "Введите адрес: ";
    cin >> address;
    strncpy_s(entry.address, address, sizeof(entry.address) - 1);
    fout << entry.address << "\t";

    cout << "Введите телефон: ";
    cin >> phone;
    strncpy_s(entry.phone, phone, sizeof(entry.phone) - 1);
    fout << entry.phone << "\t";

    cout << "Введите место работы/учебы: ";
    cin >> workplace;
    strncpy_s(entry.workplace, workplace, sizeof(entry.workplace) - 1);
    fout << entry.workplace << "\t";

    cout << "Введите должность: ";
    cin >> position;
    strncpy_s(entry.position, position, sizeof(entry.position) - 1);
    fout << entry.position << '\n';

    fout.close();
}

void readFromFile(const char* filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }
    NotebookEntry entry;

    cout << left << setw(20) << "Фамилия" << setw(20) << "Имя" << setw(20) << "Отчество"
        << setw(15) << "Дата рождения" << setw(25) << "Адрес" << setw(15) << "Телефон"
        << setw(15) << "Место работы/учебы" << setw(20) << "Должность" << endl;

    while (!fin.fail()) {
        fin >> entry.lastName;
        if (fin.fail()) break;
        char lastName[50];
        strncpy_s(lastName, entry.lastName, sizeof(lastName) - 1);

        fin >> entry.firstName;
        if (fin.fail()) break;
        char firstName[50];
        strncpy_s(firstName, entry.firstName, sizeof(firstName) - 1);

        fin >> entry.middleName;
        if (fin.fail()) break;
        char middleName[50];
        strncpy_s(middleName, entry.middleName, sizeof(middleName) - 1);

        fin >> entry.birthDate;
        if (fin.fail()) break;
        char birthDate[15];
        strncpy_s(birthDate, entry.birthDate, sizeof(birthDate) - 1);

        fin >> entry.address;
        if (fin.fail()) break;
        char address[100];
        strncpy_s(address, entry.address, sizeof(address) - 1);

        fin >> entry.phone;
        if (fin.fail()) break;
        char phone[20];
        strncpy_s(phone, entry.phone, sizeof(phone) - 1);

        fin >> entry.workplace;
        if (fin.fail()) break;
        char workplace[50];
        strncpy_s(workplace, entry.workplace, sizeof(workplace) - 1);

        fin >> entry.position;
        if (fin.fail()) break;
        char position[50];
        strncpy_s(position, entry.position, sizeof(position) - 1);

        cout << left << setw(20) << lastName << setw(20) << firstName << setw(20) << middleName
            << setw(15) << birthDate << setw(25) << address << setw(15) << phone
            << setw(15) << workplace << setw(20) << position << endl;
    }
    fin.close();
}

void searchByLastName(const char* filename, const char* searchLastName) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }
    NotebookEntry entry;
    bool found = false;
    int i = 0;
    while (!fin.fail()) {
        i++;
        fin >> entry.lastName;
        if (fin.fail()) break;
        if (strcmp(entry.lastName, searchLastName) == 0) {
            fin >> entry.firstName >> entry.middleName >> entry.birthDate >> entry.address >> entry.phone >> entry.workplace >> entry.position;
            cout << "Запись найдена: " << i;
            found = true;
        }
    }
    if (!found) {
        cout << "Совпадений не найдено." << endl;
    }
    fin.close();
}

int main() {
    setlocale(LC_ALL, "rus");
    const char filename[] = "notebook.txt";
    int choice;
    do {
        cout << "\n1. Ввод данных с клавиатуры и запись в файл" << endl;
        cout << "2. Вывод данных из файла" << endl;
        cout << "3. Поиск по фамилии" << endl;
        cout << "0. Выход" << endl;
        cout << "Введите номер операции: ";
        cin >> choice;
        switch (choice) {
        case 1:
            writeToFile(filename);
            break;
        case 2:
            readFromFile(filename);
            break;
        case 3: {
            char searchLastName[50];
            cout << "Введите фамилию для поиска: ";
            cin >> searchLastName;
            searchByLastName(filename, searchLastName);
            break;
        }
        case 0:
            break;
        default:
            cout << "Неверный ввод!" << endl;
        }
    } while (choice != 0);
    return 0;
}