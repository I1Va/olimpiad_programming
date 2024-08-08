#include <iostream>
#include <vector>
using namespace std;

ostream& operator<< (ostream& stream, const vector<long long>& a) {
    for (auto to : a) {
        stream << to << "\n";
    }
    return stream;
}

int n;
long long A, B;
vector<long long> t;

bool comp1(long long x) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        long long l = -1;
        long long r = x + 1;
        while (r - l > 1) {
            long long m = (l + r) / 2;
            if (m * A + (x - m) * B > t[i]) {
                r = m;
            } else {
                l = m;
            }
        }
        sum += r;
    }
    return sum <= x;
}

void solve1() {
    long long left = -1;
    long long right = 1e9;
    while (right - left > 1) {
        int mid = (left + right) / 2;
        if (comp1(mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    cout << right;
}

bool comp2(long long x) {
    long long cur = B * x;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        if (t[i] >= cur) {
            return false;
        }
        if ((cur - t[i]) % (B - A) == 0) {
            sum += (cur - t[i]) / (B - A) - 1;
        } else {
            sum += (cur - t[i]) / (B - A);
        }
    }
    return sum >= x;
}

void solve2() {
    long long l = -1;
    long long r = 1e9;
    while (r - l > 1) {
        long long m = (l + r) / 2;
        bool res = comp2(m);
        // cout << "mid = " << m << ": " << res << "\n";
        if (res) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << r;
}

int main() {
    cin >> n >> A >> B;
    t.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }
    if (A > B) {
        solve1();
    } else if (A < B) {
        solve2();
    } else {
        long long mx = -1e18;
        for (int i = 0; i < n; i++) {
            mx = max(mx, t[i]);
        }
        if (mx < 0) {
            cout << 0;
        } else {
            if (mx % B == 0) {
                cout << mx / B + 1;
            } else {
                cout << (mx + B - 1) / B;
            }
        }
    }
}