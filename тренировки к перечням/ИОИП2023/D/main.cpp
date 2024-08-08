#include <iostream>
#include <vector>
using namespace std;

int n;
vector<pair<long long, long long>> start;

bool state13() {
    for (auto x : start) {
        if (x.first > 1000) {
            return false;
        }
    }
    return true;
}

void solve13() {
    int task = 0;
    vector<long long> ans(n);
    vector<pair<long long, long long>> a = start;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        while (cnt < start[i].first) {
            while (a[task].first == 0) {
                task = (task + 1) % n;
            }
            a[task].first--;
            ans[i] += a[task].second;
            task = (task + 1) % n;

            cnt++;
        }
    }
    for (auto x : ans) {
        cout << x << " ";
    }
}

int main() {
    cin >> n;
    start.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> start[i].first >> start[i].second;
    }
    if (state13()) {
        solve13();
    } else if (n == 2) {

    }
    
}