map<string, set<string>> g;
map<string, bool> used;
map<string, int> comp;

void dfs(string cur, int num) {
    comp[cur] = num;
    for (auto s : g[cur]) {
        if (!comp[s]) {
            dfs(s, num);
        }
    }
}

void solve(string &s, string &t) {
    g.clear();
    used.clear();
    comp.clear();

    // cout << g.size() << '\n';
    // cout << used.size() << '\n';
    // cout << comp.size() << '\n';

    vector<string> ss, tt;

    string temp = "";
    for (auto &c : s) {
        if (c == ' ') {
            ss.push_back(temp);
            temp = "";
        } else {
            temp += c;
        }
    }
    if (temp != "") ss.push_back(temp);

    temp = "";
    for (auto &c : t) {
        if (c == ' ') {
            tt.push_back(temp);
            temp = "";
        } else {
            temp += c;
        }
    }
    if (temp != "") tt.push_back(temp);

    int n = (int)ss.size();
    for (int i = 0; i < n; i++) {
        if (ss[i] == tt[i]) continue;

        g[ss[i]].insert(tt[i]);
        g[tt[i]].insert(ss[i]);
    }

    int num = 0;
    for (auto &word : ss) {
        if (!comp[word]) {
            dfs(word, ++num);
        }
    }

    vector<int> cnt(n + 1, 0);
    for (auto &[key, val] : comp) {
        cnt[val]++;
    }

    vector<int> ans;
    for (auto &el : cnt) {
        if (el > 1) ans.push_back(el);
    }

    cout << (int)ans.size() << '\n';
    sort(ans);

    for (auto &el : ans) {
        cout << el << " ";
    }
    cout << '\n';
}

int test;
cin >> test;

while (test-- > 0) {
    string s, t;
    getline(cin, s);
    getline(cin, t);

    // cout << s << '\n';
    // cout << t << '\n';

    solve(s, t);
}
