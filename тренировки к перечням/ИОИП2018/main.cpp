#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> a(4);

long long S = 0;
pair<long long, long long> ans = {0, 0};

void upd(pair<long long, long long> c) {
    if (c.first * c.second > S) {
        S = c.first * c.second;
        ans = c;
    }

}

void get() {
    upd({a[0] / 4, (a[0] - 2 * (a[0] / 4)) / 2});
    cout << "4: " << a[0] / 4 << " " << (a[0] - 2 * (a[0] / 4)) / 2 << "\n";
    upd({min(a[0], a[1]), min(a[2], a[3])});
    cout << "1 1 1 1: " << min(a[0], a[1]) << " " << min(a[2], a[3]) << "\n";
    upd({a[0] / 2, a[1] / 2});
    cout << "2 2: " << a[0] / 2 << " " << a[1] / 2 << "\n";
    upd({a[0] / 3, min(a[0] - 2 * (a[0] / 3), a[1])});
    cout << "3 1: " << a[0] / 3 << " " << min(a[0] - 2 * (a[0] / 3), a[1]) << "\n";
    upd({a[0] / 2, min(a[1], a[2])});
    cout << "2 1 1: " << a[0] / 2 << " " << min(a[1], a[2]) << "\n";
}

int main() {
    
    cin >> a[0] >> a[1] >> a[2] >> a[3];
    get();
    // while (1) {
    //     get();
    //     if (!next_permutation(a.begin(), a.end())) {
    //         break;
    //     }
    // }
    cout << S;
    // cout << ans.first << " " << ans.second;
}