#include <iostream>
using namespace std;

long long n, m;

int main() {
    cin >> n >> m;
    if (m % 2 == 1) {
        cout << "0 0";
    } else {
        // минимальный случай
        long long c = m / 2;
        long long v = (1 + c - 1) * (c - 1) + 2 * (c - 1) + (1 + (m / 2 - 2)) * (m / 2 - 2);
        cout << min(2ll, max(0ll, (n - (m + 1)) - v)) << " ";
        // максимальный случай
        if (n - (m + 1) < m) {
            cout << min(2ll, (n - (m + 1)) / (m / 2));
        } else {
            n -= (m + 1 + m);
            long long cur = 1;
            long long ans = 2;
            while (1) {
                if (n - cur * 4 >= 0) {
                    n -= cur * 4;
                    ans += 4;
                    cur++;
                } else {
                    ans += n / cur;
                    break;
                }
            }
            cout << ans;
        }
    }
}