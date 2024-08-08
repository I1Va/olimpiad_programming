#include <iostream>
#include <vector>
using namespace std;

vector<vector<long long>> a;
vector<vector<long long>> prefs;

int n, m, l, k;

long long sum(int day, int l, int r) {
    // long long res = 0;
    // for (int i = l; i <= r; i++) {
    //     res += a[day][i];
    // }
    // return res;
    return prefs[day][r + 1] - prefs[day][l];
}

pair<int, int> unite(int l1, int r1, int l2, int r2) {
    if (l2 >= l1 && l2 <= r1) {
        return {l1, r2};
    }
    if (r2 >= l1 && r2 <= r1) {
        return {l2, r1};
    }
    return {-1, -1};
}

int main() {
    
    cin >> n >> m >> l >> k;
    a.resize(m);
    prefs.resize(m);
    for (int i = 0; i < m; i++) {
        a[i].resize(n);
        prefs[i].resize(n + 1);
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
        for (int j = 1; j <= n; j++) {
            prefs[i][j] = prefs[i][j - 1] + a[i][j - 1];
        }
    }
    vector<vector<vector<long long>>> dp(m, vector<vector<long long>>(k + 1, vector<long long>(n, 0)));
    for (int i = 0; i + l - 1 < n; i++) {
        dp[0][0][i] = sum(0, i, i + l - 1);
    }
    for (int i = 0; i + l - 1 < n; i++) {
        for (int j = 0; j + l - 1 < n; j++) {
            auto seg = unite(i, i + l - 1, j, j + l - 1);
            if (seg.first == -1) {
                dp[0][1][j] = sum(0, i, i + l - 1) + sum(0, j, j + l - 1);
            }  else {
                dp[0][1][j] = sum(0, seg.first, seg.second);
            }
        }
    }
    // cout << "done\n";
    for (int day = 1; day < m; day++) {
        // cout << "day: " << day << "\n";
        // cout << a[day].size() << "\n";
        for (int ki = 0; ki <= k; ki++) {
            // cout << "ki: " << ki << "\n";
            for (int pos = 0; pos + l - 1 < n; pos++) { // Не перемещаем излучатель
                // cout << "pos: " << pos << "\n";
                // cout << pos << " " << pos + l - 1 << "\n";
                dp[day][ki][pos] = max(dp[day][ki][pos], dp[day - 1][ki][pos] + sum(day, pos, pos + l - 1));
            }
            // cout << "ki++\n";
            if (ki > 0) {
                for (int prev = 0; prev + l - 1 < n; prev++) {
                    for (int cur = 0; cur + l - 1 < n; cur++) { // Переместим в середине дня day с prev в cur
                        auto seg = unite(prev, prev + l - 1, cur, cur + l - 1);
                        if (seg.first == -1) {
                            dp[day][ki][cur] = max(dp[day][ki][cur], dp[day - 1][ki - 1][prev] + sum(day, prev, prev + l - 1) + sum(day, cur, cur + l - 1));
                        } else {
                            dp[day][ki][cur] = max(dp[day][ki][cur], dp[day - 1][ki - 1][prev] + sum(day, seg.first, seg.second));
                        }
                    }
                }
            }
            
        }
    }
    // cout << "done2\n";
    long long mx = 0;
    for (int ki = 0; ki <= k; ki++) {
        for (int x = 0; x < n; x++) {
            mx = max(mx, dp[m - 1][ki][x]);
        }
    }
    cout << mx;
}
