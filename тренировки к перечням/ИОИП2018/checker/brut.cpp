#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long maxn = 1e2;

void cuter(vector<long long> p, vector<pair<int, long long>> r, bool& ans) {
    if (r[0].first == 0 && r[1].first == 0) {
        ans = true;
        return;
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            if (p[j] - r[i].second >= 0 && r[i].first) {
                p[j] -= r[i].second;
                r[i].first--;
                cuter(p, r, ans);
                p[j] += r[i].second;
                r[i].first++;
            }
        }
    }
}

int main() {
    long long a, b, c, d;
    cin >> a >> b >> c >> d;
    long long S = 0;
    pair<long long, long long> ans = {0, 0};
    for (long long fir = 1; fir <= maxn; fir++) {
        for (long long sec = 1; sec <= maxn; sec++) {
            bool cur = false;
            cuter({a, b, c, d}, {{2, fir}, {2, sec}}, cur);
            if (cur && fir * sec > S) {
                S = fir * sec;
                ans = {fir, sec};
            }
        }
    }
    cout << ans.first * ans.second;
}