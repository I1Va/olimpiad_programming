#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <set>
#include <cmath>
using namespace std;

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);

int randrange(int a, int b) {
    return a + rnd() % (b - a);
}

long double chance() {
    return (long double) rnd() / (rnd.max());
}

string s;
int n;
const int inf = 1e9;
vector<int> p;
set<int> ans;

set<int> f(const vector<int>& p) {
    set<int> pool;
    int si = 0;
    int pi = 0;
    while (si < n) {
        if (p[pi] == 2 && si + 1 < n) {
            string cur = string(1, s[si]) + string(1, s[si + 1]);
            if (cur[0] != '0') {
                pool.insert(stoi(cur));
                si += 2;
                pi++;
                continue;
            }
        }
        string cur = string(1, s[si]);
        pool.insert(stoi(cur));
        si++;
        pi++;
    }
    return pool;
}

void annealing(long double time) {
    p.resize(n);
    for (int i = 0; i < n; i++) {
        p[i] = randrange(1, 2 + 1);
    }
    long double t = 1;
    ans = f(p);
    int iters = 0;
    clock_t start = clock();
    while (1) {
        iters++;
        if (iters % 100 == 0) {
            clock_t end = clock();
            if ((long double) (end - start) / CLOCKS_PER_SEC > time) {
                break;
            }
        }
        t *= 0.99;
        auto q = p;
        q[randrange(0, n)] = randrange(1, 2 + 1);
        set<int> val = f(q);
        if (val < ans || chance() < exp((long double) ((int) ans.size() - (int) val.size()) / t)) {
            ans = val;
            p = q;
        }
    }
}

void solve() {
    cin >> s;
    set<int> end_ans;
    n = (int) s.size();
    int c = 20;
    long double time = 1.0 / 1000;
    for (int _ = 0; _ < c; _++) {
        annealing(time / c);
        if (end_ans.empty() || ans.size() < end_ans.size()) {
            end_ans = ans;
        }
    }
    if (end_ans.empty()) {
        cout << "1\n1\n";
    } else {
        cout << end_ans.size() << "\n";
        for (auto x : end_ans) {
            cout << x << " ";
        }
        cout << "\n";
    }
}
int main() {
    int q;
    cin >> q;
    while (q--) {
        solve();
    }

}