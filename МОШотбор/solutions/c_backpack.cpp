#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

const int sz = 1e3;

// void solve() {
//     int n;
//     cin >> n;
//     vector<long long> a(n), b(n);
//     for (int i = 0; i < n; i++) {
//         cin >> a[i];
//     }
//     for (int i = 0; i < n; i++) {
//         cin >> b[i];
//     }
//     bitset<sz> prev(0), cur(0);
//     bitset<sz> prev_b(0), cur_b(0);
//     vector<int> f(sz, -1);
//     bitset<sz> now_can(0);
//     prev[0] = 1;
//     prev_b[0] = 1;
//     for (int i = 0; i < n; i++) {
//         // cout << (prev << a[i]) << "\n";
//         cur = (prev) | (prev << a[i]);
//         cur_b = (prev_b) | (prev_b << b[i]);
//         now_can = cur ^ prev;
//         for (int j = now_can._Find_first(); j < sz; j = now_can._Find_next(j)) {
//             f[j] = i;
//         }
//         prev = cur;
//         prev_b = cur_b;
//     }
//     // cout << cur << "\n" << cur_b << "\n";
//     for (int w = sz - 1; w >= 0; w--) {
//         if (!(cur[w] && cur_b[w])) {
//             continue;
//         } else {
//             vector<int> ans;
//             int x = w;
//             while (x > 0) {
//                 ans.push_back(f[x] + 1);
//                 x -= a[f[x]];
//             }
//             cout << "w = " << w << "\n";
//             cout << cur_b[w] << "\n";
//             cout << ans.size() << "\n";
//             for (auto to : ans) {
//                 cout << to << " ";
//             }
//             cout << "\n";
//             return;
//         }
//         // cout << cur[w];
//     }
// }

void prev() {
    int q;
    cin >> q;
    while (q--) {
        int n;
        cin >> n;
        vector<long long> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        bitset<sz> a_cur{0}, a_prev{0}, b_cur{0}, b_prev{0};
        a_prev[0] = 1, b_prev[0] = 1;
        for (int i = 0; i < n; i++) {
            a_cur = a_prev | (a_prev << a[i]);
            b_cur = b_prev | (b_prev << b[i]);
            a_prev = a_cur;
            b_prev = b_cur;
        }
        // cout << a_cur << "\n" << b_cur << "\n";
        for (int w = sz - 1; w >= 0; w--) {
            if (a_cur[w] == b_cur[w] && b_cur[w]) {
                cout << w << "\n";
                break;
            }
        }
    }
}
int main() {
    // int q;
    // cin >> q;
    // while (q--) {
    //     solve();
    // }
    prev();
}