#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

const long long INF = 1e9;
vector<long long> dd;
long long n, m;
vector<vector<char>> a;
vector<long long> dx = {-1, 1, 0, 0}, dy = {0, 0, -1, 1};

void bfs(long long x, long long y) {
    vector<vector<long long>> dp(n, vector<long long>(m, INF));
    queue<pair<long long, long long>> q;
    dp[x][y] = 0;
    q.emplace(x, y);
    while (!q.empty()) {
        auto [xx, yy] = q.front();
        q.pop();
        for (long long i = 0; i < 4; i++) {
            long long nx = xx + dx[i], ny = yy + dy[i];
            if (0 <= nx && nx < n && 0 <= ny && ny < m && dp[nx][ny] == INF && a[nx][ny] != 'B') {
                dp[nx][ny] = dp[xx][yy] + 1;
                if (a[nx][ny] == 'I') {dd.push_back(dp[nx][ny]);continue;}
                q.emplace(nx, ny);
            }
        }
    }
}

inline void solve() {
    cin >> n >> m;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        a[i].resize(m);
    }
    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < m; j++) {
            cin >> a[i][j];
            if (a[i][j] == 'X'){bfs(i, j);}
        }
    }
    set<long long> hh;
    for (auto& i : dd) {hh.insert(i % 2);}
    if (hh.size() != 1) {cout << "-1\n";return;}
    long long mx = 0;
    for (auto x : dd) {
        mx = max(mx, x);
    }
    cout << mx * dd.size();
}

int main() {
    solve();
}