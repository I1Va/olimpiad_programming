#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <unordered_set>
#include <map>
#include <chrono>
#include <random>
using namespace std;

ostream& operator<< (ostream& stream, const vector<string>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);

int randrange(int a, int b) {
    return a + rnd() % (b - a);
}

string emp;
vector<string> alp;
string info;

string string_gen() {
    string res = "";
    for (int i = 0; i < 3; i++) {
        res += alp[randrange(0, 26)];
    }
    return res;
}

void build() {
    alp.resize(26);
    for (int i = 0; i < 26; i++) {
        alp[i] = emp + (char) ('A' + i);
    }
}

bool deb = 1;

void solve() {
    
    int n;
    if (deb) {
        build();
        n = randrange(1, 5);
        info += to_string(n) + "\n";
    } else {
        cin >> n;
    }
    
    vector<string> a(n), b(n);
    for (int i = 0; i < n; i++) {
        string temp1, temp2;
        if (deb) {
            temp1 = string_gen();
            temp2 = string_gen();
            info += temp1 + " " + temp2;
        } else {
            cin >> temp1 >> temp2;
        }
        a[i] = emp + temp1[0] + temp1[1] + temp1[2];
        b[i] = emp + temp1[0] + temp1[1] + temp2[0];
    }
    // cout << a << "\n" << b << "\n";
    set<string> used;
    vector<string> ans(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            if (a[i] == a[j] && ans[i] == "" || ans[j] == "") {
                ans[i] = b[i];
                ans[j] = b[j];
                used.insert(b[i]);
                used.insert(b[j]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            if (a[i] == b[j] && ans[j] != "" && ans[i] == "") {
                ans[i] = b[i];
                used.insert(b[i]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (ans[i] == "") {
            ans[i] = a[i];
            used.insert(ans[i]);
        }
    }
    if (used.size() != n) {
        cout << "NO";
    } else {
        cout << "YES\n";
        for (auto x : ans) {
            cout << x << "\n";
        }
    }
}
int main() {
   



}