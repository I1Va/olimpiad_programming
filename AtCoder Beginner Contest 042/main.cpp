#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

struct node {
    int l, r;
    int mn, mx;
    bool decr;
    node(int l, int r, int mn, int mx, bool decr): l{l}, r{r}, mn{mn}, mx{mx}, decr{decr} {}
};

ostream& operator<< (ostream& stream, const pair<int, int>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream;
}

int n, k;
vector<int> pool;
vector<int> a;
unordered_set<int> was;

int ask(int idx) {
    if (a[idx] == 0) {
        cout << idx + 1 << endl;
        cin >> a[idx];
        was.insert(a[idx]);
    }
    return a[idx];
}

int get_min(int l, int r) {
    while (r - l > 2) {
        int m1 = (2 * l + r) / 3;
        int m2 = (2 * r + l) / 3;
        if (ask(m1) > ask(m2)) {
            l = m1;
        } else {
            r = m2;
        }
    }
    vector<pair<int, int>> p = {{ask(l), l}, {ask((l + r) / 2), (l + r) / 2}, {ask(r), r}};
    sort(p.begin(), p.end());
    return p[0].second;
}

int get_max(int l, int r) {
    while (r - l > 2) {
        int m1 = (2 * l + r) / 3;
        int m2 = (2 * r + l) / 3;
        if (ask(m1) < ask(m2)) {
            l = m1;
        } else {
            r = m2;
        }
    }
    vector<pair<int, int>> p = {{ask(l), l}, {ask((l + r) / 2), (l + r) / 2}, {ask(r), r}};
    sort(p.begin(), p.end());
    return p[2].second;
}

void solve() {
    cin >> n >> k;
    
}

int main() {
    solve();
}