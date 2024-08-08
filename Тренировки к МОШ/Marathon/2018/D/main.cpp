#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

bool check(const int st_x, const int st_y, const bool& mark, const pair<int, int>& d, map<int, set<pair<int, bool>>>& mapa) {
    int x = st_x, y = st_y;
    int c = 1;
    for (int i = 0; i <= 5; i++) {
        x += d.first;
        y += d.second;
        if (mapa.find(x) != mapa.end() && mapa[x].find({y, mark}) != mapa[x].end()) {
            c++;
        } else {
            break;
        }
    }
    x = st_x, y = st_y;
    for (int i = 0; i <= 5; i++) {
        x -= d.first;
        y -= d.second;
        if (mapa.find(x) != mapa.end() && mapa[x].find({y, mark}) != mapa[x].end()) {
            c++;
        } else {
            break;
        }
    }
    return c >= 5;
}

vector<char> sim = {'X', 'O'};
vector<pair<int, int>> moves = {{1, 0}, {0, 1}, {1, 1}, {-1, 1}};

void solve() {
    int n;
    cin >> n;
    map<int, set<pair<int, bool>>> mapa;
    vector<pair<int, int>> quests(n);
    bool mark = false;
    for (int i = 0; i < n; i++) {
        cin >> quests[i].first >> quests[i].second;
    }
    for (auto to : quests) {
        int x = to.first, y = to.second;
        mapa[x].insert({y, mark});
        for (auto move : moves) {
            if (check(x, y, mark, move, mapa)) {
                cout << sim[mark];
                return;
            }
        }
        mark = !mark;
    }
    cout << "D";
}

int main() {
    // Будем поддерживать словарь сетов с координатами крестиков и ноликов
    // mapa[x] = {{y1, type}, {y2, type}, {y3, type} ... }
    // При добавлении крестика и нолика занесем информацию о нем в map. map[xi].insert({yi, typei}) 
    // Рассмотрим все прямые, по которым нужно насчитать >= 5 символов. 
    // Заметим, что переходы по этим прямым имеют вид (d_x, d_y) и (-d_x, -d_y):
    // Диагональ слева-направо: (+1, +1) / (-1, -1)
    // Диагональ справа-налево: (-1, +1) / (1, -1)
    // Горизонталь: (+1, 0) / (-1, 0)
    // Вертикаль: (0, +1) / (0, -1)
    // В функции get() будем идти по прямой в двух направлениям и 
    // проверять, что на текущей позиции стоит нужный нам символ
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}