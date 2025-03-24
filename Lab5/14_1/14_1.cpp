#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

struct Date {
    unsigned day : 5;
    unsigned month : 4;
    unsigned year : 12;
};

enum RoomType { LUXURY, SINGLE, DOUBLE, TRIPLE, APARTMENT };

struct Guest {
    char passportData[50];
    Date arrivalDate;
    Date departureDate;
    int roomNumber;
    RoomType roomType;
};

void handleEnum(char temp[50], Guest guests[], int size) {
    if (strcmp("luxury", temp) == 0) { guests[size].roomType = LUXURY; }
    if (strcmp("single", temp) == 0) { guests[size].roomType = SINGLE; }
    if (strcmp("double", temp) == 0) { guests[size].roomType = DOUBLE; }
    if (strcmp("triple", temp) == 0) { guests[size].roomType = TRIPLE; }
    if (strcmp("apartment", temp) == 0) { guests[size].roomType = APARTMENT; }
}

const char* writeEnum(RoomType type, char temp[50]) {
    switch (type) {
    case LUXURY: strcpy_s(temp, 50, "luxury"); break;
    case SINGLE: strcpy_s(temp, 50, "single"); break;
    case DOUBLE: strcpy_s(temp, 50, "double"); break;
    case TRIPLE: strcpy_s(temp, 50, "triple"); break;
    case APARTMENT: strcpy_s(temp, 50, "apartment"); break;
    default: strcpy_s(temp, 50, "unknown"); break;
    }
    return temp;
}

void readGuest(Guest guests[], int& size) {
    cout << "Введите паспортные данные: ";
    cin.getline(guests[size].passportData, 50);
    cout << "Введите дату приезда (день месяц год): ";

    unsigned int d, m, y;
    cin >> d >> m >> y;
    guests[size].arrivalDate = { d,m,y };
    cout << "Введите дату отъезда (день месяц год): ";
    cin >> d >> m >> y;
    guests[size].departureDate= { d,m,y };
    cout << "Введите номер комнаты: ";
    cin >> guests[size].roomNumber;
    cin.ignore();
    cout << "Введите тип размещения (luxury, single, double, triple, apartment): ";
    char temp[50];
    cin.getline(temp, 50);
    handleEnum(temp, guests, size);
    size++;
}

void writeGuests(Guest guests[], int size) {
    cout << left << setw(20) << "Паспортные данные" << setw(15) << "Дата приезда" << setw(15) << "Дата отъезда" << setw(10) << "Комната" << setw(15) << "Тип" << endl;
    for (int i = 0; i < size; i++) {
        char temp[50];
        cout << left << setw(20) << guests[i].passportData
            << setw(2) << guests[i].arrivalDate.day << '.' << setw(2) << guests[i].arrivalDate.month << '.' << setw(8) << guests[i].arrivalDate.year
            << setw(2) << guests[i].departureDate.day << '.' << setw(2) << guests[i].departureDate.month << '.' << setw(8) << guests[i].departureDate.year
            << setw(10) << guests[i].roomNumber
            << setw(15) << writeEnum(guests[i].roomType, temp) << endl;
    }
}

int searchGuest(Guest guests[], int size, Date date) {
    for (int i = 0; i < size; i++) {
        if (guests[i].arrivalDate.day == date.day && guests[i].arrivalDate.month == date.month && guests[i].arrivalDate.year == date.year) {
            return i;
        }
    }
    return -1;
}

int main() {
    setlocale(LC_ALL, "rus");
    Guest guests[20];
    int size = 0, choice;
    do {
        cout << "\n1. Добавить гостя\n";
        cout << "2. Вывести гостей\n";
        cout << "3. Поиск гостя по дате приезда\n";
        cout << "0. Выход\n";
        cout << "Выберите операцию: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1:
            readGuest(guests, size);
            break;
        case 2:
            writeGuests(guests, size);
            break;
        case 3: {
            cout << "Введите дату приезда (день месяц год): ";
            
            unsigned int d, m, y;
            cin >> d >> m >> y;
            Date date = { d,m,y };
            int index = searchGuest(guests, size, date);
            if (index == -1) {
                cout << "Гость не найден\n";
            }
            else {
                cout << "Гость номер: " << index << "\n";
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "Неверный ввод\n";
            break;
        }
    } while (choice != 0);
    return 0;
}
