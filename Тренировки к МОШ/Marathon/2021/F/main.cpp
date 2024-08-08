#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

ostream& operator<< (ostream& stream, const pair<long long, long long>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream;
}

bool comp_less(pair<long long, long long> a, pair<long long, long long> b) {
    return (long double) a.first / a.second < (long double) b.first / b.second;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<long long> a(n), s(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> s[i];
    }
    sort(a.begin(), a.end());
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    vector<pair<long long, long long>> ans(m);
    
    for (int j = 0; j < m; j++) {
        if (sum >= s[j]) {
            ans[j] = {0, 1};
            continue;
        }
        long long aval = sum;
        long long xc = 0;
        pair<long long, long long> val = {1, 0};
        for (int i = 0; i < n; i++) {
            // x >= a[i]
            // x < a[i + 1]
            aval -= 2 * a[i];
            xc += 2;
            pair<long long, long long> cur = {s[j] - aval, xc};
            // long long g = gcd(cur.first, cur.second);
            // cur = {cur.first / g, cur.second / g};
            if (comp_less(cur, val)) {
                val = cur;
            }
            // cout << i << "| xc: " << xc << ", aval: " << aval << ", val: " << cur << "\n";
        }
        ans[j] = val;
    }
    for (auto to : ans) {
        cout << to.first << " " << to.second << "\n";
    }
    cout << "\n";
}

int main() {
    // отсортим массив a по возрастанию.
    // для каждого sj:
    // будем итерироваться по индексу i < n, с инвариантом
    // x >= a[i]
    // x < a[i + 1]
    // Данный инвариант позволяет понять, как какие модули раскроются(с + или c -)
    // Исходя из этого можно легко поддерживать кол-во x (xc) и сумму ai (aval) для неравенства:
    // xc * x + aval >= sj
    // => x = (sj - aval) / (xc)
    // Обратите внимание на возможное переполнение типа long long. 
    
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}