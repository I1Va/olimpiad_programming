#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

const int k = 6;
const int n = k * 4;
const int dest = 70000;
const int maxv = ((1 << (n + 1)) - 1);

bool used[(1 << n)];
vector<int> ans;
vector<char> mapa = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

void add(int mask) {
    if (used[mask]) {
        return;
    }
    ans.push_back(mask);
    for (int i = 0; i < k; i++) {
        int cur = mask;
        for (int next = 0; next < (1 << 4); next++) {
            cur = (mask & (maxv ^ (15 << (4 * i)))) | (next << (4 * i));
            // cout << bitset<4 * k>(mask) << "\n" <<
            // bitset<4 * k> ((maxv ^ (15 << (4 * i)))) << "\n" << bitset<4 * k>(next << (4 * i))
            // << "\n" << bitset<k * 4>((mask & (maxv ^ (15 << (4 * i)))) | (next << (4 * i))) << "\n\n";
            used[cur] = true;
        }
    }
}

void print(int mask, int idx) {
    if (idx == k) {
        // cout << mapa[mask & (15 << ((idx) * 4))];
        return;
    }
    print(mask, idx + 1);
    // cout << "idx = " << idx << ", mask&pat = \n" << bitset<4 * k>(mask) << "\n" << bitset<4 * k>(15 << ((idx) * 4))
    // << "\n" << bitset<4 * k>((mask & (15 << ((idx) * 4))) >> (idx * 4)) << "\n, char = " << mapa[(mask & (15 << ((idx) * 4))) >> (idx * 4)] << "\n\n";   
    cout << mapa[(mask & (15 << ((idx) * 4))) >> (idx * 4)];
}

int main() {
    ans.reserve(dest + 1);
    for (int mask = 0; mask < (1 << n) && ans.size() < dest; mask++) {
        add(mask);
    }
    for (auto to : ans) {
        // cout << bitset<4 * k>(to) << " = ";
        print(to, 0);
        cout << "\n";
    }
}