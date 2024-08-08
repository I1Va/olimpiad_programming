#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

bool comp(const pair<int, string>& a, const pair<int, string>& b) {
    return a.first > b.first;
}

int n, m, k;

bool check(const string& a, const string& b) {
    int c = 0;
    int n = (int) a.size();
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            c++;
        }
    }
    return c <= k;
}

int main() {
  
    string s, t;
    cin >> n >> m >> k;
    cin >> s >> t;
    map<string, int> cnt;
    for (int i = 0; i <= m - n; i++) {
        string cur = "";
        for (int j = i; j < i + n; j++) {
            cur += t[j];
        }
        if (cnt.find(cur) == cnt.end()) {
            cnt[cur] = 0;
        }
        cnt[cur]++;
    }
    vector<pair<int, string>> p;
    p.reserve(cnt.size());
    for (auto to : cnt) {
        // cout << to.first << ": " << to.second << "\n";
        p.push_back({to.second, to.first});
    }
    sort(p.begin(), p.end(), comp);
    for (auto cur : p) {
        if (check(s, cur.second)) {
            cout << cur.first;
            return 0;
        }
    }
    cout << 0;
}