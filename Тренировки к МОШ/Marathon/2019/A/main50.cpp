#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

const long long INF = 1e18;

bool check(int i, int prev, int cur, const vector<vector<bool>>& field) {
    for (int j = prev; j <= cur; j++) {
        if (field[i][j]) {
            return false;
        }
    }
    return true;
}

void print(const vector<vector<bool>>& a) {
    for (auto to : a) {
        for (auto w : to) {
            cout << w << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void print_dp(const vector<vector<long long>>& a) {
    for (auto to : a) {
        for (auto w : to) {
            if (w == INF) {
                cout << "_ ";
            } else {
                cout << w << " ";
            }
            
        }
        cout << "\n";
    }
    cout << "\n";
}


void solve() {
    int n, k;
    cin >> n >> k;
    vector<pair<long long, long long>> a(k);
    vector<vector<bool>> field(4, vector<bool>(n, false));
    
    for (int i = 0; i < k; i++) {
        cin >> a[i].first >> a[i].second;
        field[a[i].second - 1][a[i].first - 1] = true;
    }
    vector<vector<long long>> dp(4, vector<long long>(n, INF));
    vector<vector<pair<int, int>>> p(4, vector<pair<int, int>>(n));
    dp[0][0] = 0;
    p[0][0] = {-1, -1};
    for (int i = 1; i < 4; i++) {
        if (!field[i][0]) {
            dp[i][0] = dp[i - 1][0] + 1;
            p[i][0] = {i - 1, 0};
        }
    }
    for (int j = 1; j < n; j++) {
        //cout << j << ":done\n";
        for (int i = 0; i < 4; i++) {
            for (int prev = j - 1; prev >= 0; prev--) {
                if (check(i, prev, j, field)) { // Полоска i чиста
                    if (dp[i][prev] + 1 < dp[i][j]) {
                        dp[i][j] = dp[i][prev] + 1;
                        p[i][j] = {i, prev};
                    }
                } else {
                    break;
                }
            }
        }
        for (int i = 1; i < 4; i++) {
            if (!field[i][j] && dp[i - 1][j] + 1 < dp[i][j]) {
                dp[i][j] = dp[i - 1][j] + 1;
                p[i][j] = {i - 1, j};
            }
        }
        for (int i = 2; i >= 0; i--) {
            if (!field[i][j] && dp[i + 1][j] + 1 < dp[i][j]) {
                dp[i][j] = dp[i + 1][j] + 1;
                p[i][j] = {i + 1, j};
            }
        }
    }
    int idx = -1;
    long long mn = INF;
    for (int i = 0; i < 4; i++) {
        if (dp[i][n - 1] < mn) {
            mn = dp[i][n - 1];
            idx = i;
        }
    }
    // print(field);
    // print_dp(dp);
    vector<string> ans;
    pair<int, int> cur = {idx, n - 1};
    while (1) {
        pair<int, int> prev = p[cur.first][cur.second];
        // cout << cur.first << " " << cur.second << "\n";
        if (prev.first == -1) {
            break;
        }
        if (prev.first > cur.first) {
            ans.push_back("U");
        } else if (prev.first < cur.first) {
            ans.push_back("D");
        } else {
            ans.push_back("R " + to_string(cur.second - prev.second));
        }
        cur = prev;
    }
    reverse(ans.begin(), ans.end());
    cout << mn << "\n";
    for (auto w : ans) {
        cout << w << "\n";
    }
    cout << "\n";
    

}
int main() {
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}