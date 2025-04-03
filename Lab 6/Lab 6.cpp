#include <iostream>
using namespace std;
struct list
{
    float number;
    list* next;
};

void insert(list*&, float); //функция добавления элемента, передается адрес спис-ка и символ, который добавляется 
int IsEmpty(list*);         //функция, которая проверяет, пуст ли список
void proiz10(list*);  //функция подсчета суммы чисел, больших 7  

int main()
{
    setlocale(LC_CTYPE, "Russian");
    list* first = NULL;
    int n;
    cout << "Введите количство элементов в списке: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        float temp;
        cin >> temp;
        insert(first, temp);
    }
    proiz10(first);

    return 0;
}

void insert(list*& p, float value) //Добавление числа value в список 
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

int IsEmpty(list* p) //Список  пустой? (1-да, 0-нет) 
{
    return p == NULL;
}

void proiz10(list* p)  // Подсчет суммы чисел, больших 7  
{
    float sm = 1;
    if (p == NULL)
        cout << "Список пуст" << endl;
    else
    {
        while (p != NULL)
        {
            if (p->number < 10)
                sm *= (p->number);
            p = p->next;
        }
        cout << "Произведение = " << sm << endl;
    }
}

