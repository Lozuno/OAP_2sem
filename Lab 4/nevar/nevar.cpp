#include <iostream>
using namespace std;

// Функции для ввода, вывода и поиска данных о студентах
void input(int size);
void output();
void find(char lastName[]);

// Структура для хранения информации о студенте
typedef struct Students {
    char fio[16];    // Фамилия студента
    char group[3];   // Группа студента
} STUD;

int number;          // Количество студентов
FILE* f;            // Указатель на файл
errno_t err;       // Переменная для хранения кода ошибки

int main() {
    setlocale(LC_ALL, "Russian"); // Установка локали для работы с русским языком
    int choice;                   // Переменная для хранения выбора пользователя
    char fio[16];                 // Переменная для хранения фамилии

    do {
        // Меню программы
        cout << "\n1.Ввод данных с клавиатуры и запись в файл\n";
        cout << "2.Вывод данных из файла\n";
        cout << "3.Поиск по фамилии\n";
        cout << "0.Выход из программы\n\n";
        cout << "Введите номер операции: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите количество студентов: ";
            cin >> number;
            input(number);
            break;
        case 2:
            output();
            break;
        case 3: {
            cout << "Введите фамилию: ";
            cin >> fio;
            find(fio);
            break;
        }
        case 0:
            exit(0);
            break;
        }
    } while (choice != 0);
}

// Функция для ввода данных о студентах
void input(int size) {
    STUD buf = { ' ', ' ' };  // Инициализация структуры студента
    if (!fopen_s(&f, "base.bin", "ab")) { // Открытие файла для добавления данных
        for (int p = 0; p < size; p++) {
            cout << "Фамилия: ";
            cin >> buf.fio; // Ввод фамилии
            cout << "Группа: ";
            cin >> buf.group; // Ввод группы
            fwrite(&buf, sizeof(buf), 1, f); // Запись данных в файл
        }
        fclose(f); // Закрытие файла
    }
    else {
        cout << "Ошибка открытия файла"; // Обработка ошибки открытия файла
        return;
    }
}

// Функция для вывода данных о студентах
void output() {
    STUD buf; // Структура для хранения данных из файла
    if (!fopen_s(&f, "base.bin", "rb")) { // Открытие файла для чтения
        cout << "\nФамилия    Группа\n";
        fread(&buf, sizeof(buf), 1, f); // Чтение данных из файла
        while (!feof(f)) {
            cout << buf.fio << "\t    " << buf.group << endl; // Вывод данных
            fread(&buf, sizeof(buf), 1, f); // Чтение следующей записи
        }
        cout << endl;
        fclose(f); // Закрытие файла
    }
    else {
        cout << "Ошибка открытия файла"; // Обработка ошибки открытия файла
        return;
    }
}

// Функция для поиска студента по фамилии
void find(char lastName[16]) {
    bool flag = false;  // Флаг для отслеживания нахождения студента
    STUD buf;           // Структура для хранения данных из файла
    if (!fopen_s(&f, "base.bin", "rb")) { // Открытие файла для чтения
        while (!feof(f)) {
            fread(&buf, sizeof(buf), 1, f); // Чтение данных из файла
            if (strcmp(lastName, buf.fio) == 0) { // Сравнение фамилий
                cout << "\nФамилия    Группа\n";
                cout << buf.fio << "\t    " << buf.group << endl; // Вывод найденного студента
                flag = true;
                break;
            }
        }
        fclose(f); // Закрытие файла
        if (!flag)
            cout << "Ничего не найдено\n"; // Если студент не найден
    }
    else {
        cout << "Ошибка открытия файла"; // Обработка ошибки открытия файла
        return;
    }
}