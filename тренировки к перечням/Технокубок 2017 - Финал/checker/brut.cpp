#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <unordered_set>
#include <map>
using namespace std;

ostream& operator<< (ostream& stream, const vector<string>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

string emp;
int main() {
    int n;
    cin >> n;
    vector<string> a(n), b(n);
    for (int i = 0; i < n; i++) {
        string temp1, temp2;
        cin >> temp1 >> temp2;
        a[i] = emp + temp1[0] + temp1[1] + temp1[2];
        b[i] = emp + temp1[0] + temp1[1] + temp2[0];
    }
    // cout << a << "\n" << b << "\n";
    set<string> used;
    vector<string> ans(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            if (a[i] == a[j]) {
                ans[i] = b[i];
                ans[j] = b[j];
                used.insert(b[i]);
                used.insert(b[j]);
            }
        }
    }
    // for (int i = 0; i < n; i++) {
    //     cout << "ans[" << i << "] = " << ans[i] << "\n";
    //     if (i == n - 1) {
    //         cout << "\n";
    //     }
    // }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            if (a[i] == b[j]) {
                ans[i] = b[i];
                used.insert(b[i]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (ans[i] == "") {
            ans[i] = a[i];
            used.insert(ans[i]);
        }
    }
    if (used.size() != n) {
        cout << "NO";
    } else {
        cout << "YES\n";
        // for (auto x : ans) {
        //     cout << x << "\n";
        // }
    }



}