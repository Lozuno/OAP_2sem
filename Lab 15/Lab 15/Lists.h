#pragma once              // ������������ ���� ��� ���������� �������� ������
#define LISTNIL (Element*)-1

namespace listx
{
    // ������� �������� ������
    struct Element
    {
        Element* prev;  // ��������� �� ���������� �������
        Element* next;  // ��������� �� ��������� �������
        void* data;     // ��������� �� ������

        // ����������� �������� ������
        Element(Element* pr, void* dat, Element* nt)
        {
            prev = pr;
            data = dat;
            next = nt;
        }

        // ��������� ���������� ��������
        Element* getNext() { return next; };

        // ��������� ����������� ��������
        Element* getPrev() { return prev; };
    };

    static Element* NIL = nullptr; // ����������� �������� "NIL" (������ ���������)

    // ���������, �������������� ������� ������
    struct Object
    {
        Element* head;  // ��������� �� ������ ������

        // ����������� ������
        Object() { head = NIL; };

        // ��������� ������� ��������
        Element* getFirst() { return head; };

        // ��������� ���������� ��������
        Element* getLast();

        // ����� �������� �� ������
        Element* search(void* data);

        // ������� �������� � ������
        bool insert(void* data);

        // �������� �������� �� ���������
        bool deleteByElement(Element* e);

        // �������� �������� �� ������
        bool deleteByData(void* data);

        // ����� ����������� ������
        void scan();
    };

    // ������� �������� ������
    Object create();
}

#undef LISTNIL 