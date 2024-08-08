#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct node {
    int val;
    int sz;

    int l_len;
    char l_sym;

    int r_len;
    char r_sym;

    bool alive;
    node(): val{0}, sz{0}, l_len{0},
    l_sym{'$'}, r_len{0}, r_sym{'$'}, alive{false} {}
    node(int val, int sz, int l_len, char l_sym, int r_len, char r_sym, bool alive): val{val}, sz{sz}, l_len{l_len},
    l_sym{l_sym}, r_len{r_len}, r_sym{r_sym}, alive{alive} {}
};

ostream& operator<< (ostream& stream, const node& a) {
    stream << "{sz = " << a.sz << ", val = " << a.val << ", left: " << a.l_sym << "(" << a.l_len << "), right = " << 
    a.r_sym << "(" << a.r_len << ")";
    return stream;
}

int n, q;
const int maxn = 1e5;
string s;

node tree[maxn * 4];

void print() {
    for (int i = 0; i < 4 * n; i++) {
        cout << i << ": " << tree[i] << "\n";
    }
}

node merge(node a, node b) {
    if (!b.alive) {
        return a;
    }
    if (!a.alive) {
        return b;
    }
    node m = node(a.val + b.val, a.sz + b.sz, a.l_len, a.l_sym, b.r_len, b.r_sym, true);
    if (a.r_sym == b.l_sym) {
        m.val += 1;
        if (b.l_len == b.sz) {
            m.r_len = b.l_len + a.r_len;
            m.r_sym = b.l_sym;
        }
        if (a.r_len == a.sz) {
            m.l_len = a.r_len + b.l_len;
            m.l_sym = a.r_sym;
        }
    }
    return m;
}

void build(int ver, int l, int r) {
    if (r - l == 1) {
        tree[ver] = node(0, 1, 1, s[l], 1, s[l], true);
        return;
    }
    int m = (l + r) / 2;
    build(ver * 2, l, m);
    build(ver * 2 + 1, m, r);
    tree[ver] = merge(tree[ver * 2], tree[ver * 2 + 1]);
}

node get(int v, int l, int r, int ql, int qr) {
    if (l >= qr || r <= ql) {
        return node(0, 0, 0, '$', 0, '$', false);
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return merge(get(v * 2, l, m, ql, qr), get(v * 2 + 1, m, r, ql, qr));
}

int main() {
    cin >> n >> q;
    cin >> s;
    build(1, 0, n);
    // print();
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << get(1, 0, n, l - 1, r).val << "\n";
    }
}
