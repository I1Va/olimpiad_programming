vector<int> ans;
vector<bool> used, child;
vector<pair<int, int>> s;

void dfs(int v, int c) {
    int t = s[v].first - 1;
    for (int i = v + 1; i < (int)s.size(); i++) {
        if (!child[i]) {
            if (t >= s[i].first) {
                t -= s[i].first;
                child[i] = true;
                ans[s[i].second] = c;
            }
        }
    }
}

int t;
cin >> t;

while (t-- > 0) {
    int n;
    cin >> n;

    s.clear();

    int x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        s.push_back({-x, i});
    }
    sort(s);

    for (int i = 0; i < n; i++) {
        s[i].first = -s[i].first;
    }

    ans.assign(n, 0);
    used.assign(n, false);
    child.assign(n, false);

    for (int i = n - 1; i >= 0; i--) {
        if (!used[i]) {
            used[i] = true;
            dfs(i, s[i].second + 1);
        }
    }

    for (auto &el : ans) cout << el << " ";
    cout << '\n';
}