#include <iostream>
#include <vector>
using namespace std;

long long n, a, b;
vector<pair<int, int>> moves = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

int get(pair<int, int> move) {
    int x = a;
    int y = b;
    int c = 2;
    vector<bool> used(n, 0);
    used[a] = 1;
    used[b] = 2;
    int time = 0;
    while (1) {
        cout << "pos: " << x << " " << y << "\n";
        if (!used[x]) {
            used[x] = 1;
            c++;
        }
        if (!used[y]) {
            used[y] = 2;
            c++;
        }
        if (c == n) {
            return time;
        }
        if (used[x + move.first] == 2) {
            move.first *= -1;
        }
        if (used[y + move.second] == 1) {
            move.second *= -1;
        }
        x += move.first;
        y += move.second;
        x = (x + n) % n;
        y = (y + n) % n;
        time++;
    }
    return -1;
}

int main() {
    
    cin >> n >> a >> b;
    if (a > b) {
        swap(a, b);
    }
    a--;
    b--;
    if (a == b) {
        cout << (n - 1 + 1) / 2;
        return 0;
    }
    int mn = 1e9;
    // for (auto move : moves) {
    //     int res = get(move);
    //     if (res < mn) {
    //         mn = res;
    //         cout << "move: " << move.first << ", " << move.second << "\n";
    //     }
    //     mn = min(mn, get(move));
    // }
    // cout << mn;
    cout << get({-1, -1});
}