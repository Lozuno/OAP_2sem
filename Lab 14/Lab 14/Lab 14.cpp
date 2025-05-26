#include "Hash.h"
#include <iostream>
#include <chrono>    // Добавляем заголовок для chrono  
#include <cstdlib>
#include <cstdio>

#define _CRT_SECURE_NO_WARNINGS  // Отключаем предупреждения безопасности CRT

using namespace std;

struct AAA {
    int key;
    char* mas;
    AAA(int k, char* z) : key(k), mas(z) {}
    AAA() : key(0), mas(nullptr) {}
};

int key(void* d) {
    return ((AAA*)d)->key;
}

int main() {
    setlocale(LC_ALL, "rus");
    const int tableSizes[] = { 16, 32, 64, 128 };
    const int numSizes = sizeof(tableSizes) / sizeof(tableSizes[0]);
    const int numElements = 1000;
    const int collisionsFactor = 5;

    for (int s = 0; s < numSizes; s++) {
        int size = tableSizes[s];
        Object H = create(size, key);

        int* keys = new int[numElements];
        int keysCount = 0;

        srand(time(0));
        for (int i = 0; i < numElements; ++i) {
            AAA* a = new AAA;
            a->key = rand() % (size / collisionsFactor);
            a->mas = new char[20];
            snprintf(a->mas, 20, "Element%d", i);  // Безопасная версия

            if (H.insert(a)) {
                if (keysCount < numElements) {
                    keys[keysCount++] = a->key;
                }
            }
            else {
                delete[] a->mas;
                delete a;
            }
        }

        // Замер времени через chrono
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < keysCount; ++i) {
            H.search(keys[i]);
        }
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;

        cout << "Размер таблицы: " << size
            << " | Элементов: " << H.N
            << " | Время поиска: " <<fixed<< double(duration.count()) << " сек\n";

        // Очистка памяти
        for (int i = 0; i < size; ++i) {
            if (H.data[i] && H.data[i] != DEL) {
                delete[]((AAA*)H.data[i])->mas;
                delete (AAA*)H.data[i];
            }
        }
        delete[] keys;
    }
    return 0;
}