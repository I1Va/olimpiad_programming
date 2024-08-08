#include <iostream>
#include <vector>
using namespace std;

const long long INF = 1e18;

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
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<node> ans;
    while (1) {
        long long mx = 0;
        pair<int, int> seg = {-1, -1};
        for (int l = 0; l < n; l++) {
            for (int r = l; r < n; r++) {
                long long res = get(l, r, a);
                // cout << l << " " << r << ": " << res * (r - l + 1) << "\n";
                if (res * (r - l + 1) > mx) {
                    mx = res * (r - l + 1);
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
        }
        ans.push_back(node(seg.first, seg.second, val));
    }
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