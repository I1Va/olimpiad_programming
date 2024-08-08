#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int get(int i, int j, const vector<vector<int>>& a) {
    vector<int> p = {
        a[i - 1][j - 1], a[i - 1][j], a[i - 1][j + 1],
        a[i][j - 1], a[i][j], a[i][j + 1],
        a[i + 1][j - 1], a[i + 1][j], a[i + 1][j + 1]
    };  
    sort(p.begin(), p.end());
    return p[4];
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n)), res(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            res[i][j] = a[i][j];
        }
    }
    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < n - 1; j++) {
            res[i][j] = get(i, j, a);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << res[i][j] << " ";
        }
        cout << "\n";
    }
}