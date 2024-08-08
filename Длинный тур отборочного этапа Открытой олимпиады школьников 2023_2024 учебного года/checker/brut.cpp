#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

struct qu {
    int t, l, r, k, v;
    qu(): t{-1}, l{-1}, r{-1}, k{-1}, v{-1} {}
    qu(int t, int l, int r, int k, int v): t{t}, l{l}, r{r}, k{k}, v{v} {}
};

int n, q;
const int sz = 7;
vector<int> a;
vector<qu> quests;

void print_bit(int x) {
    cout << bitset<sz>(x) << "\n";
}

bool state1() {
    return n <= 10 && q <= 1000;
}

void solve1() {
    for (auto cur : quests)  {
        if (cur.t == 1) {
            for (int i = cur.l; i <= cur.r; i++) {
                a[i ^ cur.k] = cur.v;
            }
        } else {
            long long sum = 0;
            for (int i = cur.l; i <= cur.r; i++) {
                sum += a[i ^ cur.k];
            }
            cout << sum << "\n";
        }
    }
}

// Несданная подгруппа(2)

bool state2() {
    if (n > 17 || q > 2 * 1e5) {
        return false;
    }
    for (auto to : quests) {
        if (to.t == 1) {
            if (to.l != to.r) {
                return false;
            }
        }
        if (__builtin_popcount(to.k) != 1) {
            return false;
        }
    }
    return true;
}

int bit_idx(int x) {
    int left = 0;
    int right = 20;
    while (right - left > 1) {
        int mid = (left + right) / 2;
        if ((1 << mid) > x) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return left;
}

int next_idx(int x, int idx) {
    return (x | (1 << idx) - 1);
}

long long get(int l, int r) {
    long long sum = 0;
    for (int i = l; i <= r; i++) {
        sum += a[i];
    }
    return sum;
}

void solve2() {
    for (auto to : quests) {
        int t, l, r, k, v;
        t = to.t, l = to.l, r = to.r, k = to.k, v = to.v;
        if (t == 1) {
            a[l ^ k] = v;
        } else {
            int ki = bit_idx(k);
            int cur = l ^ k;
            int next = next_idx(l, ki);
            long long sum = 0;
            while (1) {
                bool end = false;
                if (next >= r) {
                    next = r;
                    end = true;
                }
                
                sum += get(cur, next);

                if (end) {
                    break;
                }
                cur = next + 1;
                next = next_idx(cur, ki);       
            }
            cout << sum << "\n";
        }
    }
}

void solve_manager() {
    cin >> n;
    a.resize((1 << n));
    for (int i = 0; i < (1 << n); i++) {
        cin >> a[i];
    }
    cin >> q;
    quests.resize(q);
    for (int i = 0; i < q; i++) {
        int t, l, r, k, v = -1;
        cin >> t >> l >> r >> k;
        if (t == 1) {
            cin >> v;
        }
        quests[i] = qu(t, l, r, k, v);
    }
    // if (state1) {
    //     solve1();
    // } else if (state2) {
    //     solve2();
    // } else {
    //     exit(1);
    // }
    solve1();
}

void perebor(int l, int r, int k) {
    cout << "\nperebor:\n";
    for (int i = l; i <= r; i++) {
        cout << (i ^ k) << "\n";
    }
}

void test() {
    int left = 7;
    int right = 76;
    int ki = 4;
    int k = 1 << ki;
    cout << "ki = \n";
    int cur = left;
    print_bit(k);
    cout << "\n";
    int next = next_idx(left, ki);
    int c = 0;
    while (1) {
        bool state = false;
        if (next >= right) {
            next = right;
            state = true;
        }
        // cout << "[" << cur << ":" << next << "]\n";
        cout << "[" << (cur ^ k) << ":" << (next ^ k) << "]\n";
        c++;
        if (state) {
            break;
        }
        cur = next + 1;
        next = next_idx(cur, ki);
    }
    cout << "c = " << c << "\n";
    // perebor(left, right, k);
}

int main() {
    solve_manager();
}
