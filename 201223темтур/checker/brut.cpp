#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<long long> b(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        b[i] = a[i % n];
    }
    vector<long long> prefs(2 * n + 1);
    prefs[0] = 0;
    for (int i = 1; i < 2 * n + 1; i++) {
        prefs[i] = prefs[i - 1] + b[i - 1];
    }
    long long ans = 0;
    for (int i = 0; i < 2 * n; i++) {
        for (int j = i; j < 2 * n; j++) {
            if (j - i + 1 > n) {
                continue;
            }
            ans = max(ans, prefs[j + 1] - prefs[i]);
        }
    }
    cout << ans;
    
}