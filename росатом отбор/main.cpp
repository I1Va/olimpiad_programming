#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> cnt(n + 1, 0);
    int v;
    int mx = 0;
    while (cin >> v) {
        if (v >= 1 && v <= n) {
            cnt[v] += 1;
            mx = max(mx, cnt[v]);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (cnt[i] == mx) {
            cout << i << " ";
        }
    }
}