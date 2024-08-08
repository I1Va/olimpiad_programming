#include <iostream>
#include <vector>
using namespace std;

struct zone {
    int ri, ci;
    bool left, right, up, down;
    zone(int ri, int ci, bool left, bool right, bool up, bool down):
    ri{ri}, ci{ci}, left{left}, right{right}, up{up}, down{down} {};
};

ostream& operator<< (ostream& stream, const zone& a) {
    stream << "{" << a.ri << ", " << a.ci << ", " << a.left << ", " << a.right << ", " << a.up << ", " << a.down << "}";
    return stream;
}

struct answer {
    int ri, ci;
    char dest;
    answer(int ri, int ci, char dest): ri{ri}, ci{ci}, dest{dest} {};
};

int cnt(const vector<zone>& a, int dest, int r, int c) {
    // Скольким стеблям мы помешаем
    int res = 0;
    for (auto x : a) {
        if (x.ri == r && x.ci == c) {
            continue;
        }
        if (dest == 0) {
            if (x.ri == r) {
                if (x.ci <= c) {
                    res += x.left;
                    res += x.right;
                    res += x.up;
                    res += x.down;
                } else {
                    res += x.left;
                }
                continue;
            }
            if (x.ci <= c) {
                if (x.ri >= r) {
                    res += x.up;
                } else {
                    res += x.down;
                }
            }
        }
        if (dest == 1) {
            if (x.ri == r) {
                if (x.ci >= c) {
                    res += x.left;
                    res += x.right;
                    res += x.up;
                    res += x.down;
                } else {
                    res += x.right;
                }
                continue;
            }
            if (x.ci >= c) {
                if (x.ri >= r) {
                    res += x.up;
                } else {
                    res += x.down;
                }
            }
        }
        if (dest == 2) {
            if (x.ci == c) {
                if (x.ri <= r) {
                    res += x.left;
                    res += x.right;
                    res += x.up;
                    res += x.down;
                } else {
                    res += x.up;
                }
                continue;
            }
            if (x.ri <= r) {
                if (x.ci <= c) {
                    res += x.right;
                } else {
                    res += x.left;
                }
            }
        }
        if (dest == 3) {
            if (x.ci == c) {
                if (x.ri >= r) {
                    res += x.left;
                    res += x.right;
                    res += x.up;
                    res += x.down;
                } else {
                    res += x.up;
                }
                continue;
            }
            if (x.ri <= r) {
                if (x.ci <= c) {
                    res += x.right;
                } else {
                    res += x.left;
                }
            }
        }
    }
    return res;
}

void upd(vector<zone>& a, int dest, int r, int c) {
    for (auto& x : a) {
        if (x.ri == r && x.ci == c) {
            continue;
        }
        if (dest == 0) {
            if (x.ri == r) {
                if (x.ci <= c) {
                    x.left = 0;
                    x.right = 0;
                    x.up = 0;
                    x.down = 0;
                } else {
                    x.left = 0;
                }
                continue;
            }
            if (x.ci <= c) {
                if (x.ri >= r) {
                    x.up = 0;
                } else {
                    x.down = 0;
                }
            }
        }
        if (dest == 1) {
            if (x.ri == r) {
                if (x.ci >= c) {
                    x.left = 0;
                    x.right = 0;
                    x.up = 0;
                    x.down = 0;
                } else {
                    x.right = 0;
                }
                continue;
            }
            if (x.ci >= c) {
                if (x.ri >= r) {
                    x.up = 0;
                } else {
                    x.down = 0;
                }
            }
        }
        if (dest == 2) {
            if (x.ci == c) {
                if (x.ri <= r) {
                    x.left = 0;
                    x.right = 0;
                    x.up = 0;
                    x.down = 0;
                } else {
                    x.up = 0;
                }
                continue;
            }
            if (x.ri <= r) {
                if (x.ci <= c) {
                    x.right = 0;
                } else {
                    x.left = 0;
                }
            }
        }
        if (dest == 3) {
            if (x.ci == c) {
                if (x.ri >= r) {
                    x.left = 0;
                    x.right = 0;
                    x.up = 0;
                    x.down = 0;
                } else {
                    x.up = 0;
                }
                continue;
            }
            if (x.ri >= r) {
                if (x.ci <= c) {
                    x.right = 0;
                } else {
                    x.left = 0;
                }
            }
        }
    }
}

void solve() {
    int n, m, s;
    cin >> n >> m >> s;
    vector<zone> a(s, zone(0, 0, 0, 0, 0, 0));
    for (int i = 0; i < s; i++) {
        int ri, ci, li;
        cin >> ri >> ci >> li;
        ri--;
        ci--;
        a[i] = zone(ri, ci, (ci + 1) <= li, (m - ci) <= li, (ri + 1) <= li, (n - ri) <= li);
    }
    vector<bool> temp(4);
    vector<answer> answers;
    vector<char> dests = {'l', 'r', 'u', 'd'};
    while (1) {
        int mn = 1e9;
        int d = -1;
        int idx = -1;
        for (int i = 0; i < s; i++) {
            for (int dest = 0; dest < 4; dest++) {
                temp = {a[i].left, a[i].right, a[i].up, a[i].down};
                // cout << "dest = " << dest << ", " << a[i] << "\n";
                if (temp[dest]) {
                    int cur = cnt(a, dest, a[i].ri, a[i].ci);
                    // cout << "check: " << a[i] << ", dest = " << dests[dest] << "\n";
                    if (cur < mn) {
                        mn = cur;
                        idx = i;
                        d = dest;
                    }
                }
            }
        }
        // cout << a[0] << "\n";
        if (idx == -1) {
            break;
        }
        upd(a, d, a[idx].ri, a[idx].ci);
        if (d == 0) {
            a[idx].left = 0;
        }
        if (d == 1) {
            a[idx].right = 0;
        }
        if (d == 2) {
            a[idx].up = 0;
        }
        if (d == 3) {
            a[idx].down = 0;
        }
        
        answers.push_back(answer(a[idx].ri, a[idx].ci, dests[d]));
    }
    cout << answers.size() << "\n";
    for (auto to : answers) {
        cout << to.ri + 1 << " " << to.ci + 1<< " " << to.dest << "\n";
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
   
}