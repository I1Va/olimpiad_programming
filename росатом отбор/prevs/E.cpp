#include <iostream>
#include <vector>
#include <string>
using namespace std;

const long long INF = 1e9;

struct node {
    long long val;
    long long ver;
    bool state;
    node(): val{INF}, ver{-1}, state{false} {};
    node(long long val, long long ver, bool state): val{val}, ver{ver}, state{state} {};
};

ostream& operator<< (ostream& stream, node& a) {
    stream << "{" << a.val << " " << a.ver << " " << a.state << "}";
    return stream;
}

ostream& operator<< (ostream& stream, vector<node>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

void scan(vector<node>& x) {
    string s;
    cin >> s;
    for (long long i = 0; i < 3; i++) {
        x[i] = node(INF, INF, s[i] == '.');
    }
}

int main() {
    long long n;
    cin >> n;
    vector<node> prev(3);
    vector<node> cur(3);
    scan(prev);
    if (n == 1) {
        cout << "1\n0\n";
        return 0;
    }
    for (long long i = 0; i < 3; i++) {
        if (prev[i].state) {
            prev[i].val = 0;
            prev[i].ver = i + 1;
        }
    }
    for (long long c = 1; c < n; c++) {
        scan(cur);
        for (long long i = 0; i < 3; i++) {
            if (cur[i].state && prev[i].state && prev[i].val < cur[i].val) {
                cur[i] = prev[i];
            }
        }
        // //cur[0]
        // if (cur[0].state) {
        //     if (cur[1].state && cur[0].val > cur[1].val + 1) {
        //         cur[0] = cur[1];
        //         cur[0].val++;
        //     }
        // }
        // //cur[2]
        // if (cur[2].state) {
        //     if (cur[1].state && cur[2].val > cur[1].val + 1) {
        //         cur[2] = cur[1];
        //         cur[2].val++;
        //     }
        // }
        // //cur[1]
        // if (cur[1].state) {
        //     if (cur[0].state && cur[1].val > cur[0].val + 1) {
        //         cur[1] = cur[0];
        //         cur[1].val++;
        //     }
        //     if (cur[2].state && cur[1].val > cur[2].val + 1) {
        //         cur[1] = cur[2];
        //         cur[1].val++;
        //     }
        // }
        
        for (long long i = 1; i < 3; i++) {
            if (cur[i - 1].state && cur[i].state) {
                    if (cur[i].val > cur[i - 1].val + 1) {
                        cur[i] = cur[i - 1];
                        cur[i].val++;
                    }
                    if (cur[i].val == cur[i - 1].val + 1) {
                        cur[i].ver = min(cur[i].ver, cur[i - 1].ver);
                }
            }
        }
        for (long long i = 1; i >= 0; i--) {
            if (cur[i + 1].state && cur[i].state) {
                if (cur[i].val > cur[i + 1].val + 1) {
                    cur[i] = cur[i + 1];
                    cur[i].val++;
                }
                if (cur[i].val == cur[i + 1].val + 1) {
                    cur[i].ver = min(cur[i].ver, cur[i + 1].ver);
                }
            }
        }
        // cout << "cur = " << cur << "\n";
        prev = cur;
    }
    long long ans = INF;
    long long ver = INF;
    for (auto x : cur) {
        if (x.state && x.val < ans) {
            ans = x.val;
            ver = x.ver;
        }
        if (x.val == ans) {
            ver = min(ver, x.ver);
        }
    }
    if (ver == INF) {
        cout << -1;
    } else {
        cout << ver << "\n" << ans;
    }
    cout << "\n";
}