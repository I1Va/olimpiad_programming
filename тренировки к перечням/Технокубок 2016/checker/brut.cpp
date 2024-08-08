#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

struct node {
    long long f;
    long long s;
    node(): f{0}, s{0} {};
    node(long long f, long long s): f{f}, s{s} {}
};

bool comp(const node& a, const node& b) {
    return a.f * b.s > b.f * a.s;
}

int n, k;
node ans = {0, 1};
vector<int> ans_p;

vector<int> c;
vector<int> a;

void rec(int idx, vector<int> cur) {
    if (idx == k) {
        node res;
        for (int i = 0; i < k; i++) {
            res.f += cur[i];
            res.s += cur[i] * c[i];
        }
        for (int i = 1; i < k; i++) {
            if (cur[i - 1] < cur[i]) {
                return;
            }
        }
        if (comp(res, ans)) {
            ans_p = cur;
            ans = res;
        }
        return;
    }
    for (int i = 0; i < 10; i++) {
        cur[idx] = i;
        rec(idx + 1, cur);
    }
}

void print_ans() {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < c[i]; j++) {
            cout << ans_p[i] << " ";
        }
    }
    for (int i = a[k - 1] + 1; i <= n; i++) {
        cout << 0 << " ";
    }
}

int main() {
    
    cin >> n >> k;
    a.resize(k);
    c.resize(k);
    for (int i = 0; i < k; i++) {
        cin >> a[i];
        if (i == 0) {
            c[i] = a[i] - 0;
        } else {
            c[i] = a[i] - a[i - 1];
        }
    }
    vector<int> cur(k);
    rec(0, cur);
    
    // cout << "c = " << c << "\n";
    // cout << "ans_p = " << ans_p << "\n";
    // print_ans();
    int g = gcd(ans.f, ans.s);
    cout << ans.f / g << "\n" << ans.s / g;

}