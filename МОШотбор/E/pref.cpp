#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

vector<int> prefix_function(const string& s) {
    int n = (int) s.size();
    vector<int> p(n, 0);
    p[0] = n;
    for (int i = 1; i < n; i++) {
        // префикс функция точно не больше этого значения + 1
        int cur = p[i - 1];
        // уменьшаем cur значение, пока новый символ не сматчится
        while (s[i] != s[cur] && cur > 0)
            cur = p[cur - 1];
        // здесь либо s[i] == s[cur], либо cur == 0
        if (s[i] == s[cur])
            p[i] = cur + 1;
    }
    return p;
}

void rec(int cur, int idx, const int& len, const int& cnt, const vector<int>& pref, int& ans) {
    cout << idx << " " << cur << "\n";
    if (cur == cnt) {
        ans++;
        return;
    }
    if (idx >= (int) pref.size()) {
        return;
    }
    if (pref[idx] >= len) {
        rec(cur + 1, idx + len, len, cnt, pref, ans);
    }
    rec(cur, idx + 1, len, cnt, pref, ans);
}

int nextbit(int idx, const int& len, const vector<int>& pref) {
    idx++;
    while (idx < (int) pref.size() && pref[idx] < len) {
        idx++;
    }
    if (idx == (int) pref.size()) {
        return -1;
    }
    return idx;
}

int nextchar(int idx, const char& v, const string& a) {
    idx++;
    while (idx < (int) a.size() && a[idx] != v ) {
        idx++;
    }
    if (idx == (int) a.size()) {
        return -1;
    }
    return idx;
}

bool get(int len, string word, string bit) {
    if ((int) word.size() == 0 || (int) bit.size() == 0) {
        if (!((int) word.size() == 0 && (int) bit.size() == 0)) {
            return false;
        }
        return true;
    }
    auto pref = prefix_function(bit);
    int l1 = 0;
    int r1 = nextchar(l1, word[0], word);
    int l2 = 0;
    int r2 = nextbit(l2, len, pref);
    cout << word.substr(l1, r1 - l1 + 1) << "\n";
    cout << bit.substr(l2, r2 - l2 + 1) << "\n";
    cout << word.substr(l1 + 1, (int) word.size() - 2) << "\n";
    cout << bit.substr(l2 + len, (int) word.size() - 2 * len) << "\n";
    // символ word[l1] кодируется как word.substr(l1, len)
    return true;
}

void solve() {
    string word, bit;
    cin >> word >> bit;
    get(10, word, bit);
    
    exit(0);
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}