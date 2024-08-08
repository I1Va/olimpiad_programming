#include <iostream>
#include <vector>
#include <string>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}
int n, m;
int revs = 0;

vector<int> merge(vector<int> a, vector<int> b) {
	vector<int> ans(a.size() + b.size());
	int ai = 0, bi = 0, k = 0;
	while (ai < a.size() && bi < b.size()) {
		if (b[bi] < a[ai]) {
			ans[k] = b[bi], bi++, k++;
			revs += a.size() - ai;
		}
		else {
			ans[k] = a[ai], ai++, k++;
		}
	}
	while (ai < a.size()) {
		ans[k] = a[ai], k++, ai++;
	}
	while (bi < b.size()) {
		ans[k] = b[bi], k++, bi++;
	}
	return ans;
}

vector<int> mergeSort(vector<int> ar) {
	int half = ar.size() / 2;
	if (ar.size() < 2) {
		return ar;
	}
	vector<int> left(half);
	vector<int> right(ar.size() - half);
	for (int i = 0; i < half; i++) {
		left[i] = ar[i];
	}
	for (int i = half; i < ar.size(); i++) {
		right[i - half] = ar[i];
	}
	return merge(mergeSort(left), mergeSort(right));
}

int main() {
    string t;
    cin >> t;
    if (t == "first") {
        cin >> n >> m;
        vector<int> a(m);
        for (int i = 0; i < m; i++) {
            cin >> a[i];
        }
        for (auto to : a) {
            cout << to << " ";
        }
    } else {
        cin >> n >> m;
        vector<int> a(n);
        for (int i = 0; i < m; i++) {
            cin >> a[i];
        }
        for (int i = m; i < n; i++) {
            cin >> a[i];
        }
        mergeSort(a);
        int ans = revs;
        for (int i = 0; i < n - 1; i++) {
            revs = revs + n - 2 * (a[i] - 1) - 1;
            ans = min(ans, revs);
            // cout << revs << "\n";
	    }
        cout << ans;
    }
}