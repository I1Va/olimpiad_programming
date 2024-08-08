#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

long long n, h, q;

bool ask1(int i, int x) {
    cout << "- " << i + 1 << " " << x << endl;
    string res;
    cin >> res;
    if (res == "-1") {
        exit(1);
    }
    return res == "OK";
}

bool answer(int x) {
    cout << "! " << x << endl;
    string res;
    cin >> res;
    if (res == "-1") {
        exit(1);
    }
    return res == "OK";
}

void solve1() {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        while (1) {
            if (ask1(i, 1)) {
                ans++;
            } else {
                break;
            }
        }
    }
    if (!answer(ans)) {
        exit(1);
    }
}

void solve2() {
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        long long x = 1;
        while (x * 2ll <= h) {
            x *= 2ll;
        }
        for (long long p = x; p >= 1; p /= 2) {
            if (ask1(i, p)) {
                ans += p;
            }
        }
    }
    if (!answer(ans)) {
        exit(1);
    }
}

void solve() {
	long long ans = 0;
	for (int i = 0; i < n; ++i) {
		int bp = 1;
		while (bp * 2 <= h) {
			bp *= 2;
		}
		for (int p = bp; p >= 1; p /= 2) {
			cout << "- " << i + 1 << " " << p << endl;
			string res;
			cin >> res;
			if (res == "OK") {
				ans += p;
			}
			if (res == "-1") {
				exit(0);
			}
		}
	}
	cout << "! " << ans << endl;
	string res;
	cin >> res;
	if (res == "-1") {
		exit(0);
	}
}

int main() {
    int t;
    cin >> t;
    cin >> n >> h >> q;
    while (t--) {
        solve();
    }
}