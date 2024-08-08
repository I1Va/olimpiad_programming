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
int n;

void rec(int idx, vector<int> cur, const vector<int>& a, const vector<int>& b, int& mn, vector<int>& ans) {
    if (idx == n) {
        int res = 0;
        for (int i = 1; i < n; i++) {
            res += abs(cur[i] - cur[i - 1]);
        }
        if (res < mn) {
            mn = res;
            ans = cur;
        }
        return;
    }
    for (int w = a[idx]; w <= b[idx]; w++) {
        cur[idx] = w;
        rec(idx + 1, cur, a, b, mn, ans);
    }
}

void solve() {

    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    int mn = 1e9;
    vector<int> ans;
    vector<int> cur(n);
    rec(0, cur, a, b, mn, ans);
    cout << mn << "\n" << ans << "\n";
    

}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}