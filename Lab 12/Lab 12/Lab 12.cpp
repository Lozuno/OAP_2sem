#include "Heap.h"
#include <iostream>
#include <ctime>
#include <locale>
heap::CMP cmpAAA(void* a1, void* a2)  //Функция сравнения
{
#define A1 ((AAA*)a1)
#define A2 ((AAA*)a2)
    heap::CMP
        rc = heap::EQUAL;
    if (A1->x > A2->x)
        rc = heap::GREAT;
    else
        if (A2->x > A1->x)
            rc = heap::LESS;
    return rc;
#undef A2
#undef A1 
}

int main()
{
    setlocale(LC_ALL, "rus");
    int choice;
    heap::Heap mainHeap = heap::create(30, cmpAAA);   // Основная куча
    heap::Heap secondHeap = heap::create(30, cmpAAA); // Вторая куча для объединения

    // Инициализация основной кучи примерами
    for (int i = 0; i < 5; i++)
    {
        AAA* a = new AAA;
        a->x = rand() % 100;
        mainHeap.insert(a);
    }

    do
    {
        std::cout << "\n1. Добавить элемент в основную кучу";
        std::cout << "\n2. Извлечь максимальный элемент";
        std::cout << "\n3. Вывести основную кучу";
        std::cout << "\n4. Извлечь минимальный элемент";
        std::cout << "\n5. Извлечь элемент по индексу";
        std::cout << "\n6. Заполнить вторую кучу для объединения";
        std::cout << "\n7. Объединить кучи";
        std::cout << "\n8. Выход";
        std::cout << "\nВаш выбор: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1: // Добавление элемента
        {
            AAA* a = new AAA;
            std::cout << "Введите целое число: ";
            std::cin >> a->x;
            mainHeap.insert(a);
            break;
        }
        case 2: // Извлечение максимума
        {
            AAA* a = (AAA*)mainHeap.extractMax();
            if (a)
            {
                std::cout << "Извлечен максимум: " << a->x << std::endl;
                delete a;
            }
            else
                std::cout << "Куча пуста!" << std::endl;
            break;
        }
        case 3: // Вывод кучи
            mainHeap.scan(0);
            break;
        case 4: // Извлечение минимума
        {
            AAA* a = (AAA*)mainHeap.extractMin();
            if (a)
            {
                std::cout << "Извлечен минимум: " << a->x << std::endl;
                delete a;
            }
            else
                std::cout << "Куча пуста!" << std::endl;
            break;
        }
        case 5: // Извлечение по индексу
        {
            int idx;
            std::cout << "Введите индекс: ";
            std::cin >> idx;
            if (idx >= 0 && idx < mainHeap.size)
            {
                AAA* a = (AAA*)mainHeap.extractI(idx);
                if (a)
                {
                    std::cout << "Извлечен элемент " << a->x << std::endl;
                    delete a;
                }
            }
            else
                std::cout << "Неверный индекс!" << std::endl;
            break;
        }
        case 6: // Заполнение второй кучи
            for (int i = 0; i < 5; i++)
            {
                AAA* a = new AAA;
                a->x = rand() % 100;
                secondHeap.insert(a);
            }
            std::cout << "Вторая куча создана!" << std::endl;
            secondHeap.scan(0);
            break;
        case 7:{ // Объединение куч
            mainHeap = heap::unionHeap(mainHeap, secondHeap);
            std::cout << "Объединенная куча:" << std::endl;
            mainHeap.scan(0);
            break;
        }
        case 8: // Выход
            exit(0);
        default:
            std::cout << "Ошибка ввода!" << std::endl;
        }
    } while (true);

    return 0;
}