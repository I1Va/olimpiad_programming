#include <iostream>
#include <vector>
using namespace std;

ostream& operator<< (ostream& stream, const vector<long long>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

int n;
long long A, B;
long long ans = 1e18;

void upd(vector<long long>& t, int idx, long long B, long long A) {
    for (int i = 0; i < n; i++) {
        if (i == idx) {
            t[i] -= A;
        } else {
            t[i] -= B;
        }
    }
}

void rec(long long cur, vector<long long> t) {
    // cout << "t = " << t << "\n";
    bool state = true;
    for (int i = 0; i < n; i++) {
        if (t[i] >= 0) {
            state = false;
            break;
        }
    }
    if (state) {
        ans = min(ans, cur);
        return;
    }
    for (int i = 0; i < n; i++) {
        vector<long long> c = t;
        upd(c, i, B, A);
        rec(cur + 1, c);
    }

}

int main() {
    cin >> n >> A >> B;
    vector<long long> t(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }
    rec(0, t);
    cout << ans;
}