#include <iostream>
using namespace std;

long long X1, X2, X3, X4, Y1, Y2, Y3, Y4;

struct vec {
	long long x, y;
};

long long operator* (vec a, vec b) { return a.x * b.x + a.y * b.y; }
long long operator^ (vec a, vec b) { return a.x * b.y - a.y * b.x; }

bool between(long long X0, long long Y0, long long X1, long long Y1, long long X2, long long Y2) {
	return (X0 >= min(X1, X2) && X0 <= max(X1, X2)) && (Y0 >= min(Y1, Y2) && Y0 <= max(Y1, Y2));
}

int main() {
	cin >> X1 >> Y1 >> X2 >> Y2 >> X3 >> Y3 >> X4 >> Y4;
	vec DC{ X4 - X3, Y4 - Y3 };
	vec DA{ X1 - X3, Y1 - Y3 };
	vec DB{ X2 - X3, Y2 - Y3 };
	vec BA{ X1 - X2, Y1 - Y2 };
	vec BD{ X3 - X2, Y3 - Y2 };
	vec BC{ X4 - X2, Y4 - Y2 };
	bool state = false;
	/*cout << "DC ^ DA = " << (DC ^ DA) << "\n";
	cout << "DC ^ DB = " << (DC ^ DB) << "\n";
	cout << "BA ^ BD = " << (BA ^ BD) << "\n";
	cout << "BA ^ BC = " << (BA ^ BC) << "\n";*/
	long long a1 = (DC ^ DA) * (DC ^ DB), a2 = (BA ^ BD) * (BA ^ BC);
	// cout << "A1 = " << a1 << " " << "A2 = " << a2 << "\n";
	if ((a1 < 0 && a2 < 0) || (a1 == 0 && a2 < 0) || (a1 < 0 && a2 == 0)) {
		state = true;
	}
	else if ((DC ^ DA) * (DC ^ DB) == 0 && (BA ^ BD) * (BA ^ BC) == 0) {
		if (between(X1, Y1, X3, Y3, X4, Y4) || between(X2, Y2, X3, Y3, X4, Y4)
			|| between(X3, Y3, X1, Y1, X2, Y2) || between(X4, Y4, X1, Y1, X2, Y2)) {
			state = true;
		}
		/*else {
			cout << "ONE LINE\n";
		}*/
	}
	if (state) {
		cout << "YES";
	}
	else {
		cout << "NO";
	}
}