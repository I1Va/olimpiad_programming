#include <iostream>
#include <vector>
#include <string>
using namespace std;

const long long maxk = 6;

int main() {
    long long n;
    cin >> n;
    vector<string> a(n);
    for (long long i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long res = 0;
    vector<vector<long long>> cnt(maxk, vector<long long>(10, 0));
    for (long long i = 0; i < n; i++) {
        for (long long k = 0; k < maxk; k++) {
            cnt[k][a[i][k] - '0']++;
            for (long long j = a[i][k] - '0' + 1; j < 10; j++) {
                res += cnt[k][j];
            }
        }
    }
    // for (long long k = 0; k < maxk; k++) {
    //     for (long long i = 0; i < 10; i++) {
    //         cout << "cnt[" << k << "][" << i << "]: " << cnt[k][i] << "\n";
    //     }
    // }
    // cout << "res: " << res << "\n";
    long long ans = res;
    for (long long c = 0; c < n; c++) {
        for (long long k = 0; k < maxk; k++) {
            long long c1 = 0;
            long long c2 = 0;
            for (long long i = 0; i < a[c][k] - '0'; i++) {
                c1 += cnt[k][i];
            }
            for (long long i = a[c][k] - '0' + 1; i < 10; i++) {
                c2 += cnt[k][i];
            }
            res = res + c2 - c1;
            // cout << c << ", " << a[c][maxk - 1] << ", " << c1 << ", " << c2 << " res: " << res << "\n";
        }
        ans = min(ans, res);
    }
    cout << ans;
}