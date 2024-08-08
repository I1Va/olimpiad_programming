from random import *

S = 0

def cuter(p, x, val):
    global S
    if x == 0:
        p.sort()
        S = max(S, val * min(p[2], p[3]))
        S = max(S, val * (p[3] // 2))
        return
    for i in range(4):
        if p[i] - val >= 0:
            pc = p.copy()
            pc[i] -= val
            cuter(pc, x - 1, val)

def get(val, a, b, c, d):
    global S
    S = 0
    cuter([a, b, c, d], 2, val)
    return S

def solve(l, r, a, b, c, d):
    while r - l > 2:
        m1 = (2 * l + r) // 3
        m2 = (2 * r + l) // 3
        if get(m1, a, b, c, d) < get(m2, a, b, c, d):
            l = m1
        else:
            r = m2
    p = [
        [get(l, a, b, c, d), l],
        [get((l + r) // 2, a, b, c, d), (l + r) // 2],
        [get(r, a, b, c, d), r]
    ]
    return [p[2][0], p[2][1]]

a, b, c, d = map(int, input().split())

ans_S = 0
cur = 0
mx = max([a, b, c, d])
for i in range(10000):
    l = randrange(1, mx + 1)
    r = randrange(1, mx + 2)
    res = solve(l, r, a, b, c, d)
    # print(l, r, res)
    if res[0] > ans_S:
        ans_S = res[0]
        cur = res[1]

print(ans_S // cur, cur)