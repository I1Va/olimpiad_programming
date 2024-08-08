#pragma GCC optimize("Ofast")
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int C = 0;

bool ask(int u, int v) {
    cout << "? " << u + 1 << " " << v + 1 << endl;
    string s;
    cin >> s;
    C++;
    return (s == "forward");
}

void ans(int v) {
    cout << "! " << v + 1 << endl;
    string s1;
    cin >> s1;
    if (s1 == "WRONG") {
        exit(1);
    }
}

void solve(int n) {
    vector<int> cn(n);
    vector<vector<int>> us(n, vector<int> (n));
    vector<int> anss;
    for (int v = 0; v < n; v++) {
        if (cn[v] > 1) {
            continue;
        }
        for (int u = 0; u < n; u++) {
            if (u == v || cn[u] > 1 || us[u][v]) {
                continue;
            }
            if (ask(u, v)) {
                cn[u]++;
            } else {
                cn[v]++;
            }
            us[u][v] = 1;
            us[v][u] = 1;
            if (cn[v] > 1) {
                break;
            }
        }
        if (cn[v] <= 1) {
            anss.push_back(v);
        }
    }
    for (int i : anss) {
        if (C == 2000) {
            ans(-2);
            return;
        }
        for (int j = 0; j < n; j++) {
            if (C == 2000) {
                ans(-2);
                return;
            }
            if (i == j || us[i][j]) {
                continue;
            }
            if (cn[i] > 1) {
                break;
            }
            if (ask(i, j)) {
                cn[i]++;
            } else {
                cn[j]++;
            }
            us[i][j] = 1;
            us[j][i] = 1;
        }
        if (cn[i] <= 1) {
            ans(i);
            return;
        }
    }
    ans(-2);
    return;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int g, t;
    cin >> g >> t;
    while (t--) {
        int n;
        cin >> n;
        solve(n);
        C = 0
    }
}
