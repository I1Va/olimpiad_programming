#include <iostream>
#include <vector>
using namespace std;

void solve() {
    long long a, b, r;
    cin >> a >> b >> r;
    long long ans = 1e18;
    for (long long x = 0; x <= r; x++) {
        ans = min(ans, abs((a ^ x) - (b ^ x)));
    }
    cout << ans << "\n";   
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
 
    }
}