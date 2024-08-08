#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

ostream& operator<< (ostream& stream, const pair<int, int>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream;
}

int n, k;
vector<int> pool;
vector<int> a;

int ask(int idx) {
    if (a[idx] == 0) {
        cout << idx + 1 << endl;
        cin >> a[idx];
    }
    return a[idx];
}

int get(int l, int r) {
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

// void rec(int l, int r) {

// }

void solve() {
    cin >> n >> k;
    pool.resize(k);
    a.resize(n);
    for (int i = 0; i < k; i++) {
        cin >> pool[i];
    }
}

int main() {
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cout << get(0, n - 1);
}
