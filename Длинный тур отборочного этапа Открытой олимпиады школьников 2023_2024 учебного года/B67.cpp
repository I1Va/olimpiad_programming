#pragma GCC optimize("O3")
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

struct node {
    long long val;
    long long push;
    int sz;
    node(): val{0}, push{-1}, sz{0} {};
    node(long long val, long long push, int sz): val{val}, push{push}, sz{sz} {}
};

int n, q;
vector<node> tree;
vector<long long> a;
const long long INF = 1e18;
// Инвариант:
// node.val - АКТУАЛЬНОЕ значение суммы в данной вершине
// push - значение push - величины вершины

ostream& operator<< (ostream& stream, const node& a) {
    stream << "{" << a.val << " " << a.push << "}";
    return stream;
}

void print() {
    cout << "\n" << string(100, '#') << "\n";
    for (int i = 0; i < 4 * n + 1; i++) {
        cout << i << ": " << tree[i] << "\n";
    }
    cout << "\n" << string(100, '#') << "\n";
}

node merge(const node& a, const node& b) {
    return node(a.val + b.val, -1, a.sz + b.sz);
}

void build(int ver, int l, int r) {
    if (r - l == 1) {
        tree[ver] = node(a[l], -1, 1);
        return;
    }
    int m = (l + r) / 2;
    build(ver * 2, l, m);
    build(ver * 2 + 1, m, r);
    tree[ver] = merge(tree[ver * 2], tree[ver * 2 + 1]);
}

void push(int ver) {
    long long delta = tree[ver].push;
    if (delta == -1) {
        return;
    }
    tree[ver * 2].val = delta * tree[ver * 2].sz;
    tree[ver * 2].push = delta;
    tree[ver * 2 + 1].val = delta * tree[ver * 2 + 1].sz;
    tree[ver * 2 + 1].push = delta;
    tree[ver].push = -1;
}

void upd(int ver, int l, int r, int ql, int qr, long long x, long long k, int idx) {
    if (l >= qr || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        // cout << "upd:" << l << " " << r << "\n";
        tree[ver].push = x;
        tree[ver].val = x * tree[ver].sz;
        return;
    }
    push(ver);
    int m = (l + r) / 2;
    if ((k >> idx) & 1) {
        upd(ver * 2 + 1, l, m, ql, qr, x, k, idx - 1);
        upd(ver * 2, m, r, ql, qr, x, k, idx - 1);
    } else {
        upd(ver * 2, l, m, ql, qr, x, k, idx - 1);
        upd(ver * 2 + 1, m, r, ql, qr, x, k, idx - 1);
    }
    
    tree[ver] = merge(tree[ver * 2], tree[ver * 2 + 1]);
}

node get(int ver, int l, int r, int ql, int qr, int k, int idx) {
    // cout << l << " " << r << "\n";
    if (l >= qr || r <= ql) {
        return node(0, -1, 0);
    }
    if (ql <= l && r <= qr) {
        // cout << l << " " << r << "\n";
        return tree[ver];
    }
    push(ver);
    int m = (l + r) / 2;
    if ((k >> idx) & 1) {
        return merge(get(ver * 2 + 1, l, m, ql, qr, k, idx - 1), get(ver * 2, m, r, ql, qr, k, idx - 1));
    }
    return merge(get(ver * 2, l, m, ql, qr, k, idx - 1), get(ver * 2 + 1, m, r, ql, qr, k, idx - 1));
}

int sz(long long k) {
    int cur = 0;
    while (k >> 1 > 0) {
        cur++;
        k = k >> 1;
    }
    return cur;
}

void print(string s) {
    cout << s;
    for (int i = 0; i < n; i++) {
        cout << get(1, 0, n, i, i + 1, 0, sz(n)).val << " ";
    }
    cout << "\n";
}

void solve() {
    cin >> n;
    n = (1 << n);
    a.resize(n);
    tree.resize(4 * n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(1, 0, n);
    cin >> q;
    // print("ao = ");
    while (q--) {
        int t, l, r, k, v;
        cin >> t >> l >> r >> k;
        if (t == 1) {
            cin >> v;
            upd(1, 0, n, l, r + 1, v, k, sz(n) - 1);
        } else {
            cout << get(1, 0, n, l, r + 1, k, sz(n) - 1).val << "\n";
        }
        // print("a = ");
    }
}

int main() {
    
    solve();
}