#include "List.h"


struct Person
{
	char name[20];
	int age;
	Person* next;
};

void print(void* b)       //Функция используется при выводе 
{
	Person* a = (Person*)b;
	cout << a->name << "  " << a->age << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Person a1 = { "Петров", 20 };
	Person a2 = { "Сидоров", 25 };
	Person a3 = { "Гончаров", 47 };
	bool rc;
	Object L1 = Create();   // создание списка с именем L1
	L1.Insert(&a1);
	L1.Insert(&a2);
	L1.Insert(&a3);
	L1.PrintList(print);
	Element* e = L1.Search(&a3);
	Person* aa = (Person*)e->Data;
	cout << "Найден элемент= " << aa->name << endl;
	rc = L1.Delete(&a2);
	if (rc == true) cout << "Удален элемент" << endl;
	cout << "Список:" << endl;
	L1.PrintList(print);
	return 0;
}