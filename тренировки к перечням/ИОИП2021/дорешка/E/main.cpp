#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <set>
using namespace std;

ostream& operator<< (ostream& stream, const set<string>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

int main() {
    int n, m;
    cin >> n >> m;
    int k = -1;
    vector<string> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
        if (k == -1) {
            k = w[i].size();
        } else {
            k = gcd(w[i].size(), k);
        }
    }
    set<string> pool;
    for (int i = 0; i < n; i++) {
        for (int len = k; len <= (int) w[i].size(); len += k) {
            pool.insert(w[i].substr(0, len));
        }
    }
    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        k = gcd(a[i], k);
    }
    // cout << "k: " << k << ", pool: " << pool << "\n";
    int q;
    cin >> q;
    while (q--) {
        string t;
        cin >> t;
        int sz = (int) t.size();
        if (sz % k != 0) {
            cout << "No\n";
            continue;
        }
        int last = sz - 1;
        for (int j = sz - k; j >= 0; j -= k) {
            if (pool.find(t.substr(j, last - j + 1)) != pool.end()) {
                last = j;
            }
        }
        if (last == 0) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}
