#pragma once
// Объявление структуры AAA с целочисленным полем x и методом print()
struct AAA
{
    int x;            // Целочисленное поле для хранения данных
    void print();     // Метод для вывода значения x на экран
};

// Пространство имен для работы с кучей
namespace heap
{
    // Перечисление для сравнения элементов (LESS - меньше, EQUAL - равно, GREAT - больше)
    enum CMP
    {
        LESS = -1,
        EQUAL = 0,
        GREAT = 1
    };

    // Структура, представляющая кучу (пирамиду)
    struct Heap
    {
        int size;                  // Текущий размер кучи
        int maxSize;               // Максимальный размер кучи
        void** storage;           // Массив для хранения элементов (указателей на void)
        CMP(*compare)(void*, void*);  // Указатель на функцию сравнения элементов

        // Конструктор кучи
        Heap(int maxsize, CMP(*f)(void*, void*))
        {
            size = 0;
            storage = new void* [maxSize = maxsize];  // Выделение памяти под массив
            compare = f;                            // Инициализация функции сравнения
        };

        // Методы кучи:
        int left(int ix);      // Получить индекс левого потомка
        int right(int ix);     // Получить индекс правого потомка
        int parent(int ix);   // Получить индекс родителя

        // Проверка, заполнена ли куча
        bool isFull() const { return (size >= maxSize); };

        // Проверка, пуста ли куча
        bool isEmpty() const { return (size <= 0); };

        // Сравнение элементов через функцию сравнения
        bool isLess(void* x1, void* x2) const { return compare(x1, x2) == LESS; };
        bool isGreat(void* x1, void* x2) const { return compare(x1, x2) == GREAT; };
        bool isEqual(void* x1, void* x2) const { return compare(x1, x2) == EQUAL; };

        void swap(int i, int j);    // Обмен элементов местами
        void heapify(int ix);       // Восстановление свойств кучи
        void insert(void* x);       // Вставка нового элемента
        void* extractMax();         // Извлечение максимального элемента
        void scan(int i) const;     // Вывод кучи на экран
    };

    // Функция создания кучи
    Heap create(int maxsize, CMP(*f)(void*, void*));
};
