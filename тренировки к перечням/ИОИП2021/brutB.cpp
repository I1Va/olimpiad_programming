#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
int n, a, b;
int ans = 1e9;

vector<pair<int, int>> moves = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

void rec(int cur, int tick, int f, int s, vector<bool> used) {
    if (!used[f]) {
        used[f] = true;
        cur++;
    }
    if (!used[s]) {
        used[s] = true;
        cur++;
    }
    if (tick > 2 * n) {
        return;
    }
    if (cur == n) {
        
        ans = min(ans, tick);
        return;
    }
    for (auto move : moves) {
        int f1 = (f + move.first + n) % n;
        int s1 = (s + move.second + n) % n;
        rec(cur, tick + 1, f1, s1, used);
    }
}

int main() {
    cin >> n >> a >> b;
    vector<bool> used(n, false);
    rec(0, 0, a - 1, b - 1, used);
    cout << ans;
}
