#include <iostream>
#include <vector>
#include <set>
using namespace std;

vector<multiset<int>> g;
const int c = 1000;
bool ans[c][c];

void euler(int v, int l, int r, vector<multiset<int>>& g) {
    while (!g[v].empty()) {
        auto idx = g[v].begin();
        while (idx != g[v].end()) {
            if (*idx > r || *idx < l) {
                idx++;
            } else {
                break;
            }
        }
        if (idx == g[v].end()) {
            break;
        }
        int u = *idx;
        ans[u][v] = true;
        g[v].erase(g[v].find(u));
        g[u].erase(g[u].find(v));
        euler(u, l, r, g);
    }
    // cout << v << " ";
}

void solve(int l, int r) {
    int sz = r - l + 1;
    if (sz % 2 == 0) {
        euler(l, l, r - 1, g);
        for (int i = l; i < l + sz / 2; i++) {
            ans[sz - 1][i] = 1;
        }
    } else {
        euler(l, l, r, g);
    }
}

int main() {
    int n, w, k;
    cin >> n >> w >> k;
    g.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            g[i].insert(j);
        }
    }
    
    for (int i = 0; i < k; i++) {
        for (int j = k; j < n; j++) {
            ans[i][j] = true;
        }
    }
    solve(0, k - 1);
    solve(k, n - 1);
    vector<int> cnt(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (ans[i][j]) {
                cnt[i]++;
            }
        }
    }
    int cur = 0;
    for (int i = 0; i < n; i++) {
        if (cnt[i] >= w) {
            cur++;
        }
    }
    if (cur != k) {
        cout << "NO";
    } else {
        cout << "YES\n";
        for (int i = 0; i < n; i++) {
            for (int j =0; j < n; j++) {
                cout << ans[i][j];
            }
            cout << "\n";
        }
    }

}