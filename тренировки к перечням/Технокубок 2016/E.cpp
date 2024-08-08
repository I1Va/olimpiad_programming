#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    int n, w, k;
    cin >> n >> w >> k;
    vector<int> cnt(n, 0);
    vector<vector<int>> used(n, vector<int>(n, 0)); 
    vector<int> lose(n, 0);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            if (cnt[i] == w) {
                break;
            }
            if (j == i && used[i][j] != 0) {
                continue;
            }
            cnt[i]++;
            lose[j]++;
            used[i][j] = 1;
            used[j][i] = -1;
        }
    }
    for (int i = 0; i < k; i++) {
        if (cnt[i] != w) {
            cout << "NO";
            return 0;
        }
    }
    // Победили ровно w раз
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j || used[i][j] != 0) {
                continue;
            }
            cnt[i]++;
            used[i][j] = 1;
            used[j][i] = -1;
            lose[j]++;
        }
    }
    // Победили все разы
    set<pair<int, int>> q;
    for (int i = 0; i < n; i++) {
        q.insert({cnt[i], i});
    }
    while (q.size()) {
        auto cur = q.begin();
        q.erase(q.begin());
        for (int i = 0; i < n; i++) {

        }
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (used[i][j] == 1) {
                cout << 1;
            } else {
                cout << 0;
            }
        }
        cout << "\n";
    }
}