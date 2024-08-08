#include <iostream>
#include <vector>
using namespace std;

const int maxn = 100;
const int maxv = 10;
const int delta = maxv;

long long dp[maxn][maxn][maxv + delta + 1];

const long long INF = 1e18;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int v = -maxv; v < maxv; v++) {
                dp[i][k][v + delta] = INF;
            }
        }
    }
    for (int cur = a[0]; cur < maxv; cur++) {
        dp[0][0][cur + delta] = abs(cur - a[0]);
    }
    for (int i = 1; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int cur = a[i]; cur < maxv; cur++) {
                for (int prev = a[i - 1]; prev < maxv; prev++) {
                    if (cur + prev > 0 && k - 1 >= 0) {
                        dp[i][k][cur + delta] = min(dp[i][k][cur + delta], dp[i - 1][k - 1][prev + delta] + abs(cur - a[i]));
                    }
                    dp[i][k][cur + delta] = min(dp[i][k][cur + delta], dp[i - 1][k][prev + delta] + abs(cur - a[i]));
                    
                }
            }
        }
    }
    // for (int i = 0; i < n; i++) {
    //     for (int k = 0; k < n; k++) {
    //         for (int v = -maxv; v < maxv; v++) {
    //             cout << "dp[" << i << "][" << k << "][" << v << "]: " << dp[i][k][v] << "\n";
    //         }
    //     }
    // }
    for (int k = n - 1; k >= 0; k--) {
        long long mn = INF;
        for (int cur = -maxv; cur < maxv; cur++) {
            mn = min(mn, dp[n - 1][k][cur + delta]);
        }
        cout << mn << " ";
    }


}