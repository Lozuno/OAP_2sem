#include "Hash.h"
#include <iostream>

// Хеш-функция с использованием метода умножения
int HashFunction(int key, int size, int p)
{
	// Константы из исследования хеширования для таблиц размера 2^k
	const uint32_t A = 2654435769; // (sqrt(5)-1)/2 * 2^32
	const uint32_t BITS = 32;

	// Умножение на константу и взятие старших битов
	uint32_t hash = (uint32_t)key * A;
	hash >>= (BITS - (int)log2(size)); // Используем log2 так как size=2^k

	// Добавляем квадратичное пробирование
	return (hash + p + p * p) % size;
}
//-------------------------------
// Функция разрешения коллизий (квадратичное пробирование)
int Next_hash(int hash, int size, int p)
{
	return (hash + p + p*p) % size; // Квадратичная последовательность
}
//-------------------------------
// Фабричный метод создания таблицы
Object create(int size, int(*getkey)(void*))
{
	return *(new Object(size, getkey));
}
//-------------------------------
// Конструктор объекта таблицы
Object::Object(int size, int(*getkey)(void*))
{
	N = 0;                // Инициализация счетчика элементов
	this->size = size;    // Установка размера таблицы
	this->getKey = getkey;// Сохранение функции получения ключа
	this->data = new void* [size]; // Выделение памяти
	for (int i = 0; i < size; ++i)
		data[i] = NULL;   // Инициализация ячеек
}
//-------------------------------
// Метод вставки элемента
bool Object::insert(void* d)
{
	bool b = false;
	if (N != size) // Проверка на переполнение
		// Цикл пробирования с использованием хеш-функций
		for (int i = 0, t = getKey(d), j = HashFunction(t, size, 0);
			i != size && !b;
			j = Next_hash(j, size, ++i))
			if (data[j] == NULL || data[j] == DEL) // Поиск свободной ячейки
			{
				data[j] = d;  // Вставка элемента
				N++;          // Увеличение счетчика
				b = true;     // Флаг успешной вставки
			}
	return b;
}
//-------------------------------
// Поиск индекса элемента по ключу
int Object::searchInd(int key)
{
	int t = -1; // Индекс не найден
	bool b = false;
	if (N != 0) // Проверка на пустую таблицу
		// Цикл пробирования с двойным хешированием
		for (int i = 0, j = HashFunction(key, size, 0);
			data[j] != NULL && i != size && !b;
			j = HashFunction(key, size, ++i))
			if (data[j] != DEL) // Пропуск удаленных элементов
				if (getKey(data[j]) == key) // Проверка совпадения ключа
				{
					t = j; b = true; // Найденный индекс
				}
	return t;
}
//-------------------------------
// Поиск элемента по ключу и возвращение его данных
void* Object::search(int key)
{
	int t = searchInd(key); // Получаем индекс через searchInd
	return(t >= 0) ? (data[t]) : (NULL); // Возвращаем данные или NULL
}
//-------------------------------
// Удаление элемента по ключу (логическое удаление)
void* Object::deleteByKey(int key)
{
	int i = searchInd(key); // Поиск индекса элемента
	void* t = data[i]; // Сохранение указателя на данные
	if (t != NULL)
	{
		data[i] = DEL; // Помечаем ячейку как удаленную
		N--; // Уменьшаем счетчик элементов
	}
	return t; // Возвращаем удаленные данные (или NULL)
}
//-------------------------------
// Удаление элемента по значению
bool Object::deleteByValue(void* d)
{
	// Используем deleteByKey, преобразуя значение в ключ
	return(deleteByKey(getKey(d)) != NULL);
}
//-------------------------------
// Вывод содержимого таблицы с пользовательским форматированием
void Object::scan(void(*f)(void*))
{
	for (int i = 0; i < this->size; i++)
	{
		std::cout << " Элемент " << i;
		// Обработка трех состояний ячейки:
		if ((this->data)[i] == NULL)
			std::cout << "  пусто" << std::endl; // Пустая ячейка
		else if ((this->data)[i] == DEL)
			std::cout << "  удален" << std::endl; // Удаленный элемент
		else
			f((this->data)[i]); // Вызов пользовательской функции печати
	}
}