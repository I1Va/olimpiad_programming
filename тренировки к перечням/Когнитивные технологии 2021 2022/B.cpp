#include <iostream>
using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;
    if (a < b * 3) {
        cout << "macchiato";
    } else if (a > b * 5) {
        cout << "latte";
    } else {
        cout << "cappuccino";
    }
}