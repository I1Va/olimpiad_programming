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
   
    
    int f = 0;
    int s = 1;
    int idx = -1;
    for (int i = 0; i < k; i++) {
        if ((f + 1) * s >= f * (s + c[i])) {
            f += 1;
            if (idx == -1) {
                s = c[i];
            } else {
                s += c[i];
            }
            
            idx = i;
        } else {
            break;
        }
    }
    // cout << "idx = " << idx << "\n";
    for (int i = 1; i <= a[idx]; i++) {
        ans[i - 1] = 1;
    }
    for (int i = 1; i < k; i++) {
        if (ans[i - 1] < ans[i]) {
            cout << -1;
            return 0;
        }
    }
    // cout << "c = " << c << "\n";
    // cout << "ans = " << ans << "\n";
    int g = gcd(f, s);
    cout << f / g << "\n" << s / g;
}