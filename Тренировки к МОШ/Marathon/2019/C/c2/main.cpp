#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <map>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

ostream& operator<< (ostream& stream, const vector<bool>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);

int n;
vector<vector<int>> g;
vector<bool> num_used;
vector<bool> abs_used;
vector<int> nums;
vector<int> ans;

void dfs(int v, int num, int p) {
    num_used[num] = true;
    ans[v] = num;
    for (int u : g[v]) {
        if (u != p && u != v) {
            int last = -1;
            bool state = true;
            shuffle(nums.begin(), nums.end(), rnd);
            for (int i : nums) {
                if (!num_used[i]) {
                    last = i;
                    if (!abs_used[abs(i - num)]) {
                        abs_used[abs(i - num)] = true;
                        dfs(u, i, v);
                        state = false;
                        break;
                    }
                }
            }
            if (state) {
                dfs(u, last, v);
            }
        }
    }
}

void dfs_2(int v, int p) {
    ans[v] = 1;
    for (int u : g[v]) {
        if (u != v && u != p) {
            dfs_2(u, v);
        }
    }
}

bool zero() {
    for (auto w : ans) {
        if (!w) {
            return true;
        }
    }
    return false;
}

int main() {
    cin >> n;
    nums.reserve(2 * n);
    for (int i = 1; i < 2 * n; i += 2) {
        nums.push_back(i);
    }
    // cout << "nums0: " << nums << "\n";
    shuffle(nums.begin(), nums.end(), rnd);
    g.resize(n);
    num_used.resize(2 * n, false), abs_used.resize(2 * n);
    ans.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int v, u;
        cin >> v >> u;
        g[v - 1].push_back(u - 1);
        g[u - 1].push_back(v - 1);
    }
    dfs(0, nums[0], -1);
    // dfs_2(0, -1);
    if (zero()) {
        cout << nums;
    } else {
        cout << ans;
    }
    // Красим жадно и правильно
}