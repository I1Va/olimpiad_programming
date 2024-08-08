#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

ostream& operator<< (ostream& stream, const vector<long long>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

const long long INF = 1e18;
auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);
const int iters = 100;

long long randrange(long long a, long long b) {
    return a + rnd() % (b - a);
}

struct node {
    int l, r;
    long long val;
    node(int l, int r, long long val): l{l}, r{r}, val{val} {}
};

long long get(int l, int r, const vector<long long>& a) {
    long long mn = INF;
    for (int i = l; i <= r; i++) {
        mn = min(mn, a[i]);
    }
    return mn;
}

void remove(int l, int r, long long val, vector<long long>& a, vector<node>& ans) {
    for (int i = l; i <= r; i++) {
        a[i] -= val;
    }
    ans.push_back(node(l, r, val));
} 

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<node> ans;
    int iters1 = 1000;
    int iters2 = 100;
    for (int i = 0; i < iters1; i++) {
        long long mx = 0;
        pair<int, int> seg;
        for (int j = 0; j < iters2; j++) {
            int l = randrange(0, n);
            int r = randrange(l, n);
            long long res = get(l, r, a);
            if (res * (r - l + 1) > mx) {
                mx = res * (r - l + 1);
                seg = {l, r};
            }
        }
        if (!mx) {
            continue;
        }
        remove(seg.first, seg.second, mx / (seg.second - seg.first + 1), a, ans);
    }
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            ans.push_back(node(i + 1, i + 1, a[i]));
        }
    }
    // cout << "a: " << a << "\n";
    cout << ans.size() << "\n";
    for (auto to : ans) {
        cout << to.l + 1 << " " << to.r + 1 << " " << to.val << "\n";
    }
}
int main() {
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}