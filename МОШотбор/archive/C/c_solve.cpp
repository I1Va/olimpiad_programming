#include <iostream>
#include <map>
#include <bitset>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
using namespace std;

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);


void solve();

const int MAXN = 20000000;

bitset<MAXN> pred[100];

int dp[2][MAXN];

int main() {
    //freopen("c1.txt", "r", stdin);// для первых тестов на 30
    freopen("c2.txt", "r", stdin);// для вторых тестов на 70
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	int t;
	cin >> t;
	while (t--) {
        solve();
	}
}

vector<int> pans;

void solve() {
    int n;
    cin >> n;
    vector<pair<long long, long long>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i].second;
    }
    // shuffle(a.begin(), a.end(), rnd);
    fill(dp[0], dp[0] + MAXN, 0);
    dp[0][MAXN / 2] = 1;
    int ans = 0;
    int ff, ss;
    for (int i = 1; i <= n; ++i) {
        ff = i % 2;
        ss = (i + 1) % 2;
        fill(dp[ff], dp[ff] + MAXN, 0);
        for (int k = 0; k < MAXN; ++k) {
            if (dp[ss][k] == 0) {
                continue;
            }
            if (dp[ff][k] < dp[ss][k]) {
                dp[ff][k] = dp[ss][k];
                pred[i][k] = 0;
            }
            if (dp[ff][k + (a[i - 1].second - a[i - 1].first)] < dp[ss][k] + (a[i - 1].first + a[i - 1].second)) {
                dp[ff][k + (a[i - 1].second - a[i - 1].first)] = dp[ss][k] + (a[i - 1].first + a[i - 1].second);
                pred[i][k + (a[i - 1].second - a[i - 1].first)] = 1;
            }
        }
        ans = max(ans, dp[ff][MAXN / 2] - 1);
    }
    pans.clear();
    int k = MAXN / 2;
    for (int i = n; i >= 0; --i) {
        if (pred[i][k] == 0) {
            continue;
        }
        pans.push_back(i);
        k -= (a[i - 1].second - a[i - 1].first);
    }
    sort(pans.begin(), pans.end());
    cout << pans.size() << endl;
    for (auto i : pans) {
        cout << i << ' ';
    }
    cout << endl;
}

/*
Разбор:

Применим технику динамического программирования:
заведем динамику dp[n][k] - где первое измерение - это рассмотренный префикс урожая, а второе -
это полученная разность(корешков и вершков) после рассмотрения префикса длины n. dp[n][k] - максимальная сумма урожая
1. Начальные значения: dp[0][10000000] = 1, берем такое большое k, чтобы не уйти в отрицательный индекс, также ставим 1,
чтобы понимать, что мы можем пересчитаться отсюда(рассмотрели 0 урожаев и разность сейчас 0)
2. Переходы:
dp[i][j + (b[i] - a[i])] = max(dp[i - 1][j] + a[i] + b[i], dp[i][j + (b[i] - a[i])]) этот переход означает, что мы взяли в ответ i урожай
dp[i][j] = max(dp[i][j], dp[i - 1][j]) мы не взяли i урожай соответственно
3. Ответ лежит в dp[n][10000000]
Делаем банальную технику восстановление ответа 0/1
Оптимизация для решения на 70:
1. Будем хранить 2 слоя вместо n, потому что всегда пересчитваемся от предыдущего
2. Сделаем массив предков таким bitset<MAXN> pred[100],чтобы съэкономить память(MAXN=20'000'000)
*/
