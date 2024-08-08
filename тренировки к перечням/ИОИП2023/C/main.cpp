#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
using namespace std;

int n, h;
vector<pair<long long, long long>> a;

bool check(long long x) {
    long long cur = a[0].second;
    long long mx = cur;
    for (int i = 1; i < n; i++) {      
        if (a[i].first - a[i - 1].first <= x) {
            cur += a[i].second;
        } else {
            cur = a[i].second;
        }
        mx = max(mx, cur);
    }
    return mx >= h;
}


int main() {
    cin >> n >> h;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i].second;
    }
    sort(a.begin(), a.end());
    long long l = -1;
    long long r = 1e18;
    while (r - l > 1) {
        long long m = (l + r) / 2;
        if (check(m)) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << r;
    

}