#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <stdio.h> 
#include <cmath>
#include <time.h> 
#include <random>
using namespace std;

auto now = chrono::high_resolution_clock().now().time_since_epoch().count();
mt19937 rnd(now);

ostream& operator<< (ostream& stream, const vector<long long>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

long long f(long long x, long double k, long long w, long long h) {
    long long res = 0;
    long long mul = 1;
    while (1) {
        if (min(w, h) - 2 * x < 1) {
            return res;
        }
        res += (w - 2 * x) * (h - 2 * x) * x;
        mul *= 4;
        w = x;
        h = x;
        x = floor(x * k);
    }
}

vector<long long> recover(long long w, long long h, pair<long long, long double> p) {
    vector<long long> res;
    while (1) {
        if (min(w, h) - 2 * p.first < 1 || p.first == 0) {
            return res;
        }
        res.push_back(p.first);
        w = p.first;
        h = p.first;
        p.first = floor(p.first * p.second);
    }
}

void solve() {
    long long w, h;
    cin >> w >> h;
    long long ans = 0;
    pair<long long, long double> p;
    for (long long x = 1; x <= min(w, h); x++) {
        // cout << x << "\n";
        for (long double k = 0.16; k <= 0.17; k += 0.0001) {
            long long res = f(x, k, w, h);
            if (res > ans) {
                // cout << res << ": " << x << " " << k << "\n";
                ans = res;
                p = {x, k};
            }
        }
        
    }
    vector<long long> path = recover(w, h, p);
    cout << path.size() << " " << path << "\n";
}

int main() {
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}