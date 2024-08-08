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

int main() {
    
    cin >> n >> k;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        p[v - 1] = i;
    }
    cout << get(p);
}