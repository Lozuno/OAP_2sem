    
#include "Heap.h"
#include <iostream>
using namespace std;

// Функция сравнения для структуры AAA
heap::CMP cmpAAA(void* a1, void* a2)
{
#define A1 ((AAA*)a1)  // Приведение типа для удобства
#define A2 ((AAA*)a2)
    heap::CMP rc = heap::EQUAL;  // По умолчанию элементы равны
    if (A1->x > A2->x)
        rc = heap::GREAT;  // Первый элемент больше
    else if (A2->x > A1->x)
        rc = heap::LESS;   // Первый элемент меньше
    return rc;
#undef A2
#undef A1 
}

// Главная функция с меню для тестирования кучи
int main()
{
    setlocale(LC_ALL, "rus");  // Установка русской локали
    int k, choice;
    heap::Heap h1 = heap::create(30, cmpAAA);  // Создание кучи

    // Бесконечный цикл меню
    for (;;)
    {
        cout << "1 - вывод кучи на экран" << endl;
        cout << "2 - добавить элемент" << endl;
        cout << "3 - удалить максимальный элемент" << endl;
        cout << "0 - выход" << endl;
        cout << "сделайте выбор" << endl;
        cin >> choice;

        switch (choice)
        {
        case 0:  exit(0);  // Выход из программы
        case 1:  h1.scan(0);  // Вывод кучи
            break;
        case 2:
        {
            AAA* a = new AAA;  // Создание нового элемента
            cout << "введите ключ" << endl;
            cin >> k;
            a->x = k;          // Установка значения
            h1.insert(a);      // Вставка в кучу
        }
        break;
        case 3:   h1.extractMax();  // Удаление максимального элемента
            break;
        default:  cout << endl << "Введена неверная команда!" << endl;
        }
    }
    return 0;
}