#include <iostream>
#include <climits>
using namespace std;

struct Tree {
    int key;         // ключ
    int a, b, c;     // три целых числа
    Tree* Left, * Right;
};

// Прототипы функций
Tree* makeTree(Tree* Root);
Tree* list(int i, int a, int b, int c);
Tree* insertElem(Tree* Root, int key, int a, int b, int c);
Tree* search(Tree* n, int key);
Tree* delet(Tree* Root, int key);
void view(Tree* t, int level);
void delAll(Tree* t);
Tree* findMinSumNode(Tree* root);
Tree* deleteMinSumNode(Tree* root);

Tree* Root = NULL;

int main() {
    setlocale(0, "Russian");
    int key, choice, a, b, c;

    for (;;) {
        cout << "1 - создание дерева\n";
        cout << "2 - добавление элемента\n";
        cout << "3 - поиск по ключу\n";
        cout << "4 - удаление элемента по ключу\n";
        cout << "5 - вывод дерева\n";
        cout << "6 - очистка дерева\n";
        cout << "7 - выход\n";
        cout << "8 - удалить вершину с минимальной суммой (a+b+c)\n";
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
            cout << "Введите три числа через пробел: ";
            cin >> a >> b >> c;
            insertElem(Root, key, a, b, c);
            break;
        }
        case 3: {
            cout << "\nВведите ключ: ";
            cin >> key;
            Tree* rc = search(Root, key);
            if (rc)
                cout << "Найден элемент: ключ=" << rc->key << ", значения="
                << rc->a << "," << rc->b << "," << rc->c << endl;
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
                Root = deleteMinSumNode(Root);
                cout << "Вершина с минимальной суммой удалена\n";
            }
            else {
                cout << "Дерево пустое\n";
            }
            break;
        }
        }
    }
}

Tree* makeTree(Tree* Root) {
    int key, a, b, c;
    cout << "Конец ввода - отрицательное число\n\n";
    if (Root == NULL) {
        cout << "Введите ключ корня: ";
        cin >> key;
        cout << "Введите три числа через пробел: ";
        cin >> a >> b >> c;
        Root = list(key, a, b, c);
    }
    while (1) {
        cout << "\nВведите ключ: ";
        cin >> key;
        if (key < 0) break;
        cout << "Введите три числа через пробел: ";
        cin >> a >> b >> c;
        insertElem(Root, key, a, b, c);
    }
    return Root;
}

Tree* list(int i, int a, int b, int c) {
    Tree* t = new Tree;
    t->key = i;
    t->a = a;
    t->b = b;
    t->c = c;
    t->Left = t->Right = NULL;
    return t;
}

Tree* insertElem(Tree* t, int key, int a, int b, int c) {
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
        t = list(key, a, b, c);
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
        cout << t->key << " (" << t->a << "," << t->b << "," << t->c << ")" << endl;
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

Tree* findMinSumNode(Tree* root) {
    if (root == NULL) return NULL;

    Tree* minNode = root;
    int minSum = root->a + root->b + root->c;
    Tree* leftMin = findMinSumNode(root->Left);
    if (leftMin != NULL) {
        int leftSum = leftMin->a + leftMin->b + leftMin->c;
        if (leftSum < minSum) {
            minSum = leftSum;
            minNode = leftMin;
        }
    }
    Tree* rightMin = findMinSumNode(root->Right);
    if (rightMin != NULL) {
        int rightSum = rightMin->a + rightMin->b + rightMin->c;
        if (rightSum < minSum) {
            minSum = rightSum;
            minNode = rightMin;
        }
    }

    return minNode;
}

Tree* deleteMinSumNode(Tree* root) {
    if (root == NULL) return NULL;

    Tree* minNode = findMinSumNode(root);
    if (minNode != NULL) {
        return delet(root, minNode->key);
    }
    return root;
}