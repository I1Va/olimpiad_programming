#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <set>
using namespace std;

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);

int randrange(int a, int b) {
    return a + rnd() % (b - a);
}

string s;
int sz;
set<int> ans;
clock_t start;
int iters = 0;

void rec(int idx, set<int> pool, const long double& time, bool& stop) {
    iters++;
    if (iters % 100 == 0) {
        clock_t end = clock();
        // cout << (long double) (end - start) / CLOCKS_PER_SEC << "\n";
        if ((long double) (end - start) / CLOCKS_PER_SEC > time) {
            stop = true;
        }
    }
    if (stop) {
        return;
    }
    
    if (idx == (int) s.size()) {
        if (ans.empty() || pool.size() < ans.size()) {
            ans = pool;
        }
        return;
    }
    int mark = randrange(0, 1 + 1);
    int c = 0;
    while (c < 2) {
        if (mark == 0) {
            string cur = string(1, s[idx]);
            int val = stoi(cur);
            if (pool.find(val) == pool.end()) {
                pool.insert(stoi(cur));
                rec(idx + 1, pool, time, stop);
                pool.erase(stoi(cur));
            } else {
                rec(idx + 1, pool, time, stop);
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
                    rec(idx + 2, pool, time, stop);
                    pool.erase(stoi(cur));
                } else {
                    rec(idx + 2, pool, time, stop);
                }
            }
        }
        mark = (mark + 1) % 2;
        c++;
    }
   
}

void solve() {
    cin >> s;
    sz = (int) s.size();
    int c = 10;
    set<int> end_ans;
    long double time = 0.01;
    for (int i = 0; i < c; i++) {
        ans.clear();
        start = clock();
        set<int> pool;
        iters = 0;
        bool stop = false;
        rec(0, pool, time, stop);
        if (end_ans.empty() || ans.size() < end_ans.size()) {
            end_ans = ans;
        }
    }
    if (ans.empty()) {
        cout << "1\n1\n";
    } else {
        cout << ans.size() << "\n";
        for (auto to : ans) {
            cout << to << " ";
        }
        cout << "\n";
    }
    
}

int main() {
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}