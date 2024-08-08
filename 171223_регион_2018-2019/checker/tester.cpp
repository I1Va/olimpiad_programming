#include <iostream>
#include <vector>
using namespace std;

int main() {
    int idx = 0;
    system("cd checker && g++ opt.cpp -o opt.exe");
    system("cd checker && g++ brut.cpp -o brut.exe");
    while (1) {
        idx++;
        system("cd checker && python gen.py > inp.txt");
        system("cd checker && brut.exe < inp.txt > good.txt");
        system("cd checker && opt.exe < inp.txt > bad.txt");
        if (system("cd checker && fc bad.txt good.txt")) {
            cout << "WA!";
            return 0;
        }
        cout << idx << ": OK\n"; 
    }
}
