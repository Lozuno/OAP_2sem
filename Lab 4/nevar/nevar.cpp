#include <iostream>
using namespace std;

// Объявление функций
void input(int size); // Функция для ввода данных студентов
void output();        // Функция для вывода данных студентов
void find(char lastName[]); // Функция для поиска студента по фамилии

// Определение структуры для хранения информации о студентах
typedef struct Students
{
    char fio[16];   // Фамилия студента
    char group[3];  // Группа студента
} STUD;

int number; // Количество студентов
FILE* f;    // Указатель на файл
errno_t err; // Переменная для хранения ошибок

int main()
{
    setlocale(LC_ALL, "Russian"); // Установка локали для корректного отображения русских символов
    int choice;
    char fio[16]; // Переменная для хранения фамилии студента

    do
    {
        // Меню выбора операции
        cout << "\n1.Ввод данных с клавиатуры и запись в файл\n";
        cout << "2.Вывод данных из файла\n";
        cout << "3.Поиск по фамилии\n";
        cout << "0.Выход из программы\n\n";
        cout << "Введите номер операции: ";

        cin >> choice; // Получение выбора пользователя

        switch (choice)
        {
        case 1: // Ввод данных
            cout << "Введите количество студентов: ";
            cin >> number; // Получение количества студентов
            input(number);  // Вызов функции для ввода данных
            break;
        case 2:
            output(); // Вызов функции для вывода данных
            break;
        case 3: {
            cout << "Введите фамилию: ";
            cin >> fio; // Получение фамилии для поиска
            find(fio); // Вызов функции для поиска студента
            break;
        }
        case 0:
            exit(0); // Завершение работы программы
            break;
        }
    } while (choice != 0); // Цикл продолжается, пока пользователь не выберет выход
}

void input(int size)
{
    STUD buf = { ' ', ' ' }; // Инициализация структуры для ввода данных

    // Открытие файла для добавления данных
    if (!fopen_s(&f, "base.bin", "ab"))
    {
        for (int p = 0; p < size; p++)
        {
            cout << "Фамилия: ";
            cin >> buf.fio; // Ввод фамилии
            cout << "Группа: ";
            cin >> buf.group; // Ввод группы
            fwrite(&buf, sizeof(buf), 1, f); // Запись данных в файл
        }
        fclose(f); // Закрытие файла
    }
    else
    {
        cout << "Ошибка открытия файла"; // Сообщение об ошибке
        return;
    }
}

void output()
{
    STUD buf;

    // Открытие файла для чтения данных
    if (!fopen_s(&f, "base.bin", "rb"))
    {
        cout << "\nФамилия    Группа\n";
        fread(&buf, sizeof(buf), 1, f); // Чтение первой записи

        while (!feof(f)) // Чтение до конца файла
        {
            cout << buf.fio << "\t    " << buf.group << endl; // Вывод данных
            fread(&buf, sizeof(buf), 1, f); // Чтение следующей записи
        }
        cout << endl;
        fclose(f); // Закрытие файла
    }
    else
    {
        cout << "Ошибка открытия файла"; // Сообщение об ошибке
        return;
    }
}

void find(char lastName[16])
{
    bool flag = false;
    STUD buf;

    // Открытие файла для поиска данных
    if (!fopen_s(&f, "base.bin", "rb"))
    {
        while (!feof(f)) // Чтение до конца файла
        {
            fread(&buf, sizeof(buf), 1, f); // Чтение записи

            if (strcmp(lastName, buf.fio) == 0) // Сравнение фамилий
            {
                cout << "\nФамилия    Группа\n";
                cout << buf.fio << "\t    " << buf.group << endl; // Вывод найденных данных
                flag = true;
                break; // Выход из цикла, если найдено совпадение
            }
        }
        fclose(f); // Закрытие файла

        if (!flag) cout << "Ничего не найдено\n"; // Сообщение, если ничего не найдено
    }
    else
    {
        cout << "Ошибка открытия файла"; // Сообщение об ошибке
        return;
    }
}