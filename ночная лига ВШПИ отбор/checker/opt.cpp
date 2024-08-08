#include <iostream>
#include <vector>
using namespace std;

struct point {
    int i, j;
    point(): i{0}, j{0} {}
    point(int i, int j): i{i}, j{j} {}
};

struct star {
    int i, j, r, t;
    star(): i{0}, j{0}, r{0}, t{0} {}
    star(int i, int j, int r, int t): i{i}, j{j}, r{r}, t{t} {}
};

int q, n, s;
vector<star> stars;
point fir, sec;

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
    for (int i = 0; i <= 10; i++) {
        mx = max(mx, get());
        for (int j = 0; j < s; j++) {
            stars[j].t = (stars[j].t + 1) % (stars[j].r);
        }
    }
    cout << mx << "\n";
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
    }
}