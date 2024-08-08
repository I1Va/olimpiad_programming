#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

ostream& operator<< (ostream& stream, const pair<int, long long>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream;
}

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

struct edge {
    int u, v;
    long long w;
    int num;
    edge(int u, int v, long long w, int num): u{u}, v{v}, w{w}, num{num} {};
    edge(): u{-1}, v{-1}, w{0}, num{-1} {};
};

bool comp(const edge& a, const edge& b) {
    return a.w < b.w;
}

int n, m;
vector<int> p, sz;

int get(int v) {
    if (p[v] == v) {
        return v;
    }
    return p[v] = get(p[v]);
}

void unite(int a, int b) {
    if (sz[a] < sz[b]) {
        swap(a, b);
    }
    p[b] = a;
    sz[a] += sz[b];
}

int main() {
    
    cin >> n >> m;
    p.resize(n);
    sz.resize(n);
    for (int i = 0; i < n; i++) {
        p[i] = i;
        sz[i] = 1;
    }
    vector<edge> edges(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        long long w;
        cin >> a >> b >> w;
        edges[i] = edge(a - 1, b - 1, w, i);
    }
    sort(edges.begin(), edges.end(), comp);
    vector<int> ans;
    for (auto edge : edges) {
        if (p[edge.u] == p[edge.v]) {
            continue;
        }
        if (edge.w >= 0) {
            continue;
        }
        unite(edge.u, edge.v);
        ans.push_back(edge.num + 1);
    }
    cout << ans.size() << "\n";
    cout << ans;
}