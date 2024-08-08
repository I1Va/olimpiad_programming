#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<long long> get(long long x) {
    vector<long long> res;
    while (x > 1) {
        bool stop = true;
        for (long long i = 2; i <= (long long) sqrt(x) + 1; i++) {
            
            bool s = false;
            while (x % i == 0) {
                x /= i;
                s = true;
                stop = false;
            }
            if (s) {
                res.push_back(i);
            }
        }
        if (stop) {
            res.push_back(x);
            return res;
        }
    }
    return res;
}

void solve() {
    long long a, b;
    cin >> a >> b;
    long long ans = 1e18;
    for (auto x : get(a)) {
        long long l = 0;
        long long r = b + 1;
        while (r - l > 1) {
            long long m = (l + r) / 2;
            if (x * m < b) {
                l = m;
            } else {
                r = m;
            }
        }
        // cout << x << ": " << x * l << " " << x * r << "\n";
        ans = min(ans, r * x - b);
    }
    cout << ans << "\n";
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    {
        /* code */
    }
    
}