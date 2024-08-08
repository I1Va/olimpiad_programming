#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
using namespace std;

string emp;

int main() {
    int n;
    cin >> n;
    vector<vector<string>> a(n, vector<string>(2));
    for (int i = 0; i < n; i++) {
        string s1, s2;
        cin >> s1 >> s2;
        a[i][0] = emp + s1[0] + s1[1] + s1[2];
        a[i][1] = emp + s1[0] + s1[1] + s2[0];
    }
    for (long long mask = 0; mask < (1ll << n); mask++) {
        bool state = true;
        for (int i = 0; i < n; i++) {
            if (!state) {
                break;
            }
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }
                int idx1 = ((mask >> i) & 1);
                int idx2 = ((mask >> j) & 1);
                if (a[i][idx1] == a[j][idx2] || (idx1 == 1 && idx2 == 0 && a[j][idx2] == a[i][0])) {
                    state = false;
                    break;
                }
            }
        }
        if (state) {
            cout << "YES\n";
            for (int i = 0; i < n; i++) {
                cout << a[i][(mask >> i) & 1] << "\n";
            }
            return 0;
        }
    }
    cout << "NO";
}