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
                    res += coin(a[x1][y1], a[x2][y1], a[x1][y2], a[x2][y2]);
                }
            }
        }
    }
    return res;
}



int main() {
    cin >> n >> m >> c;
    vector<vector<int>> a(10, vector<int>(10));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = randrange(1, c + 1);
        }
    }
    long double t = 1;
    int ans = f(a);
    while (ans != 0) {
        t *= 0.99;
        int u = randrange(0, n);
        int v = randrange(0, m);
        int nc = randrange(1, c + 1);
        auto b = a;
        b[u][v] = nc;
        int val = f(b);
        if (val < ans || chance() < exp((long double) (ans - val) / t)) {
            ans = val;
            a = b;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
}
