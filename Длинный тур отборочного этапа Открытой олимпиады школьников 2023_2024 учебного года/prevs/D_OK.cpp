#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;

ostream& operator<< (ostream& stream, const vector<long long>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

long long n, t, s;
vector<long long> a;
long long q;
const bool deb = 0;

bool comp(const long long& a, const long long& b) {
    return a > b;
}

void print(string s, const vector<long long>& a) {
    if (!deb) {
        return;
    }
    cout << s << a << "\n";
}

long long calc(long long d) {
    if (d > t) {
        return 0;
    }
    if ((t - d) % s == 0) {
        return (t - d) / s;
    }
    return (t - d) / s + 1;
}

long long calc_mi(long long x) {
    return t - calc(x) * s;
}

long long calc_mn(long long bord, long long c, const vector<long long>& b) {
    long long coun = c - calc(a[0]); // Кол-во слоев над mi
    return n - (lower_bound(b.begin(), b.end(), bord) - b.begin());
}

int main() {
    cin >> n >> t >> s;
    a.resize(n);
    for (long long i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end(), comp);
    vector<long long> b = a;
    sort(b.begin(), b.end());
    print("a = ", a);
    unordered_map<long long, long long> mins;
    long long prev = calc_mi(a[0]);
    long long cap = 1;
    long long used = 0;
    mins[prev] = 0;
    for (int i = 1; i < n; i++) {
        if (calc_mi(a[i]) == prev) {
            cap++;
            continue;
        }
        long long layers = (prev - calc_mi(a[i])) / s;
        used += min(layers, cap); // Решаем задачки для слоев layers
        cap -= min(layers, cap);
        prev = calc_mi(a[i]);
        mins[calc_mi(a[i])] = used;
        cap++;
    }
    cin >> q;
    for (long long _ = 0; _ < q; _++) {
        long long d, p;
        long long mn, mx;
        cin >> d >> p;
        p--;
        long long c = calc(d); // Кол-во слоев над mi
        if (c == 0) {
            mn = 0;
            long long cnt = (n - (lower_bound(b.begin(), b.end(), d) - b.begin())) - 1; // Кол-во задач > d
            mx = (n - (lower_bound(b.begin(), b.end(), t - cnt * s) - b.begin())) - 1;
        } else {
            long long mi = calc_mi(d);
            mn = mins[mi];
            long long cnt = n - (lower_bound(b.begin(), b.end(), mi + s) - b.begin());
            // Решено mn задач. Слой - mi, осталось cnt - mn задач. можно опустить слой до mi - (cnt - mn) * s
            long long upper = n - (lower_bound(b.begin(), b.end(), d) - b.begin()) - 1;
            long long extra = n - ((lower_bound(b.begin(), b.end(), mi - (upper - mn) * s)) - b.begin()) - cnt - 1; // Кол-во задач перед d4
            print("low border = ", {mi - (upper - mn) * s});
            print("fir extra = ", {(long long)(n - (upper_bound(b.begin(), b.end(), mi - (upper - mn) * s) - b.begin()))});
            mx = extra + cnt;
            print("mi = ", {mi});
            print("c, cnt = ", {c, cnt});
            print("upper = ", {upper});
            print("extra = ", {extra});
            print("mn, mx = ", {mn, mx});
        }
        if (p >= mn && p <= mx) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}