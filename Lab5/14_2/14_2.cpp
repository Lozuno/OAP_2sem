#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

union HotelGuest {
    char passportData[50];
    char lastName[50];
    char firstName[50];
    char middleName[50];
    char checkInDate[15];
    char checkOutDate[15];
    char roomNumber[10];
    char roomType[20];
};

void writeToFile(const char* filename) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }
    HotelGuest guest;
    char passportData[50], lastName[50], firstName[50], middleName[50], checkInDate[15], checkOutDate[15], roomNumber[10], roomType[20];

    cout << "Введите паспортные данные: ";
    cin >> passportData;
    strncpy_s(guest.passportData, passportData, sizeof(guest.passportData) - 1);
    fout << guest.passportData << "\t";

    cout << "Введите фамилию: ";
    cin >> lastName;
    strncpy_s(guest.lastName, lastName, sizeof(guest.lastName) - 1);
    fout << guest.lastName << "\t";

    cout << "Введите имя: ";
    cin >> firstName;
    strncpy_s(guest.firstName, firstName, sizeof(guest.firstName) - 1);
    fout << guest.firstName << "\t";

    cout << "Введите отчество: ";
    cin >> middleName;
    strncpy_s(guest.middleName, middleName, sizeof(guest.middleName) - 1);
    fout << guest.middleName << "\t";

    cout << "Введите дату приезда (ДД.ММ.ГГГГ): ";
    cin >> checkInDate;
    strncpy_s(guest.checkInDate, checkInDate, sizeof(guest.checkInDate) - 1);
    fout << guest.checkInDate << "\t";

    cout << "Введите дату отъезда (ДД.ММ.ГГГГ): ";
    cin >> checkOutDate;
    strncpy_s(guest.checkOutDate, checkOutDate, sizeof(guest.checkOutDate) - 1);
    fout << guest.checkOutDate << "\t";

    cout << "Введите номер комнаты: ";
    cin >> roomNumber;
    strncpy_s(guest.roomNumber, roomNumber, sizeof(guest.roomNumber) - 1);
    fout << guest.roomNumber << "\t";

    cout << "Введите тип размещения (люкс, одноместный, двухместный, трехместный, апартаменты): ";
    cin >> roomType;
    strncpy_s(guest.roomType, roomType, sizeof(guest.roomType) - 1);
    fout << guest.roomType << '\n';

    fout.close();
}

void readFromFile(const char* filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }
    HotelGuest guest;

    cout << left << setw(20) << "Паспортные данные" << setw(20) << "Фамилия" << setw(20) << "Имя"
        << setw(20) << "Отчество" << setw(15) << "Дата приезда" << setw(15) << "Дата отъезда"
        << setw(10) << "Номер" << setw(20) << "Тип размещения" << endl;

    while (!fin.fail()) {
        fin >> guest.passportData;
        if (fin.fail()) break;
        char passportData[50];
        strncpy_s(passportData, guest.passportData, sizeof(passportData) - 1);

        fin >> guest.lastName;
        if (fin.fail()) break;
        char lastName[50];
        strncpy_s(lastName, guest.lastName, sizeof(lastName) - 1);

        fin >> guest.firstName;
        if (fin.fail()) break;
        char firstName[50];
        strncpy_s(firstName, guest.firstName, sizeof(firstName) - 1);

        fin >> guest.middleName;
        if (fin.fail()) break;
        char middleName[50];
        strncpy_s(middleName, guest.middleName, sizeof(middleName) - 1);

        fin >> guest.checkInDate;
        if (fin.fail()) break;
        char checkInDate[15];
        strncpy_s(checkInDate, guest.checkInDate, sizeof(checkInDate) - 1);

        fin >> guest.checkOutDate;
        if (fin.fail()) break;
        char checkOutDate[15];
        strncpy_s(checkOutDate, guest.checkOutDate, sizeof(checkOutDate) - 1);

        fin >> guest.roomNumber;
        if (fin.fail()) break;
        char roomNumber[10];
        strncpy_s(roomNumber, guest.roomNumber, sizeof(roomNumber) - 1);

        fin >> guest.roomType;
        if (fin.fail()) break;
        char roomType[20];
        strncpy_s(roomType, guest.roomType, sizeof(roomType) - 1);

        cout << left << setw(20) << passportData << setw(20) << lastName << setw(20) << firstName
            << setw(20) << middleName << setw(15) << checkInDate << setw(15) << checkOutDate
            << setw(10) << roomNumber << setw(20) << roomType << endl;
    }
    fin.close();
}

void searchByLastName(const char* filename, const char* searchLastName) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }
    HotelGuest guest;
    bool found = false;
    int i = 0;
    while (!fin.fail()) {
        i++;
        fin >> guest.passportData >> guest.lastName;
        if (strcmp(guest.lastName, searchLastName) == 0) {
            fin >> guest.firstName >> guest.middleName >> guest.checkInDate >> guest.checkOutDate >> guest.roomNumber >> guest.roomType;
            cout << "Гость номер: " << i;
            found = true;
        }
    }
    if (!found) {
        cout << "Гость не найден." << endl;
    }
    fin.close();
}

int main() {
    setlocale(LC_ALL, "rus");
    const char filename[] = "hotel_guests.txt";
    int choice;
    do {
        cout << "\n1. Добавить гостя\n";
        cout << "2. Вывести список гостей\n";
        cout << "3. Поиск по фамилии\n";
        cout << "0. Выход\n";
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
