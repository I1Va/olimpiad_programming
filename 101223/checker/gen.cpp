#include <iostream>
#include <vector>
#include <chrono>
#include <random>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937_64 rnd(now);

long long randrange(long long a, long long b) {
    return a + rnd() % (b - a);
}

int main() {
    for (int i = 0; i < 8; i++) {
        cout << randrange(-100, 500) << " ";
    }
}
