#include <iostream>
#include <vector>
#include <string>
using namespace std;

const long long mod = 1e9 + 7;

void build(int v, int l, int r, vector<long long>& tree, const vector<long long>& a) {
    if (r - l == 1) {
        tree[v] = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(v * 2, l, m, tree, a);
    build(v * 2 + 1, m, r, tree, a);
    tree[v] = (tree[v * 2] + tree[v * 2 + 1]) % mod;
}

void upd(int v, int l, int r, int pos, long long val, vector<long long>& tree) {
    if (r - l == 1) {
        tree[v] = val;
        return;
    }
    int m = (l + r);
    if (pos < m) {
        upd(v * 2, l, m, pos, val, tree);
    } else {
        upd(v * 2 + 1, m, r, pos, val, tree);
    }
    tree[v] = (tree[v * 2] + tree[v * 2 + 1]) % mod;
}

long long get(int v, int l, int r, int ql, int qr, vector<long long>& tree) {
    if (l >= qr || r <= ql) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return (get(v * 2, l, m, ql, qr, tree) + get(v * 2 + 1, m, r, ql, qr, tree)) % mod;
}

void print_tree(vector<long long>& tree, const int& x) {
    for (int i = 0; i <= x; i++) {
        cout << get(1, 0, x + 1, i, i + 1, tree) << " ";
    }
    cout << "\n";
}

int main() {
    int n, x;
    cin >> n >> x;
    string s;
    cin >> s;
    vector<long long> prev(x + 1);
    vector<long long> tree(4 * (x + 1));
    for (int i = 1; i <= x; i++) {
        prev[i] = 1;
    }
    build(1, 0, x + 1, tree, prev);
    for (int _ = n - 2; _ >= 0; _--) {
        // cout << "prev = ";
        // print_tree(tree, x);
        for (int y = 1; y <= x; y++) {
            if (s[_] == '=') {
                prev[y] = get(1, 0, x + 1, y, y + 1, tree);
            } else if (s[_] == '>') {
                prev[y] = get(1, 0, x + 1, 0, y, tree);
            } else {
                prev[y] = get(1, 0, x + 1, y + 1, x + 1, tree);
            }
        }
        build(1, 0, x + 1, tree, prev);
    }
    cout << get(1, 0, x + 1, 0, x + 1, tree);
}