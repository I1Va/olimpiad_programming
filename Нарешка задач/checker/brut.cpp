#include <iostream>
#include <vector>
using namespace std;

ostream& operator<< (ostream& stream, const pair<long long, long long>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream;
}

ostream& operator<< (ostream& stream, const vector<pair<long long, long long>>& a) {
    for (auto x : a) {
        stream << x << " ";
    }
    return stream;
}

const long long INF = 1e18;

void rec(int l, int r, long long cur, bool& ans, const int& n, const vector<long long>& a) {
    if (r == n || l == -1) {
        ans = true;
        return;
    }
    if (cur + a[l] >= 0) {
        rec(l - 1, r, cur + a[l], ans, n, a);
    }
    if (cur + a[r] >= 0) {
        rec(l, r + 1, cur + a[r], ans, n, a);
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        k--;
        bool ans = false;
        rec(k - 1, k + 1, a[k], ans, n, a);
        if (ans) {
            cout << "YES\n"; 
        } else {
            cout << "NO\n";
        }
        
    }
}