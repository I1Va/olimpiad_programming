#include <iostream>
#include <vector>
#include <map>
using namespace std;

map<char, pair<int, int>> moves;

ostream& operator<< (ostream& stream, const pair<int, int>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream;
}

pair<int, int> operator+ (pair<int, int> a, pair<int, int> b) {
    return {a.first + b.first, a.second + b.second};
}

void operator+= (pair<int, int>& a, pair<int, int> b) {
    a = {a.first + b.first, a.second + b.second};
}

void operator-= (pair<int, int>& a, pair<int, int> b) {
    a = {a.first + b.first, a.second + b.second};
}

bool out_of_border(const pair<int, int>& cur, const int& n, const int& m) {
    return !(cur.first >= 0 && cur.first < n && cur.second >= 0 && cur.second < m);
}

void build() {
    moves['R'] = {0, 1};
    moves['L'] = {0, -1};
    moves['U'] = {-1, 0};
    moves['D'] = {1, 0};
}

struct node {
    map<char, pair<int, int>> next;
    map<char, int> cnt;
    node(int x, int y) {
        next['R'] = {x, y};
        next['L'] = {x, y};
        next['U'] = {x, y};
        next['D'] = {x, y};
        cnt['R'] = 0;
        cnt['L'] = 0;
        cnt['U'] = 0;
        cnt['D'] = 0;
    }
};

void solve() {
    build();
    int n, m, d;
    cin >> n >> m >> d;
    vector<vector<char>> a(n, vector<char>(m));
    pair<int, int> cur;
    vector<vector<node>> p(n, vector<node>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            p[i][j] = node(i, j);
            if (a[i][j] == 'S') {
                cur = {i, j};
                a[i][j] = '.';
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        p[i][0].next['L'] = {i, 0};
        p[i][0].cnt['L'] = 0;
        for (int j = 1; j < m; j++) {
            if (a[i][j - 1] != '#' && a[i][j -1] != 'L') {
                p[i][j].next['L'] = p[i][j - 1].next['L'];
                p[i][j].cnt['L'] = p[i][j - 1].cnt['L'];
            }
        }
    }
    
    int q;
    cin >> q;
    int keys = 0;
    vector<vector<bool>> used(n, vector<bool>(m, false));
    while (q--) {
        char t;
        cin >> t;
        int c = 0;
        auto move = p[cur.first][cur.second];
        while (1) {
            if (a[cur.first + move.first][cur.second + move.second] == 'K') {
                cur += move;
                if (!used[cur.first][cur.second]) {
                    keys++;
                    used[cur.first][cur.second] = true;
                }
                
                c++;
                continue;
            }
            if (a[cur.first + move.first][cur.second + move.second] == 'L') {
                if (keys > 0 && !used[cur.first + move.first][cur.second + move.second]) {
                    keys--;
                    used[cur.first + move.first][cur.second + move.second] = true;
                }
                if (used[cur.first + move.first][cur.second + move.second]) {
                    cur += moves[t];
                    c++;
                } else {
                    break;
                }
            }
        }
        // cout << cur << ":" << c << "\n";
        cout << c << "\n";
    }
}

int main() {
    solve();
}