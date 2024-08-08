#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

ostream& operator<< (ostream& stream, const pair<int, int>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream;
}


bool check(int l, int r, const string& s) {
    pair<int, int> seg = {0, -1};
    for (int i = l; i <= l + (r - l + 1) / 2; i++) {
        // cout << i << " v " << r - i << "\n";
        if (s[i] == '0' && s[r - (i - l)] == '0') {
            continue;
        }
        seg = {i, r - (i - l)};
        break;
    }
    // cout << "seg: " << seg << "\n";
    for (int i = seg.first; i <= seg.second; i++) {
        if (s[i] != '1') {
            return false;
        }
    }
    // cout << "l:r | " << l << ":" << r << "\n"; 
    // for (int i = l; i <= r; i++) {
    //     cout << s[i];
    // }
    // cout << ": " << seg << "\n";
    return true;
}

long long cnt(const string& s) {
    int n = (int) s.size();
    long long res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (check(i, j, s)) {
                res++;
                // cout << s.substr(i, j - i + 1) << "\n";
            }
        }
    }
    return res;
}

void solve() {
    long long v;
    cin >> v;
    int len = 1e9;
    string ans;
    for (long long mask = 0; mask < (1 << 15); mask++) {
        string cur = bitset<20>(mask).to_string();
        for (int i = 0; i < 15; i++) {
            for (int j = i; j < 15; j++) {
                string test = cur.substr(i, j - i + 1);
                if (cnt(test) == v && j - i + 1 < len) {
                    ans = test;
                    len = ans.size();
                }
            }
        }
    }
    cout << ans << "\n";
}
int main() {
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}