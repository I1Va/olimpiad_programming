#include <iostream>
using namespace std;

int main() {
    long long l, r, a;
    cin >> l >> r >> a;
    long long n = r - l + 1;
    long long k = (r - l) / a;
    cout << n * k - (1 + k) * k * a / 2;
}
