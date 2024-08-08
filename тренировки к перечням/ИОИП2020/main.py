
mod = 10 ** 18 + 3

def binpow(a, n):
    res = 1
    while n:
        if n & 1:
            res *= a
            res %= mod
        a **= 2
        a %= mod
        n >>= 1
    return res

n = int(input())
a = list(map(int, input().split()))
d = {}

for x in a:
    for j in range(20):
        temp = binpow(2, x + j)
        if temp not in d:
            d[temp] = 1

prefs = [0] * (n + 1)
for i in range(1, n + 1):
    prefs[i] = (prefs[i - 1] + binpow(2, a[i - 1])) % mod

ans = 0

for i in range(n):
    for j in range(i, n):
        temp = (prefs[j + 1] - prefs[i] + mod) % mod
        if temp in d:
            ans += 1
print(ans)