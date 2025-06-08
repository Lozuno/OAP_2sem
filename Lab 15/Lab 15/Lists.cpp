#include "Lists.h"
#include <cstring> 
#include <iostream>

// Структура данных, хранимая в таблице (ключ + строка)
struct AAA
{
    char* mas;   // номер счета
    char* fio;   // ФИО (добавленное поле)
    AAA(char* account, char* name) : mas(account), fio(name) {}
    AAA() : mas(nullptr), fio(nullptr) {}
};

namespace listx
{
    // Вставка элемента в список
    bool Object::insert(void* data)
    {
        bool rc = NULL;
        if (head == NULL)
            head = new Element(NULL, data, head); // Вставка в пустой список
        else
            head = (head->prev = new Element(NULL, data, head)); // Вставка в начало
        return rc;
    }

    // Поиск элемента в списке по ключу
    Element* Object::search(void* data)
    {
        Element* rc = head;
        AAA* searchData = (AAA*)data;

        while (rc != nullptr)
        {
            AAA* currentData = (AAA*)rc->data;
            if (strcmp(currentData->mas, searchData->mas) == 0)
                break;
            rc = rc->next;
        }
        return rc;
    }
    // Вывод содержимого списка
    void Object::scan()
    {
        Element* e = head;
        while (e != nullptr)
        {
            AAA* item = (AAA*)e->data;
            std::cout << item->mas << " - " << item->fio << " / ";
            e = e->next;
        }
    }

    // Удаление элемента по указателю
    bool Object::deleteByElement(Element* e)
    {
        if (e == nullptr) return false;

        if (e->next) e->next->prev = e->prev;
        if (e->prev) e->prev->next = e->next;
        else head = e->next;

        AAA* data = (AAA*)(e->data);
        delete[] data->mas;  // Освобождение номера счета
        delete[] data->fio;  // Освобождение ФИО (добавлено)
        delete data;         // Освобождение структуры
        delete e;            // Освобождение элемента

        std::cout << "Элемент удален" << std::endl;
        return true;
    }

    // Удаление элемента по данным
    bool Object::deleteByData(void* data)
    {
        return deleteByElement(search(data));
    }

    // Получение последнего элемента списка
    Element* Object::getLast()
    {
        listx::Element* e = this->getFirst(), * rc = this->getFirst();
        while (e != NULL)
        {
            rc = e;
            e = e->getNext();
        };
        return rc;
    }

    // Создание нового списка
    Object create()
    {
        return *(new Object());
    };
}