#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

ostream& operator<< (ostream& stream, const pair<int, int>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream;
}

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

const vector<pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void dfs(int v, vector<bool>& used, vector<int>& order, const vector<vector<int>>& g) {
    used[v] = true;
    for (int u : g[v]) {
        if (!used[u]) {
            dfs(u, used, order, g);
        }
    }
    order.push_back(v);
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<long long>> a(n, vector<long long>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    
    vector<vector<int>> tr_g(n * m), g(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (auto move : moves) {
                int i1 = i + move.first;
                int j1 = j + move.second;
                if (i1 >= n || i1 < 0 || j1 >= m || j1 < 0) {
                    continue;
                }
                
                if (a[i1][j1] > a[i][j]) {
                    // cout << make_pair(i, j) << " -> " << make_pair(i1, j1) << "\n";
                    tr_g[i1 * m + j1].push_back(i * m + j);
                    g[i * m + j].push_back(i1 * m + j1);
                }
            }
            
        }
    }
    // for (int i = 0; i < n * m; i++) {
    //     if (g[i].empty()) {
    //         continue;
    //     }
    //     cout << make_pair(i / m, i % m) << ": ";
    //     for (auto x : g[i]) {
    //         cout << make_pair(x / m, x % m) << " ";
    //     }
    //     cout << "\n";
    // }
    // cout << "\n";
    vector<bool> used(n * m, false);
    vector<int> order;
    for (int i = 0; i < n * m; i++) {
        if (!used[i]) {
            dfs(i, used, order, g);
        }
    }
    reverse(order.begin(), order.end());
    vector<vector<long long>> dp(n * m, vector<long long>(n * m + 1, 0));
    for (int i = 0; i < n * m; i++) {
        dp[i][1] = a[i / m][i % m]; 
    }
    vector<vector<pair<long long, long long>>> p(n * m, vector<pair<long long, long long>>(n * m + 1, {-1, -1}));
    for (auto v : order) {
        for (int c = 0; c < n * m; c++) {
            for (int u : tr_g[v]) {
                if (dp[u][c] + a[v / m][v % m] > dp[v][c + 1] && dp[u][c]) {
                    dp[v][c + 1] = dp[u][c] + a[v / m][v % m];
                    p[v][c + 1] = {u, c}; 
                }
            }
        }
    }
    long long mx = 0;
    int idx;
    int cnt;
    for (int c = 1; c <= n * m; c *= 2) {
        for (int i = 0; i < n * m; i++) {
            if (dp[i][c] > mx) {
                mx = dp[i][c];
                idx = i;
                cnt = c;
            }
        }
    }
    // pair<int, int> cur = {idx, cnt};
    // cout << "cnt: " << cnt << "\n";
    // while (1) {
    //     cout << make_pair(cur.first / m, cur.first % m) << "\n";
    //     auto prev = p[cur.first][cur.second];
    //     if (prev.second == -1) {
    //         break;
    //     }
    //     cur = {prev.first, prev.second};
    // }
    cout << mx << "\n";
}

int main() {
    // Разбор (решение на 30/60 из 30/70. В решении есть баг)
    // a[n][m] - массив интересов
    // 1) Явно построим граф из n * m вершин.
    // между вершинами u и v есть ориентированное ребро, когда a[u / m][u % m] < a[v / m][v % m]
    // Аналогично построим транспонированный граф(перевернутый)
    // 2) Сделаем топологическую сортировку
    // 3) Будем поддерживать dp[n * m][cnt] = maxv на ациклическом ориентированном графе
    // n * m - текущая вершина в топологической сортировке(текущая комната)
    // cnt - кол-во ранее посещенных комнат
    // maxv - максимальный сумарный интерес, которого можно добиться, придя в текущее состояние
    // Переход: if (dp[u][c] + a[v / m][v % m] > dp[v][c + 1] && dp[u][c]) {
            //     dp[v][c + 1] = dp[u][c] + a[v / m][v % m];
            // }
    // Обход: for i in range(n * m)
    // 4) Ответом будет максимальное dp[i][cnt], где cnt - степень двойки, а i E [0 : n * m)

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
}