#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

struct Date {
    unsigned int day : 5;
    unsigned int month : 4;
    unsigned int year : 12;
};

struct Teacher {
    char lastName[50];
    char examName[50];
    Date examDate;
};

void readTeacher(Teacher teachers[], int& size) {
    cout << "Введите фамилию преподавателя: ";
    cin.getline(teachers[size].lastName, 50);
    cout << "Введите название экзамена: ";
    cin.getline(teachers[size].examName, 50);
    cout << "Введите дату экзамена (день месяц год): ";
    unsigned int d, m, y;
    cin >> d >> m >> y;
    teachers[size].examDate = { d,m,y };
    cin.ignore();
    size++;
}

void writeTeachers(Teacher teachers[], int size) {
    cout << left << setw(20) << "Фамилия" << setw(30) << "Название экзамена" << setw(15) << "Дата экзамена" << endl;
    for (int i = 0; i < size; i++) {
        cout << left << setw(20) << teachers[i].lastName
            << setw(30) << teachers[i].examName
            << setw(2) << teachers[i].examDate.day << '.' << setw(2) << teachers[i].examDate.month << '.' << setw(8) << teachers[i].examDate.year << endl;
    }
}

int searchTeacher(Teacher teachers[], int size, Date date) {
    for (int i = 0; i < size; i++) {
        if (teachers[i].examDate.day == date.day && teachers[i].examDate.month == date.month && teachers[i].examDate.year == date.year) {
            return i;
        }
    }
    return -1;
}

int main() {
    setlocale(LC_ALL, "rus");
    Teacher teachers[20];
    int size = 0, choice;
    do {
        cout << "\n1. Добавить преподавателя\n";
        cout << "2. Вывести список преподавателей\n";
        cout << "3. Поиск по дате экзамена\n";
        cout << "0. Выход\n";
        cout << "Выберите операцию: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1:
            readTeacher(teachers, size);
            break;
        case 2:
            writeTeachers(teachers, size);
            break;
        case 3: {
            cout << "Введите дату экзамена (день месяц год): ";
            unsigned int d, m, y;
            cin >> d >> m >> y;
            Date date = { d,m,y };
            int index = searchTeacher(teachers, size, date);
            if (index == -1) {
                cout << "Преподаватель не найден\n";
            }
            else {
                cout << "Преподаватель: " << teachers[index].lastName << ", экзамен: " << teachers[index].examName << "\n";
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
