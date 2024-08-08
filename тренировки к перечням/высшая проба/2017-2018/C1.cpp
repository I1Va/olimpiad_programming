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
vector<int> sz, d, up;

void dfs(int v, int time, vector<int>& used, int& cnt, const edge& blocked, const vector<vector<edge_to>>& g) {
    used[v] = time;
    cnt++;
    up[v] = d[v];
    for (auto e : g[v]) {
        
        if (e.time < used[e.to] && time <= e.time) {
            if (e.to)
            d[e.to] = d[v] + 1;
            dfs(e.to, e.time, used, cnt, blocked, g);
            sz[v] += sz[e.to];
        }
        
    }
    
}

int main() {
    cin >> n >> m;
    edges.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].v >> edges[i].u >> edges[i].time;
        edges[i].num = i;
    }
    
}