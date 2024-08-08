#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

const int INF = 1e9;
vector<int> dd;
int n, m;
vector<string> a;
vector<int> dx = {-1, 1, 0, 0}, dy = {0, 0, -1, 1};

void bfs(int x, int y) {
    vector<vector<int>> dp(n, vector<int>(m, INF));
    queue<pair<int, int>> q;
    dp[x][y] = 0;
    vector<vector<bool>> used(n, vector<bool>(m, false));
    used[x][y] = true;
    q.emplace(x, y);
    while (!q.empty()) {
        auto [xx, yy] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = xx + dx[i], ny = yy + dy[i];
            if (0 <= nx && nx < n && 0 <= ny && ny < m && !used[nx][ny] && a[nx][ny] != 'B') {
                used[nx][ny] = true;
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
    for (auto& i : a) {
        cin >> i;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 'X'){bfs(i, j);}
        }
    }
    set<int> hh;
    for (auto& i : dd) {hh.insert(i % 2);}
    if (hh.size() != 1) {cout << "-1\n";return;}
    int mx = 0;
    for (auto x : dd) {
        mx = max(mx, x);
    }
    cout << mx * dd.size();
}

int main() {
    solve();
}