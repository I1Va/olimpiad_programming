#include <iostream>
#include <random>
#include <chrono>
using namespace std;

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937_64 rnd(now);

long long randrange(long long a, long long b) {
    return a + rnd() % (b - a);
}

const long long mxv = 5;
const long double EPS = 1.0l / 1e7;

int main() {
    long double k = randrange(1, 5);
    long long b = randrange(1, 5);
    long long x1, y1, x2, y2;
    while (1) {
        x1 = randrange(-mxv, mxv);
        y1 = randrange(-mxv, mxv);
        x2 = randrange(-mxv, mxv);
        y2 = randrange(-mxv, mxv);
        if (abs(x1 * k + b - y1) > EPS && abs(x2 * k + b - y2) > EPS) {
            cout << x1 << " " << y1 << "\n" << x2 << " " << y2 << "\n" << k << " " << b;
            return 0;
        }
    }
}