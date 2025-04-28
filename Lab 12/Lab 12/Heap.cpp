#include "Heap.h"
#include <iostream>
#include <iomanip>

void AAA::print()
{
    std::cout << x;
}

namespace heap
{
    Heap create(int maxsize, CMP(*f)(void*, void*))
    {
        return Heap(maxsize, f);
    }

    int Heap::left(int ix)
    {
        int idx = 2 * ix + 1;
        return (idx < size) ? idx : -1;
    }

    int Heap::right(int ix)
    {
        int idx = 2 * ix + 2;
        return (idx < size) ? idx : -1;
    }

    int Heap::parent(int ix)
    {
        return (ix > 0) ? (ix - 1) / 2 : -1;
    }

    void Heap::swap(int i, int j)
    {
        void* buf = storage[i];
        storage[i] = storage[j];
        storage[j] = buf;
    }

    void Heap::heapify(int ix)
    {
        int largest = ix;
        int l = left(ix), r = right(ix);

        if (l != -1 && isGreat(storage[l], storage[largest]))
            largest = l;
        if (r != -1 && isGreat(storage[r], storage[largest]))
            largest = r;

        if (largest != ix)
        {
            swap(ix, largest);
            heapify(largest);
        }
    }

    void Heap::insert(void* x)
    {
        if (isFull())
            return;

        int i = size++;
        storage[i] = x;

        int p = parent(i);
        while (p != -1 && isLess(storage[p], storage[i]))
        {
            swap(p, i);
            i = p;
            p = parent(i);
        }
    }

    void* Heap::extractMax()
    {
        if (isEmpty())
            return nullptr;

        void* rc = storage[0];
        storage[0] = storage[--size];
        heapify(0);
        return rc;
    }

    void Heap::scan(int i) const     //Вывод значений элементов на экран
    {
        int probel = 20;
        std::cout << '\n';
        if (size == 0)
            std::cout << "Куча пуста";
        for (int u = 0, y = 0; u < size; u++)
        {
            std::cout << std::setw(probel + 10) << std::setfill(' ');
            ((AAA*)storage[u])->print();
            if (u == y)
            {
                std::cout << '\n';
                if (y == 0)
                    y = 2;
                else
                    y += y * 2;
            }
            probel /= 2;
        }
        std::cout << '\n';
    }

    void Heap::minHeapify(int ix)
    {
        int smallest = ix;
        int l = left(ix), r = right(ix);

        if (l != -1 && isLess(storage[l], storage[smallest]))
            smallest = l;
        if (r != -1 && isLess(storage[r], storage[smallest]))
            smallest = r;

        if (smallest != ix)
        {
            swap(ix, smallest);
            minHeapify(smallest);
        }
    }

    void* Heap::extractMin()
    {
        if (isEmpty())
            return nullptr;

        int minIdx = 0;
        for (int i = 1; i < size; ++i) {
            if (isLess(storage[i], storage[minIdx]))
                minIdx = i;
        }

        void* rc = extractI(minIdx);

        return rc;
    }


    void* Heap::extractI(int i)
    {
        if (i < 0 || i >= size)
            return nullptr;

        void* rc = storage[i];
        storage[i] = storage[--size];

       
        heapify(i);
        
        return rc;
    }

    Heap unionHeap(Heap a, Heap b)
    {
        
        Heap ans = create(a.maxSize + b.maxSize, a.compare);
        ans.size = a.size + b.size;
        for (int i = 0; i < a.size; ++i)
            ans.storage[i] = a.storage[i];
        for (int j = 0; j < b.size; ++j)
            ans.storage[a.size + j] = b.storage[j];
        for (int k = (ans.size - 2) / 2; k >= 0; --k)
            ans.heapify(k);
        return ans;
    }

}
