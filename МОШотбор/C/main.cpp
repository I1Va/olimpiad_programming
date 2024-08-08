#include <iostream>
#include <bitset>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;

auto now = chrono::high_resolution_clock().now().time_since_epoch().count();
mt19937 rnd(now);

const int maxn = 100;
const int maxv = 2 * 1e7;
const long long delta = maxv / 3;


void solve() {
    int n;
    cin >> n;
    vector<pair<long long, long long>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i].second;
    }
    vector<long long> cur(maxv), prev(maxv);
    vector<bitset<maxv>> path(maxn + 1);
    prev[delta + 0] = 1;
    for (int i = 1; i <= n; i++) {
        for (long long w = -delta; w < delta; w++) {
            if (prev[delta + w] != 0 && prev[delta + w] + a[i - 1].first + a[i - 1].second > cur[delta + w + a[i - 1].first - a[i - 1].second]) {
                cur[delta + w + a[i - 1].first - a[i - 1].second] = prev[delta + w] + a[i - 1].first + a[i - 1].second;
                path[i - 1][delta + w] = 1;
                // cout << w + a[i - 1].first - a[i - 1].second << ": " << prev[delta + w] + a[i - 1].first + a[i - 1].second << "\n";
            }
            if (prev[delta + w] != 0 && prev[delta + w] > cur[delta + w]) {
                cur[delta + w] = prev[delta + w];
                path[i - 1][delta + w] = 1;
            }
        }
        prev = cur;
    }
    // for (int i = 0; i <= n; i++) {
    //     cout << i << ": " << path[i] << "\n";
    // }
    int idx = n;
    int val = 0;
    vector<int> ans;
    while (1) {
        // cout << idx << " " << val << "\n";
        if (idx == 0) {
            break;
        }
        if (path[idx - 1][delta + val - (a[idx - 1].first - a[idx - 1].second)]) {
            // cout << "chose:" << idx << "\n";
            ans.push_back(idx);
            val -= (a[idx - 1].first - a[idx - 1].second);
        }
        idx--;
    }
    // cout << cur[delta + 0] - 1;
    cout << ans.size() << "\n";
    shuffle(ans.begin(), ans.end(), rnd);
    for (auto x : ans) {
        cout << x << " ";
    }
    cout << "\n";
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}