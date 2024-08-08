#include <iostream>
#include <vector>
using namespace std;

int main() {
    long long n, a, b;
    cin >> n >> a >> b;
    if (b < a) {
        cout << 2 * (a + b) * n - b * (n - 1);
    } else {
        long long s = (n + 1) / 2;
        if (n % 2 == 0) {
            cout << s * 2 * (a + b) + a;
        } else {
            cout << s * 2 * (a + b);
        }
    }
}
