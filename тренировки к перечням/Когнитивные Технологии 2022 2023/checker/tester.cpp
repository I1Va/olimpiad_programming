#include <iostream>
using namespace std;

int main() {
    system("cd checker && g++ opt.cpp -o opt.exe");
    system("cd checker && g++ brut.cpp -o brut.exe");
    int idx = 0;
    while (1) {
        system("cd checker && python gen.py > inp.txt");
    }
}