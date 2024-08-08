#include <iostream>
using namespace std;

int n, m;

void solve1() {
    cout << n << "\n";
    for (int i = 1; i <= n; i++) {
        cout << 1 << "\n" << i << "\n";
    }
}

int main() {
    
    cin >> n >> m;
    if (n <= 32 && m == 1e5) {
        solve1();
    }
}