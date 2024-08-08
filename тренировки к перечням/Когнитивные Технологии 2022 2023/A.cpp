#include <iostream>
using namespace std;

int main() {
    long long h, w;
    cin >> h >> w;
    long long k = 0;
    for (long long a = 1; a < w; a++) {
        for (long long b = 1; b < h; b++) {
            // cout << a << " " << b << ": " << min(a * h, min((w - a) * (h - b), b * (w - a))) << "\n";
            k = max(k, min(a * h, min((w - a) * (h - b), b * (w - a))));
        }
    }
    cout << k;
}