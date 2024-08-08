#include <iostream>
#include <vector>
using namespace std;

struct action {
    int i, l, r;
    action(): i{-1}, l{-1}, r{-1} {};
    action(int i, int l, int r): i{i}, l{l}, r{r} {}
};

vector<action> actions;

void leave() {
    return;
    cout << "ERROR\n";
    exit(1);
}

int count(const string a, const char x) {
    int res = 0;
    for (auto w : a) {
        res += (w == x);
    }
    return res;
}

int find(const string a, const char x) {
    for (int i = 0; i < (int) a.size(); i++) {
        if (a[i] == x) {
            return i;
        }
    }
    return -1;
}

bool upd(int idx, int l, int r, string& A, bool add) {
    if (A[idx] != '1') {
        return false;
    }
    for (int i = l; i <= r; i++) {
        if (i == idx) {
            A[idx] = '0';
            continue;
        }
        if (A[i] != '0') {
            return false;
        }
        A[i] = '1';
    }
    if (add) {
        actions.emplace_back(idx + 1, l + 1, r + 1);
    }
    return true;
}

bool check(string& extra, const string& B) {
    for (auto to : actions) {
        upd(to.i - 1, to.l - 1, to.r - 1, extra, 0);
    }
    return extra == B;
}

int main() {
    int n;
    string A, B;
    cin >> n >> A >> B;
    string extra = A;
    // cout << "B = " << B << "\n"; 
    // cout << "A = " << A << "\n"; 
    if (A == B) {
        cout << "YES\n0";
        return 0;
    }
    if (count(A, '1') == 0) {
        if (count(B, '1') == 0) {
            cout << "YES\n0";
        } else {
            cout << "NO";
        }
        return 0;
    }
    if (count(B, '0') == 0) {
        if (count(A, '0') == 0) {
            cout << "YES\n0";
        } else {
            cout << "NO";
        }
        return 0;
    }
    int z = find(B, '0');
    int c = find(A, '1');
    // cout << "z, c = " << z << ", " << c << "\n";
    for (int i = 0; i < n; i++) {
        if (A[i] == '0' || i == c) {
            continue;
        }
        upd(i, i, i, A, 1);
    }
    // cout << "A = " << A << "\n"; 
    // Теперь все нули кроме c;
    if (c != z) {
        upd(c, min(c, z), max(c, z), A, 1); // Теперь на z позиции 1
    }
    
    // cout << "A = " << A << "\n"; 
    for (int i = 0; i < n; i++) {
        if (A[i] == '0' || i == z) {
            continue;
        }
        upd(i, i, i, A, 1);
    }
    // Теперь только на z позиции 1
    // cout << "A = " << A << "\n"; 
    upd(z, 0, n - 1, A, 1); // Теперь все 1 кроме z
    // cout << "A = " << A << "\n"; 
    for (int i = 0; i < n; i++) {
        if (A[i] != B[i]) {
            if (A[i] == '0') {
                leave();
            }
            upd(i, i, i, A, 1);
        }
    }
    // cout << "A = " << A << "\n";
    cout << "YES\n";
    cout << actions.size() << "\n";
    for (auto to : actions) {
        cout << to.i << " " << to.l << " " << to.r << "\n";
    }

}