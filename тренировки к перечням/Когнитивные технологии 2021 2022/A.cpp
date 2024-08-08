#include <map>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    map<char, int> cnt;
    vector<char> a = {'A', 'B', 'B', 'D', 'O', 'P', 'R', 'Q'};
    for (auto to : a) {
        cnt[to]++;
    }
    char x;
    cin >> x;
    cout << cnt[x];
}