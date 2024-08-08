#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <set>
#include <cmath>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);

int randrange(int a, int b) {
    return a + rnd() % (b - a);
}

long double chance() {
    return (long double) rnd() / (rnd.max());
}

int n, m, k;
vector<vector<int>> g;

int f(const vector<int>& p) {
    vector<bool> used(n);
    for (int i = 0; i < n; i++) {
        if (p[i]) {
            used[i] = true;
            for (int j : g[i]) {
                used[j] = true;
            }
        }
    }
    int c = 0;
    for (auto x : used) {
        c += x;
    }
    return c;
}

void solve() {
    cin >> n >> m >> k;
    g.clear();
    g.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[v - 1].push_back(u - 1);
        g[u - 1].push_back(v - 1);
    }
    vector<int> p(n, 0);
    for (int i = 0; i < min(n, k); i++) {
        p[i] = 1;
    }
    int ans = 0;
    vector<int> res;
    for (int i = 0; i < 10000; i++) {
        shuffle(p.begin(), p.end(), rnd);
        int val = f(p);
        if (val > ans) {
            ans = val;
            res = p;
        }
    }
    vector<int> end;
    for (int i = 0; i < n; i++) {
        if (p[i]) {
            end.push_back(i + 1);
        }
    }
    cout << end.size() << "\n";
    for (auto to : end) {
        cout << to << " ";
    }
    cout << "\n";
}

int main() {
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}