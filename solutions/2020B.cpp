mt19937 g;

struct point {
    int x, y, z, tp;

    point(){};

    point(int a, int b, int c, int tt) {
        x = a;
        y = b;
        z = c;
        tp = tt;
    }

    int get_dist(point &p) {
        return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y) +
               (p.z - z) * (p.z - z);
    }

    pair<int, int> find_nearest(int r) {
        pair<int, int> ans = {0, 0};
        int cr = x * x + y * y + z * z;
        int rd = 0;

        if (x * x + y * y <= r * r) return {x, y};

        point cur = point(x, y, z, 1);
        for (int i = -r; i <= r; ++i) {
            while ((rd + 1) * (rd + 1) + i * i <= r * r) rd++;
            while (rd * rd + i * i > r * r) rd--;

            point p1(i, rd, 0, 1);
            point p2(i, -rd, 0, 1);

            if (cur.get_dist(p1) < cr) {
                cr = cur.get_dist(p1);
                ans = {i, rd};
            }
            if (cur.get_dist(p2) < cr) {
                cr = cur.get_dist(p2);
                ans = {i, -rd};
            }
        }

        return ans;
    }

    bool operator<(const point &p) const {
        if (x != p.x) return x < p.x;
        if (y != p.y) return y < p.y;
        return z < p.z;
    }
};

struct gen {
    vector<point> s, bs;
    int hp;
    int m, r;

    gen(){};

    gen(vector<point> &d, int rr, int mm) {
        for (auto el : d) bs.push_back(el);
        r = rr;
        m = mm;
    }

    void make_zapr() {
        if (m >= bs.size()) {
            s = bs;
            return;
        }
        s.clear();
        int lst = 0;
        for (int i = 0; i < bs.size(); ++i) {
            int p = i - lst;
            int vr = rand() % m;
            if (vr < p) {
                pair<int, int> nr = bs[i - 1].find_nearest(r);
                s.push_back(point(nr.first, nr.second, 0, 0));
                lst = i;
            }
            s.push_back(bs[i]);
        }
    }

    void mutate() {
        int r1 = rand() % bs.size();
        int r2 = rand() % bs.size();
        swap(bs[r1], bs[r2]);
    }

    void strong_mutate() { shuffle(bs.begin(), bs.end(), g); }

    void get_hp() {
        hp = 0;
        point bs(0, 0, 1, 1);
        hp += s[0].get_dist(bs);
        hp += s.back().get_dist(bs);
        for (int i = 1; i < s.size(); ++i) {
            hp += s[i].get_dist(s[i - 1]);
        }
    }

    bool operator<(const gen &g) const { return hp < g.hp; }
};

int iter = 15000, sz = 500, mt = 240, tp = 5;

ifstream cin;
cin.open("test.txt");

ofstream cout;
cout.open("ans.txt");

int t;
cin >> t;

while (t--) {
    int n, r, m;
    cin >> n >> r >> m;

    vector<point> s(n);
    map<point, int> ids;
    for (int i = 0; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        s[i] = point(x, y, z, 1);
        ids[s[i]] = i + 1;
    }

    vector<gen> pp;
    for (int i = 0; i < sz; i++) {
        pp.push_back(gen(s, r, m));
        pp[i].make_zapr();
        pp[i].get_hp();
    }

    for (int qq = 0; qq < iter; qq++) {
        for (int i = tp; i < tp + mt; i++) {
            pp[i].mutate();
            pp[i].make_zapr();
            pp[i].get_hp();
        }
        for (int i = tp + mt; i < sz; i++) {
            pp[i].strong_mutate();
            pp[i].make_zapr();
            pp[i].get_hp();
        }

        sort(pp.begin(), pp.end());
    }

    for (auto el : pp[0].s) {
        if (el.tp == 1)
            cout << ids[el] << ' ';
        else
            cout << "F(" << el.x << "," << el.y << ")" << ' ';
    }

    cout << "B" << '\n';
}

cout.close();
cout.flush();
return 0;
