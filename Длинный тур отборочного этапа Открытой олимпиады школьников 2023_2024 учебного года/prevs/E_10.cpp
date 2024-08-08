#include <iostream>
#include <vector>
using namespace std;

struct edge_to {
    int to, c;
    edge_to(): to{-1}, c{-1} {}
    edge_to(int to, int c): to{to}, c{c} {}
};

struct edge {
    int u, v, c;
    edge(): u{-1}, v{-1}, c{-1} {}
    edge(int u, int v, int c): u{u}, v{v}, c{c} {}
};

int n, m, k, q;
const bool deb = 0;
vector<vector<edge_to>> g;
vector<edge> edges;
vector<pair<int, int>> acts;

void print() {
    if (!deb) {
        return;
    }
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ": ";
        for (auto e: g[i]) {
            cout << e.to + 1 << "(" << e.c << ") "; 
        }
        cout << "\n";
    }
}

void dfs1(int v, vector<bool>& used, int& cnt) {
    used[v] = true;
    cnt++;
    for (auto e : g[v]) {
        if (!used[e.to]) {
            dfs1(e.to, used, cnt);
        }
    }
}

void solve1() {
    int cnt = 0;
    vector<bool> used(n, false);
    dfs1(0, used, cnt);
    if (cnt == n) {
        for (int i = 0; i < q; i++) {
            cout << "Yes\n";
        }
    } else {
        for (int i = 0; i < q; i++) {
            cout << "No\n";
        }
    }
}

int main() {
    cin >> n >> m >> k;
    g.resize(n);
    edges.resize(m);

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        edges[i] = edge(u - 1, v - 1, c);
        g[u - 1].emplace_back(v - 1, c);
        g[v - 1].emplace_back(u - 1, c);
    }
    print();
    cin >> q;
    acts.resize(q);
    for (int i = 0; i < q; i++) {
        int ei, ci;
        cin >> ei >> ci;
        acts[i] = make_pair(ei - 1, ci);
    }
    if (k <= 1) {
        solve1();
    }
}
