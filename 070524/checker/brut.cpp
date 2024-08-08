#pragma GCC optimize("O3")
#include <iostream>
#include <vector>
using namespace std;

ostream& operator << (ostream& stream, const vector<pair<int, int>>& a) {
    for (auto to : a) {
        stream << "{" << to.first << ", " << to.second << "} ";
    }
    return stream;
}

const int maxn = 5000;
const long long mod = 1e9 + 7;

// dp[sum][last]



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<vector<pair<int, int>>> 
    dp_down(n + 1, vector<pair<int, int>>(n + 1)),
    dp_up(n + 1, vector<pair<int, int>>(n + 1));
    dp_up[k][k] = dp_down[k][k] = {1, 1};
    for (int i = k + 1; i <= n; i++) {
        dp_up[k][i] = dp_down[k][i] = {0, 1};
    }
    if (n == k) {
        cout << 1;
        return 0;
    }
    // cout << "prefs_down: " << prefs_down << "\n";
    // cout << "prefs___up: " << prefs_up << "\n\n";
    for (int sum = k + 1; sum <= n; sum++) {
        for (int w = 1; w <= n; w++) {
            if (sum - w < 0) {
                dp_down[sum][w].second = (dp_down[sum][w - 1].second + dp_down[sum][w].first) % mod;
                dp_up[sum][w].second = (dp_up[sum][w - 1].second + dp_up[sum][w].first) % mod;
                continue;
            }
            dp_down[sum][w].first = (dp_up[sum - w][w - 1].second - dp_up[sum - w][0].second + mod) % mod;
            dp_up[sum][w].first = (dp_down[sum - w][n].second - dp_down[sum - w][w].second + mod) % mod;
            dp_down[sum][w].second = (dp_down[sum][w - 1].second + dp_down[sum][w].first) % mod;
            dp_up[sum][w].second = (dp_up[sum][w - 1].second + dp_up[sum][w].first) % mod;
        }
        // cout << "sum: " << sum << ":\n";
        // cout << "dp_down: " << dp_down[sum] << "\n";
        // cout << "dp___up: " << dp_up[sum] << "\n\n";
    }
    
    cout << (dp_down[n][n].second + dp_up[n][n].second) % mod;
}