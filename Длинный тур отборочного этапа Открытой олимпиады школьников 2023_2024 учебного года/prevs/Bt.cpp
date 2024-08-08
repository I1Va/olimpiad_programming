#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <unordered_set>
#include <chrono>
#include <random>
#include <string>
using namespace std;

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);

long long randrange(long long a, long long b) {
    return a + rnd() % (b - a);
}

ostream& operator<< (ostream& stream, const vector<long long>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

const int sz = 11;

void print(string s, int x) {
    cout << s << bitset<sz>(x) << "\n";
}

int split(const vector<long long>& a, bool bin) {
    long long left = a[0];
    long long cur = a[0];
    long long cnt = 0;
    for (int i = 1; i < (int) a.size(); i++) {
        int x = a[i];
        if (x == cur + 1) {
            cur++;
            continue;
        }
        if (bin) {
            cout << "[" << bitset<sz>(left) << ": " << bitset<sz>(cur) << "]\n";
        } else {
            cout << "[" << left << ": " << cur << "]\n";
        }
        
        cnt++;
        left = x;
        cur = x;
    }
    if (left != cur) {
        if (bin) {
            cout << "[" << bitset<sz>(left) << ": " << bitset<sz>(cur) << "]\n";
        } else {
            cout << "[" << left << ": " << cur << "]\n";
        }
    }
    return cnt;
}

int test(long long left, long long k, long long right, bool bin) {
    cout << "left = " << left << ", right = " << right << ", k = " << k << "\n";
    print("k:=", k);
    print("l:=", left);
    print("r:=", right);
    vector<long long> q;
    // unordered_set<long long> s;
    for (long long i = left; i <= right; i++) {
        q.push_back(i ^ k);
        // s.insert(i ^ k);
    }
    // if (q.size() != s.size()) {
    //     cout << "!!!!";
    //     exit(0);
    // }
    sort(q.begin(), q.end());
    // cout << "q = " << q << "\n";
    return split(q, bin);
}

void analyze() {
    long long mx = 0;
    int m = 100;
    int maxn = (1 << 20);
    for (int i = 0; i < m; i++) {
        // cout << i << "\n";
        long long left = randrange(0, maxn);
        long long right = randrange(left, maxn);
        long long k = randrange(0, maxn);
        long long ans = test(left, k, right, false);
        cout << i << ": " << left << " " << k << " " << right << ": " << ans << "\n\n";
        mx = max(mx, ans);
    }
    cout << mx;   
}

int main() {
    int left = randrange(1, 100);
    int right = randrange(left, 100);
    int k = (1 << 4);
    test(left, k, right, true);
}