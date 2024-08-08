#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> a;
int q;

void solve(int v) {
    for (int i = 0; i < n; i++) {
        if (v % a[i] != 1) {
            cout << i + 1 << "\n";
            return;
        }
    }
    cout << -1 << "\n";
}

int main() {
    
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]++;
    }
    cin >> q;
    while (q--) {
        int v;
        cin >> v;
        solve(v);
    }
}