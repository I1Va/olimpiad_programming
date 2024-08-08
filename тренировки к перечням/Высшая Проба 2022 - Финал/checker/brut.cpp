#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define ll long long

signed main() {
    ll n, k;
    cin >> n >> k;
    vector <ll> a(n);
    for (int i = 0; i < n; cin >> a[i++]);
    unordered_map <ll, vector <ll>> divisors;
    ll mx = 0;
    for (auto i : a) {
        mx = max(mx, i);
        if (divisors.find(i) != divisors.end()) {
            continue;
        }
        for (int j = 1; j * j <= i; ++j) {
            if (i % j)
                continue;
            divisors[i].push_back(j);
            if (j * j == i)
                continue;
            divisors[i].push_back(i / j);
        }
        sort(divisors[i].begin(), divisors[i].end());
    }
    vector <ll> sum(mx + 1, 0);
    for (ll d = 2; d <= mx; ++d) {
        if (sum[d]) {
            continue;
        }
        sum[d] = d;
        for (ll i = d + d; i <= mx; i += d) {
            ll num = 0, b = i;
            while (b % d == 0) {
                ++num;
                b /= d;
            }
            sum[i] += num * d;
        }
    }
    unordered_map <ll, vector <ll>> divisors_cost;
    for (auto &i : divisors) {
        divisors_cost[i.first].resize(i.second.size());
        for (ll j = i.second.size() - 1; j >= 0; --j) {
            divisors_cost[i.first][j] = sum[i.second[j]];
            if (j != i.second.size() - 1) {
                divisors_cost[i.first][j] = min(divisors_cost[i.first][j], divisors_cost[i.first][j + 1]);
            }
        }
    }
    ll l = 1, r = mx, ans = mx;
    while (l <= r) {
        ll mid = (l + r) / 2;
        ll sm = 0;
        for (auto i : a) {
            if (i <= mid) 
                continue;
            ll l1 = 0, r1 = (ll) divisors[i].size() - 1, ans1 = (ll) divisors[i].size() - 1;
            while (l1 <= r1) {
                ll mid1 = (l1 + r1) / 2;
                if (i / divisors[i][mid1] <= mid) {
                    ans1 = mid1;
                    r1 = mid1 - 1;
                }
                else {
                    l1 = mid1 + 1;
                }
            }
            sm += divisors_cost[i][ans1];
        }
        if (sm <= k) {
            ans = mid;
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    cout << ans;
}