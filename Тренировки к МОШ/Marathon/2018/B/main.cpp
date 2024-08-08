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
    long long diag = ceil(sqrt(H * H + W * W) / 2.0);
    long double v = 0;
    long double ans = f(v);
    for (int i = 0; i < 1e4; i++) {
        long double temp = diag * ch();
        long double res = f(temp);
        if (res < ans) {
            ans = res;
            v = temp;
        }
    }
    // cout << "start: " << v << " " << ans << "\n";
    long double t = 1;
    for (int i = 0; i <= iters; i++) {
        t *= 0.99;
        long double u = v + (long double) randrange(-delta.first, delta.first) / (long double) delta.second;
        long double val = f(u);
        if (val < ans || rnd() < exp((ans - val) / t)) {
            v = u;
            ans = val;
        }
        // cout << "f(" << v << "): " << ans << "\n";
    }
    cout << v << "\n";
    //cout << v << " " << ans << " " << f(v) << "\n";
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}