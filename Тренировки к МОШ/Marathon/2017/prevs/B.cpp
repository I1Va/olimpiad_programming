#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int Q;
    cin >> Q;
    while (Q--) {
        long long k, n;
        cin >> k >> n;
        // cout << k << " " << n << ":  ";
        vector<pair<long long, long long>> CF(3);
        for (int i = 0; i < 3; i++) {
            cin >> CF[i].first >> CF[i].second;
        }
        vector<pair<long long, int>> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i].first;
            a[i].second = i;
        }
        sort(a.begin(), a.end());
        vector<long long> prefs(n + 1);
        for (int i = 1; i <= n; i++) {
            prefs[i] = prefs[i - 1] + a[i - 1].first;
        }
        long long ans = 1e18;
        int c1_ans = 0, c2_ans = 0, c3_ans = 0;
        for (int c1 = 0; c1 <= k / CF[0].second + 1; c1++) {
            if (c1 > n) {
                continue;
            }
            for (int c2 = 0; c2 <= k / CF[1].second + 1; c2++) {
                int c3 = max(0ll, (k - c1 * CF[0].second - c2 * CF[1].second + CF[2].second - 1) / CF[2].second);
                if (c1 + c2 + c3 > n) {
                    continue;
                }
                // cout << c1 << ", " << c2 << ", " << c3 << "\n";
                long long cost = 0;
                cost = prefs[c1 + c2 + c3] + c1 * CF[0].first + c2 * CF[1].first + c3 * CF[2].first;
                ans = min(ans, cost);
                if (cost == ans) {
                    c1_ans = c1, c2_ans = c2, c3_ans = c3;
                }
            }
        }
        // cout << "done: " << c1_ans << " " << c2_ans << " " << c3_ans << "\n";
        vector<int> res(n);
        int pos = 0;
        while (c1_ans--) {
            res[a[pos].second] = 1;
            pos++;
        }
        while (c2_ans--) {
            res[a[pos].second] = 2;
            pos++;
        }
        while (c3_ans--) {
            res[a[pos].second] = 3;
            pos++;
        }
        for (auto x : res) {
            cout << x << " ";
        }
        cout << "\n";
        

    }
}