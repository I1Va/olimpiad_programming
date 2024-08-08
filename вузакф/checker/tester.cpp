#include <iostream>
using namespace std;

int main() {
    system("cd checker && g++ opt.cpp -o opt.exe");
    system("cd checker && g++ brut.cpp -o brut.exe");
    int idx = 0;
    while (1) {
        system("cd checker && python gen.py > inp.txt");
        system("cd checker && opt.exe < inp.txt > bad.txt");
        system("cd checker && brut.exe < inp.txt > good.txt");
        if (system("cd checker && fc bad.txt good.txt")) {
            return 0;
        }
        idx += 1;
        cout << "idx: " << idx << ": OK\n";
    }
}
