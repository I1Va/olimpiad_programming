#include <iostream>
#include <vector>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

int n, m;

void solve() {

    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    long long cur = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            cur += abs(a[i][j]);
        }
    }
    vector<vector<long long>> prefs(n, vector<long long>(m, 0));
    for (int i = 0; i < n; i++) {
        prefs[i][0] = a[i][0];
    }
    for (int j = 0; j < m; j++) {
        prefs[0][j] = a[0][j];
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < )
    }
    int c = 0;
    vector<vector<int>> b(n, vector<int>(m, 0));
    vector<vector<int>> ans;
    for (int _ = 0; _ < 16; _++) {
        vector<int> idx = {-1, -1, -1, -1, -1};
        long long temp = 1e18;
        for (int i1 = 0; i1 < n; i1++) {
            for (int j1 = 0; j1 < m; j1++) {
                for (int i2 = i1; i2 < n; i2++) {
                    for (int j2 = j1; j2 < m; j2++) {
                        for (int w = -100; w <= 100; w++) {
                            long long res = get(i1, j1, i2, j2, w, a, b);
                            if (res < temp) {
                                temp = res;
                                idx = {i1, j1, i2, j2, w};
                            }
                        }
                    }
                }
            }
        }
        // cout << temp << ": " << idx << "\n";
        if (temp >= cur) {
            break;
        }
        cur = temp;
        for (int i = idx[0]; i <= idx[2]; i++) {
            for (int j = idx[1]; j <= idx[3]; j++) {
                b[i][j] += idx[4];
            }
        }
        ans.push_back({idx[0] + 1, idx[1] + 1, idx[2] + 1, idx[3] + 1, idx[4]});
        c++;
    }
    cout << c << "\n";
    for (auto to : ans) {
        cout << to << "\n";
    }
    cout << "\n";
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}