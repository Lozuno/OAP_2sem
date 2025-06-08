#include "Lists.h"
#include <cstring> 
#include <iostream>

// ��������� ������, �������� � ������� (���� + ������)
struct AAA
{
    char* mas;   // ����� �����
    char* fio;   // ��� (����������� ����)
    AAA(char* account, char* name) : mas(account), fio(name) {}
    AAA() : mas(nullptr), fio(nullptr) {}
};

namespace listx
{
    // ������� �������� � ������
    bool Object::insert(void* data)
    {
        bool rc = NULL;
        if (head == NULL)
            head = new Element(NULL, data, head); // ������� � ������ ������
        else
            head = (head->prev = new Element(NULL, data, head)); // ������� � ������
        return rc;
    }

    // ����� �������� � ������ �� �����
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
    // ����� ����������� ������
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

    // �������� �������� �� ���������
    bool Object::deleteByElement(Element* e)
    {
        if (e == nullptr) return false;

        if (e->next) e->next->prev = e->prev;
        if (e->prev) e->prev->next = e->next;
        else head = e->next;

        AAA* data = (AAA*)(e->data);
        delete[] data->mas;  // ������������ ������ �����
        delete[] data->fio;  // ������������ ��� (���������)
        delete data;         // ������������ ���������
        delete e;            // ������������ ��������

        std::cout << "������� ������" << std::endl;
        return true;
    }

    // �������� �������� �� ������
    bool Object::deleteByData(void* data)
    {
        return deleteByElement(search(data));
    }

    // ��������� ���������� �������� ������
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

    // �������� ������ ������
    Object create()
    {
        return *(new Object());
    };
}