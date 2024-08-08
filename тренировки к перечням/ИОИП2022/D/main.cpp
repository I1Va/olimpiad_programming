#include <iostream>
#include <vector>
using namespace std;

struct node {
    int push_type;
    long long push_val;
    long long val;
    int sz;
    node(int push_type, long long push_val, long long val, int sz): push_type{push_type}, push_val{push_val}, val{val}, sz{sz} {};
};

vector<node> tree;
vector<long long> a;

node merge(node a, node b) {
    return node(0, 0, a.val + b.val, a.sz + b.sz);
}

void build(int v, int l, int r) {
    if (r - l == 1) {
        tree[v] = node(0, 0, a[l], 1);
        return;
    }
    int m = (l + r) / 2;
    build(v * 2, l, m);
    build(v * 2 + 1, m, r);
    tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

void push(int v) {
    if (tree[v].push_type == 0) {
        return;
    }
    if (tree[v].push_type == 1) {
        tree[v].push_type = 0;
        tree[v * 2].push_type = 1;
        tree[v * 2].push_val = tree[v].push_val;
        tree[v * 2].val = tree[v * 2].push_val * tree[v * 2].sz;
        tree[v * 2 + 1].push_type = 1;
        tree[v * 2 + 1].push_val = tree[v].push_val;
        tree[v * 2 + 1].val = tree[v * 2 + 1].push_val * tree[v * 2 + 1].sz;
        return;
    }
    if (tree[v].push_type == 2) {
        tree[v].push_type = 0;
        tree[v * 2].push_type = 2;
        tree[v * 2].val = get_bit()
    }
}
void upd1(int v, int l, int r, int ql, int qr, long long val) {
    if (l >= qr || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        tree[v].push_type = 1;
        tree[v].push_val = val;
        tree[v].val = tree[v].sz * val;
        return;
    }
    push(v);
}
int main() {
    int n, q;
    cin >> n >> q;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        long long x;
        if (t == 2) {
            cin >> x;
        }

    }
}