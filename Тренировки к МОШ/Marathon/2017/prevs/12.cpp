#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}


bool comp(const pair<long long, long long>& x, const pair<long long, long long>& y) {
    return x.first * y.second > y.first * x.second;
}

struct node {
    long long val;
    int cost;
    int num;
    node(long long val, int cost, int num): val{val}, cost{cost}, num{num} {};
};

struct cmp {
    bool operator() (node a, node b) const {
        return a.val * b.cost > a.cost * b.val;
    }
};

bool comp_node(const node& a, const node& b) {
    return a.val * b.cost > a.cost * b.val;
}

int main() {
    int Q;
    cin >> Q;
    while (Q--) {
        int k, n;
        cin >> k >> n;
        vector<long long> a(n);
        node best = node(0, 1, -1);
        vector<node> layers;
        vector<node> temp;
        for (int i = 0; i < 3; i++) {
            node cur = node(0, 1, -1);
            cin >> cur.cost >> cur.val;
            cur.num = i + 1;
            if (comp_node(cur, best)) {
                best = cur;
            }
            temp.push_back(cur);
        }
        for (auto x : temp) {
            if (x.num == best.num || x.val > best.val) {
                layers.push_back(x);
            }
        }
        sort(layers.begin() + 1, layers.end(), comp_node);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<int> res(n, -1);
        long long value = 0;
        long long cost = 0;
        set<node, cmp> q;
        for (int i = 0; i < n; i++) {
            q.insert(node())
        }
        while (value < k) {
            // cout << "res: " << res << "\n";
            node best = node(0, 1, -1);
            int idx = -1;
            for (int i = 0; i < n; i++) {
                if (res[i] + 1 >= layers.size()) {
                    continue;
                }
                node temp = node(0, 1, -1);
                if (res[i] == -1) {
                    temp = 
                } else {
                    temp = node(layers[res[i] + 1].val - layers[res[i]].val, layers[res[i] + 1].cost - layers[res[i]].cost, layers[res[i] + 1].num);
                }
                if (comp_node(temp, best)) {
                    best = temp;
                    idx = i;
                }
            }
            res[idx]++;
            value += best.val;
            cost += best.cost;
        }
        // cout << cost << " " << value << "\n";
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