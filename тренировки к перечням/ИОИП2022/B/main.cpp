#include <iostream>
#include <vector>
using namespace std;

const long long mod = 998244353;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<long long>> dp(n, vector<long long>(2, 0));
    dp[0][0] = 1;
    dp[0][1] = 1;
    vector<int> s = {1, -1};
    for (int i = 1; i < n; i++) {
        for (int cur = 0; cur < 2; cur++) {
            for (int prev = 0; prev < 2; prev++) {
                if (a[i] * s[cur] < a[i - 1] * s[prev]) {
                    continue;
                }
                dp[i][cur] += dp[i - 1][prev];
                dp[i][cur] %= mod;
            }
        }
    }
    cout << (dp[n - 1][0] + dp[n - 1][1]) % mod;
}