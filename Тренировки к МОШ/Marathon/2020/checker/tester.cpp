#include <iostream>
using namespace std;

int main() {
    int idx = 0;
    // system("cd checker && g++ opt.cpp -o opt.exe");
    system("cd checker && g++ brut.cpp -o brut.exe");
    while (1) {
        system("cd checker && python gen.py > inp.txt");
        system("cd checker && python opt.py < inp.txt > bad.txt");
        system("cd checker && brut.exe < inp.txt > good.txt");
        if (system("cd checker && fc good.txt bad.txt")) {
            return 0;
        }
        cout << idx << ": OK\n";
        idx++;
    }
}
