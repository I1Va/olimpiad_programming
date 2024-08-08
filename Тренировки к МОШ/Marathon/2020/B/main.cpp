#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <chrono>
using namespace std;

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);

struct point {
    int x, y, z;
    point(int x, int y, int z): x{x}, y{y}, z{z} {};
    point(): x{0}, y{0}, z{0} {};
};

int n, r, m;
string path = "";

long double dist(point a, point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

point nearest(point a, const vector<point>& pool) {
    long double val = 1e18;
    point ans;
    for (auto w : pool) {
        long double temp = dist(a, w);
        if (temp < val) {
            val = temp;
            ans = w;
        }
    }
    return ans;
}

long double f(const vector<int>& p, const vector<point>& a, const vector<point>& pool) {
    path = "";
    point cur = point(0, 0, 1);
    int fuel = m;
    long double ans = 0;
    for (auto idx : p) {
        if (!fuel) {
            point next = nearest(cur, pool);
            path += "F(" + to_string(next.x) + "," + to_string(next.y) + ") ";
            ans += dist(cur, next);
            fuel = m;
            cur = next;
        }
        ans += dist(cur, a[idx]);
        path += to_string(idx + 1) + " ";
        cur = a[idx];
        fuel--;
    }
    ans += dist(cur, point(0, 0, 1));
    path += "B";
    return ans;
}

void solve() {
    
    cin >> n >> r >> m;
    vector<point> a(n);
    vector<point> pool;
    for (int x = -100; x <= 100; x++) {
        for (int y = -100; y <= 100; y++) {
            if (x * x + y * y <= r * r) {
                pool.push_back(point(x, y, 0));
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y >> a[i].z;
    }
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
    
    long double ans = 1e9;
    string ans_path;
    int iters = 1000000;
    for (int ic = 0; ic < iters; ic++) {
        shuffle(p.begin(), p.end(), rnd);
        long double temp = f(p, a, pool);
        if (temp < ans) {
            ans = temp;
            ans_path = path;
        }
    }
    // cout << "ans: " << ans << "\n";
    cout << ans_path << "\n";
}

int main() {
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}