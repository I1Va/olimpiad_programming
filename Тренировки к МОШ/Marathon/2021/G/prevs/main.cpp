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
vector<int> p;
int ans;

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

void annealing(long double time) {
    p.clear();
    p.resize(n);
    for (int i = 0; i < min(n, k); i++) {
        p[i] = 1;
    }
    // cout << "p: " << p << "\n";
    shuffle(p.begin(), p.end(), rnd);
    long double t = 1;
    clock_t start = clock();
    int iters = 0;
    while (1) {
        // cout << iters << "\n";
        // cout << ans << "\n";
        iters++;
        if (iters % 100 == 0) {
            clock_t end = clock();
            if ((long double) (end - start) / CLOCKS_PER_SEC > time) {
                break;
            }
        }
        t *= 0.99;
        auto q = p;
        swap(q[randrange(0, n)], q[randrange(0, n)]);
        int val = f(q);
        if (val > ans || chance() < exp((long double)(val - ans) / t)) {
            ans = val;
            p = q;
        }
    }
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
    int c = 50;
    vector<int> end_p;
    int end_ans = 0;
    for (int i = 0; i < c; i++) {
        annealing(100.0 / c);
        if (ans > end_ans) {
            end_ans = ans;
            end_p = p;
        }
    }
    // cout << "p: " << end_p << "\n";
    vector<int> res;
    for (int i = 0; i < n; i++) {
        if (end_p[i]) {
            res.push_back(i + 1);
        }
    }
    cout << res.size() << "\n";
    for (auto x : res) {
        cout << x << " ";
    }
    cout << "\n\n";
}

int main() {
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}