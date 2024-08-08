#pragma gcc optimize("Ofast")
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct node {
    int val;
    int sz;
    bool push;
    node(): val{0}, sz{0}, push{0} {};
    node(int val, int sz, bool push): val{val}, sz{sz}, push{push} {};
};

ostream& operator<< (ostream& stream, const node& a) {
    stream << "{" << a.val << ", " << a.sz << ", " << a.push << "}";
    return stream; 
}

ostream& operator<< (ostream& stream, const vector<bool>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

int n, m;
bool deb = 0;

node merge(const node& a, const node& b) {
    return node(a.val + b.val, a.sz + b.sz, false);
}

void build(int v, int l, int r, vector<node>& tree, const vector<bool>& a) {
    if (r - l == 1) {
        tree[v] = node(a[l], 1, false);
        return;
    }
    int m = (l + r) / 2;
    build(v * 2, l, m, tree, a);
    build(v * 2 + 1, m, r, tree, a);
    tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

void push(int v, vector<node>& tree) {
    if (!tree[v].push) {
        return;
    }
    tree[v].push = false;
    tree[v * 2].val = tree[v * 2].sz - tree[v * 2].val;
    tree[v * 2 + 1].val = tree[v * 2 + 1].sz - tree[v * 2 + 1].val;
    tree[v * 2].push = !tree[v * 2].push;
    tree[v * 2 + 1].push = !tree[v * 2 + 1].push;
}

void upd(int v, int l, int r, int ql, int qr, vector<node>& tree) {
    if (l >= qr || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        tree[v].val = tree[v].sz - tree[v].val;
        tree[v].push = !tree[v].push;
        return;
    }
    push(v, tree);
    int m = (l + r) / 2;
    upd(v * 2, l, m, ql, qr, tree);
    upd(v * 2 + 1, m, r, ql, qr, tree);
    tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

node get(int v, int l, int r, int ql, int qr, vector<node>& tree) {
    if (l >= qr || r <= ql) {
        return node(0, 0, 0);
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    push(v, tree);
    int m = (l + r) / 2;
    return merge(get(v * 2, l, m, ql, qr, tree), get(v * 2 + 1, m, r, ql, qr, tree));
}

void print_a(const string& a, vector<node>& tree, int n) {
    cout << string(10, '=') << a << string(10, '=') << "\n";
    for (int i = 0; i < n; i++) {
        cout << get(1, 0, n, i, i + 1, tree).val << " ";
    }
    cout << "\n" << string(10, '=') << a << string(10, '=') << "\n";
}

void print_tree(const string& a, const vector<node>& tree, const int& n) {
    if (!deb) {
        return;
    }
    cout << string(10, '=') << a << string(10, '=') << "\n";
    for (int i = 0; i < 4 * n + 1; i++) {
        cout << i << ": " << tree[i] << "\n";
    }
    cout << string(10, '=') << a << string(10, '=') << "\n\n";
}

void test() {
    vector<bool> a = {0, 1, 1, 0, 0, 0, 1, 1};
    int n = (int) a.size();
    vector<node> tree(4 * n + 1);
    build(1, 0, n, tree, a);
    int q;
    cin >> q;
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            upd(1, 0, n, l, r + 1, tree);
        } else {
            cout << "query:" << get(1, 0, n, l, r + 1, tree).val << "\n";
        }
    }
    print_a("a", tree, n);

}

int get_manager(int l, int r, int sz1, vector<node>& tree1, int sz2, vector<node>& tree2) {
    if (l > r) {
        return 0;
    }
    int k = (r - l) / 2;
    int ql1 = l / 2;
    int qr1 = (l + 2 * k) / 2 + 1;
    if (l % 2 == 1) {
        int res = get(1, 0, sz1, ql1, qr1, tree1).val;
        if (deb) {
            cout << "CHOOSE: tree1[" << ql1 << ":" << qr1 << ") = " << res << "\n";
        }
        return res;
    } else {
        int res = get(1, 0, sz2, ql1, qr1, tree2).val;
        if (deb) {
            cout << "CHOOSE: tree2[" << ql1 << ":" << qr1 << ") = " << res << "\n";
        }
        return res;
    }
}

void solve() {
    cin >> n >> m;
    vector<bool> a(n);
    int sz1 = n / 2, sz2 = n / 2 + n % 2;
    vector<bool> a1(sz1), a2(sz2);
    vector<node> tree1(sz1 * 4 + 1), tree2(sz2 * 4 + 1);
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        a[i] = v;
        if (i % 2 == 1) {
            a1[i / 2] = v;
        } else {
            a2[i / 2] = v;
        }
    }
    build(1, 0, sz1, tree1, a1);
    build(1, 0, sz2, tree2, a2);
    if (deb) {
        cout << "a = " << a << "\n";
        cout << "a1 = " << a1 << "\n";
        cout << "a2 = " << a2 << "\n";
    }
    

    // print_a("a1", tree1, sz1);
    // print_a("a2", tree2, sz2);
    // cout << "start:\n";
    print_tree("tree1", tree1, sz1);
    print_tree("tree2", tree2, sz2);
    while (m--) {
        int t, l, r;
        cin >> t >> l >> r;
        l--;
        r--;
        int k = (r - l) / 2;
        int ql = l / 2;
        int qr = (l + 2 * k) / 2 + 1;
        if (deb) {
            cout << "QUESION: " << t << ", [" << l << ":" << r << "]\n";
        }
        
        
        if (t == 1) {
            int k = (r - l) / 2;
            int ql = l / 2;
            int qr = (l + 2 * k) / 2 + 1;
            if (deb) {
                cout << "CHOOSE: ";
                if (l % 2 == 1) {
                    cout << "tree1\n";
                } else {
                    cout << "tree2\n";
                }
                cout << "TRANSLATED QUESTION: " << t << ", [" << ql << ":" << qr << ")\n";
            }
            if (l % 2 == 1) {
                upd(1, 0, sz1, ql, qr, tree1);
            } else {
                upd(1, 0, sz2, ql, qr, tree2);
            }  
        } else {
            int l1 = l;
            int l2 = l + 1;
            if (l1 % 2 != 1) {
                swap(l1, l2);
            }
            int res1 = get_manager(l, r, sz1, tree1, sz2, tree2);
            int res2 = get_manager(l + 1, r, sz1, tree1, sz2, tree2);
            // if (deb) {
            //     cout << "GET: tree1[" << ql1 << ":" << qr1 << "): " << res1 << "\n";
            //     cout << "GET: tree2[" << ql2 << ":" << qr2 << "): " << res2 << "\n";
            // }
            cout << res1 + res2 << "\n";
        }
        print_tree("tree1", tree1, sz1);
        print_tree("tree2", tree2, sz2);
        // print_a("a1", tree1, sz1);
        // print_a("a2", tree2, sz2);
        // cout << "\n\n";

    }

}

int main() {
    // test();
    deb = 0;
    solve();
}