#include <iostream>
#include <vector>
#include <map>
using namespace std;

ostream& operator<< (ostream& stream, const vector<long long>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

long long mod = 1e9 + 7;

long long binpow (long long a, long long n) {
	long long res = 1;
	while (n) {
		if (n & 1)
			res *= a;
            res %= mod;
		a = ((a % mod) * (a % mod)) % mod;
		n >>= 1;
	}
	return res;
}

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n);
    map<long long, int> used;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (int j = 0; j < 20; j++) {
            long long temp = binpow(2ll, a[i] + j);
            if (used.find(temp) == used.end()) {
                used[temp] = 1;
            }
        }
    }
    // for (auto to : used) {
    //     cout << to.first << " ";
    // }
    // cout << "\n";
    vector<long long> prefs(n + 1);
    for (int i = 1; i <= n; i++) {
        prefs[i] = prefs[i - 1] + (1ll << a[i - 1]);
    }
    // cout << "prefs = " << prefs << "\n";
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            long long temp = (prefs[j + 1] - prefs[i]);
            if (__builtin_popcount(temp) == 1) {
                ans++;
            }
        }
    }
    cout << ans;
}

int main() {
    solve();
}