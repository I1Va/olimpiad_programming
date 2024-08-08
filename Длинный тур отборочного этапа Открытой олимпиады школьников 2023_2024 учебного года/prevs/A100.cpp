#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

ostream& operator<< (ostream& stream, const pair<int, int>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream;
}

ostream& operator<< (ostream& stream, const vector<pair<int, int>>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

int n, m;

bool comp(const pair<int, int>& a, const pair<int, int>& b) {
    return a.first < b.first;
}

void add(int l, int r, vector<pair<int, int>>& pool) {
    if (l < m && r < m) {
        pool.push_back({l % m, r % m});
        return;
    }
    if (l < m && r >= m) {
        pool.push_back({l % m, m - 1});
        pool.push_back({0, min(2 * m - 1, r) % m});
        return;
    }
    if (l >= m && r >= m) {
        add(l - l / m * m, r - l / m * m, pool);
        return;
    }
}

int main() {
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<pair<int, int>> pool;

    for (int i = 1; i < n; i++) {
        if (a[i] - a[i - 1] > m) {
            add(a[i - 1] + 1, a[i] - m, pool);
        }
    }
    sort(pool.begin(), pool.end(), comp);
    // cout << "pool = " << pool << "\n";
    if (pool.empty()) {
        cout << 0;
        return 0;
    }
    pair<int, int> cur = pool[0];
    if (cur.first > 0) {
        cout << 0;
        return 0;
    }
    int sz = (int) pool.size();
    for (int i = 1; i < sz; i++) {
        if (pool[i].first - cur.second > 1) {
            cout << cur.second + 1;
            return 0;
        }
        if (pool[i].second > cur.second) {
            cur = pool[i];
        }
    }
    // cout << "cur = " << cur << "\n";
    if (cur.second + 1 < m) {
        cout << cur.second + 1;
    } else {
        cout << -1;
    }
    
}
