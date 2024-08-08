#include <iostream>
#include <vector>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

const int INF = 1e9;

void solve() {
    int n;
    int maxb = 1000;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    vector<int> ans(n);
    int mn = 1e9;
    for (int x = 0; x <= maxb; x++) {
        vector<int> cur(n);
        int res = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] <= x && x <= b[i]) {
                cur[i] = x;
                continue;
            }
            if (x > b[i]) {
                cur[i] = b[i];
                continue;
            }
            if (x < a[i]) {
                cur[i] = a[i];
                continue;
            }
        }
        for (int i = 1; i < n; i++) {
            res += abs(cur[i] - cur[i - 1]);
        }
        if (res < mn) {
            mn = res;
            ans = cur;
        }
    }
    cout << mn << "\n" << ans << "\n";

}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}