#include <iostream>
#include <vector>
using namespace std;

// ostream& operator<< (ostream& stream, ci)
long long get(long long x) {
    long long res = 0;
    while (x > 1) {
        bool s = true;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                res += i;
                s = false;
                x /= i;
                break;
            }
            
            
        }
        if (s) {
            res += x;
            break;
        }
    }
    return res;
}

void solve() {
    long long x;
    cin >> x;
    cout << get(x) << " ";
}
int main() {
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}