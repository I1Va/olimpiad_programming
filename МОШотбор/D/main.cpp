#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <chrono>
#include <random>
#include <algorithm>
#include <time.h>
#include <stdio.h>  
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);

int randrange(int a, int b) {
    return a + rnd() % (b - a);
}


struct edge {
    int u, v, num;
    edge(int u, int v, int num): u{u}, v{v}, num{num} {};
    edge(): u{-1}, v{-1}, num{-1} {}
    edge plus_1() {
        return edge(u + 1, v + 1, num + 1);
    }
};

ostream& operator<< (ostream& stream, const edge& a) {
    stream << "{" << a.u << " " << a.v << " " << a.num << "}";
    return stream;
}

ostream& operator<< (ostream& stream, const vector<edge>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    // vector<vector<int>> mark(n, vector<int>(n, -1));
    vector<edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v;
        edges[i].u--, edges[i].v--;
        edges[i].num = i;
        // mark[edges[i].u][edges[i].v] = mark[edges[i].v][edges[i].u] = 0;
    }
    // cout << edges << "\n";
    // shuffle(edges.begin(), edges.end(), rnd);
    // cout << edges << "\n";
    vector<vector<int>> colors(n, vector<int>(20, -1));
    vector<int> ans(m);
    queue<int> q;
    for (auto e : edges) {
        bool add = true;
        for (int c = 1; c <= k + 1; c++) {
            if (colors[e.u][c] == -1 && colors[e.v][c] == -1) {
                add = false;
                ans[e.num] = c;
                // cout << e.plus_1() << ": colored -> " << c << "\n";
                colors[e.u][c] = e.num;
                colors[e.v][c] = e.num;
            }
        }
        if (add) {
            q.push(e.num);
        }
    }
    // clock_t start = clock();
    bool state = false;
    while (q.size()) {
        // clock_t end = clock();
        // double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        // if (seconds > 30.0) {
        //     state = true;
        //     break;
        // }
        int cur = q.front();
        auto e = edges[cur];
        q.pop();
        int c = randrange(1, k + 2);
        // cout << e.plus_1() << ": colored -> " << c << "\n";
        for (auto w : {e.u, e.v}) {
            if (colors[w][c] != -1) {
                auto temp = edges[colors[w][c]];
                colors[temp.u][c] = -1;
                colors[temp.v][c] = -1;
                ans[temp.num] = -1;
                // cout << "removed: " << temp.plus_1() << "\n";
                q.push(temp.num);
            }
        }
        colors[e.u][c] = colors[e.v][c] = e.num;
        ans[e.num] = c;
    }
    for (auto x : ans) {
        cout << x << " ";
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