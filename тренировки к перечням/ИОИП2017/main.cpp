#include <iostream>
#include <vector>
using namespace std;

int n, x, y;
const int maxn = 1e5;

int dp[maxn + 1][4][4][2];

int check_pos(int elem, pair<int, int> neig) {
    int res = 2;
    if (elem & 1) {
        if (!((x == -1 || neig.first == x) && (y == -1 || neig.second == y))) {
        return 0;
    }
    } else {
        if ((x == -1 || neig.first == x) && (y == -1 || neig.second == y)) {
            res = 1;
        }
    }
    return res;
}

int check_base(int prev, int cur) {
    vector<pair<int, int>> neig = 
    {
        {!((prev >> 1) & 1) + !(cur & 1), (prev >> 1) & 1 + (cur & 1)},
        {!(prev & 1) + !((cur >> 1) & 1), (prev & 1) + ((cur >> 1) & 1)}
    };
    int ans = 2;
    for (int i = 0; i < 2; i++) {
        int res = check_pos((prev >> i) & 1, neig[i]);
        if (!res) {
            return 0;
        }
        if (res == 2) {
            ans = 1;
        }
    }
    return ans;
}

int check_trio(int prev, int mask, int cur) {
    vector<pair<int, int>> neig = {
        {!(prev & 1) + !((mask >> 1) & 1) + !(cur & 1), (prev & 1) + ((mask >> 1) & 1) + (cur & 1)},
        {!((prev >> 1) & 1) + !(mask & 1) + !((cur >> 1) & 1), ((prev >> 1) & 1) + (mask & 1) + ((cur >> 1) & 1)}
    };
    int ans = 2;
    for (int i = 0; i < 2; i++) {
        int res = check_pos((mask >> i) & 1, neig[i]);
        if (!res) {
            return 0;
        }
        if (res == 2) {
            ans = 1;
        }
    }
    return ans;
}

bool relax(int& value, const int& new_value) {
    if (value == -1) {
        value = new_value;
        return true;
    }
    if (new_value < value) {
        value = new_value;
        return true;
    }
    return false;
}

int main() {
    freopen("army.in", "r", stdin), freopen("army.out", "w", stdout);
    cin >> n >> x >> y;
    for (int prev = 0; prev < (1 << 2); prev++) {
        for (int cur = 0; cur < (1 << 2); cur++) {
            for (int s = 0; s < 2; s++) {
                dp[1][prev][cur][s] = -1;
            }
        }
    }
    for (int prev = 0; prev < (1 << 2); prev++) {
        for (int cur = 0; cur < (1 << 2); cur++) {
            int res = check_base(prev, cur);
            if (!res) {
                continue;
            }
            dp[2][prev][cur][res - 1] = __builtin_popcount(prev) + __builtin_popcount(cur);
        }
    }

    for (int i = 3; i <= n; i++) {
        for (int prev = 0; prev < (1 << 2); prev++) {
            for (int mask = 0; mask < (1 << 2); mask++) {
                for (int cur = 0; cur < (1 << 2); cur++) {
                    for (int s = 0; s < 2; s++) {
                        int prev_value = dp[i - 1][prev][mask][s];
                        if (prev_value == -1) {
                            continue; // Состояния dp[i - 1][prev][mask][s] не существует
                        }
                        int res = check_trio(prev, mask, cur);
                        if (!res) {
                            continue;
                        }
                        relax(dp[i][mask][cur][s || (res == 2)], dp[i - 1][prev][cur][s] + __builtin_popcount(cur)); 
                    }
                }
            }
        } 
    }
    int mn = 1e9;
    for (int cur = 0; cur < (1 << 2); cur++) {
        for (int prev = 0; prev < (1 << 2); prev++) {
            relax(mn, dp[n][prev][cur][1]);
        }
    }
    cout << mn;
}