
#include "Heap.h"
#include <iostream>
#include <iomanip>

// Реализация метода print() для структуры AAA
void AAA::print()
{
    std::cout << x;   // Просто выводим значение x
}

// Реализация методов кучи
namespace heap
{
    // Создание новой кучи
    Heap create(int maxsize, CMP(*f)(void*, void*))
    {
        return *(new Heap(maxsize, f));  // Создаем и возвращаем новую кучу
    }

    // Получение индекса левого потомка
    int Heap::left(int ix)
    {
        return (2 * ix + 1 >= size) ? -1 : (2 * ix + 1);  // -1 если потомка нет
    }

    // Получение индекса правого потомка
    int Heap::right(int ix)
    {
        return (2 * ix + 2 >= size) ? -1 : (2 * ix + 2);  // -1 если потомка нет
    }

    // Получение индекса родителя
    int Heap::parent(int ix)
    {
        return (ix + 1) / 2 - 1;  // Формула для расчета индекса родителя
    }

    // Обмен элементов местами
    void Heap::swap(int i, int j)
    {
        void* buf = storage[i];   // Временное хранение элемента i
        storage[i] = storage[j];  // Перемещение элемента j на место i
        storage[j] = buf;         // Перемещение элемента i на место j
    }

    // Восстановление свойств кучи (просеивание вниз)
    void Heap::heapify(int ix)
    {
        int l = left(ix), r = right(ix), irl = ix;  // Индексы левого, правого потомков и наибольшего элемента
        if (l > 0)  // Если левый потомок существует
        {
            if (isGreat(storage[l], storage[ix])) irl = l;  // Если левый больше текущего
            if (r > 0 && isGreat(storage[r], storage[irl])) irl = r;  // Если правый больше наибольшего
            if (irl != ix)  // Если наибольший не текущий
            {
                swap(ix, irl);      // Меняем местами
                heapify(irl);      // Рекурсивно вызываем для нового положения
            }
        }
    }

    // Вставка нового элемента
    void Heap::insert(void* x)
    {
        int i;
        if (!isFull())  // Если куча не заполнена
        {
            storage[i = ++size - 1] = x;  // Добавляем элемент в конец
            // Просеивание вверх
            while (i > 0 && isLess(storage[parent(i)], storage[i]))
            {
                swap(parent(i), i);  // Меняем с родителем
                i = parent(i);       // Переходим к родителю
            }
        }
    }

    // Извлечение максимального элемента
    void* Heap::extractMax()
    {
        void* rc = nullptr;
        if (!isEmpty())  // Если куча не пуста
        {
            rc = storage[0];        // Максимальный элемент - корень
            storage[0] = storage[size - 1];  // Перемещаем последний элемент в корень
            size--;                // Уменьшаем размер
            heapify(0);            // Восстанавливаем свойства кучи
        }
        return rc;  // Возвращаем максимальный элемент
    }

    // Вывод кучи на экран в виде дерева
    void Heap::scan(int i) const
    {
        int probel = 20;  // Начальное количество пробелов для форматирования
        std::cout << '\n';
        if (size == 0)  // Если куча пуста
            std::cout << "Куча пуста";
        // Вывод элементов с форматированием
        for (int u = 0, y = 0; u < size; u++)
        {
            std::cout << std::setw(probel + 10) << std::setfill(' ');
            ((AAA*)storage[u])->print();  // Вывод элемента
            if (u == y)  // Переход на новую строку для нового уровня дерева
            {
                std::cout << '\n';
                if (y == 0)
                    y = 2;
                else
                    y += y * 2;
            }
            probel /= 2;  // Уменьшение отступа для следующих уровней
        }
        std::cout << '\n';
    }
}
