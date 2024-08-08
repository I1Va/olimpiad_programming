#include <iostream>
#include <vector>
using namespace std;

int dist(const pair<int, int>& a, const pair<int, int>& b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

const int maxn = 2000;

int d[maxn][maxn];
bool A[maxn][maxn];
pair<int, int> B[maxn][maxn];

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> p;
    pair<int, int> X;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char v;
            cin >> v;
            if (v == 'I') {
                p.push_back({i, j});
            }
            if (v == 'X') {
                X = {i, j};
            }
        }
    }
    int mx = dist(p[0], X);
    int c = mx % 2;
    for (int i = 1; i < (int) p.size(); i++) {
        int cur = dist(p[i], X);
        if (cur % 2 != c) {
            cout << -1;
            return 0;
        }
        mx = max(mx, cur);
    }
    cout << mx * (int) p.size();
}