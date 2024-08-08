#include <iostream>
#include <vector>
#include <queue>
using namespace std;

ostream& operator<< (ostream& stream, queue<int> a) {
    while (!a.empty()) {
        cout << a.front() << " ";
        a.pop();
    }
    return stream;
}

ostream& operator<< (ostream& stream, vector<int> a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

int n, m;
vector<int> a, b;

bool state1() {
    if (n != m) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

void solve1() {
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        cout << n << " ";
    }
}

bool state2() {
    if (n != m) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        if (a[i] != b[n - i - 1]) {
            return false;
        }
    }
    return true;
}

void solve2() {
    cout << n - 1 + n << "\n";
    for (int i = 0; i < n - 1; i++) {
        cout << n - i << " ";
    }
    for (int i = 0; i < n; i++) {
        cout << n << " ";
    }
}

void solve() {
    vector<int> num(n + 1); // num[w] - позиция карты w в очереди
    for (int i = 0; i < n; i++) {
        num[b[i]] = i;
    }
    vector<int> ans;
    int idx = 0;
    while (idx < m) {
        if (a[idx] == b[0]) {
            idx++;
        }
        int pos = 0;
        bool state = false;
        for (int j = idx; j < m; j++) {
            if (a[j] == b[0]) {
                state = true;
                break;
            }
            pos = max(pos, num[a[j]]);
        }
        if (!state) { // Не встретили
            pos = n - 1;
        }
        // Переместим нулевой элемент на позицию pos
        ans.push_back(pos + 1);
        for (int j = 1; j <= pos; j++) {
            swap(b[j - 1], b[j]);
        }
        for (int j = 0; j < n; j++) {
            num[b[j]] = j;
        }
    }
    cout << ans.size() << "\n";
    // cout << ans;
}

int main() {
    cin >> n >> m;
    a.resize(m), b.resize(n);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    // if (state1) {
    //     solve1();
    // } else if (state2) {
    //     solve2();
    // } else {
    //     solve();
    // }
    solve();
    
}