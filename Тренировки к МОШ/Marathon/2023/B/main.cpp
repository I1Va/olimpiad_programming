#include <iostream>
#include <vector>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

const long long inf = 1e18;

struct node {
    long long mn = inf;
    long long mx = -inf;
    node() {}
    node(long long _mn, long long _mx) {
        mn = _mn;
        mx = _mx;
    }
};

vector<long long> a;
vector<node> tree;

node merge(node a, node b) {
    return node(min(a.mn, b.mn), max(a.mx, b.mx));
}

void build(int v, int l, int r) {
    if (r - l == 1) {
        tree[v] = node(a[l], a[l]);
        return;
    }
    int m = (l + r) / 2;
    build(v * 2, l, m);
    build(v * 2 + 1, m, r);
    tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

node get(int v, int l, int r, int ql, int qr) {
    if (l >= qr || r <= ql) {
        return node(inf, -inf);
    } 
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return merge(get(v * 2, l, m, ql, qr), get(v * 2 + 1, m, r, ql, qr));
}

void solve() {
    int n, d;
    long long I;
    cin >> n >> d >> I;
    a.resize(n);
    tree.resize(4 * n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(1, 0, n);
    vector<int> ans;
    for (int i = 0; i + d - 1 < n; i++) {
        auto res = get(1, 0, n, i, i + d);
        if (res.mx - res.mn <= I) {
            ans.push_back(i + 1);
        }
    }
    cout << ans.size() << "\n" << ans << "\n\n";
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}