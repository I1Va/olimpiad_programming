#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

ostream& operator<< (ostream& stream, const unordered_set<int>& a) {
    for (auto to : a) {
        stream << to + 1<< " ";
    }
    return stream;
}

struct qu {
    int t, u, v;
    qu(): t{-1}, u{-1}, v{-1} {}
    qu(int t, int u, int v): t{t}, u{u}, v{v} {}
};

int group;
int n, m, q;
vector<unordered_set<int>> g;
vector<unordered_set<int>> un_g;

vector<qu> quests;

void print() {
    cout << "g:\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ": " << g[i] << "\n";
    }
}

void dfs(int v, int d, int prev, long long& res) {
    res += d;
    for (auto to : g[v]) {
        if (to != prev) {
            dfs(to, d + 1, v, res);
        }
    }
}

bool dfs_orient(int v, int prev, const int& target) {
    for (auto to : un_g[v]) {
        if (to != prev) {
            if (to == target) {
                g[to].erase(v);
                g[v].insert(to);
                return true;
            }
            if (dfs_orient(to, v, target)) {
                // cout << "erase: " << to + 1<< " -> " << v + 1 << "\n"; 
                // cout << "insert: " << v + 1 << " -> " << to + 1 << "\n"; 
                g[to].erase(v);
                g[v].insert(to);
                return true;
            }
        }
    }
    return false;
}

long long get_beauty() {
    long long res = 0;
    for (int i = 0; i < n; i++) {
        dfs(i, 0, -1, res);
    }
    return res;
}

void solve0() {
    for (int v = 0; v < n; v++) {
        for (int u : g[v]) {
            un_g[v].insert(u);
            un_g[u].insert(v);
        }
    }
    cout << get_beauty() << "\n";
    // print();
    for (auto cur : quests) {
        // cout << "\nquestion: " << cur.t << " " << cur.u + 1 << " " << cur.v + 1<< "\n";
        if (cur.t == 1) {
            g[cur.u].insert(cur.v);

            un_g[cur.u].insert(cur.v);
            un_g[cur.v].insert(cur.u);
        }
        if (cur.t == 2) { // ??
            g[cur.u].erase(cur.v);
            g[cur.v].erase(cur.u);

            un_g[cur.u].erase(cur.v);
            un_g[cur.v].erase(cur.u);
        }
        if (cur.t == 3) { // ??
            if (g[cur.u].find(cur.v) != g[cur.u].end()) {
                g[cur.u].erase(cur.v);
                g[cur.v].insert(cur.u);
            } else {
                g[cur.v].erase(cur.u);
                g[cur.u].insert(cur.v);
            }
            
        }
        if (cur.t == 4) {
            dfs_orient(cur.u, -1, cur.v);
        }
        // print();
        // cout << "beauty = " << 
        cout << get_beauty() << "\n";
    }
}

int main() {
    cin >> group;
    cin >> n >> m >> q;
    g.resize(n);
    un_g.resize(n);
    quests.resize(q);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u - 1].insert(v - 1);
    }
    for (int i = 0; i < q; i++) {
        int t, u, v;
        cin >> t >> u >> v;
        quests[i] = qu(t, u - 1, v - 1);
    }
    solve0();
}
