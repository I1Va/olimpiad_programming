#include <iostream>
#include <vector>
using namespace std;

ostream& operator<< (ostream& stream, const vector<long long>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

vector<long long> segs, tree;

void build(int v, int l, int r) {
    if (r - l == 1) {
        tree[v] = segs[l];
        return;
    }
    int m = (l + r) / 2;
    build(v * 2, l, m);
    build(v * 2 + 1, m, r);
    tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
}

long long get(int v, int l, int r, int ql, int qr) {
    if (ql >= r || qr <= l) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return max(get(v * 2, l, m, ql, qr), get(v * 2 + 1, m, r, ql, qr));
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<long long> prefs(n + 1);
    for (int i = 1; i <= n; i++) {
        prefs[i] = prefs[i - 1] + a[i - 1];
    }
    segs.resize(n);
    for (int i = 0; i + k - 1 < n; i++) {
        segs[i] = prefs[i + k] - prefs[i];
    }
    tree.resize(4 * n);
    build(1, 0, n);
    // cout << "segs:\n" << segs << "\n";
    long long ans = 1e18;
    for (int i = 0; i + k - 1 < n; i++) {
        // Алиса выбирает отрезок [i, i + k - 1]
        long long alice = segs[i];
        long long bob = max(get(1, 0, n, 0, i - k + 1), get(1, 0, n, i + k, n));
        // cout << alice << ": " << bob << "\n";
        ans = min(ans, bob);
    }
    cout << ans;
    // printf("%I64d\n", ans);
}