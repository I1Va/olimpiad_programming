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
vector<long long> a;
vector<long long> val;
const bool deb = 0;

struct node {
    int last;
    long long cnt;
    bool end;
    node(): last{-1}, cnt{-1}, end{true} {}
    node(int last, long long cnt, bool end): last{last}, cnt{cnt}, end{end} {}
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
        dp[sz - 1] = node(num * k + sz - 1, val[num * k + sz - 1], true);
        for (int i = sz - 2; i >= 0; i--) {
            if (i + a[i + num * k] >= sz) {
                dp[i] = node(num * k + i, val[num * k + i], true);
            } else {
                dp[i] = node(dp[i + a[i + num * k]].last, val[num * k + i] + dp[i + a[i + num * k]].cnt, false);
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
        dp[sz - 1] = node(num * k + sz - 1, val[num * k + sz - 1], true);
        for (int i = sz - 2; i >= 0; i--) {
            if (i + a[i + num * k] >= sz) {
                dp[i] = node(num * k + i, val[num * k + i], true);
            } else {
                dp[i] = node(dp[i + a[i + num * k]].last, val[num * k + i] + dp[i + a[i + num * k]].cnt, false);
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

pair<int, long long> get(int cur, vector<block>& blocks, const int n) {
    long long cnt = 0;
    int last = 0;
    while (1) {
        auto& x = blocks[cur / k];
        if (x.changed != -1) {
            x.rebuild();
            x.changed = -1;
        }
        last = cur;
        int prev_cur = cur;
        long long prev_cnt = cnt;
        
        if (x.dp[cur % k].end) {
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
    cin >> n;
    
    k = 200;
    c = (n + k - 1) / k;
    a.resize(n, 1);
    val.resize(n);
    vector<long long> questions(n - 1);
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }
    for (int i = 0; i < n - 1; i++) {
        cin >> questions[i];    
    }
    vector<block> blocks(c);
    for (int i = 0; i < c; i++) {
        blocks[i] = block(i);
    }
    print(blocks);
    cin >> m;
    for (int i = 0; i < m; i++) {
        int v;
        cin >> v;
        a[v - 1] = questions[v - 1];
        blocks[i / k].changed = max(blocks[i / k].changed, i % k);
        blocks[i / k].rebuild();
        blocks[i / k].changed = -1;
        print(blocks);
        auto res = get(0, blocks, n);
        cout << res.second << "\n";
        
    }
}
