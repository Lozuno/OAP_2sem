#include "Hach_chain.h"
#include <iostream>
using namespace std;

// Структура данных для хранения в хеш-таблице
struct AAA
{
    char* mas;   // номер счета
    char* fio;   // ФИО
    AAA(char* account = nullptr, char* name = nullptr) : mas(account), fio(name) {}
};

// Хеш-функция (возвращает ключ)
int hf(void* d)
{
    AAA* f = (AAA*)d;
    char* s = f->mas;
    unsigned int hash = 0;

    // Вычисление XOR-хеша
    for (int i = 0; s[i] != '\0'; i++)
    {
        hash = (hash << 4) ^ (hash >> 28) ^ s[i]; // Комбинация сдвигов и XOR
    }
    return (int)(hash & 0x7FFFFFFF); // Гарантия положительного числа
}

// Вывод элемента списка
void AAA_print(listx::Element* e)
{
    std::cout << hf(((AAA*)e->data)) << '-' << ((AAA*)e->data)->mas << " / ";
}

int main()
{
    setlocale(LC_ALL, "rus");
    int current_size;
    cout << "Введите размер хеш-таблицы" << endl;
    cin >> current_size;

    hashTC::Object H = hashTC::create(current_size, hf);

    int choice;
    for (;;)
    {
        cout << "1 - вывод хеш-таблицы" << endl;
        cout << "2 - добавление элемента" << endl;
        cout << "3 - удаление элемента" << endl;
        cout << "4 - поиск элемента" << endl;
        cout << "0 - выход" << endl;
        cout << "сделайте выбор" << endl;
        cin >> choice;

        switch (choice)
        {
        case 0: exit(0);
        case 1: H.Scan(); break;

        case 2: { // Добавлен ввод ФИО
            char* account = new char[20];
            char* fio = new char[100];

            cout << "Введите номер счета: ";
            cin >> account;

            cout << "Введите ФИО: ";
            cin.ignore(); // Очистка буфера
            cin.getline(fio, 100); // Чтение с пробелами

            H.insert(new AAA(account, fio));
            break;
        }

        case 3: { // Удаление по номеру счета
            char* str = new char[20];
            cout << "Введите номер счета: ";
            cin >> str;

            AAA* temp = new AAA(str);
            H.deleteByData(temp);

            delete temp;
            delete[] str;
            break;
        }

        case 4: { // Поиск по номеру счета
            char* str = new char[20];
            cout << "Введите номер счета: ";
            cin >> str;

            AAA* temp = new AAA(str);
            listx::Element* result = H.search(temp);

            if (result) {
                AAA* found = (AAA*)result->data;
                cout << "Найден: " << found->mas << " - " << found->fio << endl;
            }
            else {
                cout << "Не найден" << endl;
            }

            delete temp;
            delete[] str;
            break;
        }
        }
    }
    return 0;
}