#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

ostream& operator<< (ostream& stream, const pair<int, int>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream;
}

bool comp(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) {
        return a.second > b.second;
    }
    return a.first < b.first;
}

int main() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a;
    a.reserve(2 * q);
    for (int i = 0; i < q; i++) {
        int x, d;
        cin >> x >> d;
        a.push_back({max(1, x - d), 1});
        a.push_back({min(n, x + d), -1});
    }
    sort(a.begin(), a.end(), comp);
    int cur = 0;
    int ans = 0;
    int prev = a[0].first;
    bool open = true;
    for (auto x : a) {
        if (cur) {
            ans += x.first - prev;
            if (open) {
                ans++;
                open = false;
            }
        } else {
            open = true;
        }
        cur += x.second;
        prev = x.first;
        // cout << "ans = " << ans << ", cur = " << cur << ", x = " << x << "\n";
    }
    if (cur) {
        ans += n - prev;
    }
    cout << n - ans;
}