// Created by Nikolay Budin

#ifdef DEBUG
#  define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define ff first
#define ss second
#define szof(x) ((int)x.size())
#ifndef LOCAL
#  define cerr __get_ce
#endif

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef unsigned long long ull;

using namespace __gnu_pbds;
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V> using ordered_map = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF = (int)1e9 + 1e3;
ll const INFL = (ll)1e18 + 1e6;
#ifdef LOCAL
	mt19937 tw(9450189);
#else
	mt19937 tw(chrono::high_resolution_clock::now().time_since_epoch().count());
#endif
uniform_int_distribution<ll> ll_distr;
ll rnd(ll a, ll b) { return ll_distr(tw) % (b - a + 1) + a; }

const int P = 239;
const int MOD = 1'000'000'007;

void add(int& a, int b) {
	a += b;
	if (a >= MOD) {
		a -= MOD;
	}
}

int sum(int a, int b) {
	add(a, b);
	return a;
}

int mult(int a, int b) {
	return (ll) a * b % MOD;
}

vector<int> calc_arrh(string const& s) {
	vector<int> ret = {0};
	for (char c : s) {
		ret.push_back(sum(mult(ret.back(), P), c));
	}
	return ret;
}

vector<int> pp = {1};

int get_hash(vector<int> const& arrh, int l, int r) {
	return sum(arrh[r], MOD - mult(pp[r - l], arrh[l]));
}

void solve() {
	int n, m;
	cin >> n >> m;
	vector<string> arrw;
	int len = 0;
	for (int i = 0; i < n; ++i) {
		string w;
		cin >> w;
		len = __gcd(len, szof(w));
		arrw.push_back(w);
	}
	for (int i = 0; i < m; ++i) {
		int a;
		cin >> a;
		len = __gcd(len, a);
	}

	gp_hash_table<int, char> all_hashes;
	for (auto& w : arrw) {
		auto tmp = calc_arrh(w);
		for (int i = len; i <= szof(w); i += len) {
			all_hashes.insert({tmp[i], 0});
		}
	}

	int q;
	cin >> q;
	for (int i = 0; i < q; ++i) {
		string t;
		cin >> t;
		if (szof(t) % len != 0) {
			cout << "No\n";
			continue;
		}
		auto arrh_t = calc_arrh(t);
		int last = szof(t);
		for (int j = szof(t) - len; j >= 0; j -= len) {
			if (all_hashes.find(get_hash(arrh_t, j, last)) != all_hashes.end()) {
				last = j;
			}
		}

		if (last == 0) {
			cout << "Yes\n";
		} else {
			cout << "No\n";
		}
	}
}


int main() {
#ifdef LOCAL
	auto start_time = clock();
	cerr << setprecision(3) << fixed;
#endif
	cout << setprecision(15) << fixed;
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	for (int i = 0; i < 1e6 + 5; ++i) {
		pp.push_back(mult(pp.back(), P));
	}

	int test_count = 1;
	// cin >> test_count;
	for (int test = 1; test <= test_count; ++test) {
		solve();
	}

#ifdef LOCAL
	auto end_time = clock();
	cerr << "Execution time: " << (end_time - start_time) * (int)1e3 / CLOCKS_PER_SEC << " ms\n";
#endif
}