#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct node {
    long long mn_x, mx_x;
    long long mn_y, mx_y;
    node(): mn_x{0}, mx_x{0}, mn_y{0}, mx_y{0} {};
    node(long long mn_x, long long mx_x, long long mn_y, long long mx_y): 
    mn_x{mn_x}, mx_x{mx_x}, mn_y{mn_y}, mx_y{mx_y} {};
};

ostream& operator<< (ostream& stream, const node& a) {
    stream << "{" << a.mn_x << ", " << a.mx_x << ", " << a.mn_y << ", " << a.mx_y << "}";
    return stream;
}

int n, m;
map<long long, long long> p;
map<long long, node> info;
map<long long, int> sz;
vector<pair<int, int>> moves = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 0}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

bool in_bord(long long x, long long y) {
    return (x >= 1 && x <= n && y >= 1 && y <= m);
}

node merge(node a, node b) {
    return node(min(a.mn_x, b.mn_x), max(a.mx_x, b.mx_x), min(a.mn_y, b.mn_y), max(a.mx_y, b.mx_y));
}

long long get(long long x) {
    if (p[x] == x) {
        return x;
    }
    return p[x] = get(p[x]);
}

bool check(long long a) {
    if (info[a].mn_x == 1 && info[a].mn_y == 1) {
        return true;
    }
    if (info[a].mx_x == n && info[a].mx_y == m) {
        return true;
    }
    if (info[a].mn_x == 1 && info[a].mx_x == n) {
        return true;
    }
    if (info[a].mn_y == 1 && info[a].mx_y == m) {
        return true;
    }
    return false;
}

void unite(long long a, long long b) {
    if (get(a) == get(b)) {
        return;
    }
    a = get(a);
    b = get(b);
    if (sz[a] < sz[b]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    p[b] = a;
    info[a] = merge(info[a], info[b]);
    
}

void print() {
    for (auto to : info) {
        cout << to.first / m << ", " << to.first % m << ": " << to.second << "\n";
    }
    cout << "\n";
}

bool state = false;

int main() {
    cin >> n >> m;
    int k;
    cin >> k;
    while (k--) {
        long long x, y;
        cin >> x >> y;
        long long val = x * m + y;
        p[val] = val;
        sz[val] = 1;
        info[val] = node(x, x, y, y);
        for (auto to : moves) {
            pair<long long, long long> next = {x + to.first, y + to.second};
            if (in_bord(next.first, next.second)) {
                long long next_val = next.first * m + next.second;
                if (info.find(next_val) == info.end()) {
                    continue;
                }
                unite(val, next_val);
            }
        }
        // print();
        state = state | check(get(val));
        if (state) {
            cout << "Defeat!\n";
        } else {
            cout << "Success!\n";
        }
    }
}