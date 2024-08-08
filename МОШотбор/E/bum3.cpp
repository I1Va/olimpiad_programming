#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <chrono>
#include <random>
#include <algorithm>
#include <map>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

const int lb = 1;
const int rb = 11;
vector<int> range;

map<char, string> global_ans;
map<char, int> global_cnt;
long long iters = 0;
const int sec = 1e5;

vector<int> unic_cnt(const string& a) {
    set<char> v;
    for (auto x : a) {
        v.insert(x);
    }
    vector<int> ans;
    ans.reserve(v.size());
    for (auto x : v) {
        ans.push_back(x);
    }
    return ans;
}

bool fano_check(const map<char, string>& a) {
    map<long long, int> bor;
    for (auto elem : a) {
        int cur = 1;
        for (auto w : elem.second) {
            if (w == '0') {
                cur = cur * 2;
            } else {
                cur = cur * 2 + 1;
            }
            if (bor[cur] == 2) {
                return false;
            }
            bor[cur] = 1;
        }
        bor[cur] = 2;
    }
    return true;
}

map<char, string> translate(const map<char, pair<int, int>>& alp, const string& word) {
    map<char, string> tr;
    for (auto x : alp) {
        tr[x.first] = word.substr(x.second.first, x.second.second - x.second.first + 1);
    }
    return tr;
}

void check(const vector<int>& lm, const vector<int>& sym, const string& word, const string& bit) {
    int wi = 0;
    int bi = 0;
    map<char, int> lens;
    for (int i = 0; i < (int) sym.size(); i++) {
        lens[sym[i]] = lm[i];
    }
    map<char, pair<int, int>> alp;
    while (wi < (int) word.size() && bi < (int) bit.size()) {
        if (alp.find(word[wi]) == alp.end()) {
            alp[word[wi]] = {bi, bi + lens[word[wi]] - 1}; //bit.substr(bi, lens[word[wi]]);
        } else {
            int l = alp[word[wi]].first;
            int r = alp[word[wi]].second;
            if (bit.substr(bi, lens[word[wi]]) != bit.substr(l, r - l + 1)) { // Медленно!
                return;
            }
        }
        bi += lens[word[wi]];
        wi++;
    }
    if (!(wi == (int) word.size() && bi == (int) bit.size())) {
        return;
    }
    if (alp.size() == sym.size()) {
        auto tr = translate(alp, bit);
        if (fano_check(tr)) {
            global_ans = tr;
        }
        
    }
}

void rec(int ost, vector<int> lens, int idx, const vector<int>& sym, const string& word, const string& bit) {
    if (ost < 0) {
        return;
    }
    if (idx == sym.size()) {
        // cout << "lens: " << lens << "\n";
        check(lens, sym, word, bit);
        return;
    }
    int cur = global_cnt[sym[idx]];
    if (idx == (int) lens.size() - 1) {
        if (ost % cur != 0) {
            return;
        }
        lens[idx] = ost / cur;
        rec(0, lens, idx + 1, sym, word, bit);
        return;
    }
    // cout << "lens: " << lens << ", ost: " << ost << ", cur: " << cur << "\n";
    // shuffle(range.begin(), range.end(), rnd);
    for (int i = lb; i <= rb; i++) {
        if (global_ans.size()) {
            return;
        }
        lens[idx] = i;
        rec(ost - cur * i, lens, idx + 1, sym, word, bit);
    }
}

void solve(int tc) {
    iters = 0;
    global_ans.clear();
    global_cnt.clear();
    string word, bit;
    cin >> word >> bit;
    vector<int> unic = unic_cnt(word);
    vector<int> lens(unic.size());
    for (auto w : word) {
        global_cnt[w]++;
    }
    rec((int) bit.size(), lens, 0, unic, word, bit);
    for (auto to : global_ans) {
        cout << to.first << " " << to.second << "\n";
    }
    cout << "\n";
}

int main() {
    range.resize(rb - lb + 2);
    for (int i = lb; i <= rb; i++) {
        range[i - lb] = i;
    }
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        solve(tc);
    }
}