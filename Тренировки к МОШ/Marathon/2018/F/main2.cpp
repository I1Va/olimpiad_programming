#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

ostream& operator<< (ostream& stream, const vector<long long>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

ostream& operator<< (ostream& stream, const vector<char>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

vector<long long> sim;
long long x;

const long long border = 1e7;

bool check(long long P) {
    int sz = (int) sim.size();
    if (sz <= 2) {
        return pow(abs(P), sz - 1) <= x;
    }
    return (abs(P) <= ceil(pow(x, 1.0 / (long double) ((int) sim.size() - 2))));
}


long long f(long long P) {
    int n = sim.size();
    long long res = 0;
    
    for (int i = 0; i < n; i++) {
        res += pow(P, i) * sim[i];
    }
    return res - x;
}

void solve() {
    string s;
    cin >> s;
    int n = (int) s.size();
    sim.clear();
    sim.reserve(n);
    int idx = n - 1;
    while (s[idx] == '0') {
        idx--;
    }
    for (int i = 0; i <= idx; i++) {
        sim.push_back(s[i] - '0');
    }
    x = stoll(s);
    // cout << x << ": " << check(1000) << "\n";
    long long l1 = -border;
    long long r1 = 0;
    while (r1 - l1 > 1) {
        long long m1 = (l1 + r1) / 2;
        if (check(m1)) {
            r1 = m1;
        } else {
            l1 = m1;
        }
    }
    long long l2 = 0;
    long long r2 = border;
    while (r2 - l2 > 1) {
        long long m2 = (l2 + r2) / 2;
        if (check(m2)) {
            l2 = m2;
        } else {
            r2 = m2;
        }
    }
    vector<long long> ans;
    // cout << x << ": " << l1 << ":" << r2 << "\n";
    for (long long P = -border; P <= border; P++) {
        if (!f(P)) {
            ans.push_back(P);
        }
    }
    cout << ans.size() << "\n" << ans << "\n";
}
int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
        // cout << i << ": done\n";
    }
    
}