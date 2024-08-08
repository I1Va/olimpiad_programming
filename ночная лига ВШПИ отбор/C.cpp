#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct point {
    int i, j;
    point(): i{0}, j{0} {}
    point(int i, int j): i{i}, j{j} {}
};

ostream& operator<< (ostream& stream, const point& a) {
    cout << "{" << a.i << ", " << a.j << "}";
    return stream;
}

struct star {
    int i, j, r, t;
    star(): i{0}, j{0}, r{0}, t{0} {}
    star(int i, int j, int r, int t): i{i}, j{j}, r{r}, t{t} {}
};

int q, n, s;
vector<star> stars;
point fir, sec;

ostream& operator<< (ostream& stream, const set<pair<int, int>>& a) {
    for (auto to : a) {
        cout << "{" << to.first << ", " << point(to.second / n, to.second % n) << "} ";
    }
    return stream;
}

bool state1() {
    return q == 1;
}

void color(vector<vector<bool>>& a, star x) {
    for (int i = max(0, x.i - 10); i <= min(n - 1, x.i + 10); i++) {
        for (int j = max(0, x.j - 10); j <= min(n - 1, x.j + 10); j++) {
            if (abs(i - x.i) + abs(j - x.j) <= x.t) {
                a[i][j] = true;
            }
        }
    }
}

int get() {
    vector<vector<bool>> a(n, vector<bool>(n, false));
    for (int i = 0; i < s; i++) {
        color(a, stars[i]);
    }
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += a[i][j];
        }
    }
    return sum;
}

void solve1() {
    int mx = 0;
    for (int i = 0; i <= 100; i++) {
        mx = max(mx, get());
        for (int j = 0; j < s; j++) {
            stars[j].t = (stars[j].t + 1) % (stars[j].r);
        }
    }
    cout << mx << "\n";
}

bool state2() {
    if (q != 2) {
        return false;
    }
    for (auto x : stars) {
        if (x.r != 1) {
            return false;
        }
    }
    return true;
}

void solve2() {
    int INF = 1e9;
    vector<pair<int, int>> moves = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
    vector<vector<bool>> used(n, vector<bool>(n, false));
    vector<vector<int>> dist(n, vector<int>(n, INF));
    for (auto x : stars) {
        used[x.i][x.j] = true;
    }
    set<pair<int, int>> q;
    q.insert({0, fir.i * n + fir.j});
    dist[fir.i][fir.j] = 0;
    while (q.size()) {
        int val = q.begin() -> second;
        point cur = point(val / n, val % n);
        // cout << "cur = " << cur << "\n";
        q.erase(q.begin());
        for (auto move : moves) {
            point to = point(cur.i + move.first, cur.j + move.second);
            if (to.i < 0 || to.i >= n || to.j < 0 || to.j >= n) {
                continue;
            }
            
            // cout << "to = " << to << "\n";
            if (!used[to.i][to.j] && dist[to.i][to.j] > dist[cur.i][cur.j] + 1) {
                q.erase({dist[to.i][to.j], to.i * n + to.j});
                dist[to.i][to.j] = dist[cur.i][cur.j] + 1;
                q.insert({dist[to.i][to.j], to.i * n + to.j});
            }
        }
        // cout << "q = " << q << "\n";
    }
    cout << dist[sec.i][sec.j];
}

int main() {
    cin >> q >> n >> s;
    stars.resize(s);
    for (int i = 0; i < s; i++) {
        int x, y, r, t;
        cin >> x >> y >> r >> t;
        stars[i] = star(n - y, x - 1, r, t);
    } 
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    fir = point(n - y1, x1 - 1);
    sec = point(n - y2, x2 - 1);
    if (state1()) {
        solve1();
    } else if (state2()) {
        solve2();
    }
}