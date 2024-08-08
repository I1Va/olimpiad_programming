#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <chrono>
using namespace std;
auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937_64 rnd(now);

long long randrange(long long a, long long b) {
    return a + rnd() % (b - a);
}

bool chance(int x) {
    return (randrange(1, 100 + 1) <= x);
}

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto x : a) {
        stream << x << " ";
    }
    return stream;
}

int n, k;
vector<pair<long long, long long>> a;

struct node {
    vector<int> p;
    node() {
        p.resize(0);
    }
    node(vector<int> p): p{p} {};
    node(int n) {
        p.resize(n);
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
        shuffle(p.begin(), p.end(), rnd);
    }
};

node cross(node& a, node& b, const int& common_features) {
    vector<int> m(n, -1);
    vector<bool> used(n, false);
    vector<bool> used_idx(n, false);
    for (int _ = 0; _ < common_features; _++) {
        // cout << "_ = " << _ << "\n";
        while (1) {
            int idx = randrange(0, n);
            // cout << idx << " " << a.p.size() << " " << b.p.size() << " " << a.p[idx] << " " << b.p[idx] << "\n";
            if (used_idx[idx] || (used[a.p[idx]] && used[b.p[idx]])) {
                continue;
            }
            used_idx[idx] = true;
            if (!used[a.p[idx]] && chance(50) || used[b.p[idx]]) {
                m[idx] = a.p[idx];
                used[a.p[idx]] = true;
            } else {
                m[idx] = b.p[idx];
                used[b.p[idx]] = true;
            }
            break;
        } 
    }
    // cout << "m = " << m << "\n";
    vector<int> rem;
    rem.reserve(n);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            rem.push_back(i);
        }
    }
    // cout << "rem: " << rem << "\n";
    shuffle(rem.begin(), rem.end(), rnd);
    int rem_i = 0;
    int m_i = 0;
    while (rem_i < (int) rem.size()) {
        // cout << rem_i << " " << m_i << "\n";
        if (m[m_i] != -1) {
            m_i++;
        } else {
            m[m_i] = rem[rem_i];
            rem_i++;
            m_i++;
        }
    }
    return node(m);
}

void mutation(node& a, const int mutation_cnt) {
    for (int _ = 0; _ < mutation_cnt; _++) {
        swap(a.p[randrange(0, n)], a.p[randrange(0, n)]);
    }
}

long long get(const vector<int>& p) {
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

bool comp(const node& a, const node& b) {
    return get(a.p) < get(b.p);
}

void elimination(vector<node>& data, int sz) {
    sort(data.begin(), data.end(), comp);
    vector<node> res(sz);
    for (int i = 0; i < sz; i++) {
        res[i] = data[i].p;
    }
    data = res;
}

vector<int> transform(const vector<int>& data) {
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[data[i]] = i % k + 1;
    }
    return ans;
    // for (auto x : ans) {
    //     cout << x << "\n";
    // }
}

void print(const vector<int>& data) {
    for (auto to : data) {
        cout << to << "\n";
    }
}

int main() {
    
    cin >> n >> k;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
    
    vector<node> pool;
    int sz = 200;
    for (int i = 0; i < sz; i++) {
        pool.push_back(node(n));
    }
    int crossing_cnt = 10;
    int common_features = 30;
    int mutation_cnt = 0;
    int mutation_features = 0;
    long long mn = 1e18;
    vector<int> ans;
    
    for (int cycle = 0; cycle < 100; cycle++) {
        vector<node> new_gen;
        for (int _ = 0; _ < crossing_cnt; _++) {
            int fir = randrange(0, (int) pool.size());
            int sec = randrange(0, (int) pool.size());
            auto kid = cross(pool[fir], pool[sec], common_features);
            new_gen.push_back(kid);
        }
        for (auto x : pool) {
            new_gen.push_back(x);
        }
        pool = new_gen;
        for (int _ = 0; _ < mutation_cnt; _++) {
            mutation(pool[randrange(0, (int) pool.size())], mutation_cnt);
        }
        elimination(pool, sz);
        long long temp = get(pool[0].p);
        if (temp < mn) {
            mn = temp;
            ans = pool[0].p;
        } 
    }
    print(transform(ans));
    cout << "Q = " << get(ans) << "\n";
}