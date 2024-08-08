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


const int sz = 200;
const int iterations = 1e9;
int field_sz;
pair<int, int> parallel;

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

int f(const vector<seg>& p) {
    if (!check(p)) {
        return 0;
    }
    vector<int> field(field_sz, 0);
    for (auto& to : p) {
        for (int x = to.l; x <= to.r; x++) {
            field[x]++;
        } 
    }
    cout << "dome";
    int ans = 0;
    int cur = 0;
    for (auto x : field) {
        if (x >= parallel.first && x <= parallel.second) {
            cur++;
        } else {
            cur = 0;
        }
        ans = max(ans, cur);
    }
    return ans;
}

pair<int, vector<seg>> random(long double prep_time, vector<seg> p) {
    clock_t start = clock();
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
    // cout << annealing(1, p);

}

int annealing(long double prep_time, long double main_time, vector<seg> p) {
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
    vector<seg> p = {
    seg(6, {0}, 1, 6),
    seg(2, {0}, 5, 6),
    seg(5, {1, 2}, 7, 11),
    seg(4, {1}, 7, 10),
    seg(7, {3}, 12, 18),
    seg(6, {4}, 11, 16),
    seg(3, {4, 5}, 19, 21),
    seg(5, {6}, 17, 21),
    seg(7, {0}, 5, 11),
    seg(6, {0}, 5, 10),
    seg(9, {9}, 12, 20),
    seg(11, {10}, 11, 21)
    };
    parallel = {4, 4};
    field_sz = 30;
    cout << f(p) << "\n";
    return 0;
    int ans = 0;
    for (int i = 0; i < 1; i++) {
        
        ans = max(ans, annealing(5, 10, p));
    }
    cout << ans;
    
}
