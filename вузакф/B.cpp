#include <iostream>
#include <vector>
using namespace std;

int c1 = 0;
int c2 = 0;
int c3 = 0;
void ans(bool s) {
    if (s) {
        cout << "! YES" << endl;
    } else {
        cout << "! NO" << endl;
    }
}

int ask(int a, int b, int c, int d) {
    cout << "? " << a + 1 << " " << b + 1 << " " << c + 1 << " " << d + 1 << endl;
    char v;
    cin >> v;
    if (v == '0') {
        c3++;
    }
    if (v == '+') {
        c1++;
    } else if (v == '-') {
        c2++;
    }
}


int main() {
    int n;
    cin >> n;
    int v = 1;
    for (int i = 0; i < n; i++) {
        ask(i, (i + 1) % n, (i + 1) % n, (i + 2) % n);
    }
    ans((c1 == 0 && c2 > 0) || (c1 > 0 && c2 == 0) || ());
}