#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>
#include <chrono>
using namespace std;

long double H, W;
const long double EPS = 1.0 / 1e7;
const long double PI = 3.14159265359;
const int iters = 1e7;
const pair<long long, long long> delta = {1, 1e7};
auto now = chrono::high_resolution_clock().now().time_since_epoch().count();
mt19937_64 rnd(now);

long double ch() {
    return ((long double) rnd()) / rnd.max();
}

long long randrange(long long a, long long b) {
    return a + rnd() % (b - a);
}

long double sector(long double R, long double h) {
    long double cosb = h / R;
    long double b = acos(cosb);
    long double AB = sqrt(R * R - h * h) * 2;
    return R * R * b;
}

long double triang(long double R, long double h) {
    long double cosb = h / R;
    long double b = acos(cosb);
    long double AB = sqrt(R * R - h * h) * 2;
    // cout << "AB: " << AB << "\n";
    return AB * h / 2.0;
}

long double f(long double R) {
    long double halfdi = sqrt(H * H + W * W) / 2.0; 
    if (R <= H / 2.0) {
        return H * W - PI * R * R;
    }
    if (R <= W / 2.0) {
        // cout << "var2: ";
        long double s = sector(R, H / 2.0);
        long double t = triang(R, H / 2.0);
        // cout << "t: " << t << "\n";
        long double good = PI * R * R - 2 * s + 2 * t;
        return W * H - good + 2 * (s - t);
    }
    if (R < halfdi) {
        long double s1 = sector(R, H / 2.0);
        long double t1 = triang(R, H / 2.0);
        long double s2 = sector(R, W / 2.0);
        long double t2 = triang(R, W / 2.0);
        long double good = 2 * t1 + 2 * t2 + PI * R * R - 2 * (s1 + s2);
        // cout << "var3: ";
        return W * H - good + 2 * (s1 - t1 + s2 - t2);
    }
    if (R >= halfdi) {
        // cout << "var4: ";
        return 2 * PI * R * R - H * W;
    }
    cout << "ERROR, R: " << R << "\n";
    exit(1);
}

void solve() {
    cout << fixed << setprecision(8);
    cin >> H >> W;
    if (H > W) {
        swap(H, W);
    }
    long double diag = sqrt(H * H + W * W);
    cout << "diag: " << diag << "\n";
    vector<pair<long double, long double>> bords = {
        {0, H / 2.0}, {H / 2.0, W / 2.0}, {W / 2.0, diag / 2.0}, {diag / 2.0, diag}};
    pair<long double, long double> ans = {1e9, 0};
    for (auto bord : bords) {
        long double l = bord.first;
        long double r = bord.second;
        while (r - l > EPS) {
            long double m1 = l + (r - l) / 3;
            long double m2 = r - (r - l) / 3;
            if (f(m1) < f(m2)) {
                l = m1;
            } else {
                r = m2;
            }
        }
        long double p = (l + r) / 2.0;
        if (f(p) < ans.first) {
            ans = {f(p), p};
        }
    }
    cout << ans.first << " " << ans.second << "\n";
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}