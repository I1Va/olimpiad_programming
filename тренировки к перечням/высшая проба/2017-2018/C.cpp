#include <iostream>
#include <vector>
using namespace std;

struct edge {
    int v, u, time, num;
    edge(): v{-1}, u{-1}, time{-1}, num{-1} {}
    edge(int v, int u, int time, int num): v{v}, u{u}, time{time}, num{num} {};
    bool operator == (const edge& b) {
        return num == b.num;
    } 
};

ostream& operator<< (ostream& stream, const edge& a) {
    stream << a.v << " " << a.u << " " << a.time;
    return stream;
}

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to + 1 << " ";
    }
    return stream;
}

struct edge_to {
    int to;
    int time;
    int num;
    edge_to(): to{-1}, time{-1}, num{-1} {}
    edge_to(int to, int time, int num): to{to}, time{time}, num{num} {}
};


int n, m;
vector<edge> edges;

void dfs(int v, int time, vector<int>& used, int& cnt, const edge& blocked, const vector<vector<edge_to>>& g) {
    used[v] = time;
    cnt++;
    for (auto e : g[v]) {
        if (edge(v, e.to, e.time, e.num) == blocked) {
            continue;
        }
        if (e.time < used[e.to] && time <= e.time) {
            dfs(e.to, e.time, used, cnt, blocked, g);
        }
    }
}

void solve1() {
    int INF = 1e9;
    vector<vector<edge_to>> g(n);
    for (auto e : edges) {
        g[e.u - 1].emplace_back(e.v - 1, e.time, e.num);
        g[e.v - 1].emplace_back(e.u - 1, e.time, e.num);
    }
    int mn = 1e9;
    edge ans;
    for (auto e : edges) {
        e.u--;
        e.v--;
        int cnt = 0;
        vector<int> used(n, INF);
        dfs(0, 0, used, cnt, e, g);
        if (cnt < mn) {
            mn = cnt;
            ans = e;
        }
    }
    ans.u++;
    ans.v++;
    cout << ans;
}

void dfs2(int v, int time, vector<int>& used, const vector<vector<edge_to>>& g, vector<vector<int>>& g_new) {
    used[v] = time;
    for (auto e : g[v]) {
        if (e.time < used[e.to] && time < e.time) {
            // cout << v + 1 << "->" << e.to + 1 << "\n";
            g_new[v].push_back(e.to);
            g_new[e.to].push_back(v);
            dfs2(e.to, e.time, used, g, g_new);
        }
    }
}

void most_dfs(int v, vector<bool> used, vector<int>& d, vector<int>& up, vector<int>& sz, const vector<vector<int>> g) {
    up[v] = d[v];
    for (int u : g[v]) {
        if (!used[u]) {
            d[u] = d[v] + 1;
            most_dfs(u, used, d, up, sz, g);
            if (up[u] > d[v]) {
                // не мост
            }
            sz[v] += sz[u];
        } else {
            up[v] = min(up[v], d[u]);
        }
    }
}
void solve2() {
    int INF = 1e9 + 7;
    vector<vector<edge_to>> g(n);
    for (auto e : edges) {
        g[e.u - 1].emplace_back(e.v - 1, e.time, e.num);
        g[e.v - 1].emplace_back(e.u - 1, e.time, e.num);
    }
    vector<int> used(n, INF);
    vector<vector<int>> g_new(n);
    dfs2(0, 0, used, g, g_new);
    // for (int i = 0; i < n; i++) {
    //     cout << i + 1 << ": " << g_new[i] << "\n";
    // }


}
int main() {
    cin >> n >> m;
    edges.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].v >> edges[i].u >> edges[i].time;
        edges[i].num = i;
    }
    solve2();
}