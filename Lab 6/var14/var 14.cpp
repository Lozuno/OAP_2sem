#include <iostream>
using namespace std;
struct list
{
    int number;
    list* next;
};

void insert(list*&, int);
void sumDvuz(list*);

int main()
{
    setlocale(LC_CTYPE, "Russian");
    list* first = NULL;
    int n;
    cout << "Введите количство элементов в списке: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        insert(first, temp);
    }
    sumDvuz(first);

    return 0;
}

void insert(list*& p, int value) //Добавление числа value в список 
{
    list* newP = new list;
    if (newP != NULL)     //есть ли место?  
    {
        newP->number = value;
        newP->next = p;
        p = newP;
    }
    else
        cout << "Операция добавления не выполнена" << endl;
}


void sumDvuz(list* p) 
{
    int sm = 0;
    bool flag = false;
    if (p == NULL)
        cout << "Список пуст" << endl;
    else
    {
        while (p != NULL)
        {
            if (p->number < 0 && p->number % 5 == 0) {
                sm += (p->number);
                flag = true;
            }
            p = p->next;
        }
        if (flag) {
            cout << "Сумма = " << sm << endl;
        }
        else {
            cout << "Отрицательных элементов кратных 5 не найдено"<<endl;
        }
    }
}

