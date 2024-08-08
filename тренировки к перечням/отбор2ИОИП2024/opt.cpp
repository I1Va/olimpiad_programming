void solve() {
    string s, t;
    cin >> s >> t;
    int n = len(s);
    string p;
    int j = 0;
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == t[j]) {
            p += s[i];
            j++;
            if (j == len(t)) {
                break;
            }
        } else {
            if (i % 2 == 1) { c++;continue;}
            if (c == 0) {
                p.pop_back();
                j--;
            }
            c++;
        }
    }
    if (t == p) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}