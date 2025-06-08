#pragma once            // Заголовочный файл для хеш-таблицы с цепочками (метод разрешения коллизий)
#include "Lists.h"

namespace hashTC
{
    // Структура, представляющая хеш-таблицу
    struct Object
    {
        int size;               // Размер хеш-таблицы
        int(*FunKey)(void*);   // Указатель на хеш-функцию
        listx::Object* Hash;    // Массив связных списков для хранения данных

        // Конструктор хеш-таблицы
        Object(int siz, int(*f)(void*))
        {
            size = siz;
            FunKey = f;
            Hash = new listx::Object[size]; // Инициализация массива списков
        };

        int hashFunction(void* data);    // Вычисление хеша для данных
        bool insert(void* data);        // Вставка элемента
        listx::Element* search(void* data); // Поиск элемента
        bool deleteByData(void* data);   // Удаление элемента по данным
        void Scan();                    // Вывод содержимого таблицы
    };

    // Функция создания хеш-таблицы
    Object create(int size, int(*f)(void*));
}