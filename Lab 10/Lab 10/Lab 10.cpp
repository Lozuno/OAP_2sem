#include <iostream>
using namespace std;

int F(int m, int n) {
	if (m == 0 || n == 0)
		return n + 1;
	return F(m - 1, F(m, n - 1));
}
double Var_12(double x, int n) {
	if (n == 1) 
		return cos(x);
	return cos(n * x) + Var_12(x, n - 1);

}

int main() {
	setlocale(LC_ALL, "rus");
	cout << "Введите номер варианта:";
	int choice;
	cin >> choice;
	switch (choice)	{
	case 10: {
		cout << "Введите целые, неотрицательные n и m\n";
		int n, m;
		cin >> n >> m;
		cout << "F = " << F(m, n);
		break;
	}
	case 12: {
		cout << "Введите целое число n: ";
		int n;
		cin >> n;
		cout << "Введите число x:";
		double x;
		cin >> x;
		cout << "y = " << Var_12(x, n);
		break;
	}
	default: break;
	}
	return 0;
}