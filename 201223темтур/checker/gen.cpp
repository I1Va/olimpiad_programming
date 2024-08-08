#include <iostream>
#include <vector>
#include <chrono>
#include <random>
using namespace std;

auto now = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(now);

int randrange(int a, int b) {
    return a + rnd() % (b - a);
}

int main() {
    int n = randrange(17, 20);
    vector<int> a = {0};
    
}