#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

const int maxn = 20;
const long long mod = 998244353;

long long dp[1 << maxn];
int n;
vector<vector<int>> g;

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
    dp[0] = 1;
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int cur = 0; cur < n; cur++) {
            if ((mask >> cur) & 1) {
                continue;
            }
            if (check(cur, mask)) {
                dp[(1 << cur) | mask] += dp[mask];
                dp[(1 << cur) | mask] %= mod;
            }
            
        } 
    }
   
    // print();
    cout << dp[(1 << n) - 1];

}