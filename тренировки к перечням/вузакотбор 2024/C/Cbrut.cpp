#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

ostream& operator<< (ostream& stream, const pair<int, int>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream;
}

bool comp(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) {
        return a.second > b.second;
    }
    return a.first < b.first;
}

int main() {
    int n, q;
    cin >> n >> q;
    vector<bool> field(n);
    for (int i = 0; i < q; i++) {
        int x, d;
        cin >> x >> d;
        x--;
        for (int j = max(0, x - d); j <= min(n - 1, x + d); j++) {
            field[j] = true;
        }
    }
    int ans = 0;
    for (auto to : field) {
        ans += to;
    }
    cout << n - ans;
}