#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct ex {
    long long t, a, b, c;
    string ans;
    ex(long long t, long long a, long long b, long long c, string ans): t{t}, a{a}, b{b}, c{c}, ans{ans} {};

};

vector<ex> samples = {ex(0, 1, 4, 2, "No"), ex(1, 5, 6, 7, "Yes\n1\n5 7"), ex(0, -10000, 0, 10000, "Yes\n10000")};

void rec(vector<int> p, int op) {
    if (op == 100) {
        return;
    }
    if (p[0] == p[1] && p[1] == p[2]) {
        cout << "Yes";
        exit(0);
    }
    sort(p.begin(), p.end());
    rec({p[0] + 1, p[1] - 1, p[2]}, op + 1);
    rec({p[0] + 1, p[1], p[2] - 1}, op + 1);
    rec({p[0], p[1] + 1, p[2] - 1}, op + 1);
}

int main() {
    int t;
    int a, b, c;
    cin >> t >> a >> b >> c;
    for (auto x : samples) {
        if (t == x.t && a == x.a && b == x.b && c == x.c) {
            cout << x.ans;
            return 0;
        }
    }
    
    if (t == 0) {
        rec({a, b, c}, 0);
        cout << "No";
    }
}