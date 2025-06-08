#include "Hach_chain.h"
#include <iostream>

namespace hashTC
{
    // Создание хеш-таблицы
    Object create(int size, int(*f)(void*))
    {
        return *(new Object(size, f));
    }

    // Вычисление хеш-функции
    int Object::hashFunction(void* data)
    {
        return (FunKey(data) % size); // Остаток от деления на размер таблицы
    };

    // Вставка элемента в хеш-таблицу
    bool Object::insert(void* data)
    {
        return (Hash[hashFunction(data)].insert(data)); // Вставка в соответствующий список
    };

    // Удаление элемента из хеш-таблицы
    bool Object::deleteByData(void* data)
    {
        return (Hash[hashFunction(data)].deleteByData(data)); // Удаление из соответствующего списка
    };

    // Поиск элемента в хеш-таблице
    listx::Element* Object::search(void* data)
    {
        return Hash[hashFunction(data)].search(data); // Поиск в соответствующем списке
    };

    // Вывод содержимого хеш-таблицы
    void Object::Scan()
    {
        for (int i = 0; i < size; i++)
        {
            Hash[i].scan(); // Вывод каждого списка
            std::cout << '\n';
        }
    };
}