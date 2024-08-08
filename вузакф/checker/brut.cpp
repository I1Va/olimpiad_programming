#include <iostream>
#include <vector>
using namespace std;

vector<pair<int, int>> moves = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
int n, m;
vector<vector<bool>> a;

bool in_bord(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < m);
}

void dfs(int x, int y, vector<vector<bool>>& used) {
    used[x][y] = true;
    for (auto to : moves) {
        int n_x = x + to.first;
        int n_y = y + to.second;
        // cout << n_x << ", " << n_y << ": " <<  in_bord(n_x, n_y) << " " << !used[n_x][n_y] << " " << !a[n_x][n_y] << "\n";
        if (in_bord(n_x, n_y) && !used[n_x][n_y] && !a[n_x][n_y]) {
            dfs(n_x, n_y, used);
        }
    }
}

int main() {
    cin >> n >> m;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        a[i].resize(m, false);
    }
    int k;
    cin >> k;
    while (k--) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        a[x][y] = true; 
        vector<vector<bool>> used(n, vector<bool>(m, false));
        dfs(0, 0, used);
        if (used[n - 1][m - 1]) {
            cout << "Success!\n";
        } else {
            cout << "Defeat!\n";
        }
    }
}