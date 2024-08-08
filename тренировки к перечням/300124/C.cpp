#include <iostream>
#include <vector>
using namespace std;

const int n = 60;

void solve() {
    long long a, b, r;
    cin >> a >> b >> r;
    long long d = a - b;
    // vector<bool> used(n, false);
    while (1) {
        long long cur = d;
        int idx = -1;
        for (int i = n; i >= 0; i--) {
            if (((a >> i) & 1ll) == ((b >> i) & 1ll)) {
                continue;
            }
            if ((1ll << i) > r) {
                continue;
            }
            // cout << i << ": " << ((a >> i) & 1ll) << "\n";
            if (((a >> i) & 1ll) == 0ll) {
                // cout << i << ":+ " << d + 2 * (1ll << i) << "\n";
                if (abs(d + 2ll * (1ll << i)) <= abs(cur)) {
                    cur = d + 2ll * (1ll << i);
                    idx = i;
                }
            } else {
                // cout << i << ":- " << d - 2 * (1ll << i) << "\n";
                if (abs(d - 2ll * (1ll << i)) <= abs(cur)) {
                    cur = d - 2ll * (1ll << i);
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            break;
        }
        a ^= (1ll << idx);
        r -= (1ll << idx);
        d = cur;
        // cout << idx << ": " << d << "\n";
    }
    cout << abs(d) << "\n";
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
 
    }
}