#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <string>
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







int n;
vector<long long> a;
vector<int> p;
long long ans;

long long f(long long a, long long b) {
    return stoll(to_string(a) + to_string(b));
}

long long build(const vector<int>& p) {
    long long res = 0;
    for (int i = 0; i < 2 * n; i += 2) {
        res += f(a[p[i]], a[p[i + 1]]);
    }
    return res;
}

long long get(int u) {
    if (u % 2 == 0) {
        return f(a[p[u]], a[p[u + 1]]);
    }
    return f(a[p[u - 1]], a[p[u]]);
}

void change(int u, int v) {
    long long cnt1 = 0, cnt2 = 0;
    cnt1 = get(u) + get(v);
    swap(p[u], p[v]);
    cnt2 = get(u) + get(v);
    ans = ans - cnt1 + cnt2;
}

long long try_change(int u, int v) {
    change(u, v);
    long long val = ans;
    change(u, v);
    return val;
}

void annealing(long double time) {
    for (int i = 0; i < 2 * n; i++) {
        p[i] = i;
    }
    shuffle(p.begin(), p.end(), rnd);
    ans = build(p);
    long double t = 0.5;
    int iters = 0;
    clock_t start = clock();
    while (iters % 100 != 0 || (long double) (clock() - start) / CLOCKS_PER_SEC <= time) {
        iters++;
        t *= 0.99;
        int u = randrange(0, 2 * n), v = randrange(0, 2 * n);
        long long val = try_change(u, v);
        if (val > ans || chance() < exp((long double)(val - ans) / t)) {
            change(u, v);
        }
    }
}

void answer(const vector<int>& p) {
    vector<pair<int, int>> ans;
    for (int i = 0; i < 2 * n; i += 2) {
        ans.push_back({p[i] + 1, p[i + 1] + 1});
    }
    for (auto to : ans) {
        cout << to.first << " " << to.second << "\n";
    }
    cout << "\n";
}

void solve() {
    cin >> n;
    a.resize(2 * n);
    p.resize(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        cin >> a[i];
    }
    // cout << "done\n";
    vector<int> end_p;
    long long end_ans = 0;
    int c = 10;
    long double time = 5;
    for (int i = 0; i < c; i++) {
        // cout << "annealing";
        annealing(time / c);
        if (ans > end_ans) {
            end_ans = ans;
            end_p = p;
        }
    }
    // cout << end_ans << "\n";
    cout << build(end_p) << "\n";
    answer(end_p);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}