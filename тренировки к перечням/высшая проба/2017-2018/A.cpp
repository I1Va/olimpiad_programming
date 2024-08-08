    #include <iostream>
    #include <vector>
    using namespace std;

    int main() {
        int n, m;
        cin >> n >> m;
        vector<int> a(m);
        vector<int> cnt(n);
        for (int i = 0; i < m; i++) {
            cin >> a[i];
            cnt[a[i] - 1]++;
        }
        int k = 0;
        for (auto to : cnt) {
            k = max(k, to);
        }
        for (auto& to : cnt) {
            to = 0;
        }
        for (auto x : a) {
            cnt[x - 1]++;
            if (cnt[x - 1] == k) {
                cout << x << "\n";
                exit(0);
            }
        }

    }