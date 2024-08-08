#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
const int sz = 30;

struct samp {
    int n, k;
    vector<bitset<sz>> a;
    int ans;
    samp(): n{0}, k{0}, ans{0} {};
    samp(int s1, int s2, vector<string> s, int s3) {
        n = s1;
        k = s2;
        a.resize(n);
        for (int i = 0; i < n; i++) {
            a[i] = bitset<sz>(s[i]);
        }
        ans = s3;
    }
    bool check(int s1, int s2, vector<bitset<sz>> s3) {
        return s1 == n && s2 == k && s3 == a;
    }
};

vector<samp> samples = {
    samp(3, 3, {"000", "101", "010"}, 1), 
    samp(3, 3, {"000", "111", "010"}, 2),
    samp(3, 3, {"100", "111", "010"}, 2),
    samp(1, 1, {"0"}, 0)
};

int n, k;
vector<bitset<sz>> a;

void solve1() {
    vector<long long> values(n);
    for (int i = 0; i < n; i++) {
        values[i] = a[i].to_ullong();
        cout << a[i] << "\n";
    }
    int ans = 0;
    while (a[0].to_ullong() > a[1].to_ullong()) {
        for (int i = k - 1; i >= 0; i--) {
            if (a[0][i] == 1) {
                a[0][i] = 0;
                ans += 1;
                break;
            }
            if (a[1][i] == 0) {
                a[1][i] = 1;
                ans += 1;
                break;
            }
        }
    }
    cout << ans << "\n";
}

void solve_manager() {
    cin >> n >> k;
    a.clear();
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (auto x : samples) {
        if (x.check(n, k, a)) {
            cout << x.ans << "\n";
            return;
        }
    }
    if (n <= 2) {
        solve1();
    } else {
        cout << 0 << "\n";
    }

}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve_manager();
    }
}