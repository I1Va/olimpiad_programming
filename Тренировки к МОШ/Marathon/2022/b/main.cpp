#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <set>
using namespace std;

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);

struct node {
    int l1, r1, l2, r2;
    long long w;
    node() {}
    node(int _l1, int _r1, int _l2, int _r2, int _w) {
        l1 = _l1;
        r1 = _r1;
        l2 = _l2;
        r2 = _r2;
        w = _w;
    }
};

const long long inf = 1e18;

void add(int l1, int r1, int l2, int r2, long long w, vector<vector<pair<long long, int>>>& g) {
    for (int i = l1 - 1; i < r1; i++) {
        for (int j = l2 - 1; j < r2; j++) {
            g[i].push_back({w, j});
            g[j].push_back({w, i});
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<long long, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        g[u - 1].push_back({w, v - 1});
        g[v - 1].push_back({w, u - 1});
    }
    int q;
    cin >> q;
    for (int _ = 0; _ < q; _++) {
        int l1, r1, l2, r2;
        long long w;
        cin >> l1 >> r1 >> l2 >> r2 >> w;
        add(l1, r1, l2, r2, w, g);
    }

    int s, e;
    cin >> s >> e;
    s--, e--;
    vector<long long> dist(n, inf);
    set<pair<long long, int>> p;
    dist[s] = 0;
    p.insert({0, s});
    while (p.size()) {
        int v = p.begin() -> second;
        p.erase(p.begin());
        for (auto [w, u] : g[v]) {
            if (dist[u] > dist[v] + w) {
                p.erase({dist[u], u});
                dist[u] = dist[v] + w;
                p.insert({dist[u], u});
            }
        }
    }
    cout << dist[e] << "\n";
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        solve();   
    }
}