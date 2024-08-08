#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;


struct node {
    int l, r;
    int num;
    node(int l, int r, int num): l{l}, r{r}, num{num} {};
};

bool comp(const node& a, const node& b) {
    return a.l < b.l;
}

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

ostream& operator<< (ostream& stream, const node& a) {
    stream << "{" << a.l << ", " << a.r << ", " << a.num << "}";
    return stream;
}

ostream& operator<< (ostream& stream, const vector<pair<int, int>>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

ostream& operator<< (ostream& stream, const vector<node>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

int find_seg(int x, const vector<node>& a) {
    int l = 0;
    int r = (int) a.size();
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (a[m].l <= x) {
            l = m;
        } else {
            r = m;
        }
    }
    if (a[l].l <= x && x <= a[l].r) {
        return a[l].num;
    }
    return -1;
}

int main() {
    int n, k, q;
    cin >> n >> k >> q;
    map<int, vector<node>> lines; // по y
    map<int, vector<node>> columns; // по x
    set<pair<int, int>> used;
    vector<int> cnt(k);
    for (int i = 0; i < k; i++) {
        int s1, s2, e1, e2;
        cin >> s1 >> s2 >> e1 >> e2;
        s1--, s2--, e1--, e2--;
        if (s1 == e1) { // Вертикальная мишень
            if (columns.find(s1) == columns.end()) {
                columns[s1] = {};
            }
            columns[s1].push_back(node(s2, e2, i));
        } else {
            if (lines.find(s2) == lines.end()) {
                lines[s2] = {};
            }
            lines[s2].push_back(node(s1, e1, i));
        }
        cnt[i] = (e1 - s1 + 1) * (e2 - s2 + 1);
    }
    for (auto& to : lines) {
        sort(to.second.begin(), to.second.end(), comp);
    }
    for (auto& to : columns) {
        sort(to.second.begin(), to.second.end(), comp);
    }
    // cout << "lines:\n";
    // for (auto to : lines) {
    //     cout << to.first << ": " << to.second << "\n";
    // }
    // cout << "\ncolumns:\n";
    // for (auto to : columns) {
    //     cout << to.first << ": " << to.second << "\n";
    // }
    // cout << "\n";
    while (q--) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        if (used.find(make_pair(x, y)) != used.end()) {
            cout << "REPEAT\n";
            continue;
        }
        int hit = -1;
        if (lines.find(y) != lines.end()) {
            int temp = find_seg(x, lines[y]);
            // cout << "line hit = " << temp << "\n";
            if (temp != -1) {
                hit = temp;
            }
            
            
        }
        if (columns.find(x) != columns.end()) {
            int temp = find_seg(y, columns[x]);
            // cout << "column hit = " << temp << "\n";
            if (temp != -1) {
                hit = temp;
            }

        }
        used.insert(make_pair(x, y));
        // cout << "hit = " << hit << "\n";
        if (hit == -1) {
            cout << "MISS\n";
        } else {
            cnt[hit]--;
            if (cnt[hit] == 0) {
                cout << "SINK\n";
            } else {
                cout << "HIT\n";
            }
        }
    }

}