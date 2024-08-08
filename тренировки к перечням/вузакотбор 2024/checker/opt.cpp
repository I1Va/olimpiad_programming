#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) {
        return a.second > b.second;
    }
    return a.first < b.first;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a;
    for (int i = 0; i < q; i++) {
        int x, d;
        cin >> x >> d;
        a.emplace_back(abs(x - d), x + d);
    }
    int ans = 0;
    sort(a.begin(), a.end(), cmp);
    auto [l, r] = a[0];
    for (int i = 0; i < q; i++) {
        if (a[i].first > r) {
            ans += r - l + 1;
            l = a[i].first;
            r = a[i].second;
            continue;
        }
        r = a[i].second;
    }
    ans += r - l + 1;
    cout << n - ans;
}

int main() {
    solve();
}