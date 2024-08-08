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

vector<int> merge(const vector<int>& a, const vector<int>& b, int& cnt, const int& k) {
    vector<int> m;
    m.reserve(a.size() + b.size());
    int asz = (int) a.size();
    int bsz = (int) b.size();
    int ai = 0;
    int bi = 0;
    while (ai < asz && bi < bsz) {
        if (sim(a[ai], k) <= sim(b[bi], k)) {
            m.push_back(a[ai]);
            ai++;
        } else {
            cnt += asz - ai;
            m.push_back(b[bi]);
            bi++;
        }
    }
    while (bi < bsz) {
        m.push_back(b[bi]);
        bi++;
    }
    while (ai < asz) {
        m.push_back(a[ai]);
        ai++;
    }
    return m;
}

vector<int> merge_sort(const vector<int>& a, int& cnt, const int& k) {
    int n = (int) a.size();
    if (n == 1) {
        return a;
    }
    vector<int> l;
    vector<int> r;
    for (int i = 0; i < n / 2; i++) {
        l.push_back(a[i]);
    }
    for (int i = n / 2; i < n; i++) {
        r.push_back(a[i]);
    }
    return merge(merge_sort(l, cnt, k), merge_sort(r, cnt, k), cnt, k);
}

int get(const vector<int>& a) {
    int c = 0;
    int n = (int) a.size();
    for (int k = 0; k < 6; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (sim(a[i], k) > sim(a[j], k)) {
                    c++;
                }
            }
        }
    }
    return c;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int mn = 1e9;
    for (int i = 0; i <= n + 2; i++) {
        mn = min(mn, get(a));
        int v = a[0];
        a.erase(a.begin());
        a.push_back(v);
    }
    cout << mn;
}