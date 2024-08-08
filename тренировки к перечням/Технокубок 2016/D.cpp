#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

ostream& operator<< (ostream& stream, const pair<long long, long long>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream; 
}

ostream& operator<< (ostream& stream, const vector<pair<long long, long long>>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

ostream& operator<< (ostream& stream, const vector<long long>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

bool comp(const pair<long long, long long>& a, const pair<long long, long long>& b) {
    return a.first < b.first;
}

int n;

long long get_left(const vector<pair<long long, long long>>& a) {
    // Начинаем с нулевой позиции, двигаемся вправо до i, потом до 0
    int mx = 0;
    vector<long long> left;
    left.reserve(n);
    for (int i = 0; i < n; i++) {
        if (a[i].first < 0) {
            left.push_back(a[i].second - abs(a[i].first - 0)); // Если дотащить до нуля, то сколько времени останется?
        }
    }
    sort(left.begin(), left.end());
    int cur = 0;
    int sz = (int) left.size();
    for (int i = 0; i < n; i++) {
        if (a[i].first < 0) {
            continue;
        }
        if (abs(a[i].first - 0) < a[i].second) { // Текущий цветок останется живым
            cur++;
        }
        long long time = abs(a[i].first - 0) * 2;
        auto delta = sz - (upper_bound(left.begin(), left.end(), time) - left.begin());
        // cout << a[i] << ": " << "time = " << time << ", cur = " << cur << ", left_p = " << delta << "\n";
        mx = max(mx, cur + (int) delta);
    }
    return mx;
}

long long get_right(const vector<pair<long long, long long>>& a) {
    int mx = 0;
    vector<long long> left;
    left.reserve(n);
    for (int i = 0; i < n; i++) {
        if (a[i].first > 0) {
            left.push_back(a[i].second - abs(a[i].first - 0)); // Если дотащить до нуля, то сколько времени останется?
        }
    }
    sort(left.begin(), left.end());
    // cout << "left = " << left << "\n";
    int cur = 0;
    int sz = (int) left.size();
    for (int i = 0; i < n; i++) {
        if (a[i].first > 0) {
            continue;
        }
        if (abs(a[i].first - 0) < a[i].second) { // Текущий цветок останется живым
            cur++;
        }
        long long time = abs(a[i].first - 0) * 2;
        auto delta = sz - (upper_bound(left.begin(), left.end(), time) - left.begin());
        // cout << a[i] << ": " << "time = " << time << ", cur = " << cur << ", left_p = " << delta << "\n";
        mx = max(mx, cur + (int) delta);
    }
    return mx;
}

void solve() {
    cin >> n;
    vector<pair<long long, long long>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end(), comp);
    int res1 = get_left(a);
    // cout << res1 << "\n";
    reverse(a.begin(), a.end());
    int res2 = get_right(a);
    // cout << res2 << "\n";
    int res = max(res1, res2);
    cout << max(0, res - (res % 2 == 0));
}

int main() {
    solve();

}