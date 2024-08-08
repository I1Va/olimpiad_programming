#include <iostream>
#include <vector>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

int n;
vector<int> a;

int get(int l, int r) {
    int mn = 2 * 1e9;
    for (int i = l; i <= r; i++) {
        mn = min(mn, a[i]);
    }
    return mn;
}

int main() {
    cin >> n;
    while (n--) {
        char t;
        int i, j;
        cin >> t >> i >> j;
        if (t == '+') {
            if (a.empty()) {
                a.push_back(j);
            } else {
                a.insert(a.begin() + i, j);
            }
        } else {
            cout << get(i - 1, j - 1) << "\n";
        }
    }
}
