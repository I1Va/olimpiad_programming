#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
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

int get_mxcord(const vector<pair<int, int>>& a) {
    int mx = 0;
    for (auto to : a) {
        mx = max(max(abs(to.first), abs(to.second)), mx);
    }
    return mx;
}

struct node {
    vector<int> y;
    node(vector<int> y): y{y} {};
    node(): y{{}} {};
    int calc(int mn_val, int mx_val) {
        return max(
            (int) ((upper_bound(y.begin(), y.end(), mx_val) - y.begin()) -
            (lower_bound(y.begin(), y.end(), mn_val) - y.begin())), 0);
    }
};

const int sz = 1e5;

vector<node> tree;
map<int, vector<int>> columns;
vector<int> x_cords;

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

void build(int v, int l, int r) {
    if (r - l == 1) {
        tree[v] = node(columns[x_cords[l]]);
        return;
    }
    int m = (l + r) / 2;
    build(v * 2, l, m);
    build(v * 2 + 1, m, r);
    tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

node get(int v, int l, int r, int ql, int qr) {
    if (l >= qr || r <= ql) {
        vector<int> temp;
        return node(temp);
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return merge(get(v * 2, l, m, ql, qr), get(v * 2 + 1, m, r, ql, qr));
}

void print(const vector<node>& tree) {
    for (int i = 0; i < (int) tree.size(); i++) {
        cout << i << ": " << tree[i].y << "\n";
    }
    cout << "\n";
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
    
    set<int> used;
    for (auto to : a) {
        if (used.find(to.first) == used.end()) {
            x_cords.push_back(to.first);
            used.insert(to.first);
        }
        if (columns.find(to.first) == columns.end()) {
            columns[to.first] = {};
        }
        columns[to.first].push_back(to.second);
    }
    sort(x_cords.begin(), x_cords.end());
    // cout << "x_cords = " << x_cords << "\n";
    for (auto& to : columns) {
        sort(to.second.begin(), to.second.end());
    }
    int sz = (int) x_cords.size();
    tree.resize(4 * sz);
    build(1, 0, sz);
    // print(tree);
    // for (auto to : columns) {
    //     cout << to.first << ": " << to.second << "\n";
    // }
    // cout << "\n";
    
    for (auto quest : quests) {
        int l = -1;
        int r = 1e7;
        while (r - l > 1) {
            // cout << l << " " << r << "\n";
            int m = (l + r) / 2;
            int l_val = max(0, a[quest.first - 1].first - m);
            int ql = lower_bound(x_cords.begin(), x_cords.end(), l_val) - x_cords.begin();
            int r_val = min(2 * mx, a[quest.first - 1].first + m);
            int qr = upper_bound(x_cords.begin(), x_cords.end(), r_val) - x_cords.begin() - 1;
            int mn_val = max(0, a[quest.first - 1].second - m);
            int mx_val = min(2 * mx, a[quest.first - 1].second + m);
            auto res = get(1, 0, sz, ql, qr + 1);
            // cout << "dist: " << m << " = " << res.y << ", " << mn_val << ":" << mx_val << ", " << ql << ":" << qr << ", " << res.calc(mn_val, mx_val) << "\n";
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