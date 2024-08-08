#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <set>
#include <cmath>
#include <map>
#include <stdio.h>
#include <time.h>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);

long double chance() {
    return (long double) rnd() / (long double) rnd.max();
}

int randrange(int a, int b) {
    return a + rnd() % (b - a);
}

struct seg {
    int len;
    int l, r;
    vector<int> con;
    seg() {}
    seg(int _len, vector<int> _con, int _l = -1, int _r = -1) {
        len = _len;
        con = _con;
        l = _l;
        r = _r;
    }
    void rebuild() {
        l = randrange(0, field_sz - len + 1);
        r = l + len - 1;
    }
};









//#######################################
// VARIABLES
const int sz = 200;
const int iterations = 1e9;
const int field_sz = 50;
const int iterations = 1;
const long double prep_time = 10;   
const long double main_time = 30;
pair<int, int> parallel = {4, 4};
vector<seg> p = {
    seg(4, {0}),
    seg(3, {0}),
    seg(5, {1, 2}),
    seg(7, {3}),
    seg(6, {3}),
    seg(2, {5}),
    seg(9, {0})
};
//#######################################











ostream& operator << (ostream& stream, const seg& a) {
    stream << "{" << a.l << ", " << a.r << "}";
    return stream;
}

ostream& operator << (ostream& stream, const vector<seg>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

void build(vector<seg>& p) {
    for (auto& to : p) {
        to.rebuild();
    }
}

void change(vector<seg>& p) {
    for (int i = 0; i < 2; i++) {
        int idx = randrange(0, (int) p.size());
        p[idx].rebuild();
    }
}

bool check(const vector<seg>& p) {
    for (auto& to : p) {
        for (auto& prev : to.con) {
            if (prev == 0) {
                continue;
            }
            if (to.l <= p[prev - 1].r) {
                return false;
            }
        }
    }
    return true;
}

bool comp(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.first == b.first) {
        return a.second > b.second;
    }
    return a.first < b.first;
}

int f(const vector<seg>& p) {
    if (!check(p)) {
        return 0;
    }
    vector<pair<int, int>> field;
    field.reserve(p.size() * 2);
    for (auto& to : p) {
        field.push_back({to.l, 1});
        field.push_back({to.r + 1, -1});
    }
    sort(field.begin(), field.end(), comp);
    int ans = 0;
    pair<int, bool> prev = {field[0].first, 0};
    int cur = 0;
    int idx = 0;
    while (idx < (int) field.size()) {
        int pos = field[idx].first;
        cur += field[idx].second;
        auto to = field[idx];
        idx += 1;
        while (idx < (int) field.size() && field[idx].first == pos) {
            cur += field[idx].second;
            idx++;
        }
        
        if (cur >= parallel.first && cur <= parallel.second) {
            if (!prev.second) {
                prev.first = to.first;
                prev.second = true;
            }
            ans = max(ans, to.first - prev.first + 1);
        } else {
            if (prev.second) {
                ans = max(ans, to.first - prev.first);
            }
            prev = {to.first, false};
        }
        // cout << "prev: " << prev.first << "/" << prev.second << ", " << to.first << ": " << cur << "\n";
    }
    return ans;
}

pair<int, vector<seg>> random(long double prep_time, vector<seg> p) {
    clock_t start = clock();
    build(p);
    pair<int, vector<seg>> ans = {f(p), p};
    for (int i = 0; i >= 0; i++) {
        if (i % 100 == 0) {
            clock_t end = clock();
            if ((double) (end - start) / CLOCKS_PER_SEC >= prep_time) {
                break;
            }
        }
        build(p);
        // cout << p << "\n";
        // cout << f(p);
        int cur = f(p);
        if (cur > ans.first) {
            ans = {cur, p};
            // cout << ans.first << "\n";
        }
        // break;
        // cout << f(p) << "\n";
    }
    return ans;
    // cout << ans.first << "\n" << ans.second;
    // cout << magic(1, p);

}

int magic(long double prep_time, long double main_time, vector<seg> p) {
    clock_t start = clock();
    p = random(prep_time, p).second;
    long double t = 1;
    long long ans = f(p);
    for (int i = 0; i >= 0; i++) {
        if (i % 100 == 0) {
            clock_t end = clock();
            if ((double) (end - start) / CLOCKS_PER_SEC >= main_time) {
                break;
            }
        }
        t *= 0.99;
        vector<seg> u = p;
        change(u);
        long long temp = f(u);
        // cout << temp << "\n";
        if (temp > ans || chance() < exp((long double) (temp - ans) / t)) {
            p = u;
            ans = temp;
        }
    }
    return ans;
}

int main() {
    build(p);
    int ans = 0;
    for (int i = 0; i < 1; i++) {
        ans = max(ans, magic(10, 30, p));
    }
    cout << ans;
    
}
