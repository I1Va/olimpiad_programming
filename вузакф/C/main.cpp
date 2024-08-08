#include <iostream>
#include <vector>
using namespace std;

long long n, q;

const long long mod =  998244353;
vector<long long> a;

void get() {
    vector<long long> b(n);
    b[0] = a[0];
    for (int i = 1; i < n; i++) {
        b[i] = b[i - 1] + a[i];
        b[i] %= mod;
    }
    a = b;
}

int main() {
    
    cin >> n >> q;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    while (q--) {
        get();
    }
    for (auto to : a) {
        cout << to << " ";
    }


}