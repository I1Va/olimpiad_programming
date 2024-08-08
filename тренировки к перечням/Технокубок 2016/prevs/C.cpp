#include <iostream>
#include <vector>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(k);
    vector<int> ans(n);
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }
    if (a[0] == 1) {
        cout << 1 << " ";
        for (int i = 1; i < n; i++) {
            cout << 0 << " ";
        }
        return 0;
    }
    int cur = 1;
    for (int i = k - 1; i > 0; i--) {
        for (int j = a[i]; j > a[i - 1]; j--) {
            ans[j - 1] = cur; 
        }
        cur++;
    }
    cout << ans << "\n";
    for (int i = a[0]; i >= 1; i--) {
        ans[i - 1] = cur;
    }
    cout << ans << "\n";
    
}