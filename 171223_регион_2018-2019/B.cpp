#pragma GCC optimize("O3")
#include <iostream>
#include <unordered_map>
#include <cmath>
using namespace std;

const long long INF = 1e18;

void solve2(long long k) {
    long long mn = INF;
    if (k == 0) {
        cout << 0;
        return;
    }
    for (long long d = 1; d <= (long long) sqrt(k) + 1; d++) {
        // cout << d << "\n";
        long long cur = d * d + k;
        if (cur % (2 * d) == 0) {
            mn = min(mn, cur / (2 * d));
        }
    }
    if ((k * k + k) % (2 * k) == 0) {
        mn = min(mn, (k * k + k) / (2 * k));
    }
    if (mn == INF) {
        cout << "none";
        return;
    }
    cout << mn;
}

void solve2_2(long long k) {
    k *= -1;
    long long mn = INF;
    for (long long d = 1; d <= (long long) sqrt(k) + 1; d++) {
        // cout << d << "\n";
        long long cur = k - d * d;
        if (cur % (2 * d) == 0) {
            mn = min(mn, abs(cur / (2 * d)));
        }
    }
    if ((k - k * k) % (2 * k) == 0) {
        mn = min(mn, abs((k - k * k) / (2 * k)));
    }
    if (mn == INF) {
        cout << "none";
        return;
    }
    cout << mn;
}

int main() {
    long long k;
    cin >> k;
    if (k >= 0) {
        solve2(k);
    } else {
        solve2_2(k);
    }
}