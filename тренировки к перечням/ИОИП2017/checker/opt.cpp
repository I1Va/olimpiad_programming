#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

int get_first(long long x) {
    return (to_string(x)[0] - '0');
}

int get_last(long long x) {
    return (*(to_string(x).end() - 1) - '0');
}

int main() {
    // freopen("counting.in", "r", stdin), freopen("counting.out", "w", stdout);
    int g, r, b;
    cin >> g >> r >> b;
    map<long long, long long> cnt_g, cnt_r, cnt_b;
    vector<long long> ga(g), ba(b);
    vector<long long> G(10), B(10);
    vector<vector<long long>> R(10, vector<long long>(10));
    for (int i = 0; i < g; i++) {
        long long x;
        cin >> x;
        G[get_last(x)]++;
        cnt_g[x]++;
        ga[i] = x;
    }
    for (int i = 0; i < r; i++) {
        long long x;
        cin >> x;
        cnt_r[x]++;
        R[get_first(x)][get_last(x)]++;
    }
    for (int i = 0; i < b; i++) {
        long long x;
        cin >> x;
        cnt_b[x]++;
        B[get_first(x)]++;
        ba[i] = x;
    }
    long long ans = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            ans += G[i] * R[i][j] * B[j];
        }
    }
    // cout << "startans: " << ans << "\n";
    for (auto x : cnt_g) {
        if (get_first(x.first) == get_last(x.first)) {
            ans -= x.second * cnt_r[x.first] * B[get_last(x.first)];
        }
        ans -= x.second * cnt_b[x.first] * R[get_last(x.first)][get_first(x.first)];
        
    }
    for (auto x : cnt_r) {
        if (get_first(x.first) == get_last(x.first)) {
            ans -= x.second * cnt_b[x.first] * G[get_first(x.first)];
        }   
    }
    for (auto x : cnt_g) {
        if (get_first(x.first) == get_last(x.first)) {
            ans += 2 * x.second * cnt_r[x.first] * cnt_b[x.first];
        }
        
    }
    cout << ans;
}