#pragma GCC optimize("O3")
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
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

struct node {
    int i1, i2, i3;
    bool e1, e2, e3;
    node() {}
    node(int _i1, bool _e1, int _i2, bool _e2, int _i3, bool _e3) {
        i1 = _i1;
        e1 = _e1;
        i2 = _i2;
        e2 = _e2;
        i3 = _i3;
        e3 = _e3;
    }
    bool get(int x1, int x2, int x3) {
        return (x1 == e1) || (x2 == e2) || (x3 == e3);
    }
};

ostream& operator<< (ostream& stream, const node& a) {
    stream << "{i1: " << a.i1 << ", e1: " << a.e1
    << ", i2: " << a.i2 << ", e2: " << a.e2
    << ", i3: " << a.i3 << ", e3: " << a.e3 << "}";
    return stream;
}

int n, m;
vector<node> nodes;

int f(const vector<bool>& p) {
    int c = 0;
    for (int i = 0; i < m; i++) {
        // cout << nodes[i];
        c += nodes[i].get(p[nodes[i].i1], p[nodes[i].i2], p[nodes[i].i3]);
    }
    return c;
}

vector<bool> p;

bool annealing(long double time) {
    for (int i = 0; i < n; i++) {
        p[i] = randrange(0, 2);
    }
    long double t = 1;
    int iters = 0;
    int val = f(p);
    clock_t start = clock();
    while (1) {
        if (val == m) {
            return true;
        }
        iters++;
        if (iters % 100 == 0) {
            clock_t end = clock();
            if ((long double) (end - start) / CLOCKS_PER_SEC > time) {
                // cout << (long double) (end - start) / CLOCKS_PER_SEC << "\n";
                break;
            }
        }
        t *= 0.99;
        auto q = p;
        int idx = randrange(0, n);
        q[idx] = !q[idx];
        int temp = f(q);
        if (temp > val || chance() < exp((long double) (temp - val) / t)) {
            val = temp;
            p = q;
        }
    }
    return (val == m);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    nodes.resize(m);
    p.resize(n);
    for (int i = 0; i < m; i++) {
        int i1, e1, i2, e2, i3, e3;
        cin >> i1 >> e1 >> i2 >> e2 >> i3 >> e3;
        nodes[i] = node(i1 - 1, e1, i2 - 1, e2, i3 - 1, e3);
    }
    long double time = 1.9;
    int c = 10;
    for (int _ = 0; _ < c; _++) {
        if (annealing(time / c)) {
            break;
        }
    }
    for (auto x : p) {
        cout << x;
    }
}
