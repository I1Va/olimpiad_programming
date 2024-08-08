#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int f(const vector<int>& p, const vector<char>& a, const vector<char>& b) {
    int n = a.size();
    vector<char> a1(n);
    for (int i = 0; i < n; i++) {
        a1[p[i]] = a[i];
    }
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (a1[i] == 'n' || b[i] == 'n') {
            continue;
        }
        if (a1[i] - '0' < b[i] - '0') {
            c++;
        }
    }
    return c;
}

void solve() {
    int n;
    cin >> n;
    vector<char> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
    vector<int> ans;
    int val = n + 1;
    while (1) {
        if (f(p, a, b) < val) {
            val = f(p, a, b);
            ans = p;
        }
        if (!next_permutation(p.begin(), p.end())) {
            break;
        }
    }
    for (auto x : ans) {
        cout << x + 1 << " ";
    }
    // cout << "val : " << val << "\n";
    cout << "\n";
}
int main() {
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}