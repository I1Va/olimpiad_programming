#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <unordered_set>
using namespace std;

const int maxn = 20;
const long long mod = 1e9 + 7;

int n;
vector<vector<int>> g;

bool check(const vector<int>& p) {
    unordered_set<int> used;
    for (int v : p) {
        for (int u : g[v]) {
            if (used.find(u) != used.end()) {
                return false;
            }
        }
        used.insert(v);
    }
    return true;
}

int main() {
    cin >> n;
    g.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
    }
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
    long long ans = 0;
    while(1) {
        ans += check(p);
        if (!next_permutation(p.begin(), p.end())) {
            break;
        }
    }
    cout << ans;

}