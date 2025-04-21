#include "Queue.h"
using namespace std;
int main() {
	setlocale(LC_ALL, "rus");
	Queue* myQueue = new Queue;
	cout << "Введите количество элементов для ввода в очередь:";
	int size;
	cin >> size;
	for (int i = 0; i < size; i++) {
		A buf;
		cin >> buf;
		push(buf, myQueue);
	}
	moveMax(myQueue);
	print(myQueue);
	return 0;
}