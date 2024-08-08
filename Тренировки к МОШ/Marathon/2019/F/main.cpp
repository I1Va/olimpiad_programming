#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <bitset>
using namespace std;

map<int, bool> used;
string coms;
vector<int> order;
map<int, int> tin, tout;
int timer = 0;

void rec(int v, int idx) {
    if (used.find(v) == used.end()) {
        used[v] = true;
    }
    tin[v] = timer++;
    order.push_back(v);
    if (coms[idx] == 'D') {
        if (used.find(v * 2) == used.end()) {
            rec(v * 2, idx + 1);
        } else {
            rec(v * 2 + 1, idx + 1);
        }
    } else {
        if (v % 2 == 0) {
            rec(v + 1, idx + 1);
        } else {
            while (v % 2 != 0) {
                v /= 2;
            }
            rec(v, idx + 1);
        }
    }
    tout[v] = timer++;
}
void solve() {
    used.clear();
    order.clear();
    tin.clear(), tout.clear();
    timer = 0;
    cin >> coms;
    rec(1, 0);
    vector<long long> ans;
    for (auto v : order) {
        if (tin[v] = tout[v] - 1) {
            cout << get(v) << "\n";
        }
    }


}
int main() {
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}