#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

ostream& operator<< (ostream& stream, const pair<int, int>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream;
}

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

ostream& operator<< (ostream& stream, priority_queue<pair<int, int>> a) {
    while (a.size()) {
        stream << a.top() << " ";
        a.pop();
    }
    return stream;
}

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a.begin(), a.end());
    priority_queue<pair<int, int>> q;
    vector<int> ans(n, 0);
    int idx = 0;
    for (auto x : a) {
        // cout << "idx: " << idx << "\n";
        // cout << "q: " << q << "\n";
        idx++;
        if (x.first == 1) {
            q.push(x);
        } else {
            int cur = x.first;
            cur--;
            priority_queue<pair<int, int>> temp;
            // cout << "q: " << q << "\n";
            while (cur > 0 && q.size()) {
                pair<int, int> v = q.top();
                q.pop();
                if (v.first <= cur) {
                    cur -= v.first;
                    ans[v.second] = x.second + 1;
                } else {
                    temp.push(v);
                }
            }
            // if (cur) {
            //     cout << cur << "\n";
            //     cout << "ERROR";
            //     exit(0);
            // }
            temp.push(x);
            while (q.size()) {
                auto v = q.top();
                q.pop();
                temp.push(v);
            }
            q = temp;
        }
    }
    cout << ans << "\n";

}
int main() {
    int q1;
    cin >> q1;
    while (q1--) {
        solve();
    }
}