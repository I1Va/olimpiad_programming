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
    int cur, prev;
    node(): cur{-1}, prev{-1} {};
    node(int cur, int prev): cur{cur}, prev{prev} {};
};

ostream& operator<< (ostream& stream, const node& a) {
    stream << "{" << a.cur << ", " << a.prev << "}";
    return stream;
}


void solve() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> dp(n, vector<int>(n, 0));
    sort(a.begin(), a.end());
    // cout << "a = " << a << "\n";
    for (int i = 0; i < n; i++) {
        for (int prev = 0; prev < i; prev++) {
            dp[i][prev] = 2;
        }
    }
    vector<vector<int>> pref_max(n, vector<int>(n, 0));
    for (int i = 0; i < 2; i++) {
        pref_max[i][0] = dp[i][0];
        for (int j = 1; j < n; j++) {
            pref_max[i][j] = max(pref_max[i][j - 1], dp[i][j]);
        }
    }
    for (int k = 2; k < n; k++) {
        for (int i = 0; i < k; i++) {
            long long d = a[k] - a[i];
            int r = min(i, (int) (lower_bound(a.begin(), a.end(), a[i] - d) - a.begin())) - 1;
            if (r == -1) {
                continue;
            }
            // for (int j = 0; j <= r; j++) {
            //     // j i k
            //     dp[k][i] = max(dp[k][i], dp[i][j] + 1);
            // }
            dp[k][i] = max(dp[k][i], pref_max[i][r] + 1);
        }
        pref_max[k][0] = dp[k][0];
        for (int j = 1; j < n; j++) {
            pref_max[k][j] = max(pref_max[k][j - 1], dp[k][j]);
        }
        
    }
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < i; j++) {
    //         cout << "dp[" << i << "][" << j << "] = " << dp[i][j] << "\n";
    //     }
    // }
    int mx = 1;
    for (int cur = 0; cur < n; cur++) {
        for (int prev = 0; prev < cur; prev++) {
            mx = max(mx, dp[cur][prev]);
        }
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