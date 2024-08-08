#include <iostream>
#include <vector>
using namespace std;

int n, q;
vector<long long> a;

void updater(int l, int r, int k, int v) {
    
}
int main() {
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cin >> q;
    while (q--) {
        int t, l, r, k, v;
        cin >> t >> l >> r >> k;
        if (t == 1) {
            cin >> v;
            updater(l, r, k, v);
        }
    }
}