#include <iostream>
#include <bitset>
#include <string>
using namespace std;

const int n = 4;

void print(int mask, string extra) {
    cout << bitset<n>(mask) << extra << "\n";
}

void print_2(int mask) {
    for (int i = 0; i < n; i++) {
        cout << ((mask >> i) & 1);
    }
    cout << "\n";
}

int main() {
    int mask = 14;
    for (int i = 0; i <= n; i++) {
        print(mask, "");
        int fir = (mask & 1);
        string s = ", fir = " + to_string(fir);
        // print(fir << (n - 1), " -> fir<<n");
        mask = (mask >> 1) | (fir << (n - 1));  
    }
}