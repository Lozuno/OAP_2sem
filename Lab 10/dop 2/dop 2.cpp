#include <iostream>
#include <climits>

using namespace std;

void backtrack(int** adj, int n, int current, int* groups, int& min_cut, int current_cut = 0) {
    if (current == n) {
        if (current_cut < min_cut) {
            min_cut = current_cut;
        }
        return;
    }

    // Пробуем группу 0
    groups[current] = 0;
    int new_cut = current_cut;
    for (int i = 0; i < current; ++i) {
        if (adj[current][i] && groups[i] != groups[current]) {
            new_cut++;
        }
    }
    if (new_cut < min_cut) {
        backtrack(adj, n, current + 1, groups, min_cut, new_cut);
    }

    // Пробуем группу 1
    groups[current] = 1;
    new_cut = current_cut;
    for (int i = 0; i < current; ++i) {
        if (adj[current][i] && groups[i] != groups[current]) {
            new_cut++;
        }
    }
    if (new_cut < min_cut) {
        backtrack(adj, n, current + 1, groups, min_cut, new_cut);
    }
}

int minCutPartition(int** adj, int n) {
    if (n == 0) return 0;

    int* groups = new int[n];
    for (int i = 0; i < n; ++i) groups[i] = -1;
    int min_cut = INT_MAX;

    backtrack(adj, n, 0, groups, min_cut);

    delete[] groups;
    return min_cut;
}

int main() {
    const int n = 4;

    // Создаем и инициализируем матрицу смежности
    int** adj = new int* [n];
    for (int i = 0; i < n; ++i) {
        adj[i] = new int[n];
    }

    // Заполняем матрицу смежности
    adj[0][0] = 0; adj[0][1] = 1; adj[0][2] = 1; adj[0][3] = 0;
    adj[1][0] = 1; adj[1][1] = 0; adj[1][2] = 1; adj[1][3] = 1;
    adj[2][0] = 1; adj[2][1] = 1; adj[2][2] = 0; adj[2][3] = 1;
    adj[3][0] = 0; adj[3][1] = 1; adj[3][2] = 1; adj[3][3] = 0;

    int result = minCutPartition(adj, n);
    cout << "Minimal cuts between groups: " << result << endl;

    // Освобождаем память
    for (int i = 0; i < n; ++i) {
        delete[] adj[i];
    }
    delete[] adj;

    return 0;
}