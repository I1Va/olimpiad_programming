#include <iostream>
using namespace std;

long long a, b, c;

void solve1() {
    if (!(a <= 1e5 && b <= 1e5 && c <= 1e5)) {
        return;
    }
    int cnt = 0;
    while (a < b) {
        if ((a + 2) % c != 0) {
            a += 2;
        } else {
            a += 1;
        }
        cnt++;
    }
    cout << cnt;
    exit(0);
}

void solve2() {
    if (c != 2) {
        return;
    }
    cout << (b - a + 1) / 2;
}

int main() {

    cin >> a >> b >> c;
    solve1();
    solve2();
}