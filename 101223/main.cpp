#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int n, m;
vector<int> p;
vector<int> h;
vector<deque<int>> d;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

ostream& operator<< (ostream& stream, deque<int> a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

void print() {
    for (int i = 1; i <= n; i++) {
        cout << i << ": " << d[i] << "\n";
    }
}

int act(int d1) {
    if (p[d1] == d1) {
        return h[d1];
    }
    return h[d1] = act(p[d1]) + 1;
}

void dsu_push_back(int d1, int d2) {
    d[d2].push_back(d1);
    p[d1] = d2;
    act(d1);
}

void dsu_push_front(int d1, int d2) {
    d[d2].push_front(d1);
    p[d1] = d2;
    act(d1);
}

void dsu_pop_back(int d1) {
    int cur = d[d1].back();
    h[cur] = 0;
    d[d1].pop_back();
    p[cur] = cur;
}

void dsu_pop_front(int d1) {
    int cur = d[d1].front();
    h[cur] = 0;
    d[d1].pop_front();
    p[cur] = cur;
}



int idx(int d1) {
    int idx = 0;
    for (auto to : d[p[d1]]) {
        if (to == d1) {
            return idx;
        }
        idx++;
    }
    return -1;
}

int get(int a) {
    if (p[a] == a) {
        return 0;
    }
    return min((int) d[p[a]].size() - idx(a), idx(a) + 1) + get(p[a]);
}

int main() {
    cin >> n >> m;
    p.resize(n + 1), d.resize(n + 1), h.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        p[i] = i;
        h[i] = 0;
    }
    while (m--) {
        string t;
        cin >> t;
        if (t == "push_back") {
            int d1, d2;
            cin >> d1 >> d2;
            dsu_push_back(d1, d2);
        }
        if (t == "push_front") {
            int d1, d2;
            cin >> d1 >> d2;
            dsu_push_front(d1, d2);
        }
        if (t == "pop_back") {
            int d1;
            cin >> d1;
            dsu_pop_back(d1);
        }
        if (t == "pop_front") {
            int d1;
            cin >> d1;
            dsu_pop_front(d1);
        }
        if (t == "pop_complexity") {
            int d1;
            cin >> d1;
            if (n <= 2000 && m <= 2000) {
                cout << get(d1) <<", " << h[d1] << "\n";
            } else {
                cout << h[d1] << "\n";
            }
            
        }
        cout << "h = " << h << "\n"; 
    }
    print();
    cout << h[6] << "\n";
    // cout << p[4] << ": " << d[p[4]] << "\n";
    // cout << get(4) << ", " << get(2) << "\n";
}
