#include <iostream>
#include <vector>
#include <string>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

int n, k;
vector<vector<int>> g;
vector<int> d;
vector<bool> targs;
long long res = 0;
bool deb = 1;

int dfs(int v, int prev) {
    int c = 0;
    for (int u : g[v]) {
        if (u == prev) {
            continue;
        }
        d[u] = d[v] + 1;
        c += dfs(u, v);
    }
    if (targs[v]) {
        c += 1;
        res += d[v];
    }
    
    res -= max(0, c - 1) * d[v];
    if (deb) {
        cout << "v = " << v + 1 << ", d[v] = " << d[v] << ", c = " << c << ", target = " << targs[v] << ", res = " << res << ", ret_c = " << c - max(0, c - 1) << "\n";
    }
    c -= max(0, c - 1);
    return c;
}

void print_gr() {
    if (!deb) {
        return;
    }
    cout << string(10, '=') << "gr" << string(10, '=') << "\n";
    for (int i = 0; i < n; i++) {
        cout << i  + 1 << ": ";
        for (auto x : g[i]) {
            cout << x + 1 << " ";
        }
        cout << "\n";
    }
    cout << string(10, '=') << "gr" << string(10, '=') << "\n";
}

int main() {
    deb = 0;
    cin >> n >> k;
    d.resize(n);
    targs.resize(n);
    g.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int v;
        cin >> v;
        g[v - 1].push_back(i + 1);
        // g[i + 1].push_back(v - 1);
    }
    for (int i = 0; i < k; i++) {
        int v;
        cin >> v;
        targs[v - 1] = true;
    }
    print_gr();
    d[0] = 1;
    dfs(0, -1);
    cout << res;
}