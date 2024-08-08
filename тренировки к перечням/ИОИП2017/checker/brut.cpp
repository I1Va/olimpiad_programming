#include <iostream>
#include <vector>
#include <map>
using namespace std;


int getFirst(int x) {
    return x % 10;
}

int getLast(int x) {
    while(x >= 10) {
        x /= 10;
    }
    return x;
}

int main(){
    int a, b, c;
    cin >> a >> b >> c;
    map<int, int> L, R, S;
    vector<vector<int> > B(10, vector<int>(10));
    vector<int> A(10), C(10);
    for(int i = 0; i < a; i++) {
        int t;
        cin >> t;
        A[getFirst(t)]++;
        L[t]++;
    }
    for(int i = 0; i < b; i++) {
        int t;
        cin >> t;
        B[getLast(t)][getFirst(t)]++;
        S[t]++;
    }
    for(int i = 0; i < c; i++) {
        int t;
        cin >> t;
        C[getLast(t)]++;
        R[t]++;
    }
    long long result = 0;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            result += (long long) A[i] * B[i][j] * C[j];
        }
    }
    for(auto v : L) {
        if(getLast(v.first) == getFirst(v.first)) {
            result -= (long long) v.second * S[v.first] * C[getFirst(v.first)];
            result += (long long) 2 * v.second * S[v.first] * R[v.first];
        }
        result -= (long long) v.second * R[v.first] * B[getFirst(v.first)][getLast(v.first)];
    }
    for(auto v : S) {
        if(getLast(v.first) == getFirst(v.first)) {
            result -= (long long) v.second * A[getLast(v.first)] * R[v.first];
        }
    }
    cout << result;
}