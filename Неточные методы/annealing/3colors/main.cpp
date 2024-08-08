#pragma GCC optimize("O3")
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
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

vector<vector<int>> g;
vector<int> p;
vector<pair<int, int>> edges;

int val;

int n, m;

int get(int b) {
    vector<int> pool;
    pool.reserve(3);
    for (int i = 1; i <= 3; i++) {
        if (i == b) {
            continue;
        }
        pool.push_back(i);
    }
    return pool[randrange(0, (int) pool.size())];
}

void build_dfs(int v, vector<int>& mark, int b) {
    mark[v] = get(b);
    for (int u : g[v]) {
        if (!mark[u]) {
            build_dfs(u, mark, mark[v]);
        }
    }
}

int cnt(int v) {
    int bad = 0;
    for (int u : g[v]) {
        if (p[u] == p[v]) {
            bad++;
        }
    }
    return bad;
}

int f(const vector<int>& p) {
    int bad = 0;
    for (auto edge : edges) {
        if (p[edge.first] == p[edge.second]) {
            bad++;
        }
    }
    return bad;
}

void change(int v, int c) {
    int bad1 = cnt(v);
    p[v] = c;
    int bad2 = cnt(v);
    val = val - bad1 + bad2;
}

int try_change(int v, int c) {
    int prev = p[v];
    change(v, c);
    int temp = val;
    change(v, prev);
    return temp;
}

void build(bool random) {
    if (random) {
        for (int i = 0; i < n; i++) {
            p[i] = randrange(1, 3 + 1);
        }
        return;
    }
    for (int i = 0; i < n; i++) {
        if (p[i]) {
            continue;
        }
        build_dfs(i, p, -1);
    }
}
bool try_change_annealing(long double time) {
    for (int i = 0; i < n; i++) {
        p[i] = 0;
    }
    build(0);
    // cout << "p: " << p << "\n";
    // cout << "val: " << val << "\n";
    int iters = 0;
    clock_t start = clock();
    long double t = 1.0;
    val = f(p);
    while (1) {
        t *= 0.99999;
        iters++;
        if (iters % 100 == 0) {
            clock_t end = clock();
            if ((long double) (end - start) / CLOCKS_PER_SEC > time) {
                break;
            }
        }
        if (!val) {
            return true;
        }
        int v = randrange(0, n);
        int c = randrange(1, 3 + 1);
        int temp = try_change(v, c);
        if (temp < val || chance() < exp((long double) (val - temp) / t)) {
            change(v, c);
        }
    }
    return !val;
}

void cnt_try_change_annealing(int c, long double time) {
    for (int _ = 0; _ < c; _++) {
        if (try_change_annealing(time / c)) {
            break;
        }
    }
}

bool annealing(long double time) {
    for (int i = 0; i < n; i++) {
        p[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        if (p[i]) {
            continue;
        }
        build_dfs(i, p, -1);
    }
    val = f(p);
    int iters = 0;
    clock_t start = clock();
    long double t = 1.0;
    while (1) {
        t *= 0.99;
        iters++;
        if (iters % 100 == 0) {
            clock_t end = clock();
            if ((long double) (end - start) / CLOCKS_PER_SEC > time) {
                break;
            }
        }
        if (!val) {
            return true;
        }
        auto q = p;
        q[randrange(0, n)] = randrange(1, 3 + 1);
        int temp = f(q);
        if (temp < val || chance() < exp((long double) (val - temp) / t)) {
            p = q;
            val = temp;
        }
    }
    return !val;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    g.resize(n);
    edges.resize(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u - 1, v - 1};
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    p.resize(n);
    cnt_try_change_annealing(30, 1.99);
    // cout << "p: " << p << "\n";
    // cout << "val: " << val << "\n";
    cout << p;
    // build_dfs(0, p, -1);
    // cout << "p: " << p << "\n";
    // cout << "val: " << val << "\n";
    // for (int i = 0; i < 100; i++) {
    //     try_change(randrange(0, n), randrange(1, 3 + 1));
    // }
    // cout << "p: " << p << "\n";
    // cout << "val: " << val << "\n";
}
