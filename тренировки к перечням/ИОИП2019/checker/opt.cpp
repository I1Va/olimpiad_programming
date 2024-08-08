#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

const int maxn = 20;
const long long mod = 1e9 + 7;

long long dp[maxn + 1][1 << maxn];
int n;
vector<vector<int>> g;
void print() {
    for (int i = 1; i <= n; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (dp[i][mask]) {
                cout << "dp[" << i << "][" << bitset<4>(mask) << "] = " << dp[i][mask] << "\n";
            }
        }
    }
}

bool check(int ver, int mask) {
    for (int u : g[ver]) {
        if ((mask >> u) & 1) {
            return false;
        }
    }
    return true;
}

int main() {
    
    cin >> n;
    g.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
    }
    for (int mask = 0; mask < (1 << n); mask++) {
        if (__builtin_popcount(mask) == 1) {
            dp[1][mask] = 1;
        }
    }
    
    for (int i = 2; i <= n; i++) {
        for (int cur = 0; cur < n; cur++) {
            for (int mask = 0; mask < (1 << n); mask++) {
                if ((mask >> cur) & 1) {
                    continue;
                }
                if (check(cur, mask)) {
                    dp[i][(1 << cur) | mask] += dp[i - 1][mask];
                    dp[i][(1 << cur) | mask] %= mod;
                }
                
            }
        }
    }
    // print();
    cout << dp[n][(1 << n) - 1];

}