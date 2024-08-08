#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct node {
    int val;
    int push;
    node(int val, int push): val{val}, push{push} {}
};

struct point {
    bool dot;
    bool red;
    int x;
    int y1, y2;
    int num;
    int ord;
    point(bool dot, bool red, int x, int y1, int y2, int num, int ord): dot{dot}, red{red}, x{x}, y1{y1}, y2{y2}, num{num}, ord{ord} {}
};

ostream& operator<< (ostream& stream, const point& a) {
    stream << "{dot = " << a.dot << ", red = " << a.red << ", x = " << a.x << ", y1 = ";
    stream << a.y1 << ", y2 = " << a.y2 << ", num = " << a.num << "}";
    return stream;
}

bool comp(const point& a, const point& b) {
    if (a.x == b.x) {
        return a.ord < b.ord;
    }
    return a.x < b.x;
}

int n, m;
const int maxn = 1e5;
unordered_map<int, int> cord_num;
vector<node> tree;

node merge(const node& a, const node& b) {
    return node(a.val + b.val, 0);
}

void push(int ver) {
    int delta = tree[ver].push;
    tree[ver * 2].val += delta;
    tree[ver * 2].push += delta;
    tree[ver * 2 + 1].val += delta;
    tree[ver * 2 + 1].push += delta;
    tree[ver].push = 0;
}

void update(int ver, int l, int r, int ql, int qr, int x) {
    if (l >= qr || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        tree[ver].val += x;
        tree[ver].push += x;
        return;
    }
    push(ver);
    int m = (l + r) / 2;
    update(ver * 2, l, m, ql, qr, x);
    update(ver * 2 + 1, m, r, ql, qr, x);
    tree[ver] = merge(tree[ver * 2], tree[ver * 2 + 1]);
}

node get(int ver, int l, int r, int ql, int qr) {
    if (l >= qr || r <= ql) {
        return node(0, 0);
    }
    if (ql <= l && r <= qr) {
        return tree[ver];
    }
    push(ver);
    int m = (l + r) / 2;
    return merge(get(ver * 2, l, m, ql, qr), get(ver * 2 + 1, m, r, ql, qr));
}

int compress(vector<int>& cords) {
    sort(cords.begin(), cords.end());
    cords.erase(unique(cords.begin(), cords.end()), cords.end());
    int num = 0;
    for (auto& to : cords) {
        cord_num[to] = num++;
    }
    return num;
}

int main() {
    cin >> n >> m;
    vector<point> a;
    vector<int> cords;
    a.reserve(3 * maxn);
    cords.reserve(3 * maxn);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a.push_back(point(true, false, x, y, y, -1, 1));
        cords.push_back(y);
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        a.push_back(point(false, true, x2, y1, y2, i, 2));
        a.push_back(point(false, false, x1, y1, y2, i, 0));
        cords.push_back(y1);
        cords.push_back(y2);
    }
    int num = compress(cords);
    sort(a.begin(), a.end(), comp);
    for (auto& to : a) {
        to.y1 = cord_num[to.y1];
        to.y2 = cord_num[to.y2];
    }
    /*cout << "num = " << num << "\n";
    for (auto to : cord_num) {
        cout << to.first << ": " << to.second << "\n";
    }*/
    // num - размер оси oy
    vector<int> ans(m, 0);
    tree.resize(4 * num + 1, node(0, 0));
    for (const auto& ev : a) {
        // cout << ev << "\n";
        if (ev.dot) {
            update(1, 0, num, ev.y1, ev.y1 + 1, 1); // Хз лол ДО без массовых операций что ли?
        } else {
            if (ev.red) {
                ans[ev.num] += get(1, 0, num, ev.y1, ev.y2 + 1).val;
            } else {
                ans[ev.num] -= get(1, 0, num, ev.y1, ev.y2 + 1).val;
            }
        }
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << "\n";
    }
}