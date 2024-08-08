#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <map>
#include <chrono>
using namespace std;
auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto x : a) {
        stream << x << " ";
    }
    return stream;
}

int n, k;
vector<pair<long long, long long>> a;

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
    // cout << "p = " << p << "\n";
    long long mn = 1e18;
    vector<int> ans(n);
    for (int i = 0; i < 100000; i++) {
        shuffle(p.begin(), p.end(), rnd);
        long long res = get(p);
        if (res < mn) {
            mn = res;
            ans = p;
        }
    }
    // cout << "p = " << p << "\n";
    cout << "Q = " << mn << "\n";
    ans = transform(ans);
    for (auto x : ans) {
        cout << x << "\n";
    }
    // map<int, int> cnt;
    // for (auto to : ans) {
    //     cnt[to]++;
    // }
    // for (auto to : cnt) {
    //     cout << to.first << ": " << to.second << "\n";
    // }
}