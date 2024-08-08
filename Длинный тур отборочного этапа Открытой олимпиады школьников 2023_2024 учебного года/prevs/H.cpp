#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct dot {
    long long x, y;
    dot(): x{0}, y{0} {}
    dot(long long _x, long long _y): x{_x}, y{_y} {}
};

struct quest {
    char c;
    dot a;
    quest(): c{'-'}, a{dot(0, 0)} {}
    quest(char c, dot a): c{c}, a{a} {}
};

bool orient_left(dot a, dot b, dot c) {
    long long l = (b.x - a.x) * (c.y - a.y);
    long long r = (b.y - a.y) * (c.x - a.x);
    long long res = l - r;
    if (res > 0) {
        return true;
    } else {
        return false;
    }
}

istream &operator>>(istream &in, dot &a) {
    long long x1, y1;
    in >> x1 >> y1;
    a = dot(x1, y1);
    return in;
}

struct line {
    long long a, b, c;
    line(long long _a, long long _b, long long _c): a{_a}, b{_b}, c{_c} {}
    line(dot F, dot S): a{S.y - F.y}, b{F.x - S.x}, c{S.x * F.y - F.x * S.y} {}
    long double dist(dot Q) {
        return (long double) abs(a * Q.x + b * Q.y + c) / sqrt(a * a + b * b);
    }
    bool on_line(dot Q) {
        return (a * Q.x + b * Q.y + c == 0);
    }
};

struct point {
    long long x, y;
    point(dot a, dot b): x{b.x - a.x}, y{b.y - a.y} {}
    point(): x{0}, y{0} {}
    long long len_2() {
        return x * x + y * y;
    }
    long long operator* (point b) {
        return x * b.x + y * b.y;
    }
};

struct seg {
    long long x1, x2, y1, y2;
    seg(dot a, dot b): x1{a.x}, x2{b.x}, y1{a.y}, y2{b.y} {}
    bool on_seg(dot Q) {
        if (line(dot(x1, y1), dot(x2, y2)).on_line(Q)) {
            if (Q.x >= min(x1, x2) && Q.x <= max(x1, x2) && Q.y >= min(y1, y2) && Q.y <= max(y1, y2)) {
                return true;
            }
        }
        return false;
    }
};

void inter(line Q, line P) {
    long double y = (long double) (Q.c * P.a - P.c * Q.a) / (long double) (P.b * Q.a - P.a * Q.b);
    long double x = (long double) (Q.b * P.c - Q.c * P.b) / (long double) (P.b * Q.a - Q.b * P.a);
    cout << x << " " << y;
}

bool dot_inside_polygon(dot q, vector<dot> dots) {
    int cnt = 0;
    for (int i = 1; i < (int) dots.size(); i++) {
        dot a = dots[i - 1];
        dot b = dots[i];
        if (a.y > b.y) {
            swap(a, b);
        }
        if (line(a, b).on_line(q)) {
            return true;
        }
        if (a.y == b.y) {
            continue;
        }
        if (q.y == a.y) {
            continue;
        }
        if (q.y == b.y && q.x < min(a.x, b.x)) {
            cnt++;
        }
        if (q.y > a.y && q.y < b.y && orient_left(a, b, q)) {
            cnt++;
        }
    }
    return cnt % 2;
}



int n, m, q;
dot C;
vector<dot> polygon;
vector<quest> quests;

unordered_map<int, unordered_set<int>> specials;

bool dot_inside_polygon2(dot q, int mask) {
    int cnt = 0;
    for (int i = 1; i < n; i++) {
        dot a, b;
        if ((mask >> (i - 1)) & 1) {
            a = C;
        }
        if ((mask >> i) & 1) {
            b = C;
        }
        if (a.y > b.y) {
            swap(a, b);
        }
        if (line(a, b).on_line(q)) {
            return true;
        }
        if (a.y == b.y) {
            continue;
        }
        if (q.y == a.y) {
            continue;
        }
        if (q.y == b.y && q.x < min(a.x, b.x)) {
            cnt++;
        }
        if (q.y > a.y && q.y < b.y && orient_left(a, b, q)) {
            cnt++;
        }
    }
    return cnt % 2;
}

bool state1() {
    return n == 3 && m <= 3 && q == 0;
}

int get(const vector<dot>& polygon) {
    int res = 0;
    for (auto to : specials) {
        for (auto y : to.second) {
            if (dot_inside_polygon(dot(to.first, y), polygon)) {
                res++;
            }
        }
    }
    return res;
}

bool rec(vector<dot> polygon) {
    int cnt = get(polygon);
    bool lose = true;
    for (int i = 0; i < n; i++) {
        dot prev = polygon[i];
        polygon[i] = C;
        if (get(polygon) < cnt) {
            lose = false;
            lose &= !rec(polygon); // Можем сходить. Смотрим где проиграет след. игрок
        }
        polygon[i] = prev;
    }
    return lose;
}

void solve1() {
    if (!rec(polygon)) {
        cout << "Alice";
    } else {
        cout << "Bob";
    }
}

int get2(int mask) {
    int res = 0;
    for (auto to : specials) {
        for (auto y : to.second) {
            if (dot_inside_polygon2(dot(to.first, y), mask)) {
                res++;
            }
        }
    }
    return res;
}

bool rec2(int mask, vector<int>& states) {
    int cnt = get2(mask);
    bool lose = true;
    for (int i = 0; i < n; i++) {
        if ((mask >> i) & 1) {
            continue;
        }
        int prev = mask;
        mask |= (1 << i);
        if (get2(mask) < cnt) {
            lose = false;
            if (states[mask] == -1) {
                lose &= !rec2(mask, states); // Можем сходить. Смотрим где проиграет след. игрок
            } else {
                lose &= states[mask];
            }
            
        }
        mask = prev;
    }
    states[mask] = lose;
    return lose;
}

void ans(vector<int>& states) {
    if (!rec2(0, states)) {
        cout << "Alice\n";
    } else {
        cout << "Bob\n";
    }
}

void solve2() {
    vector<int> states(1 << n, -1);
    ans(states);
    for (int i = 0; i < q; i++) {
        vector<int> states(1 << n, -1);
        if (quests[i].c == '+') {
            specials[quests[i].a.x].insert(quests[i].a.y);
        } else {
            specials[quests[i].a.x].erase(quests[i].a.y);
        }
        ans(states);
    }
}

int main() {
    cin >> n >> m >> q;
    cin >> C;
    polygon.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> polygon[i];
    }
    for (int i = 0; i < m; i++) {
        dot Q;
        cin >> Q;
        specials[Q.x].insert(Q.y);
    }
    quests.resize(q);
    for (int i = 0; i < q; i++) {
        cin >> quests[i].c >> quests[i].a;
    }
    if (state1) {
        solve1();
    } else {
        solve2();
    }
}