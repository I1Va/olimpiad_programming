#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    unordered_map<int, int> cnt;
    long long cur = 0;
    int res;
    int len = n;
    for (int i = 0; i < n; i++) {
        long long v;
        cin >> v;
        cur ^= v;
        if (cnt.find(v) == cnt.end()) {
            cnt[v] = 0;
        }
        cnt[v]++;
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            long long x;
            cin >> x;
            cnt[x]--;
            cur ^= x;
            len--;
        }
        if (t == 2) {
            long long x;
            cin >> x;
            cnt[x]++;
            cur ^= x;
            len++;
        }
        if (t == 3) {
            if (cur == 0) {
                cout << len << "\n";
            } else {
                cout << 0 << "\n";
            }
        }
    }
    
}