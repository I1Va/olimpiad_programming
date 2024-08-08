#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


ostream& operator<< (ostream& stream, const vector<long long>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

struct node {
    int cur, prev, start;
    node(): cur{-1}, prev{-1}, start{-1} {};
    node(int cur, int prev, int start): cur{cur}, prev{prev}, start{start} {};
};

ostream& operator<< (ostream& stream, const node& a) {
    stream << "{" << a.cur << ", " << a.prev << ", " << a.start << "}";
    return stream;
}

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, 0)));
    vector<vector<vector<node>>> p(n, vector<vector<node>>(n, vector<node>(2)));
    sort(a.begin(), a.end());
    cout << "a = " << a << "\n";
    for (int i = 0; i < n; i++) {
        for (int prev = 0; prev < i; prev++) {
            dp[i][prev][1] = 2;
        }
    }
    oef
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < i; j++) {
                // j i k
                dp[k][i][0] = max(dp[k][i][0], dp[i][j][1] + 1); // Релаксируем из первого прыжка
                if (dp[i][j][1] + 1 == dp[k][i][0]) {
                    p[k][i][0] = node(i, j, 1);
                }
                if (a[i] - a[j] > a[k] - a[i]) {
                    dp[k][i][0] = max(dp[k][i][0], dp[i][j][0] + 1); // Релаксируем НЕ из первого прыжка
                    if (dp[i][j][0] + 1 == dp[k][i][0]) {
                        p[k][i][0] = node(i, j, 0);
                    }
                }
            }
        }
        
    }
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < i; j++) {
    //         cout << "dp[" << i << "][" << j << "] = " << dp[i][j] << "\n";
    //     }
    // }
    int mx = 0;
    node start;
    for (int cur = 0; cur < n; cur++) {
        for (int prev = 0; prev < cur; prev++) {
            mx = max(mx, dp[cur][prev][0]);
            mx = max(mx, dp[cur][prev][1]);
            if (dp[cur][prev][1] = mx) {
                start = node(cur, prev, 1);
            }
            if (dp[cur][prev][0] = mx) {
                start = node(cur, prev, 0);
            }
        }
    }
    while (start.cur != -1) {
        cout << start << " ";
        start = p[start.cur][start.prev][start.start];
    }
    cout << mx << "\n";
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}