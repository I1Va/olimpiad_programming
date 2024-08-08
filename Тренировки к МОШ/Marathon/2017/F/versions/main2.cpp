#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <stdio.h> 
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

long long gl_W, gl_H, gl_ans;
clock_t start;
vector<long long> gl_path;

void rec(long long w, long long h, long long res, long long mul, vector<long long> path) {
    if ((long double) (clock() - start) / CLOCKS_PER_SEC >= 30) {
        return;
    }
    if (path.size() > gl_path.size() && res < gl_ans) {
        return;
    }
    if (min(w, h) - 2 < 1) {
        if (res > gl_ans) {
            gl_ans = res;
            gl_path = path;
        }
        return;
    }
    path.push_back(0);
    long long g = min(w, h);
    vector<long long> vars;
    vars.reserve((g - 1) / 2);
    for (long long x = 1; x <= (g - 1) / 2; x++) {
        vars.push_back(x);
    }
    shuffle(vars.begin(), vars.end(), rnd);
    for (long long x : vars) {
        path[(int) path.size() - 1] = x;
        rec(x, x, res + (w - 2 * x) * (h - 2 * x) * x * mul, mul * 4, path);
    }
}

void solve() {
    gl_ans = 0;
    gl_path.clear();
    cin >> gl_W >> gl_H;
    start = clock();
    rec(gl_W, gl_H, 0, 1, {});
    cout << gl_ans << "\n";
    // cout << gl_path.size() << " " << gl_path << "\n";

}
int main() {
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}