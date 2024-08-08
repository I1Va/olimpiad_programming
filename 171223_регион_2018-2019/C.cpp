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

struct node {
    int num;
    int l, r;
    node(): num{-1}, l{-1}, r{-1} {}
    node(int num, int l, int r): num{num}, l{l}, r{r} {}
};

int n, m;
vector<int> a;
queue<int> b;

int main() {
    cin >> n >> m;
    a.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        b.push(c);
    }
    vector<int> k;
    vector<bool> used(n + 1, false);
    vector<queue<int>> next(n + 1);
    for (int x : a) {
        if (!used[x]) {
            while (1) {
                int cur = b.front();
                bool end = cur == x;
                used[cur] = true;
                b.pop();
                next[cur].push(k.size());
                k.push_back(cur);
                if (end) {
                    break;
                }
            }
        } else {
            next[x].push(k.size());
            k.push_back(x);
        }
    }
    cout << k << "\n";
    vector<node> q;
    vector<int> ans(k.size());
    for (int i = 0; i < (int) k.size(); i++) {-
        if (next[k[i]].empty()) {
            ans[i] = n;
        } else {
            q.push_back(node(i, ))
        }
    }
    
    
    
}
