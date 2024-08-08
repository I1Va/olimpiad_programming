bool color(int i, int j) {
    // 1 - белый
    // 0 - черный
    return !((i % 2) == (j % 2));
}

bool check(int i, int j, int n) {
    return (i >= 1 && i <= n) && (j >= 1 && j <= n);
}

vector<pair<int, int>> m = {
    {+1, -2}, {+2, -1},
    {+2, +1}, {+1, +2},
    {-1, -2}, {-2, -1},
    {-2, +1}, {-1, + 2}
};

vector<int> ans;

void solve() {
    int n;
    cin >> n;

    int si, sj;
    cin >> si >> sj;

    int fi, fj;
    cin >> fi >> fj;

    if (si == fi && sj == fj) {
        ans.push_back(0);
        return;
    }

    if (color(si, sj) && !color(fi, fj)) {
        ans.push_back(-1);
        return;
    }

    if (!color(si, sj) && !color(fi, fj)) {
        ans.push_back(-1);
        return;
    }

    if (color(si, sj) && color(fi, fj)) {
        if (abs(si - fi) == abs(sj - fj)) {
            ans.push_back(1);
        } else {
            ans.push_back(2);
        }
    } else {
        int curi, curj;
        for (auto &[dx, dy] : m) {
            curi = si + dx;
            curj = sj + dy;
            if (curi == fi && curj == fj && check(curi, curj, n)) {
                ans.push_back(1);
                return;
            }
        }

        for (auto &[dx, dy] : m) {
            curi = si + dx;
            curj = sj + dy;
            if (abs(curi - fi) == abs(curj - fj) && check(curi, curj, n)) {
                ans.push_back(2);
                return;
            }
        }

        ans.push_back(3);
        return;
    }
}

int t;
cin >> t;

while (t-->0) {
    solve();
}

for (auto &el : ans) {
    cout << el << '\n';
}
