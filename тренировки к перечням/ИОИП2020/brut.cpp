#include <iostream>
#include <cmath>
using namespace std;


bool is_prime(long long x) {
    for (long long d = 2; d <= (int) sqrt(x) + 1; d++) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    long long w = 1e18;
    while (!is_prime(w)) {
        w++;
    }
    cout << w;
    cout << ": " << is_prime(w);
}