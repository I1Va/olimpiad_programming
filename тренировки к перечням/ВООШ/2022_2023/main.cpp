#pragma GCC optimaze("Ofast")
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

struct node {
    int x, y;
    bool s;
    node(int x, int y, bool s): x{x}, y{y}, s{s} {};
    node(): x{-1}, y{-1}, s{0} {};
};

struct point {
    int x, y;
    point(int x, int y): x{x}, y{y} {};
};

ostream& operator<< (ostream& stream, const node& a) {
    stream << "{" << a.x << ", " << a.y << ", " << a.s << "}";
    return stream;
}

ostream& operator<< (ostream& stream, const point& a) {
    stream << "{" << a.x << ", " << a.y << "}";
    return stream;
}

ostream& operator<< (ostream& stream, queue<pair<point, int>> q) {
    while (q.size()) {
        cout << "{" << q.front().first << ", " << q.front().second << "} "; 
        q.pop();
    }
    return stream;
}

ostream& operator<< (ostream& stream, const vector<node>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}



const long double EPS = 1.0 / 1e9;
int W, H, n, K, P, L;
int xo, yo;

long double dist(long long x1, long long y1, long long x2, long long y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

bool check(long double d, vector<node> a) {
    queue<pair<point, long double>> q;
    q.push({point(xo, yo), d});
    int c = 0;
    bool extra = true;
    while (q.size()) {
        auto cur = q.front();
        q.pop();
        for (int i = 0; i < n; i++) {
            long double R = dist(a[i].x, a[i].y, cur.first.x, cur.first.y);
            // cout << "try: " << a[i] << " -> ";
            // cout << "cur_power = " << cur.second << ", dist = " << R * K << ", remain_power = " << cur.second - R * K << ", success: " << (cur.second - R * K >= P) << "\n";
            if (cur.second - R * K >= P) {
                if (a[i].s) {
                    if (cur.first.x == xo && cur.first.y == yo) {
                        q.push({point(a[i].x, a[i].y), L});
                    }
                } else {
                    a[i].s = true;
                }
            }
        }
    }
    for (auto to : a) {
        if (!to.s) {
            return false;
        }
    }
    return true;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> W >> H >> n >> K >> P >> L;
    cin >> xo >> yo;
    vector<node> a(n);
    for (int i = 0; i < n; i++) {
        int x, y, s;
        cin >> x >> y >> s;
        a[i] = node(x, y, (bool) s);
    }
    long double l = 0;
    long double r = 1e5;
    while (r - l > EPS) {
        long double m = (l + r) / 2.0;
        // cout << l << " " << r << "\n";
        if (check(m, a)) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << fixed << setprecision(14) << (l + r) / 2.0;
}