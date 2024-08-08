#include <iostream>
#include <vector>
#include <string>
using namespace std;
ostream& operator<< (ostream& stream, const pair<char, int>& a) {
    stream << "{" << a.first << ", " << a.second << "}";
    return stream;
}

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

ostream& operator<< (ostream& stream, const vector<pair<char, int>>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

struct seg {
    int l, r;
    bool empty;
    bool over;
    seg(int l, int r, bool empty, bool over): l{l}, r{r}, empty{empty}, over{over} {};
};

ostream& operator<< (ostream &stream, const seg& x) {
    stream << "{" << x.l << ":" << x.r << ", " << x.empty << ", " << x.over << "}";
    return stream;
}

ostream& operator<< (ostream& stream, const vector<seg>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}


int main() {
    string s, t;
    cin >> s >> t;
    int n = (int) s.size();
    int m = (int) t.size();
    vector<pair<char, int>> sp, tp;
    sp.push_back({s[0], 1});
    for (int i = 1; i < n; i++) {
        if (s[i] == sp[(int) sp.size() - 1].first) {
            sp[(int) sp.size() - 1].second++;
        } else {
            sp.push_back({s[i], 1});
        }
    }
    tp.push_back({t[0], 1});
    for (int i = 1; i < m; i++) {
        if (t[i] == tp[(int) tp.size() - 1].first) {
            tp[(int) tp.size() - 1].second++;
        } else {
            tp.push_back({t[i], 1});
        }
    }
    cout << "sp = " << sp << "\n";
    cout << "tp = " << tp << "\n";
    vector<seg> segs;
    int si = 0;
    int sc = 0;
    int ti = 0;
    while (si < (int) sp.size() && ti < (int) tp.size()) {
        // cout << si << " " << ti << ", segs = " << segs << "\n";
        if (sp[si].first == tp[ti].first) {
            segs.push_back(seg(sc, sc + sp[si].second - 1, false, sp[si].second > tp[ti].second));
            if (sp[si].second < tp[ti].second) {
                tp[ti].second -= sp[si].second;
            } else {
                ti++;
            }
            sc += sp[si].second;
            si++;
        } else {
            int l = sc;
            while (si < (int) sp.size() && ti < (int) tp.size() && sp[si].first != tp[ti].first) {
                sc += sp[si].second;
                si++;     
            }
            segs.push_back(seg(l, sc - 1, true, false));
        }
    }
    if (ti != (int) tp.size()) {
        cout << "NO";
        return 0;
    }
    while (si < (int) sp.size()) {
        if (segs[(int) segs.size() - 1].empty) {
            segs[(int) segs.size() - 1].r += sp[si].second;
            si++;
        } else {
            segs.push_back(seg(sc, sc + sp[si].second - 1, true, false));
            si++;
        }
    }
    cout << "\n\nsegs = " << segs << "\n";
}