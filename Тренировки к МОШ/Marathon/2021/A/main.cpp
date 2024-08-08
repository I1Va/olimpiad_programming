#include <iostream>
#include <vector>
#include <queue>
using namespace std;


vector<pair<int, int>> horse = {{-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}};
vector<pair<int, int>> diag = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

const int INF = 1e9;

int n;

bool inbord(pair<int, int> v) {
    return (v.first <= n && v.first >= 1 && v.second <= n && v.second >= 1);
}

void solve() {
    cin >> n;
    pair<int, int> st, nd;
    cin >> st.first >> st.second;
    cin >> nd.first >> nd.second;
    queue<pair<int, int>> q;
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));
    dist[st.first][st.second] = 0;
    q.push(st);
    while (q.size()) {
        auto v = q.front();
        q.pop();
        if ((v.first + v.second) % 2 == 0) {
            // Черная клетка
            for (auto move : horse) {
                pair<int, int> u = {v.first + move.first, v.second + move.second};
                if (inbord(u) && dist[u.first][u.second] > dist[v.first][v.second] + 1) {
                    dist[u.first][u.second] = dist[v.first][v.second] + 1;
                    q.push(u);
                }
            } 
        } else {
            for (int k = 1; k <= n; k++) {
                for (auto move : diag) {
                    pair<int, int> u = {v.first + move.first * k, v.second + move.second * k};
                    if (inbord(u) && dist[u.first][u.second] > dist[v.first][v.second] + 1) {
                        dist[u.first][u.second] = dist[v.first][v.second] + 1;
                        q.push(u);
                    }
                }
            }
        }
    }
    if (dist[nd.first][nd.second] == INF) {
        cout << "-1\n";
    } else {
        cout << dist[nd.first][nd.second] << "\n";
    }
}

int main() {
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}