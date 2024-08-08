#include <iostream>
#include <vector>
#include <string>
using namespace std;

string S, T;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to;
    }
    return stream;
}

void P_funct(const string& s, vector<int>& P) {
    P[0] = 0;
    int n = (int) s.size();
    for (int i = 1; i < n; i++) {
        int cur = P[i - 1];
        while (s[cur] != s[i] && cur > 0) {
            cur = P[cur - 1];
        }
        P[i] = cur + (int) (s[cur] == s[i]);
    }
}

int main() {
    cin >> S >> T;
    S = S + S;
    string M = T + "#" + S;
    int n = (int) M.size();
    vector<int> P(n, 0);
    P_funct(M, P);
    // cout << M << endl;
    // cout << P << endl;
    int cnt = 0;
    // cout << n - (int) S.size() / 2 << "\n";
    for (int i = (int)T.size() + 1; i < n - (int) S.size() / 2 + (int) T.size() - 1; i++) {
        if (P[i] >= (int)T.size()) {
            cout << i << "\n";
            cnt++;
        }
    }
    cout << cnt;
}