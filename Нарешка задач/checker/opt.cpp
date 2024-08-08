#include <iostream>
#include <vector>
using namespace std;

ostream& operator<< (ostream& stream, const pair<long long, long long>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream;
}

ostream& operator<< (ostream& stream, const vector<pair<long long, long long>>& a) {
    for (auto x : a) {
        stream << x << " ";
    }
    return stream;
}

const long long INF = 1e18;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        k--;
        // if (a[k] < 0) {
        //     cout << "NO\n";
        //     continue;
        // }
        vector<pair<long long, long long>> left, right;
        long long cur = 0;
        long long mn = INF;
        for (int i = k - 1; i >= 0; i--) {
            cur += a[i];
            if (cur < 0) {
                mn = min(mn, cur);
            }
            if (cur > 0) {
                if (mn == INF) {
                    mn = 0;
                }
                left.push_back({cur, mn});
                mn = INF;
                cur = 0;
            }
        }
        if (cur < 0) {
            left.push_back({0, mn});
        }
        cur = 0;
        mn = INF;
        for (int i = k + 1; i < n; i++) {
            cur += a[i];
            if (cur < 0) {
                mn = min(mn, cur);
            }
            if (cur > 0) {
                if (mn == INF) {
                    mn = 0;
                }
                right.push_back({cur, mn});
                mn = INF;
                cur = 0;
            }
        }
        if (cur < 0) {
            right.push_back({0, mn});
        }
        // cout << "left = " << left << "\n";
        // cout << "right = " << right << "\n";
        int l = 0;
        int r = 0;
        cur = a[k];
        while (1) {
            // cout << l << " " << r << "\n";
            if (l == (int) left.size()) {
                cout << "YES\n";
                break;
            }
            if (r == (int) right.size()) {
                cout << "YES\n";
                break;
            }
            if (left[l].second + cur >= 0) {
                cur += left[l].first;
                l++;
                continue;
            }
            if (right[r].second + cur >= 0) {
                cur += right[r].first;
                r++;
                continue;
            }
            cout << "NO\n";
            break;
        }
    }
}