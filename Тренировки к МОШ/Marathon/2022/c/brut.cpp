#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m, k, t;
    cin >> n >> m >> k >> t;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<pair<int, int>> segs(m);
    for (int i = 0; i < m; i++) {
        cin >> segs[i].first >> segs[i].second;
        segs[i].first--, segs[i].second--;
    }
    for (int ti = 1; ti <= t; ti++) {
        vector<vector<long long>> f(k + 1, vector<long long>(k + 1));
        for (int i = 1; i <= k; i++) {
            for (int j = 1; j <= k; j++) {
                cin >> f[i][j];
            }
        }
        if (ti <= 35) {
            cout << -1 << "\n";
        }
        long long ans = 0;
        for (auto x : segs) {
            if (x.second - x.first + 1 == 1) {
                ans += a[x.first];
                continue;
            }
            long long cur = a[x.first];
            for (int i = x.first + 1; i <= x.second; i++) {
                cur = f[cur][a[i]];
            }
            ans += cur;
        }
        cout << ans << "\n";
    }
}