#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int c = 0;
    for (int i = 0; i < n; i++) {
        c += s[i] - '0';
    }
    int a, b;
    cin >> a >> b;
    int Petya = c - min(c, a);
    // Ответ для Пети: min(c, a);
    // Ответ для Вадима:
    int Vadim;
    if (b < c) {
        Vadim = c - min(b, c);
    } else {
        b -= c;
        b %= 2; // Цикл: бегемот зашел-вышел с берега
        // Сейчас все бегемоты в воде. b бегемотов выйдет на сушу
        Vadim = b;
    }
    // cout << Petya << " " << Vadim << "\n";
    if (Petya == Vadim) {
        cout << "Draw";
    } else if (Petya < Vadim) {
        cout << "Petya";
    } else {
        cout << "Vadim";
    }


}