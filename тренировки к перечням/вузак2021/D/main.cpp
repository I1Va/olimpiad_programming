#include <iostream>
#include <vector>
using namespace std;

int m, n;
vector<pair<int, int>> a;

bool cont(int x1, int y1, int x2, int y2) {
    vector<pair<int, int>> b = {
        {x1, y1},
        {x1, y1 - 1},
        {x1, y1 + 1},
        {x1 - 1, y1},
        {x1 - 1, y1 - 1},
        {x1 - 1, y1 + 1},
        {x1 + 1, y1},
        {x1 + 1, y1 - 1},
        {x1 + 1, y1 + 1},
    };
    for (auto to : b) {
        if (to.first == x2 && to.second == y2) {
            return true;
        }
    }
    return false;
}

void get(int xo, int yo, int& ans, const pair<int, int>& move) {
    for (int i = 0; i < m + 10; i++) {
        if (xo >= m || xo < 0 || yo >= m || yo < 0) {
            return;
        }
        bool state = true;
        int c = 0;
        for (auto w : a) {
            if (cont(w.first, w.second, xo, yo)) {
                state = false;
                break;
            }
            if (w.first == xo || w.second == yo || abs(w.first - xo) == abs(w.second - yo)) {
                c++;
            }
        }
        if (c == n && state) {
            // cout << "+: " << xo << " " << yo << "\n";
            ans++;
        }
        
        xo += move.first;
        yo += move.second;
    }
}

void solve() {
    
    cin >> m >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        a[i].first--;
        a[i].second--;
    }
    vector<pair<int, int>> moves = {{0, 1}, {0, -1}, {1,  1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 0}, {-1, 0}};
    int ans = 0;
    for (auto move : moves) {
        get(a[0].first, a[0].second, ans, move);
    }
    cout << ans << "\n";
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
}