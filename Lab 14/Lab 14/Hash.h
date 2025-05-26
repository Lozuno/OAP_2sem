#pragma once
#define HASHDEL (void*) -1  // Маркер для удаленных элементов
#define _CRT_SECURE_NO_WARNINGS
// Структура хеш-таблицы
struct Object
{
	void** data;            // Массив указателей на данные
	Object(int, int(*)(void*)); // Конструктор
	int size;   // Общий размер таблицы
	int N;      // Количество элементов
	int(*getKey)(void*);    // Функция получения ключа

	// Методы:
	bool insert(void*);         // Вставка элемента
	int searchInd(int key);     // Поиск индекса по ключу
	void* search(int key);      // Поиск данных по ключу
	void* deleteByKey(int key); // Удаление по ключу
	bool deleteByValue(void*);  // Удаление по значению
	void scan(void(*f)(void*)); // Вывод содержимого
};

static void* DEL = (void*)HASHDEL; // Маркер удаления
Object create(int size, int(*getkey)(void*)); // Фабрика создания таблицы
#undef HASHDEL