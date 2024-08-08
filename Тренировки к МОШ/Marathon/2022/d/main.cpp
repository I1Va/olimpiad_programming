#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <random>
#include <cmath>
using namespace std;

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);

const long double maxv = 1e6;

long double randomv() {
    return (long double) rnd() / rnd.max() * 2 * maxv - maxv;
}

int randrange(int a, int b) {
    return a + rnd() % (b - a);
}

long double chance() {
    return (long double) rnd() / rnd.max();
}








int n, m, k;

long double dist(const vector<long double> a, const vector<long double> b) {
    long long res = 0;
    for (int i = 0; i < (int) a.size(); i++) {
        res += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return sqrt(res);
}

long double start_f(const vector<vector<long double>>& cord) {
    long double res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            res += dist(cord[i], cord[j]);
        }
    }
    return res;
}


vector<vector<long double>> cord;
vector<vector<long double>> p;
long double ans;

long double f(const vector<vector<long double>>& p) {
    vector<vector<long double>> new_cord(n, vector<long double>(k));
    for (int i = 0; i < n; i++) {
        for (int ki = 0; ki < k; ki++) {
            for (int mi = 0; mi < m; mi++) {
                new_cord[i][ki] = p[mi][ki] * cord[i][mi];
            }
        }
    }
    // cout << "done";
    return abs(start_f(cord) -  start_f(new_cord));
}

void print_matrix(const vector<vector<long double>>& a) {
    for (auto& row : a) {
        for (auto& w : row) {
            cout << w << " ";
        }
        cout << "\n";
    }
}

void annealing(long double time) {
    // cout << "end";
    for (int i = 0; i < m; i++) {
        // cout << i << "\n";
        for (int j = 0; j < k; j++) {
            p[i][j] = randomv();
        }
    }
    // cout << "done";
    ans = f(p);
    long double t = 1;
    int iters = 0;
    clock_t start = clock();
    while (iters % 100 != 0 || (long double) (clock() - start) / CLOCKS_PER_SEC <= time) {
        iters++;
        // cout << iters << "\n";
        t *= 0.99;
        auto q = p;
        q[randrange(0, m)][randrange(0, k)] = randomv();
        long long val = f(q);
        if (val < ans || chance() < exp((ans - val) / t)) {
            ans = val;
            p = q;
        }
    }
}

void solve() {
    cin >> n >> m >> k;
    cord.resize(n);
    p.resize(m);
    for (int i = 0; i < m; i++) {
        p[i].resize(k);
    }
    for (int i = 0; i < n; i++) {
        cord[i].resize(m);
        for (int j = 0; j < m; j++) {
            cin >> cord[i][j];
        }
    }
    long double end_ans = 1e18;
    auto end_p = p;
    long double time = 1;
    int c = 20;
    for (int i = 0; i < c; i++) {
        annealing(time / c);
        if (ans < end_ans) {
            end_ans = ans;
            end_p = p;
        }
    }
    // cout << dist(cord[0], cord[1]) << "\n";
    // cout << start_f(cord);
    // print_matrix(end_p);
    // cout << "\n";
    // cout << "end_ans: " << end_ans << "\n";
    cout << "done\n";
   
}

int main() {
    cout << fixed << setprecision(6);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}