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

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    vector<node> ans;
    long long cur = 0;
    while (1) {
        cout << cur << "/" << sum << "\n";
        long long mx = 0;
        pair<int, int> seg = {-1, -1};
        for (int l = 0; l < n; l++) {
            long long mn = a[l];
            for (int r = l; r < n; r++) {
                mn = min(mn, a[r]);
                if (mn * (r - l + 1) > mx) {
                    mx = mn * (r - l + 1);
                    seg = {l, r};
                }
            }
        }
        if (seg.first == -1) {
            break;
        }
        long long val = mx / (seg.second - seg.first + 1);
        for (int i = seg.first; i <= seg.second; i++) {
            a[i] -= val;
            cur += val;
        }
        ans.push_back(node(seg.first, seg.second, val));
        // cout << "a: " << a << "\n";
    }
    
    // for (int i = 0; i < n; i++) {
    //     if (a[i] > 0) {
    //         ans.push_back(node(i + 1, i + 1, a[i]));
    //     }
    // }
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