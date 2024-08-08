#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);

int randrange(int a, int b) {
    return a + rnd() % (b - a);
}

long double chance() {
    return (long double) rnd() / (rnd.max());
}


int n;
vector<vector<long long>> C;
vector<vector<int>> p;
long long ans;

long long get(const vector<int>& com) {
    return C[com[0]][com[1]] * C[com[1]][com[2]] * C[com[2]][com[0]];
}

vector<int> stabilize(vector<int> cur) {
    vector<int> best = cur;
    long long ans = get(best);
    for (int i = 0; i < 10; i++) {
        long long val = get(cur);
        if (val > ans) {
            ans = val;
            best = cur;
        }
        next_permutation(cur.begin(), cur.end());
    }
    return best;
}

void print_team(const vector<vector<int>>& p) {
    for (int i = 0; i < n / 3; i++) {
        cout << p[i] << "\n";
    }
    cout << "\n";
}


long long f(const vector<vector<int>>& p) {
    long long res = 0;
    for (int i = 0; i < n / 3; i++) {
        res += get(p[i]);
    }
    return res;
}

void change(int ui, int uj, int vi, int vj) {
    long long cnt1 = get(p[ui]) + get(p[vi]);
    swap(p[ui][uj], p[vi][vj]);
    long long cnt2 = get(p[ui]) + get(p[vi]);
    ans = ans - cnt1 + cnt2;
}

long long try_change(int ui, int uj, int vi, int vj) {
    change(ui, uj, vi, vj);
    long long val = ans;
    change(ui, uj, vi, vj);
    return val;
}

void annealing(long double time) {
    p.clear();
    p.resize(n / 3);
    vector<int> st;
    st.reserve(n);
    for (int i = 0; i < n / 3; i++) {
        for (int j = 0; j < 3; j++) {
            st.push_back(i);
        }
    }
    shuffle(st.begin(), st.end(), rnd);
    for (int i = 0; i < n; i++) {
        p[st[i]].push_back(i);
    }
    ans = f(p);
    long double t = 1;
    int iters = 0;
    clock_t start = clock();
    // cout << "done\n";
    while (iters % 100 != 0 || (long double) (clock() - start) / CLOCKS_PER_SEC <= time) {
        iters++;
        // cout << iters << "\n";
        t *= 0.99;
        int ui = randrange(0, n / 3), uj = randrange(0, 3);
        int vi = randrange(0, n / 3), vj = randrange(0, 3);
        long long val = try_change(ui, uj, vi, vj);
        if (val > ans || chance() < exp((long double)(val - ans) / t)) {
            change(ui, uj, vi, vj);
        }
    }
}

void solve(int tc) {
    cin >> n;
    C.resize(n);
    for (int i = 0; i < n; i++) {
        C[i].resize(n);
        for (int j = 0; j < n; j++) {
            cin >> C[i][j];
        }
    }
    long double time = 40;
    int c = 50;
    vector<vector<int>> end_p;
    long long end_ans = 0;
    for (int i = 0; i < c; i++) {
        annealing(time / c);
        if (ans > end_ans) {
            end_ans = ans;
            end_p = p;
        }
    }
    // cout << "done\n";
    for (int i = 0; i < n / 3; i++) {
        end_p[i] = stabilize(end_p[i]);
    }
    for (auto& row : end_p) {
        for (auto w : row) {
            cout << w + 1 << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
}