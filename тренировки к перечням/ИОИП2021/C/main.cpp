#pragma GCC optimaze("Ofast")
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

int sim(int x, int k) {
    return to_string(x)[k] - '0';
}

void merge(int l1, int r1, int l2, int r2, int& cnt, vector<int>& a) {
    vector<int> m;
    m.reserve(r1 - l1 + r2 - l2);
    int ai = l1;
    int bi = l2;
    while (ai < r1 && bi < r2) {
        if (a[ai] <= a[bi]) {
            m.push_back(a[ai]);
            ai++;
        } else {
            cnt += r1 - l1 - ai;
            m.push_back(a[bi]);
            bi++;
        }
    }
    while (bi < r2) {
        m.push_back(a[bi]);
        bi++;
    }
    while (ai < r1) {
        m.push_back(a[ai]);
        ai++;
    }
    for (int i = l1; i < r2; i++) {
        a[i] = m[i - l1];
    }
}

void merge_sort(int l, int r, int& cnt, vector<int>& a) {
    if (r - l <= 1) {
        return;
    }
    int m = (l + r) / 2;
    merge_sort(l, m, cnt, a);
    merge_sort(m, r, cnt, a);
    merge(l, m, m, r, cnt, a);
}

int get(const vector<string>& a) {
    int cnt = 0;
    int n = (int) a.size();
    for (int k = 0; k < 6; k++) {
        vector<int> temp(n);
        for (int i = 0; i < n; i++) {
            temp[i] = a[i][k] - '0';
            merge_sort(0, n, cnt, temp);
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<string> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int mn = 1e9;
    for (int i = 0; i <= n + 2; i++) {
        mn = min(mn, get(a));
        string v = a[0];
        a.erase(a.begin());
        a.push_back(v);
    }
    cout << mn;
}