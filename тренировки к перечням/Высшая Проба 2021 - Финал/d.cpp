#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>
using namespace std;

int n, k;
vector<vector<int>> g;
vector<pair<int, int>> edges;

void dfs1(int v, int d, int prev, int& mx, int& ver) {
    if (d > mx) {
        mx = d;
        ver = v;
    }
    for (int u : g[v]) {
        if (u != prev) {
            dfs1(u, d + 1, v, mx, ver);
        }
    }
}

void solve1() {
    int mx = 0;
    int ver = -1;
    dfs1(0, 0, -1, mx, ver);
    mx = 0;
    dfs1(ver, 0, -1, mx, ver);
    cout << mx * 10 << "\n";
}

void dfs2_1(int v, int prev, vector<int>& sz) {
    sz[v] = 1;
    for (int u : g[v]) {
        if (u != prev) {
            dfs2_1(u, v, sz);
            sz[v] += sz[u];
        }
    }
}
vector<int> sz;

bool comp(int a, int b) {
    return sz[a] > sz[b];
}

void dfs2_2(int v, int prev, int& ans, vector<int>& value) {
    value[v]--;
    // cout << v << "[" << value[v] << "], ";
    for (int u : g[v]) {
        if (value[v] == 0) {
            break;
        }
        if (u != prev) {
            ans += 10;
            dfs2_2(u, v, ans, value);
            ans += 10;
            value[v]--;
        }
    }
}

int get(int start) {
    // cout << start << ": ";
    sz.clear();
    sz.resize(n);
    dfs2_1(start, -1, sz);
    vector<int> value(n, k);
    for (auto& x : g) {
        sort(x.begin(), x.end(), comp);
    }
    int res = 0;
    dfs2_2(start, -1, res, value);
    // cout << "\n";
    return res;
}

void solve2() {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, get(i));
    }
    cout << ans << "\n";
}

void dfs3_2(int v, int prev, int& ans, vector<int>& value, const int mask) {
    value[v]--;
    // cout << v << "[" << value[v] << "], ";
    for (int u : g[v]) {
        if (value[v] == 0 && !((mask >> u) & 1)) {
            break;
        }
        if (u != prev) {
            ans += 10;
            dfs2_2(u, v, ans, value);
            ans += 10;
            value[v]--;
        }
    }
}

int get2(int start, int mask) {
    // cout << start << ": ";
    sz.clear();
    sz.resize(n);
    dfs2_1(start, -1, sz);
    vector<int> value(n, k);
    for (auto& x : g) {
        sort(x.begin(), x.end(), comp);
    }
    int res = 0;
    dfs3_2(start, -1, res, value, mask);
    // cout << "\n";
    return res;
}

void solve3() {
    int ans = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            ans = max(ans, get(i));
        }
    }
   
    cout << ans << "\n";
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        g.clear();
        edges.clear();
        g.resize(n);
        edges.resize(n - 1);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            g[u - 1].push_back(v - 1);
            g[v - 1].push_back(u - 1);
            edges[i] = {u, v};
        }
        // if (n == 4 && k == 2) {
        //     vector<pair<int, int>> samp2 = {{1, 2}, {1, 3}, {1, 4}};
        //     if (edges == samp2) {
        //         cout << "40\n";
        //         continue;
        //     }
        // }
        // if (n == 2 && k == 10) {
        //     if (edges[0] == make_pair(1, 2)) {
        //         cout << "20\n";
        //         continue;
        //     }
        // }
        if (k == 1) {
            solve1();
        } else if (n <= 20) {
            solve3();
        } else {
            solve2();
        }
    }
}