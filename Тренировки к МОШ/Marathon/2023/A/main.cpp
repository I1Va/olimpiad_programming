#include <iostream>
#include <map>
using namespace std;

map<long long, int> ans;
const int inf = 1e9;
const int maxv = 300;
const int iters = 100;

int dp[iters][maxv][maxv];

void build() {
    for (int i = 0; i < iters; i++) {
        for (int cur = 0; cur < maxv; cur++) {
            for (int buf = 0; buf < maxv; buf++) {
                dp[i][cur][buf] = inf;
            }
        }
    }
}
int main() {
    build();
    dp[0][1][0] = 0;
    for (int i = 1; i < iters; i++) {
        for (int cur = 0; cur < maxv; cur++) {
            for (int buf = 0; buf < maxv; buf++) {
                if (cur + buf < maxv) {
                    dp[i][cur + buf][buf] = min(dp[i][cur + buf][buf], dp[i - 1][cur][buf] + 1);
                }
                dp[i][cur][cur] = min(dp[i][cur][cur], dp[i - 1][cur][buf] + 1);
            }
        }
    }
    for (int i = 0; i < iters; i++) {
        for (int cur = 0; cur < maxv; cur++) {
            for (int buf = 0; buf < maxv; buf++) {
                if (ans.find(cur) == ans.end()) {
                    ans[cur] = inf;
                }
                ans[cur] = min(ans[cur], dp[i][cur][buf]);
            }
        }
    }
    long long x;
    cin >> x;
    cout << ans[x];
    
    
    
}