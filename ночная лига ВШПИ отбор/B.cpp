#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct node {
    long long p, q;
    node(): p{0}, q{0} {}
    node(long long p, long long q): p{p}, q{q} {}
    bool operator == (node b) {
        return p == b.p && q == b.q;
    }
};

struct ans {
    int j, l, r;
    ans(): j{0}, l{0}, r{0} {}
    ans(int j, int l, int r): j{j}, l{l}, r{r} {}
};

node act(node a, node b) {
    long long p = a.p * b.q + b.p * a.q;
    long long q = a.q * b.q;
    long long g = gcd(p, q);
    return node(p / g, q / g);
}

void check(vector<int>& temp, const vector<node>& a, int fir, int sec) {
    vector<int> cur = {fir, sec};
    vector<ans> res;
    for (auto x : temp) {
        bool state = true;
        int a1, a2;
        for (auto u : cur) {
            for (auto v : cur) {
                if (u == v) {
                    continue;
                }
                if (act(a[u], a[v]) == a[x]) {
                    state = false;
                    a1 = u;
                    a2 = v;
                    break;
                }
            }
            if (!state) {
                break;
            }
        }
        if (state) {
            return;
        }
        cur.push_back(x);
        res.emplace_back(x, a1, a2);
    }
    cout << "YES\n";
    for (auto to : res) {
        cout << to.j + 1 << " " << to.l + 1 << " " << to.r + 1 << "\n";
    }
    exit(0);
}

int main() {
    int n;
    cin >> n;
    vector<node> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].p >> a[i].q;
    }
    vector<int> pool;
    int fir, sec;
    for (int i = 0; i < n; i++) {
        if (a[i] == node(0, 1)) {
            fir = i;
        }
        else if (a[i] == node(1, 1)) {
            sec = i;
        } else {
            pool.push_back(i);
        }
    }
    check(pool, a, fir, sec);
    while (next_permutation(pool.begin(), pool.end())) {
        check(pool, a, fir, sec);
    }
}