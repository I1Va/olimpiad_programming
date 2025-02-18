#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct dot {
    long double x, y;
    dot(): x{0}, y{0} {};
    dot(long double x, long double y): x{x}, y{y} {};
};

ostream& operator<< (ostream& stream, const dot& A) {
    stream << "{" << A.x << ", " << A.y << "}";
    return stream;
}

struct line {
    dot A, B;
    long double k = 0, b = 0;
    bool vert;
    line(dot A, dot B) {
        A = A;
        B = B;
        vert = (A.x == B.x);
        if (!vert) {
            k = (A.y - B.y) / (A.x - B.x);
            b = (A.y - k * A.x);
        } 
    }
};

dot inter(line a, line b) {
    if (a.vert && b.vert) {
        cout << "WARNING! 2 verts\n";
        return dot(0, 0);
    }
    if (a.vert || b.vert) {
        if (b.vert) {
            swap(a, b);
        }
        long double x = a.A.x;
        long double y = b.k * x + b.b;
        return dot(x, y);
    }
    long double x = (b.b - a.b) / (a.k - b.k);
    long double y = a.k * x + a.b;
    return dot(x, y);
}

struct seg {
    dot A, B;
    seg(dot A, dot B): A{A}, B{B} {};
};

struct polygon {
    long double x, y;
    dot A, B, C, D, E, F;
    polygon(long double x, long double y) {
        x = x;
        y = y;
        A = dot(x, y);
        B = dot(x + sqrt(3) / 2.0, y + 1.0 / 2.0);
        C = dot(x + sqrt(3) / 2.0, y + 3.0 / 2.0);
        D = dot(x, y + 2);
        E = dot(x - sqrt(3) / 2.0, y + 1.0 / 2.0);
        F = dot(x - sqrt(3) / 2.0, y + 3.0 / 2.0);
    }
};

void build(vector<dot>& fig, long long x, long long y) {
    fig.emplace_back(x, y);
    
    fig.emplace_back(x + sqrt(3) / 2.0, y + 1.0 / 2.0);
    fig.emplace_back(x + sqrt(3) / 2.0, y + 3.0 / 2.0);

    fig.emplace_back(x, y + 2);

    fig.emplace_back(x - sqrt(3) / 2.0, y + 1.0 / 2.0);
    fig.emplace_back(x - sqrt(3) / 2.0, y + 3.0 / 2.0);
    
}

int main() {
    long long x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    if (x1 > x2) {
        swap(x1, x2);
        swap(y1, y2);
    }
    if (abs(x1 - x2) >= 2) {
        cout << 0;
        return 0;
    }
    if (x1 == x2) {
        if (abs(y1 - y2) >= 2) {
            cout << 0;
            return 0;
        }
        if (y1 < y2) {
            swap(y1, y2);
        }
        if (y1 - y2 >= 1) {
            long double h = 
        }
    }
    // x1 < x2

}