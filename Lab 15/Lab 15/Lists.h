#pragma once              // Заголовочный файл для реализации связного списка
#define LISTNIL (Element*)-1

namespace listx
{
    // Элемент связного списка
    struct Element
    {
        Element* prev;  // Указатель на предыдущий элемент
        Element* next;  // Указатель на следующий элемент
        void* data;     // Указатель на данные

        // Конструктор элемента списка
        Element(Element* pr, void* dat, Element* nt)
        {
            prev = pr;
            data = dat;
            next = nt;
        }

        // Получение следующего элемента
        Element* getNext() { return next; };

        // Получение предыдущего элемента
        Element* getPrev() { return prev; };
    };

    static Element* NIL = nullptr; // Специальное значение "NIL" (пустой указатель)

    // Структура, представляющая связный список
    struct Object
    {
        Element* head;  // Указатель на голову списка

        // Конструктор списка
        Object() { head = NIL; };

        // Получение первого элемента
        Element* getFirst() { return head; };

        // Получение последнего элемента
        Element* getLast();

        // Поиск элемента по данным
        Element* search(void* data);

        // Вставка элемента в список
        bool insert(void* data);

        // Удаление элемента по указателю
        bool deleteByElement(Element* e);

        // Удаление элемента по данным
        bool deleteByData(void* data);

        // Вывод содержимого списка
        void scan();
    };

    // Функция создания списка
    Object create();
}

#undef LISTNIL 