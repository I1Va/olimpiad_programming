#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct node {
    int A, B;
    int num;
    node(): A{0}, B{0}, num{-1} {}
    node(int A, int B, int num): A{A}, B{B}, num{num} {}
};

int n;
vector<node> a;

bool comp(const node& a, const node& b) {
    return a.A < b.A;
}

void print(vector<node> a) {
    cout << "cur =\n";
    for (auto to : a) {
        cout << "{" << to.A << " " << to.B << "}\n";
    }
    cout << "\n";
}

void upd(const vector<node>& cur, int& mx, vector<node>& ans) {
    vector<int> field(101, -1);
    int cnt = 0;
    for (auto e : cur) {
        if (e.A == -1 && e.B == -1) {
            continue;
        }
        for (int x = e.A; x <= e.B; x++) {
            if (field[x] != -1) {
                return;
            }
            field[x] = e.num;
            cnt++;
        }
    }
    if (cnt < mx) {
        return;
    }
    // print(cur);
    mx = cnt;
    ans = cur;
}

void rec(vector<node> cur, int idx, int& mx, vector<node>& ans) {
    if (idx == n) {
        upd(cur, mx, ans);
        return;
    }
    cur[idx] = node(-1, -1, cur[idx].num);
    rec(cur, idx + 1, mx, ans);
    for (int Ai = a[idx].A; Ai <= a[idx].B; Ai++) {
        for (int Bi = Ai; Bi <= a[idx].B; Bi++) {
            cur[idx] = node(Ai, Bi, cur[idx].num);
            rec(cur, idx + 1, mx, ans);
        }
    }
}

void brut_solve() {
    int mx = 0;
    vector<node> ans(n);
    rec(a, 0, mx, ans);
    for (auto to : ans) {
        cout << to.A << " " << to.B << "\n";
    }
}

void solve() {
    sort(a.begin(), a.end(), comp);
    vector<pair<int, int>> ans(n, {-1, -1});
    node cur = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i].B > cur.B) {
            ans[cur.num] = {cur.A, a[i].A - 1};
            cur = a[i];
        }
    }
    ans[cur.num] = {cur.A, cur.B};
    // cout << "ANS =\n";
    for (auto to : ans) {
        cout << to.first << " " << to.second << "\n";
    }
}

int main() {
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].A >> a[i].B;
        a[i].num = i;
    }
    solve();
    // brut_solve();
}