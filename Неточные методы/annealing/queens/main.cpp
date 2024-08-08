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

int randrange(int a, int b) {
    return a + rnd() % (b - a);
}

const int sz = 200;
const int iterations = 1e9;

long double chance() {
    return (long double) rnd() / (long double) rnd.max();
}

long long f(const vector<int>& p) {
    int n = (int) p.size();
    vector<int> diag1(sz * 2 + 1), diag2(sz * 2 + 1);
    for (int i = 0; i < n; i++) {
        // cout << i + p[i] + sz << " " << i - p[i] + sz << "\n";
        diag1[i + p[i]]++;
        diag2[i - p[i] + sz]++;
    }
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (diag1[i + p[i]] == 1 && diag2[i - p[i] + sz] == 1) {
            c++;
        }
    }
    return c;
}

int main() {
    clock_t start = clock();
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
    shuffle(p.begin(), p.end(), rnd);
    long double t = 1;
    long long ans = f(p);
    for (int i = 0; i < iterations; i++) {
        if (iterations % 100 == 0) {
            clock_t end = clock();
            // cout << "clock: " << (double) (end - start) / CLOCKS_PER_SEC << "\n";
            if ((double) (end - start) / CLOCKS_PER_SEC >= 0.99) {
                break;
            }
        }
        t *= 0.99;
        vector<int> u = p;
        swap(u[randrange(0, n)], u[randrange(0, n)]);
        long long temp = f(u);
        if (temp > ans || chance() < exp((long double) (temp - ans) / t)) {
            p = u;
            ans = temp;
        }
    }
    // cout << "ans: " << ans << "\n";
    for (int i = 0; i < n; i++) {
        cout << p[i] + 1 << " ";
    }
}
