#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> a(m);
    int mn_l = 1e9 + 1;
    int mx_r = 0;
    for (int i = 0; i < m; i++) {
        cin >> a[i].first >> a[i].second;
        mn_l = min(mn_l, a[i].first);
        mx_r = max(mx_r, a[i].second);
    }
    vector<int> cand;
    for (int i = 0; i < m; i++) {
        if (a[i].first == mn_l && a[i].second == mx_r) {
            cout << "YES";
            return 0;
        } 
    }
    cout << "NO";

}