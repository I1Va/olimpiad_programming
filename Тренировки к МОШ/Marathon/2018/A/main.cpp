#include <iostream>
#include <vector>
using namespace std;

void solve() {
    // Ну тут нужно рассмотреть несколько случаев нахождения
    // Точки в одной из четвертей координатной плоскости
    long long x, y;
    cin >> x >> y;
    if (x == 0 && y == 0) {
        cout << "0\n";
        return;
    }
    if (x == 0) {
        cout << "2\n0 " << abs(y) << "\n";
        return;
    }
    if (y == 0) {
        if (x > 0) {
            cout << "1\n" << abs(x) << "\n";
        } else {
            cout << "3\n 0 0 " << abs(x) << "\n";
        }
        return;
    }
    if (x > 0 && y > 0) {
        cout << "5\n" << x << " 0 0 0 " << y << "\n";
    } else if (x > 0 && y < 0) {
        cout << "3\n" << x << " 0 " << -y << "\n";
    } else if (x < 0 && y < 0) {
        cout << "4\n0 " << -y << " 0 " << -x << "\n"; 
    } else {
        cout << "5\n0 0 " << -x << " 0 " << y << "\n";
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}