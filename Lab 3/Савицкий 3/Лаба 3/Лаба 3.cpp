#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

bool isvowel(char ch) {
	if (ch == ' ') return true;
	char vowels[] = "aeiou";
	for (int i = 0; vowels[i] != '\0'; i++) {
		if (ch == vowels[i]) {
			return true;
		}
	}
	return false;
}

int main() {
	setlocale(LC_ALL, "rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int var;
	cout << "Введите номер варианта: ";
	cin >> var;
	switch (var) {
	case 10: {
		int part;
		cout << "Введите номер задания: ";
		cin >> part;
		switch (part) {
		case 1: {
			fstream fin("FILE1.txt");
			fstream fout("FILE2.txt");
			char word[50];
			fin >> word;
			fin.seekg(0);
			while (!fin.fail()) {
				char str[100];
				fin.getline(str, 100);
				int i = 0;
				int j = 0;
				bool flag = false;
				while (str[i - 1] != '\0') {
					if (str[i] == ' ' || str[i] == '\0') {
						if (word[j] == '\0') {
							flag = true;
							break;
						}
					}
					if (word[j] != str[i]) {
						j = 0;
						while (str[i - 1] != '\0' && str[i - 1] != ' ') i++;
					}
					i++;
					j++;
				}
				if (flag) {
					fout << str << '\n';
				}
			}
			char str[100];
			fout.seekg(0);
			fout.getline(str, 100);
			int sum = 0;
			for (int i = 0; str[i] != '\0'; i++) {
				if (!isvowel(str[i])) {
					sum++;
				}
			}
			cout << "Количество согласных:" << sum;
			fout.close();
			fin.close();
			break;
		}
		case 2:
			ofstream fout("FILE10_2.txt");
			char str[256];
			cin.ignore(cin.rdbuf()->in_avail());
			cin.getline(str, 256);
			fout << str;
			fout.close();
			ifstream fin("FILE10_2.txt");
			char buf[50];
			while (fin >> buf) {
				int i = 0;
				while (buf[i] != '\0') {
					if (buf[i] == 'p') {
						cout << buf << ' ';
						break;
					}
					i++;
				}
			}
			fin.close();
		}
		break;
	}
	case 11: {
		int part;
		cout << "Введите номер задания: ";
		cin >> part;
		switch (part) {
		case 1: {
			ifstream fin("FILE11_1.txt");
			ofstream fout("FILE11_2.txt");
			char buf[256];
			while (!fin.fail()) {
				fin.getline(buf, 256);
				int i = 0;
				bool flag = true;
				while (buf[i] != '\0') {
					if (buf[i] == ' ') {
						if (buf[i + 1] != '\0' && buf[i + 1] != ' ') {
							flag = false;
							break;
						}
					}
					i++;
				}
				if (flag) {
					fout << buf << '\n';
				}
			}
			fin.close();
			fout.close();
			fin.open("FILE11_2.txt");
			int sum = 0;
			while (!fin.fail()) {
				char ch = fin.get();
				sum++;
			}
			cout << "Количество символов в файле: " << sum;
			break;
		}
		case 2: {
			ofstream fout("FILE11_3.txt");
			char buf[256];
			cout << "Первая строка:\n";
			cin.ignore(cin.rdbuf()->in_avail());
			cin.getline(buf, 256);
			fout << buf << '\n';
			cout << "Вторая строка:\n";
			cin.ignore(cin.rdbuf()->in_avail());
			cin.getline(buf, 256);
			fout << buf;
			fout.close();
			ifstream fin("FILE11_3.txt");
			fin.getline(buf, 256);
			int min = 256, i = 0, start = 0;
			while (buf[i - 1] != '\0') {
				if (buf[i] == ' ' || buf[i] == '\0') {
					if (i - start < min) {
						min = i - start;
					}
					start = i + 1;
				}
				i++;
			}
			cout << "Минимальная длина слова: " << min;
			int max = 0;
			i = 0;
			start = 0;
			while (buf[i - 1] != '\0') {
				if (buf[i] == ' ' || buf[i] == '\0') {
					if (i - start > max) {
						max = i - start;
					}
					start = i + 1;
				}
				i++;
			}
			cout << "\nМаксимальная длина слова: " << max;
			break;
		}
		}
		break;
	}
	case 12: {
		int part;
		cout << "Введите номер задания: ";
		cin >> part;
		switch (part) {
		case 1: {
			fstream fin("FILE12_1.txt");
			fstream fout("FILE12_2.txt");
			char word[100];
			fin >> word;
			fin.seekg(0);
			while (!fin.fail()) {
				char str[256];
				fin.getline(str, 100);
				int i = 0;
				int j = 0;
				bool flag = false;
				while (str[i - 1] != '\0') {
					if (str[i] == ' ' || str[i] == '\0') {
						if (word[j] == '\0') {
							flag = true;
							break;
						}
					}
					if (word[j] != str[i]) {
						j = 0;
						while (str[i - 1] != '\0' && str[i - 1] != ' ') i++;
					}
					i++;
					j++;
				}
				if (flag) {
					fout << str << '\n';
				}
			}
			fout << '\0';
			fout.close();
			fin.close();
			fin.open("FILE12_2.txt");
			int sum = 0;
			char ch = fin.get();
			while (ch != '\0') {
				if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
					sum++;
				ch = fin.get();
			}
			cout << "Количество букв: " << sum;
			fin.close();
			break;
		}
		case 2: {
			ofstream fout("FILE12_3.txt");
			char buf[256];
			cin.ignore(cin.rdbuf()->in_avail());
			cin.getline(buf, 256);
			fout << buf;
			fout.close();
			ifstream fin("FILE12_3.txt");
			while (fin>>buf) {
				int i = 0;
				bool flag = true;
				while (buf[i] != '\0') {
					if (!(buf[i] >= '0' && buf[i] <= '9')) {
						flag = false;
						break;
					}
					i++;
				}
				if (flag) {
					if ((buf[i - 1] - '0') % 2 == 1) {
						cout << buf << ' ';
					}
				}
			}
			fin.close();
			break;
		}
		}
		break;
	}
	case 13: {
		int var;
		cout << "Введите номер задания: ";
		cin >> var;
		switch (var) {
		case 1: {
			ifstream fin("FILE13_1.txt");
			ofstream fout("FILE13_2.txt");
			char buf[256];
			while (!fin.fail()) {
				fin.getline(buf, 256);
				int k = 0, i = 0;
				while (buf[i] != '\0') {
					if (buf[i] == ' ') {
						if (!(buf[i + 1] == ' ' || buf[i + 1] == '\0')) {
							k++;
						}
					}
					i++;
				}
				if (k > 1) {
					fout << buf << '\n';
				}
			}
			fin.close();
			fout.close();
			fin.open("FILE13_2.txt");
			int max = -1, j = 1, maxj = 0;
			while (fin>>buf) {
				int i = 0;
				int sum = 0;
				while (buf[i] != '\0') {
					if (isvowel(buf[i])) {
						sum++;
					}
					i++;
				}
				if (sum > max) {
					max = sum;
					maxj = j;
				}
				j++;
			}
			cout << "Максимальное количество глассных: " << max << " в слове под номером: " << maxj;
			break;
		}
		case 2: {
			ofstream fout("FILE13_3.txt");
			char buf[256];
			cin.ignore(cin.rdbuf()->in_avail());
			cin.getline(buf, 256);
			fout << buf<<'\0';
			fout.close();
			ifstream fin("FILE13_3.txt");
			char ch = fin.get();
			char skobki[6] = { '(',')','[',']','{','}' };
			int sum[6] = { 0,0,0,0,0,0 };
			while (ch != '\0') {
				for (int i = 0; i < 6; i++) {
					if (ch == skobki[i]) {
						sum[i]++;
					}
				}
				ch = fin.get();
			}
			for (int i = 0; i < 6; i++) {
				cout << "Количество скобок вида: " << skobki[i] << " - " << sum[i]<<'\n';
			}
			break;
		}
		}
		break;
	}
	}
	return 0;
}