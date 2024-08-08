#include <iostream>
#include <vector>
using namespace std;

const int maxn = 1e5;

int a[maxn];
int tree[maxn * 4 + 1];

void build(int v, int l, int r) {
    if (r - l == 1) {
        tree[v] = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(v * 2, l, m);
    build(v * 2 + 1, m, r);
    tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
}

int get(int v, int l, int r, int ql, int qr) {
    if (l >= qr || r <= ql) {
        return 1e9;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return min(get(v * 2, l, m, ql, qr), get(v * 2 + 1, m, r, ql, qr));
}

void upd(int v, int l, int r, int pos, int val) {
    if (r - l == 1) {
        tree[v] = val;
        return;
    }
    int m = (l + r) / 2;
    if (pos < m) {
        upd(v * 2, l, m, pos, val);
    } else {
        upd(v * 2 + 1, m, r, pos, val);
    }
    tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(1, 0, n);
    int q;
    cin >> q;
    while (q--) {
        int t, i;
        cin >> t >> i;
        i--;
        if (t == 2) {
            upd(1, 0, n, i, -a[i]);
        } else {
            int l = i + 1;
            int r = n;
            while (r - l > 1) {
                int m = (l + r) / 2;
                cout << m << ": " << get(1, 0, n, m, n) << "\n";
                if (get(1, 0, n, m, n) <= a[i]) {
                    l = m;
                } else {
                    r = m;
                }
            }
            
            cout << get(1, 0, n, r, n) << "\n";
        }
    }
}