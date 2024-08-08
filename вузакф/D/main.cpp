#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

int n, m;
int sz;

vector<vector<long long>> a;

map<char, pair<int, int>> moves;

void print(const vector<vector<bool>>& a) {
    for (auto row : a) {
        for (auto w : row) {
            cout << w << " ";
        }
        cout << "\n";
    }
}

bool out_border(int x, int y) {
    return (x < 0 || x >= n || y < 0 || y >= m);
}

long long get(const string& coms) {
    // vector<vector<bool>> b(n, vector<bool>(m));
    // b[0][0] = true;
    pair<int, int> cur = {0, 0};
    long long sum = a[0][0]; 
    for (auto x : coms) {
        cur.first += moves[x].first;
        cur.second += moves[x].second;
        if (!out_border(cur.first, cur.second)) {
            sum += a[cur.first][cur.second];
        }
        // b[cur.first][cur.second] = true;
        
    }
    return sum;
}

string trans(const string& com, int f, int s) {
    string res = "";
    for (int i = 0; i < sz; i++) {
        if (i == f) {
            continue;
        }
        res += com[i];
    }
    res.insert(res.begin() + s, com[f]);
    return res;
}

int main() {
    moves['R'] = {0, 1};
    moves['D'] = {1, 0};
    moves['L'] = {0, -1};
    moves['U'] = {-1, 0};    
    
    cin >> n >> m;
    a.resize(n);
    string com;
    for (int i = 0; i < n; i++) {
        a[i].resize(m);
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    cin >> com;
    sz = (int) com.size();
    long long mn = 1e18;
    string ans;
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            string cur = trans(com, i, j);
            long long res = get(cur);
            if (res < mn) {
                mn = res;
                ans = cur;
            }
        }
    }
    cout << ans;
    
}