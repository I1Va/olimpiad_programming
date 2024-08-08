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
    vector<vector<node>> p(n, vector<node>(n));
    sort(a.begin(), a.end());
    cout << "a = " << a << "\n";
    for (int i = 0; i < n; i++) {
        for (int prev = 0; prev < i; prev++) {
            dp[i][prev] = 2;
        }
    }
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < i; j++) {
                // j i k
                if (a[i] - a[j] > a[k] - a[i]) {
                    dp[k][i] = max(dp[k][i], dp[i][j] + 1);
                    if (dp[i][j] + 1 == dp[k][i]) {
                        p[k][i] = node(i, j);
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
            mx = max(mx, dp[cur][prev]);
            if (dp[cur][prev] = mx) {
                start = node(cur, prev);
            }
        }
    }
    while (start.cur != -1) {
        cout << start << " ";
        start = p[start.cur][start.prev];
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