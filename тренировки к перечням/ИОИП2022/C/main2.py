a = ["#", "$"]
sz = 15000 + 1
pows = [0] * (sz)
d = {}

def build():
    global a, sz, pows
    pows[0] = 1
    for i in range(1, sz):
        pows[i] = pows[i - 1] * 2
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
    res = 0
    for i in range(len(s) - 1, -1, -1):
        res += pows[6 * i] * d[s[i]]
    return res

build()

k, m = map(int, input().split())

for _ in range(m):
    x, y = input().split()
    x = get(x)
    y = get(y)
    flag = True
    for i in range(6 * k + 1):
        l = pows[i]
        c = y // l # Кол-во прошедших циклов
        pos = y - c * l # Позиция в текущем цикле
        val = pos * pows[6 * k - i] + c
        if val == x:
            print(i)
            flag = False
            break
    if (flag):
        print(-1)