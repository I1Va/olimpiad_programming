#include <iostream>
#include <vector>
#include <string>
using namespace std;

ostream& operator<< (ostream& stream, const pair<long long, long long>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream; 
}

ostream& operator<< (ostream& stream, const vector<pair<long long, long long>>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

long long n;
vector<pair<long long, long long>> a;

long long get(long long x1, long long y1, long long x2, long long y2) {
    long long c = 0;
    for (long long i = 0; i < n; i++) {
        if (a[i].first >= x1 && a[i].first <= x2 && a[i].second >= y1 && a[i].second <= y2) {
            c++;
        }
    }
    return c;
}

void upd(long long xo, long long yo) {
    for (auto& to : a) {
        long long x = to.first;
        long long y = to.second;
        x = -(to.second - yo) + xo;
        y = (to.first - xo) + yo;
        to = {x, y};
    }
}

void solve() {
    cin >> n;
    a.resize(n);
    for (long long i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    long long q;
    cin >> q;
    while (q--) {
        string t;
        cin >> t;
        if (t == "ask") {
            long long x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << get(x1, y1, x2, y2) << "\n";
        } else {
            long long v = stoi(t.substr(1, (long long) t.size() - 1)) / 90;
            long long xo, yo;
            cin >> xo >> yo;
            for (long long i = 0; i < v; i++) {
                upd(xo, yo);
            }
            // cout << a << "\n";
        }
    }
}

int main() {
    solve();
}