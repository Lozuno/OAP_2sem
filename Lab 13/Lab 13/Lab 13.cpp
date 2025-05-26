#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;

void bubbleSort(int a[], int n)
{
	int i, j, t;
	for (i = 1; i < n; i++)
		for (j = n - 1; j >= i; j--)
			if (a[j - 1] > a[j])
			{
				t = a[j - 1];
				a[j - 1] = a[j];
				a[j] = t;
			}
}

void heapify(int A[], int pos, int n)
{
	int t, tm;
	while (2 * pos + 1 < n)
	{
		t = 2 * pos + 1;
		if (2 * pos + 2 < n && A[2 * pos + 2] >= A[t])
			t = 2 * pos + 2;
		if (A[pos] < A[t])
		{
			tm = A[pos];
			A[pos] = A[t];
			A[t] = tm;
			pos = t;
		}
		else break;
	}
}
void piramSort(int A[], int n)
{
	for (int i = n - 1; i >= 0; i--)
		heapify(A, i, n);
	while (n > 0)
	{
		int tm = A[0];
		A[0] = A[n - 1];
		A[n - 1] = tm;
		n--;
		heapify(A, 0, n);
	}
}

void test(int n) {
	int* a = new int[n];
	int* b = new int[n];
	int bmax = INTMAX_MIN;
	srand(time(0));
	for (int i = 0; i < n; i++) {
		a[i] = pow(rand(),3);
		b[i] = pow(rand(),3);
		if (bmax < b[i]) {
			bmax = b[i];
		}
	}
	int* c = new int[n];
	int csize = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] > bmax) {
			c[csize] = a[i];
			csize++;
		}
	}
	int* temp = new int[n];
	for (int i = 0; i < csize; i++) {
		temp[i] = c[i];
	}
	double start = clock();
	bubbleSort(c, csize);
	double end = clock();
	double sec = (end - start) / CLOCKS_PER_SEC;
	cout << "Время сортировки пузырьком: " << sec << " секунд\n";
	start = clock();
	piramSort(temp, csize);
	end = clock();
	sec = (end - start) / CLOCKS_PER_SEC;
	cout << "Время пирамидальноя сортировки: " << sec << " секунд\n";
	cout << '\n';
}

int main() {
	setlocale(LC_ALL, "rus");
	test(10000);
	test(20000);
	test(30000);
	test(40000);
	return 0;
}