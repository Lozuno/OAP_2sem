#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

union Citizen {
    char lastName[50];
    char firstName[50];
    char middleName[50];
    char birthDate[15];
    char address[100];
    char gender;
};

void writeToFile(const char* filename) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }
    Citizen citizen;
    char lastName[50], firstName[50], middleName[50], birthDate[15], address[100];
    char gender;

    cout << "Введите фамилию: ";
    cin >> lastName;
    strncpy_s(citizen.lastName, lastName, sizeof(citizen.lastName) - 1);
    fout << citizen.lastName << "\t";

    cout << "Введите имя: ";
    cin >> firstName;
    strncpy_s(citizen.firstName, firstName, sizeof(citizen.firstName) - 1);
    fout << citizen.firstName << "\t";

    cout << "Введите отчество: ";
    cin >> middleName;
    strncpy_s(citizen.middleName, middleName, sizeof(citizen.middleName) - 1);
    fout << citizen.middleName << "\t";

    cout << "Введите дату рождения (ДД.ММ.ГГГГ): ";
    cin >> birthDate;
    strncpy_s(citizen.birthDate, birthDate, sizeof(citizen.birthDate) - 1);
    fout << citizen.birthDate << "\t";

    cout << "Введите адрес: ";
    cin >> address;
    strncpy_s(citizen.address, address, sizeof(citizen.address) - 1);
    fout << citizen.address << "\t";

    cout << "Введите пол (м/ж): ";
    cin >> gender;
    citizen.gender = gender;
    fout << citizen.gender << '\n';

    fout.close();
}

void readFromFile(const char* filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }
    Citizen citizen;

    cout << left << setw(20) << "Фамилия" << setw(20) << "Имя" << setw(20) << "Отчество"
        << setw(15) << "Дата рождения" << setw(40) << "Адрес" << setw(5) << "Пол" << endl;

    // Reading data using a while loop with fin.fail check
    while (!fin.fail()) {
        fin >> citizen.lastName;
        if (fin.fail()) break;
        char lastName[50];
        strncpy_s(lastName, citizen.lastName, sizeof(lastName) - 1);

        fin >> citizen.firstName;
        if (fin.fail()) break;
        char firstName[50];
        strncpy_s(firstName, citizen.firstName, sizeof(firstName) - 1);

        fin >> citizen.middleName;
        if (fin.fail()) break;
        char middleName[50];
        strncpy_s(middleName, citizen.middleName, sizeof(middleName) - 1);

        fin >> citizen.birthDate;
        if (fin.fail()) break;
        char birthDate[15];
        strncpy_s(birthDate, citizen.birthDate, sizeof(birthDate) - 1);

        fin >> citizen.address;
        if (fin.fail()) break;
        char address[100];
        strncpy_s(address, citizen.address, sizeof(address) - 1);

        fin >> citizen.gender;
        if (fin.fail()) break;
        char gender = citizen.gender;

        // Output the data
        cout << left << setw(20) << lastName << setw(20) << firstName << setw(20) << middleName
            << setw(15) << birthDate << setw(40) << address << setw(5) << gender << endl;

    }
    fin.close();
}

void searchByYear(const char* filename, const char* year) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }
    Citizen citizen;
    bool found = false;

    cout << "Результаты поиска по году " << year << ":\n";

    // Loop through file and search for year in birth date
    while (!fin.fail()) {
        fin >> citizen.lastName;
        if (fin.fail()) break;
        char lastName[50];
        strncpy_s(lastName, citizen.lastName, sizeof(lastName) - 1);

        fin >> citizen.firstName;
        if (fin.fail()) break;
        char firstName[50];
        strncpy_s(firstName, citizen.firstName, sizeof(firstName) - 1);

        fin >> citizen.middleName;
        if (fin.fail()) break;
        char middleName[50];
        strncpy_s(middleName, citizen.middleName, sizeof(middleName) - 1);

        fin >> citizen.birthDate;
        if (fin.fail()) break;
        char birthDate[15];
        strncpy_s(birthDate, citizen.birthDate, sizeof(birthDate) - 1);

        fin >> citizen.address;
        if (fin.fail()) break;
        char address[100];
        strncpy_s(address, citizen.address, sizeof(address) - 1);

        fin >> citizen.gender;
        if (fin.fail()) break;
        char gender = citizen.gender;

        // Check if the year is in the birthDate
        if (strstr(birthDate, year)) {
            cout << left << setw(20) << lastName << setw(20) << firstName << setw(20) << middleName
                << setw(15) << birthDate << setw(40) << address << setw(5) << gender << endl;
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
    const char filename[] = "citizens.txt";
    int choice;
    do {
        cout << "\n1. Ввод данных с клавиатуры и запись в файл" << endl;
        cout << "2. Вывод данных из файла" << endl;
        cout << "3. Поиск по году рождения" << endl;
        cout << "0. Выход" << endl;
        cout << "Введите номер операции: ";
        cin >> choice;
        cin.ignore();  // To handle the newline after choice input
        switch (choice) {
        case 1:
            writeToFile(filename);
            break;
        case 2:
            readFromFile(filename);
            break;
        case 3: {
            char year[5];
            cout << "Введите год для поиска: ";
            cin >> year;
            searchByYear(filename, year);
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
