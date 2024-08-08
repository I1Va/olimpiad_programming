#include <iostream>
#include <string>
using namespace std;

int main() {
    system("cd checker && g++ opt.cpp -o opt.exe");
    system("cd checker && g++ brut.cpp -o brut.exe");
    system("cd checker && g++ gen.cpp -o gen.exe");
    int idx = 0;
    while (1) {
        system("cd checker && gen.exe > inp.txt");
        system("cd checker && opt.exe < inp.txt > bad.txt");
        system("cd checker && brut.exe < inp.txt > good.txt");
        if (system("cd checker && fc bad.txt good.txt")) {
            cout << "!WA";
            return 0;
        }
        cout << idx << ": OK\n";
        idx++;
    }
}