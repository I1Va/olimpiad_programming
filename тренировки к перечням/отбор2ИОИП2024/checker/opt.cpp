#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <vector>
using namespace std;

ostream& operator<< (ostream& stream, const vector<char>& a) {
    for (auto to : a) {
        stream << to;
    }
    return stream;
}

void del(vector<char>& cur) {
    if (((int) cur.size() - 1) % 2 == 1) {
        // Можно удалить последний элемент
        cur.pop_back();
        // cout << "deleted top: new_cur = " << cur << "\n";
    } else {
        // Можно попробовать удалить предпоследний элемент
        int top = *(cur.end() - 1);
        cur.pop_back();
        cur.pop_back();
        cur.push_back(top);
    }
}

bool equal(const string s1, const vector<char>& s2) {
    int n = (int) s1.size();
    int m = (int) s2.size();
    if (n != m) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    string s, t;
    cin >> s >> t;
    if (s[0] != t[0]) {
        cout << "NO";
        return 0;
    }
    int si = 2;
    int ti = 1;
    int n = (int) s.size();
    int m = (int) t.size();
    vector<char> cur;
    cur.push_back(s[0]);
    cur.push_back(s[1]);
    while (si < n) {
        // cout << "cur = " << cur << "\n";
        if (*(cur.end() - 1) == t[ti]) {
            cur.push_back(s[si]);
            si++;
            ti++;
            if (ti == m) {
                del(cur);
                ti--;
            }
        }
        if (*(cur.end() - 1) != t[ti]) {
            del(cur);
            ti--;
        }
    }
    // cout << "con: " << cur << "\n";
    if (equal(t, cur)) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    
}