#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;

ostream& operator<< (ostream& stream, const vector<long double>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

ostream& operator<< (ostream& stream, const vector<pair<int, long double>>& a) {
    for (auto to : a) {
        stream << "{" << to.first << " " << to.second << "} ";
    }
    return stream;
}

long double sum(int l, int r, const vector<pair<int, long double>>& a) {
    long double res = 0;
    for (int i = l; i <= r; i++) {
        res += a[i].second;
    }
    return res;
}

long double get(int mask, const int& n) {
    long double res = 1;
    for (int i = 0; i < n; i++) {
        if ((mask >> i) & 1) {
            res *= 0.6;
        } else {
            res *= 0.4;
        }
    }
    return res;
}

vector<long double> build(int c) {
    vector<long double> a;
    for (int mask = 0; mask < (1 << c); mask++) {
        a.push_back(get(mask, c));
    }
    return a;
}

int main() {
    for (int c = 2; c <= 10; c++) {
        vector<pair<int, long double>> masks;
        for (int mask = 0; mask < (1 << c); mask++) {
            masks.push_back({mask, get(mask, c)});
        }
        cout << "a: " << masks << "\n";
        while (1) {
            if (sum(0, 3, masks) == sum(4, 7, masks)) {
                cout << "\n";
                for (auto to : masks) {
                    cout << bitset<4>(to.first) << ": " << to.second << "\n";
                }
                cout << "\n";
                cout << "a: " << masks << "\n";
                return 0;
                break;
            }
            if (!next_permutation(masks.begin(), masks.end())) {
                break;
            }
        }
    }
    
}