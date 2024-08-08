#include <iostream>
#include <vector>
#include <set>
using namespace std;


int n;
vector<int> ans;
vector<multiset<int>> g;

void euler(int v) {
    while (!g[v].empty()) {
        int u = *g[v].begin();
        g[v].erase(g[v].find(u));
        g[u].erase(g[u].find(v));
        euler(u);
    }
    ans.push_back(v + 1);
}

int main() {
    cin >> n;
    g.resize(n);
    int cnt = 0;
    int start = 0;
    for (int i = 0; i < n; i++) {
        int sz;
        cin >> sz;
        for (int j = 0; j < sz; j++) {
            int ver;
            cin >> ver;
            g[i].insert(ver - 1);
        }
        if (g[i].size() % 2 == 1) {
            start = i;
            cnt++;
        }
    }
    if (!(cnt == 2 || cnt == 0)) {
        cout << -1;
        return 0;
    }
    euler(start);
    cout << ans.size() << "\n";
    for (auto to : ans) {
        cout << to << " ";
    }
}