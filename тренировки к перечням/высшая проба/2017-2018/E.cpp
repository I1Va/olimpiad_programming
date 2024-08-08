#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

struct edge {
    int v, u, d;
    edge(): v{-1}, u{-1}, d{-1} {}
    edge(int v, int u, int d): v{v}, u{u}, d{d} {}
};

struct edge_to {
    int to, d, num;
    edge_to(): to{-1}, d{-1}, num{-1} {};
    edge_to(int to, int d, int num): to{to}, d{d}, num{num} {}
};

int n, m;
vector<edge> edges;
vector<vector<edge_to>> g;

void dfs(int v, int prev, vector<int>& used, bool& state, const int& mask) {
    used[v] = 1;
    // cout << v + 1 << " ";
    for (auto e : g[v]) {
        if (e.to == prev) {
            continue;
        }
        if (e.d == 2) {
            if ((v < e.to) != ((mask >> e.num) & 1)) { // нет ребра
                continue;
            }
        }
        if (used[e.to] == 0) {
            dfs(e.to, v, used, state, mask);
        } else if (used[e.to] == 1) {
            state = false;
        }
    }
    used[v] = 2;
}

void print_gr(int mask) {
    cout << "print gr:\n";
    for (int i = 0; i < m; i++) {
        if (edges[i].d == 1) {
            cout << edges[i].v << " " << edges[i].u << "\n";
        } else {
            pair<int, int> cur = {min(edges[i].u, edges[i].v), max(edges[i].u, edges[i].v)};
            if (!((mask >> i) & 1)) {
                swap(cur.first, cur.second);
            }
            cout << cur.first << " " << cur.second << "\n";
        }
    }
    cout << "\n";
}

int main() {
    cin >> n >> m;
    edges.resize(m);
    vector<int> vers;
    for (int i = 0; i < m; i++) {   
        cin >> edges[i].v >> edges[i].u >> edges[i].d;
        vers.push_back(edges[i].v - 1);
        vers.push_back(edges[i].u - 1);
    }
    g.resize(n);
    for (int i = 0; i < m; i++) {
        auto to = edges[i];
        if (to.d == 2) {
            g[to.v - 1].emplace_back(to.u - 1, to.d, i);
            g[to.u - 1].emplace_back(to.v - 1, to.d, i);
        } else {
            g[to.v - 1].emplace_back(to.u - 1, to.d, i);
        }
        
    }
    for (int mask = 0; mask < (1 << m); mask++) {
        bool state = true;
        for (auto to : vers) {
            vector<int> used(n, 0);
            dfs(to, -1, used, state, mask);
        }
        
        // cout << state << "\n";
        if (state) {
            for (int i = 0; i < m; i++) {
                if (edges[i].d == 2) {
                    pair<int, int> cur = {min(edges[i].u, edges[i].v), max(edges[i].u, edges[i].v)};
                    if (!((mask >> i) & 1)) {
                        swap(cur.first, cur.second);
                    }
                    cout << cur.first << " " << cur.second << "\n";
                }
            }
            exit(0);
        }
    }
}