#include <iostream>
#include <vector>
using namespace std;

ostream& operator<< (ostream& stream, const vector<long long>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long cur = 0;
    vector<long long> ans(n);
    ans[n - 1] = 0;
    for (int ir = n - 2; ir >= 0; ir--) {
        // Нужно сделать 1 пару хорошей
        long long temp = 1e18;
        int idx = -1;
        for (int i = 1; i < n - 1; i++) {
            if (a[i - 1] + a[i] <= 0) {
                if (abs(a[i - 1] + a[i]) + 1 < temp) {
                    temp = abs(a[i - 1] + a[i]) + 1;
                    idx = i;
                }
            }
            if (a[i] + a[i + 1] <= 0) {
                if (abs(a[i + 1] + a[i]) + 1 < temp) {
                    temp = abs(a[i + 1] + a[i]) + 1;
                    idx = i;
                }
            }
        }
        cur += temp;
        a[idx] += temp;
        ans[ir] = cur;
        // cout << "bads: " << ir << ", a: " << a << "\n";
    }
    for (auto x : ans) {
        cout << x << " ";
    }
}