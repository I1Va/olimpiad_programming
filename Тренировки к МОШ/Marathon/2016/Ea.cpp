#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <random>
using namespace std;

const long double e = 2.71828182846;

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937_64 rnd(now);

long long randrange(long long a, long long b) {
    return a + rnd() % (b - a);
}

bool chance(long double x) {
    return randrange(0, 101) <= floor(x);
}

int n, k;
vector<pair<long long, long long>> a;

long long f(const vector<int>& p) {
    vector<pair<long long, long long>> groups(k);
    for (int i = 0; i < n; i++) {
        groups[i % k].first += a[p[i]].first;
        groups[i % k].second += a[p[i]].second;
    }
    long long Pmax = 0, Pmin = 1e18, Mmax = 0, Mmin = 1e18;
    for (auto x : groups) {
        Mmax = max(Mmax, x.first);
        Mmin = min(Mmin, x.first);
        Pmax = max(Pmax, x.second);
        Pmin = min(Pmin, x.second);
    }
    return Pmax - Pmin + Mmax - Mmin;
}

// void upd()
int main() {
    cin >> n >> k;
    a.resize(n);
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        v[i] = i;
    }
    shuffle(v.begin(), v.end(), rnd);
    long double t = 1;
    long long cur = f(v);
    int iters = 100000;
    long long ans = cur;
    while (iters--) {
        t *= 0.9;
        vector<int> u = v;
        swap(u[randrange(0, n)], u[randrange(0, n)]);
        long long val = f(u);
        ans = min(ans, cur);
        if (val < cur) {
            v = u;
        }
    }
    cout << ans;


}