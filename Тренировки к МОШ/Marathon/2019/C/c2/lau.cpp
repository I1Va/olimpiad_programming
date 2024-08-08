#include <iostream>
#include <string>
using namespace std;

int main() {
    for (int i = 0; i <= 14; i++) {
        string num = string(2 - to_string(i).size(), '0') + to_string(i);
        string s = "main.exe < " + num + ".txt > " + num + "ans.txt";
        cout << "com: " << s << "\n";
        auto com = s.c_str();
        system(com);
    }
}