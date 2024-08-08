#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, q;
    long long x;
    cin >> n >> q >> x;
    x *= 100;
    vector<long long> cnt(q);
    for (int i = 0; i < n; i++) {
        int t;
        long long m;
        int k;
        cin >> t >> m >> k;
        cnt[t - 1] += m * k;
    }
    sort(cnt.begin(), cnt.end());
    reverse(cnt.begin(), cnt.end());
    int idx = 0;
    while (x > 0 && idx < q) {
        x -= cnt[idx];
        idx += 1;
    }
    if (x <= 0) {
        cout << idx;
        return 0;
    }
    cout << -1;
}
