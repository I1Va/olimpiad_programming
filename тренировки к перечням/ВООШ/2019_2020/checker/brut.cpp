#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

ostream& operator<< (ostream& stream, const pair<int, int>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream;
}

int n, q;
vector<pair<int, int>> a, quests;

int get1_2(int u, int d) {
    int res = 0;
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

bool state3() {
    int mx = 0;
    for (auto to : a) {
        mx = max(max(abs(to.first), abs(to.second)), mx);
    }
    return mx * mx <= 1e7;
}

int get3(int u, int d, const vector<vector<int>>& field) {
    int res = 0;
    for (int x = a[u].first - d; x <= a[u].first + d; x++) {
        for (int y = a[u].second - d; y <= a[u].second + d; y++) {
            res++;
        }
    }
    return res;
}

void solve3() {
    int mx = 2000;
    vector<vector<int>> field(2 * mx + 1, vector<int>(2 * mx + 1));
    for (auto& to : a) {
        to = {to.first + to.second + mx, to.first - to.second + mx};
    }
    for (auto to : a) {
        field[to.first][to.second] = 1;
    }
    for (auto quest : quests) {
        int l = -1;
        int r = 1e8;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (get3(quest.first - 1, m, field) - 1 < quest.second) {
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
    solve1_2();
}