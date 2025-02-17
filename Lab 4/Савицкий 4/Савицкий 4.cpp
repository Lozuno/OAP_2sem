#include <iostream>
#include <fstream>
using namespace std;
struct Cars
{
	char brand[20];
	char color[20];
	int serial;
	char release[20];
	char type[20];
	char check[20];
	char owner[20];
};
void readMas(Cars all[20],int &size) {
	cin >> all[size].brand >> all[size].color >> all[size].serial >> all[size].release >> all[size].type >> all[size].check >> all[size].owner;
	size++;
	return;
}
void writeMas(Cars all[20], int size) {
	cout << "Марка автомобиля цвет\t заводской номер\t дата выпуска\t тип кузова\tдата последнего техосмотра\tвладелец";
	for (int i = 0; i < size; i++) {
		cout << all[size].brand << "\t" << all[size].color << "\t" << all[size].serial << "\t" << all[size].release << "\t" << all[size].type << "\t" << all[size].check << "\t" << all[size].owner;
		cout << "\n";
	}
	return;
}
void writeFile(Cars all[20], int size, ofstream fout) {
	fout.clear();
	for (int i = 0; i < size; i++) {
		fout << all[size].brand << "\t" << all[size].color << "\t" << all[size].serial << "\t" << all[size].release << "\t" << all[size].type << "\t" << all[size].check << "\t" << all[size].owner;
		fout << "\n";
	}
	return;
}
void readFile(Cars all[20], int size, ifstream fin) {
	Cars newall[20];
	fin.seekg(0);
	while (fin >> newall[size].brand) {
		fin >> newall[size].color >> newall[size].serial >> newall[size].release >> newall[size].type >> newall[size].check >> newall[size].owner;
		size++;
	}
	all = newall;
	return;
}
void searchMas(Cars all[20], int size, Cars item) {
	for (int i = 0; i < size; i++) {
	}
}
int main() {
	setlocale(LC_ALL, "rus");
	Cars all[20];
	int size = 0;
	ifstream fin("Var10.txt");
	ofstream fout("Var10.txt");
	while (fin >> all[size].brand) {
		fin >> all[size].color >> all[size].serial >> all[size].release >> all[size].type >> all[size].check >> all[size].owner;
		size++;
	}
	fin.close();
	int choice;
	cin >> choice;
	do {

		cout << "\n1.Ввод данных с клавиатуры и запись в массив\n";
		cout << "2.Вывод данных из массива\n";
		cout << "3.Перенос данных из массива в файл\n";
		cout << "4.Вывод данных из файла\n";
		cout << "5.Поиск по владельцу\n";
		cout << "6.Удаление данных из массива\n";
		cout << "0.Выход из программы\n\n";
		cout << "Введите номер операции: ";
		cin >> choice;
		switch (choice) {
		case 1: {

		}
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 0: {
			break;
		}
		default: {
			cout << "Неверный ввод\n";
			break;
		}
		}
	} while (choice != 0);
	return 0;
}
