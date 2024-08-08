#pragma GCC optimize("Ofast")
#include <iostream>
#include <vector>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

ostream& operator<< (ostream& stream, const pair<int, int>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream;
}

int n, m;
int k;
int c;
vector<int> a;
const bool deb = 0;

struct node {
    int last;
    int cnt;
    bool end;
    node(): last{-1}, cnt{-1}, end{true} {}
    node(int last, int cnt, bool end): last{last}, cnt{cnt}, end{end} {}
};

ostream& operator<< (ostream& stream, const node& a) {
    stream << "{" << a.last << ", " << a.cnt << ", " << a.end << "}";
    return stream;
}

struct block {
    int num;
    int sz;
    int changed;
    vector<node> dp;
    block(): num{-1}, sz{0}, changed{-1} {};
    block(int x) {
        num = x;
        sz = min(k, n - num * k);
        dp.resize(sz);
        // cout << "num = " << num << ", b = " << b << "\n";
        dp[sz - 1] = node(num * k + sz - 1, 0, true);
        for (int i = sz - 2; i >= 0; i--) {
            if (i + a[i + num * k] >= sz) {
                dp[i] = node(num * k + i, 0, true);
            } else {
                dp[i] = node(dp[i + a[i + num * k]].last, dp[i + a[i + num * k]].cnt + 1, false);
            }
        }
    }
    void print_b(bool new_line) {
        for (int i = num * k; i < min(n, (num + 1) * k); i++) {
            cout << a[i] << " ";
        }
        if (new_line) {
            cout << "\n";
        }
    }
    void print_dp(bool new_line) {
        for (auto to : dp) {
            cout << to << " ";
        }
        if (new_line) {
            cout << "\n";
        }
    }
    void rebuild() {
        if (changed == sz - 1) {
            dp[sz - 1] = node(num * k + sz - 1, 0, true);
            changed--;
        }
        for (int i = changed; i >= 0; i--) {
            if (i + a[i + num * k] >= sz) {
                dp[i] = node(num * k + i, 0, true);
            } else {
                dp[i] = node(dp[i + a[i + num * k]].last, dp[i + a[i + num * k]].cnt + 1, false);
            }
        }
    }
};

void print_jump(int v1, int v2, int v3, int v4, int v5) {
    if (!deb) {
        return;
    }
    cout << "jump[" << v1 << " " << v2 << "] -> " << "[" << v3 << " " << v4 << "], end = " << v5 << "\n";
}

void print(vector<block>& blocks) {
    if (!deb) {
        return;
    }
    for (int i = 0; i < c; i++) {
        blocks[i].print_b(0);
        cout << "| ";
    }
    cout << "\n";
    for (int i = 0; i < c; i++) {
        blocks[i].print_dp(0);
        cout << "| ";
    }
    cout << "\n";
}

pair<int, int> get(int cur, vector<block>& blocks, const int n) {
    int cnt = 0;
    int last = 0;
    while (1) {
        auto& x = blocks[cur / k];
        if (x.changed != -1) {
            x.rebuild();
            x.changed = -1;
        }
        last = cur;
        int prev_cur = cur;
        int prev_cnt = cnt;
        if (x.dp[cur % k].end) {
            cnt++;
            cur += a[cur];
        } else {
            cnt += x.dp[cur % k].cnt;
            cur = x.dp[cur % k].last;
        }
        print_jump(prev_cur, prev_cnt, cur, cnt, x.dp[cur % k].end);
        if (cur >= n) {
            break;
        }
    }
    return {last, cnt};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    k = 200;
    c = (n + k - 1) / k;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<block> blocks(c);
    for (int i = 0; i < c; i++) {
        blocks[i] = block(i);
    }
    print(blocks);
    while (m--) {
        int t;
        cin >> t;
        if (t == 0) {
            int f, s;
            cin >> f >> s;
            f--;
            a[f] = s;
            blocks[f / k].changed = max(blocks[f / k].changed, f % k);
        } else {
            int f;
            cin >> f;
            auto res = get(f - 1, blocks, n);
            cout << res.first + 1 << " " << res.second << "\n";
        }
        print(blocks);
    }
}
