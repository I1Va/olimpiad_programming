#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool check(int cur, int next, char op) {
    if (op == '=') {
        return cur == next;
    }
    if (op == '<') {
        return cur < next;
    }
    if (op == '>') {
        return cur > next;
    }
    return true;
}

const long long mod = 1e9 + 7;

int main() {
    int n, x;
    cin >> n >> x;
    string s;
    cin >> s;
    vector<vector<long long>> dp(n, vector<long long>(x + 1));
    for (int i = 1; i <= x; i++) {
        dp[n - 1][i] = 1;
    }
    for (int i = n - 2; i >= 0; i--) {
        for (int cur = 1; cur <= x; cur++) {
            for (int next = 1; next <= x; next++) {
                if (!check(cur, next, s[i])) {
                    continue;
                }
                dp[i][cur] += dp[i + 1][next];
                dp[i][cur] %= mod; 
            }
        }
    }
    long long sum = 0;
    for (int i = 1; i <= x; i++) {
        sum += dp[0][i];
        sum %= mod;
    }
    cout << sum;
}