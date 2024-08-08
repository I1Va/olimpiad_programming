#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;

const long double pi = acos(-1);
const long double EPS = 1.0l / 1e10;
const int deb = 0;

struct ir_dot {
    long double x, y;
    ir_dot(long double x, long double y): x{x}, y{y} {}
};

struct dot {
    long long x, y;
    dot(): x{0}, y{0} {}
    dot(long long x, long long y): x{x}, y{y} {}
    ir_dot to_irdot() {
        return ir_dot(x, y);
    }
    bool operator== (dot b) {
        return x == b.x && y == b.y;
    }
};

long double dist(dot A, ir_dot B) {
    return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}

long double dist(dot a, dot b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

istream& operator>> (istream& stream, dot& a) {
    long long x, y;
    stream >> x >> y;
    a = dot(x, y);
    return stream;
}

struct point {
    long long x, y;
    point(dot a, dot b): x{b.x - a.x}, y{b.y - a.y} {}
    long long operator* (point S) {
        return x * S.x + y * S.y;
    }
};

struct ir_point {
    long double x, y;
    ir_point(dot a, dot b): x{(long double) b.x - a.x}, y{(long double) b.y - a.y} {}
    ir_point(long double x, long double y): x{x}, y{y} {}
    void rot(long double f) {
        long double n_x = x * cos(f) - y * sin(f);
        long double n_y = y * cos(f) + x * sin(f);
        x = n_x;
        y = n_y;
    }
    ir_point normalize() {
        long double l = len();
        return ir_point(x / l, y / l);
    }
    ir_point mul(long double k) {
        return ir_point(x * k, y * k);
    }
    long double pol_ang() {
        long double ang = atan2(y, x);
        if (ang < 0) {
            ang += 2 * pi;
        }
        return ang;
    }
    ir_point operator+ (dot a) {
        return ir_point(x + a.x, y + a.y);
    }
    long double len() {
        return sqrt(x * x + y * y);
    }
    long double operator* (ir_point S) {
        return x * S.x + y * S.y;
    }
    long double operator% (ir_point S) {
        return x * S.y - S.x * y;
    }
    ir_point operator+ (ir_point S) {
        return ir_point(x + S.x, y + S.y);
    }
    ir_dot to_irdot() {
        return ir_dot(x, y);
    }
    void print(string name) {
        if (!deb) {
            return;
        }
        cout << name << ":{" << x << " " << y << "}\n";
    }
};

struct ir_line {
    long double a, b, c;
    const int precision = 10;
    ir_line(ir_dot F, ir_dot S): a{S.y - F.y}, b{F.x - S.x}, c{S.x * F.y - F.x * S.y} {}
    void print_par() {
        cout << fixed << setprecision(precision) << a << " " << b << " " << c;
    }
};

struct line {
    long long a, b, c;
    const int precision = 10;
    line(dot F, dot S): a{S.y - F.y}, b{F.x - S.x}, c{S.x * F.y - F.x * S.y} {}
    line(long long a, long long b, long long c): a{a}, b{b}, c{c} {}
    void print_par() {
        cout << fixed << setprecision(precision) << a << " " << b << " " << c;
    }
    long double dist(dot Q) {
        return abs(a * Q.x + b * Q.y + c) / sqrt(a * a + b * b);
    }
    bool on_line(ir_dot Q) {
        return abs(Q.x * a + Q.y * b + c) <= EPS;
    }
    bool on_line(dot Q) {
        return Q.x * a + Q.y * b + c == 0;
    }
    ir_dot per_base(dot Q) {
        ir_point n(a, b);
        long double d = dist(Q);
        n.print("n");
        n = n.normalize();
        n.print("n_norm");
        n = n.mul(d);
        n.print("resized_n");
        // cout << "d = " << d << "\n";
        // Откладываем вектора нормалей от точки Q
        if (on_line((n + Q).to_irdot())) {
            return (n + Q).to_irdot();
        }
        if (on_line((n.mul(-1) + Q).to_irdot())) {
            return (n.mul(-1) + Q).to_irdot();
        }
        cout << "PERP NOT FOUND";
        exit(1);
    }
};

ir_dot inter(line F, line S) {
    long double x = (long double) (S.c * F.b - F.c * S.b) / (S.b * F.a - F.b * S.a);
    long double y = (long double) (F.c * S.a - S.c * F.a) / (S.b * F.a - F.b * S.a);
    return ir_dot(x, y);
}

struct seg {
    long long x1, x2, y1, y2;
    seg(dot A, dot B): x1{A.x}, x2{B.x}, y1{A.y}, y2{B.y} {}
    bool on_seg(ir_dot Q) {
        if (line(dot(x1, y1), dot(x2, y2)).on_line(Q)) {
            if (Q.x >= min(x1, x2) && Q.x <= max(x1, x2) && Q.y >= min(y1, y2) && Q.y <= max(y1, y2)) {
                return true;
            }
        }
        return false;
    }
};

ostream& operator<< (ostream& stream, const ir_point& a) {
    stream << "{" << a.x << ", " << a.y << "}";
    return stream;
}

long double ang(ir_point a, ir_point b) {
    if (b.pol_ang() >= a.pol_ang()) {
        return b.pol_ang() - a.pol_ang();
    }
    return b.pol_ang() - a.pol_ang() + 2 * pi;
}

long double f(long double x, long double k, long long b, dot A, dot B) {
    ir_dot X(x, k * x + b);
    return dist(A, X) + dist(B, X);
}

int main() {
    dot A, B;
    long double k;
    long long b;
    cin >> A >> B;
    cin >> k >> b;
    if (A == B) {
        exit(1);
    }
    line L(k, -1, b);
    if (seg(A, B).on_seg(inter(line(A, B), L))) { // Река проходит между монастырями
        cout << "No solution.";
        return 0;
    }
    // Потернарим по x
    long double left = -100000.0l;
    long double right = 100000.0l;
    while (right - left > EPS) {
        long double m1 = left + (right - left) / 3;
        long double m2 = right - (right - left) / 3;
        if (f(m1, k, b, A, B) > f(m2, k, b, A, B)) {
            left = m1;
        } else {
            right = m2;
        }
    }
    cout << fixed << setprecision(8) << f((left + right) / 2, k, b, A, B);
}