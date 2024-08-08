#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const long double EPS = 1.0 / 1e5;

ostream& operator<< (ostream& stream, const vector<int>& a) {
    for (auto to : a) {
        stream << to << " ";
    }
    return stream;
}

struct node {
    // time, idx, v
    long double s;
    int l;
    long double w;
    node(long double s, int l, long double w): s{s}, l{l}, w{w} {};
    node(): s{-1}, l{-1}, w{0} {};
};

struct edge {
    int a, b;
    long double v;
    edge(int a, int b, long double v): a{a}, b{b}, v{v} {};
    edge(): a{-1}, b{-1}, v{0} {};
};

struct lake {
    long double vin_sum = 0;
    vector<int> vin;
    long double vout_sum = 0;
    vector<int> vout;
    long double cur = 0;
    long double c;
    lake(long double c): c{c} {};
    lake(): c{0} {};
    void upd(long double dt) {
        cur = cur + dt * vin_sum - dt * vout_sum;
    }
};

vector<lake> lakes;
vector<edge> edges;
long double cur_time;
vector<node> ans;

void remove() {
    lakes.clear();
    edges.clear();
    cur_time = 0;
    ans.clear();
}

int n, m, x;


int check() {
    for (int i = 0; i < n - 1; i++) {
        if (lakes[i].cur - lakes[i].c > EPS) {
            return i;
        }
    }
    return -1;
}



void build_lake(int i) {
    lakes[i].vin_sum = 0;
    lakes[i].vout_sum = 0;
    for (auto x : lakes[i].vin) {
        lakes[i].vin_sum += edges[x].v;
    }
    for (auto x : lakes[i].vout) {
        lakes[i].vout_sum += edges[x].v;
    }
}

pair<long double, int> scan() {
    long double mn = 1e9;
    int idx = -1;
    for (int i = 0; i < n - 1; i++) {
        // время переполнения
        if (lakes[i].vin_sum - lakes[i].vout_sum <= EPS) {
            continue;
        }
        long double t = (lakes[i].c - lakes[i].cur) / (lakes[i].vin_sum - lakes[i].vout_sum);
        // cout << lakes[i].c << ", " << lakes[i].cur << ", " << lakes[i].vin_sum << ", " << lakes[i].vout_sum << "\n"; 
        // cout << i << ": " << t << "\n";
        if (t < mn) {
            mn = t;
            idx = i;
        }
    }
    // cout << "\n";
    return {mn, idx}; // Через время mn, озеро idx переполнится
}

void stabilize(int idx) {
    // Делаем в озере idx vin = vout
    long double vin_sum = lakes[idx].vin_sum;
    long double vout_sum = lakes[idx].vout_sum;
    long double p = vout_sum / vin_sum;
    for (int i : lakes[idx].vin) { // Сделаем vi *= p. Уменьшим скорость поступления
        edges[i].v *= p;
        ans.push_back(node(cur_time, i + 1, edges[i].v));
    }
    for (int i : lakes[idx].vin) {
        build_lake(edges[i].a); // Обновили актуальные значения для смежных озер
        build_lake(edges[i].b);
    }
}

void print_log() {
    for (int i = 0; i < n; i++) {
        cout << string(10, '=') << "\n";
        cout << i << ":\n";
        cout << "c: " << lakes[i].c << ", cur: " << lakes[i].cur << ", vin_sum: " << lakes[i].vin_sum << ", vout_sum: " << lakes[i].vout_sum << "\n";
        cout << "vin: " << lakes[i].vin << "\n";
        cout << "vout: " << lakes[i].vout << "\n";
        cout << string(10, '=') << "\n";
    }
}

void solve() {
    remove();
    cin >> n >> m >> x;
    lakes.resize(n);
    lakes[n - 1].cur = x;
    for (int i = 0; i < n - 1; i++) {
        cin >> lakes[i].c;
    }
    edges.resize(m);
    for (int i = 0; i < m; i++) {
        int ai, bi;
        long double v;
        cin >> ai >> bi >> v;
        ai--;
        bi--;
        edges[i] = edge(ai, bi, v);
        lakes[ai].vout.push_back(i);
        lakes[bi].vin.push_back(i);
    }
    for (int i = 0; i < n; i++) {
        build_lake(i);
    }
    ans.clear();
    for (int i = 0; i < m; i++) {
        ans.push_back(node(cur_time, i + 1, edges[i].v));
    }
    // print_log();
    while (lakes[n - 1].cur > EPS) {
        // cout << "main lake cur: " << lakes[n - 1].cur << "\n";
        long double dt = lakes[n - 1].cur / lakes[n - 1].vout_sum;
        // cout << "main dt: " << dt << "\n";
        auto cur = scan();
        cur.first = min(cur.first, dt);
        for (int i = 0; i < n; i++) {
            lakes[i].upd(cur.first);
        }
        int er = check();
        if (er != -1) {
            cout << "er: " << er << "\n";
            print_log();
            exit(0);
        }
        cur_time += cur.first;
        if (cur.second == -1) {
            continue;
        }
        stabilize(cur.second);
        // cout << "dt: " << cur.first << ", stabilize: " << cur.second << "\n";
        // break;
    }
    for (int i = 0; i < m; i++) {
        ans.push_back(node(cur_time, i + 1, 0));
    }
    cout << cur_time << " " << ans.size() << "\n";
    for (auto x : ans) {
        cout << x.s << " " << x.l << " " << x.w << "\n";
    }
    cout << "\n";
}

int main() {
    cout << fixed << setprecision(7);
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}