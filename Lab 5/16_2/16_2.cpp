#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

union Student {
    char lastName[50];
    char firstName[50];
    char middleName[50];
    char admissionDate[15];
    char specialty[50];
    char group[10];
    char faculty[50];
    double averageGrade;
};

void writeToFile(const char* filename) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }
    Student student;

    cout << "Введите фамилию: ";
    cin >> student.lastName;
    fout << student.lastName << "\t";

    cout << "Введите имя: ";
    cin >> student.firstName;
    fout << student.firstName << "\t";

    cout << "Введите отчество: ";
    cin >> student.middleName;
    fout << student.middleName << "\t";

    cout << "Введите дату поступления (ДД.ММ.ГГГГ): ";
    cin >> student.admissionDate;
    fout << student.admissionDate << "\t";

    cout << "Введите специальность: ";
    cin >> student.specialty;
    fout << student.specialty << "\t";

    cout << "Введите группу: ";
    cin >> student.group;
    fout << student.group << "\t";

    cout << "Введите факультет: ";
    cin >> student.faculty;
    fout << student.faculty << "\t";

    cout << "Введите средний балл: ";
    cin >> student.averageGrade;
    fout << student.averageGrade << '\n';

    fout.close();
}

void readFromFile(const char* filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }
    Student student;

    cout << left << setw(20) << "Фамилия" << setw(20) << "Имя" << setw(20) << "Отчество"
        << setw(15) << "Дата поступления" << setw(25) << "Специальность"
        << setw(10) << "Группа" << setw(20) << "Факультет" << setw(10) << "Средний балл" << endl;

    while (!fin.fail()) {
        fin >> student.lastName;
        if (fin.fail()) break;
        char lastName[50];
        strncpy_s(lastName, student.lastName, sizeof(lastName) - 1);

        fin >> student.firstName;
        if (fin.fail()) break;
        char firstName[50];
        strncpy_s(firstName, student.firstName, sizeof(firstName) - 1);

        fin >> student.middleName;
        if (fin.fail()) break;
        char middleName[50];
        strncpy_s(middleName, student.middleName, sizeof(middleName) - 1);

        fin >> student.admissionDate;
        if (fin.fail()) break;
        char admissionDate[15];
        strncpy_s(admissionDate, student.admissionDate, sizeof(admissionDate) - 1);

        fin >> student.specialty;
        if (fin.fail()) break;
        char specialty[50];
        strncpy_s(specialty, student.specialty, sizeof(specialty) - 1);

        fin >> student.group;
        if (fin.fail()) break;
        char group[10];
        strncpy_s(group, student.group, sizeof(group) - 1);

        fin >> student.faculty;
        if (fin.fail()) break;
        char faculty[50];
        strncpy_s(faculty, student.faculty, sizeof(faculty) - 1);

        fin >> student.averageGrade;
        if (fin.fail()) break;

        cout << left << setw(20) << lastName << setw(20) << firstName << setw(20) << middleName
            << setw(15) << admissionDate << setw(25) << specialty << setw(10) << group
            << setw(20) << faculty << setw(10) << student.averageGrade << endl;
    }
    fin.close();
}

void searchByAverageGrade(const char* filename, double minGrade) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }
    Student student;
    bool found = false;
    int i = 0;
    while (!fin.fail()) {
        fin >> student.lastName >> student.firstName >> student.middleName;
        fin >> student.admissionDate >> student.specialty >> student.group >> student.faculty >> student.averageGrade;
        i++;
        if (fin.fail()) break;

        if (student.averageGrade == minGrade) {
            cout << "Студент номер: " << i;
            found = true;
        }
    }

    if (!found) {
        cout << "Студенты с указанным средним баллом не найдены." << endl;
    }
    fin.close();
}

int main() {
    setlocale(LC_ALL, "rus");
    const char filename[] = "students.txt";
    int choice;
    do {
        cout << "\n1. Добавить студента\n";
        cout << "2. Вывести список студентов\n";
        cout << "3. Поиск по среднему баллу\n";
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
            double minGrade;
            cout << "Введите минимальный средний балл для поиска: ";
            cin >> minGrade;
            searchByAverageGrade(filename, minGrade);
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
