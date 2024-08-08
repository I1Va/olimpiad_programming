#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>
using namespace std;

int n;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

ostream& operator<< (ostream& stream, const pair<int, int>& a) {
    cout << "{" << a.first << " " << a.second << "}";
    return stream;
}

ostream& operator<< (ostream& stream, const vector<pair<int, int>>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

bool comp1(const pair<int, int>& a, const pair<int, int>& b) {
    return a.first > b.first;
}

bool comp2(int a, int b) {
    return a > b;
}

bool comp_bin(int val, pair<int, int> elem) {
    return elem.first >= val;
}

long long ans = 0;
int coun, heig, width;

void relax(long long cur, int h, int w) {
    if (cur * h > ans) {
        ans = cur * h;
        coun = cur;
        heig = h;
        width = w;
    }
}

int main() {
    cin >> n;
    vector<int> a(n);
    map<int, int> cnt;
    vector<int> b;
    vector<pair<int, int>> c;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    for (auto to : cnt) {
        c.push_back({to.second, to.first});
        b.push_back(to.first);
    }
    sort(c.begin(), c.end(), comp1);
    sort(b.begin(), b.end(), comp2);
    // for (auto to : cnt) {
    //         cout << to.first << ": " << to.second << "\n";
    // }
    // cout << "c = " << c << "\n";
    // cout << "b = " << b << "\n";

    for (int h : b) {
        // Выбрали высоту. Нужно выбрать ширину. 
        // Спичек, отвечающих за ширину в идеале должно быть>= cnt[h] - 1
        // Также можно разделить кол-во спичек h пополам и сложить башню из них
        for (int i = 0; i < min((int) c.size(), 2); i++) {
            long long cur;
            if (c[i].second == h) {
                cur = (cnt[h] - 1) / 3;
                relax(cur, h, h);
            } else {
                cur = min(c[i].first - 1, cnt[h] / 2);
                relax(cur, h, c[i].second);
            }
            // cout << make_pair(cnt[h], h) << ", " << c[i] << ", cur = " << cur << "\n";
        }
        // cout << h << ", idx: " <<
    }

    if (ans == 0) {
        cout << "-1 -1 -1";
    } else {
        cout << coun << " " << heig << " " << width;
    }
}