#include <iostream>
#include <vector>
using namespace std;

long long n, a, b;
vector<pair<int, int>> moves = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

int get(pair<int, int> move) {
    int x = a;
    int y = b;
    int c = 0;
    vector<bool> used(n, 0);
    int time = 0;
    while (c < n) {
        // cout << "pos: " << x << " " << y << "\n";
        if (used[x] == 2) {
            move.first *= -1;
        } else {
            c++;
            used[x] = 1;
        }
        if (used[y] == 1) {
            move.second *= -1;
        } else {
            c++;
            used[y] = 2;
        }
        x += move.first;
        y += move.second;
        x = (x + n) % n;
        y = (y + n) % n;
        time++;
    }
    return time - 1;
}

int main() {
    
    cin >> n >> a >> b;
    if (a > b) {
        swap(a, b);
    }
    a--;
    b--;
    int mn = 1e9;
    for (auto move : moves) {
        mn = min(mn, get(move));
    }
    cout << mn;
}