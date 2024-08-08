#include <iostream>
using namespace std;

void solve(long long n, long long m) {
    if (n >= m) {
        cout << 0 << "\n";
    } else {
        long long res = 1;
        for (int i = 1; i <= n; i++) {
            res *= i;
            res %= m;
        }
        cout << res << "\n";
    }
}

int main() {
    long long n, m;
    for (int i = 0; i < 3; i++) {
        cin >> n >> m;
        solve(n, m);
    }
}