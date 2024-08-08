#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> split(const string& s) {
    vector<string> res;
    string buf = "";
    for (auto x : s) {
        if (x == ' ') {
            res.push_back(buf);
            buf = "";
        } else {
            buf += x;
        }
    }
    if (buf.size()) {
        res.push_back(buf);
    }
    return res;
}

void solve() {
    string s1, s2;
    cin >> s1 >> s2;
    cout << s1 << "\n" << s2 << "\n";
}

int main() {
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}