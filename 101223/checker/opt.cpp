#include <iostream>
#include <vector>
#include <iomanip>
#include <numeric>
using namespace std;

const long long EPS = 1.0l / 1e7;

struct dot {
    long long x, y;
    dot(): x{0}, y{0} {}
    dot(long long x, long long y): x{x}, y{y} {}
};

istream& operator>> (istream& in, dot& a) {
    long long x, y;
    in >> x >> y;
    a = dot(x, y);
    return in;
}

ostream& operator<< (ostream& stream, const dot& a) {
    stream << a.x << " " << a.y;
    return stream;
}

struct point {
    long long x1, x2, y1, y2;
    long long x, y;
    long long a, b, c;
    point(dot F, dot S):
        x1{F.x}, x2{S.x}, y1{F.y}, y2{S.y}, x{S.x - F.x}, y{S.y - F.y},
        a{F.y - S.y}, b{S.x - F.x}, c{F.x * S.y - S.x * F.y} {}
    long long operator% (point S) {
        return x * S.y - S.x * y;
    }
    bool is_dot() {
        return (x1 == x2) && (y1 == y2);
    }
    bool operator || (point b) {
        return x * b.y == y * b.x;
    }
    bool operator == (point b) {
        return (x1 == b.x1 && x2 == b.x2 && y1 == b.y1 && y2 == b.y2);
    }
    bool on_seg(dot Q) {
        if (Q.x * a + Q.y * b + c == 0) {
            return (Q.x >= min(x1, x2) && Q.x <= max(x1, x2)) && (Q.y >= min(y1, y2) && Q.y <= max(y1, y2));
        }
        return false;
    }
    dot to_dot() {
        return dot(x1, y1);
    }
    void print_par() {
        cout << "{" << a << ", " << b << ", " << c << "}";
    }
};

ostream& operator<< (ostream& stream, const point& a) {
    stream << a.x << " " << a.y;
    return stream;
}

dot inter(point F, point S) {
    // cout << "F = " << F.a << ", " << F.b << ", " << F.c << ", S = " << S << "\n";
    long long x = (S.c * F.b - F.c * S.b) / (S.b * F.a - F.b * S.a);
    long long y = (F.c * S.a - S.c * F.a) / (S.b * F.a - F.b * S.a);
    // cout << dot(x, y) << "\n";
    return dot(x, y);
}

void change(dot& a, dot& b) {
    // a < b
    if (a.x == b.x) {
        if (a.y > b.y) {
            swap(a, b);
            return;
        }
    }
    if (a.x > b.x) {
        swap(a, b);
    }
}

void tc1(point a, point b) {
    if (a.x1 > b.x1) {
        swap(a, b);
    }
    if (b.x1 <= a.x2 && a.x2 <= b.x2) {
        // cout << b.x1 << " " << b.y1 << "\n" << a.x2 << " " << a.y2;
        cout << "YES";
    } else {
        cout << "NO";
    }
}

void solve() {
    dot A, B, C, D;
    cin >> A >> B >> C >> D;
    point AB(A, B), AC(A, C), AD(A, D), DC(D, C), DA(D, A), DB(D, B), CD(C, D);
    bool state = ((AB % AC) * (AB % AD)) < 0 && ((DC % DA) * (DC % DB)) < 0;
    // cout << "s1 = " << state << "\n";
    bool bug = false;
    if (AB.is_dot() && CD.is_dot()) {
        bool cur = (AB == CD);
        if (bug) {
            cout << "dot, dot: " << cur << "\n";
        }
        // cout << "s2 = " << state << "\n";
    }
    if ((AB.is_dot() && !CD.is_dot()) || (!AB.is_dot() && CD.is_dot())) {
        
        if (!AB.is_dot() && CD.is_dot()) {
            swap(AB, CD); // AB - точка
        }
        // cout << "dot: " << AB;
        bool cur = CD.on_seg(AB.to_dot());
        if (bug) {
            cout << "dot, line: " << cur << "\n";
        }
        state = state || cur;
    }
    if (!AB.is_dot() && !CD.is_dot()) {
        bool cur = (((AB % AC) * (AB % AD)) <= 0 && ((DC % DA) * (DC % DB)) <= 0);
        if (bug) {
            cout << "line, line: " << cur << "\n";
        }
        state = state || cur;
    }
    if (state) {
        cout << "YES";
        return;
    }
    cout << "NO";
}

int main() {
    solve();
}