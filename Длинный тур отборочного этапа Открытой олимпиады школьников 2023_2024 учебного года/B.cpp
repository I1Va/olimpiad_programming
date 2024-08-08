#pragma GCC optimize("O3")
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

int n, q;
vector<long long> tree;
vector<long long> mod;
vector<long long> a;

// Инвариант:
// node.val - АКТУАЛЬНОЕ значение суммы в данной вершине
// push - значение push - величины вершины

void build(int ver, int l, int r) {
    if (r - l == 1) {
        tree[ver] = a[l];
        mod[ver] = -1;
        return;
    }
    int m = (l + r) / 2;
    build(ver * 2, l, m);
    build(ver * 2 + 1, m, r);
    tree[ver] = tree[ver * 2] + tree[ver * 2 + 1];
}

void upd(int ver, int l, int r, int ql, int qr, long long x, long long k, int idx) {
    if (l >= qr || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        // cout << "upd:" << l << " " << r << "\n";
        tree[ver] = x * (r - l);
        mod[ver] = x;
        return;
    }
    int m = (l + r) / 2;
    if ((k >> idx) & 1) {
        upd(ver * 2 + 1, l, m, ql, qr, x, k, idx - 1);
        upd(ver * 2, m, r, ql, qr, x, k, idx - 1);
    } else {
        upd(ver * 2, l, m, ql, qr, x, k, idx - 1);
        upd(ver * 2 + 1, m, r, ql, qr, x, k, idx - 1);
    }
    if (mod[ver] == -1) {
        tree[ver] = tree[ver * 2] + tree[ver * 2 + 1];
    } else {
        tree[ver] = mod[ver] * (r - l);
    }
    
}

long long get(int ver, int l, int r, int ql, int qr, int k, int idx) {
    // cout << l << " " << r << "\n";
    if (l >= qr || r <= ql) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        // cout << l << " " << r << "\n";
        return tree[ver];
    }
    int m = (l + r) / 2;
    if ((k >> idx) & 1) {
        
        return get(ver * 2 + 1, l, m, ql, qr, k, idx - 1) + get(ver * 2, m, r, ql, qr, k, idx - 1)
    }
    return get(ver * 2, l, m, ql, qr, k, idx - 1), get(ver * 2 + 1, m, r, ql, qr, k, idx - 1);
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
            cout << get(1, 0, n, l, r + 1, k, sz(n) - 1) << "\n";
        }
        // print("a = ");
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    solve();
}