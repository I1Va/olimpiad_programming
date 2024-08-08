#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

int n, k, q;
long long x;
vector<vector<long long>> a;
vector<pair<int, int>> quests;

const long long INF = 1e18;

long long get(int bi, int bj) {
    vector<vector<long long>> dp(n, vector<long long>(k, INF));
    for (int i = 0; i < k; i++) {
        dp[0][i] = a[0][i];
    }
    for (int i = 1; i < n; i++) {
        for (int cur = 0; cur < k; cur++) {
            
            for (int prev = 0; prev < k; prev++) {
                if (i - 1 == bi && prev == bj) {
                    continue;
                }
                dp[i][cur] = min(dp[i][cur], dp[i - 1][prev] + a[i][cur] + abs(prev - cur) * x);
            }
        }
    }
    long long mn = INF;
    for (int i = 0; i < k; i++) {
        mn = min(mn, dp[n - 1][i]);
    }
    return mn;
}

void solve() {
    cout << get(-1, -1) << "\n";
    for (auto x : quests) {
        cout << get(x.first - 1, x.second - 1) << "\n";
    }
}

int main() {
    cin >> n >> k >> x;
    a.resize(n);
    for (auto& x : a) {
        x.resize(k);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cin >> a[i][j];
        }
    }
    cin >> q;
    quests.resize(q);
    for (int i = 0; i < q; i++) {
        cin >> quests[i].first >> quests[i].second;
    }
    solve();
    
}