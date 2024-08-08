#include <iostream>
#include <string>
using namespace std;

long long mod;

long long mul(long long a, long long b) {
    return ((a % mod) * (b % mod)) % mod;
}

long long POW(long long a, long long n) {
    long long res = 1;
    while (n != 0) {
        if (n & 1)
            res = mul(res, a);
        a = mul(a, a);
        n >>= 1;
    }
    return res;
}

int main() {
    int n;
    long long x, y;
    cin >> n >> x >> y;
    mod = stoll(string('9', n));
    cout << POW(x, y);
}