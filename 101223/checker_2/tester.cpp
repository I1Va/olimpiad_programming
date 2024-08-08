#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const long double EPS = 1 / 1e5;

long double get(string name) {
    std::ifstream in(name); // окрываем файл для чтения
    long double res = -1e9;
    if (in.is_open()) {
        in >> res;
    }
    in.close();
    return res;
}

int main() {
    int idx = 0;
    system("cd checker_2 && g++ brut.cpp -o brut.exe");
    system("cd checker_2 && g++ opt.cpp -o opt.exe");
    while (1) {
        idx++;
        system("cd checker_2 && g++ gen.cpp -o gen.exe");
        system("cd checker_2 && gen.exe > inp.txt");
        system("cd checker_2 && opt.exe < inp.txt > bad.txt");
        system("cd checker_2 && brut.exe < inp.txt> good.txt");
        long double bad = get("bad.txt");
        long double good = get("good.txt");
        cout << good << " " << bad << "\n";
        if (abs(good - bad) > EPS) {
            cout << "WA!";
            return 0;
        }
        cout << idx << ": OK\n";
    }    
}