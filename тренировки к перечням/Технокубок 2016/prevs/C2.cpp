#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

struct node {
    long long f, s;
    node(): f{0}, s{1} {};
    node(long long f, long long s): f{f}, s{s} {};
};

bool comp(const node& a, const node& b) {
    return a.f * b.s > b.f * a.s;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(k);
    vector<int> ans(n);
    vector<int> c(k);
    for (int i = 0; i < k; i++) {
        cin >> a[i];
        if (i == 0) {
            c[i] = a[i] - 0;
        } else {
            c[i] = a[i] - a[i - 1];
        }
    }
   
    
    node best = node(0, 1);
    int idx = -1;
    
    node cur = node(0, 0);
    for (int i = 0; i < k; i++) {
        cur.f++;
        cur.s += c[i];
        if (comp(cur, best)) {
            best = cur;
            idx = i;
        }
    }
    // cout << "idx = " << idx << "\n";
    for (int i = 1; i <= a[idx]; i++) {
        ans[i - 1] = 1;
    }
    // cout << "c = " << c << "\n";
    cout << ans << "\n";
    // int g = gcd(f, s);
    // cout << f / g << "\n" << s / g;
}