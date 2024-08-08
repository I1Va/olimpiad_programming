#include <iostream>
#include <vector>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

bool deb = 1;

bool pull(vector<int>& p, vector<int>& idx, int obj, const int n) {    
    int cur = idx[1];
    cout << "pull 1 start: p = " << p << "\n";
    while (cur - idx[obj] < 1) {
        cout << "p = " << p << "\n";
        int jump = min(idx[obj] + n / 2, min(cur + n / 2, n));
        if (p[jump] == obj) {
            jump--;
        }
        if (jump == cur) {
            return false;
        }
        swap(idx[p[cur]], idx[p[jump]]);
        swap(p[cur], p[jump]);
    }
    cout << "pull 1 end: p = " << p << "\n";
    return true;
}


bool move(vector<int>& p, vector<int>& idx, int obj, const int n) {
    cout << "moving " << obj << "start,  p = " << p << "\n";
    while (idx[obj] != obj) {
        if (!pull(p, idx, obj, n)) {
            return false;
        } // Теперь 1 в зоне досигаемости
        swap(p[idx[1]], p[idx[obj]]);
        swap(idx[1], idx[obj]);
        cout << "p = " << p << "\n";
    }
    cout << "moving " << obj << "end,  p = " << p << "\n";
    return true;
}

void solve() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<int> p(n + 1);
    vector<int> idx(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        idx[p[i]] = i;
    }
    for (int i = n; i >= 1; i--) {
        if (!move(p, idx, i, n)) {
            cout << -1;
            return;
        }
    }

}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}