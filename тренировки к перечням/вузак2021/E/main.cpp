#include <iostream>
#include <vector>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

vector<vector<int>> g;
vector<pair<int, int>> a;
const int maxa = 101;
vector<vector<int>> dp;

void merge(vector<int>& f, const vector<int>& s) {
    for (int i = 1; i < maxa; i++) {
        f[i] = max(f[i], s[i]);
    }
}

void dfs(int v, int p) {
    dp[v].resize(maxa, 0);
    bool leaf = true;
    for (int u : g[v]) {
        if (u != p) {
            dfs(u, v);
            leaf = false;
            merge(dp[v], dp[u]);
        }
    }
    for (int i = 1; i <= a[v].first; i++) {
        dp[v][i] = max(dp[v][i], a[v].second);
    }
}

int main() {
    int n;
    cin >> n;
    g.resize(n);
    dp.resize(n);
    a.resize(n);
    for (int i = 0; i < n; i++) {
        int p, f, s;
        cin >> p >> f >> s;
        a[i] = {f, s};
        if (p == 0) {
            continue;
        }
        g[i].push_back(p - 1);
        g[p - 1].push_back(i);
    }
    dfs(0, -1);
    // cout << "done\n";
    for (int i = 0; i < n; i++) {
        // cout << i << ": " << dp[i] << "\n";
        long long ans = 0;
        for (int j = 0; j < maxa; j++) {
            if (dp[i][j]) {
                ans += dp[i][j];
            }
        }
        cout << ans << "\n";
    }
}
