#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <chrono>
#include <random>
#include <cmath>
using namespace std;

const long double e = 2.71828182846;
auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);

long long randrange(long long a, long long b) {
    return a + rnd() % (b - a);
}

bool chance(long double x) {
    return randrange(0, 101) <= floor(x);
}

struct lay {
    long long val;
    long long cost;
    int num;
    lay(long long val, long long cost, int num): val{val}, cost{cost}, num{num} {};
};

bool comp_lay(const lay& a, const lay& b) {
    return a.val * b.cost > a.cost * b.val;
}

ostream& operator<< (ostream& stream, const lay& a) {
    stream << "{" << a.val << ", " << a.cost << ", " << a.num << "}";
    return stream;
}

ostream& operator<< (ostream& stream, const vector<lay>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}


struct node {
    long long d_val;
    long long d_cost;
    int idx;
    node(): d_val{0}, d_cost{1}, idx{-1} {};
    node(long long d_val, long long d_cost, int idx): d_val{d_val}, d_cost{d_cost}, idx{idx} {};
};

struct cmp {
    bool operator() (node a, node b) const {
        return a.d_val * b.d_cost > a.d_cost * b.d_val;
    }
};

void upd(int idx, int s, pair<long long, long long>& par, const vector<long long>& a, const vector<lay>& layers) {
    if (s == -1) {
        par = {par.first - layers[res[idx]].value, par.second - a[idx] - layers[res[idx]].cost};
    } else {
        par = {par.first - layers[res[idx]].value + layers[res[s]].value, par.second - layers[res[idx]].cost + layers[res[s]].cost};
    }
}

// void upd(vector<int>& res, pair<long long, long long> par) {
    
//     int u1 = randrange(0, n);
//     int u2 = randrange(0, n);
//     int v = randrange(0, n);
    
    
// }
int main() {
    int Q;
    cin >> Q;
    while (Q--) {
        int k, n;
        cin >> k >> n;
        vector<long long> a(n);
        lay best = lay(0, 1, -1);
        vector<lay> layers;
        vector<lay> temp;
        for (int i = 0; i < 3; i++) {
            lay cur = lay(0, 1, -1);
            cin >> cur.cost >> cur.val;
            cur.num = i + 1;
            if (comp_lay(cur, best)) {
                best = cur;
            }
            temp.push_back(cur);
        }
        for (auto x : temp) {
            if (x.num == best.num || x.val > best.val) {
                layers.push_back(x);
            }
        }
        sort(layers.begin() + 1, layers.end(), comp_lay);
        // cout << "layers: " << layers << "\n";
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<int> res(n, -1);
        multiset<node, cmp> q;
        for (int i = 0; i < n; i++) {
            q.insert(node(layers[0].val, layers[0].cost + a[i], i));
        }
        pair<long long, long long> par;
        // cout << "sz = " << layers.size() << "\n";
        while (value < k) {
            // cout << res << ", " << q.size() << "\n";
            auto cur = *q.begin();
            q.erase(q.begin());
            tr
            res[cur.idx]++;
            if (res[cur.idx] + 1 == layers.size()) {
                continue;
            }
            q.insert(node(
                layers[res[cur.idx] + 1].val - layers[res[cur.idx]].val,
                layers[res[cur.idx] + 1].cost - layers[res[cur.idx]].cost,
                cur.idx));
        }
        // int iters = 100;
        // while (iters--) {
        //     long long
        //     vector<int> u;

        // }
        // cout << k << " " << value << "\n";
        // cout << "fin: " << res << "\n";
        for (auto x : res) {
            if (x == -1) {
                cout << 0 << " ";
            } else {
                cout << layers[x].num << " ";
            }
        }
        cout << "\n";
        
    }
}