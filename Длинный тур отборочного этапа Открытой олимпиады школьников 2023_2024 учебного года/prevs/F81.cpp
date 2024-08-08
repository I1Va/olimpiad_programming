#pragma gcc optimize("Ofast")
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <random>
#include <chrono>
#include <unordered_set>
#include <set>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

ostream& operator<< (ostream& stream, queue<int> a) {
    while (a.size()) {
        cout << a.front() + 1 << " ";
        a.pop();
    }
    return stream;
}

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);

int randrange(int a, int b) {
    return a + rnd() % (b - a);
}

int dest[500][500];
int g, t, n;
int questions = 0;
bool stress = 0;

bool gr[500][500];
bool opt = 0;
unordered_set<int> goods;

void TL() {
    long long mod = 1e9;
    long long a = 12454;
    for (int i = 0; i < 1e10; i++) {
        a = (a * mod) % mod;
    }
}

void print_gr() {
    vector<vector<int>> a(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (gr[i][j]) {
                a[i].push_back(j);
            } else {
                a[j].push_back(i);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ": ";
        for (auto to : a[i]) {
            cout << to + 1 << " ";
        }
        cout << "\n";
    }
}

void build() {
    goods.clear();
    n = 500;
    cout << "n = " << n << "\n";
    vector<int> cnt(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int v = randrange(0, 2);
            if (v == 1) {
                cnt[i]++;
            } else {
                cnt[j]++;
            }
            gr[i][j] = v;
            gr[j][i] = (v + 1) % 2;
        }
    }
    bool c = randrange(0, 2);
    if (c) {
        int v = randrange(0, n);
        cout << "extra good!: " << v + 1 << "\n";
        cnt[v] = 0;
        for (int i = 0; i < n; i++) {
            gr[i][v] = 1;
            gr[v][i] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        if (cnt[i] <= 1) {
            goods.insert(i);
        }
    }
    
    return;
    cout << "gr = \n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << gr[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    cout << "cnt = " << cnt << "\n";
    print_gr();
    

}

bool ask(int v, int u) {
    if (!stress && questions == 2000) {
        TL();
        // exit(1);
    }
    bool a;
    if (stress) {
        a = gr[v][u];
    } else {
        cout << "? " << v + 1 << " " << u + 1 << endl;
        string res;
        cin >> res;
        a = (res == "forward");
    }
    dest[v][u] = a;
    dest[u][v] = !a;
    questions++;
    return a;
}

void ans(int v) {
    cout << "! " << v + 1 << endl;
    if (stress) {
        bool state = false;
        if (goods.size() == 0) {
            if (v == -2) {
                state = true;
            }
        } else {
            state = (goods.find(v) != goods.end());
        }
        if (state) {
            cout << "OK";
        } else {
            cout << "WA!";
            print_gr();
            cout << goods.size() << ", good = " << *goods.begin() << "\n";
            if (opt) {
                exit(228);
            }
            
        }
    } else {
        string res;
        cin >> res;
        if (res != "OK") {
            TL();
        }
    }  
}

void solve1() {
    vector<int> cnt(n);
    for (int v = 0; v < n; v++) {
        for (int u = v + 1; u < n; u++) {
            if (ask(v, u)) {
                cnt[v]++;
            } else {
                cnt[u]++;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (cnt[i] <= 1) {
            ans(i);
            return;
        }
    }
    ans(-2);
}

void solve2() {
    int cur = 0;
    int idx = 1;
    vector<bool> used(n, false);
    used[cur] = true;
    for (int i = 1; i < n; i++) {
        if (ask(cur, i)) {
            // Вершина i ближе к концу перестановки
            cur = i;
        }
    }
    ans(cur);
}

void solve3() {
    vector<int> cnt(n);
    for (int v = 2; v < n; v++) {
        if (cnt[v] >= 2) {
            continue;
        }
        bool s0 = ask(v, 0);
        bool s1 = ask(v, 1);
        if (s0 && s1) {
            cnt[v] += 2;
            continue;
        } else if (s0) {
            cnt[v] += 1;
            cnt[1] += 1;
        } else {
            cnt[v] += 1;
            cnt[0] += 1;
        }
        for (int u = 3; u < n; u++) {
            if (ask(v, u)) {
                cnt[v] += 1;
                if (cnt[v] >= 2) {
                    break;
                }
            } else {
                cnt[u] += 1;
            }
        }
    }
}

void bad_solve() {
    vector<int> cnt(n, 0);
    vector<vector<bool>> used(n, vector<bool>(n, false));
    for (int v = 0; v < n; v++) {
        if (cnt[v] >= 2) {
            continue;
        }
        for (int u = 0; u < n; u++) {
            if (u == v || used[u][v] || used[v][u]) {
                continue;
            }
            used[v][u] = used[u][v] = true;
            bool s = ask(v, u);
            // cout << "edge: " << v + 1 << "->" << u + 1 << ": " << s << "\n";
            if (s) {
                cnt[v]++;
            } else {
                cnt[u]++;
            }
            if (cnt[v] >= 2) {
                break;
            }
        }
        if (cnt[v] <= 1) {
            ans(v);
            return;
        }
    }
    ans(-2);
}

void bad_solve2() {
    set<pair<int, int>> pool;
    for (int i = 0; i < n; i++) {
        pool.insert(make_pair(0, i));
    }
    for (int iter = 0; iter < 2000; iter++) {
        auto f = *pool.begin();
        pool.erase(pool.begin());
        auto s = * pool.begin();
        pool.erase(pool.begin());
        bool res = ask(f.second, s.second);
        if (res) {
            f = {f.first + 1, f.second};
        } else {
            s = {s.first + 1, s.second};
        }
        pool.insert(f);
        pool.insert(s);
    }
    auto cur = *pool.begin();
    if (cur.first <= 1) {
        ans(cur.second);
    } else {
        ans(-2);
    }
}

void solve81() {
    vector<int> cnt(n, 0);
    vector<vector<bool>> used(n, vector<bool>(n, false));
    for (int v = 0; v < n; v++) {
        if (cnt[v] >= 2) {
            continue;
        }
        for (int u = 0; u < n; u++) {
            if (u == v || cnt[u] >= 2 || used[v][u]) {
                continue;
            }
            if (cnt[v] >= 2) {
                break;
            }
            used[v][u] = used[u][v] = true;
            bool s = ask(v, u);
            if (s) {
                cnt[v]++;
            } else {
                cnt[u]++;
            }
        }
    }
    vector<int> good;
    for (int i = 0; i < n; i++) {
        if (cnt[i] <= 1) {
            good.push_back(i);
        }
        
    }
    int sz = (int) good.size();
    for (int i = 0; i < sz; i++) {
        if (cnt[good[i]] >= 2) {
            continue;
        }
        for (int j = 0; j < sz; j++) {
        
            if (cnt[good[j]] >= 2 || good[i] == good[j] || used[good[i]][good[j]]) {
                continue;
            }
            if (cnt[good[i]] >= 2) {
                break;
            }
            used[good[i]][good[j]] = used[good[j]][good[i]] = true;
            if (ask(good[i], good[j])) {
                cnt[good[i]]++;
            } else {
                cnt[good[j]]++;
            }
        }
    }
    good.clear();
    for (int i = 0; i < n; i++) {
        if (cnt[i] <= 1) {
            good.push_back(i);
        }
    }
    // cout << "good = " << good << "\n";
    for (auto v : good) {
        for (int i = 0; i < n; i++) {
            if (i == v || used[v][i]) {
                continue;
            }
            used[v][i] = used[i][v] = true;
            if (ask(v, i)) {
                cnt[v]++;
            } else {
                cnt[i]++;
            }
            if (cnt[v] >= 2) {
                break;
            }
        }
        if (cnt[v] <= 1) {
            ans(v);
            return;
        }
    }
    ans(-2);
}

void solve4() {
    queue<int> a;
    for (int i = 0; i < n; i++) {
        a.push(i);
    }
    vector<int> cnt(n, 0);
    vector<vector<bool>> used(n, vector<bool>(n, false));
    int cyc1 = n * 4 / 5;
    int cyc2 = n * 4 / 5;
    for (int i1 = 0; i1 < cyc1 && a.size(); i1++) {
        int cur = a.front();
        a.pop();
        bool state = true;
        for (int i2 = 0; i2 < cyc2 && a.size(); i2++) {
            int next = a.front();
            a.pop();
            if (!used[cur][next]) {
                used[cur][next] = used[next][cur] = true;
                if (ask(cur, next)) {
                    cnt[cur]++;
                } else {
                    cnt[next]++;
                }
            }
            if (cnt[next] <= 1) {
                a.push(next);
            }
            if (cnt[cur] > 1) {
                state = false;
                break;
            }  
        }
        if (state) {
            a.push(cur);
        }
    }
    // cout << "canditates.size() = " << a.size() << "\n";
    while (a.size()) {
        int cur = a.front();
        a.pop();
        for (int i = 0; i < n; i++) {
            if (cur == i || used[cur][i]) {
                continue;
            }
            used[cur][i] = used[i][cur] = true;
            if (ask(cur, i)) {
                cnt[cur]++;
            } else {
                cnt[i]++;
            }
            if (cnt[cur] > 1) {
                break;
            }
        }
        if (cnt[cur] <= 1) {
            ans(cur);
            return;
        }
    }
    ans(-2);
}

void solve5() {
    vector<int> cnt(n, 0);
    vector<vector<bool>> used(n, vector<bool>(n, false));
    vector<int> goods;
    for (int cur = 0; cur < n; cur++) {
        if (cnt[cur] > 1) {
            continue;
        }
        for (int next = 0; next < n; next++) {
            if (next == cur || cnt[next] > 1 || used[cur][next]) {
                continue;
            }
            used[cur][next] = used[next][cur] = true;
            if (ask(cur, next)) {
                cnt[cur]++;
            } else {
                cnt[next]++;
            }
            if (cnt[cur] > 1) {
                break;
            }
        }
        if (cnt[cur] <= 1) {
            goods.push_back(cur);
        }
    }
    for (auto x : goods) {
        for (int to = 0; to < n; to++) {
            if (questions == 2000) {
                ans(-2);
                return;
            }
            if (to == x || used[x][to]) {
                continue;
            }
            used[x][to] = used[to][x] = true;
            if (ask(x, to)) {
                cnt[x]++;
            } else {
                cnt[to]++;
            }
            if (cnt[x] > 1) {
                break;
            }
        }
        if (cnt[x] <= 1) {
            ans(x);
            return;
        }
    }
    ans(-2);
}

void solve_manager() {
    cin >> g >> t;
    while(t--) {
        cin >> n;
        questions = 0;
        // if (g <= 1 || n <= 63) {
        //     solve1();
        // } else if (g == 2) {
        //     solve2();
        // } else {
        //     bad_solve();
        // }
        // if (n <= 63) {
        //     solve1();
        // } else {
        //     solve81();
        // }
        solve5();
    }
}

void test_qu() {
    int mx = 0;
    for (int i = 0; i < 1000; i++) {
        questions = 0;
        build();
        solve4();
        mx = max(mx, questions);
    }
    cout << "mx = " << mx << "\n";
}

void test_wa() {
    opt = 1;
    while (1) {
        questions = 0;
        build();
        solve4();
        cout << "\n";
    }
}


int main() {
    stress = 0;
    if (!stress) {
        solve_manager();
    } else {
        test_qu();
        // test_wa();
    }
}
