#include <iostream>
#include <vector>
using namespace std;

int n, k;

int get(int idx, const vector<int>& a) {
    int cur = 1;
    int cap = 1;
    int cnt = 0;
    for (int i = idx; i < n; i++) {
        if (cap - a[i] <= 0) {
            cur++;
            cap = cur;
        } else {
            cap -= a[i];
        }
        cnt++;
        if (cur == k) {
            return cnt;
        }
    }
    return -1;
}

int main() {
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = 1e9;
    for (int i = 0; i < n; i++) {
        int res = get(i, a);
        if (res != -1) {
            ans = min(ans, res);
        }
    }
    if (ans == 1e9) {
        cout << -1;
    } else {
        cout << ans;
    }
}