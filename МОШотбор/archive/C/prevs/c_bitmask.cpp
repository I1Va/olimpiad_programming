#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <bitset>
#include <map>
#include <chrono>
#include <random>
#include <set>
using namespace std;

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);

long long randrange(long long a, long long b) {
    return a + rnd() % (b - a);
}

const int sz_cut = 30;
const int iters = 1;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

ostream& operator<< (ostream& stream, const pair<long long, long long>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream;
}

ostream& operator<< (ostream& stream, const vector<pair<long long, long long>>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

struct node {
    long long val;
    long long mask;
    node(long long val, long long mask): val{val}, mask{mask} {};
};

node get(int l, int r, const vector<pair<long long, long long>>& a) {
    vector<pair<long long, long long>> pool;
    pool.reserve(r - l + 1);
    for (int i = l; i <= r; i++) {
        pool.push_back(a[i]);
    }
    // cout << "pool: " << pool << "\n";
    int sz = pool.size();
    node res = node(0, 0);
    for (long long mask = 0; mask < (1ll << sz); mask++) {
        pair<long long, long long> val = {0, 0};
        for (int i = 0; i < sz; i++) {
            if ((mask >> i) & 1ll) {
                val = {val.first + pool[i].first, val.second + pool[i].second};
            }
        }
        // cout << val.first << ", " << val.second << ", mask = " << bitset<8>(mask) << "\n";
        if (val.first == val.second && val.first > res.val) {
            
            res = node(val.first, mask);
        }
    }
    return res;
}

void add(int l, int r, node res, long long& val, vector<int>& ans) {
    int n = r - l + 1;
    val += res.val;
    for (int i = 0; i < n; i++) {
        if ((res.mask >> i) & 1ll) {
            ans.push_back(l + i + 1);
        }
    }
}

pair<long long, vector<int>> f(vector<pair<long long, long long>>& a) {
    long long val = 0;
    vector<int> ans;
    int n = (int) a.size();
    ans.reserve(n);
    int l = 0;
    int r = -1;
    while (1) {
        l = r + 1;
        r = l + sz_cut - 1;
        bool state = false;
        if (r >= n) {
            state = true;
            r = n - 1;
        }        
        add(l, r, get(l, r, a), val, ans);
        // cout << "[" << l << ":" << r << "]\n";
        if (state) {
            break;
        }
    }
    return make_pair(val, ans);
}

vector<pair<long long, long long>> changed(vector<pair<long long, long long>> a) {
    swap(a[randrange(0, (int) a.size())], a[randrange(0, (int) a.size())]);
    return a;
}

int main() {
    int q;
    cin >> q;
    while (q--) {
        int n;
        cin >> n;
        vector<pair<long long, long long>> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i].first;
        }
        for (int i = 0; i < n; i++) {
            cin >> a[i].second;
        }
        
        pair<long long, vector<int>> ans = {0, {}};
        for (int i = 0; i < iters; i++) {
            // shuffle(a.begin(), a.end(), rnd);
            auto res = f(a);
            if (res.first > ans.first) {
                ans = res;
            }
        }
        // shuffle(a.begin(), a.end(), rnd);
        // for (int i = 0; i < iters; i++) {
        //     auto temp = changed(a);
        //     auto s1 = f(temp);
        //     auto s2 = f(a);
        //     if (s1.first > s2.first) {
        //         a = temp;
        //     }
        // }
        // ans = f(a);
        // cout << ans.first << "\n";
        cout << ans.second.size() << "\n" << ans.second << "\n";
    }
}