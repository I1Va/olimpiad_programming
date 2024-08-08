#include <iostream>
#include <vector>
using namespace std;

// vector<long long> fact(long long w) {
//     vector<long long> res;
//     while (w > 1) {
//         for (long long i = 2; i <= (int) sqrt(w) + 1; i++) {
//             bool state = false;
//             while (w % i == 0) {
//                 state = true;
//                 w /= i;
//             }
//             if (state) {
//                 res.push_back(i);
//             }
            
//         }
//     }
// }


void solve() {
    long long n;
    cin >> n;
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            ans++;
        }
    }
    cout << ans << "\n";
}

int main() {
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}