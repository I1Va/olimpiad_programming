#include <iostream>
#include <string>
#include <vector>
using namespace std;

const char* bs = string(1, (char) (92)).c_str();

string merge(const vector<string>& a) {
    string res = "";
    for (auto to : a) {
        res.append(to);
    }
    return res;
}

int DoSystem(string com) {
    int res = system(com.c_str());
    if (res != 0) {
        cout << com;
        cout << "Error\n";
        exit(1);
    }
    return res;
}

void solve() {
    DoSystem("cd checker && g++ opt.cpp -o opt.exe");
    DoSystem("cd checker && g++ brut.cpp -o brut.exe");
    int idx = 0;
    while (1) {
        system("cd checker && python gen.py > inp.txt");
        auto com1 = merge({"cd checker && brut.exe < inp.txt > good.txt"});
        auto com2 = merge({"cd checker && opt.exe < inp.txt > bad.txt"});

        // auto com1 = merge({"cd checker && brut.exe < tests/", to_string(idx), ".txt > good.txt"});
        // auto com2 = merge({"cd checker && opt.exe < tests/", to_string(idx), ".txt > bad.txt"});
        
        DoSystem(com1);
        DoSystem(com2);
        if (DoSystem("cd checker && fc bad.txt good.txt")) {
            cout << "WA: idx = " << idx << "\n";
            return;
        }
        cout << idx << ": OK\n";
        idx++;
    }
}

int main() {
    solve();
}
