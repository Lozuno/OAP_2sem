#include "Queue.h"
int main() {
	setlocale(LC_ALL, "rus");
	Queue* myQueue=new Queue;
	cout << "Введите количество элементов для ввода в очередь:";
	int size;
	cin >> size;
	for (int i = 0; i < size; i++) {
		int buf;
		cin >> buf;
		push(buf, myQueue);
	}
	Queue* q1 = new Queue;
	Queue* q2 = new Queue;
	minmax(myQueue, q1, q2);
	print(myQueue);
	print(q1);
	print(q2);
}