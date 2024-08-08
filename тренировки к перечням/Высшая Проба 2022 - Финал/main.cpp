#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <numeric>
#include <algorithm>
using namespace std;

long long get_sum(long long x) {
    long long res = 0;
    while (x > 1) {
        bool state = true;
        for (long long i = 2; i <= (long long) sqrt(x); i++) {
            if (x % i == 0) {
                res += i;
                x /= i;
                state = false;
                break;
            }
        }
        if (state && x > 1) {
            res += x;
            x = 1;
        }
    }
    return res;
}

void get(map<long long, long long>& div, long long x) {
    while (x > 1) {
        bool state = true;
        for (long long i = 2; i <= (long long) sqrt(x); i++) {
            if (x % i == 0) {
                div[i]++;
                x /= i;
                state = false;
                break;
            }
        }
        if (state && x > 1) {
            div[x]++;
            x = 1;
        }
    }
}

void print(const map<long long, long long>& div) {
    auto it = div.end();
    it--;
    while (1) {
        cout << it -> first << ": " << it -> second << "\n";
        if (it == div.begin()) {
            break;
        }
        it--;
    }
}

bool comp(long long a, long long b) {
    return a > b;
}

bool check(long long S, const vector<long long>& a, const vector<map<long long, long long>>& divs, const vector<vector<long long>>& dividers, const long long n, long long k) {
    for (long long i = 0; i < n; i++) {
        if (a[i] <= S) {
            return true;
        }
        int l = -1;
        int r = (int) dividers[i].size() - 1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (a[i] / dividers[i][m] <= S) {
                r = m;
            } else {
                l = m;
            }
        }
        k -= get_sum(dividers[i][r]);
        if (k < 0) {
            return false;
        }
    }
    return true;
}

void build(vector<long long>& dividers, long long x) {
    for (int i = 1; i <= sqrt(x); i++) {
        if (x % i == 0) {
            dividers.push_back(i);
            if (i * i != x) {
                dividers.push_back(x / i);
            }
        }
    }
    sort(dividers.begin(), dividers.end());
}

int main() {
    long long n, k;
    cin >> n >> k;
    vector<long long> a(n);
    vector<map<long long, long long>> divs(n);
    vector<vector<long long>> divisors(n);
    long long mx = 0;
    for (long long i = 0; i < n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    sort(a.begin(), a.end(), comp);
    for (long long i = 0; i < n; i++) {
        get(divs[i], a[i]);
        build(divisors[i], a[i]);
    }
    long long l = 0;
    long long r = mx;
    while (r - l > 1) {
        long long m = (l + r) / 2;
        if (check(m, a, divs, divisors, n, k)) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << r;
}