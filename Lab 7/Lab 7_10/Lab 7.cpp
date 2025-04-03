#include <iostream>
#include "myStack.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	int choice; int x;
	Stack* myStk = NULL, * stack1 = new Stack, * stack2 = new Stack; //выделение памяти для стека
	cout << "Выберите стек для заполнения (0/1)" << endl;
	stack1 = NULL;
	stack2 = NULL;
	bool k;
	cin >> k;
	if (k) {
		myStk = stack2;
	}
	else {
		myStk = stack1;
	}

	for (;;) {
		cout << "Выберите команду:" << endl;
		cout << "0 - Выход" << endl;
		cout << "1 - Добавление элемента в стек" << endl;
		cout << "2 - Извлечение элемента из стека" << endl;
		cout << "3 - Запись в файл" << endl;
		cout << "4 - Чтение из файла" << endl;
		cout << "5 - Вывод стека с очисткой" << endl;
		cout << "6 - Найти элемент в заданном диапазоне" << endl;
		cout << "7 - Поменять stack" << endl;
		cout << "8 - Сформировать новый Stack из одинаковых элементов" << endl;
		cout << "9 - Удалить первый повторяющийся элемент стека" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: {
			cout << "Введите элемент: " << endl;
			cin >> x;
			push(x, myStk); break;
		}
		case 2: {
			x = pop(myStk);
			if (x != -1)
				cout << "Извлеченный элемент: " << x << endl;
			break;
		}
		case 3: { toFile(myStk);  break; }
		case 4: { fromFile(myStk); break; }
		case 5: {
			cout << "Весь стек: " << endl;
			show(myStk); break;
		}
		case 6: {
			cout << "Введите диапазон от ";
			int min, max;
			cin >> min;
			cout << "до ";
			cin >> max;
			checkDiapason(myStk, min, max);
			break;
		}
		case 7: {
			cout << "Выберите стек для заполнения (0/1)" << endl;
			cin >> k;
			if (k) {
				stack1 = myStk;
				myStk = stack2;
			}
			else {
				stack2 = myStk;
				myStk = stack1;
			}
			break;
		}
		case 8: {
			Stack* tempSteck = NULL	;
			if (k) {
				stack2 = myStk;
			}
			else {
				stack1 = myStk;
			}
			fuseStack(stack1, stack2, tempSteck);
			show(tempSteck);
			break;
		}
		case 9: {
			removeFirstDuplicate(myStk);
			break;
		}
		case 0: return 0; break;
		}
	}
	return 0;
}
