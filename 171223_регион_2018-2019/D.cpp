#include <iostream>
#include <vector>
using namespace std;

int n, m;
long long k;
const long long mod = 1e9 + 7;

void solve1() {
    vector<vector<long long>> dp(n, vector<long long>(k + 1));
    for (int i = 0; i <= k; i++) {
        dp[0][i] = 1;
    }
    for (int i = 1; i < n; i++) {
        for (int w = 0; w <= k; w++) {
            for (int prev = 0; prev <= k; prev++) {
                if ((prev & w) == prev) {
                    dp[i][w] = (dp[i][w] + dp[i - 1][prev]) % mod;
                }
            }
        }
    }
    // for (int i = 0; i < n; i++) {
    //     for (int w = 0; w <= k; w++) {
    //         cout << "dp[" << i << "][" << w << "] = " << dp[i][w] << "\n";
    //     }
    // } 
    long long ans = 0;
    for (int i = 0; i <= k; i++) {
        ans = (ans + dp[n - 1][i]) % mod;
    }
    cout << ans;
}

int main() {
    cin >> n >> m >> k;
    solve1();

}