#include <iostream>
#include <iomanip>
using namespace std;

enum polit { monarchy, republic, dict, oligarchy, totalit };

struct GOSUDAR {
    char name[30];
    int population;
    int area;
    char capital[30];
    polit form;
};

void handleEnum(char temp[50], GOSUDAR all[], int size) {
    if (strcmp("monarchy", temp) == 0) { all[size].form = monarchy; }
    if (strcmp("republic", temp) == 0) { all[size].form = republic; }
    if (strcmp("dict", temp) == 0) { all[size].form = dict; }
    if (strcmp("oligarchy", temp) == 0) { all[size].form = oligarchy; }
    if (strcmp("totalit", temp) == 0) { all[size].form = totalit; }
}

const char* writeEnum(enum polit en, char temp[50]) {
    switch (en) {
    case monarchy: {
        strcpy_s(temp, 50, "monarchy");
        break;
    }
    case republic: {
        strcpy_s(temp, 50, "republic");
        break;
    }
    case dict: {
        strcpy_s(temp, 50, "dict");
        break;
    }
    case oligarchy: {
        strcpy_s(temp, 50, "oligarchy");
        break;
    }
    case totalit: {
        strcpy_s(temp, 50, "totalit");
        break;
    }
    default: {
        strcpy_s(temp, 50, "unknown");
        break;
    }
    }
    return temp;
}
void readMas(GOSUDAR all[20], int& size) {
    char temp[20];
    cout << left << setw(15) << "Имя" << setw(10) << "Население" << setw(15) << "Площадь" << setw(15) << "Столица" << setw(20) << "Форма правления" << endl;
    cin >> all[size].name >> all[size].population >> all[size].area >> all[size].capital >> temp;
    handleEnum(temp, all, size);
    size++;
}



void writeMas(GOSUDAR all[20], int size) {
    cout << left << setw(15) << "Имя" << setw(10) << "Население" << setw(15) << "Площадь" << setw(15) << "Столица" << setw(20) << "Форма правления" << endl;
    for (int i = 0; i < size; i++) {
        char temp[50];
        writeEnum(all[i].form, temp);
        cout << left << setw(15) << all[i].name << setw(10) << all[i].population << setw(15) << all[i].area << setw(15) << all[i].capital << setw(20) << temp << endl;
    }
}

int searchMas(GOSUDAR all[20], int size, const char* item) {
    for (int i = 0; i < size; i++) {
        bool flag = true;
        for (int j = 0; item[j] != '\0' && all[i].capital[j] != '\0'; j++) {
            if (item[j] != all[i].capital[j]) {
                flag = false;
            }
        }
        if (flag) {
            return i;
        }
    }
    return -1;
}

void deleteElement(GOSUDAR all[20], int& size, int nomer) {
    for (int i = nomer; i < size - 1; i++) {
        all[i] = all[i + 1];
    }
    size--;
}

int main() {
    setlocale(LC_ALL, "rus");
    int choice;
    GOSUDAR all[20];
    int size = 0;
    do {
        cout << "\n1.Ввод данных с клавиатуры и запись в массив\n";
        cout << "2.Вывод данных из массива\n";
        cout << "3.Поиск по столице\n";
        cout << "4.Удаление данных из массива\n";
        cout << "0.Выход из программы\n\n";
        cout << "Введите номер операции: ";
        cin >> choice;
        cin.ignore();
        int ans = 0;
        switch (choice) {
        case 1: {
            readMas(all, size);
            break;
        }
        case 2: {
            writeMas(all, size);
            break;
        }
        case 3: {
            cout << "Введите столицу\n";
            char buf[256];
            cin.getline(buf, 256);
            int ans = searchMas(all, size, buf);
            if (ans == -1) {
                cout << "Элемент не найден\n";
            }
            else {
                cout << "Элемент номер: " << ans + 1 << '\n';
            }
            break;
        }
        case 4: {
            cout << "Введите номер элемента для удаления: ";
            int k;
            cin >> k;
            deleteElement(all, size, k - 1);
            cout << "Элемент удалён\n";
            break;
        }
        case 0:
            break;
        default: {
            cout << "Неверный ввод\n";
            break;
        }
        }
    } while (choice != 0);
    return 0;
}