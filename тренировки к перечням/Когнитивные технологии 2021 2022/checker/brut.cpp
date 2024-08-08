#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

long long ans;
int c, height, width;

void relax(long long cur, long long h, long long w) {
    if (cur * h > ans) {
        ans = cur * h;
        c = cur;
        height = h;
        width = w;
    }
}

void finish() {
    if (ans == 0) {
        cout << "-1 -1 -1";
    } else {
        cout << c << " " << height << " " << width;
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    unordered_map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    
    for (auto h : cnt) {
        for (auto w : cnt) {
            if (h.first == w.first) {
                relax((h.second - 1) / 3, h.first, w.first);
            } else {
                long long cur = min(w.second - 1, h.second / 2);
                relax(cur, h.first, w.first);
            }
        }
    }
    finish();
}