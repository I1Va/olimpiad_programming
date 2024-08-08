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


struct HASH {
    long long mod = 10000000019;
    long long p = 179;
    int n;
    string s;
    vector<long long> pows, prefs;
    long long add(long long a, long long b) {
        return (a % mod + b % mod) % mod;
    }
    long long mul(long long a, long long b) {
        return ((a % mod) * (b % mod)) % mod;
    }
    long long sub(long long a, long long b) {
        return (a % mod - b % mod + mod) % mod;
    }
    HASH(string s) {
        n = (int) s.size();
        pows.resize(n + 1);
        pows[0] = 1;
        for (int i = 1; i <= n; i++) {
            pows[i] = mul(pows[i - 1], p);
        }
        prefs.resize(n + 1);
        prefs[0] = 0;
        for (int i = 1; i <= n; i++) {
            prefs[i] = add(mul(prefs[i - 1], p), s[i - 1] - 'a');
        }
    }
    long long get(int l, int r) {
        return sub(prefs[r + 1], mul(prefs[l], pows[r - l + 1]));
    }
};

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
    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        k = gcd(a[i], k);
    }
    set<long long> pool;
    for (int i = 0; i < n; i++) {
        HASH cur = HASH(w[i]);
        for (int len = k; len <= (int) w[i].size(); len += k) {
            // w[i].substr(0, len)
            pool.insert(cur.get(0, len - 1));
        }
    }
    
    // cout << "k: " << k << ", pool: " << pool << "\n";
    int q;
    cin >> q;
    while (q--) {
        string t;
        cin >> t;
        HASH h_t = HASH(t);
        int sz = (int) t.size();
        if (sz % k != 0) {
            cout << "No\n";
            continue;
        }
        int last = sz;
        for (int j = sz - k; j >= 0; j -= k) {
            // t.substr(j, last - j)
            bool res = pool.find(h_t.get(j, last - 1)) != pool.end();
            // cout << j << ": " << last << "\n";
            // cout << "find: " << t.substr(j, last - j) << ": " << res << "\n";
            if (res) {
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