#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

ostream& operator<< (ostream& stream, const pair<int, int>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream;
}

string a, b;
map<char, string> alp;
const int sz = 26;
pair<int, int> tree[1 << sz];

void print_tree() {
    cout << string(10, '=') << "tree" << string(10, '=') << "\n";
    for (int i = 0; i < (1 << sz); i++) {
        cout << i << ": " << tree[i] << "\n";
    }
    cout << string(10, '=') << "tree" << string(10, '=') << "\n\n";
}

bool add(const string& word) {
    int cur = 1;
    bool state = true;
    for (auto x : word) {
        if (x == '0') {
            cur = cur * 2;
        } else {
            cur = cur * 2 + 1;
        }
        if (tree[cur].second != 0) {
            state = false;
            break;
        }
    }
    if (!state) {
        return false;
    }
    if (tree[cur].first != 0 && tree[cur].second != 0) {
        return false;
    }
    cur = 1;
    for (auto x : word) {
        tree[cur].first++;
        if (x == '0') {
            cur = cur * 2;
        } else {
            cur = cur * 2 + 1;
        }
    }
    tree[cur].second++;
    return true;
}

void rem(const string& word) {
    int cur = 1;
    // cout << "remove: " << word << "\n";
    for (auto x : word) {
        tree[cur].first--;
        if (x == '0') {
            cur = cur * 2;
        } else {
            cur = cur * 2 + 1;
        }
        // cout << "removed node: " << cur << "\n";
    }
    tree[cur].second--;
}

bool stop = false;

bool match(int fi, const string& fir, int si, const string& sec) {
    while (fi < (int) fir.size() && si < (int) sec.size()) {
        if (fir[fi] != sec[si]) {
            return false;
        }
        fi++, si++;
    }
    return true;
}

void print_log(int w1, int w2, map<char, string>& alp) {
    cout << string(10, '=') << "log" << string(10, '=') << "\n";
    cout << "ai: " << w1 << ", bi:" << w2 << "\n"; 
    for (auto to : alp) {
        cout << to.first << " " << to.second << "\n";
    }
    cout << string(10, '=') << "***" << string(10, '=') << "\n\n";
}

void rec(int ai, int bi) {
    print_log(ai, bi, alp);
    // print_tree();
    if (stop) {
        return;
    }
    if (bi > (int) b.size()) {
        return;
    }
    if (ai == (int) a.size()) {
        if (bi != (int) b.size()) {
            return;
        }
        stop = true;
        return;
    }
    if (alp[a[ai]].size()) {
        // cout << "match: " << ai << " " << bi << "\n";
        if (!match(0, alp[a[ai]], bi, b)) {
            return;
        }
        rec(ai + 1, bi + int (alp[a[ai]].size()));
    } else {
        
        alp[a[ai]] = "";
        int cur = 1;
        // cout << "new(" << a[ai] << "): " << ai << " " << bi << "\n"; 
        for (int i = bi; i < (int) b.size(); i++) {
            alp[a[ai]] += b[i];
            if (!add(alp[a[ai]])) {
                continue;
            }
            // cout << "try: " << a[ai] << " = " << alp[a[ai]] << "\n";
            rec(ai + 1, i + 1);
            rem(alp[a[ai]]);
            if (stop) {
                return;
            }
        }
        alp[a[ai]] = "";
    }
}

void solve() {
    cin >> a >> b;
    rec(0, 0);
    // cout << "solved: " << stop << "\n";
    for (auto to : alp) {
        cout << to.first << " " << to.second << "\n";
    }
    cout << "\n";
}

void solve_manager() {
    int t;
    cin >> t;
    while (t--) {
        alp.clear();
        for (int i = 0; i < (1 << sz); i++) {
            tree[i] = {0, 0};
        }
        stop = false;
        solve();
    }
}

int main() {
    solve_manager();
}