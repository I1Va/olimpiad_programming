#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <deque>
#include <random>
#include <chrono>
#define x first
#define y second
using namespace std;

void solve();
int cnt_test = 0;

int main() {
    // freopen("d2.txt", "r", stdin);
    std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	int t = 1;
	cin >> t;
	while (t--) {
        //cout << cnt_test + 1 << endl;
        solve();
        cnt_test += 1;
	}
}

int n, m, k;

int pp[2200][30];

vector<pair<int, int>> e;

deque<int> drop;

vector<int> cl_p;

int color[100000];

int pnt[110000];

set<int> ss[11010];

auto now = chrono::high_resolution_clock().now().time_since_epoch().count();
mt19937 rng(now);

vector<int> get(int l, int r) {
    vector<int> res;
    res.reserve(r - l + 1);
    for (int i = l; i <= r; i++) {
        res.push_back(i);
    }
    shuffle(res.begin(), res.end(), rng);
    return res;
}

void solve() {
    e.clear();
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 30; ++j) {
            pp[i][j] = 0;
        }
        pnt[i] = 0;
        ss[i].clear();
    }
    int x, y;
    for (int i = 0; i < m; ++i) {
        color[i] = 0;
        cin >> x >> y;
        --x;
        --y;
        pnt[x] += 1;
        pnt[y] += 1;
        if (x > y) {
            swap(x, y);
        }
        e.push_back({x, y});
    }
    /*if (cnt_test == 9 || cnt_test == 10 || cnt_test == 11 || cnt_test == 12) {
        return;
    }*/
    bool ff;
    for (int i : get(0, m - 1)) {
        ff = false;
        for (int j : get(1, k + 1)) {
            if (pp[e[i].x][j] != 0 || pp[e[i].y][j] != 0) {
                continue;
            }
            ff = true;
            color[i] = j;
            pp[e[i].x][j] = i + 1;
            pp[e[i].y][j] = i + 1;
            break;
        }
        if (!ff) {
            drop.push_back(i);
        }
    }
    int cl, tind;
    while (drop.size() > 0) {
        int t = drop.front();
        drop.pop_front();
        ff = false;
        for (int j : get(1, k + 1)) {
            if (pp[e[t].x][j] != 0 || pp[e[t].y][j] != 0) {
                continue;
            }
            ff = true;
            color[t] = j;
            pp[e[t].x][j] = t + 1;
            pp[e[t].y][j] = t + 1;
            break;
        }
        if (ff) {
            continue;
        }
        cl_p.clear();
        for (int j : get(1, k + 1)) {
            if (pp[e[t].x][j] != 0 && pp[e[t].y][j] != 0)
                continue;
            cl_p.push_back(j);
        }
        shuffle(cl_p.begin(), cl_p.end(), rng);
        cl = cl_p[0];
        color[t] = cl;
        if (pp[e[t].x][cl] != 0) {
            tind = pp[e[t].x][cl] - 1;
            color[tind] = 0;
            pp[e[tind].x][cl] = 0;
            pp[e[tind].y][cl] = 0;
            drop.push_back(tind);
        }
        pp[e[t].x][cl] = t + 1;
        if (pp[e[t].y][cl] != 0) {
            tind = pp[e[t].y][cl] - 1;
            color[tind] = 0;
            pp[e[tind].x][cl] = 0;
            pp[e[tind].y][cl] = 0;
            drop.push_back(tind);
        }
        pp[e[t].y][cl] = t + 1;
    }
    for (int i = 0; i < m; ++i) {
        cout << color[i] << ' ';
        ss[e[i].x].insert(color[i]);
        ss[e[i].y].insert(color[i]);
    }
    cout << '\n';
    //проверка корректности ответа
    for (int i = 0; i < n; ++i) {
        if (ss[i].size() != pnt[i]) {
            cout << "No";
            exit(0);
        }
    }
}

/*
Разбор:
Воспользуемся методом рандомизированного перебора с отсечениями
Будем жадно красить ребра в любой цвет пока можем, затем у нас остануться ребра которые нельзя покрасить
Тогда заведем очередь и положим туда все эти ребра, когда мы достаем, то выбираем рандомный цвет,
а все ребра которые нам мешают мы кидаем в очередь и так пока очередь не пустая, в итоге мы получим нужный нам ответ
*/
