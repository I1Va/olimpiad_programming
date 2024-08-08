#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <map>
using namespace std;

void solve(int tc) {
    string word, bit;
    cin >> word >> bit;
    // tc == 1 || tc == 3 || tc == 4
    if (0) {
        map<char, string> alp;
        int l = 0;
        int len = (int) bit.size() / (int) word.size();
        int wi = 0;
        while (l < (int) bit.size()) {
            string cur = bit.substr(l, len);
            l += len;
            if (alp.find(word[wi]) == alp.end()) {
                alp[word[wi]] = cur;
            }
            wi++;
            }
            for (auto to : alp) {
                cout << to.first << " " << to.second << "\n";
            }
            cout << "\n";
    } else {
        set<char> v;
        for (char w : word) {
            v.insert(w);
        }
        int idx = 1;
        for (auto x : v) {
            cout << x << " " << string(idx, '1') + string(1, '0') << "\n";
            idx++;
        }
        cout << "\n";
    }
    
    
    
}
int main() {
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        solve(tc);
    }
}