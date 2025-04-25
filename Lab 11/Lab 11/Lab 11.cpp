#include <iostream>
using namespace std;

struct Tree {
    int key;         // ключ
    Tree* Left, * Right;
};

Tree* makeTree(Tree* Root);       // Создание дерева
Tree* list(int i);                // Создание нового элемента
Tree* insertElem(Tree* Root, int key);  // Добавление нового элемента
Tree* search(Tree* n, int key);   // Поиск элемента по ключу 
Tree* delet(Tree* Root, int key); // Удаление элемента по ключу
void view(Tree* t, int level);    // Вывод дерева 
void delAll(Tree* t);             // Очистка дерева
int sumTreeNodes(Tree* p1);
int sumLeafs(Tree* p1);
Tree* Root = NULL; // указатель на корень

int main() {
    setlocale(0, "Russian");
    int key, choice;

    for (;;) {
        cout << "1 - создание дерева\n";
        cout << "2 - добавление элемента\n";
        cout << "3 - поиск по ключу\n";
        cout << "4 - удаление элемента\n";
        cout << "5 - вывод дерева\n";
        cout << "6 - очистка дерева\n";
        cout << "7 - выход\n";
        cout << "8 - сумма дерева";
        cout << "9 - сумма листьев дерева";
        cout << "ваш выбор?\n";
        cin >> choice;
        cout << "\n";

        switch (choice) {
        case 1: {
            Root = makeTree(Root);
            break;
        }
        case 2: {
            cout << "\nВведите ключ: ";
            cin >> key;
            insertElem(Root, key);
            break;
        }
        case 3: {
            cout << "\nВведите ключ: ";
            cin >> key;
            Tree* rc = search(Root, key);
            if (rc)
                cout << "Найден элемент с ключом: " << rc->key << endl;
            break;
        }
        case 4: {
            cout << "\nВведите удаляемый ключ: ";
            cin >> key;
            Root = delet(Root, key);
            break;
        }
        case 5: {
            if (Root) {
                cout << "Дерево повернуто на 90 град. влево" << endl;
                view(Root, 0);
            }
            else
                cout << "Дерево пустое\n";
            break;
        }
        case 6: {
            delAll(Root);
            Root = NULL;
            break;
        }
        case 7:
            exit(0);
        case 8: { 
            if (Root) {
                int totalSum = sumTreeNodes(Root);
                cout << "Сумма всех вершин дерева: " << totalSum << endl;
            }
            else {
                cout << "Дерево пустое\n";
            }
            break;
        }
        case 9: {
            if (Root) {
                int totalSum = sumLeafs(Root);
                cout << "Сумма всех листьев дерева: " << totalSum << endl;
            }
            else {
                cout << "Дерево пустое\n";
            }
        }
        }
    }
}

Tree* makeTree(Tree* Root) {
    int key;
    cout << "Конец ввода - отрицательное число\n\n";
    if (Root == NULL) {
        cout << "Введите ключ корня: ";
        cin >> key;
        Root = list(key);
    }
    while (1) {
        cout << "\nВведите ключ: ";
        cin >> key;
        if (key < 0) break;
        insertElem(Root, key);
    }
    return Root;
}

Tree* list(int i) {
    Tree* t = new Tree;
    t->key = i;
    t->Left = t->Right = NULL;
    return t;
}

Tree* insertElem(Tree* t, int key) {
    Tree* Prev = nullptr;
    int find = 0;
    while (t && !find) {
        Prev = t;
        if (key == t->key)
            find = 1;
        else if (key < t->key)
            t = t->Left;
        else
            t = t->Right;
    }
    if (!find) {
        t = list(key);
        if (key < Prev->key)
            Prev->Left = t;
        else
            Prev->Right = t;
    }
    return t;
}

Tree* delet(Tree* Root, int key) {
    Tree* Del, * Prev_Del, * R, * Prev_R;
    Del = Root;
    Prev_Del = NULL;
    while (Del != NULL && Del->key != key) {
        Prev_Del = Del;
        if (Del->key > key)
            Del = Del->Left;
        else
            Del = Del->Right;
    }
    if (Del == NULL) {
        cout << "\nНет такого ключа";
        return Root;
    }
    if (Del->Right == NULL)
        R = Del->Left;
    else if (Del->Left == NULL)
        R = Del->Right;
    else {
        Prev_R = Del;
        R = Del->Left;
        while (R->Right != NULL) {
            Prev_R = R;
            R = R->Right;
        }
        if (Prev_R == Del)
            R->Right = Del->Right;
        else {
            R->Right = Del->Right;
            Prev_R->Right = R->Left;
            R->Left = Prev_R;
        }
    }
    if (Del == Root)
        Root = R;
    else if (Del->key < Prev_Del->key)
        Prev_Del->Left = R;
    else
        Prev_Del->Right = R;

    cout << "\nУдален элемент с ключом " << Del->key << endl;
    delete Del;
    return Root;
}

Tree* search(Tree* n, int key) {
    if (n == NULL || n->key == key)
        return n;
    if (key < n->key)
        return search(n->Left, key);
    else
        return search(n->Right, key);
}

void view(Tree* t, int level) {
    if (t) {
        view(t->Right, level + 1);
        for (int i = 0; i < level; i++)
            cout << "   ";
        cout << t->key << endl;
        view(t->Left, level + 1);
    }
}

void delAll(Tree* t) {
    if (t != NULL) {
        delAll(t->Left);
        delAll(t->Right);
        delete t;
    }
}
int sumTreeNodes(Tree* p1) {
    if (p1 == nullptr) {
        return 0;
    }
    return p1->key + sumTreeNodes(p1->Left) + sumTreeNodes(p1->Right);
}
int sumLeafs(Tree* p1) {
    if (p1->Left == nullptr && p1->Right == nullptr) {
        return p1->key;
    }
    return sumLeafs(p1->Left) + sumLeafs(p1->Right);
}