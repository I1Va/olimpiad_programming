#include <iostream>
#include <vector>
using namespace std;

long long a, b, T;

void solve_1() {
    long long ans1 = 1, ans2 = 1;
    long long fv = 1;
    long long sv = 1;
    long long n_fv, n_sv;
    vector<long long> f = {1}, s = {1};
    // cout << fv << " " << sv << "\n";
    for (int i = 1; i <= T; i++) {
        n_fv = sv + (i % a == 0);
        n_sv = fv + (i % b == 0); 
        fv = n_fv;
        sv = n_sv;
        ans1 += fv;
        ans2 += sv;
        f.push_back(fv);
        s.push_back(sv);
        // cout << fv << " " << sv << "\n";
    }
    cout << ans1 << " " << ans2;
}

long long get(const vector<long long>& a) {
    long long res = 0;
    for (auto x : a) {
        res += x;
    }
    return res;
}

void solve_3() {
    cout << (1 + T + 1) * (T + 1) / 2 << " " << (1 + T + 1) * (T + 1) / 2;
}

void solve_2() {
    vector<long long> f(T + 1), s(T + 1);
    f[0] = s[0] = 1;
    f[1] = 1 + (1 % a == 0);
    s[1] = 1 + (1 % b == 0);
    for (int i = 2; i <= T; i++) {
        f[i] = f[i - 2] + (i % a == 0) + ((i - 1) % b == 0);
        s[i] = s[i - 2] + (i % b == 0) + ((i - 1) % a == 0);
    }
    cout << get(f) << " " << get(s);

}


int main() {
    
    cin >> a >> b >> T;
    if (a == 1 && b == 1) {
        solve_3();
        return 0;
    }
    solve_2();
}