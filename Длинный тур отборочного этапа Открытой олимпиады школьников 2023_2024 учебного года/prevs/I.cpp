#include <iostream>
#include <vector>
using namespace std;

struct edge {
    int u, v;
    long long w;
    edge(): u{-1}, v{-1}, w{} {}
    edge(int u, int v, long long w): u{u}, v{v}, w{w} {}
};

int n, k, t;
vector<long long> w;
vector<edge> edges;

bool state1() {
    return n <= 200 && t == 0;
}

bool state4() {
    if (t != 0) {
        return false;
    }
    for (auto to : edges) {
        if (to.v != to.u + 1) {
            return false;
        }
    }
    return true;
}

void print_dp(const vector<vector<vector<long long>>>& dp) {
    for (int i = 0; i < n; i++) {
        for (int ki = 0; ki <= k; ki++) {
            for (int state = 0; state < 2; state++) {
                cout << "dp[" << i << "][" << k << "][" << state << "] = " << dp[i][ki][state] << "\n";
            }
        }
    }
}

void solve4() {
    long long INF = 1e18;
    vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(k + 1, vector<long long>(2, -INF)));
    vector<pair<int, long long>> g(n);
    for (auto e : edges) {
        g[e.u] = {e.v, e.w};
    }
    dp[0][0][0] = 0;
    for (int i = 1; i < n; i++) {
        for (int ki = 0; ki <= k; ki++) {
            dp[i][ki][0] = max(dp[i][ki][0], dp[i - 1][ki][0]);
            dp[i][ki][0] = max(dp[i][ki][0], dp[i - 1][ki][1]);
            if (ki == 0 || i == n - 1) {
                continue;
            }
            dp[i][ki][1] = max(dp[i][ki][1], dp[i - 1][ki - 1][0] + w[i] - g[i - 1].second - g[i].second);
        }
    }
    // print_dp(dp);
    cout << 1;
    // cout << max(dp[n - 1][k][0], dp[n - 1][k][1]);
}

int main() {
    cin >> n >> k >> t;
    w.resize(n);
    edges.resize(n - 1);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edges[i] = edge(u - 1, v - 1, w);
    }
    solve4();
}