#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        long long x;
        cin >> n >> x;
        vector<long long> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
        }
        vector<long long> s(n);
        for (int i = 0; i < n; i++) {
            cin >> s[i];
        }
        vector<long long> l(n);
        for (int i = 0; i < n; i++) {
            cin >> l[i];
        }
        vector<long long> r(n);
        for (int i = 0; i < n; i++) {
            cin >> r[i];
        }
        long long mx = -1 * 1e18;
        bool state = false;
        for (int mask = 0; mask < (1 << n); mask++) {
            long long cur = x;
            bool temp = true;
            for (int i = 0; i < n; i++) {
                if ((mask  >> i) & 1) {
                    cur *= p[i]; 
                } else {
                    cur += s[i];
                }
                if (cur < l[i] || cur > r[i]) {
                    temp = false;
                    break;
                }
            }
            if (temp) {
                state = true;
                mx = max(mx, cur);
            } 
        }
        if (state) {
            cout << mx << "\n";
        } else {
            cout << "fail\n";
        }
    }
}