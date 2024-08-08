#include <iostream>
#include <vector>
using namespace std;

ostream& operator<< (ostream& stream, const vector<long long>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

long long gl_W, gl_H, gl_ans;
vector<long long> gl_path;

void get(const vector<long long>& path) {
    long long res = 0;
    long long mul = 1;
    long long w = gl_W;
    long long h = gl_H;
    for (auto x : path) {
        res += (w - 2 * x) * (h - 2 * x) * x * mul;
        mul *= 4;
        w = x;
        h = x;
    }
    // cout << "get(" << path << "): " << res << "\n";
    if (res > gl_ans) {
        gl_ans = res;
        gl_path = path;
    }
}

void rec(long long w, long long h, vector<long long> path) {
    if (min(w, h) - 2 < 1) {
        // cout << "path: " << path << "\n";
        get(path);
        return;
    }
    path.push_back(0);
    for (long long x = 1; min(w, h) - 2 * x >= 1; x++) {
        path[(int) path.size() - 1] = x;
        rec(x, x, path);
    }
}

void solve() {
    gl_ans = 0;
    cin >> gl_W >> gl_H;
    rec(gl_W, gl_H, {});
    cout << gl_path.size() << " " << gl_path << "\n";

}
int main() {
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}