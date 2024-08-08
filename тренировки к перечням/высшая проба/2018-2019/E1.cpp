#include <iostream>
#include <vector>
using namespace std;

int n, m;

int main() {
    cin >> n >> m;
    vector<bool> a(n);
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        a[i] = (bool) v;
    }
    while (m--) {
        int t, l, r;
        cin >> t >> l >> r;
        l--;
        r--;
        if (t == 1) {
            for (int i = l; i <= r; i += 2) {
                a[i] = !a[i];
            }
        } else {
            int res = 0;
            for (int i = l; i <= r; i++) {
                res += a[i];
            }
            cout << res << "\n";
        }
    }

}