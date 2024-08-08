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
    map<string, vector<int>> line1;
    set<string> line2;
    for (int i = 0; i < n; i++) {
        line1[a[i]].push_back(i);
    }
    for (auto x : line1) {
        if (x.second.size() != 1) {
            for (auto y : x.second) {
                ans[y] = b[y];
                used.insert(b[y]);
                line2.insert(b[y]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (ans[i] == "" && line2.find(a[i]) != line2.end()) {
            line2.insert(b[i]);
            ans[i] = b[i];
            used.insert(b[i]);
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