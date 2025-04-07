#include<iostream>
#include<fstream>
#include<limits>
using namespace std;

struct Node {
    int value;
    Node* next;
};
void addNode(Node*& head, int value) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = head;
    head = newNode;
}

void delNode(Node*& head, int value) {
    Node* current = head;
    Node* previos = nullptr;
    while (current != nullptr && current->value != value) {
        previos = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Элемент не найден." << endl;
        return;
    }

    if (previos == nullptr) {
        head = current->next;
    }
    else {
        previos->next = current->next;
    }

    delete current;
    cout << "Элемент удален." << endl;
}

// Функция для поиска элемента в односвязном списке
Node* searchNode(Node* head, int value) {
    Node* current = head;
    while (current != nullptr) {
        if (current->value == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Функция для вывода односвязного списка в консольное окно
void displayList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << "Значение: " << current->value << endl;
        current = current->next;
    }
}

// Функция для записи односвязного списка в файл
void writeListToFile(Node* head, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        Node* current = head;
        while (current != nullptr) {
            outFile << current->value << endl;
            current = current->next;
        }
        outFile.close();
        cout << "Список записан в файл." << endl;
    }
    else {
        cout << "Ошибка открытия файла." << endl;
    }
}

// Функция для считывания односвязного списка из файла
void readListFromFile(Node*& head, const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        int value;
        head = nullptr; // очищаем текущий список перед чтением из файла
        while (inFile >> value) {
            addNode(head, value);
        }
        inFile.close();
        cout << "Список считан из файла." << endl;
    }
    else {
        cout << "Ошибка открытия файла." << endl;
    }
}




void sumDvuz(Node* p) {
    int sm = 0;
    bool flag = false;
    if (p == NULL)
        cout << "Список пуст" << endl;
    else
    {
        while (p != NULL)
        {
            if (int(log10(abs(p->value))) + 1 == 2 && p->value < 0) {
                sm += (p->value);
                flag = true;
            }
            p = p->next;
        }
        if (flag) {
            cout << "Сумма = " << sm << endl;
        }
        else {
            cout << "Двухзначных отрицательных элементов не найдено" << endl;
        }
    }
}




void menu() {
    Node* head = nullptr;
    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Добавить элемент\n";
        cout << "2. Удалить элемент\n";
        cout << "3. Поиск элемента\n";
        cout << "4. Вывод списка в консольное окно\n";
        cout << "5. Запись списка в файл\n";
        cout << "6. Считывание списка из файла\n";
        cout << "7. Найти сумму отрицательных двухзначных элементов\n";
        cout << "8. Выход\n";
        cout << "Выберите опцию: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            cout << "Введите значение: ";
            cin >> value;
            addNode(head, value);
            break;
        }
        case 2: {
            int value;
            cout << "Введите значение для удаления: ";
            cin >> value;
            delNode(head, value);
            break;
        }
        case 3: {
            int value;
            cout << "Введите значение для поиска: ";
            cin >> value;
            Node* foundNode = searchNode(head, value);
            if (foundNode) {
                cout << "Элемент найден: Значение: " << foundNode->value << endl;
            }
            else {
                cout << "Элемент не найден." << endl;
            }
            break;
        }
        case 4:
            displayList(head);
            break;
        case 5: {
            string filename;
            cout << "Введите имя файла для записи: ";
            cin >> filename;
            writeListToFile(head, filename);
            break;
        }
        case 6: {
            string filename;
            cout << "Введите имя файла для чтения: ";
            cin >> filename;
            readListFromFile(head, filename);
            break;
        }
        case 7:
            sumDvuz(head);
            break;
        case 8:
            return;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    menu();
    return 0;
}


