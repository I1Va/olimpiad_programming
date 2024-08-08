#include <iostream>
using namespace std;

long long a, b, c;
const bool deb = 0;

void print() {
    if (!deb) {
        return;
    }
    long long kf = (a + c - 1) / c;
    long long kl = b / c;
    cout << kf << " " << kl << "\n";
    cout << (kf * c - a) / 2 << " " << (b - kl * c) / 2 << " " << (kl - kf) * (1 + (c / 2)) + 1 << "\n";
}

int main() {
    
    cin >> a >> b >> c;
    long long kf = (a + c - 1) / c;
    long long kl = b / c;
    if (c > b || kf > kl) {
        cout << (b - a + 1) / 2;
        return 0;
    }
    
    print();
    long long ans = (kf * c - a) / 2 + (b - kl * c) / 2 + max(0ll, (kl - kf) * (1 + ((c - 1) / 2))) + 1;
    cout << ans;
}
