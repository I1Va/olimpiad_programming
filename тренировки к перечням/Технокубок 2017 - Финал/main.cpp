#include <iostream>
#include <vector>
using namespace std;

vector<int> ord;
vector<vector<int>> g;
vector<bool> used;

void dfs(int v) {
    used[v] = true;
    ord.push_back(v);
    for (int u : g[v]) {
        if (!used[u]) {
            dfs(u);
            ord.push_back(v);
        }
    }
    
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    g.resize(n), used.resize(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        g[x - 1].push_back(y - 1);
        g[y - 1].push_back(x - 1);
    }
    dfs(0);
    int idx = 0;
    int sz = (int) ord.size();
    for (int i = 0; i < k; i++) {
        if (idx == sz) {
            cout << "1 1\n";
        } else {
            vector<int> temp;
            for (int c = 0; c < (2 * n + k - 1) / k && idx < sz; c++) {
                temp.push_back(ord[idx]);
                idx++;
            }
            cout << temp.size() << " ";
            for (auto x : temp) {
                cout << x + 1 << " ";
            }
            cout << "\n";
        }
    }
}