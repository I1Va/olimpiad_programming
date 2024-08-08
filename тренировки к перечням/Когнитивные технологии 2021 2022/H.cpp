#include <iostream>
#include <vector>
using namespace std;

int ask(int v) {
    cout << "? " << v << endl;
    int res;
    cin >> res;
    return res;
}

void ans(int v) {
    cout << "! " << v << endl;
    exit(0);
}

int n;

int min3(int a, int b, int c) {
    return min(c, min(a, b));
}

int main() {
    cin >> n;
    ans(min3(ask(1), ask(1 + n / 3), ask(1 + n / 3 * 2)));
}