#include "Hach_chain.h"
#include <iostream>

namespace hashTC
{
    // �������� ���-�������
    Object create(int size, int(*f)(void*))
    {
        return *(new Object(size, f));
    }

    // ���������� ���-�������
    int Object::hashFunction(void* data)
    {
        return (FunKey(data) % size); // ������� �� ������� �� ������ �������
    };

    // ������� �������� � ���-�������
    bool Object::insert(void* data)
    {
        return (Hash[hashFunction(data)].insert(data)); // ������� � ��������������� ������
    };

    // �������� �������� �� ���-�������
    bool Object::deleteByData(void* data)
    {
        return (Hash[hashFunction(data)].deleteByData(data)); // �������� �� ���������������� ������
    };

    // ����� �������� � ���-�������
    listx::Element* Object::search(void* data)
    {
        return Hash[hashFunction(data)].search(data); // ����� � ��������������� ������
    };

    // ����� ����������� ���-�������
    void Object::Scan()
    {
        for (int i = 0; i < size; i++)
        {
            Hash[i].scan(); // ����� ������� ������
            std::cout << '\n';
        }
    };
}