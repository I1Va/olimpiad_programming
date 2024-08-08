#include <iostream>
#include <vector>
using namespace std;

int n, m;
const int mxt = 1e9;

vector<int> a;

bool state1() {
    return true;
}

int find_first_d(int k) {
    int d0 = (a[0] - k) / m;
    int d1 = (a[0] - k + m - 1) / m;
    int idx0 = lower_bound(a.begin(), a.end(), d0) - a.begin();
    int idx1 = lower_bound(a.begin(), a.end(), d1) - a.begin();
    if (a[idx0] - d0 + 1 <= m) {
        return d0;
    }
    return d1;
}

void solve1() {
    int ans = -1;
    for (int k = 0; k <= m - 1; k++) {
        int d = find_first_d(k);
        bool state = true;
        while (1) {
            int left = d * m + k;
            int right = (d + 1) * m + k - 1;
            int idx = lower_bound(a.begin(), a.end(), left) - a.begin();
            if (idx == n) {
                break;
            }
            if (a[idx] > right) {
                state = false;
                break;
            }
            d++;
        }
        if (state) {
            ans = k;
            break;
        }
    }
    cout << ans;
}

int main() {
    cin >> n >> m;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    if (state1) {
        solve1();
    }

}