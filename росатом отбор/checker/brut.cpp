#include <iostream>
#include <vector>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

int n, m;

int get_man(int l, int r, const vector<int>& a) {
    int res = 0;
    for (int i = l; i < r; i++) {
        res += a[i];
    }
    return res;
}

void upd_man(int pos, int val, vector<int>& a, vector<int>& left, vector<int>& right) {
    a[pos] = val;
    if (pos + 2 < n) {
        left[pos] = (a[pos] == 1 && a[pos + 1] == 2 && a[pos + 2] == 3);
        right[pos] = (a[pos + 2] == 1 && a[pos + 1] == 2 && a[pos] == 3);
    }
    if (pos - 1 >= 0 && pos + 1 < n) {
        left[pos - 1] = (a[pos - 1] == 1 && a[pos] == 2 && a[pos + 1] == 3);
        right[pos - 1] = (a[pos + 1] == 1 && a[pos] == 2 && a[pos - 1] == 3);
    }
    if (pos - 2 >= 0) {
        left[pos - 2] = (a[pos - 2] == 1 && a[pos - 1] == 2 && a[pos] == 3);
        right[pos - 1] = (a[pos] == 1 && a[pos - 1] == 2 && a[pos - 2] == 3);
    }
}

void rebuild(vector<int>& a, vector<int>& left, vector<int>& right) {
    for (int i = 0; i < n - 2; i++) {
        left[i] = (a[i] == 1 && a[i + 1] == 2 && a[i + 2] == 3);
        right[i] = (a[i + 2] == 1 && a[i + 1] == 2 && a[i] == 3);
    }   
}
void print(vector<int>& a, vector<int>& left, vector<int>& right) {
    return;
    cout << "a = " << a << "\n";
    cout << "left = " << left << "\n";
    cout << "right = " << right << "\n";
}

int main() {
    cin >> n;
    vector<int> a(n), left(n), right(n), tree(4 * n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    rebuild(a, left, right);
    cin >> m;
    while (m--) {
        char c;
        cin >> c;
        if (c == '?') {
            int l, r, t;
            cin >> l >> r >> t;
            if (t == 1) {
                cout << get_man(l - 1, r - 2, left);
            } else {
                cout << get_man(l - 1, r - 2, left) + get_man(l - 1, r - 2, right);
            }
            cout << "\n";
        } else {
            int pos, val;
            cin >> pos >> val;
            a[pos - 1] = val;
            rebuild(a, left, right);
        }
        // print(a, left, right);
        
    }
}