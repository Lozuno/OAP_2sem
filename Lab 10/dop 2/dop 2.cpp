#include <iostream>

using namespace std;

void backtrack(int** adj, int n, int current, int* groups, int* best_groups, int& min_cut, int current_cut = 0) {
    if (current == n) {
        
        bool has_cut = false;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (adj[i][j] && groups[i] != groups[j]) {
                    has_cut = true;
                    break;
                }
            }
            if (has_cut) break;
        }
        if (has_cut && current_cut < min_cut) {
            min_cut = current_cut;
            for (int i = 0; i < n; ++i) {
                best_groups[i] = groups[i];
            }
        }
        return;
    }

    
    groups[current] = 0;
    int new_cut = current_cut;
    for (int i = 0; i < current; ++i) {
        if (adj[current][i] && groups[i] != groups[current]) {
            new_cut++;
        }
    }
    if (new_cut < min_cut) {
        backtrack(adj, n, current + 1, groups, best_groups, min_cut, new_cut);
    }

    
    groups[current] = 1;
    new_cut = current_cut;
    for (int i = 0; i < current; ++i) {
        if (adj[current][i] && groups[i] != groups[current]) {
            new_cut++;
        }
    }
    if (new_cut < min_cut) {
        backtrack(adj, n, current + 1, groups, best_groups, min_cut, new_cut);
    }
}

int minCutPartition(int** adj, int n, int* best_groups) {
    if (n == 0) return 0;

    int* groups = new int[n];
    for (int i = 0; i < n; ++i) groups[i] = -1;
    int min_cut = INT_MAX;

    backtrack(adj, n, 0, groups, best_groups, min_cut);

    delete[] groups;
    return min_cut;
}

int main() {
    setlocale(LC_ALL, "rus");
    const int n = 4;

    
    int** adj = new int* [n];
    for (int i = 0; i < n; ++i) {
        adj[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            adj[i][j] = 0;
        }
    }

   
    adj[0][1] = adj[1][0] = 1; // Страны 0 и 1 имеют общую границу
    adj[0][2] = adj[2][0] = 1; // Страны 0 и 2 имеют общую границу
    adj[1][2] = adj[2][1] = 1; // Страны 1 и 2 имеют общую границу
    adj[1][3] = adj[3][1] = 1; // Страны 1 и 3 имеют общую границу
    adj[2][3] = adj[3][2] = 1; // Страны 2 и 3 имеют общую границу

    int* best_groups = new int[n];
    int result = minCutPartition(adj, n, best_groups);

    cout << "Минимальные смежные границы между группами: " << result << endl;
    cout << "Распределение груп: ";
    for (int i = 0; i < n; ++i) {
        cout << best_groups[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < n; ++i) {
        delete[] adj[i];
    }
    delete[] adj;
    delete[] best_groups;

    return 0;
}