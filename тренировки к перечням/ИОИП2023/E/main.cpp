#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n, m, d, p;
vector<long long> a, b;
vector<string> coms;

void shift() {
    vector<long long> n_a(n);
    int c = 0;
    for (int i = d; i < n; i++) {
        n_a[i - d] = a[i];
        c = i - d;
    }
    for (int i = 0; i < d; i++) {
        n_a[i + c + 1] = a[i];
    }
    a = n_a;
}

void xorp() {
    for (int i = 0; i < n; i++) {
        b[i] = a[i] ^ b[i];
    }
}

void andp() {
    for (int i = 0; i < n; i++) {
        b[i] = a[i] & b[i];
    }
}

void orp() {
    for (int i = 0; i < n; i++) {
        b[i] = a[i] | b[i];
    }
}

void solve1() {
    b = a;
    while (p--) {
        for (auto x : coms) {
            shift();
            if (x == "xor") {
                xorp();
            } else if (x == "and") {
                andp();
            } else if (x == "or") {
                orp();
            }
        }
    }
    for (auto x : b) {
        cout << x << " ";
    }
}

int main() {
    
    cin >> n >> m >> d >> p;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    coms.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> coms[i];
    }
    if (n <= 1000 && p <= 100) {
        solve1();
    }

}