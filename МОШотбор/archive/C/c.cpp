#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
using namespace std;

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);

ostream& operator<< (ostream& stream, const pair<long long, long long>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream;
}

ostream& operator<< (ostream& stream, const vector<pair<long long, long long>>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}



int main() {
    int q;
    cin >> q;
    while (q--) {
        int n;
        cin >> n;
        vector<pair<long long, long long>> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i].first;
        }
        for (int i = 0; i < n; i++) {
            cin >> a[i].second;
        }
        // shuffle(a.begin(), a.end(), rnd);
        cout << a << "\n";
        const int delta = 100;
        const int sz = delta * 3;
        vector<vector<long long>> dp(n + 1, vector<long long>(sz, -1));
        dp[0][delta + 0] = 0;
        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int k = 0; k < delta; k++) {
                if (dp[i - 1][delta + k] != -1) {
                    dp[i][delta + k + (a[i - 1].first - a[i - 1].second)] = max(dp[i][delta + k + (a[i - 1].first - a[i - 1].second)], dp[i - 1][delta + k] + a[i - 1].first + a[i - 1].second);
                }
                if (dp[i - 1][delta + k] != -1) {
                    dp[i][delta + k] = max(dp[i][delta + k], dp[i - 1][delta + k]);
                }
            }
            // ans = max(ans, dp[i][delta + 0]);
        }
        for (int i = 0; i <= n; i++) {
            for (int k = 0; k <= delta; k++) {
                cout << "dp[" << i << "][" << k << "] = " << dp[i][k] << "\n";
            }
        }
        cout << dp[n][delta + 0] << "\n";
    }
    
}