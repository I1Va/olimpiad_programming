#include <iostream>
using namespace std;

int main() {
    long long r, g, n;
    cin >> r >> g >> n;
    long long mod = r + g + 1;
    long long n1 = n % mod;
    if (n1 >= r + 1 && n1 < r + 1 + g) {
        cout << n;
    } else {
        cout << n + r + 1 - n1;
    }
}