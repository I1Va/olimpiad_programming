#include <iostream>
#include <vector>
using namespace std;

int n;
const long long INF = 1e18;

long long get(int l, int r, const vector<long long>& a) {
    long long mn = 1e18;
    for (int i = l; i < r; i++) {
        mn = min(mn, a[i]);
    }
    return mn;
}

void build(int v, int l, int r, vector<long long>& tree, const vector<long long>& a) {
    if (r - l == 1) {
        tree[v] = a[l];
        return; 
    }
    int m = (l + r) / 2;
    build(v * 2, l, m, tree, a);
    build(v * 2 + 1, m, r, tree, a);
    tree[v] = min(tree[2 * v], tree[v * 2 + 1]);
}

long long get(int v, int l, int r, int ql, int qr, const vector<long long>& tree) {
    if (l >= qr || r <= ql) {
        return INF;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return min(get(v * 2, l, m, ql, qr, tree), get(v * 2 + 1, m, r, ql, qr, tree));
}

int main() {
    cin >> n;
    vector<long long> b(2 * n);
    
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        b[i + n] = b[i];
    }
    vector<long long> prefs(2 * n + 1);
    prefs[0] = 0;
    for (int i = 1; i < 2 * n + 1; i++) {
        prefs[i] = prefs[i - 1] + b[i - 1];
    }
    vector<long long> tree(8 * n + 1);
    build(1, 0, 2 * n, tree, prefs);
    long long ans = 0;
    for (int r = 0; r < 2 * n; r++) {
        ans = max(ans, prefs[r + 1] - get(1, 0, 2 * n, max(0, r + 1 - n), r + 1, tree));
    }
    cout << ans;
}
