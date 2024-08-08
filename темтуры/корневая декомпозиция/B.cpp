#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

ostream& operator<< (ostream& stream, const pair<int, int>& a) {
    stream << "{" << a.first << " " << a.second << "}";
    return stream;
}

const int INF = 1e9 + 7;

struct block {
    vector<int> a;
    int sz;
    int mn;
    block(): sz{0}, mn{INF} {};
    block(int x): a{{x}}, sz{1}, mn{x} {};
    block(vector<int> a, int sz): a{a}, sz{sz} {};
    void insert(int idx, int x) {
        mn = min(mn, x);
        a.insert(a.begin() + idx, x);
        sz++;
    }
};

vector<block> blocks;
const int operations_border = 333;
int operations = 1;
const bool deb = 0;

void print_blocks() {
    if (!deb) {
        return;
    }
    for (int i = 0; i < (int) blocks.size(); i++) {
        cout << blocks[i].a;
        if (i != (int) blocks.size() - 1) {
            cout << "| ";
        } else {
            cout << "\n";
        }
    }
}

void insert(int idx, int x) {
    operations++;
    int cur = 0;
    while (1) {
        if (cur == (int) blocks.size()) {
            blocks.emplace_back(x);
            return;
        }
        // cout << "cur = " << cur << ", idx = " << idx << ", sz = " << blocks[cur].sz << "\n";
        if (idx - blocks[cur].sz >= 0) {
            idx -= blocks[cur].sz;
            cur++;
        } else {
            // cout << "insertion: " << idx << "\n";
            blocks[cur].insert(idx, x);
            return;
        }
    }
}

pair<int, int> find_idx(int idx) {
    int cur = 0;
    while (1) {
        if (idx - blocks[cur].sz >= 0) {
            idx -= blocks[cur].sz;
        } else {
            return {cur, idx};
        }
        cur++;
    }
}

int get(int f, int s) {
    auto l = find_idx(f);
    auto r = find_idx(s);
    // cout << l << " " << r << "\n";
    int mn = INF;
    for (int i = l.second; i < min(s + 1 - (f - l.second), blocks[l.first].sz); i++) {
        mn = min(mn, blocks[l.first].a[i]); // Обработка правой неполной границы
    }
    // cout << "leftmn: " << mn << "\n";
    for (int i = l.first + 1; i < r.first; i++) {
        mn = min(mn, blocks[i].mn); // Обработка целых блоков по середине
    }
    // cout << "midmn: " << mn << "\n";
    if (l.first != r.first) {
        for (int i = 0; i <= r.second; i++) {
            mn = min(mn, blocks[r.first].a[i]);
        }
    }
    // cout << "rightmn: " << mn << "\n";
    return mn;
}

void rebuild() {
    vector<int> a;
    a.reserve(operations);
    for (auto to : blocks) {
        for (auto x : to.a) {
            a.push_back(x);
        }
    }
    int sz = (int) a.size();
    blocks.clear();
    int k = sqrt(sz);
    blocks.resize((sz + k - 1) / k);
    for (int i = 0; i < sz; i++) {
        blocks[i / k].insert(blocks[i / k].sz, a[i]);
    }
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        char t;
        int i, j;
        if (operations % operations_border == 0) {
            rebuild();
        }
        cin >> t >> i >> j;
        if (t == '+') {
            insert(i, j);
        } else {
            cout << get(i - 1, j - 1) << "\n";
        }
        print_blocks();
    }
}
