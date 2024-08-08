a = []
d = {}
def build():
    global a, d

    a = ["#", "$"]
    for i in range(0, 10):
        a.append(str(i))
    for i in range(ord("a"), ord("z") + 1):
        a.append(chr(i))
    for i in range(ord("A"), ord("Z") + 1):
        a.append(chr(i))
    a.sort()
    for i in range(len(a)):
        d[a[i]] = i

def get(s):
    s = s[::-1]
    res = 0
    for i in range(len(s)):
        res += 64 ** i * d[s[i]]
    return res

def upd(a):
    n = len(a)
    m = [a[:n // 2], a[n // 2:]]
    idx = [0, 0]
    t = 0
    for i in range(n):
        a[i] = m[t][idx[t]]
        idx[t] += 1
        t = (t + 1) % 2
    return a

def solve(k, x, y):
    n = 64 ** k
    a = [i for i in range(n)]
    for i in range(6 * k):
        if a[y] == x:
            return i
        a = upd(a)
    return -1

build()
k, m = map(int, input().split())


for _ in range(m):
    x, y = input().split()
    x = get(x)
    y = get(y)
    n = 64 ** k
    print(solve(k, x, y))
