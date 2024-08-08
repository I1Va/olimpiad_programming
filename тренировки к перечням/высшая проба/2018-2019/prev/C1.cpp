#include <iostream>
#include <vector>
#include <unordered_set>
#include <bitset>
using namespace std;

int n, k;
vector<vector<int>> g;
unordered_set<int> tags;

void dfs(int v, int prev, int& used, int& cnt, const int& mask) {
    used++;
    if (tags.find(v) != tags.end()) {
        cnt++;
    }
    for (int u : g[v]) {
        if (u == prev || !((mask >> u) & 1)) {
            continue;
        }
        dfs(u, v, used, cnt, mask);
    }
}

int main() {
    cin >> n >> k;
    g.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int v;
        cin >> v;
        g[v - 1].push_back(i + 1);
    }
    for (int i = 0; i < k; i++) {
        int v;
        cin >> v;
        tags.insert(v - 1);
    }
    int res = 1e9;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (!((mask >> 0) & 1)) {
            continue;            
        }
        int used = 0;
        int cnt = 0;
        dfs(0, -1, used, cnt, mask);
        // cout << bitset<5>(mask) << ": " << used << ", " << cnt << "\n";
        if (cnt == (int) tags.size()) {
            res = min(res, used);
        }
    }
    cout << res;
}