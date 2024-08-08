#include <iostream>
#include <vector>
using namespace std;

int n;

int exec(const vector<int>& a, const int u, const int v) {
    int sc = a[u];
    for (int i = u + 1; i <= v; i++) {
        sc = (sc <= a[i]);
    }
    int cur = a[0];
    for (int i = 1; i < n; i++) {
        if (i >= u && i <= v) {
            if (i == u) {
                cur = (cur <= a[i]);
            }
            continue;
        }
        cur = (cur <= a[i]);
    }
    return cur;
}

int main() {

    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int r;
    cin >> r;
    if (exec(a, -1, -1) == r) {
        cout << 0;
        return 0;
    }
    for (int u = 1; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            if (exec(a, u, v) == r) {
                cout << u + 1 << " " << v + 1;
                return 0;
            }
        }
    }
    cout << -1;
}
