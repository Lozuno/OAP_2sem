
#include "Heap.h"
#include <iostream>
#include <iomanip>

// ���������� ������ print() ��� ��������� AAA
void AAA::print()
{
    std::cout << x;   // ������ ������� �������� x
}

// ���������� ������� ����
namespace heap
{
    // �������� ����� ����
    Heap create(int maxsize, CMP(*f)(void*, void*))
    {
        return *(new Heap(maxsize, f));  // ������� � ���������� ����� ����
    }

    // ��������� ������� ������ �������
    int Heap::left(int ix)
    {
        return (2 * ix + 1 >= size) ? -1 : (2 * ix + 1);  // -1 ���� ������� ���
    }

    // ��������� ������� ������� �������
    int Heap::right(int ix)
    {
        return (2 * ix + 2 >= size) ? -1 : (2 * ix + 2);  // -1 ���� ������� ���
    }

    // ��������� ������� ��������
    int Heap::parent(int ix)
    {
        return (ix + 1) / 2 - 1;  // ������� ��� ������� ������� ��������
    }

    // ����� ��������� �������
    void Heap::swap(int i, int j)
    {
        void* buf = storage[i];   // ��������� �������� �������� i
        storage[i] = storage[j];  // ����������� �������� j �� ����� i
        storage[j] = buf;         // ����������� �������� i �� ����� j
    }

    // �������������� ������� ���� (����������� ����)
    void Heap::heapify(int ix)
    {
        int l = left(ix), r = right(ix), irl = ix;  // ������� ������, ������� �������� � ����������� ��������
        if (l > 0)  // ���� ����� ������� ����������
        {
            if (isGreat(storage[l], storage[ix])) irl = l;  // ���� ����� ������ ��������
            if (r > 0 && isGreat(storage[r], storage[irl])) irl = r;  // ���� ������ ������ �����������
            if (irl != ix)  // ���� ���������� �� �������
            {
                swap(ix, irl);      // ������ �������
                heapify(irl);      // ���������� �������� ��� ������ ���������
            }
        }
    }

    // ������� ������ ��������
    void Heap::insert(void* x)
    {
        int i;
        if (!isFull())  // ���� ���� �� ���������
        {
            storage[i = ++size - 1] = x;  // ��������� ������� � �����
            // ����������� �����
            while (i > 0 && isLess(storage[parent(i)], storage[i]))
            {
                swap(parent(i), i);  // ������ � ���������
                i = parent(i);       // ��������� � ��������
            }
        }
    }

    // ���������� ������������� ��������
    void* Heap::extractMax()
    {
        void* rc = nullptr;
        if (!isEmpty())  // ���� ���� �� �����
        {
            rc = storage[0];        // ������������ ������� - ������
            storage[0] = storage[size - 1];  // ���������� ��������� ������� � ������
            size--;                // ��������� ������
            heapify(0);            // ��������������� �������� ����
        }
        return rc;  // ���������� ������������ �������
    }

    // ����� ���� �� ����� � ���� ������
    void Heap::scan(int i) const
    {
        int probel = 20;  // ��������� ���������� �������� ��� ��������������
        std::cout << '\n';
        if (size == 0)  // ���� ���� �����
            std::cout << "���� �����";
        // ����� ��������� � ���������������
        for (int u = 0, y = 0; u < size; u++)
        {
            std::cout << std::setw(probel + 10) << std::setfill(' ');
            ((AAA*)storage[u])->print();  // ����� ��������
            if (u == y)  // ������� �� ����� ������ ��� ������ ������ ������
            {
                std::cout << '\n';
                if (y == 0)
                    y = 2;
                else
                    y += y * 2;
            }
            probel /= 2;  // ���������� ������� ��� ��������� �������
        }
        std::cout << '\n';
    }
}
