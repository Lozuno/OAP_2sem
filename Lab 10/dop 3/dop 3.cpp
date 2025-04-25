#include <iostream>
#include <fstream>
using namespace std;

void fVarA(int n, int index, int buf[],int ans[]) {
	if (index == 0) {
		for (int i = 0; i < n; i++) {
			cout << ans[i] << ' ';
		}
		cout << '\n';
		return;
	}
	int newbuf[256];
	for (int i = 0; i < n; i++) {
		newbuf[i] = buf[i];
	}
	for (int i = 0; i < n; i++) {
		if (newbuf[i] != -1) {
			int temp = newbuf[i];
			ans[index-1] = temp;
			newbuf[i] = -1;
			fVarA(n, index - 1, newbuf,ans);
			newbuf[i] = temp;
		}
	}
	return;
}

int main() {
	setlocale(LC_ALL, "rus");
	int n, ans[256];
	cout << "Введите количество элементов: ";
	cin >> n;
	cout << "Элементы массива: ";
	int* buf = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> buf[i];
	}
	fVarA(n, n, buf,ans);
	return 0;
}