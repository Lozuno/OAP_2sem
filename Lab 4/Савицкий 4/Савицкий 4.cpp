#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Cars {
    char brand[20];
    char color[20];
    int serial;
    char release[20];
    char type[20];
    char check[20];
    char owner[20];
};

void readMas(Cars all[20], int& size) {
    cin >> all[size].brand >> all[size].color >> all[size].serial >> all[size].release >> all[size].type >> all[size].check >> all[size].owner;
    size++;
}



void writeMas(Cars all[20], int size) {
    cout << left << setw(15) << "Марка"<< setw(10) << "Цвет"<< setw(15) << "Заводской номер"<< setw(15) << "Дата выпуска"<< setw(15) << "Тип кузова"<< setw(20) << "Дата техосмотра"<< setw(15) << "Владелец"<< endl;

    for (int i = 0; i < size; i++) {
        cout << left<< setw(15) << all[i].brand<< setw(10) << all[i].color<< setw(15) << all[i].serial<< setw(15) << all[i].release<< setw(15) << all[i].type<< setw(20) << all[i].check<< setw(15) << all[i].owner<< endl;
    }
}


void writeFile(Cars all[20], int size, const char filename[]) {
    ofstream fout(filename);
    for (int i = 0; i < size; i++) {
        fout << all[i].brand << "\t" << all[i].color << "\t" << all[i].serial << "\t" << all[i].release << "\t" << all[i].type << "\t" << all[i].check << "\t" << all[i].owner << "\n";
    }
    fout.close();
}

void readFile(Cars all[20], int& size, const char filename[]) {
    ifstream fin(filename);
    Cars newall[20];
    size = 0;
    while (fin >> newall[size].brand) {
        fin >> newall[size].color >> newall[size].serial >> newall[size].release >> newall[size].type >> newall[size].check >> newall[size].owner;
        size++;
    }
    for (int i = 0; i < size; i++) {
        all[i] = newall[i];
    }
    fin.close();
}

int searchMas(Cars all[20], int size, const char* item) {
    for (int i = 0; i < size; i++) {
        bool flag = true;
        for (int j = 0; item[j] != '\0' && all[i].owner[j] != '\0'; j++) {
            if (item[j] != all[i].owner[j]) {
                flag = false;
            }
        }
        if (flag) {
            return i;
        }
    }
    return -1;
}

void deleteElement(Cars all[20], int& size, int nomer) {
    for (int i = nomer; i < size - 1; i++) {
        all[i] = all[i + 1];
    }
    size--;
}

int main() {
    setlocale(LC_ALL, "rus");
    Cars all[20];
    int size = 0;
    const char filename[] = "Var10.txt";

    readFile(all, size, filename);

    int choice;
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
        case 3:
            writeFile(all, size, filename);
            break;
        case 4: {
            readFile(all, size, filename);
            writeMas(all, size);
            break;
        }
        case 5: {
            cout << "Введите владельца\n";
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
        case 6: {
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

