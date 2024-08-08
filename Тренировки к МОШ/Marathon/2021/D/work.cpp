#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

string s;
int sz;
int ans_sz = 1e9;
set<int> ans;

void rec(int idx, set<int> pool) {
    if (idx == (int) s.size()) {
        if (pool.size() < ans_sz) {
            ans = pool;
            ans_sz = pool.size();
        }
        return;
    }
    int mark = 0;
    int c = 0;
    while (c < 2) {
        if (mark == 0) {
            string cur = string(1, s[idx]);
            int val = stoi(cur);
            if (pool.find(val) == pool.end()) {
                pool.insert(stoi(cur));
                rec(idx + 1, pool);
                pool.erase(stoi(cur));
            } else {
                rec(idx + 1, pool);
            }
        }
        if (mark == 1) {
            if (idx + 1 < sz) {
                string cur = string(1, s[idx]) + string(1, s[idx + 1]);
                if (cur[0] == '0') {
                    return;
                }
                int val = stoi(cur);
                if (pool.find(val) == pool.end()) {
                    pool.insert(stoi(cur));
                    rec(idx + 2, pool);
                    pool.erase(stoi(cur));
                } else {
                    rec(idx + 2, pool);
                }
            }
        }
        mark = (mark + 1) % 2;
        c++;
    }
   
}

void solve() {
    ans.clear();
    ans_sz = 1e9;
    cin >> s;
    sz = (int) s.size();
    set<int> pool;
    rec(0, pool);
    cout << ans.size() << "\n";
    for (auto to : ans) {
        cout << to << " ";
    }
    cout << "\n\n";
}

int main() {
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}