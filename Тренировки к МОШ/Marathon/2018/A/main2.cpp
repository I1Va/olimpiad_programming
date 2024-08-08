#include <iostream>
#include <vector>
using namespace std;


void solve() {
    long long x, y;
    cin >> x >> y;
    vector<bool> move = {true, true, false, false};
    // > 0
    vector<int> ans;
    int idx = 0;
    while (1) {
        if (idx % 2 == 0) {
            if ((x > 0) == move[idx]) {
                ans.push_back(abs(x));
                x = 0;
            }
        } else {
            if ((y > 0) == move[idx]) {
                ans.push_back(abs(y));
                y = 0;
            }
        }
        if (x == 0 && y == 0) {
            break;
        }
        ans.push_back(0);
        idx++;
        idx %= 4;
    }
    cout << ans.size() << "\n";
    for (auto to : ans) {
        cout << to << " ";
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