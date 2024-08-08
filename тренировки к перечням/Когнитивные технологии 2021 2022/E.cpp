#include <iostream>
#include <vector>
using namespace std;

int n;

int main() {
    cin >> n;
    vector<int> T(n);
    for (int i = 0; i < n; i++) {
        cin >> T[i];
    }
    vector<int> P(n);
    for (int i = 0; i < n; i++) {
        cin >> P[i];
    }
    vector<int> F(n);
    vector<int> calc(n);
    for (int i = 0; i < n; i++) {
        cin >> F[i];
        F[i]--;
        if (F[i] == -1) {
            continue;
        }
        if (T[i] > T[F[i]] && P[i] >= 1) {
            calc[F[i]]++;
        }
    }
    int ans = 0;
    vector<int> S;
    for (int i = 0; i < n; i++) {
        if (calc[i] >= 2) {
            ans++;
            S.push_back(i + 1);
        }
    }
    cout << ans << "\n";
    for (auto to : S) {
        cout << to << " ";
    }

}