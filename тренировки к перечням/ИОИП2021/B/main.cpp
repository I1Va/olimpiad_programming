#include <iostream>
using namespace std;

long long n, a, b;

bool check1(long long t) {
    long long ab = b - a - 1;
    long long b_a = n - ab - 2;
    if (t < ab) {
        return t >= 2 * b_a + ab - t;
    }
    if (t <= 2 * ab) {
        return t >= b_a;
    }
    if (t > ab) {
        return t >= b_a - (t - 2 * ab);
    }
    return true;
}

bool check2(long long t) {
    long long ab = b - a - 1;
    long long b_a = n - ab - 2;
    return t >= ab + ab % 2 + (b_a + 1) / 2;
}

bool check3(long long t) {
    long long ab = b - a - 1;
    long long b_a = n - ab - 2;
    if (t < ab) {
        return t >= 2 * b_a + ab - t;
    }
    if (t <= 2 * ab) {
        return t >= b_a;
    }
    if (t > ab) {
        return t >= b_a - (t - 2 * ab);
    }
    return true;
}

bool check4(long long t) {
    long long ab = b - a - 1;
    long long b_a = n - ab - 2;
    return t >= b_a + b_a % 2 + (ab + 1) / 2;
}

bool comp(long long t) {
    if (check1(t)) {
        return true;
    }
    if (check2(t)) {
        return true;
    }
    if (check3(t)) {
        return true;
    }
    if (check4(t)) {
        return true;
    }
    return false;
} 

int main() {
    
    cin >> n >> a >> b;
    if (a > b) {
        swap(a, b);
    }
    long long l = -1;
    long long r = n;
    while (r - l > 1) {
        long long m = (l + r) / 2;
        bool res = comp(m);
        // cout << m << ": " << res << "\n";
        if (res) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << r;
}