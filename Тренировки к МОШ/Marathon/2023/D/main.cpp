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

ostream& operator<< (ostream& stream, const vector<string>& a) {
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
vector<string> s;
int asz;
vector<string> a;

int dist(string a, string b) {
    int c = max((int) a.size(), (int) b.size());
    int sz = min((int) a.size(), (int) b.size());
    for (int i = 0; i < sz; i++) {
        if (a[i] == b[i]) {
            c--;
        }
    }
    return c;
}

vector<int> rnd_build() {
    vector<int> p(asz);
    for (int i = 0; i < asz; i++) {
        p[i] = 1;
    }
    for (int i = 0; i < n - asz; i++) {
        p[randrange(0, asz)]++;
    }
    return p;
}

vector<string> trans(const vector<int>& p) {
    vector<string> cur(asz, "");
    int idx = 0;
    for (int i = 0; i < asz; i++) {
        for (int j = 0; j < p[i]; j++) {
            cur[i] += s[idx];
            idx++;
        }
    }
    return cur;
}

long long f(const vector<int>& p) {
    auto cur = trans(p);
    long long res = 0;
    for (int i = 0; i < asz; i++) {
        res += dist(a[i], cur[i]);
    }
    return res;
}


vector<int> p;
long long ans;

void annealing(long double time) {
    p = rnd_build();
    ans = f(p);
    clock_t start = clock();
    int iters = 0;
    long double t = 1;
    while (iters % 100 != 0 || (long double)(clock() - start) / CLOCKS_PER_SEC <= time) {
        iters++;
        t *= 0.99;
        vector<int> q = p;
        while (1) {
            int v = randrange(0, asz - 1);
            if (q[v + 1] > 1) {
                q[v]++;
                q[v + 1]--;
                break;
            }
        }
        long long val = f(q);
        if (val < ans || (chance() < exp((long double)(ans - val) / t))) {
            ans = val;
            p = q;
        }
    }    
}

void solve() {
    cin >> n;
    s.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    
    cin >> asz;
    a.resize(asz);
    for (int i = 0; i < asz; i++) {
        int szi;
        cin >> szi;
        a[i] = "";
        for (int j = 0; j < szi; j++) {
            string temp;
            cin >> temp;
            a[i] += temp;
        }
    }
    long long end_ans = 1e18;
    vector<int> end_p;
    int c = 20;
    long double time = 5;
    for (int i = 0; i < c; i++) {
        annealing(time / c);
        if (ans < end_ans) {
            end_ans = ans;
            end_p = p;
        }
    }
    cout << end_p << "\n";

}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}