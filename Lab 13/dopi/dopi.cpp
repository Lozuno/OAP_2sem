#include <iostream>
#include <ctime>
using namespace std;

void selectionSort(int a[], int n)
{
    int i, j, minIndex, temp;
    for (i = 0; i < n - 1; i++)
    {
        minIndex = i;
        for (j = i + 1; j < n; j++)
            if (a[j] < a[minIndex])
                minIndex = j;

        temp = a[i];
        a[i] = a[minIndex];
        a[minIndex] = temp;
    }
}

void insertionSort(int a[], int n)
{
    int i, j, temp;
    for (i = 1; i < n; i++)
    {
        temp = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > temp)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = temp;
    }
}

void shellSort(int a[], int n)
{
    int gap, i, j, temp;
    for (gap = n / 2; gap > 0; gap /= 2)
    {
        for (i = gap; i < n; i++)
        {
            temp = a[i];
            j = i;

            while (j >= gap && a[j - gap] > temp)
            {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = temp;
        }
    }
}
int main() {
    setlocale(LC_ALL, "rus");
    int n = 100000;
    int* t1 = new int[n];
    int* t2 = new int[n];
    int* t3 = new int[n];
    srand(time(0));
    for (int i = 0; i < n; i++) {
        int temp = rand();
        t1[i] = temp;
        t2[i] = temp;
        t3[i] = temp;
    }
    double start = clock();
    selectionSort(t1, n);
    double end = clock();
    double sec = (end - start) / CLOCKS_PER_SEC;
    cout << "Время сортировки выбором: " << sec << " секунд\n";
    start = clock();
    insertionSort(t2, n);
    end = clock();
    sec = (end - start) / CLOCKS_PER_SEC;
    cout << "Время сортировки вставкой: " << sec << " секунд\n";
    start = clock();
    shellSort(t2, n);
    end = clock();
    sec = (end - start) / CLOCKS_PER_SEC;
    cout << "Время сортировки Шелла: " << sec << " секунд\n";
    return 0;
}