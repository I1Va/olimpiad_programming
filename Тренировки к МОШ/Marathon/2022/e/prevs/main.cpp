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

int n;
vector<int> p;
vector<long long> a;
long long ans;

long long f(const vector<int>& p) {
    long long res = 0;
    for (int i = 0; i < n; i++) {
        string m = to_string(max(a[p[i]], a[p[i + n]])) + to_string(min(a[p[i]], a[p[i + n]]));
        res += stoll(m);
    }
    return res;
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

// void try_change_annealing() {

// }

void annealing(long double time) {
    p = build();
    // shuffle(p.begin(), p.end(), rnd);
    ans = f(p);
    long double t = 1;
    int iters = 0;
    clock_t start = clock();
    while ((iters % 100 != 0) || ((long double) (clock() - start) / CLOCKS_PER_SEC <= time)) {
        iters++;
        t *= 0.99;
        auto q = p;
        swap(q[randrange(0, 2 * n)], q[randrange(0, 2 * n)]);
        long long val = f(q);
        if (val > ans || chance() < exp((long double)(val - ans) / t)) {
            p = q;
            ans = val;
        }
    }
    
}

void cnt_an() {
    cin >> n;
    a.resize(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        cin >> a[i];
    }
    vector<int> end_p;
    long long end_ans = 0;
    int c = 10;
    long double time = 4;
    for (int i = 0; i < c; i++) {
        annealing(time / c);
        if (ans > end_ans) {
            end_ans = ans;
            end_p = p;
        }
    }
    vector<pair<int, int>> ps(n);
    // cout << "end_p: " << end_p << "\n";
    // cout << "f: " << f(end_p) << "\n";
    for (int i = 0; i < n; i++) {
        ps[i] = {end_p[i] + 1, end_p[i + n] + 1};
    }
    cout << end_ans << "\n";
    for (auto to : ps) {
        cout << to.first << " " << to.second << "\n";
    }    
}

void jad() {
    cin >> n;
    a.resize(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        cin >> a[i];
    }
    vector<int> end_p = build();
    long long end_ans = f(end_p);
    vector<pair<int, int>> ps(n);
    // cout << "end_p: " << end_p << "\n";
    // cout << "f: " << f(end_p) << "\n";
    for (int i = 0; i < n; i++) {
        ps[i] = {end_p[i] + 1, end_p[i + n] + 1};
    }
    cout << end_ans << "\n";
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

    vector<pair<int, int>> ps(n);
    vector<int> end_p = build();
    long long end_ans = f(end_p);
    cout << "end_p: " << end_p << "\n";
    cout << "f: " << f(end_p) << "\n";
    for (int i = 0; i < n; i++) {
        ps[i] = {end_p[i] + 1, end_p[i + n] + 1};
    }
    cout << end_ans << "\n";
    for (auto to : ps) {
        cout << to.first << " " << to.second << "\n";
    }    
    
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        jad();
    }
}