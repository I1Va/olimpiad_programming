#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <random>
using namespace std;

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);

int randrange(int a, int b) {
    return a + rnd() % (b - a);
}

long double chance() {
    return (long double) rnd() / rnd.max();
}

int n, m, c;
int ans;
vector<vector<int>> a(10, vector<int>(10));

void build() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = randrange(1, c + 1);
        }
    }
}

bool coin(int a, int b, int c, int d) {
    if (b != a) {
        return false;
    }
    if (c != a) {
        return false;
    }
    if (d != a) {
        return false;
    }
    return true;
}

int f(const vector<vector<int>>& a) {
    int res = 0;
    for (int x1 = 0; x1 < n; x1++) {
        for (int y1 = 0; y1 < m; y1++) {
            for (int x2 = x1 + 1; x2 < n; x2++) {
                for (int y2 = y1 + 1; y2 < m; y2++) {
                    auto s = coin(a[x1][y1], a[x2][y1], a[x1][y2], a[x2][y2]);
                    if (s) {
                        // cout << x1 << " " << y1 << " " << x2 << " " << y2 << ": " << s << "\n";
                        res++;
                    }
                }
            }
        }
    }
    return res;
}

int cnt(int x1, int y1) {
    int cnt = 0;
    for (int x2 = 0; x2 < n; x2++) {
        for (int y2 = 0; y2 < m; y2++) {
            if (x1 == x2 || y1 == y2) {
                continue;
            }
            if (coin(a[x1][y1], a[x1][y2], a[x2][y1], a[x2][y2])) {
                cnt++;
                // cout << "+ " << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
            }
        }
    }
    return cnt;
}

void change(int u, int v, int nc) {
    int cnt1 = cnt(u, v);
    a[u][v] = nc;
    int cnt2 = cnt(u, v);
    // cout << "cnt1/2: " << cnt1 << " " << cnt2 << "\n";
    ans = ans - cnt1 + cnt2;
}

int try_change(int u, int v, int nc) {
    int prev = a[u][v];
    change(u, v, nc);
    int val = ans;
    change(u, v, prev);
    return val;
}

void print() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
}

bool annealing() {
    long double t = 1;
    build();
    ans = f(a);
    int iters = 1e4;
    while (iters--) {
        t *= 0.99;
        int u = randrange(0, n);
        int v = randrange(0, m);
        int nc = randrange(1, c + 1);
        int val = try_change(u, v, nc);
        // cout << ans << "\n";
        if (val < ans || chance() < exp((long double) (ans - val) / t)) {
            change(u, v, nc);
        }
    }
    return !ans;
}

void solve() {
    cin >> n >> m >> c;
    for (int i = 0; i < 10; i++) {
        if (annealing()) {
            break;
        }
    }
    print();
}

int main() {
    solve();
}
