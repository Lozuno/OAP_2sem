#pragma once
// ���������� ��������� AAA � ������������� ����� x � ������� print()
struct AAA
{
    int x;            // ������������� ���� ��� �������� ������
    void print();     // ����� ��� ������ �������� x �� �����
};

// ������������ ���� ��� ������ � �����
namespace heap
{
    // ������������ ��� ��������� ��������� (LESS - ������, EQUAL - �����, GREAT - ������)
    enum CMP
    {
        LESS = -1,
        EQUAL = 0,
        GREAT = 1
    };

    // ���������, �������������� ���� (��������)
    struct Heap
    {
        int size;                  // ������� ������ ����
        int maxSize;               // ������������ ������ ����
        void** storage;           // ������ ��� �������� ��������� (���������� �� void)
        CMP(*compare)(void*, void*);  // ��������� �� ������� ��������� ���������

        // ����������� ����
        Heap(int maxsize, CMP(*f)(void*, void*))
        {
            size = 0;
            storage = new void* [maxSize = maxsize];  // ��������� ������ ��� ������
            compare = f;                            // ������������� ������� ���������
        };

        // ������ ����:
        int left(int ix);      // �������� ������ ������ �������
        int right(int ix);     // �������� ������ ������� �������
        int parent(int ix);   // �������� ������ ��������

        // ��������, ��������� �� ����
        bool isFull() const { return (size >= maxSize); };

        // ��������, ����� �� ����
        bool isEmpty() const { return (size <= 0); };

        // ��������� ��������� ����� ������� ���������
        bool isLess(void* x1, void* x2) const { return compare(x1, x2) == LESS; };
        bool isGreat(void* x1, void* x2) const { return compare(x1, x2) == GREAT; };
        bool isEqual(void* x1, void* x2) const { return compare(x1, x2) == EQUAL; };

        void swap(int i, int j);    // ����� ��������� �������
        void heapify(int ix);       // �������������� ������� ����
        void insert(void* x);       // ������� ������ ��������
        void* extractMax();         // ���������� ������������� ��������
        void scan(int i) const;     // ����� ���� �� �����
    };

    // ������� �������� ����
    Heap create(int maxsize, CMP(*f)(void*, void*));
};
