#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> split(string s) {
    vector<string> res = {""};
    int cur = 0;
    for (auto w : s) {
        if (w == ' ') {
            res.push_back("");
            cur++;
        } else {
            res[cur] += w;
        }
    }
    return res;
}

void create(int f, vector<long long>& resources, vector<vector<pair<int, long long>>>& recipes) {
    bool state = true;
    int mn = 1e9;
    for (auto w : recipes[f]) {
        if (resources[w.first - 1] - w.second < 0) {
            state = false;
            mn = min(mn, w.first);
        }
    }
    if (!state) {
        cout << "FAIL: missing " << mn << "\n";
    } else {
        for (auto w : recipes[f]) {
            resources[w.first - 1] -= w.second;
        }
        cout << "OK\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        long long A, E;
        int n;
        cin >> A >> E >> n;
        vector<long long> e(n);
        for (int i = 0; i < n; i++) {
            cin >> e[i];
        }
        vector<long long> x(n);
        for (int i = 0; i < n; i++) {
            cin >> x[i];
        }
        vector<bool> work(n, false);
        int m;
        cin >> m;
        vector<vector<pair<int, long long>>> recipes(m);
        for (int i = 0; i < m; i++) {
            int k;
            cin >> k;
            recipes[i].reserve(k);
            for (int j = 0; j < k; j++) {
                pair<int, long long> cur;
                cin >> cur.first >> cur.second;
                recipes[i].push_back(cur);
            }
        }
        int q;
        cin >> q;
        long long balance = A;
        int prev = 0;
        vector<long long> resources(n);
        while (q--) {
            string s1;
            cin >> s1;
            int step;
            cin >> step;
            for (int _ = 0; _ < step - prev; _++) {
                for (int i = 0; i < n; i++) {
                    if (!work[i]) {
                        continue;
                    }
                    if (balance - e[i] < 0) {
                        continue;
                    }
                    balance -= e[i];
                    resources[i] += x[i];
                }
                balance += E;
            }
            prev = step;
            char s2;
            cin >> s2;
            int f;
            cin >> f;
            string ty;
            cin >> ty;
            if (ty == "ON") {
                work[f - 1] = true;
            } else if (ty == "OFF") {
                work[f - 1] = false;
            } else {
                create(f - 1, resources, recipes);
            }
        }
    }
}