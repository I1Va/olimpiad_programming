#include <iostream>
#include <string>
using namespace std;

bool check(const string& s, const string& t) {
    int s_sz = (int) s.size();
    int t_sz = (int) t.size();
    int si = 0, ti = 0;
    int cnt = 0;
    while (si < s_sz && ti < t_sz) {
        while (si < s_sz && s[si] != t[ti]) {
            si += 2;
            cnt += 2;
        }
        if (cnt % 2 == 0) {
            ti++;
            si++;
            cnt = 0;
        } else {
            return false;
        }
    }
    if (ti < t_sz) {
        return false;
    }
    if ((s_sz - si) % 2 == 1) {
        return false;
    }
    return true;
}

int main() {
    string s, t;
    cin >> s >> t;
    if (check(s, t)) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    
}