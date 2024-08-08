#include <iostream>
#include <vector>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

int n, m;

void build(int v, int l, int r, vector<int>& tree, const vector<int>& a) {
    if (r - l == 1) {
        tree[v] = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(v * 2, l, m, tree, a);
    build(v * 2 + 1, m, r, tree, a);
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
}

void upd(int v, int l, int r, int pos, int val, vector<int>& tree) {
    if (r - l == 1) {
        tree[v] = val;
        return;
    }
    int m = (l + r) / 2;
    if (pos < m) {
        upd(v * 2, l, m, pos, val, tree);
    } else {
        upd(v * 2 + 1, m, r, pos, val, tree);
    }
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
}

int get(int v, int l, int r, int ql, int qr, vector<int>& tree) {
    if (l >= qr || r <= ql) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return get(v * 2, l, m, ql, qr, tree) + get(v * 2 + 1, m, r, ql, qr, tree);
}

void print_tree(const vector<int>& tree) {
    return;
    for (int i = 0; i < 4 * n; i++) {
        cout << i << ": " << tree[i] << "\n";
    }
}

void upd_man(int pos, int val, vector<int>& a, vector<int>& left, vector<int>& right, vector<int>& tree_left, vector<int>& tree_right) {
    a[pos] = val;
    if (pos + 2 < n) {
        left[pos] = (a[pos] == 1 && a[pos + 1] == 2 && a[pos + 2] == 3);
        upd(1, 0, n, pos, left[pos], tree_left);
        right[pos] = (a[pos] == 3 && a[pos + 1] == 2 && a[pos + 2] == 1);
        upd(1, 0, n, pos, right[pos], tree_right);

    }
    if (pos - 1 >= 0 && pos + 1 < n) {
        left[pos - 1] = (a[pos - 1] == 1 && a[pos] == 2 && a[pos + 1] == 3);
        upd(1, 0, n, pos - 1, left[pos - 1], tree_left);
        right[pos - 1] = (a[pos - 1] == 3 && a[pos] == 2 && a[pos + 1] == 1);
        upd(1, 0, n, pos - 1, right[pos - 1], tree_right);
    }
    if (pos - 2 >= 0) {
        left[pos - 2] = (a[pos - 2] == 1 && a[pos - 1] == 2 && a[pos] == 3);
        upd(1, 0, n, pos - 2, left[pos - 2], tree_left);
        right[pos - 2] = (a[pos - 2] == 3 && a[pos - 1] == 2 && a[pos] == 1);
        upd(1, 0, n, pos - 2, right[pos - 2], tree_right);
    }
}

void print(vector<int>& a, vector<int>& left, vector<int>& right) {
    return;
    cout << "a = " << a << "\n";
    cout << "left = " << left << "\n";
    cout << "right = " << right << "\n";
}

int main() {
    cin >> n;
    vector<int> a(n), left(n), right(n), tree_left(4 * n + 1), tree_right(4 * n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 2; i++) {
        left[i] = (a[i] == 1 && a[i + 1] == 2 && a[i + 2] == 3);
        right[i] = (a[i + 2] == 1 && a[i + 1] == 2 && a[i] == 3);
    }
    build(1, 0, n, tree_left, left);
    build(1, 0, n, tree_right, right);
    
    cin >> m;
    print(a, left, right);
    print_tree(tree_right);
    while (m--) {
        char c;
        cin >> c;
        if (c == '?') {
            int l, r, t;
            cin >> l >> r >> t;
            if (t == 1) {
                cout << get(1, 0, n, l - 1, r - 2, tree_left);
            } else {
                cout << get(1, 0, n, l - 1, r - 2, tree_left) + get(1, 0, n, l - 1, r - 2, tree_right);
            }
            cout << "\n";
        } else {
            int pos, val;
            cin >> pos >> val;
            upd_man(pos - 1, val, a, left, right, tree_left, tree_right);
            print_tree(tree_right);
        }
        print(a, left, right);
        
    }
}