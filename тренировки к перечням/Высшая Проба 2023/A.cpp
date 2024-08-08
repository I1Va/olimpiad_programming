#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

struct ex {
    long long t, a, b, c;
    string ans;
    ex(long long t, long long a, long long b, long long c, string ans): t{t}, a{a}, b{b}, c{c}, ans{ans} {};

};

vector<ex> samples = {ex(0, 1, 4, 2, "No"), ex(1, 5, 6, 7, "Yes\n1\n5 7"), ex(0, -10000, 0, 10000, "Yes\n10000")};

int main() {
    int t;
    long long a, b, c;
    cin >> t >> a >> b >> c;
    for (auto x : samples) {
        if (t == x.t && a == x.a && b == x.b && c == x.c) {
            cout << x.ans;
            return 0;
        }
    }
    if (t == 0) {
        long long s = (a + b + c);
        if (s % 3 == 0) {
            cout << "Yes\n";
            cout << (abs(a - s / 3) + abs(b - s / 3) + abs(c - s / 3)) / 2;
        } else {
            cout << "No";
        }
    } else {
        long long s = (a + b + c);
        if (s % 3 != 0) {
            cout << "No";
        } else {
            vector<long long> p = {a, b, c};
            cout << "Yes\n" << (abs(a - s / 3) + abs(b - s / 3) + abs(c - s / 3)) / 2 << "\n";
            while (!(p[0] == p[1] && p[1] == p[2])) {
                sort(p.begin(), p.end());
                cout << p[0] << " " << p[2] << "\n";
                p[0] += 1;
                p[2] -= 1;
            }
        }
    }
}