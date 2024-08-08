#include <iostream>
#include <vector>
using namespace std;

int n;
vector<long long> a, b, c, d;
const long long INF = 1e18;

bool check1() {
    for (auto x : a) {
        if (x == 0) {
            return false;
        }
    }
    return true;
}

long long get(int i) {
    if (a[i] > 0) {
        return (abs(-1 - a[i]) + b[i] - 1) / b[i] * d[i];
    } else {
        return (abs(1 - a[i]) + b[i] - 1) / b[i] * c[i];
    }
}

void solve1() {
    int v = 0;
    for (auto x : a) {
        if (x < 0) {
            v++;
        }
    }
    if (v % 2 == 0) {
        cout << 0;
        return;
    }
    long long mn = 1e18;
    for (int i = 0; i < n; i++) {
        mn = min(mn, get(i));
    }
    cout << mn;
}

void solve2() {
    int v = 0;
    for (auto x : a) {
        if (x < 0) {
            v++;
        }
    }
    vector<vector<long long>> dp(n, vector<long long>(2, INF));
    if (a[0] > 0) {
        dp[0][0] = 0;
        dp[0][1] = get(0);
    } else if (a[0] < 0) {
        dp[0][1] = 0;
        dp[0][0] = get(0);
    }  else {
        dp[0][0] = c[0];
        dp[0][1] = d[0];
    }
    for (int i = 1; i < n; i++) {
        if (a[i] < 0) {
            dp[i][0] = min(dp[i][0], dp[i - 1][0] + get(i));
            dp[i][0] = min(dp[i][0], dp[i - 1][1]);
            dp[i][1] = min(dp[i][1], dp[i - 1][1] + get(i));
            dp[i][1] = min(dp[i][1], dp[i - 1][0]);
        } else if (a[i] == 0) {
            dp[i][0] = min(dp[i][0], dp[i - 1][0] + c[i]);
            dp[i][0] = min(dp[i][0], dp[i - 1][1] + d[i]);
            dp[i][1] = min(dp[i][1], dp[i - 1][1] + c[i]);
            dp[i][1] = min(dp[i][1], dp[i - 1][0] + d[i]);
        } else {
            dp[i][0] = min(dp[i][0], dp[i - 1][0]);
            dp[i][0] = min(dp[i][0], dp[i - 1][1] + get(i));
            dp[i][1] = min(dp[i][1], dp[i - 1][1]);
            dp[i][1] = min(dp[i][1], dp[i - 1][0] + get(i));
        }
    }
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < 2; j++) {
    //         cout << "dp[" << i << "][" << j << "] = " << dp[i][j] << "\n";
    //     }
    // }
    cout << dp[n - 1][0];
}

int main() {
    cin >> n;
    a.resize(n), b.resize(n), c.resize(n), d.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }
    solve2();
}