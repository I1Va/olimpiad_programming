#include <iostream>
#include <bitset>
#include <vector>
#include <immintrin.h>
using namespace std;

template<size_t Size>
size_t FindFirst(const std::bitset<Size>& rhs) {
    size_t retval;
    size_t limit;
    int index;
    uint64_t* source;
    retval = 0;
    source = (uint64_t*)std::addressof(rhs);
    limit = Size / 64;
    if (Size % 64 > 0)
        limit += 1;
    for (size_t i = 0; i != limit; ++i) {
        index = __builtin_ffsll(*source++) - 1;
        retval += index;
        if (index != 64)
            break;
    }
    return retval;
}

int n, w;
const int sz = 6250001;

int main() {
    cin >> n >> w;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    bitset<sz> prev(0), cur(0);
    vector<int> f(w + 1, -1);
    bitset<sz> now_can(0);
    prev[0] = 1;
    for (int i = 0; i < n; i++) {
        // cout << (prev << a[i]) << "\n";
        cur = (prev) | (prev << a[i]);
        now_can = cur ^ prev;
        for (int j = FindFirst(now_can); j <= w; j = now_can._Find_next(j)) {
            f[j] = i;
        }
        prev = cur;
    }
    if (!cur[w]) {
        cout << "NO";
    } else {
        cout << "YES\n";
        vector<int> ans;
        int x = w;
        while (x > 0) {
            ans.push_back(f[x] + 1);
            x -= a[f[x]];
        }
        cout << ans.size() << "\n";
        for (auto to : ans) {
            cout << to << " ";
        }
    }
    // cout << cur[w];
}
