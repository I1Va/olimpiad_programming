#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <unordered_map>
using namespace std;

int n, k, q;

int main() {
    cin >> n >> k >> q;
    vector<vector<int>> a(k);
    for (int i = 0; i < k; i++) {
        int s;
        cin >> s;
        a[i].resize(s);
        for (int j = 0; j < s; j++) {
            cin >> a[i][j];
        }
    }
    vector<pair<int, int>> b(q);
    multiset<int> next;
    for (int i = 0; i < q; i++) {
        cin >> b[i].first >> b[i].second;
        if (b[i].first == 1) {
            next.insert(b[i].second);
        }
    }
    int ans = 0;
    vector<pair<int, int>> path;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < (int) a[i].size(); j++) {
            if (next.find(a[i][j]) != next.end()) {
                for (int x = 0; x < (int) a[i].size() - j; x++) {
                    ans++;
                    path.push_back({3, i + 1});
                }
                break;
            }
        }
    }
    // Все тарелки, которые будут использоваться далее в запросах помыты
    for (int i = 0; i < q; i++) {
        if (b[i].first == 2) {
            path.push_back({2, 1});
            if (next.find(b[i].second) != next.end()) {
                // Помоем сразу
                ans++;
                path.push_back({3, 1});
            }
        } else {
            next.erase(next.find(b[i].second));
            path.push_back({1, -1});
        }
    }
    cout << ans << "\n";
    for (auto to : path) {
        if (to.first == 1) {
            cout << 1 << "\n";
        } else {
            cout << to.first << " " << to.second << "\n";
        }
    }
}