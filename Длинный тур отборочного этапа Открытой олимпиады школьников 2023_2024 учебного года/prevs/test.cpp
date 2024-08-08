#include <iostream>
#include <vector>
using namespace std;

long long q;

long long get(long long x) {
    long long res = 1;
    while (x % 2 == 0) {
        x /= 2;
    }
    while (x > 1) {
        for (int i = 2; i <= x; i++) {
            long long cur = 0;
            while (x % i == 0) {
                cur++;
                x /= i;
            }
            res *= (cur * 2 + 1);
        }
    }
    return res;
}

int main() {
 
    cin >> q;
    cout << get(q);

}