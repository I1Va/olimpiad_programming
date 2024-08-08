#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;
    int a, b;
    while (t--) {
        cin >> a >> b;
        cout << min(a/2, b/2) << "\n";
    }
}
