#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>
#include <cmath>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

const int INF = 1e9;

int gcd (int a, int b) {
	while (b) {
		a %= b;
		swap (a, b);
	}
	return a;
}

bool check(int a, int b, int n) {
    for (int i = 0; i < n; i++) {
        bool state = true;
        for (int j = i; j < i + n; j++) {
            if (((a >> (j - i)) & 1) != ((b >> (j % n)) & 1)) {
                state = false;
                break;
            }
        }
        if (state) {
            return true;
        }
    }
    return false;
}

int count(vector<int> p, int n) {
    unordered_set<int> buf;
    vector<int> f(n, INF);
    int num = 0;
    for (auto cur : p) {
        for (int s = 0; s < n; s++) {
            int col = INF;
            int cnt = 0;
            for (int i = s; i < n; i += cur) {
                col = min(col, f[i]);
                cnt++;
            }
            if (cnt < 2) {
                continue;
            }
            if (col == INF) {
                col = num++;
            }
            for (int i = s; i < n; i += cur) {
                f[i] = col;
            }
        }
        
    }
    buf.clear();
    int c = 0;
    for (auto to : f) {
        if (to == INF) {
            c++;
        } else {
            buf.insert(to);
        }
        
    }
    // cout << "f = " << f << "\n"; 
    return (int) buf.size() + c;
}

int get(int p) {
    unordered_set<int> pool;
    for (int mask = 0; mask < (1 << p); mask++) {
        bool state = true;
        for (auto to : pool) {
            if (check(mask, to, p)) {
                state = false;
                break;
            }
        }
        if (state) {
            pool.insert(mask);
        }
    }
    return pool.size();
}

int n_count(int a, int b, int c) {
    int f = (a * b) / gcd(a, b);
    return (f * c) / gcd(f, c);
}

map<int, int> fact(int x) {
    map<int, int> res;
    while (x > 1) {
        for (int i = 2; i <= x; i++) {
            if (x % i == 0) {
                if (res.find(i) == res.end()) {
                    res[i] = 0;
                }
                res[i]++;
                x /= i;
                break;
            }
        }
    }
    return res;
}

int nok(int a, int b, int c) {
    map<int, int> res = fact(a);
    auto fb = fact(b);
    auto fc = fact(c);
    for (auto to : fb) {
        res[to.first] = max(res[to.first], to.second);
    }
    for (auto to : fc) {
        res[to.first] = max(res[to.first], to.second);
    }
    int ans = 1;
    for (auto to : res) {
        ans *= pow(to.first, to.second);
    }
    return ans;
}

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    int n = nok(a, b, c);
    // cout << count({a, b}, n + 1) << "\n";
    cout << get(count({a, b}, n + 1)) - get(count({a, b, c}, n + 1));
    // cout << n << ": " << count({a, b}, n + 1);
}
