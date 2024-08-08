#include <iostream>
#include <vector>
#include <queue>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

int n, m;
queue<int> a;
vector<int> b;

int sz = 1e9;
vector<int> ans;

vector<int> move(int idx, const vector<int>& a) {
    vector<int> res = a;
    for (int i = 1; i <= idx; i++) {
        swap(res[i - 1], res[i]);
    }
    return res;
}

void rec(queue<int> a, vector<int> b, vector<int> path) {
    // cout << b << "\n";
    if ((int) path.size() > 8) {
        return;
    }
    if (a.empty()) {
        if ((int) path.size() < sz) {
            sz = (int) path.size();
            ans = path;
        }
        return;
    }
    if (a.front() == b[0]) {
        a.pop();
    }
    for (int i = 0; i < n; i++) {
        vector<int> new_b = move(i, b);
        path.push_back(i + 1);
        rec(a, new_b, path);
        path.pop_back();
    }
}

int main() {
    cin >> n >> m;
    b.resize(n);
    for (int i = 0; i < m; i++) {
        int t;
        cin >> t;
        a.push(t);
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    rec(a, b, {});
    cout << ans.size() << "\n";
    // cout << ans;
}
