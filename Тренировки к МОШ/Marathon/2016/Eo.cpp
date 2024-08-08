#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct node {
    long long M;
    long long P;
    int num;
    int cnt;
    node(long long M, long long P, int num, int cnt): M{M}, P{P}, num{num}, cnt{cnt} {};
};

int n, k;

bool comp_M(const node& a, const node& b) {
    if (a.cnt == n / k) {
        return false;
    }
    if (b.cnt == n / k) {
        return true;
    }
    return a.M < b.M;
}

bool comp_P(const node& a, const node& b) {
    if (a.cnt == n / k) {
        return false;
    }
    if (b.cnt == n / k) {
        return true;
    }
    return a.P < b.P;
}

long long f(long long x, long long y) {
    return x + y;
}

bool comp_all(const node& a, const node& b) {
    return f(a.P, a.M) > f(b.P, b.M);
}


int main() {
   
    cin >> n >> k;
    vector<node> a(n, node(0, 0, 0, 0));
    vector<node> g(k, node(0, 0, 0, 0));
    for (int i = 0; i < k; i++) {
        g[i].num = i;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i].M >> a[i].P;
        a[i].num = i;
    }
    sort(a.begin(), a.end(), comp_all);
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        node cur = a[i];
        if (cur.M > cur.P) {
            sort(g.begin(), g.end(), comp_M);
        } else {
            sort(g.begin(), g.end(), comp_P);
        }
        g[0] = node(g[0].M + cur.M, g[0].P + cur.P, g[0].num, g[0].cnt + 1);
        ans[cur.num] = g[0].num + 1;
    }
    for (auto x : ans) {
        cout << x << "\n";
    }
}