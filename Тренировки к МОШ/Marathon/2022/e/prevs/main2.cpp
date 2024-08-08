#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>
#include <random>
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


struct node {
    int len;
    long long val;
    int idx;
    node() {}
    node(int _len, long long _val, int _idx) {
        len = _len;
        val = _val;
        idx = _idx;
    }
};

bool comp1(node a, node b) {
    if (a.len == b.len) {
        return a.val < b.len;
    }
    return a.len > b.len;
}

bool comp2(pair<long long, int> a, pair<long long, int> b) {
    return a.first > b.first;
}


int n;
vector<int> p;
vector<long long> a;
long long ans;

long long f(const vector<int>& p) {
    long long res = 0;
    for (int i = 0; i < n; i++) {
        string m = to_string(a[p[i]]) + to_string(a[p[i + n]]);
        res += stoll(m);
    }
    return res;
}

vector<int> build() {
    vector<node> lens(2 * n);
    vector<pair<long long, int>> b(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        b[i] = {a[i], i};
        lens[i] = node(to_string(a[i]).size(), a[i], i);
    }
    sort(lens.begin(), lens.end(), comp1);
    sort(b.begin(), b.end(), comp2);
    vector<bool> used(2 * n, false);
    vector<int> p(2 * n);
    int pi = 0;
    int li = 0;
    for (int i = 0; i < 2 * n; i++) {
        // cout << i << "\n";
        if (used[b[i].second]) {
            continue;
        }
        used[b[i].second] = true;
        while (used[lens[li].idx]) {
            li++;
        }
        // cout << "li: " << li << "\n";
        p[pi] = b[i].second;
        p[pi + n] = lens[li].idx;
        pi++;
        used[lens[li].idx] = true;
    }
    return p;
}

pair<int, int> tr(int u) {
    pair<int, int> fir;
    if (u < n) {
        fir = {u, u + n};
    } else {
        fir = {u - n, u};
    }
    return fir;
}

void change(int u, int v) {
    // pair<int, int> fir = tr(u), sec = tr(v);
    // string m1 = to_string(a[p[fir.first]]) + to_string(a[p[fir.second]]);
    // string m2 = to_string(a[p[sec.first]]) + to_string(a[p[sec.second]]);
    // long long cnt1 = stoll(m1) + stoll(m2);
    // swap(p[u], p[v]);
    // m1 = to_string(a[p[fir.first]]) + to_string(a[p[fir.second]]);
    // m2 = to_string(a[p[sec.first]]) + to_string(a[p[sec.second]]);
    // long long cnt2 = stoll(m1) + stoll(m2);
    // ans = ans - cnt1 + cnt2;
    swap(p[u], p[v]);
    ans = f(p);
}

long long try_change(int u, int v) {
    change(u, v);
    long long temp = ans;
    change(u, v);
    return temp;
}

void annealing(long double time) {
    p = build();
    ans = f(p);
    long double t = 1;
    int iters = 0;
    clock_t start = clock();
    while ((iters % 100 != 0) || ((long double) (clock() - start) / CLOCKS_PER_SEC <= time)) {
        iters++;
        t *= 0.99;
        int u = randrange(0, 2 * n);
        int v = randrange(0, 2 * n);
        long long val = try_change(u, v);
        if (val > ans || chance() < exp((long double)(val - ans) / t)) {
            change(u, v);
        }
    }
}

void answer(const vector<int>& p) {
    vector<pair<int, int>> ps(n);
    for (int i = 0; i < n; i++) {
        ps[i] = {p[i] + 1, p[i + n] + 1};
    }
    cout << ans << "\n";
    for (auto to : ps) {
        cout << to.first << " " << to.second << "\n";
    }
}

void solve() {
    cin >> n;
    a.resize(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        cin >> a[i];
    }
    vector<int> end_p;
    long long end_ans = 0;
    int c = 20;
    for (int i = 0; i < c; i++) {
        annealing(1.0 / c);
        if (ans > end_ans) {
            end_ans = ans;
            end_p = p;
        }
    }
    answer(end_p);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}