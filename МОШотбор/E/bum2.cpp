#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <map>
using namespace std;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

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

struct HASH {
    const long long mod = 1e9 + 7;
    const long long p = 7;
    vector<long long> pows;
    vector<long long> prefs;
    HASH(const string& s) {
        int n = (int) s.size();
        pows.resize(n + 1), prefs.resize(n + 1);
        pows[0] = 1;
        for (int i = 1; i < n + 1; i++) {
            pows[i] = (pows[i - 1] * p) % mod;
        }
        prefs[0] = s[0] - '0';
        for (int i = 1; i < n; i++) {
            prefs[i] = (prefs[i - 1] * p + s[i - 1]) % mod;
        }
    }
    long long get(int l, int r) {
        return (prefs[r + 1] - prefs[l] * pows[r - l + 1] + mod) % mod;
    }
};

const int lb = 4;
const int rb = 20;
map<char, string> global_ans;
map<char, int> global_cnt;

bool fano_check(const map<char, string>& a) {
    vector<string> pool;
    pool.reserve(a.size());
    for (auto x : a) {
        pool.push_back(x.second);
    }
    int n = (int) pool.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            string fir = pool[i];
            string sec = pool[j];
            if (fir.size() > sec.size()) {
                swap(fir, sec);
            }
            if (fir == sec.substr(0, fir.size())) {
                return false;
            }
        }
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

void check(const vector<int>& lm, const vector<int>& sym, const string& word, const string& bit, HASH& bit_hash) {
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
            // if (bit_hash.get(bi, bi + lens[word[wi]] - 1) != bit_hash.get(alp[word[wi]].first, alp[word[wi]].second)) {
            //     return;
            // }
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

void rec(int ost, vector<int> lens, int idx, const vector<int>& sym, const string& word, const string& bit, HASH& bit_hash) {
    if (ost < 0) {
        return;
    }
    if (idx == sym.size()) {
        // cout << "lens: " << lens << "\n";
        check(lens, sym, word, bit, bit_hash);
        return;
    }
    int cur = global_cnt[sym[idx]];
    if (idx == (int) lens.size() - 1) {
        if (ost % cur != 0) {
            return;
        }
        lens[idx] = ost / cur;
        rec(0, lens, idx + 1, sym, word, bit, bit_hash);
        return;
    }
    // cout << "lens: " << lens << ", ost: " << ost << ", cur: " << cur << "\n";
    for (int i = lb; i <= rb; i++) {
        if (global_ans.size()) {
            return;
        }
        lens[idx] = i;
        rec(ost - cur * i, lens, idx + 1, sym, word, bit, bit_hash);
    }
}

void solve() {
    global_ans.clear();
    global_cnt.clear();
    string word, bit;
    cin >> word >> bit;
    auto bit_hash = HASH(bit);
    vector<int> unic = unic_cnt(word);
    vector<int> lens(unic.size());
    for (auto w : word) {
        global_cnt[w]++;
    }
    rec((int) bit.size(), lens, 0, unic, word, bit, bit_hash);
    for (auto to : global_ans) {
        cout << to.first << " " << to.second << "\n";
    }
    // cout << "done: " << global_ans.size() << "\n";
    cout << "\n";
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}