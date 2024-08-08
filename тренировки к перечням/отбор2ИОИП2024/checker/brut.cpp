#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

unordered_set<string> used;


void rec(string s) {
    used.insert(s);
    for (int i = 1; i < (int) s.size(); i += 2) {
        string f;
        for (int j = 0; j < i; j++) {
            f += s[j];
        }
        for (int j = i + 1; j < (int) s.size(); j++) {
            f += s[j];
        }
        rec(f);
    }
}

int main() {
    string s, t;
    cin >> s >> t;
    rec(s);
    if (used.find(t) == used.end()) {
        cout << "NO";
    } else {
        cout << "YES";
    }
}