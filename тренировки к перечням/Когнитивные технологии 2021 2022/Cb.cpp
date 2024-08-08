#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int n, k, q;
vector<pair<int, int>> b;

int ans = 1e9;
vector<pair<int, int>> ans_path;
void rec(int cur, vector<vector<int>> a, unordered_set<int> used, int idx, vector<pair<int, int>> path) {
    if (idx == q) {
        if (cur < ans) {
            ans = cur;
            ans_path = path;
        }
        return;
    }
    if (b[idx].first == 1) {
        if (used.find(b[idx].second) != used.end()) {
            used.erase(b[idx].second);
            path.push_back({1, b[idx].second});
            rec(cur, a, used, idx + 1, path);
            path.pop_back();
            used.insert(b[idx].second);

        }
    } else {
        for (int i = 0; i < k; i++) {
            a[i].push_back(b[idx].second);
            path.push_back({2, i + 1});
            rec(cur, a, used, idx + 1, path);
            a[i].pop_back();
            path.pop_back();
        }
    }
    for (int i = 0; i < k; i++) {
        if (a[i].size()) {
            int val = a[i][(int) a[i].size() - 1];
            a[i].pop_back();
            used.insert(val);
            path.push_back({3, i + 1});
            rec(cur + 1, a, used, idx, path);
            path.pop_back();
            used.erase(val);
            a[i].push_back(val);
        }
    } 
}

int main() {
    cin >> n >> k >> q;
    vector<vector<int>> a(k);
    for (int i = 0; i < k; i++) {
        int s;
        cin >> s;
        for (int j = 0; j < s; j++) {
            int v;
            cin >> v;
            a[i].push_back(v);
        }
    }
    b.resize(q);
    for (int i = 0; i < q; i++) {
        cin >> b[i].first >> b[i].second;
    }
    unordered_set<int> used;
    rec(0, a, used, 0, {});
    cout << ans << "\n";
    for (auto to : ans_path) {
        if (to.first == 1) {
            cout << 1 << "\n";
        } else {
            cout << to.first << " " << to.second << "\n";
        }
    }
}