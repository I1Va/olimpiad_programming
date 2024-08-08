#include <iostream>
#include <vector>
#include <queue>
using namespace std;


const long long maxn = 2000;
const long long INF = 1e9;
long long n, m;
char a[maxn][maxn];
vector<pair<long long, long long>> p;
vector<vector<long long>> d;
pair<long long, long long> x;

vector<pair<long long, long long>> moves = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

void build() {
    d.resize(n);
    for (long long i = 0; i < n; i++) {
        d[i].resize(m, INF);
    }
    queue<pair<long long, long long>> q;
    q.push(x);
    d[x.first][x.second] = 0;
    while (q.size()) {
        auto v = q.front();
        long long i = v.first;
        long long j = v.second;
        q.pop();
        for (auto move : moves) {
            long long to_i = i + move.first;
            long long to_j = j + move.second;
            if (to_i < 0 || to_i >= n || to_j < 0 || to_j >= m || d[to_i][to_j] <= d[i][j] + 1 || a[to_i][to_j] == 'B') {
                continue;
            }
            d[to_i][to_j] = d[i][j] + 1;
            if (a[to_i][to_j] != 'I') {
                q.push({to_i, to_j});
            }
        }
    }
}

long long get(pair<long long, long long> x) {
    if (d[x.first][x.second] == INF) {
        cout << -1;
        exit(0);
    }
    return d[x.first][x.second];
}

int main() {
    cin >> n >> m;
    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < m; j++) {
            char v;
            cin >> v;
            a[i][j] = v;
            if (v == 'I') {
                p.push_back({i, j});
            }
            if (v == 'X') {
                x = {i, j};
            }
        }
    }
    build();
    long long mx = get(p[0]);
    long long c = mx % 2;
    for (long long i = 1; i < (long long) p.size(); i++) {
        long long cur = get(p[i]);
        if (cur % 2 != c) {
            cout << -1;
            return 0;
        }
        mx = max(mx, cur);
    }
    cout << mx * (long long) p.size();
}