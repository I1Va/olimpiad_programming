// c это и количество блоков, и также их размер; оно должно быть чуть больше корня
const int maxn = 1e5, c = 330;
int a[maxn], b[c];
int add[c];

for (int i = 0; i < n; i++)
    b[i / c] += a[i];