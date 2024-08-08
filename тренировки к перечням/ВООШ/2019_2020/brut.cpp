#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

ostream& operator<< (ostream& stream, const pair<int, int>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream;
}

int n, q;
vector<pair<int, int>> a, quests;

int get1_2(int u, int d) {
    int res = -1;
    for (auto x : a) {
        if (abs(x.first - a[u].first) + abs(x.second - a[u].second) <= d) {
            res++;
        }
    }
    return res;
}

bool state1_2() {
    return n * q <= 1e7;
}

void solve1_2() {
    for (auto quest : quests) {
        int l = -1;
        int r = 1e8;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (get1_2(quest.first - 1, m) - 1 < quest.second) {
                l = m; 
            } else {
                r = m;
            }
        }
        cout << r << "\n";
    }
}

int get_mxcord(const vector<pair<int, int>>& a) {
    int mx = 0;
    for (auto to : a) {
        mx = max(max(abs(to.first), abs(to.second)), mx);
    }
    return mx;
}

bool state3() {
    return pow(get_mxcord(a), 2) <= 1e7;
}

int get3(int u, int d, const vector<vector<int>>& field, const int& mx) {
    int res = 0;
    for (int x = max(0, a[u].first - d); x <= min(2 * mx, a[u].first + d); x++) {
        for (int y = max(0, a[u].second - d); y <= min(2 * mx, a[u].second + d); y++) {
            res += field[x][y];
        }
    }
    return res;
}

struct node {
    vector<int> y;
    node(vector<int> y): y{y} {};
    node() {
        vector<int> temp;
        y = temp;
    }
    int calc(int mn_val, int mx_val) {
        return max(
            (int) ((upper_bound(y.begin(), y.end(), mx_val) - y.begin()) -
            (lower_bound(y.begin(), y.end(), mn_val) - y.begin())), 0);
    }
};

node merge(const node& a, const node& b) {
    int asz = (int) a.y.size();
    int ai = 0;
    int bsz = (int) b.y.size();
    int bi = 0;
    vector<int> m;
    m.reserve(asz + bsz);
    while (ai < asz && bi < bsz) {
        if (a.y[ai] < b.y[bi]) {
            m.push_back(a.y[ai]);
            ai++;
        } else {
            m.push_back(b.y[bi]);
            bi++;
        }
    }
    while (ai < asz) {
        m.push_back(a.y[ai]);
        ai++;
    }
    while (bi < bsz) {
        m.push_back(b.y[bi]);
        bi++;
    }
    return node(m);
}

void build(int v, int l, int r, vector<node>& tree, const vector<vector<int>>& columns) {
    if (r - l == 1) {
        tree[v] = node(columns[l]);
        return;
    }
    int m = (l + r) / 2;
    build(v * 2, l, m, tree, columns);
    build(v * 2 + 1, m, r, tree, columns);
    tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

node get(int v, int l, int r, int ql, int qr, const vector<node>& tree) {
    if (l >= qr || r <= ql) {
        vector<int> temp;
        return node(temp);
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return merge(get(v * 2, l, m, ql, qr, tree), get(v * 2 + 1, m, r, ql, qr, tree));
}

void solve3() {
    for (auto& to : a) {
        to = {to.first + to.second, to.first - to.second};
    }
    int mx = get_mxcord(a);
    for (auto& to : a) {
        to.first += mx;
        to.second += mx;
        // cout << "point: " << to << "\n";
    }
    const int sz = 4 * 1e6;
    vector<vector<int>> columns(sz);
    for (auto to : a) {
        columns[to.first].push_back(to.second);
    }
    for (auto& to : columns) {
        sort(to.begin(), to.end());
    }
    // for (int i = 0; i <= sz; i++) {
    //     if (!columns[i].empty()) {
    //         cout << i << ": " << columns[i] << "\n";
    //     }
    // }
    // cout << "\n";
    vector<node> tree(4 * sz);
    build(1, 0, sz, tree, columns);
    for (auto quest : quests) {
        int l = -1;
        int r = 1e7;
        while (r - l > 1) {
            // cout << l << " " << r << "\n";
            int m = (l + r) / 2;
            int ql = max(0, a[quest.first - 1].first - m);
            int qr = min(2 * mx, a[quest.first - 1].first + m);
            int mn_val = max(0, a[quest.first - 1].second - m);
            int mx_val = min(2 * mx, a[quest.first - 1].second + m);
            auto res = get(1, 0, sz, ql, qr + 1, tree);
            // cout << "dist: " << m << " = " << res.y << ", " << mn_val << ":" << mx_val << ", " << res.calc(mn_val, mx_val) << "\n";
            if (res.calc(mn_val, mx_val) - 1 < quest.second) {
                l = m; 
            } else {
                r = m;
            }
        }
        cout << r << "\n";
    }
}

int main() {
    cin >> n >> q;
    a.resize(n);
    quests.resize(q);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    for (int i = 0; i < q; i++) {
        cin >> quests[i].first >> quests[i].second;
    }
    solve3();
}